<?php
//ensure we have the role id constants
module_load_include('profile', 'cforge');

/**
 * Implementation of hook_default_view_views_alter()
 */
function cforge_currencies_views_default_views_alter(&$views) {

  $view = new view;
  $view->name = 'transactions';
  $view->description = '';
  $view->tag = 'mcapi';
  $view->base_table = 'mcapi_transactions';
  $view->human_name = 'transactions';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'transactions';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    DRUPAL_AUTHENTICATED_RID => DRUPAL_AUTHENTICATED_RID,
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '25';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'name' => 'name',
    'name_1' => 'name_1',
    'transaction_description' => 'transaction_description',
    'worth' => 'worth',
    'view' => 'view',
  );
  /* Relationship: Transaction: Payee */
  $handler->display->display_options['relationships']['payee']['id'] = 'payee';
  $handler->display->display_options['relationships']['payee']['table'] = 'mcapi_transactions';
  $handler->display->display_options['relationships']['payee']['field'] = 'payee';
  $handler->display->display_options['relationships']['payee']['required'] = 0;
  /* Relationship: Transaction: Payer */
  $handler->display->display_options['relationships']['payer']['id'] = 'payer';
  $handler->display->display_options['relationships']['payer']['table'] = 'mcapi_transactions';
  $handler->display->display_options['relationships']['payer']['field'] = 'payer';
  $handler->display->display_options['relationships']['payer']['required'] = 0;


