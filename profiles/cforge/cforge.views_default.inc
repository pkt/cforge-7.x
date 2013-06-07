<?php


/**
 * Implementation of hook_default_view_views()
 */
function cforge_views_default_views() {
  $view_names = array('member_list', 'news', 'member_dues', 'comments_recent');
  foreach($view_names as $name) {
    $function = 'cforge_views_get_'.$name;
    $views[$name] = $function();
  }
  return $views;
}

function cforge_views_get_member_list() {
  $view = new view;
  $view->name = 'member_list';
  $view->description = 'Member list with alpha pagers,';
  $view->tag = 'cforge';
  $view->base_table = 'users';
  $view->human_name = 'Member list';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
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
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '100';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« first';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ previous';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'next ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'last »';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'uid' => 'uid',
    'picture' => 'picture',
    'profile_address' => 'profile_address',
    'profile_address_1' => 'profile_address_1',
    'profile_phones' => 'profile_phones',
    'current_balance' => 'current_balance',
    'current_balance_1' => 'current_balance_1',
    'profile_address_2' => 'profile_address_2',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'uid' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'picture' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'profile_address' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'profile_address_1' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'profile_phones' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'current_balance' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'current_balance_1' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'profile_address_locality' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  /* Champ: Utilisateur : Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['label'] = 'N°';
  /* Champ: Utilisateur : Image */
  $handler->display->display_options['fields']['picture']['id'] = 'picture';
  $handler->display->display_options['fields']['picture']['table'] = 'users';
  $handler->display->display_options['fields']['picture']['field'] = 'picture';
  $handler->display->display_options['fields']['picture']['label'] = '';
  $handler->display->display_options['fields']['picture']['image_style'] = 'thumbnail';
  /* Field: User: Name & Address */
  $handler->display->display_options['fields']['profile_address']['id'] = 'profile_address';
  $handler->display->display_options['fields']['profile_address']['table'] = 'field_data_profile_address';
  $handler->display->display_options['fields']['profile_address']['field'] = 'profile_address';
  $handler->display->display_options['fields']['profile_address']['label'] = 'First name';
  $handler->display->display_options['fields']['profile_address']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['profile_address']['alter']['text'] = '[profile_address-first_name]';
  $handler->display->display_options['fields']['profile_address']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['profile_address']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(
      'address' => 'address',
    ),
  );
  /* Field: User: Name & Address */
  $handler->display->display_options['fields']['profile_address_1']['id'] = 'profile_address_1';
  $handler->display->display_options['fields']['profile_address_1']['table'] = 'field_data_profile_address';
  $handler->display->display_options['fields']['profile_address_1']['field'] = 'profile_address';
  $handler->display->display_options['fields']['profile_address_1']['label'] = 'Family name';
  $handler->display->display_options['fields']['profile_address_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['profile_address_1']['alter']['text'] = '[profile_address_1-last_name]';
  $handler->display->display_options['fields']['profile_address_1']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['profile_address_1']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(
      'address' => 'address',
    ),
  );
  /* Field: User: Phone Numbers */
  $handler->display->display_options['fields']['profile_phones']['id'] = 'profile_phones';
  $handler->display->display_options['fields']['profile_phones']['table'] = 'field_data_profile_phones';
  $handler->display->display_options['fields']['profile_phones']['field'] = 'profile_phones';
  if (module_exists('cforge_currencies')) {
    /* Champ: Utilisateur : Transaction statistic */
    $handler->display->display_options['fields']['current_balance']['id'] = 'current_balance';
    $handler->display->display_options['fields']['current_balance']['table'] = 'users';
    $handler->display->display_options['fields']['current_balance']['field'] = 'current_balance';
    $handler->display->display_options['fields']['current_balance']['label'] = t('Balance');
    $handler->display->display_options['fields']['current_balance']['currcode'] = array('credunit' => 'credunit');
    /* Champ: Utilisateur : Transaction statistic */
    $handler->display->display_options['fields']['current_balance_1']['id'] = 'current_balance_1';
    $handler->display->display_options['fields']['current_balance_1']['table'] = 'users';
    $handler->display->display_options['fields']['current_balance_1']['field'] = 'current_balance';
    $handler->display->display_options['fields']['current_balance_1']['label'] = 'Gross Income';
    $handler->display->display_options['fields']['current_balance_1']['total'] = 'gross_in';
    $handler->display->display_options['fields']['current_balance_1']['currcode'] = array('credunit' => 'credunit');
  }
  /* Field: User: Locality */
  $handler->display->display_options['fields']['profile_address_locality']['id'] = 'profile_address_dependent_locality';
  $handler->display->display_options['fields']['profile_address_locality']['table'] = 'field_data_profile_address';
  $handler->display->display_options['fields']['profile_address_locality']['field'] = 'profile_address_dependent_locality';
  /* Critère de tri: Utilisateur : Uid */
  $handler->display->display_options['sorts']['uid']['id'] = 'uid';
  $handler->display->display_options['sorts']['uid']['table'] = 'users';
  $handler->display->display_options['sorts']['uid']['field'] = 'uid';
  $handler->display->display_options['sorts']['uid']['order'] = 'DESC';
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = '0';
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: User: Roles */
  $handler->display->display_options['filters']['rid']['id'] = 'rid';
  $handler->display->display_options['filters']['rid']['table'] = 'users_roles';
  $handler->display->display_options['filters']['rid']['field'] = 'rid';
  $handler->display->display_options['filters']['rid']['operator'] = 'not';
  $handler->display->display_options['filters']['rid']['value'] = array(7 => '7');
  $handler->display->display_options['filters']['rid']['group'] = '0';
  $handler->display->display_options['filters']['rid']['expose']['operator'] = FALSE;
  $handler->display->display_options['filters']['rid']['reduce_duplicates'] = 0;
  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Members';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['path'] = 'members/all';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = t('Members');
  $handler->display->display_options['menu']['weight'] = '4';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = t('Members');
  $handler->display->display_options['tab_options']['weight'] = '0';
  /* Sort criterion: User: Uid */
  $handler->display->display_options['sorts']['uid']['id'] = 'uid';
  $handler->display->display_options['sorts']['uid']['table'] = 'users';
  $handler->display->display_options['sorts']['uid']['field'] = 'uid';
  $handler->display->display_options['sorts']['uid']['order'] = 'DESC';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: User: Name &amp; Address (profile_address:first_name) */
  $handler->display->display_options['arguments']['profile_address_first_name']['id'] = 'profile_address_first_name';
  $handler->display->display_options['arguments']['profile_address_first_name']['table'] = 'field_data_profile_address';
  $handler->display->display_options['arguments']['profile_address_first_name']['field'] = 'profile_address_first_name';
  $handler->display->display_options['arguments']['profile_address_first_name']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['profile_address_first_name']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['profile_address_first_name']['summary']['format'] = 'unformatted_summary';
  $handler->display->display_options['arguments']['profile_address_first_name']['summary_options']['count'] = FALSE;
  $handler->display->display_options['arguments']['profile_address_first_name']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['profile_address_first_name']['summary_options']['inline'] = TRUE;
  $handler->display->display_options['arguments']['profile_address_first_name']['summary_options']['separator'] = ' ';
  $handler->display->display_options['arguments']['profile_address_first_name']['glossary'] = TRUE;
  $handler->display->display_options['arguments']['profile_address_first_name']['limit'] = '1';
  $handler->display->display_options['arguments']['profile_address_first_name']['case'] = 'lower';
  $handler->display->display_options['arguments']['profile_address_first_name']['path_case'] = 'lower';
  /* Contextual filter: User: Name &amp; Address (profile_address:last_name) */
  $handler->display->display_options['arguments']['profile_address_last_name']['id'] = 'profile_address_last_name';
  $handler->display->display_options['arguments']['profile_address_last_name']['table'] = 'field_data_profile_address';
  $handler->display->display_options['arguments']['profile_address_last_name']['field'] = 'profile_address_last_name';
  $handler->display->display_options['arguments']['profile_address_last_name']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['profile_address_last_name']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['profile_address_last_name']['summary']['format'] = 'unformatted_summary';
  $handler->display->display_options['arguments']['profile_address_last_name']['summary_options']['count'] = FALSE;
  $handler->display->display_options['arguments']['profile_address_last_name']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['profile_address_last_name']['summary_options']['inline'] = TRUE;
  $handler->display->display_options['arguments']['profile_address_last_name']['glossary'] = TRUE;
  $handler->display->display_options['arguments']['profile_address_last_name']['limit'] = '1';
  $handler->display->display_options['arguments']['profile_address_last_name']['case'] = 'upper';
  $handler->display->display_options['arguments']['profile_address_last_name']['path_case'] = 'upper';
  $handler->display->display_options['arguments']['profile_address_last_name']['break_phrase'] = TRUE;

  /* Display: alphapager firstname */
  $handler = $view->new_display('attachment', 'alphapager firstname', 'attachment_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'First name';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['text']['id'] = 'area';
  $handler->display->display_options['header']['text']['table'] = 'views';
  $handler->display->display_options['header']['text']['field'] = 'area';
  $handler->display->display_options['header']['text']['empty'] = FALSE;
  $handler->display->display_options['header']['text']['content'] = 'First name:';
  $handler->display->display_options['header']['text']['format'] = '1';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: User: Name &amp; Address (profile_address:first_name) */
  $handler->display->display_options['arguments']['profile_address_first_name']['id'] = 'profile_address_first_name';
  $handler->display->display_options['arguments']['profile_address_first_name']['table'] = 'field_data_profile_address';
  $handler->display->display_options['arguments']['profile_address_first_name']['field'] = 'profile_address_first_name';
  $handler->display->display_options['arguments']['profile_address_first_name']['default_action'] = 'summary';
  $handler->display->display_options['arguments']['profile_address_first_name']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['profile_address_first_name']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['profile_address_first_name']['summary']['format'] = 'unformatted_summary';
  $handler->display->display_options['arguments']['profile_address_first_name']['summary_options']['count'] = FALSE;
  $handler->display->display_options['arguments']['profile_address_first_name']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['profile_address_first_name']['summary_options']['inline'] = TRUE;
  $handler->display->display_options['arguments']['profile_address_first_name']['summary_options']['separator'] = ' ';
  $handler->display->display_options['arguments']['profile_address_first_name']['glossary'] = TRUE;
  $handler->display->display_options['arguments']['profile_address_first_name']['limit'] = '1';
  $handler->display->display_options['arguments']['profile_address_first_name']['case'] = 'lower';
  $handler->display->display_options['arguments']['profile_address_first_name']['path_case'] = 'lower';
  $handler->display->display_options['arguments']['profile_address_first_name']['break_phrase'] = TRUE;
  $handler->display->display_options['displays'] = array(
    'page_1' => 'page_1',
    'default' => 0,
    'page_2' => 0,
  );
  $handler->display->display_options['inherit_arguments'] = 0;
  $handler->display->display_options['render_pager'] = TRUE;

  /* Display: alphapager familyname */
  $handler = $view->new_display('attachment', 'alphapager familyname', 'attachment_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Family name:';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['text']['id'] = 'area';
  $handler->display->display_options['header']['text']['table'] = 'views';
  $handler->display->display_options['header']['text']['field'] = 'area';
  $handler->display->display_options['header']['text']['empty'] = FALSE;
  $handler->display->display_options['header']['text']['content'] = 'Family name:';
  $handler->display->display_options['header']['text']['format'] = '1';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: User: Name &amp; Address (profile_address:last_name) */
  $handler->display->display_options['arguments']['profile_address_last_name']['id'] = 'profile_address_last_name';
  $handler->display->display_options['arguments']['profile_address_last_name']['table'] = 'field_data_profile_address';
  $handler->display->display_options['arguments']['profile_address_last_name']['field'] = 'profile_address_last_name';
  $handler->display->display_options['arguments']['profile_address_last_name']['default_action'] = 'summary';
  $handler->display->display_options['arguments']['profile_address_last_name']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['profile_address_last_name']['default_argument_skip_url'] = TRUE;
  $handler->display->display_options['arguments']['profile_address_last_name']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['profile_address_last_name']['summary']['format'] = 'unformatted_summary';
  $handler->display->display_options['arguments']['profile_address_last_name']['summary_options']['base_path'] = 'members/all/all';
  $handler->display->display_options['arguments']['profile_address_last_name']['summary_options']['count'] = FALSE;
  $handler->display->display_options['arguments']['profile_address_last_name']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['profile_address_last_name']['summary_options']['inline'] = TRUE;
  $handler->display->display_options['arguments']['profile_address_last_name']['summary_options']['separator'] = ' ';
  $handler->display->display_options['arguments']['profile_address_last_name']['glossary'] = TRUE;
  $handler->display->display_options['arguments']['profile_address_last_name']['limit'] = '1';
  $handler->display->display_options['arguments']['profile_address_last_name']['case'] = 'upper';
  $handler->display->display_options['arguments']['profile_address_last_name']['path_case'] = 'upper';
  $handler->display->display_options['arguments']['profile_address_last_name']['break_phrase'] = TRUE;
  $handler->display->display_options['displays'] = array(
    'page_1' => 'page_1',
  );
  $handler->display->display_options['inherit_arguments'] = 0;

  /* Display: System */
  $handler = $view->new_display('page', 'System', 'page_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Non-member accounts';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = '0';
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: User: Roles */
  $handler->display->display_options['filters']['rid']['id'] = 'rid';
  $handler->display->display_options['filters']['rid']['table'] = 'users_roles';
  $handler->display->display_options['filters']['rid']['field'] = 'rid';
  $handler->display->display_options['filters']['rid']['value'] = array(RID_SYSTEM => RID_SYSTEM);
  $handler->display->display_options['filters']['rid']['group'] = '0';
  $handler->display->display_options['filters']['rid']['expose']['operator'] = FALSE;
  $handler->display->display_options['filters']['rid']['reduce_duplicates'] = 0;
  $handler->display->display_options['path'] = 'members/system';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'System accounts';
  $handler->display->display_options['menu']['weight'] = '0';


  /* Display: CSV export */
  $handler = $view->new_display('views_data_export', 'CSV export', 'views_data_export_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'All active users';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(RID_COMMITTEE => RID_COMMITTEE);
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: User : Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['label'] = 'N°';
  /* Field: User : Name & Address */
  $handler->display->display_options['fields']['profile_address']['id'] = 'profile_address';
  $handler->display->display_options['fields']['profile_address']['table'] = 'field_data_profile_address';
  $handler->display->display_options['fields']['profile_address']['field'] = 'profile_address';
  $handler->display->display_options['fields']['profile_address']['label'] = 'First name';
  $handler->display->display_options['fields']['profile_address']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['profile_address']['alter']['text'] = '[profile_address-first_name]';
  $handler->display->display_options['fields']['profile_address']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(
      'address' => 'address',
    ),
  );
  /* Field: User : : Name & Address */
  $handler->display->display_options['fields']['profile_address_1']['id'] = 'profile_address_1';
  $handler->display->display_options['fields']['profile_address_1']['table'] = 'field_data_profile_address';
  $handler->display->display_options['fields']['profile_address_1']['field'] = 'profile_address';
  $handler->display->display_options['fields']['profile_address_1']['label'] = 'Family name';
  $handler->display->display_options['fields']['profile_address_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['profile_address_1']['alter']['text'] = '[profile_address_1-last_name]';
  $handler->display->display_options['fields']['profile_address_1']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(
      'address' => 'address',
    ),
  );
  /* Field: User : Transaction statistic */
  $handler->display->display_options['fields']['current_balance']['id'] = 'current_balance';
  $handler->display->display_options['fields']['current_balance']['table'] = 'users';
  $handler->display->display_options['fields']['current_balance']['field'] = 'current_balance';
  $handler->display->display_options['fields']['current_balance']['label'] = 'Balance';
  /* Field: User : Transaction statistic */
  $handler->display->display_options['fields']['current_balance_1']['id'] = 'current_balance_1';
  $handler->display->display_options['fields']['current_balance_1']['table'] = 'users';
  $handler->display->display_options['fields']['current_balance_1']['field'] = 'current_balance';
  $handler->display->display_options['fields']['current_balance_1']['label'] = 'Gross income';
  $handler->display->display_options['fields']['current_balance_1']['total'] = 'gross_in';
  /* Field: User : Email */
  $handler->display->display_options['fields']['mail']['id'] = 'mail';
  $handler->display->display_options['fields']['mail']['table'] = 'users';
  $handler->display->display_options['fields']['mail']['field'] = 'mail';
  $handler->display->display_options['fields']['mail']['link_to_user'] = '0';
  /* Field: User : Name & Address */
  $handler->display->display_options['fields']['profile_address_2']['id'] = 'profile_address_2';
  $handler->display->display_options['fields']['profile_address_2']['table'] = 'field_data_profile_address';
  $handler->display->display_options['fields']['profile_address_2']['field'] = 'profile_address';
  $handler->display->display_options['fields']['profile_address_2']['label'] = 'Street address';
  $handler->display->display_options['fields']['profile_address_2']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['profile_address_2']['alter']['text'] = '[profile_address_2-thoroughfare]';
  $handler->display->display_options['fields']['profile_address_2']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(
      'address' => 'address',
    ),
  );
  /* Field: User : Name & Address */
  $handler->display->display_options['fields']['profile_address_3']['id'] = 'profile_address_3';
  $handler->display->display_options['fields']['profile_address_3']['table'] = 'field_data_profile_address';
  $handler->display->display_options['fields']['profile_address_3']['field'] = 'profile_address';
  $handler->display->display_options['fields']['profile_address_3']['label'] = 'Neighbourhood';
  $handler->display->display_options['fields']['profile_address_3']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['profile_address_3']['alter']['text'] = '[profile_address_3-dependent_locality]';
  $handler->display->display_options['fields']['profile_address_3']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(
      'address' => 'address',
    ),
  );
  /* Field: User : Name & Address */
  $handler->display->display_options['fields']['profile_address_4']['id'] = 'profile_address_4';
  $handler->display->display_options['fields']['profile_address_4']['table'] = 'field_data_profile_address';
  $handler->display->display_options['fields']['profile_address_4']['field'] = 'profile_address';
  $handler->display->display_options['fields']['profile_address_4']['label'] = 'Postal code';
  $handler->display->display_options['fields']['profile_address_4']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['profile_address_4']['alter']['text'] = '[profile_address_4-postal_code]';
  $handler->display->display_options['fields']['profile_address_4']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(
      'address' => 'address',
    ),
  );
  /* Field: User : Responsibility */
  $handler->display->display_options['fields']['manage_responsibility']['id'] = 'manage_responsibility';
  $handler->display->display_options['fields']['manage_responsibility']['table'] = 'field_data_manage_responsibility';
  $handler->display->display_options['fields']['manage_responsibility']['field'] = 'manage_responsibility';
  /* Field: User : Phone Numbers */
  $handler->display->display_options['fields']['profile_phones']['id'] = 'profile_phones';
  $handler->display->display_options['fields']['profile_phones']['table'] = 'field_data_profile_phones';
  $handler->display->display_options['fields']['profile_phones']['field'] = 'profile_phones';
  $handler->display->display_options['fields']['profile_phones']['label'] = 'Phone';
  $handler->display->display_options['fields']['profile_phones']['delta_offset'] = '0';
  /* Field: User : Creation date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'users';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Created';
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'd/m/y';
  /* Field: User : Management notes */
  $handler->display->display_options['fields']['manage_notes']['id'] = 'manage_notes';
  $handler->display->display_options['fields']['manage_notes']['table'] = 'field_data_manage_notes';
  $handler->display->display_options['fields']['manage_notes']['field'] = 'manage_notes';

  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter: User : Actif */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = '0';
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  $handler->display->display_options['path'] = 'members.csv';
  $handler->display->display_options['displays'] = array(
    'page_1' => 'page_1',
    'page_2' => 'page_2',
    'default' => 0,
  );

  return $view;

  $translatables['member_list'] = array(
    t('N°'),
    t('Name'),
    t('Balance'),
    t('Gross Income'),
    t('Members'),
    t('First name'),
    t('Family name'),
    t('Street address'),
    t('Neighbourhood'),
    t('Postal code'),
    t('Non-member accounts'),
    t('All active users'),
    t('System accounts')
  );
}


