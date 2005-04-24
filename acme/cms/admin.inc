<?php
include($conf["cmsbase"] . "/debuglib.inc");
include($conf["cmsbase"] . "/ets.inc");
include($conf["cmsbase"] . "/fkt_createsel.inc");
include($conf["cmsbase"] . "/fkt_groups.inc");
include($conf["cmsbase"] . "/fkt_db.inc");
include($conf["cmsbase"] . "/fkt_etc.inc");
include($conf["cmsbase"] . "/fkt_img.inc");
include($conf["cmsbase"] . "/fkt_page.inc");
include($conf["cmsbase"] . "/fkt_rte.inc");
include($conf["cmsbase"] . "/fkt_date." . $conf["lang"] . ".inc");

dbconnect();

$conf["admp"] = "acme-admin.php?";

include($conf["admbase"] . "/auth.inc");

if ($typ=="C") {$conf["admp"] = $conf["admp"]."&typ=C";}
if ($typ=="L") {$conf["admp"] = $conf["admp"]."&typ=L";}
if ($typ=="A") {$conf["admp"] = $conf["admp"]."&typ=A";}

include($conf["admbase"] . "/lang/admin." . $conf["lang"] . ".inc");

if ($logged_in == 1) {

?>

<html>
<head>
<meta http-equiv="content-type" content="text/html; charset=utf8">
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
        #menu {
               position: fixed;
               left:5px;
               top:5px;
               width:149px;
          }
        #head {
               position: absolute;
               left: 166px;
               top: 5px;
               height : 30px;
              }
        #main {
               position: absolute;
               left: 176px;
               top: 36px;
               }
        #debug {
               position: absolute;
               left: 1000px;
               top: 36px;
               }

        .error
              {color="red";}
              }
</style>
<script language="JavaScript" type="text/javascript" src="admin_bbc.js"></script>
</head>
<body onLoad = "self.name = 'AdminWindow';">
<?php
echo "<div id=\"menu\" style=\"position:absolute; left:0px; top:0px;\">";
echo "<table>\n";
echo "<tr><td align = center><img src=\"" . $conf["images_admin"] . "omikron_logo.png\" alt=\"Logografik: ACME\" width=\"70\" height=\"70\" align=\"left\" border=\"0\"></td></tr>\n";
echo "<tr><td><br></td></tr>";
echo "<tr><td><a href=\"acme-admin.php?&typ=C\" class=\"navbuttonlink\">                             <img src=\"" . $conf["images_admin"] . "content.png\" alt=\"Administrationsbereich: Inhalt" . $lang["admin_content"]. "\" border=\"0\"><div style=\"position:relative; left:60px; top:-32px; width:90px; z-index:10; \">" . $lang["admin_content"]. "</div></a></td></tr>";

