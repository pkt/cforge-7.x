<?php

/*
 * implements views hook_views_plugins
 */
function cforge_offline_views_plugins() {
  return array(
    'module' => 'cforge_offline',
    'display' => array(
      'print-table' => array(
        'title' => 'print-table',
        'help' => t('An html table sent direct to the browser'),
        'handler' => 'views_plugin_display_print_table',
        'path' => drupal_get_path('module', 'cforge_offline'),
        'uses hook menu' => TRUE,
        'use ajax' => FALSE,
        'use pager' => FALSE,
        'use more' => FALSE,
        'accept attachments' => TRUE,
        'theme' => 'print_table',
        'theme file' => 'cforge_offline.module'
      )
    ),
  );
}

