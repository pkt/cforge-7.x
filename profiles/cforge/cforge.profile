<?php
// $Id:

//roles
define('RID_TRADER', 3);
define('RID_COMMITTEE', 4);
define('RID_SYSTEM', 7);

/*
 * implements hook_user_login
 */
function cforge_form_user_login_block_alter(&$form) {
  if (!array_key_exists('destination', $_GET)) {
    //if we are on a user page, stay there, otherwise redirect to news
    if (strpos(current_path(), 'user') !== 0) {
      $form['#action'] = url(current_path(), array('query' => array('destination' => 'news'), 'external' => FALSE));
    }
  }
}

function cf_vids($all = FALSE) {
  static $blocks;
  if (isset($blocks)) return $blocks;
  global $language;
  $langs = $all ? array_keys(language_list()) : array($language->language);
  $blocks = array();
  if (in_array('fr', $langs)) {
    $blocks['sel_promo'] = array(
      'url' => 'http://www.youtube.com/embed/fwy2sojt3ZM',
      'title' => '',
    );
    $blocks['decouvrir'] = array(
      //'url' => 'http://www.youtube.com/embed/videoseries?list=PLBA6ED7FC6AFC4A2A&amp;hl=en_US',
      'url' => 'http://www.youtube.com/embed/En1RWomDFgI',
      'title' => 'Video découvrir le site',
    );
  }
  if (in_array('es', $langs)) {
    $blocks['cf_training'] = array(
      'url' => 'http://www.youtube.com/embed/pEdk1gct0Iw?list=PL2C2A689416705667',
      'title' => 'Darse de alta en la Central de Talentos',
    );
  }
  if (in_array('el', $langs)) {
    $blocks['nitin'] = array(
      'url' => 'http://www.youtube.com/embed/dPN6SEaEfyE',
      'title' => 'Παρουσίαση του CForge',
    );
  }
  if (in_array('en', $langs)) {
    $blocks['nitin'] = array(
      'url' => 'http://www.youtube.com/embed/YvegNqKcQ-g',
      'title' => 'Mutual Credit',
    );
  }
  return $blocks;
}

/*
 * implements hook_block_info
 */
function cforge_block_info() {
  //these blocks will appear for all languages.
  foreach (cf_vids(TRUE) as $delta => $data) {
    $blocks[$delta] = array(
      'info' => $delta,
      'visibility' => BLOCK_VISIBILITY_LISTED,
      'pages' => "<front>\nLETS\ncommit\nfaq\ngalleries",
      'status' => 1,
    );
  }
  return $blocks;
}


/*
 * implements hook_block_info_alter
 */
function cforge_block_info_alter(&$blocks, $theme, $code_blocks) {
  if ($theme != variable_get('theme_default', $theme)) return;
  $blocks['system']['main-menu']['title'] = '<none>';
  $blocks['search']['form']['title'] =  '<none>';
  $blocks['user']['new']['visibility'] = BLOCK_VISIBILITY_LISTED;
  $blocks['user']['new']['pages'] = "<front>\nnews\nmembers";
  $blocks['user']['new']['user_block_whois_new_count'] = 5;
  $blocks['user']['new']['roles'] = array(DRUPAL_AUTHENTICATED_RID);

  if (isset($blocks['aggregator'])) {
    $blocks['aggregator']['feed-1']['visibility'] = BLOCK_VISIBILITY_LISTED;
    $blocks['aggregator']['feed-1']['pages'] = 'news*';
    $blocks['aggregator']['feed-1']['cac'] = 'news*';
  }

  if (array_key_exists('menu', $blocks)) {
    if (array_key_exists('secondary-menu', $blocks['menu'])) {
      $blocks['menu']['secondary-menu']['title'] = '<none>';
    }
    if (array_key_exists('visitors', $blocks['menu'])) {
      $blocks['menu']['visitors']['title'] = '<none>';
    }
  }

  //the roles don't make up part of the block_info, so we'll just hard set it here.
  db_delete('block_role')->condition('delta', array('visitors', 'main-menu'))->execute();
  db_insert('block_role')->fields(array('delta' => 'visitors', 'module' => 'menu', 'rid' => DRUPAL_ANONYMOUS_RID))->execute();
  db_insert('block_role')->fields(array('delta' => 'visitors', 'module' => 'menu', 'rid' => RID_COMMITTEE))->execute();
  db_insert('block_role')->fields(array('delta' => 'main-menu', 'module' => 'system', 'rid' => DRUPAL_AUTHENTICATED_RID))->execute();
}


