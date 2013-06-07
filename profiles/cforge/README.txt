Architecture.

In hope that this installation profile may be of use to others, I write here a description of the architecture of this profile. My hope is always to make discreet, reusable components that other developers can modify or build on. The architecture is deliberately simple because my first interest is module development more than site design. Also LETS groups are not very ambitious with technology. A LETS is a grass roots community club which exists for its members to exchange things without money. Typically it provides an accounting system, a directory of offers and wants and a newsletter. Its a great social technology for building relationships and strengthening community but does not concern itself with the full spectrum of community activities. Each one is managed by a usually conservative committee. Most groups have between 50 and 150 members.

The main installation profile aims to provide some basic services and the included modules are optional / replacable features which depend on certain elements of the profile. One theme is included, a heavily modified version of Sky (which doesn't use the standard regions, but should).

The cforge.profile defines many things common to all use cases (LETS). They are realworld membership groups with a management structure and a reluctance to do too much online, A full list follows, and then a brief description of the 'features'.

Settings
Two node-types are defined, page and story, as in the 'standard' profile.
Two new filters are defined for use with the ckeditor.
5 roles are defined - trader, committee, accountant, local admin, and system. The last one is for non-member accounts because the mutual credit module uses user IDs for accounting.
7 user profile fields.
Some presets are provided for the contact module for ease of setup
Some default pages are provided for ease of setup. Also a block with a video in the appropriate language.
The first user, called local admin, is created as part of the setup
A setup menu is created with links to config forms for use by the local admin. Many of these forms are only partially visible to prevent the local admin making bad decisions.
the backup and migrate module allows only downloads and restorations of the whole database dump
Two permissions are provided corresponding to the roles, local admin and committee.

Builtin features
Realnames hack - rather than reslying on the realnames module, the firstname and secondname (required fields) comprise the username. In community there is no expectation of anonymity. The drupal autocomplete function is overridden to support this searching on username, email, or uid.
Broadcast feature allows nodes to be 'broadcast' once only, to all active users. This is for newsletters and
Password strength checker is disabled since users found it annoying.
Login_redirect is implemented in one line of code to take user to a view of recent articles.
plus some modules
Advanced help has been written
Captcha is configured for account creation
Role expire is configured because these groups have an annual membership fee.
Community Tasks module is included as is.

Cforge config modules
I call these features because most of these modules are just configuring other modules and include little logic. Nonetheless I hope they can save a lot of time. They mostly just create node-types, menu links for the user menu and setup menu, they provide views and create and place blocks in known regions.
cforge_currencies configures the Community Accounting package (mutual_credit)
cforge_docs allows committee to upload and categorise attached files for public or private.
cforge_events provides an 'event' nodetype with datefield and calendar views.
cforge_gallery allows images to be uploaded and categorised
cforge_launch provides import tools and emails everyone with a new password before uninstalling itself
cforge_offline provides a user profile flag for users to register themselves as non-internet users. Committee can then print from a special printable view and snail mail it.
cforge_yell configures the offers_wants module

=== THANKS ===
This installation profile and some the modules that comprise it are the fruits of 3 1/2 years concentrated effort. Community Forge would like to acknowledge the participation of many individual who have contributed materially or otherwise.
First of all the users, for tolerating and reporting issues. Users are the best testers, and the only testers in absence of other resources. Most of users comprise a several SELs in French speaking Europe, especially SEL du Lac in Geneva and the SELs in Wallonia, Belgium.
In Belgium, Bernard Simon, Marie Ullens and Daninelle Lagasse.
Art Brock and Timebanks USA, early adoptors of the Community Accounting module
Objectif Gaia retreat centre outside Geneva.
Mary Fee, for her excellent work over the years gathering and understanding requirements
Danièle Warynski, behind the scenes in Geneva
Route des SEL who brought 3000 user to the Community Accounting early on
Olivier Hetzl, Auroville, for moral and financial support
Annette Loudon for her encouragement


== SCRIPTS ===
//user pictures did not become managed files during upgrade
foreach ($filenames as $pic) {
  $uid = substr(substr($pic, 8), 0, -4);
  $uri = 'public://pictures/'.$pic;
  if ($fid = db_query("SELECT fid FROM {file_managed} WHERE uri = :uri", array(':uri' => $uri))->fetchfield()) {debug($fid, 'already');continue; }
  $fields = array(
    'uid' => $uid,
    'uri' => $uri,
    'filename' => $pic,
    'filemime' => 'image/jpeg',
    'status' => 1,
    'timestamp' => REQUEST_TIME
  );
  $fid = db_insert('file_managed')->fields($fields)->execute();
  db_update('users')->fields(array('picture' => $fid))->condition('uid', $uid)->execute();
}