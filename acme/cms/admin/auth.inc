<?php

include("lang/auth." . $conf["lang"] . ".inc");

function displayLogin() {
   global $conf, $lang;
   
   header("WWW-Authenticate: Basic realm=\"www.doerrstadt.org\"");
   header("HTTP/1.0 401 Unauthorized");
   echo "<h2>".$lang["authorisierung_fehler"] . "</h2>";
   echo $lang["authorisierung_unbekannt"];
   echo "<a href = \"". $conf["admp"] . "\">".$lang["authorisierung_neu_anmelden"] . "</a>";   
   exit;
}
if ($section == "logout") {
   $result = dbquery("update acme_user set user_login = 'N' WHERE user_name = '" . $conf["user_name"] . "'");   
   displayLogin();
   }
if (!isset($PHP_AUTH_USER) || !isset($PHP_AUTH_PW)) {
   displayLogin($PW);
} else {
  $USER = addslashes($PHP_AUTH_USER);
  $PW = $PHP_AUTH_PW;
  $result = dbquery("SELECT user_id, user_name, user_active, user_groups FROM acme_user WHERE user_passwd = '" . $PW . "' AND user_name = '" . $USER . "'") or die("Couldn't query the user-databasee.");   
   if ( mysql_num_rows($result) > 0 ) {
      $row = mysql_fetch_array($result);
      $conf["user_id"]       = $row["user_id"];
      $conf["user_name"]     = $row["user_name"];      
      $conf["user_active"]   = $row["user_active"];      
      $conf["user_groups"]   = $row["user_groups"];
      $result = dbquery("update acme_user set user_login = 'Y', set user_last_login = NOW() WHERE user_name = '" . $USER . "'");   
   } else { displayLogin($PW); }
} 
?>    