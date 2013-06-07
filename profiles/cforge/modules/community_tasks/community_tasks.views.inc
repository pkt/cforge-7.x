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
  return $data;
}