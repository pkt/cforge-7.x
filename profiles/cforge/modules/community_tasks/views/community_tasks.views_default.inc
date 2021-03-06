<?php

/**
 * @file
 * Contains default views for the community tasks  module.
 */

/**
 * implements views hook_views_default_views
 */
function community_tasks_views_default_views() {
  $view = new view;
  $view->name = 'community_tasks';
  $view->description = 'Contributions à faire, et accomplies';
  $view->tag = 'cforge';
  $view->base_table = 'node';
  $view->human_name = '';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['title'] = 'Contributions';
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    2 => 2,
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Remise à zéro';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'community_task_state',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['columns'] = array(
    'created' => 'created',
    'title' => 'title',
    'community_task_state' => 'community_task_state',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  $handler->display->display_options['style_options']['info'] = array(
    'created' => array(
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
    'community_task_state' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* No results behavior: Global: Zone de texte */
  $handler->display->display_options['empty']['text']['id'] = 'area';
  $handler->display->display_options['empty']['text']['table'] = 'views';
  $handler->display->display_options['empty']['text']['field'] = 'area';
  $handler->display->display_options['empty']['text']['empty'] = FALSE;
  $handler->display->display_options['empty']['text']['content'] = 'No tasks completed yet';
  $handler->display->display_options['empty']['text']['format'] = '1';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Champ: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Created';
  $handler->display->display_options['fields']['created']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['created']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['created']['hide_empty'] = 0;
  $handler->display->display_options['fields']['created']['empty_zero'] = 0;
  $handler->display->display_options['fields']['created']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['created']['date_format'] = 'long';
  /* Champ: Content: Titre */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: Content: Community Tasks state */
  $handler->display->display_options['fields']['community_task_state']['id'] = 'community_task_state';
  $handler->display->display_options['fields']['community_task_state']['table'] = 'node';
  $handler->display->display_options['fields']['community_task_state']['field'] = 'community_task_state';
  $handler->display->display_options['fields']['community_task_state']['label'] = '';
  $handler->display->display_options['fields']['community_task_state']['exclude'] = TRUE;
  $handler->display->display_options['fields']['community_task_state']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['community_task_state_1']['advanced_render'] = 0;
  /* Field: Content: Community Tasks state */
  $handler->display->display_options['fields']['community_task_state_1']['id'] = 'community_task_state_1';
  $handler->display->display_options['fields']['community_task_state_1']['table'] = 'node';
  $handler->display->display_options['fields']['community_task_state_1']['field'] = 'community_task_state';
  $handler->display->display_options['fields']['community_task_state_1']['label'] = '';
  $handler->display->display_options['fields']['community_task_state_1']['advanced_render'] = 1;
  /* Sort criterion: Content: Updated date */
  $handler->display->display_options['sorts']['changed']['id'] = 'changed';
  $handler->display->display_options['sorts']['changed']['table'] = 'node';
  $handler->display->display_options['sorts']['changed']['field'] = 'changed';
  $handler->display->display_options['sorts']['changed']['order'] = 'DESC';
  $handler->display->display_options['sorts']['changed']['granularity'] = 'hour';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'community_task' => 'community_task',
  );
  $handler->display->display_options['filters']['type']['group'] = '0';
  $handler->display->display_options['filters']['type']['expose']['operator'] = FALSE;

  /* Filter criterion: Content: Promoted to front page */
  $handler->display->display_options['filters']['promote']['id'] = 'promote';
  $handler->display->display_options['filters']['promote']['table'] = 'node';
  $handler->display->display_options['filters']['promote']['field'] = 'promote';
  $handler->display->display_options['filters']['promote']['value'] = '0';

  /* Display: all (Page) */
  $handler = $view->new_display('page', 'all (Page)', 'page_1');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['path'] = 'community_tasks';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Community tasks';
  $handler->display->display_options['menu']['weight'] = 15;
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;


  /* Display: tasks feed */
  $handler = $view->new_display('feed', 'tasks feed', 'feed_1');
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'rss';
  $handler->display->display_options['row_plugin'] = 'node_rss';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['path'] = 'tasks/feed';
  $handler->display->display_options['displays'] = array(
    'page_1' => 'page_1',
    'default' => 0,
    'page_2' => 0,
  );

  /* Display: User acknowledgements */
  $handler = $view->new_display('page', 'User acknowledgements', 'page_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['path'] = 'user/%/community_tasks';
  $handler->display->display_options['title'] = 'Acknowledgements';
  $handler->display->display_options['defaults']['link_display'] = FALSE;
  $handler->display->display_options['link_display'] = 'user_tasks_completed_page';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Zone de texte */
  $handler->display->display_options['header']['text']['id'] = 'area';
  $handler->display->display_options['header']['text']['table'] = 'views';
  $handler->display->display_options['header']['text']['field'] = 'area';
  $handler->display->display_options['header']['text']['empty'] = TRUE;
  $handler->display->display_options['header']['text']['content'] = '<h4>Completed tasks</h4>';
  $handler->display->display_options['header']['text']['format'] = '2';
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Zone de texte */
  $handler->display->display_options['empty']['text']['id'] = 'area';
  $handler->display->display_options['empty']['text']['table'] = 'views';
  $handler->display->display_options['empty']['text']['field'] = 'area';
  $handler->display->display_options['empty']['text']['empty'] = FALSE;
  $handler->display->display_options['empty']['text']['content'] = 'No tasks completed yet';
  $handler->display->display_options['empty']['text']['format'] = '1';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: User: Uid */


  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'users';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['relationship'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['uid']['exception']['value'] = 'me';
  $handler->display->display_options['arguments']['uid']['exception']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['uid']['exception']['title'] = 'My';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'user';
  $handler->display->display_options['arguments']['uid']['default_argument_options']['user'] = FALSE;
  $handler->display->display_options['arguments']['uid']['title'] = 'Tasks assigned to %1';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['uid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['uid']['validate']['type'] = 'user';

  /* Filter criterion: Content: Type */
  $handler->display->display_options['defaults']['filters'] = FALSE;
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'community_task' => 'community_task',
  );
  $handler->display->display_options['filters']['type']['group'] = '0';
  $handler->display->display_options['filters']['type']['expose']['operator'] = FALSE;

  $translatables['community_tasks'] = array(
    t('Contributions'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Pas de Contributions pour l\'instant'),
    t('tasks completed'),
    t('Completed Contributions'),
    t('No tasks completed yet'),
    t('User commitments'),
    t('<h4>Completed tasks</h4>'),
    t('My'),
    t('User acknowledgements'),
    t('Acknowledgements'),
    t('all (Page)'),
  );

  $views[$view->name] = $view;
  return $views;
}
