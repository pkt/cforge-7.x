<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns = "http://www.w3.org/1999/xhtml" lang = "fr" xml:lang = "fr">
  <head>
    <meta http-equiv = "Content-Type" content = "text/html; charset=utf-8" />
    <meta http-equiv = "Content-Type" content = "text/html; charset=utf-8" />
    <meta name="robots" content = "noindex, nofollow, noarchive" />
    <title><?php print variable_get('site_name', ''); ?></title>
    <style>
      img{height:5em;float:left;margin-right:1em}
      thead{background-color:#dddddd;}
      th{text-align: left; font-size:1.3em;}
      caption {text-align: left; font-size:2em;}
      table{width:100%;margin-bottom:1em; font-family: arial; font-size: 8pt; page-break-inside:auto;}
      td{border-bottom:thin solid #dddddd;}

    </style>
  </head>
  <body onload = "window.print();">
    <img src = "<?php print theme_get_setting('logo'); ?>" alt = "logo" />
      <h1><?php
      print $page_title; //as determined in the view
      ?></h1>
    <?php print $table; ?>
    <font size ="-1"><?php print t('Printed on @date', array('@date' => format_date(time(), 'small'))); ?> </font>
  </body>
</html>
