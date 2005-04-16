<?php
include("lang/auth." . $conf["lang"] . ".inc");

function displayLogin($error) {
   global $conf, $lang;
   
   header("WWW-Authenticate: Basic realm=\"".$conf["domain"]."\"");
   header("HTTP/1.0 401 Unauthorized");
   echo "<h2>".$lang["authorisierung_fehler"] . "</h2>";
   if (isset($error)){
   	  if ($error=="nf") echo $lang["authorisierung_unbekannt"];
      if ($error=="ad") echo $lang["authorisierung_gesperrt"];
   } else {echo "unknown error";}
   echo "<a href = \"". $conf["admp"] . "\">".$lang["authorisierung_neu_anmelden"] . "</a>";   
   exit;
}

if ($section == "logout") {
   $result = dbquery("update ".$conf["db_namespace"]."author set author_login = 'N' WHERE autor_name = '" . $conf["author_name"] . "'");   
   displayLogin();
}

if (!isset($PHP_AUTH_USER) || !isset($PHP_AUTH_PW)) {
   displayLogin("");
} 
else {
   $USER = addslashes($PHP_AUTH_USER);
   $PW = $PHP_AUTH_PW;
   $query = "SELECT author_id,author_active,author_name,author_groups FROM ".$conf["db_namespace"]."author WHERE author_passwd = '" . $PW . "' AND author_name = '" . $USER . "';";
   $result = dbquery($query) or die("Couldn't query the database.". mysql_error());   
   if ( mysql_num_rows($result) > 0 ) {
      $row = mysql_fetch_array($result);
      $conf["author_id"]       = $row["author_id"];
      $conf["author_name"]     = $row["author_name"];      
      $conf["author_active"]   = $row["author_active"];      
      $conf["author_groups"]   = $row["author_groups"];
      if ($conf["author_active"]=="Y") {
         $result = dbquery("update ".$conf["db_namespace"]."author set author_login = 'Y', set author_last_login = NOW() WHERE author_name = '" . $USER . "'");
      } 
      else {displayLogin("ad");}     
   } 
   else {displayLogin("nf");}
}  
?>    