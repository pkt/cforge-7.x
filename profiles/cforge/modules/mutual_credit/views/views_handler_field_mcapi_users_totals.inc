<?php
// $Id:

/**
 * @file
 * Given the user, this shows the balance.
 * choose ONE currency from a list of options.
 * note that this is a bit of a pseudo field, since it makes a separate call to the transaction controller layer.
 */
class views_handler_field_mcapi_users_totals extends views_handler_field {

  var $fetched;

  function query() {
    $this->ensure_my_table();
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['currcode'] = array('default' => array());
    $options['total'] = array('default' => 'balance');
    return $options;
  }

  function options_form(&$form, &$form_state) {
    $currencies = &drupal_static('currencies');
    module_load_include('inc', 'mcapi');
    $form['currcode'] = currency_picker_element(array_keys($currencies), $this->options['currcode'], TRUE);

    $form['total'] = array(
      '#title' => t('Aggregate'),
      '#description' => t('How do you want to summarise the the transaction totals?'),
      '#type' => 'radios',
      '#options' => array(
        'count' => t('Number of transactions'),
        'gross_in' => t('Gross income'),
        'gross_out' => t('Gross expenditure'),
        'balance' => t('Balance'),
        'participation' => t('Participation')
      ),
      '#default_value' => $this->options['total']
    );
    parent::options_form($form, $form_state);
  }

  function render($values) {
    $uid = &$values->uid;
    $currcodes = empty($this->options['currcode']) ? array_keys(currencies_load(user_load($uid))): $this->options['currcode'];
    $key = $this->options['total'];
    $elements = array();
    foreach ($currcodes as $currcode) {
      if (empty($this->fetched[$uid][$currcode])) {
        $this->fetched[$uid][$currcode] = transaction_totals($uid, $currcode);
      }
      $quant = $this->fetched[$uid][$currcode]->$key;
      if ($key == 'count') {
        $elements[$currcode] = array('#type' => 'markup', '#markup' => $quant);
      }
      else {
        $elements[$currcode] = array(
          '#theme' => 'worth_item',
          '#quantity' => $quant,
          '#currcode' => $currcode
        );
      }
    }
    return $elements;
  }
}