function cforge_views_get_news() {
  $view = new view;
  $view->name = 'recent_news';
  $view->description = t('Latest stories in full, with list of stories');
  $view->tag = 'cforge';
  $view->base_table = 'node';
  $view->human_name = '';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['title'] = 'News';
  $handler->display->display_options['use_more'] = TRUE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['row_options']['view_mode'] = 'full';
  $handler->display->display_options['row_options']['links'] = 1;
  $handler->display->display_options['row_options']['comments'] = 0;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: Content: Updated date */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  $handler->display->display_options['sorts']['created']['granularity'] = 'minute';
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'story' => 'story',
  );
  $handler->display->display_options['filters']['type']['group'] = '0';
  $handler->display->display_options['filters']['type']['expose']['operator'] = FALSE;
  /* Filter criterion: Contenu : Publié */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['row_options']['links'] = TRUE;
  $handler->display->display_options['row_options']['comments'] = 0;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['filters']['type']['group'] = '0';
  $handler->display->display_options['filters']['type']['expose']['operator'] = FALSE;
  $handler->display->display_options['path'] = 'news';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'News';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Feed */
  $handler = $view->new_display('feed', 'Feed', 'feed_1');
  $handler->display->display_options['defaults']['hide_admin_links'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'rss';
  $handler->display->display_options['row_plugin'] = 'node_rss';
  $handler->display->display_options['path'] = 'news/feed.xml';
  $handler->display->display_options['displays'] = array(
    'page_1' => 'page_1',
    'default' => 0,
  );
  $translatables['recent_news'] = array(
    t('Updated date'),
    t('Previous articles'),
    t('News')
  );

  return $view;
}

