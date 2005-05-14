<?php
include($conf["admbase"] . "/lang/downloadss." . $conf["lang"] . ".inc");

echo "<form action=\"".$conf["indexbase"]."/link.php?modul=downloads&name=".$name."&field=".$field."\" method=\"post\">";
echo "<table class=\"reda_td \">";
echo "<tr></td><td>";
$result = dbquery("select * from ".$conf["db_namespace"]."download_typs order by download_typ_name");
echo "<select size = \"1\" name=\"download_typ_id\">";
if (!isset($url_typ)){echo "<option value=\"\" selected></option>";}
if ( mysql_num_rows($result) > 0 )   {
   while ( $row = mysql_fetch_object($result)) {
         echo "<option value=" . $row->download_typ_id;
         if ( $row->url_typ_id == $url_typ ){ echo " selected ";}
         echo ">" . $row->download_typ_name . "</option>";
   }
   mysql_free_result($result);
}
echo "</select>";
echo "<input type=\"submit\" name = ok value=\"ok\"></td></tr></table></form>";

echo "<table class=\"reda_td \">";
echo "<tr></td><td>".$lang["url_name"]."</td><td>".$lang["url_link"]."</td></tr>";
$result = dbquery("select * from ".$conf["db_namespace"]."download where download_typ like '%:" . $download_typ_id . ":%'");
if ( mysql_num_rows($result) > 0 ){	
   while ($row = mysql_fetch_object($result)){
      echo "<tr>";
      echo "<td>".$row->download_name."</td>";
      echo "<td>";
      $linkname = "[download=".$row->download_id."]".$row->download_name."[/download]";
      echo $linkname;
      if (isset($name)&&isset($field)) {
         echo "<input type=button value=\">\" onClick= writelink('".$linkname."');>";
      }                  
      echo "</td>";
      echo "</tr>";
   }
   echo "</table>";
   mysql_free_result($result);
}
?>