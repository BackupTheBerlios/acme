<?php

include($conf["cms"] . "/debuglib.inc");

include($conf["cms"] . "/ets.inc");

include($conf["cms"] . "/fkt_createsel.inc");

include($conf["cms"] . "/fkt_groups.inc");

include($conf["cms"] . "/fkt_db.inc");

include($conf["cms"] . "/fkt_etc.inc");

include($conf["cms"] . "/fkt_rte.inc");

include($conf["cms"] . "/fkt_date." . $conf["lang"] . ".inc");

dbconnect();



$conf["admp"] = "acme-admin.php?";

if ($typ=="C") {$conf["admp"] = $conf["admp"]."&typ=C";}

if ($typ=="L") {$conf["admp"] = $conf["admp"]."&typ=L";}

if ($typ=="A") {$conf["admp"] = $conf["admp"]."&typ=A";}

include($conf["admbase"] . "/auth.inc");

include($conf["admbase"] . "/lang/admin." . $conf["lang"] . ".inc");

if ($conf["user_id"] <> 0) {

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

        .error

              {color="red";}

              }

</style>

<script language="JavaScript" type="text/javascript" src="richtext.js"></script>

</head>

<body>

<?php

echo "<div id=\"menu\" style=\"position:absolute; left:0px; top:0px;\">";

echo "<table>\n";

echo "<tr><td align = center><img src=\"" . $conf["images_admin"] . "omikron_logo.png\" alt=\"Logografik: ACME\" width=\"70\" height=\"70\" align=\"left\" border=\"0\"></td></tr>\n";

echo "<tr><td><br></td></tr>";

echo "<tr><td><a href=\"acme-admin.php?&typ=C\">                             <img src=\"" . $conf["images_admin"] . "content.png\" alt=\"Administrationsbereich: Inhalt" . $lang["admin_content"]. "\" border=\"0\"> <div style=\"position:relative; left:60px; top:-37px; z-index:10; \">" . $lang["admin_content"]. "</div></a></td></tr>";

if ($typ=="C"){

$statement = "SELECT m.modul FROM acme_module m  where m.typ='C' order by m.modul";

$result = dbquery($statement);

if ( mysql_num_rows($result) > 0 ) {

   while ($row = mysql_fetch_object($result)) {

       if (checkgroupaccess($conf["user_groups"], $row->modul) == 1) {

          echo "<tr><td class=\"nav_button_td_c\"><a href=" . $conf["admp"] ."&section=" . $row->modul . ">" . $lang["admin_$row->modul"] . "</a></td></tr>\n";

       }

    }

}

}
 
echo "<tr><td><a href=\"acme-admin.php?&typ=L\" class=\"navbuttonlink\">                              <img src=\"" . $conf["images_admin"] . "layout.png\" alt=\"Administrationsbereich: Layout" . $lang["admin_layout"]. "\" border=\"0\"><div style=\"position:relative; left:60px; top:-37px; z-index:10; \">" . $lang["admin_layout"]. "</div></a></td></tr>";

if ($typ=="L"){

$statement = "SELECT m.modul FROM acme_module m  where m.typ='L' order by m.modul";

$result = dbquery($statement);

if ( mysql_num_rows($result) > 0 ) {

   while ($row = mysql_fetch_object($result)) {

       if (checkgroupaccess($conf["user_groups"], $row->modul) == 1) {

          echo "<tr><td class=\"nav_button_td_l\"><a href=" . $conf["admp"] ."&section=" . $row->modul . ">" . $lang["admin_$row->modul"] . "</a></td></tr>\n";

       }

    }
 
}

}

echo "<tr><td><a href=\"acme-admin.php?&typ=A\"><img src=\"" . $conf["images_admin"] . "admin.png\" alt=\"" . $lang["admin_admin"]. "\" border=\"0\"><div style=\"position:relative; left:60px; top:-32px;; z-index:10; \">" . $lang["admin_admin"]. "</div></a></td></tr>";

if ($typ=="A"){

$statement = "SELECT m.modul FROM acme_module m  where m.typ='A' order by m.modul";

$result = dbquery($statement);

if ( mysql_num_rows($result) > 0 ) {

   while ($row = mysql_fetch_object($result)) {

       if (checkgroupaccess($conf["user_groups"], $row->modul) == 1) {

          echo "<tr><td class=\"nav_button_td_a\"><a href=" . $conf["admp"] ."&section=" . $row->modul . ">" . $lang["admin_$row->modul"] . "</a></td></tr>\n";

       }

    }

}

}

echo "<tr><td><a href=\"http://www.doerrstadt.org/kwiki/\" target=\"_blank\"><img src=\"" . $conf["images_admin"] . "help.png\" alt=\"Hilfe" . $lang["admin_hilfe"]. "\" border=\"0\" style=\"z-index:2;\"><div style=\"position:relative; left:60px; top:-32px;; z-index:10; \"> " . $lang["admin_hilfe"]. "</div></a>    </td></tr>";

echo "<tr><td><a href=" . $conf["admp"] ."&section=logout><img src=\"" . $conf["images_admin"] . "logout.png\" alt=\"" . $lang["admin_logout"]. "\" border=\"0\"><div style=\"position:relative; left:60px; top:-32px; z-index:10; \">" . $lang["admin_logout"]. "</div></a></td></tr>\n";

echo "<tr><td><b>User:</b></td></tr>\n";

echo "<tr><td>" . $conf["user_name"] . "</td></tr>\n";

echo "<tr><td><b>Gruppen:</b></td></tr>\n";

echo "<tr><td>" . getgroupnamesbyarray($conf["user_groups"]) . "</td></tr>\n";

echo "<tr><td><b>Rechte in  \"" . $section . "\"</b></td></tr>\n";

echo "<tr><td>" . getgrouprights($section, $conf["user_groups"]) . "</td></tr>\n";

echo "<tr><td><b>Date:</b></td></tr>\n";

echo "<tr><td>" . date("d.m.Y.") . "</td></tr>\n";

echo "<tr><td><b>Time:</b></td></tr>\n";

echo "<tr><td>" . date("H:i") ."</td></tr>\n";

echo "</table>\n</div>";

echo "<div id=\"main\">\n";

// echo "<h1 class="error">Administrationsbereich tempor&auml;r nicht verf&uuml;gbar<br>Bitte keine &Auml;nderungen durchf&uuml;hren!!!</h1><br>infos unter: icq 142499232<br>email: innomine@gmx.net<br>";

// menu actions

  if ($section <> "") {

     $conf["modul"] = $section;

     include($conf["admbase"] . "/" . $section . ".inc");

  }

echo "</div>";

?>

</body>

</html>

<?php

} else {echo "ha";}

?>