/*
 * implements hook_block_view
 * put the menu blocks in place
 */
function cforge_block_view($delta) {
  $vids = cf_vids(FALSE);
  if (!isset($vids[$delta])) return array();
  return array(
    'subject' => isset($vids[$delta]['title']) ? $vids[$delta]['title'] : '<none>',
    'content' => '<iframe width="248" height=184 src="'.$vids[$delta]['url'].'" frameborder="0" allowfullscreen></iframe>'
  );
}

/*
 * implements hook_block_view_MODULE_DELTA_alter
 * Change the title of the user block
 */
function cforge_block_view_alter(&$renderable, $block) {
  if ($block->delta =='user-menu') $renderable['subject'] = format_username($GLOBALS['user']);
}

/*
 * Implements views hook_views_api
 */
function cforge_views_api() {
  return array(
    'api' => 3,
    'path' => drupal_get_path('module', 'cforge'),
  );
}

/*
 * implements hook_cron
 */
function cforge_cron() {
  db_query("DELETE FROM {sessions} WHERE uid = 0 AND timestamp < :dayago", array(':dayago' => strtotime('-1 day')));
  db_query("DELETE FROM {sessions} WHERE timestamp < :monthago", array(':monthago' => strtotime('-1 month')));
  db_query("DELETE FROM {watchdog} WHERE timestamp < :weekago", array(':weekago' => strtotime('-1 week')));

}

/**
 * implements hook_init().
 */
function cforge_init() {
  drupal_add_css(drupal_get_path('module', 'cforge').'/cforge.css');
}

/**
 * Implements hook_element_info_alter().
 * this is all the code from the disablepwstrength module
 */
function cforge_element_info_alter(&$types) {
  if (isset($types['password_confirm']['#process']) && (($position = array_search('user_form_process_password_confirm', $types['password_confirm']['#process'])) !== FALSE)) {
    unset($types['password_confirm']['#process'][$position]);
  }
}

/*
 * implements hook_menu
 */
function cforge_menu() {
  return array(
    'admin/config/cforge' => array(
      'title' => 'Cforge settings',
      'description' => 'settings not governed by other modules',
      'page callback' => 'drupal_get_form',
      'page arguments' => array('cforge_settings_form'),
      'access arguments' => array('administer nodes')
    ),
    'hamlets_helpdesk' => array(
      'title' => 'Hamlets helpdesk',
      'description' => 'Give/request help from other users of this software',
      'page callback' => 'drupal_goto',
      'page arguments' => array('http://hamlets.communityforge.net/questions'),
      'access arguments' => array('administer nodes'),
      'options' => array('attributes' => array('target'=>'_blank')),
    ),
    'robots.txt' => array(
      'page callback' => 'cforge_robots',
      'access callback' => TRUE,
      'type' => MENU_CALLBACK,
    ),
    'cforge/reset' => array(
      'type' => MENU_CALLBACK,
      'page callback' => 'cforge_reset',
      'access arguments' => array('access administration pages'),
      'file' => 'cforge.install'
    )
  );
}

/**
 * implements hook_menu_alter
 */
function cforge_menu_alter(&$items) {
  module_load_install('cforge');
  cforge_load_frontend();
  $items['user/%/propositions']['weight'] = 1;
  $items['user/%/statement']['weight'] = 2;
  $items['user/%user/contact']['weight'] = 3;

  //committee can re-arrange menu items but not add and remove them through the menu interface
  $items['admin/structure/menu/manage/%menu/add'] ['access arguments'] = array('access administration pages');
  $items['admin/structure/menu/manage/%menu/delete']['access arguments'] = array('access administration pages');
  //this improvement on core makes the menu item visible only if things underneath it are visible
  $items['node/add']['access callback'] = '_cf_add_access';
  //set the order of the user tabs, assuming usertabs has already altered them
  $items['user/%user/account/edit']['title'] = 'Settings';
  $items['user/%user/account/edit']['weight'] = 2;
  $items['user/%user/account/profile']['weight'] = 1;//see cforge_user_categories

  //i think this is a core bug, but we only notice it with i18n
  $items['user/%user/account/profile']['title'] = $items['user/%user/account/profile']['title arguments'][0];
  $items['user/%user/account/manage']['title'] = $items['user/%user/account/manage']['title arguments'][0];
  $items['user/%user/account/profile']['title callback'] = 't';
  $items['user/%user/account/manage']['title callback'] = 't';
}

