<?php
// $Id:

/**
 * @file
 * Field handler to retrieve the running balance by adding the previous transactions
 * NB this doesn't apply to the worth_field and mcapi_transactions table, only to the transaction_index table
 * @ingroup views_field_handlers
 */
class views_handler_field_mcapi_index_balance extends views_handler_field {

  var $uid;

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    $currcode = &$values->{$this->aliases['currcode']};
    if (empty($this->uid)) {
      $arg = array_search('uid1', array_keys($this->view->argument));
      if (is_numeric($arg)) {
        $this->uid = $this->view->args[$arg];
      }
      elseif (isset($this->view->filter['uid1'])) {
        $this->uid = $this->view->filter['uid1']->value['value'];
      }
      else {
        drupal_set_message("Running balance requires filter or contextual filter 'Transaction index: 1st user'", 'error', FALSE);
        return 'error';
      }
    }
    return array(
      '#theme' => 'worth_item',
      '#currcode' => $currcode,
      '#quantity' => db_query(
        "SELECT SUM(diff) FROM {mcapi_index}
          WHERE uid1 = :uid
          AND xid <= :xid
          AND currcode = :currcode",
        array(
          ':xid' => $values->{$this->aliases['xid']},
          ':uid' => $this->uid,
          ':currcode' => $currcode
        )
      )->fetchField()
    );
  }
}