<?php

//helper function for building up the form element
function _process_uchoo_few($element, &$form_state) {
  $uids = _uchoo_query($element);
  if (count($uids) < variable_get('user_chooser_threshhold', 50)) {
    $element['#options'] = uchoo_display_all($uids, FALSE);
    $element['#theme'] = 'select';
    if (!$element['#multiple']) {
      $firstitem = $element['#required'] ? t('Please choose...') : t('<none>');
      $element['#options'] = array('' => $firstitem) + $element['#options'];
    }
    $element = form_process_select($element);
    if (empty($element['#default_value']) && !empty($form_state['values'][$element['#name']])) {
      $element['#default_value'] = $form_state['values'][$element['#name']];
    }
  }
  else {
    $uids = array_splice($uids, 0, variable_get('user_chooser_threshhold', 50));
    $element['#theme'] = 'textfield';
    $element['#autocomplete_path'] = implode('/', array(
      'system/ajax/uchoo',
      $form_state['complete form']['form_build_id']['#value'],
      implode(',', $element['#array_parents'])
    ));
    if (!empty($form_state['values'][$element['#name']])) {
      $element['#value'] = $form_state['values'][$element['#name']];
    }
    if (!isset($element['#description'])) {
      $fields = variable_get('user_chooser_matching', array('u.uid', 'u.name', 'u.mail'));
      if (in_array('u.uid', $fields)) $accepts[] = t('user ID');
      if (in_array('u.username', $fields)) $accepts[] = t('username');
      if (in_array('u.mail', $fields)) $accepts[] = t('email');
      if ($element['#multiple']) {
        $element['#description'] =  t('Accepts @types; comma separated', array('@types' => implode(', ', $accepts)));
      }
      else {
        $element['#description'] =  t('Accepts @types', array('@types' => implode(', ', $accepts)));
      }
    }
    if ($element['#multiple']) {
      $element['#attributes']['style'] = 'width:100%;';
    }
    $form_state['cache'] = TRUE;
  }
  return $element;
}

/*
 * Settings form to set global restrictions
 */
function uchoo_config_form() {
  $form = array (
    'user_chooser_threshhold' => array(
      '#title' => t('Autocomplete threshhold'),
      '#description' => t('Below this number of items, a select box is shown, above it, an autocomplete field'),
      '#type' => 'textfield',
      '#size' => 3,
      '#maxlength' => 3,
      '#default_value' => variable_get('user_chooser_threshhold', 50),
      '#element_validate' => array('_element_validate_integer'),
      '#weight' => 1
    ),
    'user_chooser_sort' => array(
      '#title' => t('Select widget - order by'),
      '#description' => t('The select field will show results in what order'),
      '#type' => 'radios',
      '#options' => array(
        0 => t('User ID'),
        1 => t('Alphabetical')
      ),
      '#default_value' => variable_get('user_chooser_sort', 0),
      '#weight' => 2
    ),
    'user_chooser_matching' => array(
      '#title' => t('Autocomplete widget - match against'),
      '#description' => t('The autocomplete widget will get matches based on which fields?') .' '. t('Only applies to permission role and conditions based widgets.'),
      '#type' => 'checkboxes',
      '#options' => array(
        'u.uid' => t('user ID'),
        'u.name' => t('username'),
        'u.mail' => t('email'),
      ),
      '#default_value' => variable_get('user_chooser_matching', array('u.uid', 'u.name', 'u.mail')),
      '#weight' => 3
    ),
    'user_chooser_format' => array(
      '#title' => t('Display format'),
      '#description' => t('Use at least one of the tokens below'),
      '#type' => 'textfield',
      '#maxlength' => 64,
      '#required' => TRUE,
      '#default_value' => variable_get('user_chooser_format', '[user:name]'),
    ),
    'token_tree' => array(
      '#theme' => 'token_tree',
      '#token_types' => array('user'),
      '#global_types' => FALSE,
      '#weight' => 4
    ),
  );
  return system_settings_form($form);
}


//form element callback
//checks that all submited values are in fact in the list.
function user_chooser_few_validate(&$element, &$form_state) {

  if (isset($element['#unidentified']) && count($element['#unidentified'])) {//unidentified users from uchoo_set_value
    $message = t('Unknown users: @users', array('@users' => implode($element['#unidentified'])));
    if (!$element['#multiple'] || $element['#multiple_fail_alert'] > 1) form_error($element, $message);
    elseif($element['#multiple'] && $element['#multiple_fail_alert'] == 1) drupal_set_message($message, 'warning');
  }

  if (empty($element['#allow_me']) && $key = array_search($GLOBALS['user']->uid, (array)$element['#value']) && is_integer($key)) {
    unset($element['#value'][$key]);
    if (!$element['#multiple'] || in_array($element['#type'], array('user_chooser_callback', 'user_chooser_preselect'))) {
      form_error($element, t("You can't put yourself in '@name'", array('@name' => $element['#title'])));
    }
  }
}


//takes an array of $uids and formats them for display
function uchoo_display_all($uids, $username_key = TRUE) {
  $names = array();
  $format = variable_get('user_chooser_format', '[user:name]');
  foreach (user_load_multiple($uids) as $account) {
    $key = $username_key ? $account->name :$account->uid;
    $names[$key] = token_replace($format, array('user' => $account));
  }
  if (variable_get('user_chooser_sort')) {
    asort($names);
  }
  return $names;
}