function cforge_views_get_member_dues() {
  $view = new view;
  $view = new view;
  $view->name = 'member_dues';
  $view->description = 'expiry dates';
  $view->tag = 'cforge';
  $view->base_table = 'users';
  $view->human_name = '';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Paramètres par défaut */
  $handler = $view->new_display('default', 'Paramètres par défaut', 'default');
  $handler->display->display_options['title'] = 'Member list';
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(RID_COMMITTEE => RID_COMMITTEE);
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['grouping'] = '';
  $handler->display->display_options['style_options']['columns'] = array(
    'expiry_timestamp' => 'expiry_timestamp',
    'name' => 'name',
    'value_4' => 'value_4',
    'login' => 'login',
    'cleared_balance' => 'cleared_balance',
  );
  $handler->display->display_options['style_options']['default'] = 'expiry_timestamp';
  $handler->display->display_options['style_options']['info'] = array(
    'expiry_timestamp' => array(
      'sortable' => 1,
      'separator' => '',
    ),
    'name' => array(
      'sortable' => 1,
      'separator' => ' ',
    ),
    'value_4' => array(
      'sortable' => 0,
      'separator' => '',
    ),
    'login' => array(
      'sortable' => 1,
      'separator' => '',
    ),
    'cleared_balance' => array(
      'sortable' => 1,
      'separator' => '',
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  /* Field: User: Role expiration date/time */
  $handler->display->display_options['fields']['expiry_timestamp']['id'] = 'expiry_timestamp';
  $handler->display->display_options['fields']['expiry_timestamp']['table'] = 'role_expire';
  $handler->display->display_options['fields']['expiry_timestamp']['field'] = 'expiry_timestamp';
  $handler->display->display_options['fields']['expiry_timestamp']['label'] = 'Renewal date';
  $handler->display->display_options['fields']['expiry_timestamp']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['expiry_timestamp']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['expiry_timestamp']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['expiry_timestamp']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['expiry_timestamp']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['expiry_timestamp']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['expiry_timestamp']['alter']['html'] = 0;
  $handler->display->display_options['fields']['expiry_timestamp']['hide_empty'] = 0;
  $handler->display->display_options['fields']['expiry_timestamp']['empty_zero'] = 0;
  $handler->display->display_options['fields']['expiry_timestamp']['date_format'] = 'medium';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['name']['link_to_user'] = 1;
  $handler->display->display_options['fields']['name']['overwrite_anonymous'] = 0;
  /* Field: User: Last login */
  $handler->display->display_options['fields']['login']['id'] = 'login';
  $handler->display->display_options['fields']['login']['table'] = 'users';
  $handler->display->display_options['fields']['login']['field'] = 'login';
  $handler->display->display_options['fields']['login']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['login']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['login']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['login']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['login']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['login']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['login']['alter']['html'] = 0;
  /* Filter criterion: User: Roles */
  $handler->display->display_options['filters']['rid']['id'] = 'rid';
  $handler->display->display_options['filters']['rid']['table'] = 'users_roles';
  $handler->display->display_options['filters']['rid']['field'] = 'rid';
  $handler->display->display_options['filters']['rid']['operator'] = 'not';
  $handler->display->display_options['filters']['rid']['value'] = array(RID_SYSTEM => RID_SYSTEM);
  $handler->display->display_options['filters']['rid']['group'] = '0';
  $handler->display->display_options['filters']['rid']['expose']['operator'] = FALSE;
  $handler->display->display_options['filters']['rid']['reduce_duplicates'] = 0;
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = '0';
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: User: Role expiration date/time */
  $handler->display->display_options['filters']['expiry_timestamp']['id'] = 'expiry_timestamp';
  $handler->display->display_options['filters']['expiry_timestamp']['table'] = 'role_expire';
  $handler->display->display_options['filters']['expiry_timestamp']['field'] = 'expiry_timestamp';
  $handler->display->display_options['filters']['expiry_timestamp']['operator'] = '>';
  $handler->display->display_options['filters']['expiry_timestamp']['value']['value'] = 'now';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['path'] = 'members/expiry';

  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Expiry';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'manage';

  $translatables['member_dues'] = array(
    t('Renewal date'),
    t('Name'),
    t('Last login'),
  );

  return $view;
}

function cforge_views_get_comments_recent() {
  $view = new view();
  $view->name = 'comments_recent';
  $view->description = t('Contains a block and a page to list recent comments; the block will automatically link to the page, which displays the comment body as well as a link to the node.');
  $view->tag = 'default';
  $view->base_table = 'comment';
  $view->human_name = 'Recent comments';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Recent comments';
  $handler->display->display_options['use_more'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'plus';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = 5;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'name' => 'name',
    'subject' => 'subject',
  );
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  /* Relation: Commentaire : Contenu */
  $handler->display->display_options['relationships']['nid']['id'] = 'nid';
  $handler->display->display_options['relationships']['nid']['table'] = 'comment';
  $handler->display->display_options['relationships']['nid']['field'] = 'nid';
  /* Champ: Contenu : Chemin */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['relationship'] = 'nid';
  $handler->display->display_options['fields']['path']['label'] = '';
  $handler->display->display_options['fields']['path']['exclude'] = TRUE;
  /* Champ: Commentaire : Auteur */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'comment';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['exclude'] = TRUE;
  /* Champ: Commentaire : Titre */
  $handler->display->display_options['fields']['subject']['id'] = 'subject';
  $handler->display->display_options['fields']['subject']['table'] = 'comment';
  $handler->display->display_options['fields']['subject']['field'] = 'subject';
  $handler->display->display_options['fields']['subject']['label'] = '';
  $handler->display->display_options['fields']['subject']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['subject']['alter']['text'] = t('[name] said "!whatever_link"', array('@name' => '[name]', '!whatever' => '<a href="[path]">[subject]</a>'));

  $handler->display->display_options['fields']['subject']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['subject']['link_to_comment'] = FALSE;
  /* Critère de tri: Commentaire : Date de mise à jour */
  $handler->display->display_options['sorts']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['table'] = 'comment';
  $handler->display->display_options['sorts']['timestamp']['field'] = 'changed';
  $handler->display->display_options['sorts']['timestamp']['order'] = 'DESC';
  /* Critère de filtrage: Contenu : Publié ou admin */
  $handler->display->display_options['filters']['status_extra']['id'] = 'status_extra';
  $handler->display->display_options['filters']['status_extra']['table'] = 'node';
  $handler->display->display_options['filters']['status_extra']['field'] = 'status_extra';
  $handler->display->display_options['filters']['status_extra']['relationship'] = 'nid';
  $handler->display->display_options['filters']['status_extra']['group'] = 0;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['use_more'] = FALSE;
  $handler->display->display_options['defaults']['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['defaults']['use_more_text'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'plus';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'title' => 'title',
    'timestamp' => 'timestamp',
  );
  $handler->display->display_options['row_options']['separator'] = '&nbsp;';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Champ: Contenu : Titre */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'nid';
  $handler->display->display_options['fields']['title']['label'] = 'Reply to';
  /* Champ: Commentaire : Date de mise à jour */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'comment';
  $handler->display->display_options['fields']['timestamp']['field'] = 'changed';
  $handler->display->display_options['fields']['timestamp']['label'] = '';
  $handler->display->display_options['fields']['timestamp']['date_format'] = 'time ago';
  /* Champ: Commentaire : Titre */
  $handler->display->display_options['fields']['subject']['id'] = 'subject';
  $handler->display->display_options['fields']['subject']['table'] = 'comment';
  $handler->display->display_options['fields']['subject']['field'] = 'subject';
  $handler->display->display_options['fields']['subject']['label'] = '';
  /* Champ: Commentaire : Commentaire */
  $handler->display->display_options['fields']['comment']['id'] = 'comment';
  $handler->display->display_options['fields']['comment']['table'] = 'field_data_comment_body';
  $handler->display->display_options['fields']['comment']['field'] = 'comment_body';
  $handler->display->display_options['fields']['comment']['label'] = '';
  $handler->display->display_options['path'] = 'comments/recent';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;

  return $view;

  $translatables['comments_recent'] = array(
    t('Recent comments'),
    t('[name] said "<a href="[path]">[subject]</a>"'),
    t('Reply to'),
  );
}
