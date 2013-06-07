<!-- start node.tpl.php -->
<div id="node-<?php print $node->nid; ?>" class="node<?php print " node-" . $node->type; ?>">
  <?php if ($teaser || arg(1) != $node->nid) : ?>
  <h2 class="title"><a href="<?php print $node_url; ?>" title="<?php print $title; ?>"><?php print $title; ?></a></h2>
  <?php endif; ?>

<div class="content">
  <?php print render($content); ?>
</div>

</div>
<!-- end node.tpl.php -->
