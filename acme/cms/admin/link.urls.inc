<?php
include($conf["admbase"] . "/lang/urls." . $conf["lang"] . ".inc");

echo "<form action=\"".$conf["indexbase"]."/link.php?modul=urls\" method=\"post\">";
echo "<table class=\"reda_td \">";
echo "<tr></td><td>";
$result = dbquery("select * from ".$conf["db_namespace"]."url_typs order by url_typ_name");
echo "<select size = \"1\" name=\"url_typ_id\">";
if (!isset($url_typ)){echo "<option value=\"\" selected></option>";}
if ( mysql_num_rows($result) > 0 )   {
   while ( $row = mysql_fetch_object($result)) {
         echo "<option value=" . $row->url_typ_id;
         if ( $row->url_typ_id == $url_typ ){ echo " selected ";}
         echo ">" . $row->url_typ_name . "</option>";
   }
   mysql_free_result($result);
}
echo "</select>";
echo "<input type=\"submit\" name = ok value=\"ok\"></td></tr></table></form>";

echo "<table class=\"reda_td \">";
echo "<tr></td><td>".$lang["url_name"]."</td><td>".$lang["url_link"]."</td></tr>";
$result = dbquery("select * from ".$conf["db_namespace"]."url where url_typ like '%:" . $url_typ_id . ":%'");
if ( mysql_num_rows($result) > 0 ){	
   while ($row = mysql_fetch_object($result)){
      echo "<tr>";
      echo "<td>".$row->url_name."</td>";
      echo "<td>";
      $linkname = "[iurl=".$row->url_id."]".$row->url_name."[/iurl]";
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