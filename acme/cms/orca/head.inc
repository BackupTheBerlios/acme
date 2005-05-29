<?php /* ***** Orca Forum - Head File ************************* */

/* ***************************************************************
* Orca Forum v4.0b
*  A simple threaded forum for a small community
* Copyright (C) 2004 GreyWyvern
*
* This program may be distributed under the terms of the GPL
*   - http://www.gnu.org/licenses/gpl.txt
* 
* See the readme.txt file for installation instructions.
*************************************************************** */

/* ***** SQL Information ************************************** */
$hostname = $conf["dbhost"];
$username = $conf["dbuser"];
$password = $conf["dbpass"];
$database = $conf["dbname"];
$sqlType = "MySQL";
$tableName = "orcaforum";

/* ***** Other User Variables ********************************* */
$forumAdmin = "admin";
$forumPassword = "password";

$dateFormat = "M j, Y  g:i a";
$timeZone = "EST";
$timeZoneOffset = "-5";
$adjustForDaylightSavings = true;

$emailMung = "REMOVE@THIS";
$replyEmail = "your@email.com";
$emailFrom = "Forum";

$wrapWordsAt = 40;
$threadsPerPage = 15;
$threadCollapse = false;
$avatarPixels = 80;
$maxThreads = 105;


/* ***** Database functions **************************************
* Adaptation to PostgreSQL by Dragoniade
*************************************************************** */
function db_connect($hostname, $username, $password, $database, $tableName) {
  global $sqlType;

  if ($sqlType == "MySQL") {
    $db = mysql_connect($hostname, $username, $password) or die("Could not connect to the MySQL server!");
    mysql_select_db($database,$db) or die("Could not connect to the database!");
    mysql_query("CREATE TABLE IF NOT EXISTS `$tableName` (
      `pid` int(11) NOT NULL auto_increment,
      `ip` text,
      `author` text,
      `subject` text,
      `message` longtext,
      `image` text,
      `date` int(11) default NULL,
      `views` int(11) default NULL,
      `email` text,
      `notify` text,
      `parent` int(11) default NULL,
      PRIMARY KEY  (`pid`)
    ) TYPE=MyISAM;") or die("Could not create forum table!");
  } else {
    $str_connect = (($hostname != "") ? "host=$hostname " : "")."dbname=$database user=$username password=$password";
    $db = pg_connect($str_connect) or die("Could not connect to the postgreSQL server!");
    $createTable = @pg_query("CREATE TABLE `$tableName` (
      pid int NOT NULL auto_increment,
      ip text,
      author text,
      subject text,
      message text,
      image text,
      date int,
      views int,
      email text,
      notify text,
      parent int,
      PRIMARY KEY  (`pid`)
    );");
  } return $db;
}

function db_query($query) {
  return ($GLOBALS['sqlType'] == "MySQL") ? mysql_query($query) : @pg_query($query);
}
function db_numrows($result) {
  return ($GLOBALS['sqlType'] == "MySQL") ? mysql_numrows($result) : @pg_numrows($result);
}
function db_result($result, $row, $field) {
  return ($GLOBALS['sqlType'] == "MySQL") ? mysql_result($result, $row, $field) : @pg_fetch_result($result, $row, $field);
}

function get_all() {
  return db_query("SELECT * FROM `{$GLOBALS['tableName']}` ORDER BY `pid`;");
}
function get_row($id) {
  return db_query("SELECT * FROM `{$GLOBALS['tableName']}` WHERE `pid`='$id';");
}
function get_kids($id) {
  return db_query("SELECT * FROM `{$GLOBALS['tableName']}` WHERE `parent`='$id' ORDER BY `pid` DESC;");
}

$db = db_connect($hostname, $username, $password, $database, $tableName);


