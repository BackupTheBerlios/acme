<?php
include("lang/auth." . $conf["lang"] . ".inc");

session_start();

if ($section == "logout") {
   $result = dbquery("update acme_author set author_login = 'N' WHERE autor_name = '" . $conf["author_name"] . "'");
   displayLogin();
}

if (isset($_POST['username']) && isset($_POST['password'])) {

   $query = "SELECT author_id,author_active,author_name,author_groups FROM acme_author WHERE author_passwd = '" . $_POST['password'] . "' AND author_name = '" . $_POST['username'] . "';";
   $result = dbquery($query) or die("Couldn't query the database.". mysql_error());   
   if ( mysql_num_rows($result) > 0 ) {
      $row = mysql_fetch_array($result);
      $conf["author_id"]       = $row["author_id"];
      $conf["author_name"]     = $row["author_name"];      
      $conf["author_active"]   = $row["author_active"];      
      $conf["author_groups"]   = $row["author_groups"];
      $conf["author_login"]    = $row["author_login"];
      if ($conf["author_active"]=="Y"){
         $logged_in = 1;
         $_SESSION['username'] = $_POST['uname'];
         $_SESSION['password'] = $_POST['password'];

         $result = dbquery("update acme_author set author_login = 'Y', set author_last_login = NOW() WHERE author_name = '" . $USER . "'");
      } 
      else {displayLogin("ad");}     
   } 
   else {displayLogin("nf");}
}
elseif (isset($_SESSION['username']) && isset($_SESSION['password'])) {
   $query = "SELECT author_id,author_active,author_name,author_groups FROM acme_author WHERE author_passwd = '" . $_SESSION['password'] . "' AND author_name = '" . $_SESSION['username'] . "';";
   $result = dbquery($query) or die("Couldn't query the database.". mysql_error());   
   if ( mysql_num_rows($result) > 0 ) {
      $row = mysql_fetch_array($result);
      $conf["author_id"]       = $row["author_id"];
      $conf["author_name"]     = $row["author_name"];      
      $conf["author_active"]   = $row["author_active"];      
      $conf["author_groups"]   = $row["author_groups"];
      $conf["author_login"]    = $row["author_login"];
      if ($conf["author_active"]=="Y"){
         $logged_in = 1;
      } 
      else {displayLogin("ad");}     
   } 
   else {displayLogin("nf");}
}
else{
   $logged_in = 0;
   displaylogin();
}

function displayLogin($error) {
   global $conf, $lang;

   $logged_in = 0;
   unset($_SESSION['username']);
   unset($_SESSION['password']);   
	     
   echo '<form name="login" method="POST" action="' . $conf["admp"] . '">
         <input name="username" type="text" id="username" value="user">
         <input name="password" type="password" id="password" value="password" maxlength="40">
         <input name="Sign In" type="submit" id="Sign In" value="' . $lang["authorisierung_neu_anmelden"] . '">
         </form>';
   if (isset($error)){
      echo "<h2>".$lang["authorisierung_fehler"] . "</h2>";
   	  if ($error=="nf") echo $lang["authorisierung_unbekannt"];
      if ($error=="ad") echo $lang["authorisierung_gesperrt"];
   } 
   exit;
}
?>    