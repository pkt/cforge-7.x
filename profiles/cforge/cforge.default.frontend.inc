<?php
//this file must be named cforge_* in order to be seen by transaction template extractor potx

module_load_install('cforge');

/*
 * Cforge .front file, one for each theme
 * runs at the last stage of installation only
 * manages which cforge_* modules are enabled during the installation procedure
 * and all block positions according to the theme
 * and all menu items in specific menus
 */
function cforge_frontend_modules() {
  return array(
    'cforge_currencies',
    'cforge_events',
    'cforge_yell',
    'cforge_docs',
    'cforge_offline',
    'cforge_gallery',
    'cforge_broadcast'
  );
}

function cforge_frontend_theme() {
  return 'sky_seldulac';
}
function cforge_frontend_frontpage() {
  //this is the alias of a node inserted in cforge_frontend_default_content
  return 'home';
}
/*
 * declare all the visible menu items
 * anything not already in that menu will be cloned
 * any path not already in the menu_router will be ignored
 * any path without a title will use its existing title.
 *
 */
function cf_frontend_menu() {
  $positions = array(
    'user-menu' => array(
      'user',
      'transact/1stparty',
      'transact/3rdparty',
      'node/add/offer',
      'node/add/want',
      'node/add',
      'admin/people',
      'admin/content',
      'admin/structure/taxonomy/galleries',
      'admin/config/system/backup_migrate/export',
      'hamlets_helpdesk',
      'user/logout'
    ),
    'secondary-menu' => array(
      db_query("SELECT source FROM url_alias where alias = 'faq'")->fetchField(),//drupal_lookup_path is too language dependent
      'contact',
      'galleries',
      'events-all',
    ),
    'main-menu' => array(
      'news',
      'offers',
      'members',
      'wants',
      'transactions',
      'community_tasks'
    ),
    //put things things here to hide them
    'navigation' => array(),
    'setup' => array(
      'admin/modules',
      'admin/config/system/site-information',
      'admin/appearance/settings/sky_seldulac',
      'admin/config/people/accounts',
      'admin/config/ow',
      'admin/structure/taxonomy',
      'admin/structure/menu/manage/main-menu',
      'admin/structure/menu/manage/secondary-menu',
      'admin/structure/menu/manage/visitors',
      'admin/structure/contact',
      'admin/config/cforge',
      'admin/accounting/intertrade',
      'admin/people/launch',
       BACKUP_MIGRATE_MENU_PATH .'/restore'
    ),
    //the visitors menu is not declared here because all the links are placed there by nodes
  );
  drupal_load('module', 'mcapi');
  currencies_load();
  $currcodes = &drupal_static('currencies');
  foreach (array_keys($currcodes) as $currcode) {
    $currs[] = 'admin/accounting/currencies/list/'.$currcode.'/edit';
  }
  array_splice($positions['setup'], 5, 0, $currs);
  return $positions;
}

//expected function
//unfortunately potx module ignores this file, and I can't think how to get the menu names and descriptions elsewhere
function cforge_frontend_menus() {
  $all_menus = menu_get_menus();
  //add the custom menus
  $custom_menus[] = array(
    'menu_name' => 'visitors',
    'title' => t("Visitor menu"),
    'description' => t('For visitors who are not logged in')
  );
  $custom_menus[] = array(
    'menu_name' => 'secondary-menu',//this is because that's how it worked in Drupal6
    'title' => t('Secondary links menu'),
    'description' => t('Less prominent links, for all users')
  );
  foreach ($custom_menus as $info) {
    if (!isset($all_menus[$info['menu_name']])) {
      menu_save($info);
    }
  }
  variable_set('menu_secondary_links_source', 'secondary-menu');//as in cforge for d6
  variable_set('menu_main_links_source', 'main-menu');
}


/*
 * specifythe blocks in the cforge_* modules
 * have to check for the presence of each block in case it's module is not enabled
 */
function cforge_block_positions() {
  //this structure isn't perfect but assumes that there are no delta duplicates per region.
  $placements = array(
    'navigation' => array(
      'main-menu' => 'system',
      'visitors' => 'menu'
    ),
    'headerright' => array(
      'form' => 'search',
      'secondary-menu' => 'menu',
    ),
    'help' => array(
      'help' => 'system',
    ),
    'content' => array(
      'main' => 'system'
    ),
    'sidebar_first' => array(
      '1stparty' => 'mcapi_forms',
      'transactions-who_gave_what' => 'views',
      'events-block_upcoming' => 'views',
      'propositions_taxonomy_block' => 'offers_wants',
      'comments_recent-block' => 'views',
      'ow_offers-latest' => 'views',
      'ow_wants-latest' => 'views',
      'add_proposition' => 'offers_wants',
      'feed-1'=> 'aggregator',
      'new' => 'user',
    ),
    'sidebar_second' => array(
      'user-menu' => 'system',
      'masquerade_nominate' => 'masquerade_nominate',
      'setup' => 'menu',
      'waiting_on_uid' => 'mcapi_signatures',
      'trading_limits' => 'mcapi_limits',
      'login' => 'user',
      'random_photo' => 'cforge_gallery',
      'nitin' => 'cforge',
      'sel_promo' => 'cforge',
      'decouvrir' => 'cforge',
      'cf_training' => 'cforge'
    ),
    'contentbottom' =>array(
      'user_pending' => 'mcapi_signatures'
    ),
    'footer' => array(
      'trade_analysis-system' => 'views'
    ),
  );
  return $placements;
}


