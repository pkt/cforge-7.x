<?php print render($page['header']); ?>

<div id="wrapper">
  <div id="header">
    <?php if (isset($page['headerright'])) print render($page['headerright']); ?>
    <img src="<?php print $logo; ?>" alt="<?php print $site_name; ?>" class="logo" />
    <h1>
      <a href="<?php print $base_path; ?>" title="<?php print $site_name; ?>"><?php print $site_name; ?></a>
    </h1>
    <br /><div class="slogan"><?php print $site_slogan; ?> </div>
  </div>

  <div id = "navigation">
    <div class ="wrap-center">
    <!-- the following can be either blocks, or defined in sky_seldulac_preprocess_page when I get time I'll make it all blocks -->
    <?php if (!empty($page['navigation']))print render($page['navigation']); ?>
    </div>
  </div>


  <div class="container">
    <?php if (isset($page['sidebar_first'])): ?>
      <div id="sidebar-left" class="sidebar">
          <?php print render($page['sidebar_first']); ?>
      </div>
    <?php endif; ?>
    <div id="main">
      <div class="main-inner">
        <?php if ($page['#show_messages'] && strlen($messages)): ?>
          <?php print $messages; ?>
        <?php endif; ?>
        <?php if ($title): ?>
          <h1 class="title"><?php print $title; ?></h1>
        <?php endif; ?>
        <?php print render($title_suffix); ?>
        <?php print render($page['help']); ?>
        <?php print render($tabs); ?>
        <?php print render($title_prefix); ?>
        <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
        <?php print render($page['content']); ?>
        <!-- END CONTENT -->
        <?php if ($feed_icons): ?>
          <div id="feed-icons">
            <?php print $feed_icons; ?>
          </div>
        <?php endif; ?>
        <?php if (isset($page['contentbottom'])): ?>
          <?php print render($page['contentbottom']); ?>
        <?php endif; ?>
      </div>
      <!-- END MAIN INNER -->
    </div>
    <!-- END MAIN -->
    <?php if (isset($page['sidebar_second'])): ?>
      <div id="sidebar-right" class="sidebar">
        <?php print render($page['sidebar_second']); ?>
      </div>
    <!-- END SIDEBAR RIGHT -->
    <?php endif; ?>
  </div>
  <!-- END CONTAINER -->
  <div class="push">&nbsp;</div>
</div>
<!-- END WRAPPER -->
<div id="footer">
  <div id="footer-content">
  <?php print render($page['contentfooter']); ?>
  <?php print render($page['footer']); ?>
  </div>
  <div class="bottom">
    <span class="fl">&nbsp;</span>
    <span class="middle">&nbsp;</span>
    <span class="fr">&nbsp;</span>
  </div>
  <div id="credit"><?php print t('Site designed and hosted for free by !cforge, a non-profit association registered in Geneva, Switzerland.', array('!cforge' => l('Community Forge', 'http://communityforge.net'))) ?></div>
</div>
