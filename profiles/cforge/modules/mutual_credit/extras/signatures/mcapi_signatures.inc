<?php


/*
 * do callback derived from hook_transaction_operations
 */
function transaction_operation_do_sign($serial) {
  transaction_sign($serial, $GLOBALS['user']->uid);
}
/*
 * access callback derived from hook_transaction_operations
 */
function transaction_operation_access_sign($callbacks, $transaction) {
  if ($transaction->state != TRANSACTION_STATE_PENDING) return FALSE;
  return _transaction_check_access_callbacks($callbacks, $transaction);
}

/*
 * do callback derived from hook_transaction_operations
 */
function transaction_operation_do_signoff($serial) {
  $needed = array_filter(mcapi_get_signatories($serial));
  foreach (array_keys($needed) as $uid) {
    transaction_sign($serial, $uid);
  }
}
/*
 * access callback derived from hook_transaction_operations
 */
function transaction_operation_access_signoff($callbacks, $transaction) {
  if ($transaction->state != TRANSACTION_STATE_PENDING) return FALSE;
  return _transaction_check_access_callbacks($callbacks, $transaction);
}


/*
 * do callback derived from hook_transaction_operations
 */
function transaction_operation_do_undo_pending($serial) {
  transaction_state($serial, TRANSACTION_STATE_UNDONE);
}
/*
 * access callback derived from hook_transaction_operations
 */
function transaction_operation_access_undo_pending($callbacks, $transaction) {
  if ($transaction->state != TRANSACTION_STATE_PENDING) return FALSE;
  return _transaction_check_access_callbacks($callbacks, $transaction);
}


function mcapi_signall($form, $form_state, $account) {
  $serials = transactions_needing_sig_of_user($account->uid);
  $transactions = transaction_load_multiple(array(), array('serial' => $serials));
  $form['preview'] = transaction_view($transactions, variable_get('mcapi_sentence'));
  $form['uid'] = array(
    '#type' => 'hidden',
    '#value' => $account->uid
  );
  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Sign all')
  );
  return $form;
}

function mcapi_signall_submit($form, &$form_state) {
  $uid = &$form_state['values']['uid'];
  foreach (transactions_needing_sig_of_user($uid) as $serial) {
    transaction_sign($serial, $uid);
  }
  $form_state['redirect'] = 'user';
}


//check whether this transaction type needs signatures and change the state accordingly
//changes the status in the transaction form according to the settings for the transaction_type
function _set_form_state_to_pending(&$form, $form_state) {
   //read the settings and set the $form['state'] hidden widget
  $type = isset($form['type']['#value']) ? $form['type']['#value'] : $form['type']['#default_value'];//yuk
  if (in_array($type, _get_signable_transaction_types())) {
    $config = _signature_settings_default($type);
    if (@$config['participants'] || count(@$config['countersignatories'])) {
      $form['state'] = array(
        '#type' => 'value',
        '#value' => TRANSACTION_STATE_PENDING
      );
    }
  }
}


function list_pending_for_uid($uid, $currcodes = array()) {
  //couldn't be bothered with a theme callback for this
  $output = array(
    '#prefix' => '<div class = "user-pending">',
    'waiting on' => list_waiting_on_uid($uid, $currcodes),
    'waiting_not_on' => list_waiting_not_on_uid($uid, $currcodes),
    '#suffix' => '</div>'
  );
  return $output;
}

function list_waiting_on_uid($uid, $currcodes = array()) {
  $output = array();
  $serials = transactions_needing_sig_of_user($uid);
  if ($serials) {
    $transactions = transaction_load_multiple(array(), array('serial' => $serials));
    if (count($transactions) > 1) {
      $output[] = array(
        '#theme' => 'link',
        '#text' => t('Sign all'),
        '#path' => "user/$uid/signall",
        '#options' => array(
          'attributes' => array(),
          'html' => FALSE
        )
      );
    }
    $output[] = transaction_view($transactions, variable_get('mcapi_sentence'));
  }
  return $output;
}
function list_waiting_not_on_uid($uid, $currcodes = array()) {
  $output = array();
  $serials = db_query(
    "SELECT DISTINCT t.serial FROM {mcapi_transactions} t
     LEFT JOIN {mcapi_signatures} s ON t.serial = s.serial
     WHERE t.state = :pending
       AND (t.payer = $uid OR t.payee = $uid)
       AND (s.uid = $uid AND s.pending = 0)
      ORDER BY xid ASC",
    array(':pending' => TRANSACTION_STATE_PENDING)
  )->fetchCol();
  foreach($serials as $serial) {
    $output[] = transaction_view(transaction_load($serial), variable_get('mcapi_sentence'));
  }
  return $output;
}


