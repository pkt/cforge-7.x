<?php

/*
 * implements hook_views_default_views
 */
function cforge_offline_views_default_views() {
  $view = new view();
  $view->name = 'postal_members';
  $view->description = 'addresses to csv';
  $view->tag = 'cforge';
  $view->base_table = 'users';
  $view->human_name = 'Offline members';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Paramètres par défaut */
  $handler = $view->new_display('default', 'Default', 'default');
  $handler->display->display_options['title'] = 'Offline members';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'plus';
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    4 => 4,
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Appliquer';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Réinitialiser';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Trier par';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'grid';
  $handler->display->display_options['style_options']['grouping'] = '';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'profile_phones' => 'profile_phones',
  );
  /* Champ: Utilisateur : Nom */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  /* Champ: Utilisateur : Numéros de téléphone */
  $handler->display->display_options['fields']['profile_phones']['id'] = 'profile_phones';
  $handler->display->display_options['fields']['profile_phones']['table'] = 'field_data_profile_phones';
  $handler->display->display_options['fields']['profile_phones']['field'] = 'profile_phones';
  $handler->display->display_options['fields']['profile_phones']['label'] = 'Téléphone';
  $handler->display->display_options['fields']['profile_phones']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['profile_phones']['delta_offset'] = '0';
  /* Champ: Utilisateur : Name & Address */
  $handler->display->display_options['fields']['profile_address']['id'] = 'profile_address';
  $handler->display->display_options['fields']['profile_address']['table'] = 'field_data_profile_address';
  $handler->display->display_options['fields']['profile_address']['field'] = 'profile_address';
  $handler->display->display_options['fields']['profile_address']['label'] = '';
  $handler->display->display_options['fields']['profile_address']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['profile_address']['alter']['text'] = '[profile_address-thoroughfare],<br />
  [profile_address-dependent_locality],<br />
  [profile_address-postal_code]';
  $handler->display->display_options['fields']['profile_address']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['profile_address']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['profile_address']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(
      'address' => 'address',
    ),
  );
  /* Critère de filtrage: Utilisateur : Membre postal (account_offline) */
  $handler->display->display_options['filters']['account_offline_value']['id'] = 'account_offline_value';
  $handler->display->display_options['filters']['account_offline_value']['table'] = 'field_data_account_offline';
  $handler->display->display_options['filters']['account_offline_value']['field'] = 'account_offline_value';
  $handler->display->display_options['filters']['account_offline_value']['value'] = array(
    1 => '1',
  );
  /* Critère de filtrage: Utilisateur : Actif */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'members/postal';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Offline members';
  $handler->display->display_options['menu']['description'] = "Addresses of members with the 'offline' preference";
  $handler->display->display_options['menu']['weight'] = '10';
  $handler->display->display_options['menu']['name'] = 'manage';

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Champ: Utilisateur : Nom */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_user'] = FALSE;
  /* Champ: Utilisateur : Name & Address */
  $handler->display->display_options['fields']['profile_address']['id'] = 'profile_address';
  $handler->display->display_options['fields']['profile_address']['table'] = 'field_data_profile_address';
  $handler->display->display_options['fields']['profile_address']['field'] = 'profile_address';
  $handler->display->display_options['fields']['profile_address']['label'] = 'Street';
  $handler->display->display_options['fields']['profile_address']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['profile_address']['alter']['text'] = '[profile_address-thoroughfare]';
  $handler->display->display_options['fields']['profile_address']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['profile_address']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['profile_address']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(
      'address' => 'address',
    ),
  );
  /* Champ: Utilisateur : Name & Address */
  $handler->display->display_options['fields']['profile_address_1']['id'] = 'profile_address_1';
  $handler->display->display_options['fields']['profile_address_1']['table'] = 'field_data_profile_address';
  $handler->display->display_options['fields']['profile_address_1']['field'] = 'profile_address';
  $handler->display->display_options['fields']['profile_address_1']['label'] = 'Neighbourhood';
  $handler->display->display_options['fields']['profile_address_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['profile_address_1']['alter']['text'] = 'profile_address_1-dependent_locality';
  $handler->display->display_options['fields']['profile_address_1']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['profile_address_1']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(
      'address' => 'address',
    ),
  );
  /* Champ: Utilisateur : Name & Address */
  $handler->display->display_options['fields']['profile_address_2']['id'] = 'profile_address_2';
  $handler->display->display_options['fields']['profile_address_2']['table'] = 'field_data_profile_address';
  $handler->display->display_options['fields']['profile_address_2']['field'] = 'profile_address';
  $handler->display->display_options['fields']['profile_address_2']['label'] = 'Post Code';
  $handler->display->display_options['fields']['profile_address_2']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['profile_address_2']['alter']['text'] = '[profile_address_2-postal_code]';
  $handler->display->display_options['fields']['profile_address_2']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['profile_address_2']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(
      'address' => 'address',
    ),
  );
  $handler->display->display_options['path'] = 'members/postal/csv';
  $handler->display->display_options['displays'] = array(
    'page_1' => 'page_1',
    'default' => 0,
  );
  $translatables['postal_members'] = array(
    t('Téléphone'),
    t('Page'),
    t('Street'),
    t('Neighbourhood'),
    t('Post Code'),
    t('Offline members'),
    t("Addresses of members with the 'offline' preference")
  );

  $views[$view->name] = $view;
  return $views;
}