/* ***** Forum Functions ************************************** */
function listChildren($msg) {
  global $lData, $fData, $dateFormat;

  $thisMsg = get_row($msg); ?>

  <div class="of_post">
    <a class="of_post_subject" href="<?php echo $_SERVER['PHP_SELF']."?msg=$msg"; ?>"><?php echo to_scrn(db_result($thisMsg, 0, "subject")); ?></a>
    <span class="of_post_author" title="<?php echo db_result($thisMsg, 0, "ip"); ?>"><?php echo to_scrn(db_result($thisMsg, 0, "author")); ?></span>
    <span class="of_post_date<?php if (db_result($thisMsg, 0, "date") > time() - $_COOKIE['of_mark']) echo "_new"; ?>"><?php echo gmdate($dateFormat, db_result($thisMsg, 0, "date") + $fData['offset']); ?></span>
    <?php $nextLevel = get_kids($msg);
    if (db_numrows($nextLevel)) {
      for ($x = 0; $x < db_numrows($nextLevel); $x++) {
        listChildren(db_result($nextLevel, $x, "pid"));
      }
    } ?>
  </div>
  <?php $lData['replies']++;
}

function to_scrn($input) {
  return htmlspecialchars(trim($input));
}

function to_dbse($input) {
  return addslashes(trim($input));
}

function parseImage($input) {
  global $fData, $lang, $avatarPixels;

  if (!$input || $input == "http://") return NULL;
  if (preg_match("/http:\/\/\w\S*\.(png|gif|jpg|jpeg|bmp|php|asp)/i", $input)) {
    if ($dims = getimagesize_remote($input)) {
      if ($dims[0] <= $avatarPixels && $dims[1] <= $avatarPixels) {
        return $input;
      } else if ($_POST['command'] == "Preview") $fData['error'] = $lang['avatar1'];
    } else if ($_POST['command'] == "Preview") $fData['error'] = $lang['avatar2'];
  } else if ($_POST['command'] == "Preview") $fData['error'] = $lang['avatar3'];
  return NULL;
}

function getimagesize_remote($image_url) {
  $handle = @fopen($image_url, "rb");
  $contents = "";
  if ($handle) {
    while ($data = fread($handle, 8192)) $contents .= $data;
    fclose($handle);

    $im = imagecreatefromstring($contents);
    if ($im) {
      $gis[0] = imagesx($im);
      $gis[1] = imagesy($im);
      $gis[3] = "width=\"{$gis[0]}\" height=\"{$gis[1]}\"";
      imagedestroy($im);
      return $gis;
    }
  }
  return false;
}

function parseEmail($input) {
  global $fData, $emailMung, $lang;

  if (!$input) return NULL;
  if (preg_match("/^([a-z0-9\-_.]+?)@([\w\-]+\.([\w\-\.]+\.)?[\w]+)$/i", $input)) {
    return str_replace("@", $emailMung, $input);
  } else if ($_POST['command'] == "Preview") $fData['error'] = $lang['emaila'];
  return NULL;
}

function parseMessage($input) {
  global $wrapWordsAt, $lang;

  $input = to_scrn($input);

  do {
    $length = strlen($input);
    $input = preg_replace("/\[quote=?(.*?)\]\n?(.*?(?!\[quote.*?\]))\[\/quote\]\n?/is", "<blockquote><h5>$1 {$lang['parse2']}:</h5><div>$2</div></blockquote>", $input);
  } while ($length != strlen($input));
  $tag = preg_quote("<blockquote><h5> {$lang['parse2']}:</h5>", "/");
  $input = preg_replace("/".$tag."/i", "<blockquote><h5>".$lang['parse1'].":</h5>", $input);

  do {
    $length = strlen($input);
    $input = preg_replace("/\[b\](.*?(?!\[b\]))\[\/b\]/is", "<strong>$1</strong>", $input);
  } while ($length != strlen($input));

  do {
    $length = strlen($input);
    $input = preg_replace("/\[i\](.*?(?!\[i\]))\[\/i\]/is", "<em>$1</em>", $input);
  } while ($length != strlen($input));

  do {
    $length = strlen($input);
    $input = preg_replace("/\[link=(http:\/\/.*?)\](.*?(?!\[link=http:\/\/.*?\]))\[\/link\]/is", "<a href=\"$1\">$2</a>", $input);
  } while ($length != strlen($input));

  do {
    $length = strlen($input);
    $input = preg_replace("/\[img=(http:\/\/.*?)\]/is", "<img src=\"$1\" alt=\"\">", $input);
  } while ($length != strlen($input));

  do {
    $length = strlen($input);
    $input = preg_replace("/\[code\]\n?(.*?(?!\[code\]))\[\/code\]\n?/is", "<code>$1</code>", $input);
  } while ($length != strlen($input));

  $input = preg_replace("/\[\/?(quote=?.*?|b|i|link=?.*?|img=?.*?|code)\]/is", "", $input);

  $input = wordwrap2($input, $wrapWordsAt, " ");

  if (preg_match_all("/<code>.*?<\/code>/s", $input, $pre1)) {
    for ($x = 0; $x < count($pre1[0]); $x++) {
      $pre2[$x] = str_replace("  ", "&nbsp;&nbsp;", $pre1[0][$x]);
      $pre2[$x] = preg_replace("/(\n|>) /", "$1&nbsp;", $pre2[$x]);
      $pre1[0][$x] = "/".preg_quote($pre1[0][$x], "/")."/";
    }
    $input = preg_replace($pre1[0], $pre2, $input);
  }

  return $input;
}