function transactions_needing_sig_of_user($uid) {
  //assumes data integrity that all transactions referenced are in pending state
  return db_select("mcapi_signatures", 's')
    ->fields('s', array('serial'))
    ->condition('uid', $uid)
    ->condition('pending', TRUE)
    ->execute()
    ->fetchCol();
}
/*
 * transaction operation submit callback
 * resaves signatories from the transaction object and changes state if all are signed
 */
function transaction_sign($serial, $uid = NULL) {
  if (!$uid) $uid = $GLOBALS['user']->uid;
  //remove signatures one at a time
  //only the first transaction in the cluster can have signatures
  $transaction = transaction_load($serial);
  if ($transaction->pending_signatures[$uid]) {
    $transaction->pending_signatures[$uid] = 0;
    //this might change the state of the transaction
    mcapi_signatures_save($transaction);
    $remaining = array_filter($transaction->pending_signatures);
    if (empty($remaining)) {
      drupal_set_message(t('Transaction @serial is signed off', array('@serial' => $transaction->serial)));
      module_invoke_all('transaction_signed_off', $transaction);
    }
  }
  else {
    //access control should prevent this from happening, unless perhaps the page is refreshed
    drupal_set_message(t('Transaction #@serial is already signed by @name',
      array('@serial' => $transaction->serial, '@name' => user_load($uid)->name)
    ));
  }

}


/*
 * write the signature for each transaction to the database.
 * $transaction->pending signatures is an array
 * array(
 *   $uid => $signature_needed BOOLEAN
 * )
 * Every value should be 1 when the transaction is created
 */
function mcapi_signatures_save($transaction) {
  $old_state = $transaction->state;
  //need to check property 'pending_signatures' because it may not have been declared
  if (!empty($transaction->pending_signatures)) {
    //save all the signatures whether or not they have been signed
    foreach ($transaction->pending_signatures as $uid => $pending) {
      $values[] = "( $transaction->serial, $uid, ". intval($pending)." )";
    }
    db_query("REPLACE INTO {mcapi_signatures} (serial, uid, pending) VALUES ". implode(', ', $values));
  }
  $new_state = count(array_filter($transaction->pending_signatures)) ? TRANSACTION_STATE_PENDING : TRANSACTION_STATE_FINISHED;
  if ($new_state != $old_state) {
    //change the state of the loaded object, then change the state in the db
    $transaction->state = $new_state;
    //because the transaction is already written, and to improve integrity, we reset the state here
    transaction_state(
      $transaction->serial,
      $new_state
    );
  }
}



function mcapi_signatures_config($form, $form_state) {
  module_load_include('inc', 'mcapi');
  $w = 0;
  $form = array('#tree' => TRUE);
  foreach (_get_signable_transaction_types() as $type) {
    $var_name = 'mcapi_signatures_'.$type;
    $settings = @$form_state['values'][$var_name] ? $form_state['values'][$var_name] : _signature_settings_default($type);
    $form[$var_name] = array(
      '#title' => $type,
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#id' => $type,
      'participants' => array(
        '#title' => t('Both participants must sign'),
        '#description' => t("Logged in user signs automatically"),
        '#type' => 'checkbox',
        '#default_value' => $settings['participants']
      ),
      'countersignatories' => array(
        '#title' => t('Counter-signers'),
        '#description' => t('Choose one or more users'),
        '#type' => 'user_chooser_few',
        '#callback' => 'user_chooser_segment_roles',
        '#args' => array(DRUPAL_AUTHENTICATED_RID),
        '#default_value' => $settings['countersignatories'],
        '#multiple' => TRUE,
        '#required' => FALSE,
      ),
      'notify' => array(
        '#title' => t("Send 'pending' notification"),
        '#description' => t("Use the email template on this page to notify all signatories"),
        '#type' => 'checkbox',
        '#default_value' => $settings['notify'],
        '#weight' => 5,
      ),
      '#weight' => $w++
    );
  }
  $mail_def = variable_get('mcapi_sign_notify_template', array());
  $form['mcapi_sign_notify_template'] = array(
    '#title' => t('Signature notification'),
    '#description' => implode(' ', array(
      t('Compose the email notifying signatories that a transaction needs their attention.'),
      t('Use the tokens provided.'),
      t("To notify users when a transaction is completed, use the action and triggers: !link",
        array('!link' => l('admin/config/system/actions', 'admin/config/system/actions')))
    )),
    '#type' => 'fieldset',
    'subject' => array(
      '#title' => t('Subject'),
      '#type' => 'textfield',
      '#default_value' => isset($mail_def['subject']) ? $mail_def['subject'] : t('Your signature required'),
      '#required' => TRUE,
    ),
    'body' => array(
      '#title' => t('Body'),
      '#type' => 'textarea',
      '#default_value' => isset($mail_def['body']) ? $mail_def['body'] : '[transaction:url:absolute]',
      '#required' => TRUE,
      '#weight' => 1
    ),
    '#weight' => $w++
  );
  $form['token_tree'] = array(
    '#theme' => 'token_tree',
    '#token_types' => array('transaction', 'user', 'site'),
    '#global_types' => FALSE,
    '#weight' => $w++
  );
  return system_settings_form($form);
}