/*
 * implements hook_translated_menu_link_alter
 */
function cforge_translated_menu_link_alter(&$item) {
  switch($item['link_path']) {
    case 'admin/people/launch':
      $item['title'] = t('Launch');break;//this shouldn't have been necessary
    case 'admin/people':
      $item['title'] = t('Manage people'); break;
    case 'admin/content':
      $item['title'] = t('Manage content'); break;
    case 'admin/structure/taxonomy/galleries':
      $item['title'] = t('Manage galleries');break;//this shouldn't have been necessary
  }
  if (strpos($item['link_path'], 'currencies')) {
    $currencies = &drupal_static('currencies');
    $map = explode('/', $item['link_path']);
    if (array_key_exists($map[4], $currencies)) {
      $item['title'] = t("Edit currency '@name'", array('@name' => $currencies[$map[4]]->human_name));
    }
    else $item['access'] = FALSE;
  }
}

/*
 * implements hook_system_modules_alter
 * disable the cforge_hosted checkbox, if present
 * move other modules into the cforge section
 */
function cforge_form_system_modules_alter(&$form) {
  $section = t('Other');
  if (isset($form['modules'][$section]) && array_key_exists('cforge_hosted', $form['modules'][$section])) {
    $form['modules'][$section]['cforge_hosted']['enable']['#disabled'] = TRUE;
  }
  $form['modules']['Community Forge']['#weight'] = -100;
}

/*
 * menu callback
 */
