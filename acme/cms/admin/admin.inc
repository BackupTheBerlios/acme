<?php
$conf["admp"] = $conf["indexname"] . "?page=admin";
include($conf["admbase"] . "/auth.inc");
if ($conf["user_id"] <> 0) {
?>
<html>
<head>
<title>ACME :: Redaktionsbereich</title>
<link rel="stylesheet" type="text/css" href="acme.css">
<style type="text/css">
        @import "all.css"; /* just some basic formatting, no layout stuff */

        body {
                margin:10px 10px 0px 10px;
                padding:0px;
                }
    #menu {
                position: absolute;
                left:5px;
                top:5px;
                width:160px;

                }
  #head {
                position: absolute;
      left: 166px;
      top: 5px;

                height : 30px;
                                }
        #main {
                position: absolute;
             left: 166px;
             top: 36px;
                }
</style>

</head>
<body>
<?php
echo "<div id=\"menu\">";
echo "<table cellpadding = 5 width = 155>\n";
echo "<tr><td align = center><img src=\"/europaspiegel/cms/bilder/logo_pic_70x70.gif\" alt=\"acme_logo\" width=\"70\" height=\"70\" align=\"left\"></td></tr>\n";
$statement = "SELECT m.modul FROM acme_module m, acme_user_rights r  WHERE m.modul = r.modul and r.access = 'Y' and r.user_id = '" . $conf["user_id"]  . "'";
$result = dbquery($statement);
if ( mysql_num_rows($result) > 0 ) {while ($row = mysql_fetch_object($result)) {echo "<tr><td class=\"nav_button_td\"><a href=" . $conf["admp"] ."&section=" . $row->modul . ">" . $row->modul . "</a></td></tr>\n"; }}



echo "<tr><td class=\"nav_button_td\"><a href=" . $conf["base"] . "/doc/admin/index.php?include=" . $conf["include"] . " target=x_new>Hilfe</a></td></tr>\n";
echo "<tr><td class=\"nav_button_td\"><a href=" . $conf["indexname"] . " target=x_new_home>Home</a></td></tr>\n";
echo "<tr><td class=\"nav_button_td\"><a href=" . $conf["indexname"] . "?page=admin&section=logout>Logout</a></td></tr>\n";



echo "<tr><td class=\"nav_button_td\"><strong>Status:</strong><br><br>\n";
echo "<strong>Admin user:</strong><br>\n";
echo  "" . $conf["user_name"] . "<br><br>\n";
echo "<strong>Date:</strong><br>\n";
echo  "" . date("d.m.Y.") . "<br><br>\n";
echo "<strong>Last job time:</strong><br>\n";
echo  "" . date("H:i") ."</td></tr>\n";
echo "</table>\n</div>";
echo "<div id=\"main\">\n";
// menu actions
  if ($section <> "") {include($conf["admbase"] . "/" . $section . ".inc");}
echo "</div>";
?>
</body>
</html>
<?php
} else {echo "ha";}
?>