/*
 * ajax menu callback
 * the autocomplete a textfield uses get and so you have no access to the form and can't retrieve the triggering element
 * so this is a special callback which expects the path and the $element['name']
 * then it retrieves the triggering element and returns only valid users
 */
function uchoo_autocomplete() {
  $output = array();
  $args = func_get_args();
  $string = array_pop($args);
  $parents = explode(',', array_pop($args));
  $form_build_id = array_pop($args);
  //see ajax_get_form
  $form = form_get_cache($form_build_id, form_state_defaults());
  if ($form) {
    $element = uchoo_get_element($form, $parents);
    // Since some of the submit handlers are run, redirects need to be disabled.
    $form_state['no_redirect'] = TRUE;
    $form_state['rebuild_info']['copy']['#build_id'] = TRUE;
    $form_state['rebuild_info']['copy']['#action'] = TRUE;
    //we don't need to process the form - we just wanted the $element
    //this has to work for multiple select fields, where we autocomplete the whole string from the last incomplete name
    $array = drupal_explode_tags($string);
    $last_string = trim(array_pop($array));
    $prefix = implode(', ', $array);
    if ($prefix) $prefix .= ', ';

    $suggested_uids = _uchoo_query($element, 10, $last_string);
    $names = uchoo_display_all($suggested_uids, TRUE);
    foreach ($names as $name => $formatted) {
      //exclude from the suggestions any names already in the $array
      if (in_array($name, $array)) continue;
      $output[$prefix.$name] = $formatted;
    }
  }
  drupal_json_output($output);
  //not sure but without die, then some other stuff is appended to the json and it breaks
  //{"drupal7":"drupal7 (1)"} //wanted
  die();
}

function _uchoo_query($element, $limit = 0, $string = '') {
  $callback = &$element['#callback'];
  if (!function_exists($callback)) {
    drupal_set_message('user_chooser callback not found: '.$callback);
    return array();
  }
  $query = _uchoo_query_helper($element, $limit, $string);
  $callback($query, $element['#args'], $string);
  return $query->execute()->fetchCol();
}

function _uchoo_query_helper($element, $limit = 0, $string = '') {
  $query = db_select('users', 'u')
    ->fields('u', array('uid'))
    ->condition('u.uid', 0, '!=');
  if ($limit) {
    $query->range(0, $limit);
  }
  if (strlen($string)) {
    $or = db_or();
    $match_against = variable_get('user_chooser_matching', array('u.uid', 'u.name', 'u.mail'));
    $like_string = db_like($string) .'%';
    foreach ($match_against as $field) {
      $or->condition($field, $like_string, 'LIKE');
    }
    $query->condition($or);
  }
  if (empty($element['#allow_blocked'])) {
    $query->condition('u.status', TRUE);
  }
  if (!empty($element['#exclude'])) {
    $query->condition('u.uid', $element['#exclude'], '<>');
  }
  if (!variable_get('user_chooser_sort')) {
    $query->orderby('u.uid', 'ASC');
  }
  return $query;
}

/*
 * These form value callbacks have to go in the module file
 * because the form include isn't made in time.
 */

/*
 * value_callback to replace form_type_ELEMENT_TYPE_value
 * declared in the element_info
 */
function form_type_user_chooser_few_value(&$element, $edit = FALSE, &$form_state) {
  if ($edit === FALSE || $edit === '') return;
  //check that the valid users only are selected, and mark the items which can't be found
  $uids = array();
  $invalids = array();
  $match_against = variable_get('user_chooser_matching', array('u.uid', 'u.name', 'u.mail'));
  //this is an emergency fix
  //the trouble is, with a normal select widget we definitely do want to add a uid condition
  //however we don't know until the element is processed
  //whether we are filtering with uids from select widget or strings from autocomplete
  $match_against += array('u.uid');
  if (is_string($edit) && $element['#multiple']) {
    $edit = explode(',', $edit);
  }
  foreach ((array)$edit as $key => $string) {
    $conditions = db_or();
    foreach ($match_against as $field) {
      $conditions->condition($field, trim($string));
    }
    $uids[$key] = db_select('users', 'u')
      ->fields('u', array('uid'))
      ->condition('u.uid', 0, '!=')
      ->condition($conditions)
      ->execute()
      ->fetchField();
    if (!$uids[$key]) {//users who don't exist
      $element['#unidentified'][] = $string;
    }
  }
  if (!$element['#multiple']) {
    $uids = array_pop($uids);//so we return one value not an array
  }
  else $uids = array_filter($uids);
  drupal_array_set_nested_value($form_state['values'], $element['#array_parents'], $uids);
  return $uids;
}

/*
 * value_callback to replace form_type_ELEMENT_TYPE_value
 * declared in the element_info
 */
function form_type_user_chooser_many_value(&$element, $edit = FALSE, &$form_state) {
  if ($edit === FALSE) return;
  if ($element['#config'] == TRUE) return $edit;
  $element['#callback'] = strtok($edit, ':');
  $element['#args'] = array(strtok(':'));

  $uids = user_chooser_segment($element['#callback'],  $element['#args'], $element);

  drupal_array_set_nested_value($form_state['values'], $element['#array_parents'], $uids);
  //bypass validation because this value is not congruent with the select field it came from
  $element['#validated'] = TRUE;
  return $uids;
}


/*
 * Returns the element from the given path.
 */
function uchoo_get_element($form, $path) {
  $element = $form;
  foreach ($path as $key) {
    $element = $element[$key];
  }
  return $element;
}