function cforge_settings_form() {
  $form['mail_footer'] = array(
    '#title' => t('Mail footer'),
    '#description' => t('This will be appended to all automated emails. HTML is allowed.'),
    '#type' => 'fieldset',
    'cforge_mail_footer' => array(
      '#type' => 'textarea',
      '#rows' => 4,
      '#default_value' => variable_get('cforge_mail_footer', '')
    ),
    'cforge_mail_tokens' => array(
      '#theme' => 'token_tree',
      '#token_types' => array('user', 'site'),
      '#global_types' => FALSE,
      '#weight' => 5,
    )
  );
  $form['cforge_robots_protect'] = array(
    '#title' => t('Conceal from search engines'),
    '#description' => t('Rewrites the robots.txt file'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('cforge_robots_protect', 0)
  );
  $form['cforge_neighbourhoods'] = array(
    '#title' => t('Localities'),
    '#description' => t('Limited list of possible neighbourhoods, one per line. Leave blank to allow a free choice'),
    '#type' => 'textarea',
    '#default_value' => variable_get('cforge_neighbourhoods', ''),
  );
  return system_settings_form($form);
}

/*
 * implements hook_user_presave
 * implements a cforge version of username
 */
function cforge_user_presave(&$edit, &$account, $category = NULL) {
  if ($category == 'account') {
    if (!empty($account->is_new)) {
      //if the user is being created, add the trader role
      $edit['roles'][RID_TRADER] = 'trader';
    }
  }
  //the following borrowed from user_user_presave which assumes it knows what categories these things are in.
  elseif($category == 'manage' && isset($edit['roles'])) {
    $edit['roles'] = array_filter($edit['roles']);
  }
  /*
  elseif($category == 'profile') {
    if (!empty($edit['picture_upload'])) {
      $edit['picture'] = $edit['picture_upload'];
    }
    // Delete picture if requested, and if no replacement picture was given.
    elseif (!empty($edit['picture_delete'])) {
      $edit['picture'] = NULL;
    }
  }
   *
   */
  if (array_key_exists('profile_address', $edit)) {
    if (!array_key_exists(LANGUAGE_NONE, $edit['profile_address']))debug($edit);
    //fix the username
    $edit['name'] = _cforge_make_username($edit['profile_address'][LANGUAGE_NONE][0]);
  }
}

/*
 * implements hook_node_view_alter
 */
function cforge_node_view_alter(&$render_array, $view_mode) {
  $render_array['comments']['#weight'] = 19;
  $render_array['links']['#weight'] = 20;
}

/*
 * implements hook_form_FORM_ID_alter
 */
function cforge_form_user_profile_form_alter(&$form, &$form_state) {
  $fieldnames = array_keys(field_info_instances('user', 'user'));
  if ($form['#user_category'] == 'account') {
    //the default option - all the user instances are attached in user_profile_form
    //and here we need to block them
    foreach ($fieldnames as $field_name) {
      $form[$field_name]['#access'] = substr($field_name, 0, 7) == 'account';
    }
    $form['account']['roles']['#access'] = FALSE;
    $form['account']['status']['#access'] = FALSE;
    unset($form['ckeditor']);

    //prevent editing of essential user 1 fields
    if ($form['#user']->uid == 1) {
      if ($GLOBALS['user']->uid != 1) {
        $form['account']['pass']['#access'] = FALSE;
        $form['account']['mail']['#access'] = FALSE;
        $form['account']['roles']['#access'] = FALSE;
      }
      $form['account']['status']['#access'] = FALSE;
    }
    //remove the current password validation
    // searches the #validate array for the current_pass validation function, and removes it
    $key = array_search('user_validate_current_pass', $form['#validate']);
    if ($key !== FALSE) {
      unset($form['#validate'][$key]);
    }
    // hide the current password fields
    $form['account']['current_pass_required_value']['#access'] = FALSE;
    $form['account']['current_pass']['#access'] = FALSE;
    //for cosmetic reasons
    $form['account']['roles'][DRUPAL_AUTHENTICATED_RID]['#access'] = FALSE;
  }
  else {
    //get these fields so we can selectively re-add them
    $pseudoform = array('#user' => $form['#user']);
    if($form['#user_category'] == 'manage') {
      user_account_form($pseudoform, $form_state);
      $form['account'] = array(
        'roles' => $pseudoform['account']['roles'],
        'status' => $pseudoform['account']['status']
      );
    }
    //now load up the fieldnames depending on their prefix
    $categ = substr($form['#user_category'], 0, 5);
    foreach($fieldnames as $field_name) {
      $field_name_prefix = substr($field_name, 0, 5);
      if ($field_name_prefix == 'field')$field_name_prefix = 'profi';
      if ($field_name_prefix == $categ) {
        $options = array('field_name' => $field_name);
        $form += _field_invoke_default('form', 'user', $form['#user'], $form, $form_state, $options);
      }
    }
  }
  _cf_modify_form_profile($form);
}

/*
 * implements hook_form_user_register_form_alter
 */
function cforge_form_user_register_form_alter(&$form) {
  _cf_modify_form_profile($form);
}

//modifications to the profile form for both creating and editing.
function _cf_modify_form_profile(&$form) {
  _cf_hide_filter();
  if (in_array($form['#user_category'], array('account', 'register'))) {
    //advanced_help
    _cf_prefix_help($form['account']['pass']['#description'], 'pass');
    _cf_prefix_help($form['account']['mail']['#description'], 'mail');
    _cf_prefix_help($form['account']['status']['#title'], 'status');
    _cf_prefix_help($form['account']['roles']['#title'], 'roles');
    _cf_prefix_help($form['limits_personal']['#description'], 'balance_limits');

    $form['picture']['picture_upload']['#title'] .= ' ('.t('No spaces in filenames!').')';
    _cf_prefix_help($form['picture']['picture_upload']['#description'], 'image');
    $form['account']['name']['#access'] = FALSE;
    $form['contact']['#access'] = FALSE;//everyone can be contacted
    $form['mimemail']['#access'] = FALSE;//everyone can be contacted
    $form['timezone']['#access'] = FALSE;

    //this system doesn't show usernames to anyone, but uses sky_seldulac_username() instead
    //prevent non-admin from editing account 1 login
    if ($form['#user']->uid == 1 && $GLOBALS['user']->uid != 1) {
      $form['account']['pass']['#type'] == 'hidden';
    }
  }
  if (in_array($form['#user_category'], array('profile', 'register'))) {
    //not sure how fields added by user 1 will behave or what the default filter is,
    //but I'm hiding the text filter selector anyway for aesthetic reasons. Could also be done in css
    $form['manage_notes'][LANGUAGE_NONE][0]['#format'] = 'plain_text';
    _cf_prefix_help($form['profile_address']['firstname']['#description'], 'name');
    $lan = $form['profile_phones']['#language'];
    $form['profile_phones'][$lan][0]['#prefix'] = t('Mobile phone');
    if (array_key_exists(1, $form['profile_phones'][$lan])) {
      $form['profile_phones'][$lan][1]['#prefix'] = t('Other phone');
    }
    unset($form['profile_phones'][$lan][0]['_weight']);
    unset($form['profile_phones'][$lan][1]['_weight']);
    $form['profile_phones'][$lan]['#cardinality'] = 1;//spoofs the theming

    if (!module_exists('uid_login')) {
      $form['profile_address'][LANGUAGE_NONE][0]['#description'] = t("Your login name is derived from your firstname + your family name.");
      if (property_exists($form['#user'], 'name')) {
         $form['profile_address'][LANGUAGE_NONE][0]['#description'] .= ' '.t("E.g. @name", array('@name' => $form['#user']->name));
      }
    }
    if ($neighbourhoods = variable_get('cforge_neighbourhoods')) {
      $form['profile_address'][LANGUAGE_NONE][0]['locality_block']['dependent_locality']['#type'] = 'select';
      $form['profile_address'][LANGUAGE_NONE][0]['locality_block']['dependent_locality']['#options'] = drupal_map_assoc(preg_split("/\r\n|\n|\r/", $neighbourhoods));
    }

    $form['#validate'][] = 'cforge_check_duplicate_name';
  }
  if ($form['#user_category'] == 'register') {
    $form['account']['name']['#value'] = 'name not yet supplied';
  }
}

/*
 * implements hook_user_view
 */
function cforge_user_view($account) {
  unset($account->content['account_offline']);
  $account->content['user_picture']['#weight'] = -50;//this is also floating left
  $addresses = field_get_items('user', $account, 'profile_address');
  $account->content['summary']['neighbourhood'] = array(
    '#title' => t('Neighbourhood'),
    '#type' => 'user_profile_item',
    '#markup' => $addresses[0]['dependent_locality']
  );
}

/*
 * implements hook_user_view_alter
 */
function cforge_user_view_alter(&$build) {
  unset($build['mimemail']);
}

function cforge_hook_info() {
  return array(
    'cf_block_setup' => array(),
    'cf_role_permissions' => array()
  );
}

function _cf_prefix_help(&$text, $topic) {
  //put the linked helpicon at the start of the given text
  $text = theme('advanced_help_topic', array('module' => 'cforge', 'topic' => $topic)) . $text;
}
/*
 * implements hook_help
 */
function cforge_help($path, $args) {
  if (substr($path, 0, 6) == 'user/%' && $args[2] != 'signall') {
    drupal_set_title(format_username(user_load($args[1])), PASS_THROUGH);
  }
}
/*
 * implements hook_admin_paths_alter
 */
function cforge_admin_paths_alter(&$paths) {
  $paths['admin/structure/taxonomy/*'] = 1;
  unset($paths['user/*/edit']);
}

/*
 * implements hook_form_FORM_ID_alter
 */
function cforge_form_user_admin_settings_alter(&$form) {
  unset($form['registration_cancellation']['user_register']['#options'][1]);
  unset($form['registration_cancellation']['#description']);
  unset($form['registration_cancellation']['#type']);
  $form['registration_cancellation']['#weight'] = -5;
  $form['registration_cancellation']['user_register']['#title'] = t('How to add new members');
  $form['registration_cancellation']['user_register']['#options'][0] = t('Only committee can create accounts');
  $form['registration_cancellation']['user_register']['#options'][2] =t('Anyone can create an account, then a committee member must enable it');
  $form['registration_cancellation']['user_cancel_method']['#access'] = FALSE;

  unset($form['email_no_approval_required']['#access']);
  if ($GLOBALS['user']->uid != 1) {
    $form['registration_cancellation']['#description'] = $form['registration_cancellation']['user_email_verification']['#description'];
    $form['registration_cancellation']['user_email_verification'] = FALSE;
    $form['personalization']['#access'] = FALSE;
    $form['contact']['#access'] = FALSE;
    $form['admin_role']['#access'] = FALSE;
  }
}

/*
 * implements hook_form_FORM_ID_alter
 * adding context to the site-information page for local admins
 */
function cforge_form_system_site_information_settings_alter(&$form) {
  $form['front_page']['#access'] = FALSE;
  $form['error_page']['#access'] = FALSE;
  $form['site_information']['site_name']['#description'] = t('Appears at the top of the page');
  $form['site_information']['slogan']['#description'] = t('Appears below the site name');
}

/**
 * implements hook_form_comment_form_alter
 */
function cforge_form_comment_form_alter(&$form) {
  _cf_hide_filter();
  unset($form['author']['_author']);
}

function _cf_menu_options() {
  return db_query("SELECT CONCAT(menu_name,':0'), title
    FROM {menu_custom}
    WHERE menu_name IN ('main-menu', 'secondary-menu', 'user-menu', 'visitors')"
  )->fetchAllKeyed();
}


/*
 * implements hook_form_FORM_ID_alter
 */
function cforge_form_node_form_alter(&$form, &$form_state) {
  //set the ckeditor according to node-type
  if (isset($form['body'])) {
    foreach (element_children($form['body']) as $lang) {
      foreach (element_children($form['body'][$lang]) as $delta) {
        $filter = in_array($form['#node']->type, array('page', 'story')) ? 'editor_full_html' : 'editor_filtered_html';
        if (array_key_exists($filter, filter_formats())) {
          $form['body'][$lang][$delta]['#format'] = $filter;
          _cf_hide_filter();
        }
      }
    }
  }
  //forces users to put pages in one of the four flattened menus, and other node types have no menus at all
  if ($form['#node']->type == 'page') {
    //prevent changing the alias of the home page
    if ($GLOBALS['user']->uid != 1) {
      if ($form['path']['alias']['#default_value'] == '<front>') {
        $form['path']['#access'] = FALSE;
      }
    }
    //flatten the menu, so you can only put things at the top level
    foreach ($form['menu']['link']['parent']['#options'] as $key => $linkname) {
      if (substr($linkname, 0, 2) == '--') {
        unset($form['menu']['link']['parent']['#options'][$key]);
      }
    }
    $form['menu']['link']['parent']['#title'] = t('Put in menu');

    drupal_add_css('.form-item-menu-enabled{display:none;}', array('type' => 'inline'));
    $form['menu']['enabled']['#default_value'] = TRUE;
    $form['menu']['link']['link_title']['#required'] = TRUE;
  }
  else {
    unset($form['menu']);
  }
  //rename the url alias field and explain it better
  if (in_array($form['#node']->type, array('page', 'document', 'story', 'event', 'image'))) {
    $form['path']['alias']['#title'] = t('Friendly address');
    $form['path']['alias']['#description'] = t("Give your page a more memorable address. E.g. 'articles-of-association'");
  }
  else {
    $form['path']['#access'] = FALSE;
  }
}

/*
 * implement hook_form_FORM_ID_alter
 */
function cforge_form_taxonomy_overview_vocabularies_alter(&$form, &$form_state, $form_id) {
  foreach (element_children($form) as $key) {
    $form[$key]['edit']['#access'] = user_access('administer taxonomy');
  }
}

/*
 * implements hook_form_FORM_ID_alter
 * remove the title
 */
function cforge_form_search_block_form_alter(&$form) {
  if ($GLOBALS['user']->uid != 1) {
    $form['search_block_form']['#title'] = '';
  }
}

/*
 * implements hook_form_taxonomy_form_term_alter
 * hide the text formatting options for taxonomy_term form
 */
function cforge_form_taxonomy_form_term_alter(&$form) {
  $form['description']['#format'] = 'plain_text';
  _cf_hide_filter();
}
/*
 * Ensure that the user-visible menus are all flat
 */
function cforge_form_menu_edit_item_alter(&$form) {
  if ($GLOBALS['user']->uid == 1) return;
  $form['parent']['#options'] = _cf_menu_options();
}

/*
 * implements hook_mail_alter
 * add the mail footer
 */
function cforge_mail_alter(&$message) {
  if (@$message['params']['module'] == 'contact') return;
  $footer =  token_replace(
    variable_get('cforge_mail_footer', ''),
    $message['params'],
    array('language' => $message['language'], 'sanitize' => FALSE)
  );
  $message['body'][] = $footer;
}


/*
 * menu callback
 * shortcut to the backup & restore module download backup
 */
function backup_direct() {
  $tables = array('cache', 'cache_admin_menu', 'cache_block', 'cache_bootstrap', 'cache_field', 'cache_filter', 'cache_image', 'cache_menu', 'cache_page', 'cache_path', 'cache_update', 'cache_views', 'cache_views_data', 'watchdog');

  foreach($tables as $table) {
    $queries[] = "TRUNCATE {$table}";
  }
  db_query(implode(';', $queries));
  $form_state['values'] = array(
    'profile_id' => NULL,
    'destination_id' => 'download',
    'source_id' => NULL,
  );
  drupal_form_submit('backup_migrate_ui_manual_quick_backup_form', $form_state);
  drupal_goto(BACKUP_MIGRATE_MENU_PATH .'/restore');
}


//protect certain fields from being inadvertantly included in views
function __cforge_views_pre_render(&$view) {
  if (user_access('access user profiles')) return;
  debug($view->result, "stripping users' pictures, mail and name from view $view->name");
  $private = array(
    'users_picture' => '',
    'users_mail' => variable_get('site_mail', 'blah'),
    'users_name' => ''
  );
  foreach ($private as $field => $value) {
    foreach ($view->result as $key=>$row) {
      $view->result[$key]->$field = $value;
    }
  }
}

/*
 * overrides theme template_preprocess_username, which truncates the username to 15 chars
 */
function cforge_preprocess_username(&$vars) {
  $vars['uid'] = (int) $vars['account']->uid;
  $vars['name'] = $vars['name_raw'];
}

/*
 * implements theme hook_process_username
 */
function cforge_process_username(&$vars) {
  if (!$GLOBALS['user']->uid) {
    $vars['name'] = t('Member @uid', array('@uid' => $vars['account']->uid));
  }
}

function _cf_hide_filter() {
  //the filter format chooser widget isn't added until hook_form_FORM_ID_alter, so we can hide it here with css
  drupal_add_css('fieldset.filter-wrapper{display:none;}', array('type' => 'inline'));
}
/*
 * implements hook_token_info_alter
 * remove the 'user:original' set of tokens, which is confusing
 */
function cforge_token_info_alter(&$items) {
  unset($items['tokens']['user']['original']);
}

/*
 * this special callback determines if the node/add container link is visible
 * not on the basis of whether the user can edit any content types,
 * but on the basis of whether any children of the link can be accessed.
 */
function _cf_add_access() {
  if (arg(0) == 'admin') return TRUE;
  static $access;
  $mlid = db_select('menu_links', 'ml')->fields('ml', array('mlid'))->condition('link_path', 'node/add')->execute()->fetchfield();
  $children = db_select('menu_links', 'ml')->fields('ml', array('link_path'))->condition('plid', $mlid)->condition('hidden', 0)->execute()->fetchcol();
  foreach ($children as $link_path) {
    $item = menu_get_item($link_path);
    if ($item['access'])return TRUE;
  }
}

/*
 * menu_callback
 */
function cforge_robots() {
  drupal_add_http_header('Content-type', 'text/plain');
  if (variable_get('cforge_robots_protect')) {
    echo 'User-agent: *
Disallow: /';
  }
  else {
    echo file_get_contents(DRUPAL_ROOT . '/profiles/cforge/robots.txt');
  }
  exit;
}


/*
 * this does the same as entity tokens, but without making a mess
 */
function addressfield_tokens($type, $tokens, array $data = array(), array $options = array()) {
  if ($type == 'entity') return;
  $entity = &$data[$type];
  $url_options = array('absolute' => TRUE);
  $sanitize = !empty($options['sanitize']);
  $language_code = NULL;

  if (isset($options['language'])) {
    $url_options['language'] = $options['language'];
    $language_code = $options['language']->language;
  }
  $replacements = array();
  //find out what entities have an address field.
  foreach(field_read_fields(array('type' => 'addressfield')) as $field_name => $field) {
    foreach ($tokens as $name => $original) {
      if (!strpos($name, ':')) continue;
      list ($prefix, $prop) = explode(':', $name);
      if ($prefix != $field_name) continue;
      $replacements[$original] = $entity->{$field_name}[LANGUAGE_NONE][0][$prop];
    }
  }
  return $replacements;
}

/*
 * implements hook_token_info for the addressfield module
 */
function addressfield_token_info() {
  //find out what entities have an address field.
  foreach(field_read_fields(array('type' => 'addressfield')) as $field_name => $field) {
    foreach (field_read_instances(array('field_name' => $field_name)) as $instance) {
      $entities[$instance['entity_type']][] = $field_name;
    }
  }
  foreach ($entities as $entity_type => $field_names) {
    foreach ($field_names as $field_name) {
      foreach (addressfield_data_property_info() as $column => $data) {
        $info['tokens'][$entity_type]["$column"] = array(
          'name' => $data['label'],
          'description' => t('Addressfield property'),
          'type' => NULL//not exactly sure why this is needed to get past token_get_invalid_tokens() in token.module
        );
      }
    }
  }
  return $info;
}

/**
 * Implements hook_ctools_plugin_directory().
 */
function cforge_ctools_plugin_directory($module, $plugin) {
  if ($module == 'addressfield') {
    return 'plugins/' . $plugin;
  }
}

function cforge_user_categories() {
  return array(
    array(
      'name' => 'profile',
      'title' => 'My info',
      'weight' => 1,
    ),
    array(
      'name' => 'manage',
      'title' => 'Manage',
      'weight' => 3,
      'access callback' => 'user_access',
      'access arguments' => array('administer users')
    )
  );
  t('My info');
  t('Manage');
}

/*
 * implements hook_uchoo_segments()
 */
function cforge_uchoo_segments() {
  return array(
    'user_chooser_segment_neighbourhood' => t('Everyone in the same neighbourhood as the current user')
  );
}
function user_chooser_segment_neighbourhood($query, array $neighbourhoods) {
  //temp filter until user_chooser 1.3 comes through
  if (!array_filter($neighbourhoods)) {
    $items = field_get_items('user', user_load($GLOBALS['user']->uid), 'profile_address');
    $neighbourhoods[] = $items[0]['dependent_locality'];
  }
  $query->join('field_data_profile_address', 'pa', 'pa.entity_id = u.uid');
  $query->condition('profile_address_dependent_locality', $neighbourhoods);//dont' know if it is case sensitive.

}
//in_ version of user_chooser segment
function in_user_chooser_segment_neighbourhood(array $neighbourhoods, $uid = NULL) {
  $account = empty($uid) ? $GLOBALS['user'] : user_load($uid);
  $items = field_get_items('user', $account, 'profile_address');
  return in_array($items[0]['dependent_locality'], $neighbourhoods);
}


/*
 * implements hook_field_access
 * prevent other members from seeing the address, phone number & notes
 */
function cforge_field_access($op, $field, $entity_type, $entity, $account) {
  if ($entity_type == 'user' && $field['field_name'] == 'manage_notes') {
    return user_access('administer users');
  }
}

/*
 * user profile form validate function
 * because we are manipulating the user names, we need to do our own duplicate check here
 */
function cforge_check_duplicate_name($form, $form_state) {
  $duplicate = db_query(
    "SELECT name FROM {users} where name = :name AND uid != :uid",
    array(
      ':name' => _cforge_make_username($form_state['values']['profile_address']['und'][0]),
      ':uid' => array_key_exists('#user', $form) ? $form['#user']->uid : 0
    )
  )->fetchField();
  if ($duplicate) {
    form_set_error('first_name', t('The name @name is already used.', array('@name' => $duplicate)));
  }
}

function _cforge_make_username($address) {
  $username = trim($address['first_name']);
  if (array_key_exists('last_name', $address)) {
    $username .= ' '.trim($address['last_name']);
  }
  return $username;
}
/**
 * implements hook_file_download
 * corrects for a design fault in drupal
 * when the default file wrapper is private, uploaded logos cannot be seen unless access is specifically granted
 * this function reveals all images, by file extension
 */
function cforge_file_download($uri) {
  $info = pathinfo($uri);
  if (!in_array($info['extension'], array('gif', 'jpg', 'jpeg', 'png'))) return;
  $info = image_get_info($uri);
  return array('Content-Type' => $info['mime_type']);
}
