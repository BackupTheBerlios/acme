<?php
include("lang/auth." . $conf["lang"] . ".inc");

   session_start();

   if ($section == "logout") {
      $result = dbquery("update ".$conf["db_namespace"]."author set author_session = '' ,author_ip = '', author_login = 'N' WHERE author_name = '" . $_SESSION['username'] . "'");
      displayLogin();
   } else {
      if (isset($_POST['username']) && isset($_POST['password'])) {
         $query = "SELECT * FROM ".$conf["db_namespace"]."author WHERE author_passwd = '" . $_POST['password'] . "' AND author_name = '" . $_POST['username'] . "';";
         $result = dbquery($query) or die("Couldn't query the database.". mysql_error());   
         if ( mysql_num_rows($result) > 0 ) {
            $row = mysql_fetch_array($result);
            $conf["author_id"]       = $row["author_id"];
            $conf["author_name"]     = $row["author_name"];      
            $conf["author_active"]   = $row["author_active"];      
            $conf["author_groups"]   = $row["author_groups"];
            $conf["author_login"]    = $row["author_login"];
            $conf["lang"]            = $row["author_lang"];
            if ($conf["author_active"]=="Y"){
               $logged_in = 1;
               $_SESSION['username'] = $conf["author_name"];
               $_SESSION['sess-id'] = session_id();
               session_write_close();
               $result = dbquery("update ".$conf["db_namespace"]."author set author_session = '" . session_id() . "' ,author_ip = '" . $_SERVER['REMOTE_ADDR'] ."', author_login = 'Y', author_last_login = NOW() WHERE author_name = '" . $conf["author_name"] . "'");
            } else {
               displayLogin("ad");
            }     
         } else {
            displayLogin("nf");
         }
      } elseif (isset($_SESSION['username'])) {
         $query = "SELECT * FROM ".$conf["db_namespace"]."author WHERE author_session = '" . $_SESSION['sess-id'] . "';";
         $result = dbquery($query) or die("Couldn't query the database.". mysql_error());   
         if ( mysql_num_rows($result) > 0 ) {
            $row = mysql_fetch_array($result);
            $conf["author_id"]       = $row["author_id"];
            $conf["author_name"]     = $row["author_name"];      
            $conf["author_active"]   = $row["author_active"];      
            $conf["author_groups"]   = $row["author_groups"];
            $conf["author_login"]    = $row["author_login"];
            $conf["lang"]            = $row["author_lang"];
            if ($conf["author_active"]=="Y"){
               $logged_in = 1;
            } else {
               displayLogin("ad");
            }     
         } else {
            displayLogin("nf");
         }
      } else {
         $logged_in = 0;
         displaylogin();
      }
   }
function displayLogin($error) {
   global $conf, $lang;

   $logged_in = 0;
   $_SESSION = array();
   if (isset($_COOKIE[session_name()])) {setcookie(session_name(), '', time()-42000, '/');}
   session_destroy();
// unset($_SESSION['username']);
// unset($_SESSION['password']);   
?>
<html>
<head>
<title>
<?php $lang["authorisierung"] ?>
</title>
<link rel="stylesheet" type="text/css" href="acme.css">
<style type="text/css">
@import "all.css"; /* just some basic formatting, no layout stuff */
body  {
margin:10px 10px 0px 10px;
padding:0px;
}
</style>
</head>
<body>
<?php
   echo "<table>";
   echo "<tr><td align = center rowspan=5><img src=\"" . $conf["images_admin"] . "omikron_logo.png\" alt=\"Logografik: ACME\" width=\"70\" height=\"70\" align=\"left\" border=\"0\"></td></tr>\n";
   echo "<tr><td colspan=2><br>";
   echo '<form name="login" method="POST" action="' . $conf["admp"] . '"></td></tr>
         <tr><td>' . $lang["authorisierung_username"] . '</td><td><input name="username" type="text" id="username" value="user"></td></tr>
         <tr><td>' . $lang["authorisierung_passwort"] . '</td><td><input name="password" type="password" id="password" value="password" maxlength="40"></td></tr>
         <tr><td>&nbsp;</td><td><input name="Sign In" type="submit" id="Sign In" value="' . $lang["authorisierung_neu_anmelden"] . '"></td></tr>
         <tr><td colspan = 2></form></td></tr>';
   echo "</table>";      
   if (isset($error)){
      echo "<h2>".$lang["authorisierung_fehler"] . "</h2>";
   	  if ($error=="nf") echo $lang["authorisierung_unbekannt"];
      if ($error=="ad") echo $lang["authorisierung_gesperrt"];
   } 
?>   
</body>
</html>
<?   
   exit;

}
?>    