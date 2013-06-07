<!-- start block.tpl.php -->
<div id="<?php print $block_html_id; ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>
<?php if ($block->subject): ?>
  <div class="title"><?php print $block->subject; ?></div>
<?php endif; ?>
<?php print render($title_suffix); ?>
<div class="content"><?php print $content; ?></div>
</div>
<!-- start block.tpl.php -->