/* Field: Transaction: Created */
$handler->display->display_options['fields']['created']['id'] = 'created';
$handler->display->display_options['fields']['created']['table'] = 'mcapi_transactions';
$handler->display->display_options['fields']['created']['field'] = 'created';
$handler->display->display_options['fields']['created']['date_format'] = 'short';
/* Field: Transaction: Serial number */
$handler->display->display_options['fields']['serial']['id'] = 'serial';
$handler->display->display_options['fields']['serial']['table'] = 'mcapi_transactions';
$handler->display->display_options['fields']['serial']['field'] = 'serial';
$handler->display->display_options['fields']['serial']['link_to_transaction'] = 1;

  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'payee';
  $handler->display->display_options['fields']['name']['label'] = t('Payee');
  /* Field: User: Name */
  $handler->display->display_options['fields']['name_1']['id'] = 'name_1';
  $handler->display->display_options['fields']['name_1']['table'] = 'users';
  $handler->display->display_options['fields']['name_1']['field'] = 'name';
  $handler->display->display_options['fields']['name_1']['relationship'] = 'payer';
  $handler->display->display_options['fields']['name_1']['label'] = t('Payer');
  /* Field: Transaction: Description */
  $handler->display->display_options['fields']['transaction_description']['id'] = 'transaction_description';
  $handler->display->display_options['fields']['transaction_description']['table'] = 'field_data_transaction_description';
  $handler->display->display_options['fields']['transaction_description']['field'] = 'transaction_description';
  $handler->display->display_options['fields']['transaction_description']['label'] = t('Description');
  /* Field: Transaction: Worth */
  $handler->display->display_options['fields']['worth']['id'] = 'worth';
  $handler->display->display_options['fields']['worth']['table'] = 'field_data_worth';
  $handler->display->display_options['fields']['worth']['field'] = 'worth';
  $handler->display->display_options['fields']['worth']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['worth']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['worth']['hide_empty'] = 0;
  $handler->display->display_options['fields']['worth']['empty_zero'] = 0;
  $handler->display->display_options['fields']['worth']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['worth']['click_sort_column'] = 'currcode';
  $handler->display->display_options['fields']['worth']['type'] = 'worth_field';
  $handler->display->display_options['fields']['worth']['field_api_classes'] = 0;
  /* Field: Transaction: Operations */
  $handler->display->display_options['fields']['operations']['id'] = 'operations';
  $handler->display->display_options['fields']['operations']['table'] = 'mcapi_transactions';
  $handler->display->display_options['fields']['operations']['field'] = 'operations';
  $handler->display->display_options['fields']['operations']['link_to_transaction'] = 0;
  /* Sort criterion: Transaction: created */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'mcapi_transactions';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  $handler->display->display_options['sorts']['created']['granularity'] = 'hour';
  /* Filter criterion: Transaction: State */
  $handler->display->display_options['filters']['state']['id'] = 'state';
  $handler->display->display_options['filters']['state']['table'] = 'mcapi_transactions';
  $handler->display->display_options['filters']['state']['field'] = 'state';
  $handler->display->display_options['filters']['state']['value'] = array(
    TRANSACTION_STATE_FINISHED => TRANSACTION_STATE_FINISHED,
  );
  /* Filter criterion: Transaction: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'mcapi_transactions';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['operator'] = 'not in';
  $handler->display->display_options['filters']['type']['value'] = array(
    'child' => 'child',
    'mass' => 'mass',
  );
  $handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['label'] = 'Type';
  $handler->display->display_options['filters']['type']['expose']['use_operator'] = FALSE;
  $handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
  $handler->display->display_options['filters']['type']['expose']['required'] = FALSE;
  $handler->display->display_options['filters']['type']['expose']['remember'] = FALSE;
  $handler->display->display_options['filters']['type']['expose']['multiple'] = FALSE;

  /* Display: Transactions */
  $handler = $view->new_display('page', 'Transactions', 'transactions');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'transactions/log';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'Log';
  $handler->display->display_options['menu']['weight'] = 10;
  $handler->display->display_options['menu']['name'] = 'navigation';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Transactions';
  $handler->display->display_options['tab_options']['weight'] = '0';

  /* Display: Who gave what */
  $handler = $view->new_display('block', 'Who gave what', 'who_gave_what');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'name' => 'name',
    'transaction_description' => 'transaction_description',
  );
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: User: Nom */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'payee';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  /* Field: Transaction: Description */
  $handler->display->display_options['fields']['transaction_description']['id'] = 'transaction_description';
  $handler->display->display_options['fields']['transaction_description']['table'] = 'field_data_transaction_description';
  $handler->display->display_options['fields']['transaction_description']['field'] = 'transaction_description';
  $handler->display->display_options['fields']['transaction_description']['label'] = '';
  $handler->display->display_options['fields']['transaction_description']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['transaction_description']['alter']['text'] = "[name] gave [transaction_description]";
  $handler->display->display_options['fields']['transaction_description']['element_label_colon'] = FALSE;
  t('[name] gave [@name]', array('@name' => 'transaction_description'));


  $translatables['transactions'] = array(
    t('Payee'),
    t('Payer'),
    t('Serial number'),
    t('Name'),
    t('Worth'),
    t('Transactions'),
    t('[name] gave [transaction_description]')
  );

  $views[$view->name] = $view;

  drupal_load('profile', 'cforge');//for the constants
  $view = new view;
  $view->name = 'transactions_all';
  $view->description = 'For admin or accountant to manage transactions';
  $view->tag = 'mcapi';
  $view->base_table = 'mcapi_transactions';
  $view->human_name = 'Administer transactions';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Transaction management';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(RID_COMMITTEE => RID_COMMITTEE);
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Remise à zéro';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'created' => 'created',
    'payee' => 'payee',
    'payer' => 'payer',
    'type' => 'type',
    'state' => 'state',
    'worth' => 'worth',
    'field_cat' => 'field_cat',
  );
  $handler->display->display_options['style_options']['default'] = 'created';
  $handler->display->display_options['style_options']['info'] = array(
    'participant' => array(
      'sortable' => 0,
      'align' => '',
      'separator' => '',
    ),
    'payee' => array(
      'sortable' => 0,
      'align' => '',
      'separator' => '',
    ),
    'payer' => array(
      'sortable' => 0,
      'align' => '',
      'separator' => '',
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
    ),
    'type' => array(
      'sortable' => 0,
      'align' => '',
      'separator' => '',
    ),
    'state' => array(
      'sortable' => 0,
      'align' => '',
      'separator' => '',
    ),
    'worth' => array(
      'sortable' => 0,
      'align' => '',
      'separator' => '',
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 1;
  $handler->display->display_options['style_options']['order'] = 'desc';
  $handler->display->display_options['style_options']['summary'] = 'All transactions, filtered';
  /* Header: Global: Zone de texte */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = FALSE;
  $handler->display->display_options['header']['area']['content'] = 'All transactions can be seen from here. Use the filters to list what you need.';
  /* Relationship: Transaction: Payee */
  $handler->display->display_options['relationships']['payee']['id'] = 'payee';
  $handler->display->display_options['relationships']['payee']['table'] = 'mcapi_transactions';
  $handler->display->display_options['relationships']['payee']['field'] = 'payee';
  $handler->display->display_options['relationships']['payee']['required'] = 1;
  /* Relationship: Transaction: Payer */
  $handler->display->display_options['relationships']['payer']['id'] = 'payer';
  $handler->display->display_options['relationships']['payer']['table'] = 'mcapi_transactions';
  $handler->display->display_options['relationships']['payer']['field'] = 'payer';
  $handler->display->display_options['relationships']['payer']['required'] = 1;
  /* Champ: Transaction: created */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'mcapi_transactions';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Recorded';
  $handler->display->display_options['fields']['created']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['created']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['created']['hide_empty'] = 0;
  $handler->display->display_options['fields']['created']['empty_zero'] = 0;
  $handler->display->display_options['fields']['created']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  /* Champ: Transaction: Serial number */
  $handler->display->display_options['fields']['serial']['id'] = 'serial';
  $handler->display->display_options['fields']['serial']['table'] = 'mcapi_transactions';
  $handler->display->display_options['fields']['serial']['field'] = 'serial';
  $handler->display->display_options['fields']['serial']['label'] = '';
  $handler->display->display_options['fields']['serial']['exclude'] = TRUE;
  $handler->display->display_options['fields']['serial']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['serial']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['serial']['hide_empty'] = 0;
  $handler->display->display_options['fields']['serial']['empty_zero'] = 0;
  $handler->display->display_options['fields']['serial']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['serial']['link_to_transaction'] = 0;
  /* Champ: Utilisateur: Nom */
  $handler->display->display_options['fields']['name_1']['id'] = 'name_1';
  $handler->display->display_options['fields']['name_1']['table'] = 'users';
  $handler->display->display_options['fields']['name_1']['field'] = 'name';
  $handler->display->display_options['fields']['name_1']['relationship'] = 'payer';
  $handler->display->display_options['fields']['name_1']['label'] = 'Payer';
  $handler->display->display_options['fields']['name_1']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['name_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['name_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['name_1']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['name_1']['link_to_user'] = 1;
  $handler->display->display_options['fields']['name_1']['overwrite_anonymous'] = 0;
  $handler->display->display_options['fields']['name_1']['format_username'] = 1;
  /* Champ: Utilisateur: Nom */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'payee';
  $handler->display->display_options['fields']['name']['label'] = 'Payee';
  $handler->display->display_options['fields']['name']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['name']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name']['empty_zero'] = 0;
  $handler->display->display_options['fields']['name']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['name']['link_to_user'] = 1;
  $handler->display->display_options['fields']['name']['overwrite_anonymous'] = 0;
  $handler->display->display_options['fields']['name']['format_username'] = 1;
  /* Champ: Transaction: Worth */
  $handler->display->display_options['fields']['worth']['id'] = 'worth';
  $handler->display->display_options['fields']['worth']['table'] = 'field_data_worth';
  $handler->display->display_options['fields']['worth']['field'] = 'worth';
  $handler->display->display_options['fields']['worth']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['worth']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['worth']['hide_empty'] = 0;
  $handler->display->display_options['fields']['worth']['empty_zero'] = 0;
  $handler->display->display_options['fields']['worth']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['worth']['click_sort_column'] = 'currcode';
  $handler->display->display_options['fields']['worth']['type'] = 'worth_field';
  $handler->display->display_options['fields']['worth']['field_api_classes'] = 0;
  /* Champ: Transaction: Description */
  $handler->display->display_options['fields']['transaction_description']['id'] = 'transaction_description';
  $handler->display->display_options['fields']['transaction_description']['table'] = 'field_data_transaction_description';
  $handler->display->display_options['fields']['transaction_description']['field'] = 'transaction_description';
  $handler->display->display_options['fields']['transaction_description']['label'] = '';
  $handler->display->display_options['fields']['transaction_description']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['transaction_description']['alter']['make_link'] = 1;
  $handler->display->display_options['fields']['transaction_description']['alter']['path'] = 'transaction/[serial]';
  $handler->display->display_options['fields']['transaction_description']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['transaction_description']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['transaction_description']['hide_empty'] = 0;
  $handler->display->display_options['fields']['transaction_description']['empty_zero'] = 0;
  $handler->display->display_options['fields']['transaction_description']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['transaction_description']['type'] = 'text_plain';
  $handler->display->display_options['fields']['transaction_description']['settings'] = array(
    'trim_length' => '600',
  );
  $handler->display->display_options['fields']['transaction_description']['field_api_classes'] = 0;
  /* Champ: Transaction: State */
  $handler->display->display_options['fields']['state']['id'] = 'state';
  $handler->display->display_options['fields']['state']['table'] = 'mcapi_transactions';
  $handler->display->display_options['fields']['state']['field'] = 'state';
  $handler->display->display_options['fields']['state']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['state']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['state']['hide_empty'] = 0;
  $handler->display->display_options['fields']['state']['empty_zero'] = 0;
  /* Champ: Transaction: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'mcapi_transactions';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['type']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['type']['hide_empty'] = 0;
  $handler->display->display_options['fields']['type']['empty_zero'] = 0;
  /* Champ: Echange : Actions */
  $handler->display->display_options['fields']['operations']['id'] = 'operations';
  $handler->display->display_options['fields']['operations']['table'] = 'mcapi_transactions';
  $handler->display->display_options['fields']['operations']['field'] = 'operations';
  $handler->display->display_options['fields']['operations']['label'] = '';
  $handler->display->display_options['fields']['operations']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['operations']['link_to_transaction'] = 0;
  /* Sort criterion: Transaction: created */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'mcapi_transactions';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  $handler->display->display_options['sorts']['created']['granularity'] = 'minute';
  /* Filter criterion: Transaction: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'mcapi_transactions';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['group'] = 0;
  $handler->display->display_options['filters']['type']['exposed'] = TRUE;
  $handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['label'] = 'Type';
  $handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
  $handler->display->display_options['filters']['type']['expose']['multiple'] = 1;
  $handler->display->display_options['filters']['type']['expose']['reduce'] = 0;
  /* Filter criterion: Utilisateur: Nom */
  $handler->display->display_options['filters']['uid']['id'] = 'uid';
  $handler->display->display_options['filters']['uid']['table'] = 'users';
  $handler->display->display_options['filters']['uid']['field'] = 'uid';
  $handler->display->display_options['filters']['uid']['relationship'] = 'payee';
  $handler->display->display_options['filters']['uid']['value'] = '';
  $handler->display->display_options['filters']['uid']['group'] = 0;
  $handler->display->display_options['filters']['uid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['uid']['expose']['operator_id'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['label'] = 'Payee';
  $handler->display->display_options['filters']['uid']['expose']['operator'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['identifier'] = 'uid';
  $handler->display->display_options['filters']['uid']['expose']['multiple'] = FALSE;
  $handler->display->display_options['filters']['uid']['expose']['reduce'] = 0;
  /* Filter criterion: Utilisateur: Nom */
  $handler->display->display_options['filters']['uid_1']['id'] = 'uid_1';
  $handler->display->display_options['filters']['uid_1']['table'] = 'users';
  $handler->display->display_options['filters']['uid_1']['field'] = 'uid';
  $handler->display->display_options['filters']['uid_1']['relationship'] = 'payer';
  $handler->display->display_options['filters']['uid_1']['value'] = '';
  $handler->display->display_options['filters']['uid_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['uid_1']['expose']['operator_id'] = 'uid_1_op';
  $handler->display->display_options['filters']['uid_1']['expose']['label'] = 'Payer';
  $handler->display->display_options['filters']['uid_1']['expose']['operator'] = 'uid_1_op';
  $handler->display->display_options['filters']['uid_1']['expose']['identifier'] = 'uid_1';
  $handler->display->display_options['filters']['uid_1']['expose']['multiple'] = FALSE;
  $handler->display->display_options['filters']['uid_1']['expose']['reduce'] = 0;
  /* Filter criterion: Transaction: State */
  $handler->display->display_options['filters']['state']['id'] = 'state';
  $handler->display->display_options['filters']['state']['table'] = 'mcapi_transactions';
  $handler->display->display_options['filters']['state']['field'] = 'state';
  $handler->display->display_options['filters']['state']['value'] = array(
    0 => 1,
  );
  $handler->display->display_options['filters']['state']['exposed'] = TRUE;
  $handler->display->display_options['filters']['state']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['state']['expose']['label'] = 'State';
  $handler->display->display_options['filters']['state']['expose']['operator'] = 'state_op';
  $handler->display->display_options['filters']['state']['expose']['identifier'] = 'state';
  $handler->display->display_options['filters']['state']['expose']['reduce'] = 0;
  /* Filter criterion: Transaction: Worth (worth:quantity) */
  $handler->display->display_options['filters']['worth_quantity']['id'] = 'worth_quantity';
  $handler->display->display_options['filters']['worth_quantity']['table'] = 'field_data_worth';
  $handler->display->display_options['filters']['worth_quantity']['field'] = 'worth_quantity';
  $handler->display->display_options['filters']['worth_quantity']['exposed'] = TRUE;
  $handler->display->display_options['filters']['worth_quantity']['expose']['operator_id'] = 'worth_quantity_op';
  $handler->display->display_options['filters']['worth_quantity']['expose']['label'] = 'Quantity';
  $handler->display->display_options['filters']['worth_quantity']['expose']['use_operator'] = 1;
  $handler->display->display_options['filters']['worth_quantity']['expose']['operator'] = 'worth_quantity_op';
  $handler->display->display_options['filters']['worth_quantity']['expose']['identifier'] = 'worth_quantity';
  $handler->display->display_options['filters']['worth_quantity']['expose']['multiple'] = FALSE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'transactions/manage';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Manage';
  $handler->display->display_options['menu']['description'] = t("This is the default accountant's interface. It is simply a transaction view with all the filters exposed. More accountants tools are needed, depending on how the system is to be used.");
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $translatables['transactions_all'] = array(
    t('Transaction management'),
    t('All transactions can be seen from here. Use the filters to list what you need.'),
    t('Recorded'),
    t('Payer'),
    t('Payee'),
    t('Worth'),
    t('State'),
    t('Quantity'),
  );

  $views[$view->name] = $view;


  $view = new view();
  $view->name = 'trade_analysis';
  $view->description = '';
  $view->tag = 'mcapi (index)';
  $view->base_table = 'mcapi_index';
  $view->human_name = 'Trading analysis';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'plus';
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'serial' => 'serial',
    'uid2' => 'uid2',
    'volume' => 'volume',
  );
  /* Champ: COUNT(DISTINCT Transaction index : Unique serial number) */
  $handler->display->display_options['fields']['serial']['id'] = 'serial';
  $handler->display->display_options['fields']['serial']['table'] = 'mcapi_index';
  $handler->display->display_options['fields']['serial']['field'] = 'serial';
  $handler->display->display_options['fields']['serial']['group_type'] = 'count_distinct';
  $handler->display->display_options['fields']['serial']['label'] = 'Transactions';
  /* Champ: COUNT(DISTINCT Transaction index : 2nd user) */
  $handler->display->display_options['fields']['uid2']['id'] = 'uid2';
  $handler->display->display_options['fields']['uid2']['table'] = 'mcapi_index';
  $handler->display->display_options['fields']['uid2']['field'] = 'uid2';
  $handler->display->display_options['fields']['uid2']['group_type'] = 'count_distinct';
  $handler->display->display_options['fields']['uid2']['label'] = 'Active traders';
  /* Champ: SUM(Transaction index : Volume d'échange ) */
  $handler->display->display_options['fields']['volume']['id'] = 'volume';
  $handler->display->display_options['fields']['volume']['table'] = 'mcapi_index';
  $handler->display->display_options['fields']['volume']['field'] = 'volume';
  $handler->display->display_options['fields']['volume']['group_type'] = 'sum';
  /* Champ: Transaction index : Greco index */
  $handler->display->display_options['fields']['greco']['id'] = 'greco';
  $handler->display->display_options['fields']['greco']['table'] = 'mcapi_index';
  $handler->display->display_options['fields']['greco']['field'] = 'greco';
  $handler->display->display_options['fields']['greco']['label'] = '';
  $handler->display->display_options['fields']['greco']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['greco']['alter']['text'] = 'Greco index [greco]';
  $handler->display->display_options['fields']['greco']['element_label_colon'] = FALSE;
  /* Critère de filtrage: Transaction index : Devise */
  $handler->display->display_options['filters']['currcode']['id'] = 'currcode';
  $handler->display->display_options['filters']['currcode']['table'] = 'mcapi_index';
  $handler->display->display_options['filters']['currcode']['field'] = 'currcode';
  $handler->display->display_options['filters']['currcode']['value'] = array(
    0 => 'credunit',
  );
  /* Critère de filtrage: Transaction index : Change in balance */
  $handler->display->display_options['filters']['diff']['id'] = 'diff';
  $handler->display->display_options['filters']['diff']['table'] = 'mcapi_index';
  $handler->display->display_options['filters']['diff']['field'] = 'diff';
  $handler->display->display_options['filters']['diff']['operator'] = '>';
  $handler->display->display_options['filters']['diff']['value']['value'] = '0';

  /* Filter criterion: Date: Date (mcapi_index) */
  $handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['table'] = 'mcapi_index';
  $handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['operator'] = '>';
  $handler->display->display_options['filters']['date_filter']['default_date'] = '-365 days';
  $handler->display->display_options['filters']['date_filter']['year_range'] = '-3:+0';
  $handler->display->display_options['filters']['date_filter']['date_fields'] = array(
    'mcapi_index.created' => 'mcapi_index.created',
  );

  /* Display: System trading stats */
  $handler = $view->new_display('block', 'System trading stats', 'system');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'curr';
  $handler->display->display_options['access']['mode'] = 'system_data';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Champ: COUNT(DISTINCT Transaction index : 2nd user) */
  $handler->display->display_options['fields']['uid2']['id'] = 'uid2';
  $handler->display->display_options['fields']['uid2']['table'] = 'mcapi_index';
  $handler->display->display_options['fields']['uid2']['field'] = 'uid2';
  $handler->display->display_options['fields']['uid2']['group_type'] = 'count_distinct';
  $handler->display->display_options['fields']['uid2']['exclude'] = TRUE;
  $handler->display->display_options['fields']['uid2']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['uid2']['prefix'] = ' ';
  /* Champ: COUNT(DISTINCT Transaction index : Unique serial number) */
  $handler->display->display_options['fields']['serial']['id'] = 'serial';
  $handler->display->display_options['fields']['serial']['table'] = 'mcapi_index';
  $handler->display->display_options['fields']['serial']['field'] = 'serial';
  $handler->display->display_options['fields']['serial']['group_type'] = 'count_distinct';
  $handler->display->display_options['fields']['serial']['exclude'] = TRUE;
  $handler->display->display_options['fields']['serial']['element_label_colon'] = FALSE;
  /* Field: SUM(Transaction index: Volume) */
  $handler->display->display_options['fields']['volume']['id'] = 'volume';
  $handler->display->display_options['fields']['volume']['table'] = 'mcapi_index';
  $handler->display->display_options['fields']['volume']['field'] = 'volume';
  $handler->display->display_options['fields']['volume']['group_type'] = 'sum';
  $handler->display->display_options['fields']['volume']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['volume']['alter']['text'] = 'In the last year, our [uid2] active users have done [serial] transactions, totalling [volume]';
  $handler->display->display_options['fields']['volume']['element_label_colon'] = FALSE;
  /* Field: Transaction index: Greco index */
  $handler->display->display_options['fields']['greco']['id'] = 'greco';
  $handler->display->display_options['fields']['greco']['table'] = 'mcapi_index';
  $handler->display->display_options['fields']['greco']['field'] = 'greco';
  $handler->display->display_options['fields']['greco']['label'] = "Thomas Greco's system health index";
  $handler->display->display_options['fields']['greco']['alter']['text'] = ' : [greco]';
  $handler->display->display_options['fields']['greco']['element_label_colon'] = FALSE;
  $handler->display->display_options['block_description'] = 'Trading summary';

  /* Display: User trading stats */
  $handler = $view->new_display('block', 'User trading stats', 'user');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'curr';
  $handler->display->display_options['access']['mode'] = 'trader_data';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relation: Transaction index : 1st user */
  $handler->display->display_options['relationships']['uid1']['id'] = 'uid1';
  $handler->display->display_options['relationships']['uid1']['table'] = 'mcapi_index';
  $handler->display->display_options['relationships']['uid1']['field'] = 'uid1';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Champ: COUNT(DISTINCT Transaction index : Unique serial number) */
  $handler->display->display_options['fields']['serial']['id'] = 'serial';
  $handler->display->display_options['fields']['serial']['table'] = 'mcapi_index';
  $handler->display->display_options['fields']['serial']['field'] = 'serial';
  $handler->display->display_options['fields']['serial']['group_type'] = 'count_distinct';
  $handler->display->display_options['fields']['serial']['label'] = 'Trades';
  /* Champ: COUNT(DISTINCT Transaction index : 2nd user) */
  $handler->display->display_options['fields']['uid2']['id'] = 'uid2';
  $handler->display->display_options['fields']['uid2']['table'] = 'mcapi_index';
  $handler->display->display_options['fields']['uid2']['field'] = 'uid2';
  $handler->display->display_options['fields']['uid2']['group_type'] = 'count_distinct';
  $handler->display->display_options['fields']['uid2']['label'] = 'Promiscuity';
  /* Champ: SUM(Transaction index : Volume d'échange ) */
  $handler->display->display_options['fields']['volume']['id'] = 'volume';
  $handler->display->display_options['fields']['volume']['table'] = 'mcapi_index';
  $handler->display->display_options['fields']['volume']['field'] = 'volume';
  $handler->display->display_options['fields']['volume']['group_type'] = 'sum';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Filtre contextuel: Transaction index : 1st user */
  $handler->display->display_options['arguments']['uid1']['id'] = 'uid1';
  $handler->display->display_options['arguments']['uid1']['table'] = 'mcapi_index';
  $handler->display->display_options['arguments']['uid1']['field'] = 'uid1';
  $handler->display->display_options['arguments']['uid1']['exception']['title'] = 'Tout';
  $handler->display->display_options['arguments']['uid1']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['uid1']['title'] = '%1 summary';
  $handler->display->display_options['arguments']['uid1']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['uid1']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid1']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid1']['summary_options']['items_per_page'] = '25';
  /* Filtre contextuel: Transaction index : Created moment */
  $handler->display->display_options['arguments']['created']['id'] = 'created';
  $handler->display->display_options['arguments']['created']['table'] = 'mcapi_index';
  $handler->display->display_options['arguments']['created']['field'] = 'created';
  $handler->display->display_options['arguments']['created']['exception']['title'] = 'Tout';
  $handler->display->display_options['arguments']['created']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['created']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['created']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['created']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;

  /* Display: Export CSV */
  $handler = $view->new_display('views_data_export', 'Export CSV', 'views_data_export_1');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['path'] = 'user_trades';
  $translatables['trade_analysis'] = array(
    t('Active traders'),
    t("The [uid2] active users have made [serial] exchanges, totalling [volume]. Thomas Greco's system health index is: [greco]"),
  );
  $views[$view->name] = $view;

  t('In the last year, our [uid2] active users have done [serial] transactions, totalling [volume]');
  t("Thomas Greco's system health index");
}
