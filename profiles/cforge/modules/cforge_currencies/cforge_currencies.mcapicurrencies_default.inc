<?php

/*
 * implements hook_mcapicurrencies_default
 * simply copies the currency in the default currency variable, used for single currency systems
 */
function cforge_currencies_mcapicurrencies_default_alter($currencies) {
  $def = &$currencies['credunit']->data;
  $def->issuance = 'acknowledgement';
  $def->display = array(
    'format' => '<strong>CC</strong>[quantity]',
    'delimiter' => ':',
    'divisions' => CURRENCY_DIVISION_MODE_CUSTOM,
    'divisions_setting' => "0|00\n25|15 mins\n50|30 mins\n75|45mins",
    'zero' => '',
  );
  $def->transaction_view_access = array(
    TRANSACTION_STATE_FINISHED => array(
      'transaction_access_callback_perm_transact' => 'transaction_access_callback_perm_transact',
    ),
    TRANSACTION_STATE_UNDONE => array(
      'transaction_access_callback_perm_manage_all' => 'transaction_access_callback_perm_manage_all',
    ),
  );

  if (module_exists('mcapi_signatures')) {
    $def->transaction_view_access[TRANSACTION_STATE_PENDING] = array(
      'mcapi_access_authenticated' => 'transaction_access_authenticated',
    );
  }
  //upgraded sites won't be reading this
  $def->limits = array(
    'limits_callback' => 'limits_global',
    'limits_global' => array(
      'min' => '-50',
      'max' => '50',
    ),
    'personal' => FALSE,
    'skip' => array('owner', 'auto')
  );

  $currencies['escrow']->disabled = TRUE;
}