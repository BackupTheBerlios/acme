<?php

include("lang/auth." . $conf["lang"] . ".inc");

function displayLogin($error) {
   global $conf, $lang;
   
   header("WWW-Authenticate: Basic realm=\"www.doerrstadt.org\"");
   header("HTTP/1.0 401 Unauthorized");
   echo "<h2>".$lang["authorisierung_fehler"] . "</h2>";
   if (isset($error)){
   	  if ($error=="nf") echo $lang["authorisierung_unbekannt"];
      if ($error=="ad") echo $lang["authorisierung_gesperrt"];
   }
   echo "<a href = \"". $conf["admp"] . "\">".$lang["authorisierung_neu_anmelden"] . "</a>";   
   exit;
}
if ($section == "logout") {
   $result = dbquery("update acme_author set author_login = 'N' WHERE autor_name = '" . $conf["author_name"] . "'");   
   displayLogin();
   }
if (!isset($PHP_AUTH_USER) || !isset($PHP_AUTH_PW)) {
   displayLogin("");
} else {
  $USER = addslashes($PHP_AUTH_USER);
  $PW = $PHP_AUTH_PW;
  $result = dbquery("SELECT author_id, author_name, author_active, author_groups FROM acme_author WHERE author_passwd = '" . $PW . "' AND author_name = '" . $USER . "'") or die("Couldn't query the user-databasee.");   
   if ( mysql_num_rows($result) > 0 ) {
      $row = mysql_fetch_array($result);
      $conf["author_id"]       = $row["author_id"];
      $conf["author_name"]     = $row["author_name"];      
      $conf["author_active"]   = $row["author_active"];      
      $conf["author_groups"]   = $row["author_groups"];
      if ($conf["author_active"]=="Y") {
         $result = dbquery("update acme_author set author_login = 'Y', set author_last_login = NOW() WHERE author_name = '" . $USER . "'");
      } else { displayLogin("ad"); }     
   } else { displayLogin("nf"); }
} 
?>    