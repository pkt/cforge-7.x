<?php
// $Id:
/**
 * @file
 * cross between views_plugin_display_page.inc and views_plugin_display_feed.inc
 */

/**
 * This plugin is somewhat like a page, because it displays as the main item,
 * and somewhat like an attachment, because it is reached through a link at the bottom of other views
 */
class views_plugin_display_print_table extends views_plugin_display_page {

  /**
   * We skip the normal drupal page theming and output the themed view directly
   * Then exit.
   */
  function execute() {
    // Let the world know that this is the page view we're using.
    views_set_page_view($this->view);
    // Prior to this being called, the $view should already be set to this
    // display, and arguments should be set on the view.
    $this->view->build();
    if (!empty($this->view->build_info['fail'])) {
      return drupal_not_found();
    }
    if (!empty($this->view->build_info['denied'])) {
      return drupal_access_denied();
    }
    print theme('print_table', array(
      'table' => $this->view->render(),
      'page_title' => filter_xss_admin($this->view->get_title())
    ));
    die();
  }

  function render() {
    return $this->view->style_plugin->render($this->view->result);
  }


  function preview() {
    if (!empty($this->live_preview)) {
      return '<pre>' . check_plain($this->view->render()) . '</pre>';
    }
    return $this->view->render();
  }

  function option_definition() {
    $options = parent::option_definition();
    unset($options['menu']);

    $options['attachment_position'] = array('default' => 'after');
    $options['inherit_arguments'] = array('default' => TRUE);
    $options['displays'] = array('default' => array());
    return $options;
  }

  function options_summary(&$categories, &$options) {
    // It is very important to call the parent function here:
    parent::options_summary($categories, $options);
    unset($options['menu']);
    // Since we're childing off the 'page' type, we'll still *call* our
    // category 'page' but let's override it so it says feed settings.
    $categories['page']['title'] = t('Print-page settings');
    $categories['page']['column'] = 'second';

    $displays = array_filter($this->get_option('displays'));
    if (count($displays) > 1) {
      $attach_to = t('Multiple displays');
    }
    else if (count($displays) == 1) {
      $display = array_shift($displays);
      if (!empty($this->view->display[$display])) {
        $attach_to = check_plain($this->view->display[$display]->display_title);
      }
    }
    if (!isset($attach_to)) {
      $attach_to = t('None');
    }

    $options['displays'] = array(
      'category' => 'page',
      'title' => t('Attach to'),
      'value' => $attach_to,
    );
    $options['attachment_position'] = array(
      'category' => 'page',
      'title' => t('Position'),
      'value' => $this->attachment_positions($this->get_option('attachment_position')),
    );
  }

  /**
   * Provide the default form for setting options.
   */
  function options_form(&$form, &$form_state) {
    // It is very important to call the parent function here.
    parent::options_form($form, $form_state);
    switch ($form_state['section']) {
      case 'displays':
        $form['#title'] .= t('Attach to');
        $displays = array();
        foreach ($this->view->display as $display_id => $display) {
          if (!empty($display->handler) && $display->handler->accept_attachments()) {
            $displays[$display_id] = $display->display_title;
          }
        }
        $form['displays'] = array(
          '#type' => 'checkboxes',
          '#description' => t('The feed icon will be available only to the selected displays.'),
          '#options' => $displays,
          '#default_value' => $this->get_option('displays'),
        );
        break;

      case 'attachment_position':
        $form['#title'] .= t('Position');
        $form['attachment_position'] = array(
          '#type' => 'radios',
          '#description' => t('Attach before or after the parent display?'),
          '#options' => $this->attachment_positions(),
          '#default_value' => $this->get_option('attachment_position'),
        );
        break;
      case 'path':
        $form['path']['#description'] = t('This view will be displayed by visiting this path on your site. It is recommended that the path be something like "path/%/%/feed" or "path/%/%/rss.xml", putting one % in the path for each argument you have defined in the view.');
    }
  }

