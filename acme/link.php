<?php
include("cms/config.inc");
include($conf["cmsbase"] . "/debuglib.inc");
include($conf["cmsbase"] . "/ets.inc");
include($conf["cmsbase"] . "/fkt_createsel.inc");
include($conf["cmsbase"] . "/fkt_groups.inc");
include($conf["cmsbase"] . "/fkt_db.inc");
include($conf["cmsbase"] . "/fkt_etc.inc");
include($conf["cmsbase"] . "/fkt_rte.inc");
include($conf["cmsbase"] . "/fkt_date." . $conf["lang"] . ".inc");
dbconnect();
include($conf["admbase"] . "/lang/admin." . $conf["lang"] . ".inc");
include($conf["admbase"] . "/auth.inc");
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
if (isset($name)&&isset($field)) {
   echo "<form action=\"".$conf["indexbase"]."/link.php?name=".$name."&field=".$field."\" ENCTYPE=\"multipart/form-data\" method=\"post\">";
} else {
   echo "<form action=\"".$conf["indexbase"]."/link.php\" ENCTYPE=\"multipart/form-data\" method=\"post\">";
}	
echo "<table>\n";
echo "<tr><td>Modul</td><td>\n";
echo "<select size = \"1\" name=\"modul\">\n";
$statement = "SELECT m.modul FROM acme_module m  where m.typ='C' order by m.modul";
$result = dbquery($statement);
if ( mysql_num_rows($result) > 0 ) {
   while ($row = mysql_fetch_object($result)) {
       if (checkgroupaccess($conf["author_groups"], $row->modul) == 1) {
          echo "<option value=\"". $row->modul . "\" >" . $lang["admin_$row->modul"] . "</option>\n";
       }
   }
}
echo "</select><input type=\"submit\" name = ok value=\"ok\">\n</td></tr></table>\n</form>\n";

if (isset($modul)){
	include($conf["admbase"] . "/link.".$modul.".inc");
}
?>
</body>
</html>