<?php


/**
 * Override theme_menu_local_task().
 * Returns the rendered local tasks. The default implementation renders
 * them as tabs.
 *
 * @ingroup themeable
 */
function sky_seldulac_menu_local_tasks() {
  $primary = menu_primary_local_tasks();
  $secondary = menu_secondary_local_tasks();
  $output = '';
  if ($primary || $secondary) {
    if ($primary) {
      $output .= "\n".'<div class="tabs-primary">'."\n".
      '  <ul>'."\n". render($primary) .'</ul>'."\n".
      '</div>';
    }
    if ($secondary) {
      $output .= "\n".'<div class="tabs-secondary">'."\n" .
      '  <ul>'."\n". render($secondary) .'</ul>'."\n" .
      '</div>';
    }
    return '<div class="tab-wrapper">' . $output .'</div>';
  }
}

/**
* @param array $variables
* @return string
*/
function sky_seldulac_menu_local_action($variables) {
  $link = $variables['element']['#link'];
  $output = '<li>';
  $options = array('attributes' => array('title' => @$link['description']));
  if (isset($link['localized_options'])) {
    $options += $link['localized_options'];
  }

  if (isset($link['href'])) {
    $output .= l($link['title'], $link['href'], $options);
  }
  elseif (!empty($link['localized_options']['html'])) {
    $output .= $link['title'];
  }
  else {
    $output .= check_plain($link['title']);
  }
  $output .= "</li>\n";
  return $output;
}

function sky_seldulac_feed_icon($variables) {
  $text = t('Subscribe to !feed-title', array('!feed-title' => $variables['title']));
  if ($image = theme('image', array('path' => 'misc/feed.png', 'width' => 16, 'height' => 16, 'alt' => $text))) {
    $icon = l($image, $variables['url'], array('html' => TRUE, 'attributes' => array('class' => array('feed-icon'), 'title' => $text)));
    $help =  theme('advanced_help_topic', array('module' => 'cforge', 'topic' => 'feed'));
    return  $icon.$help; 
  }
}