function wordwrap2($str, $cols, $cut) {
  $tag = 0; $ent = 0; $wordlen = 0; $result = "";
  for ($i = 0; $i < strlen($str); $i++) {
    $chr = $str[$i];
    if ($chr == '<') {
      $tag++;
    } else if ($tag && $chr == '>') {
      $tag--;
    } else if ($chr == '&') {
      $ent++; $wordlen++;
    } else if ($ent && $chr == ';') {
      $ent--;
    } else if (!$tag && !$ent && preg_match("/\s/", $chr)) {
      $wordlen = 0;
    } else if (!$tag && !$ent) $wordlen++;

    $result .= $chr.((!$tag && !$ent && $wordlen && !($wordlen % $cols)) ? $cut : "");
  }
  return $result;
}

function snipThread($msg) {
  $msgkids = get_kids($msg);
  if (db_numrows($msgkids))
    for ($x = 0; $x < db_numrows($msgkids); $x++) snipThread(db_result($msgkids, $x, "pid"));

  $delete = db_query("DELETE FROM `{$GLOBALS['tableName']}` WHERE `pid`='$msg';");
}

function findMatron($msg) {
  $read = $msg;
  do {
    $this = get_row($read);
    $read = db_result($this, 0, "parent");
  } while ($read != "-1");
  return array(db_result($this, 0, "subject"), db_result($this, 0, "author"), db_result($this, 0, "date"), db_result($this, 0, "pid"), db_result($this, 0, "ip"));
}

function paginURI($input) {
  global $fData;

  if (isset($_GET['msg'])) $input .= "msg={$_GET['msg']}&amp;";
  if (isset($fData['search'])) $input .= "s=".urlencode($fData['search'])."&amp;";
  $input = preg_replace("/&amp;$/i", "", $input);
  return ($input == "?") ? "" : $input;
}

function unhtmlentities($string)  {
   $trans_tbl = get_html_translation_table(HTML_ENTITIES);
   $trans_tbl = array_flip($trans_tbl);
   $ret = strtr($string, $trans_tbl);
   return preg_replace('/&#(\d+);/me', "chr('\\1')", $ret);
}


error_reporting(E_ALL);

/* ***** Magic Quotes Fix ************************************* */
if (get_magic_quotes_gpc()) {
  $fsmq = create_function('&$mData, $fnSelf', 'if (is_array($mData)) foreach ($mData as $mKey=>$mValue) $fnSelf($mData[$mKey], $fnSelf); else $mData = stripslashes($mData);');
  $fsmq($_POST, $fsmq);
  $fsmq($_GET, $fsmq);
  $fsmq($_ENV, $fsmq);
  $fsmq($_SERVER, $fsmq);
  $fsmq($_COOKIE, $fsmq);
}
set_magic_quotes_runtime(0);


/* ***** Manage Cookies *************************************** */
if (!isset($_COOKIE['of_mark'])) $_COOKIE['of_mark'] = 0; 


/* ***** Compile Forum Data *********************************** */
$fData['msglist'] = get_all();
$fData['msgtotal'] = db_numrows($fData['msglist']);
$fData['offset'] =  $timeZoneOffset * 3600 + (($adjustForDaylightSavings) ? date("I") * 3600 : 0);
$fData['time'] = time() + $fData['offset'];
$fData['start'] = (isset($_GET['start'])) ? $_GET['start'] : 0;
$_POST['command'] = "";
if (isset($_POST['command_mark'])) $_POST['command'] = "Mark";
if (isset($_POST['command_prev'])) $_POST['command'] = "Preview";
if (isset($_POST['command_post'])) $_POST['command'] = "Post";