if ($typ=="C"){
   $statement = "SELECT m.modul FROM ".$conf["db_namespace"]."module m  where m.typ='C' order by m.modul";
   $result = dbquery($statement);
   if ( mysql_num_rows($result) > 0 ) {
      while ($row = mysql_fetch_object($result)) {
          if (acl_check("access", $conf["author_groups"], $conf["author_id"], $row->modul, 0) == 1) {
             echo "<tr><td class=\"nav_button_td_c\"><a href= " . $conf["admp"] ."&section=" . $row->modul . " class=\"navlink\">" . $lang["admin_$row->modul"] . "</a></td></tr>\n";
          }
       }
   }
}
echo "<tr><td><a href=\"acme-admin.php?&typ=L\" class=\"navbuttonlink\">                              <img src=\"" . $conf["images_admin"] . "layout.png\" alt=\"Administrationsbereich: Layout" . $lang["admin_layout"]. "\" border=\"0\"><div style=\"position:relative; left:60px; top:-32px; width:90px; z-index:10; \">" . $lang["admin_layout"]. "</div></a></td></tr>";
if ($typ=="L"){
   $statement = "SELECT m.modul FROM ".$conf["db_namespace"]."module m  where m.typ='L' order by m.modul";
   $result = dbquery($statement);
   if ( mysql_num_rows($result) > 0 ) {
      while ($row = mysql_fetch_object($result)) {
         if (acl_check("access", $conf["author_groups"], $conf["author_id"], $row->modul, 0) == 1) {
            echo "<tr><td class=\"nav_button_td_l\"><a href=" . $conf["admp"] ."&section=" . $row->modul . " class=\"navlink\">" . $lang["admin_$row->modul"] . "</a></td></tr>\n";
         }
      }
   }
}
echo "<tr><td><a href=\"acme-admin.php?&typ=A\" class=\"navbuttonlink\"><img src=\"" . $conf["images_admin"] . "admin.png\" alt=\"" . $lang["admin_admin"]. "\" border=\"0\"><div style=\"position:relative; left:60px; top:-32px; width:90px; z-index:10; \">" . $lang["admin_admin"]. "</div></a></td></tr>";
if ($typ=="A"){
   $statement = "SELECT m.modul FROM ".$conf["db_namespace"]."module m  where m.typ='A' order by m.modul";
   $result = dbquery($statement);
   if ( mysql_num_rows($result) > 0 ) {
      while ($row = mysql_fetch_object($result)) {
         if (acl_check("access", $conf["author_groups"], $conf["author_id"], $row->modul, 0) == 1) {
            echo "<tr><td class=\"nav_button_td_a\"><a href=" . $conf["admp"] ."&section=" . $row->modul . " class=\"navlink\">" . $lang["admin_$row->modul"] . "</a></td></tr>\n";
         }
      }
   }
}

echo "<tr><td><a href=\"http://www.doerrstadt.org/kwiki/\" target=\"_blank\" class=\"navbuttonlink\" alt=\"�ffnet sich im neuen Fenster: Link zum Hilfe-Center\"><img src=\"" . $conf["images_admin"] . "help.png\" alt=\"Hilfe" . $lang["admin_hilfe"]. "\" border=\"0\" style=\"z-index:2;\"><div style=\"position:relative; left:60px; top:-32px; width:90px; z-index:10; \"> " . $lang["admin_hilfe"]. "</div></a>    </td></tr>";
echo "<tr><td><a href=" . $conf["admp"] ."&section=logout class=\"navbuttonlink\"><img src=\"" . $conf["images_admin"] . "logout.png\" alt=\"" . $lang["admin_logout"]. "\" border=\"0\"><div style=\"position:relative; left:60px; top:-32px; width:90px; z-index:10; \">" . $lang["admin_logout"]. "</div></a></td></tr>\n";
echo "<tr><td class=\"nav_button_td_status\"><b>User:</b><br>". $conf["author_name"] . "(".$conf["author_id"].")<br><br>";
echo "<b>Gruppen:</b><br>" . getgroupnamesbyarray($conf["author_groups"]) ."(".$conf["author_groups"].")<br><br>";
echo "<b>Date:</b><br>" . date("d.m.Y.") . "<br><br>";
echo "<b>Time:</b><br>" . date("H:i") ."</td></tr>\n";
echo "</table>\n</div>";
echo "<div id=\"main\">\n";
// echo "<h1 class="error">Administrationsbereich tempor&auml;r nicht verf&uuml;gbar<br>Bitte keine &Auml;nderungen durchf&uuml;hren!!!</h1><br>infos unter: icq 142499232<br>email: innomine@gmx.net<br>";

// menu actions
  if ($section <> "") {
     $conf["modul"] = $section;
     include($conf["admbase"] . "/" . $section . ".inc");
  } else {
  	 include($conf["admbase"] . "/messages.inc");
  }

echo "</div>";

if ($conf["author_name"] == "developer"){echo "<div id=debug>";show_vars();echo "</div>";}

?>
</body>
</html>
<?php
}
?>