/*
 * implements hook_views_default_views_alter
 */
function cforge_offline_views_default_views_alter(&$views) {
  if (isset($views['ow_offers'])) {
    cf_add_printable_display($views['ow_offers'], FALSE);
  }
  if (isset($views['ow_wants'])) {
    cf_add_printable_display($views['ow_wants'], TRUE);
  }

  /* Display: print-table */
  $handler = $views['member_list']->new_display('print-table', 'print-table', 'print-table_1');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['path'] = 'members/print';
  $handler->display->display_options['displays'] = array(
    'page_1' => 'page_1',
    'default' => 0,
    'page_2' => 0,
    'print-table_1' => 0,
  );
}

//printable display inherits from the default.
function cf_add_printable_display(&$view, $want) {
  /* Display: print-table */
  $handler = $view->new_display('print-table', 'print-table', 'print-table_1');
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'post proposition';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['grouping'] = 'name_1';
  $handler->display->display_options['style_options']['group_rendered'] = 1;
  $handler->display->display_options['style_options']['columns'] = array(
    'name_1' => 'name_1',
    'title' => 'title',
    'name' => 'name',
    'offers_wants_types' => 'offers_wants_types',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'name_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'offers_wants_types' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['required'] = 0;
  /* Relationship: Content: Proposition categories (offers_wants_categories) */
  $handler->display->display_options['relationships']['offers_wants_categories_tid']['id'] = 'offers_wants_categories_tid';
  $handler->display->display_options['relationships']['offers_wants_categories_tid']['table'] = 'field_data_offers_wants_categories';
  $handler->display->display_options['relationships']['offers_wants_categories_tid']['field'] = 'offers_wants_categories_tid';
  $handler->display->display_options['relationships']['offers_wants_categories_tid']['required'] = 1;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name_1']['id'] = 'name_1';
  $handler->display->display_options['fields']['name_1']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name_1']['field'] = 'name';
  $handler->display->display_options['fields']['name_1']['relationship'] = 'offers_wants_categories_tid';
  $handler->display->display_options['fields']['name_1']['label'] = '';
  $handler->display->display_options['fields']['name_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['name_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['name_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['name_1']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['name_1']['link_to_taxonomy'] = 0;
  $handler->display->display_options['fields']['name_1']['convert_spaces'] = 0;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Description';
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = 'Member';
  $handler->display->display_options['fields']['name']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['name']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name']['empty_zero'] = 0;
  $handler->display->display_options['fields']['name']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['name']['link_to_user'] = 1;
  $handler->display->display_options['fields']['name']['overwrite_anonymous'] = 0;
  $handler->display->display_options['fields']['name']['format_username'] = 1;
  /* Field: Content: Proposition types */
  $handler->display->display_options['fields']['offers_wants_types']['id'] = 'offers_wants_types';
  $handler->display->display_options['fields']['offers_wants_types']['table'] = 'field_data_offers_wants_types';
  $handler->display->display_options['fields']['offers_wants_types']['field'] = 'offers_wants_types';
  $handler->display->display_options['fields']['offers_wants_types']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['offers_wants_types']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['offers_wants_types']['hide_empty'] = 0;
  $handler->display->display_options['fields']['offers_wants_types']['empty_zero'] = 0;
  $handler->display->display_options['fields']['offers_wants_types']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['offers_wants_types']['group_rows'] = 1;
  $handler->display->display_options['fields']['offers_wants_types']['delta_offset'] = '0';
  $handler->display->display_options['fields']['offers_wants_types']['delta_reversed'] = 0;
  $handler->display->display_options['fields']['offers_wants_types']['field_api_classes'] = 0;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['path'] = $want ? 'wants/print' : 'offers/print';
  $handler->display->display_options['displays'] = array('all' => 'all');

  /* Display: print-table category */
  $handler = $view->new_display('print-table', 'print-table category', 'print_table_category');
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'post proposition';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['path'] = $want ? 'wants/print/%' : 'offers/print/%';
  //get all the terms in the types vocab and add a display for each.

}