function cforge_frontend_default_nodes() {
  $lang = language_default('language') == 'en' ? LANGUAGE_NONE : language_default('language');
  cf_setup_rss();
  $nodes[] = array(
    'type' => 'page',
    'uid' => '1',
    'status' => '1',
    'comment' => '0',
    'sticky' => '0',
    'format' => 'full_html',
    'language' => $lang,
    'title' => t('Home'),
    'body' => array (
      'und' => array (
        0 => array (
          'value' => '<p>This is the default content on Community Forge\'s standard installation. It shows these four main pages to everyday secondary-links. To get a good idea of the member experience, start by logging in using one of the member ids, (taking note of the role in brackets) then you can:<ul>
<li>Start transactions with other users</li>
<li>add offers and wants to the directory</li>
<li>edit your other offers and wants</li>
<li>Change your profile information</li></ul>
Then you may log in as a committee members (they are listed on the left), and you will be able to<ul>
<li>edit announcements, FAQ, pages and categories</li>
<li>create Requests & acknowledgements</li>
<li>manage images</li></ul>
This software is ready for your community to use, and we are working round the clock and round the world to improve this service!',
          'format' => 'full_html',
        ),
      ),
      'fr' => array(
        0 => array(
          'value' => '<img src="/profiles/cforge/money-go-round.gif" align="right" style="margin:0 0 7em 1.5em" />
<h4 style="clear:none">Bienvenue</h4>
SEL veut dire «Système d&apos;Echange Local». C&apos;est une association dont les membres échangent entre eux des Services, des Savoirs et des biens. Les échanges sont mesurés dans une unité autre que l&apos;argent, les XXXX, dans le désir d&apos;évoluer vers plus de citoyenneté et de solidarité.

Pour certains, le SEL permet de suivre un cours, de donner un coup de main ou de "vendre" des objets dans un cadre convivial sans toucher à son porte-monnaie. Pour d&apos;autres, le SEL répond à un choix de vie, une envie de se positionner, de résister au système dominant.

<strong><a href="/share">Commencez par Partager></a></strong>',
         'format' => 'full_html',
        )
      )
    ),
     'path' => array (
      'alias' => 'home',
    ),
    'menu' => array (
      'link_title' => t('Home'),
      'description' => '',
      'menu_name' => 'visitors',
      'module' => 'menu',
      'weight' => '1',
      'enabled' => true,
    ),
  );

  $nodes[] = array(
    'type' => 'page',
    'uid' => '1',
    'status' => '1',
    'comment' => '0',
    'sticky' => '0',
    'format' => 'full_html',
    'language' => $lang,
    'title' => t('Share'),
    'body' => array (
      'und' => array (
        0 => array (
          'value' => '<strong>Join us and share </strong>
The local exchange systems gives you many opportunities to share.

<strong>Put your new members information here</strong>

Background, information, directions, times, locations.

<strong>Share collective tasks</strong>
Each association is only the sum of the actions of its members. That is why it is important to share the tasks related to the proper functioning thereof. The heading "Tasks" facilitates and encourages their distribution. Some tasks for the association may be paid in time or units. Solidarity contributions gain LETS for payment.


 <strong> <a href="/start"> Share your knowledge, your property - Exchange </a> </strong>',
          'format' => 'full_html',
        ),
      ),
      'fr' => array (
        0 => array (
          'value' => '<strong>Rejoignez-nous et partagez</strong>
Les Systèmes d&apos;Echange Locaux vous donnent de nombreuses occasions de partager.

<strong>Partager les premiers lundis soir du mois...</strong>
Commencez par partager un de nos repas canadiens un premier lundi du mois de 19h30 à 22h00.
A 20h30 deux membres vont vous présenter le SEL. Vous prendrez alors connaissance du fonctionnement du système, poserez vos questions et rencontrerez quelques membres. De nombreux échanges se créent lors de ces soirées.

C&apos;est à la Maison de quartier des Asters au 1er étage, 47 rue Schaub, à l’angle des rues Schaub et Hoffmann, 1202 Genève <a href="http:map.search.chgeneverue-schaub-47" target="_blank"> voir une carte></a>. Arrêt TPG "Servette" lignes 14, 16, 29, 3, 11 (le bus 8 est à 100m) <a href="http:www.tpg.chfrindex.php" target="_blank"> voir les horaires></a>

<strong>Partager des tâches collectives...</strong>
Chaque association n\'est que la somme des actions de ses membres. C\'est pourquoi il est important de partager les tâches liées au bon fonctionnement de celle-ci. La rubrique \"Contributions\" facilite et encourage leur répartition. Certaines tâches effectuées pour l&apos;association peuvent être rétribuées en grains de sel. Une Contribution Solidaire en grains de sel est perçue pour les rétribuer.

<strong><a href="start"> Partager votre Savoir, vos Biens - Échanger></a></strong>',
          'format' => 'full_html',
        ),
      ),
    ),
    'path' => array (
      'alias' => 'share',
    ),
    'menu' => array (
      'link_title' => t('Share'),
      'description' => '',
      'menu_name' => 'visitors',
      'module' => 'menu',
      'weight' => '2',
      'enabled' => true,
    ),
  );

  $nodes[] = array(
    'type' => 'page',
    'uid' => '1',
    'status' => '1',
    'comment' => '0',
    'sticky' => '0',
    'format' => 'full_html',
    'language' => $lang,
    'title' => t('Getting started'),
    'body' => array (
      'und' => array (
        0 => array (
          'value' => '<strong>How it works</strong>
<p> Offers and wants appear on our website or catalog. A member makes contact with another member to make an exchange. Members agree on its value, and make the exchange. Then, an e-member exchange takes on the site, the other confirms and finally the exchange is recognized.</p>
<p>Some tasks for the association may be paid in grain of salt. Solidarity contributions in local currency is seen to reward those tasks. </P>
<p>An annual fee in Swiss francs (CHF 30, CHF from July 20) is charged to cover the operating costs of the association (stamps, photocopies, ...)</p>
<p>A monthly meeting to exchange information is held. There is a general meeting every year. </p>
<p><strong> Start by <a href="/commit">Making a commitment</a> </strong> </p>',
          'format' => 'full_html',
        ),
      ),
      'fr' => array (
        0 => array (
          'value' => '<strong>Pour changer, échangeons!</strong>
<p>Nos membres se découvrent beaucoup plus « riches » grâce aux échanges qu\'ils effectuent, puisque la vraie richesse est constituée par les biens et services que les membres sont capables de créer ou d’offrir, et non par ce que le marché veut bien offrir.

<p><strong>Comment ça marche ?</strong>
Les Offres et Demandes paraissent sur notre site, ou sur catalogue. Un membre prend contact avec une autre membre pour faire un échange. Les membres s’accordent sur sa valeur en « grains de sel », et font l’échange. Ensuite, un-e des membres saisit l\'échange sur le site, l\'autre le confirme et voilà l\'échange est comptabilisé.

<p><strong>Les Offres</strong>
Envie de partager une passion?  Tant de personnes ont des talents, des compétences aucunement valorisés par le marché : grand-mères spécialistes en dentelles, mères de famille couturières ou cuisinières émérites, personnes handicapées avec talents artistiques, etc., la liste est longue ! <a href="/offers">voir les Offres></a>

<p><strong>Les Demandes</strong>
Grâce au système SEL, elles découvrent soudain des personnes qui ont justement besoin du service qu’elles sont capables d’offrir, et cela au moment opportun pour elles, qui ne correspond que rarement à un horaire de bureau ou d’usine. Ces personnes, souvent modestes, qui avaient coutume de se sous-estimer, s’en trouvent valorisées.  <a href="/wants">voir les Demandes></a>

<p><strong><a href="/commit">Échanger, c&apos;est S&apos;engager></a></strong>',
          'format' => 'full_html',
        ),
      ),
    ),
    'path' => array (
      'alias' => 'start',
    ),
    'menu' => array (
      'link_title' => t('Getting started'),
      'description' => '',
      'menu_name' => 'visitors',
      'module' => 'menu',
      'weight' => '3',
      'enabled' => true,
    ),
  );

  $nodes[] = array(
    'type' => 'page',
    'uid' => '1',
    'status' => '1',
    'comment' => '0',
    'sticky' => '0',
    'format' => 'full_html',
    'language' => $lang,
    'title' => t('Commit!'),
    'body' => array (
      'und' => array (
        0 => array (
          'value' => '<strong>Example: To become a member of LETS </strong>
<ol><li>Browse our site to better understand the system.</li>
<li>Contact members/attend orientation meeting, put information here.</li>
<li>Filling out registration form, put link to form here.</li>
<li>Fee to pay, how much, where/who/how to pay information here.</li>
<li>Details of how the process continues after payment.</li>
<li>Welcome to the LETS. To share and enrich you!</li></ol>',
          'format' => 'full_html',
        ),
      ),
      'fr' => array (
        0 => array (
          'value' => '<strong>Marche à suivre pour devenir membre du SEL</strong>
<ol><li>Parcourir notre site pour mieux comprendre les <a href="lets">SELs </a>et ce <a href="docs">SEL.</a></li>
<li>Participer à une présentation SEL un premier lundi du mois à 20h30 à la Maison de Quartier des Asters <a href="http:map.search.chgeneverue-schaub-47" target="_blank"> carte&gt;</a>
- Vous pouvez poser toutes vos questions après une présentation d&apos;environ 30 minutes sur le fonctionnement du SEL. La présentation commence à 20h30, mais vous êtes cordialement invité à partager le buffet canadien qui la précède, dès 19h30.</li>
<li>Une fois que vous avez assisté à cette présentation, vous pouvez devenir membre en remplissant :<br />
-le formulaire online <a href="user/register"><strong>d&apos;inscription ici ></a></strong></br />
-ou le formulaire d\'inscription et le bulletin de versement que vous avez reçu lors de la présentation</li>
<li>Payer la cotisation de xxxxx.- par xxx ou votre banque N° xxxxx (possibilité de paiement bientôt sur notre site internet)</li>
<li>Le temps de recevoir le paiement (env. 10 jours), et le secrétaire vous envoie votre numéro de membre et votre mot de passe, qui vous permettront d&apos;accéder à la partie du site réservée aux membres.</li>
<li>Bienvenue dans le SEL. Échangez et vous vous enrichissez.</li>
</ol>',
          'format' => 'full_html',
        ),
      ),
    ),
    'path' =>array (
      'alias' => 'commit',
    ),
    'menu' => array (
      'link_title' => 'Commit!',
      'description' => '',
      'menu_name' => 'visitors',
      'module' => 'menu',
      'weight' => '4',
      'enabled' => true,
    ),
  );

  $nodes[] = array(
    'type' => 'page',
    'uid' => '1',
    'status' => '1',
    'comment' => '0',
    'sticky' => '0',
    'format' => 'full_html',
    'language' => $lang,
    'title' => t('FAQ'),
    'body' => array (
      'und' => array (
        0 => array (
          'value' => '<h3> Glossary </h3>
<h5> What is a trade "to confirm" </h5>
It is an exchange awaiting confirmation of your partner.
<h5> What is a trade "recognized" </h5>
This is confirmed by an exchange, which has been debited / credited to respective accounts.
<h5> Vocabulary </h5>
The SALT avoid financial vocabulary because it does not confuse the two systems!
<li> instead of "check", use "voucher" or "trading units" </li>
<li> also avoid "selling" and "buy" it "gives", "supply", "exchange", "propose", "receives" </li>
<li> speak of "trade" rather than "transaction." </li>
<li> talk about "service" that you make to someone who needs it, "wealth" you make or receive. </li> </ul>
<h3> Your Account </h3>
<h5> How do I access my account </h5>
Click on your name (top right).
How do I change my email <h5> / password </h5>
Click on your name (top right)> Edit Account> Save Changes.
<h5> How do I change my address? </h5>
Click on your name (top right)> Edit profile> Save Changes.
How <h5> a list of My Exchange </h5>
Click on your name> My Exchanges
What is the <h5> Sale </h5>
"Balance" your current balance (excluding grains "TBC")
"Confirm" the grain that will be recognized after confirmation by your partner
"Total": total grains (positive) exchanged since the establishment of the site

<h3> Offers & Requests </h3>
<h5> supply / demand / Exchange appears in the "wrong" category (eg "Miscellaneous") </h5>
The software scans all the words in your ads and automatically in the class / category, the corresponding s-s using a system of synonyms.
It\'s not perfect, but has the advantage of being scalable because synonyms are updated regularly.
If your offer / request / exchange is not in the "good" category, you can try to modify it by changing or adding a few words that are probably in the targeted category. Otherwise, it does not matter, members will find in the research.
<h5> How to add a Supply / Demand </h5>
There are many ways, but here is the easiest:
click on your name> My Offers / Requests> Create a new offer (or request)
OR click on "Offers" in the top navigation> form appears in the lower left
click on "Applications" in the top navigation> form appears in the lower left.
<p>
<h3> Members </h3>
<h5> Contacting a member-e </h5>
Here is the easiest method:
click on "Members" in the top navigation> click on their name or membership number to go to their account> click on "contact".
<h5> How to send an email to an e-member? </h5>
Since the member\'s account, click "contact" in the display of their name, write and send (can send you a copy by checking the box next to "send" button). We chose this method to facilitate the contact and to avoid abuse emails.
<p>
<h3> Exchange </h3>
<h5> How to enter my exchange 2008 </h5>
The objective is to monitor and capture all your exchanges in 2008, without making too many duplicates.
<ol> <li> Download your Excel sheet exchange of SELduLac located in the <a href="docs"> Docs </a> site "Leaves of exchange members of ... 23/06/08 "</li>
<li> Print it for future reference when writing your discussions on the site. </li>
Gather your leaves <li> Exchange 2008 in pencil and cross out the exchange already recorded on the sheet Excel exchanges that you just printed. </li>
<li> Then in the "Members" of the site, click on your name, then click on "My Exchange". You have the list of trades already entered for the online site. Trade with a green light in the Status column are recorded and can not be changed. (Duplicates? See below). Trade with amber may be modified or deleted as appropriate to your entry. </Li>
<li> Once you have checked and deleted the exchange already entered on the Excel sheet and the site, you are ready to seize new trade. </li>
<li> Click "Enter Exchange" under your name at the top right, and within minutes you have entered all your trading! Please describe your interaction in 4 words minimum please for they are in the right category more. </Li> </ol>

Duplicates?
First try to "remove" the exchange in question. Otherwise, you can enter an exchange of "correction" (with the same person but the seeds are in the opposite direction). Put in the description: "correction of the exchange" X "" X "." That\'s it.

I took all the leaves exchange received before June 15 of the person who sent the leaves, but the exchange does not necessarily have been seized from the person who did not send his paper (for the same exchange). This can be difficult to grant the parties. To you to be flexible and understanding.

If you do not have copies of your exchange leaves sent to me since June 15, I refer you happy.

Courage, making this work, consider the accounting grains did it for years to 100 members. ;)
How to Enter <h5> Exchange </h5>
Click on the link "Enter Exchange" under your name at the top right.
You can also go to the account of a member and use the form on the left.
<h5> that captures the exchange site </h5>
Usually the person who will make the grain, or by arrangement. What is important is that you control your communications "to confirm" before entering a new exchange, to avoid duplicates. As your partner have not confirmed the exchange, you can edit or delete it.
<h5> What if the partner has not confirmed the exchange </h5>
First, to show a little patience. Some people check their emails once a week. Others may be on vacation or absent for long periods. After a while, you can restart the phone, or possibly by email.
<h5> How to register a trade with SELdulac? (Account 100) </h5>
In choosing the 100 as a partner in the exchange. An e-member committee will confirm the exchange later. Examples: the work of the festival committee and other tasks for the association.
<h5> Do I change already entered an exchange </h5>
Yes, if your partner in the exchange has not yet confirmed the exchange. You can even delete it.
<h5> What if the exchange is not accepted for reasons of balance (limit of + / -500 grains) </h5>
The principle is that each control the balance of the other before entering an important exchange. The treasurer may authorize grain exceeded for a maximum of 30 days.
<h5> What does the column "Status" </h5>
"Green" is a confirmed exchange
"Orange" is an exchange that awaits confirmation of your partner
"Red" means that the exchange entered into mediation
What if <h5> exchange duplicates? </H5>
If the exchange has not yet been confirmed, the person who took the exchange can remove it.
If the exchange is confirmed, you can enter an exchange of "correction" (with the same number of grains in the opposite direction with the same person). Put in the description: "correction of the exchange" X "" X "." So the two cancel each other exchanges.
<p>
<h3>Contributions </h3>
<h5> What is a contribution </h5>
The assumption that if each member contributes to the association, there is less need-tax (Contributions SELidaire), we display in the "Contributions" from the site helping hand to the operation of SEL. Do you volunteer for these tasks by contacting the person in the right column. You will be credited with a point "Contributions" for each task accomplished.
<h5> Procedure: Find the key to the House of Asters </h5>
Since the Neighborhood House is closed on Monday, you should look for the key on the Friday before the Monday meeting.
<h5> Procedure: Bring the key </h5>
<h5> Procedure: Note the Presence of a meal Monday </h5>
<ol> <li> Copy and paste the names of members of this page in a program like Word. </li>
<li> Print a copy of the list </li>
Make <li> members sign when they arrive at the Maison de Quartier </li>
<li> estimate the number of grains for each dish made and note the number next to the member\'s name (or ask a member of the e-estimate the value if he disagreed-as-y) </li>
<li> Replace the "Attendance Sheet" to a e-member committee for input. </li> </ol>
<p>
<h3> Docs </h3>
How to print a list <h5> </h5>
Click the "printer" that is located at bottom of pages. All pages have not this possibility. Tip: Look at the preview before printing, because the lists can be long. Remember to limit the consumption of paper using the site.
<h3> Site </h3>
<h5> I have no access to information </h5>
Only users who have entered their member ID and password can view the ad details and addresses of members.
<h5> Why did a new site </h5>
With the increase in the number of members, the seizure of trade and the division of labor became necessary.
The site also aims to:
<li> promote exchange </li>
<li> strengthen ties between members </li>
<li> increase transparency </li>
<li> lower the solidarity contribution (tax). </li> </ul>
<h5> Here is what is planned for the following versions of the site </h5>
<b> Version 1.1 (ct 2009) </b>
<em> My Account </em>
<li> work layout </li>
<li> streamlining information </li>
<li> internet payment of contributions </li> </ul>
<i> Members </i>
<li> more elegant way to search for members </li> </ul>
<i> Exchange </i>
<li> search by categories like Offers and Requests </li>
<li> separate "property" of "& Knowledge Services\' </li> </ul>
<i> Offers / Requests </i>
-View photos for offers of goods
<i> "Contributions" </i>
<li> exchange for a token </li>
Ads <li> to the attention of other members </li>
<li> Tasks to do to SELduLac "Contributions" (currently running) </li>
<li> Listings for these tasks (in progress) </li>
Thanks <li> after performing these tasks (currently operating) </li> </ul>

<h5> Who created the basic tool to manage LETS? </h5>
Hello, we are the creators of this management tool for LETS.
Matthew Slater, a computer
Tim Anderson, a member of SALT.
Our first "client" was to SELduLac Geneva. from our tool, we imported data SELduLac, suitable interface, consisting of committee members and we follow up and maintenance for one year. This is for the exchange of CHF 1\'500 .-.
We provide our expertise of other LETS to build the same trading platform. If interested, please contact http://communityforge.net',
          'format' => 'full_html',
        ),
      ),
      'fr' => array (
        0 => array (
          'value' => '<h3>Lexique</h3>
<h5>Qu&apos;est-ce qu&apos;un échange "à confirmer"?</h5>
C&apos;est un échange en attente de confirmation de votre partenaire.
<h5>Qu&apos;est-ce qu&apos;un échange "comptabilisé"?</h5>
C&apos;est un échange confirmé, qui a été débité/crédité dans les comptes respectifs.
<h5>C&apos;est quoi les Soldes?</h5>
"Solde": votre solde actuel (sans les unités"en attente")
"en attente": les unités qui seront comptabilisés après la confirmation par votre partenaire
"Cumul": le total des unités (en positif) échangés depuis la mise en place du site, la richesse que vous avez crée.

<h5>Vocabulaire SELs</h5>
Les SELS évitent le vocabulaire financier car il ne faut pas confondre les deux systèmes!
<ul><li>à la place de « chèque », utilisez « bon d’échange » ou « unités d’échange »</li>
<li>évitez aussi « vendre » et « acheter » : on « donne », « offre », « échange », « propose », « reçoit »</li>
<li>parlez d’« échange » plutôt que de « transaction ».</li>
<li>parlez de « service » que vous rendez à quelqu’un qui en a besoin, de « richesse » que vous apportez ou recevez.</li></ul>

<h3>Votre Compte</h3>
<h5>Comment accéder à mon compte?</h5>
Cliquez sur votre nom (en haut à droite).
<h5>Comment changer mon email / mot de passe?</h5>
Cliquez sur votre nom (en haut à droite) > Modifier compte > Enregistrer les modifications.
<h5>Comment changer mon adresse?</h5>
Cliquez sur votre nom (en haut à droite) > Modifier profil > Enregistrer les modifications.
<h5>Comment consulter la liste de Mes Echanges?</h5>
Cliquez sur votre nom > Echanges

<h3>Offres & Demandes</h3>
<h5>L&apos;Offre/Demande/Échange apparaît dans la "mauvaise" catégorie (p.ex. "Divers")</h5>
Le logiciel analyse toutes les mots dans vos annonces et les classe automatiquement dans la/les catégorie-s correspondante-s en utilisant un système de synonymes.
Ce n&apos;est pas parfait, mais a l&apos;avantage d&apos;être évolutif, car les synonymes sont mis à jour régulièrement.
Si votre Offre/Demande/Échange n&apos;est pas dans la "bonne" catégorie, vous pouvez essayer de la modifier en changeant ou ajoutant quelques mots qui sont probablement dans la catégorie ciblée. Sinon, ce n&apos;est pas grave, les adhérents vont la trouver par la recherche.
<h5>Comment ajouter une Offre/Demande?</h5>
Il y a plusieurs façons, mais voici la plus facile:
cliquez sur votre nom > Offres/Demandes > Ajouter une Offre (ou Demande)
OU cliquez sur "Offres" dans la navigation du haut > un formulaire apparaît en bas à gauche
cliquez sur "Demandes" dans la navigation du haut > un formulaire apparaît en bas à gauche.

<h5>Lorsque l&apos;on ajoute une offre, quelle est la différence entre Bien et Prêt?</h5>
Un Bien est à échanger contre des unités locals. Le bien change de mains.
Un Prêt est un bien ou un service qu&apos;on prêt, et qui donc ne change pas de main.

<h3>Adhérents</h3>
<h5>Comment contacter un adhérent ?</h5>
Voici la méthode la plus facile:
cliquez sur "Adhérents" dans la navigation du haut > cliquez sur leur nom ou n° d&apos;adhérent pour aller sur leur compte > cliquez sur l&apos;onglet "contact".
<h5>Comment envoyer un email à un adhérent ?</h5>
Depuis le compte du l&apos;adhérent, cliquez sur "contact" sous l&apos;affichage de son nom, rédigez et envoyez (vous pouvez vous envoyer une copie en cochant la case à coté du bouton "envoyer"). Nous avons choisi cette méthode pour faciliter la prise de contact ainsi que d&apos;éviter l&apos;abus des emails.

<h3>Échanges</h3>
<h5>Comment Ajouter un Échange?</h5>
Cliquez sur le lien "Ajouter un Échange", sous votre nom en haut à droite.
Vous avez également la possibilité d&apos;aller sur le compte d&apos;un membre et utiliser le formulaire sur la gauche.
<h5>Qui saisit l&apos;échange sur le site?</h5>
Généralement la personne qui va verser des unités, ou selon accord. Ce qui est important est que vous contrôliez vos échanges "à confirmer" avant de faire la saisie d&apos;un nouvel échange, pour éviter des doublons. Tant que votre partenaire n&apos;as pas confirmé l&apos;échange, vous pouvez le modifier ou le supprimer.
<h5>Que faire si le partenaire n&apos;a pas confirmé l&apos;échange?</h5>
D&apos;abord, faire preuve d&apos;un peu de patience. Certaines personnes ne consultent leurs emails qu&apos;une fois par semaine. D&apos;autres peuvent être en vacances ou absents pendant de longues périodes. Après un certain temps, vous pouvez les relancer par téléphone, ou éventuellement par email.
<h5>Comment enregistrer un échange avec notre SEL ? (Compte central 1)</h5>
En choisissant le Compte 1/Notre SEL comme partenaire dans l&apos;échange. Un-e membre du comité va confirmer l&apos;échange par la suite. Des exemples: des travaux du comité des fêtes et d&apos;autres tâches pour l&apos;association.
<h5>Est-ce que je peux modifier un échange déjà saisi?</h5>
Oui, si votre partenaire dans l&apos;échange n&apos;a pas encore confirmé l&apos;échange. Vous pouvez même le supprimer.
<h5>Que faire si l&apos;échange n&apos;est pas accepté pour des raisons de solde limite ?</h5>
Le principe est que chacun contrôle le solde de l&apos;autre avant d&apos;entrer dans un échange important. Le trésorier en unités peut autoriser des dépassements pour une période maximale de 30 jours.
<h5>Que faire en cas d&apos;échanges doublons ? </h5>
Si l&apos;échange n&apos;a pas encore été confirmé, la personne qui a saisi l&apos;échange peut le supprimer.
Si l&apos;échange est confirmé, vous pouvez saisir un échange de "correction" (avec le même nombre de unités dans le sens inverse avec la même personne). Mettez dans la description: "correction de l&apos;échange "X" le "X"". Donc, les deux échanges s&apos;annulent.

<h3>Contributions</h3>
<h5>Qu&apos;est-ce-qu&apos;une Contribution ?</h5>
Partant du principe que si chaque membre contribue à son association, il-y-a moins besoin d&apos;impôts (Contributions SELidaire), nous affichons dans la partie "Contributions" du site les petits coups de mains nécessaires au fonctionnement du SEL. Portez-vous volontaire pour ces tâches en contactant la personne dans la colonne de droite. Vous serez crédité d&apos;un point "Contributions" pour chaque tâche accomplie.

<h3>Documents</h3>
<h5>Comment imprimer une liste?</h5>
Cliquez sur l&apos;icône "imprimante" qui se trouve en haut des pages. Toutes les pages n&apos;ont pas cette possibilité. Conseil: Regardez l&apos;aperçu avant d&apos;imprimer, car les listes peuvent être longues. Pensez à limiter la consommation de papier en utilisant le site.
<h3>Site</h3>
<h5>Je n&apos;ai pas accès aux informations</h5>
Seuls les membres ayant saisi leur numéro de membre et leur mot de passe peuvent voir les détails des annonces et les adresses des membres.
<h5>Pourquoi avoir fait un nouveau site?</h5>
Avec l&apos;augmentation importante du nombre des membres, la saisie des échanges et la répartition des tâches est devenue nécessaire.
Le site vise également à :
<ul><li>favoriser les échanges</li>
<li>renforcer les liens entre les membres</li>
<li>augmenter la transparence</li>
<li>baisser la contribution solidaire (impôt).</li></ul>

<h3>FAQ</h3>
<h5>D&apos;autres questions?</h5>
Contactez la personne qui s&apos;occupe

<h5>Qui a créé l&apos;outil de base pour gérer les SELs?</h5>
Bonjour, nous sommes les créateurs de cet outil de gestion pour les SELs.
<a href="mailto:matslats@gmail.com">Matthew Slater, un informaticien</a>
<a href="mailto:timcarouge@gmail.com"> Tim Anderson, un membre d&apos;un SEL.</a>
Notre premier installation était le <a href="www.seldulac.ch"> SELduLac </a> à Genève. Nous mettons à disposition des autres SELs nos compétences pour mettre en place cette même plateforme d&apos;échanges.',
          'format' => 'full_html',
        ),
      ),
    ),
    'path' => array (
      'alias' => 'faq',
    ),
    'menu' => array (
      'link_title' => t('FAQ'),
      'description' => '',
      'menu_name' => 'secondary-menu',
      'module' => 'menu',
      'weight' => '2',
      'enabled' => true,
    ),
  );

  $nodes[] = array(
    'type' => 'page',
    'uid' => '1',
    'status' => '1',
    'comment' => '0',
    'sticky' => '0',
    'format' => 'full_html',
    'language' => $lang,
    'title' => t('About LETS'),
    'body' => array(
      'und' => array(
         0 => array(
           'value' => '<a href="http://www.lets-linkup.com/400-RestOfEurope.htm"> LETS-linkup.com </a> - the site offers a list of LETS present in each country, including Switzerland. Incomplete but useful.
<a href="http://www.selidaire.org/"> Selidaire </a> - general information on the operation of the LETS, forums, ...
<a href="http://transversel.apinc.org/"> Transversel </a> - information about LETS. To date, most living in French.
<a href="http://www.imaginer.ch/eba/textes/sel.html"> Imagine </a> - historical overview of the various systems of barter (including LETS) in Geneva.

<strong> LETS in Switzerland: </strong>
<a href="http://www.sel-suisse.ch"> SELs Switzerland </a> - local exchange systems of La Chaux-de-Fonds, the Val-de-Ruz (vaudruzien salt) and Littoral Neuchâtel (salt of the banks) are presented.
<a href="http://www.sel-lausanne.net"> SEL Lausanne </a> - visit our dear neighbors Lausanne.
<a href="http://www.tauschnetz.ch"> Tauschnetz </a> - Most of the LETS in Switzerland.

Why <strong> enter a SEL? <a href=pourquoisel"> click here> </a> </strong>

<strong> Questions> Answers on Salt </strong>
<em> Exchange Unit </em>
-The unit of exchange, grain, measures the interaction between members.

But <em> barter </em>
-Not at all. In barter, two people share the same time two things that have roughly the same value. In the SEL, the grains can transfer to different people and different times, services, knowledge or goods that have different values.

<em> grain of salt and the Franks, it is the same </em>
No, because, to spend the Franks, one must first possess. Whereas with a zero account I can share right away.
No, because the grains are not convertible into Franks, the Franks or beans.
No, because it is a local currency without the use outside the association.
No, because the local currency is not funded, do not bear interest and is not speculative.

<em> Who sets the value </em>
-Members are free to set the value they want according to the pleasure, the difficulty or hardship represented by a task or in their experience. The case of objects is more difficult and it is more likely to assess the amount relating to the Franc.

<em> But it\'s too booked! </em>
-Nothing to prevent those who used to make a free to do so, one time or another, or in part.

-Experience shows that the salt causes the game and generates the gift.

<em> It does not matter to have an account in negative SEL </em>
-Not at all. Each begins with an account to zero. If I paid 400 grains for the guitar by Denis, his account becomes positive but mine, negative, ascend gradually as j\'écoulerai my banana jam the pot to 10 grains. Thus, in an SEL, there are necessarily members who have a negative account, and others a positive account. The sum of all amounts for all accounts is zero.

<em> can stay indefinitely in the negative </em>
-The limits are between -500 and 500 grains. If a participant reaches this limit, it reminds him of the rules.

<em> What prevents me from leaving with a negative account </em>
-A flow is a commitment to making the group of goods, services, or knowledge. However, in the SEL, between people who meet and get to know the confidence born at the same time as the moral commitment. In practice, that\'s enough for this kind of irresponsible behavior is very rare.

<em> What guarantee is there on the quality of goods or services offered? </em>
-None. This is for members to discuss whether one has the skill level desired by the other or what happens if the object fails the next day to reach agreement before the exchange.',
          'format' => 'full_html',
        ),
      ),
      'fr' => array(
        0 => array(
          'value' => '<a href="http:www.lets-linkup.com400-RestOfEurope.htm">LETS-linkup.com</a> - le site propose la liste des SELs présents dans chaque pays dont la Suisse. Incomplet mais utile.
<a href="http:www.selidaire.org">Selidaire</a> - informations générales sur le fonctionnement des SELs, forums, ...
<a href="http:transversel.apinc.org">Transversel</a> - information à propos des SELs. A jour, le plus vivant en français.
<a href="http:www.imaginer.chebatextessel.html">Imaginer</a> - aperçu historique des divers systèmes de troc (dont les SELs) présents à Genève.

<strong>SELs en Suisse :</strong>
<a href="http:www.sel-suisse.ch">SELs Suisse</a> - systèmes d\'échange locaux de la Chaux-de-Fonds, du Val-de-Ruz (sel vaudruzien) et du Littoral neuchâtelois (sel des rives) se présentent.
<a href="http:www.sel-lausanne.net">SEL Lausanne</a> - visitez nos chers voisins Lausannois.
<a href="http:www.tauschnetz.ch"> Tauschnetz</a> - la plupart des SELs de Suisse.

<strong>Pourquoi entrer dans un SEL ? <a href=pourquoisel">cliquez ici ></a><strong>

<strong>Questions > Réponses sur les Sels</strong>
<em>Unité d&apos;échange</em>
-L’unité d’échange, le grain, permet de mesurer les échanges entre adhérents.

<em>Mais c’est du troc !</em>
-Pas du tout. Dans le troc, deux personnes échangent au même moment deux choses qui ont à peu près la même valeur. Dans le SEL, les grains permettent de transférer, à différentes personnes et différents moments, des services, des savoirs ou des biens qui ont des valeurs différentes.

<em>Les grains de SEL et les Francs, c’est pareil ?</em>
-Non, car, pour dépenser des Francs, il faut d’abord en posséder. Alors qu’avec un compte à zéro je peux échanger tout de suite.
-Non, parce que les grains ne sont pas convertibles en Francs, ni les Francs en grains.
-Non, car il s’agit d’une monnaie locale sans utilisation en dehors de l’association.
-Non, car cette monnaie locale n’est pas capitalisable, ne produit pas d’intérêts et n’est donc pas spéculative.

<em>Qui fixe la valeur ?</em>
-Les adhérents sont libres de fixer la valeur qu’ils veulent suivant le plaisir, la difficulté ou la pénibilité représentée par une tâche ou selon leur expérience. Le cas des objets est plus épineux et on aura davantage tendance à en évaluer le montant en se rapportant au Franc.

<em>Mais, c&apos;est trop comptabilisé!</em>
-Rien n&apos;empêche ceux qui avaient l’habitude de rendre un service gratuit de le faire, une fois ou l’autre, ou en partie.

-L’expérience prouve que le SEL provoque la rencontre et génère le don.

<em>Ce n&apos;est pas grave d’avoir un compte SEL en négatif ?</em>
-Pas du tout. Chacun commence avec un compte à zéro. Si j’ai versé 400 grains pour la guitare de Denis, son compte devient positif mais le mien, négatif, remontera au fur et à mesure que j’écoulerai mes confitures de banane à 10 grains le pot. Ainsi, dans un SEL, il y a nécessairement des adhérents qui ont un compte négatif, et d’autres un compte positif. La somme de tous les montants de tous les comptes est égale à zéro.

<em>On peut rester dans le négatif indéfiniment ?<em>
-Les limites sont entre -500 et +500 grains. Si un adhérent atteint cette limite, on lui rappelle les règles.

<em>Qu’est-ce qui m’empêche de partir avec un compte négatif ?</em>
-Un débit constitue un engagement à rendre au groupe des biens, des services, ou des savoirs. Or, dans le SEL, entre les personnes qui se rencontrent et font connaissance naît la confiance en même temps que l’engagement moral. En pratique, ça suffit pour que ce genre de comportement irresponsable soit très rare.

<em>Quelle garantie a-t-on sur la qualité des biens ou des services proposés ?</em>
-Aucune. C’est aux adhérents de discuter, pour savoir si l’un a le niveau de qualification que souhaite l’autre ou ce qui se passe si l’objet tombe en panne le lendemain, afin de se mettre d’accord avant l’échange. Pas de solution toute faite, ça passe par la discussion et la confiance. En cas de problème, il-y-a un-e

<em>Mais c’est du travail au noir ? </em>
-Non, il s’agit d’une entraide entre adhérents, pour des coups de main « ponctuels, non répétitifs et de courte durée ».
-La pratique montre qu’énormément d’échan­ges qui n’auraient pas pu voir le jour dans le cadre classique du marché se font au sein des SEL. D’ailleurs, même si Marie demande à Bernard de l’aider à retapisser son appartement parce que ses fins de mois sont difficiles, c’est un autre artisan ou commerçant qui bénéficiera de l’argent économisé par Marie. Plus il y a de convivialité et de rencontres, plus il y a d’échanges, plus se créent des liens de proximité, entraînant de nouveaux échanges.

<em>Mais moi je n’ai rien à proposer !</em>
-C’est ce que dit tout le monde ! Ce que vous pouvez proposer ne vous paraît pas intéressant, s’il n’est pas compté comme travail salarié en Francs. Pourtant chacun possède une richesse à donner aux autres : faire de la pâtisserie, du bricolage, proposer les noix de son jardin, raconter des histoires aux enfants, écouter celui qui a un gros coup de cafard. Tout le monde, enfants, retraités, chômeurs, a quelque chose à proposer. Il suffit d’être à l’écoute de ses différences.
-C’est fou ce qu’on peut découvrir alors comme nouveaux échanges quand on est à l’écoute de ses différences.',
          'format' => 'full_html',
        )
      )
    ),
     'path' => array (
      'alias' => 'lets',
    ),
    'menu' => array (
      'link_title' => t('About LETS'),
      'description' => '',
      'menu_name' => 'secondary-menu',
      'module' => 'menu',
      'weight' => '3',
      'enabled' => true,
    )
  );

  //special node is scraped from cforge site so it's at least up to date when the site is created

  $available_langs = array('fr', 'en');//prefixes available on cforge.net for step-by-step page
  if ($lang == LANGUAGE_NONE || !in_array($lang, $available_langs)) $lang = 'en';

  ini_set('allow_url_fopen', TRUE);
  $url = 'http://communityforge.net/'.$lang.'/step-by-step';
  $page = file_get_contents($url);
  if($page) {
    $page = substr($page, strpos($page, '<cfscrape>') + strlen('<cfscrape>'));
    $page = substr($page, 0, strpos($page, '</cfscrape>'));
    //this is nasty, but for the javascript fieldsets to work, we have to remove a linebreak which was inserted by the scraping
    $page = str_replace("/legend>\n", "/legend>", $page);

    $nodes[] = array(
      'type' => 'story',
      'uid' => '1',
      'status' => '1',
      'comment' => '0',
      'sticky' => '0',
      'format' => 'full_html',
      'language' => LANGUAGE_NONE,
      'title' => t('Step by step guide to setting up your site'),
      'body' => array (
        LANGUAGE_NONE => array (
          0 => array (
            'value' => $page,
            'format' => 'full_html',
            'summary' => substr($page, 0, strpos($page, '</p>'))
          )
        )
      ),
      'path' => array (
        'alias' => 'step-by-step',
      ),
    );
  }
  else {
    drupal_set_message(t('was unable to to retrieve: @url', array('@url' => $url)));
  }
  return $nodes;
}
