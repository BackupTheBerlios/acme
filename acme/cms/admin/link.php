<?php
include("cms/config.inc");
include($conf["cms"] . "/debuglib.inc");
include($conf["cms"] . "/ets.inc");
include($conf["cms"] . "/fkt_createsel.inc");
include($conf["cms"] . "/fkt_groups.inc");
include($conf["cms"] . "/fkt_db.inc");
include($conf["cms"] . "/fkt_etc.inc");
include($conf["cms"] . "/fkt_rte.inc");
include($conf["cms"] . "/fkt_date." . $conf["lang"] . ".inc");
dbconnect();
include($conf["admbase"] . "/lang/admin." . $conf["lang"] . ".inc");
?>
<html>
<head>
<title>
<?php $lang["admin_redaktionsbereich"] ?>
</title>
<link rel="stylesheet" type="text/css" href="acme.css">
<style type="text/css">
        @import "all.css"; /* just some basic formatting, no layout stuff */
        body  {
               margin:10px 10px 0px 10px;
               padding:0px;
              }
</style>
<script language="JavaScript" type="text/javascript" src="richtext.js"></script>
</head>
<body>
<?php
echo "<form action=\"admin/link.php\" method=\"post\">";
echo "<table>\n";
echo "<tr><td>Modul</td><td>\n";
echo "<select size = \"1\" name=\"modul\">";
$statement = "SELECT m.modul FROM acme_module m  where m.typ='C' order by m.modul";
$result = dbquery($statement);
if ( mysql_num_rows($result) > 0 ) {
   while ($row = mysql_fetch_object($result)) {
       if (checkgroupaccess($conf["user_groups"], $row->modul) == 1) {
          echo "<option value=\"". $row->modul . "\" >" . $lang["admin_$row->modul"] . "</option>";       	  
          }
   }
}
echo "<input type=\"submit\" value=\"ok\"></td></tr></table></form>";

if (isset($modul)){
	include("admin/link.".$modul.".inc");
}
?>
</body>
</html>