<?php
/**
 * @file
 * Contains default views on behalf of the transactions  module.
 */

/**
 * Implements hook_views_data().
 */
function community_tasks_views_data() {
  $data = array();
  $data['community_task_count']['table']['group'] = 'acknowledgements';

  $data['community_task_count']['table']['base'] = array(
    'field' => 'tasks',
    'title' => t('Number of acknowledgements'),
  );
  $data['community_task_count']['table']['join'] = array(
    'users' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
  );
  $data['community_task_count']['tasks'] = array(
    'title' => t('Total'),
    'field' => array(
      'help' => t("The total number of acknowledgements received by the user"),
      'handler' => 'views_handler_field',
    )
  );
  return $data;
}


/**
 * Implements hook_views_data_alter().
 */
function community_tasks_views_data_alter(&$tables) {
  $tables['node']['community_task_state'] = array(
    'title' => t('Community Tasks state'),
    'help' => t("Node type '@type' only. Possible states are: Open, Committed, Completed", array('@type' => 'community-task')),
    'field' => array(
      'handler' => 'views_handler_field_community_tasks_state',
      'format' => 1
    ),
  );
}