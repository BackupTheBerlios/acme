<?php
function dbpconnect()
{
   global $conf, $lang;
   mysql_pconnect($conf["dbhost"],$conf["dbuser"],$conf["dbpass"]) or die("Unable to connect to databases server!");
   return;
}

function admpconnect()
{
   global $conf, $lang;
   mysql_pconnect($conf["dbhost"],$conf["dbadmuser"],$conf["dbadmpass"]) or die("Unable to connect to databases server!");
   return;
}

function dbconnect()
{
   global $conf, $lang;
   mysql_connect($conf["dbhost"],$conf["dbuser"],$conf["dbpass"]) or die("Unable to connect to databases server!");;
   return;
}

function dbquery($sqlcommand)
{
   global $conf, $lang;
   $func_result = mysql_db_query($conf["dbname"], $sqlcommand);
   if (!$func_result){echo "<p>DBERROR: ". mysql_errno() . ": " . mysql_error(). "\n<br>".$sqlcommand ."</p>";}
   return $func_result;
}
?>
