<?php

function cforge_events_views_default_views() {
  $view = new view();
  $view->name = 'events';
  $view->description = '';
  $view->tag = 'events';
  $view->base_table = 'node';
  $view->human_name = 'Events calendar';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Upcoming events';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['link_display'] = 'page_1';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['date_id'] = 'month';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['row_options']['links'] = FALSE;
  /* Champ: Contenu : Date */
  $handler->display->display_options['fields']['event_date']['id'] = 'event_date';
  $handler->display->display_options['fields']['event_date']['table'] = 'field_data_event_date';
  $handler->display->display_options['fields']['event_date']['field'] = 'event_date';
  $handler->display->display_options['fields']['event_date']['label'] = '';
  $handler->display->display_options['fields']['event_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['event_date']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['event_date']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = FALSE;
  /* Sort criterion: Content: Date (event_date) */
  $handler->display->display_options['sorts']['event_date_value']['id'] = 'event_date_value';
  $handler->display->display_options['sorts']['event_date_value']['table'] = 'field_data_event_date';
  $handler->display->display_options['sorts']['event_date_value']['field'] = 'event_date_value';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 0;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Contenu: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'event' => 'event',
  );
  /* Filter criterion: Contenu: Date (event_date) */
  $handler->display->display_options['filters']['event_date_value']['id'] = 'event_date_value';
  $handler->display->display_options['filters']['event_date_value']['table'] = 'field_data_event_date';
  $handler->display->display_options['filters']['event_date_value']['field'] = 'event_date_value';
  $handler->display->display_options['filters']['event_date_value']['operator'] = '>';
  $handler->display->display_options['filters']['event_date_value']['form_type'] = 'date_popup';
  $handler->display->display_options['filters']['event_date_value']['default_date'] = 'yesterday';
  $handler->display->display_options['filters']['event_date_value']['year_range'] = '-0:+1';

  /* Display: Upcoming block */
  $handler = $view->new_display('block', 'Upcoming block', 'block_upcoming');
  $handler->display->display_options['display_description'] = 'Upcoming events block';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['use_more'] = FALSE;
  $handler->display->display_options['use_more'] = TRUE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'event_date' => 'event_date',
    'title' => 'title',
  );
  $handler->display->display_options['row_options']['separator'] = ': ';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['block_description'] = 'Upcoming events';

  /* Display: all events page */
  $handler = $view->new_display('page', 'all events page', 'page_1');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'events-all';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Upcoming events';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'secondary-menu';
  $handler->display->display_options['menu']['context'] = 0;


  $views[$view->name] = $view;
  return $views;

  t('Upcoming events');
}