function _mcapi_signatures_transaction_state($transaction, $new_state) {
  $config = _signature_settings_default($transaction->type);
  $params = array('transaction' => $transaction);
  $uid = &$GLOBALS['user']->uid;
  if ($new_state == TRANSACTION_STATE_PENDING) {
    if ($config['participants']) {
      $transaction->pending_signatures[$transaction->payer] = $uid == $transaction->payer ? 0 : 1;
      $transaction->pending_signatures[$transaction->payee] = $uid == $transaction->payee ? 0 : 1;
    }
    $config['countersignatories']= array_filter((array)$config['countersignatories']);
    foreach($config['countersignatories'] as $counter_uid) {
      $transaction->pending_signatures[$counter_uid] = $uid == $counter_uid ? 0 : 1;
    }
    mcapi_signatures_save($transaction);
    $params['mail_template'] = variable_get('mcapi_sign_notify_template', array());
  }
  elseif ($new_state == TRANSACTION_STATE_UNDONE) {
    db_delete('mcapi_signatures')->condition('serial', $transaction->serial)->execute();
  }
  //send the mail, using the module settings for this transaction
  if (!empty($params['mail_template']) && $config['notify']) {
    foreach(user_load_multiple(array_keys(array_filter($transaction->pending_signatures))) as $account) {
      $params['user'] = $account;
      drupal_mail('mcapi_signatures', 'blah', $account->mail, user_preferred_language($account), $params);
    }
  }
}

/*
 * implements hook_mail
 */
function mcapi_signatures_mail($key, &$message, $params) {
  $options = array('language' => $message['language'], 'sanitize' => FALSE);
  $message['subject'] = token_replace($params['mail_template']['subject'], $params, $options);
  $message['body'][] = token_replace($params['mail_template']['body'], $params, $options);
}

function _signature_settings_default($type) {
  if ($setting = variable_get('mcapi_signatures_'.$type, 0)) return $setting;
  return array(
    'participants' => $type == 'mass' ? FALSE : TRUE,
    'countersignatories' => array(),
    'notify' => $type == 'mass' ? FALSE : TRUE
  );
}

function _mcapi_signatures_transaction_operations() {
  return array(
    'sign' => array(
      'imperative' => 'Sign',
      'description' => 'Sign a pending transaction',
      'sure_message' => t('Are you sure you want to sign?'),
      'weight' => 2,
      'file_extension' => 'inc'
    ),
    'undo_pending' => array(
      'imperative' => 'Undo',
      'description' => t('Undo pending transactions'),
      'sure_message' => t('Are you sure you want to cancel this pending transaction?'),
      'weight' => 3,
      'redirect' => 'user',
      'file_extension' => 'inc'
    ),
    'signoff' => array(
      'imperative' => 'Sign off',
      'description' => 'Sign a pending transaction on behalf of all signatories',
      'sure_message' => t('Are you sure you want to sign off this transaction?'),
      'weight' => 5,
      'file_extension' => 'inc'
    )
  );
}

//utility function
//gets all the transaction types and excludes a few that we know aren't suitable for configuring
function _get_signable_transaction_types() {
  $types = array_diff(mcapi_get_types(), array('child', 'undo', 'undone', 'remote payment', 'remote receipt'));
  sort($types);
  return $types;
}