    /**
   * Provide the default form for setting options.
   */
  function _options_form(&$form, &$form_state) {
    // It is very important to call the parent function here:
    parent::options_form($form, $form_state);

    switch ($form_state['section']) {
      case 'inherit_arguments':
        $form['#title'] .= t('Inherit contextual filters');
        $form['inherit_arguments'] = array(
          '#type' => 'checkbox',
          '#title' => t('Inherit'),
          '#description' => t('Should this display inherit its contextual filter values from the parent display to which it is attached?'),
          '#default_value' => $this->get_option('inherit_arguments'),
        );
        break;
      case 'inherit_exposed_filters':
        $form['#title'] .= t('Inherit exposed filters');
        $form['inherit_exposed_filters'] = array(
          '#type' => 'checkbox',
          '#title' => t('Inherit'),
          '#description' => t('Should this display inherit its exposed filter values from the parent display to which it is attached?'),
          '#default_value' => $this->get_option('inherit_exposed_filters'),
        );
        break;
      case 'inherit_pager':
        $form['#title'] .= t('Inherit pager');
        $form['inherit_pager'] = array(
          '#type' => 'checkbox',
          '#title' => t('Inherit'),
          '#description' => t('Should this display inherit its paging values from the parent display to which it is attached?'),
          '#default_value' => $this->get_option('inherit_pager'),
        );
        break;
      case 'render_pager':
        $form['#title'] .= t('Render pager');
        $form['render_pager'] = array(
          '#type' => 'checkbox',
          '#title' => t('Render'),
          '#description' => t('Should this display render the pager values? This is only meaningful if inheriting a pager.'),
          '#default_value' => $this->get_option('render_pager'),
        );
        break;
      case 'attachment_position':
        $form['#title'] .= t('Position');
        $form['attachment_position'] = array(
          '#type' => 'radios',
          '#description' => t('Attach before or after the parent display?'),
          '#options' => $this->attachment_positions(),
          '#default_value' => $this->get_option('attachment_position'),
        );
        break;
      case 'displays':
        $form['#title'] .= t('Attach to');
        $displays = array();
        foreach ($this->view->display as $display_id => $display) {
          if (!empty($display->handler) && $display->handler->accept_attachments()) {
            $displays[$display_id] = $display->display_title;
          }
        }
        $form['displays'] = array(
          '#type' => 'checkboxes',
          '#description' => t('Select which display or displays this should attach to.'),
          '#options' => $displays,
          '#default_value' => $this->get_option('displays'),
        );
        break;
    }
  }


  /**
   * Perform any necessary changes to the form values prior to storage.
   * There is no need for this function to actually store the data.
   */
  function options_submit(&$form, &$form_state) {
    // It is very important to call the parent function here:
    parent::options_submit($form, $form_state);
    switch ($form_state['section']) {
      case 'displays':
      case 'attachment_position':
        $this->set_option($form_state['section'], $form_state['values'][$form_state['section']]);
        break;
    }
  }

  function attachment_positions($position = NULL) {
    $positions = array(
      'before' => t('Before'),
      'after' => t('After'),
      'both' => t('Both'),
    );

    if ($position) {
      return $positions[$position];
    }

    return $positions;
  }

  /**
   * Attach to another view.
   */
  function attach_to($display_id) {
    $displays = $this->get_option('displays');
    if (empty($displays[$display_id])) {
      return;
    }
    if ($this->get_plugin()) {
      $path = array($this->get_path());
      //tricky to get the args out of the view object
      if (count($this->view->args)) {
        $path =  array_merge($path, $this->view->args);
      }

      //this will show the print icon eventually
      $img_icon = theme('image', array('path' => drupal_get_path('module', 'cforge_offline') . '/print_icon.gif'));
      $attachment = l($img_icon, implode('/', $path), array('html' => TRUE));
      $attachment .= l(t('Printer-friendly version'), implode('/', $path));
    }
    $pos = &$this->get_option('attachment_position');
    if ($pos == 'both' || $pos == 'before') {
      $this->view->attachment_before .= $attachment;
    }
    if ($pos == 'both' || $pos == 'after') {
      $this->view->attachment_after .= $attachment;
    }
  }
  function uses_breadcrumb() {
    return FALSE;
  }

  function uses_link_display() {
    return TRUE;
  }
}
