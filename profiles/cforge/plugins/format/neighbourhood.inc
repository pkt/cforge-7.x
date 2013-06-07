<?php

/**
 * @file
 * reveal the sub-locality district
 */

$plugin = array(
  'title' => t('Neighbourhood & Cforge prefereces'),
  'format callback' => 'addressfield_format_neighbourhood_generate',
  'type' => 'neighbourhood',
  'weight' => 100,
);

/**
 * Format callback.
 *
 * @see CALLBACK_addressfield_format_callback()
 */
function addressfield_format_neighbourhood_generate(&$format, $address, $context = array()) {
  unset($format['street_block']['premise']);
  unset($format['locality_block']['administrative_area']);
  $format['locality_block'] = array('dependent_locality' => array(
    '#title' => t('Neighbourhood'),
    '#required' => TRUE,
    '#size' => 20,
    '#attributes' => array('class' => array('organisation-name')),
  )) + $format['locality_block'];
  $format['street_block']['thoroughfare']['#title'] = t('Street address');
  $format['name_block']['first_name']['#size'] = 12;
  $format['name_block']['last_name']['#size'] = 12;

  //unrequire all these fields for now. We're not her to spy!
  $format['name_block']['last_name']['#required'] = FALSE;
  if (isset($format['street_block']['thoroughfare'])) $format['street_block']['thoroughfare']['#required'] = FALSE;
  if (isset($format['locality_block']['locality'])) $format['locality_block']['locality']['#required'] = FALSE;
  if (isset($format['locality_block']['postal_code'])) $format['locality_block']['postal_code']['#required'] = FALSE;
}