/* ***** Accept Incoming Post ********************************* */
if ($_SERVER['REQUEST_METHOD'] == "POST") {

  switch($_POST['command']) {
    /* ***** Preview ****************************************** */
    case "Preview":
      // Preview message setup

      break;

    /* ***** Post ********************************************* */
    case "Post":

      /* ***** Compile Post Data ************************************ */
      $pData['lastmsg'] = db_query("SELECT * FROM `$tableName` WHERE `ip`='{$_SERVER['REMOTE_ADDR']}' ORDER BY `pid` DESC LIMIT 1;");
      if (db_numrows($pData['lastmsg'])) {
        $pData['lastmsg_date'] = db_result($pData['lastmsg'], 0, "date") + $fData['offset'];
        $pData['lastmsg_message'] = db_result($pData['lastmsg'], 0, "message");
      }

      if ($_POST['parent'] != "-1") {
        $pData['parent'] = get_row($_POST['parent']);
        if (db_numrows($pData['parent'])) {
          $pData['parent_email'] = db_result($pData['parent'], 0, "email");
          $pData['parent_notify'] = db_result($pData['parent'], 0, "notify");
          $pData['parent_author'] = db_result($pData['parent'], 0, "author");
          $pData['parent_subject'] = db_result($pData['parent'], 0, "subject");
          $pData['parent_date'] = db_result($pData['parent'], 0, "date") + $fData['offset'];
        }
      }

      $_POST['message'] = (isset($_POST['message'])) ? str_replace(chr(13), "", $_POST['message']) : NULL;


      /* ***** Check Incoming Data ********************************** */
      if (isset($_POST['author']) && $_POST['author'] == $forumAdmin && isset($_POST['subject']) && $_POST['subject'] == $forumPassword) {
        $delmess = (preg_match("/^\d/", $_POST['message'])) ? (int)$_POST['message'] : $_POST['parent'];

        if ($delmess != -1) {
          $check = get_row($delmess);

          if (db_numrows($check)) {
            snipThread($delmess);
            $fData['success'] = sprintf($lang['post1'], $delmess);
            $fData['msglist'] = get_all();
            $fData['msgtotal'] = db_numrows($fData['msglist']);

          } else $fData['error'] = sprintf($lang['post2'], $delmess);
        } else $fData['error'] = $lang['post3'];

      } else if ((!isset($_POST['subject']) || !trim($_POST['subject'])) && (!isset($_POST['message']) || !trim($_POST['message']))) {
        $fData['error'] = $lang['post4'];

      } else if (db_numrows($pData['lastmsg']) && $pData['lastmsg_date'] + 30 > $fData['time']) {
        $fData['error'] = $lang['post5'];

      } else if (isset($pData['lastmsg_message']) && similar_text($pData['lastmsg_message'], $_POST['message']) > strlen($_POST['message']) * 0.95) {
        $fData['error'] = $lang['post6'];

      } else {
        $_POST['author'] = (strlen($_POST['author']) > 32) ? substr($_POST['author'], 0, 32) : $_POST['author'];
          $_POST['author'] = to_dbse($_POST['author']) or $_POST['author'] = $lang['messageb'];

        $_POST['subject'] = to_dbse($_POST['subject']) or $_POST['subject'] = "<{$lang['message9']}>";
          $_POST['subject'] = (strlen($_POST['subject']) > 64) ? substr($_POST['subject'], 0, 64) : $_POST['subject'];

        $_POST['message'] = to_dbse($_POST['message']) or $_POST['message'] = $lang['messagea'];
          if ($_POST['message'] == $lang['messagea']) $_POST['subject'] .= " (n/t)";

        $_POST['email'] = (preg_match("/^([a-z0-9\-_.]+?)@([\w\-]+\.([\w\-\.]+\.)?[\w]+)$/i", trim($_POST['email']))) ? trim($_POST['email']) : "";

        $_POST['notify'] = ($_POST['email'] && isset($_POST['notify'])) ? "yes" : "no";

        $_POST['image'] = (preg_match("/http:\/\/\w\S*\.(png|gif|jpg|jpeg|bmp|php|asp)/i", to_dbse(trim($_POST['image'])))) ? to_dbse(trim($_POST['image'])) : "";

        $insert = db_query("INSERT INTO `$tableName` VALUES ('', '{$_SERVER['REMOTE_ADDR']}', '{$_POST['author']}', '{$_POST['subject']}', '{$_POST['message']}', '{$_POST['image']}', '".time()."', '0', '{$_POST['email']}', '{$_POST['notify']}', '{$_POST['parent']}')");

        $retrieve = db_query("SELECT * FROM `$tableName` ORDER BY `date` DESC LIMIT 1;");
        if (db_result($retrieve, 0, "pid") % 10 == 0) $optimize = db_query("OPTIMIZE TABLE `$tableName`;");

        $fData['success'] = $lang['post7'];
        $fData['msgtotal']++;

        if (isset($_POST['cookify'])) {
          $cookout = base64_encode($_POST['author']." :: ".$_POST['email']." :: ".$_POST['notify']." :: ".$_POST['image']);
          setcookie("of_cookie", $cookout, time() + 2592000, $_SERVER['PHP_SELF']);
          $_COOKIE['of_cookie'] = $cookout;
        } else setcookie ("of_cookie", "", time() - 86400, $_SERVER['PHP_SELF']);

        if ($_POST['parent'] != "-1" && $pData['parent_notify'] == "yes") {

          @ini_set(sendmail_from, $replyEmail);

          $headers = "From: $emailFrom <$replyEmail>\r\n";
          $headers .= "X-Sender: <$replyEmail>\r\n";
          $headers .= "Return-Path: <$replyEmail>\r\n";
          $headers .= "Errors-To: <$replyEmail>\r\n";
          $headers .= "X-Mailer: PHP - Orca Forum v4.0b\r\n";
          $headers .= "X-Priority: 3\r\n";
          $headers .= "Date: ".date("r")."\r\n";
          $headers .= "Content-Type: text/plain; charset=UTF-8";

          $message = sprintf($lang['email1'], $pData['parent_author'], $pData['parent_subject'], gmdate($dateFormat, $pData['parent_date'] + $fData['offset']),
                       $timeZone, $_POST['subject'], $_POST['author'], gmdate($dateFormat, time()), $_POST['message'],
                       "http://{$_SERVER['HTTP_HOST']}{$_SERVER['PHP_SELF']}?msg=".db_result($retrieve, 0, "pid"));

          mail($pData['parent_email'], $lang['subject1'], $message, $headers);

          @ini_restore(sendmail_from);

        }
      }
      break;

    /* ***** Mark ********************************************* */
    case "Mark":
      setcookie("of_mark", $_POST['time'], time() + 900, $_SERVER['PHP_SELF']);
      $_COOKIE['of_mark'] = $_POST['time'];

      break;

  }

/* ***** Accept Incoming Get ********************************** */
} else {

  if (isset($_GET['msg'])) {
    $fData['message'] = get_row($_GET['msg']);

    if (db_numrows($fData['message'])) {
      $fData['matron'] = findMatron($_GET['msg']);

    } else {
      $fData['error'] = sprintf($lang['get1'], $_GET['msg']);
      unset($_GET['msg']);

    }
  }

  if (isset($_GET['s'])) {
    if ($fData['search'] = preg_replace("/[^\s\w]/i", "", preg_replace("/\s{2,}/i", " ", stripslashes(trim($_GET['s']))))) {
      $sList = explode(" ", $fData['search']);

      $buildq = "";
      foreach($sList as $term) $buildq .= "(`subject` LIKE '%".addslashes($term)."%' OR `message` LIKE '%".addslashes($term)."%') AND ";
      
      $fData['schlist'] = db_query("SELECT * FROM `$tableName` WHERE ".preg_replace("/\sAND\s$/i", "", $buildq).";");
      $fData['schlistrows'] = db_numrows($fData['schlist']);
    } else unset($fData['search']);
  }
}


/* ***** Do not cache this page ******************************* */
/*
header("Expires: Mon, 26 Jul 1997 05:00:00 GMT");
header("Last-Modified: " . gmdate("D, d M Y H:i:s") . " GMT");
header("Cache-Control: no-store, no-cache, must-revalidate");
header("Cache-Control: post-check=0, pre-check=0", false);
header("Pragma: no-cache"); 
*/
?>