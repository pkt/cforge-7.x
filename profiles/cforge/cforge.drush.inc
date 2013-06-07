<?php
// $Id: cforge.drush.inc

/**
 * Implementation of hook_drush_help().
 */
function cforge_drush_help($section) {
  switch ($section) {
    case 'drush:cforge-mail':
      return dt('print the email addresses of all the members, by role rid');
    case 'drush:cforge-reset':
      return dt('Reset menus, blocks, translations');
  }
}

/**
 * Implementation of hook_drush_command().
 *
 */
function cforge_drush_command() {
  $items['cforge-mail'] = array(
    'callback' => 'drush_cforge_contact_role',
    'description' => 'print the email addresses of all the members, by role rid',
    'arguments' => array(
      'rid' => 'the role id of the members you want to list',
    ),
    'examples' => array(
      'drush cforge-mail 4' => 'print the email addresses of all committee members',
    ),
  );
  $items['cforge-reset'] = array(
    'callback' => 'drush_cforge_reset',
    'description' => 'Reset menus, blocks, translations',
    'arguments' => array(
      'type' => 'translations, permissions, views, blocks, menus, or all',
      'param' => '(optional) depends on above, or all',
    ),
    'examples' => array(
      'drush cforge-reset permissions' => 'reset permissions for trader role',
      'drush cforge-reset mails' => 'mail templates back to their localised originals defined in cforge.install',
      'drush cforge-reset blocks system' => 'replace all the blocks from the system module',
      'drush cforge-reset translations ctools views' => 'reload all the translations from the given package, or cforge distro if no module given',
    ),
    'options' => array(
       '--hard' => 'hard reset'
    )
  );
  return $items;
}

function drush_cforge_contact_role($rid) {
  $result = db_query("SELECT mail from {users} u LEFT JOIN {users_roles} ur ON u.uid = ur.uid WHERE ur.rid = %d", $rid);
  while ($mail = db_result($result)) $output .= $mail .', ';
  drush_print($output);
}


function drush_cforge_reset($type, $option = NULL) {
  module_load_install('cforge');
  drush_print(cforge_reset($type, $option, drush_get_option('hard')));
}
