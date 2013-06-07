<?php
// $Id: user-profile.tpl.php,v 1.2.2.1 2008/10/15 13:52:04 dries Exp $

/**
 * This has to handle all the likely elements from all the modules
 * so it might get a bit rough towards the bottom
 *
 * @see user-profile-category.tpl.php
 *   Where the html is handled for the group.
 * @see user-profile-item.tpl.php
 *   Where the html is handled for each item in the group.
 * @see template_preprocess_user_profile()
 *
 *
 * @see template_preprocess_user_profile()
 */
?>

<div id ="profile-picbox">
<?php if (isset($user_profile['manage_responsibility'])) print render($user_profile['manage_responsibility']); ?>
  <?php print render($user_profile['user_picture']); ?>
  <?php if (isset($user_profile['acknowledgements']))print render($user_profile['acknowledgements']); ?><br />
  <?php if (isset($user_profile['newbies']))print render($user_profile['newbies']); ?>
</div>

<div style ="clear:none;">
<?php if (isset($user_profile['offline_contact'])) print render($user_profile['offline_contact']); ?>
<?php if (isset($user_profile['profile_address'])) print render($user_profile['profile_address']); ?>
<?php if (isset($user_profile['current_newbies'])) print render($user_profile['current_newbies']); ?>
<?php if (isset($user_profile['welcomed_by'])) print render($user_profile['welcomed_by']); ?>
<?php if (isset($user_profile['trader_expiry'])) print render($user_profile['trader_expiry']); ?>
</div>

<?php if (isset($user_profile['profile_phones'])) print render($user_profile['profile_phones']); ?>

<?php if (module_exists('cforge_currencies') && array_key_exists('balances', $account->content)) : ?>
<table width ="100%" style ="clear:both;">
  <tr align = "center">
    <th><?php print t('Balance history'); ?></th>
    <th><?php print t('Stats'); ?></th>
    <th><?php print t('Pending transactions'); ?></th>
  </tr>
  <tr>
    <td>
      <?php print render($user_profile['balance_history']); ?>
    </td>
    <td style ="text-align:center;">
      <?php if (isset($user_profile['balance_limits'])) print render($user_profile['balance_limits']); ?>
      <?php if (isset($user_profile['balances'])) print render($user_profile['balances']); ?>
    </td>
    <td>
      <?php print render($user_profile['pending_transactions']); ?>
    </td>
  </tr>
</table>
<?php endif; ?>

<?php print render($user_profile); ?>

