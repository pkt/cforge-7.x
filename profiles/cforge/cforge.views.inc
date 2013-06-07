<?php


/*
 * implements hook_views_data_alter
 */
function cforge_views_data_alter(&$data) {
  //Explicitly expose the locality part of the addressfield
  //this way, the fieldAPI access control does not apply
  $data['field_data_profile_address']['table']['group']  = t('User');
  $data['field_data_profile_address']['profile_address_dependent_locality'] = array(
    'title' => t('Neighbourhood'),
    'help' => t('N.B. This bypasses the normal fieldAPI access control on the profile_address field.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  unset($data['field_data_profile_address']['profile_address_first_name']['argument']['empty field name']);
  unset($data['field_data_profile_address']['profile_address_last_name']['argument']['empty field name']);
}
