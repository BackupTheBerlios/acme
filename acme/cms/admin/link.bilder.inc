<?php
include($conf["admbase"] . "/lang/bilder." . $conf["lang"] . ".inc");

echo "<table class=\"reda_td \">";
echo "<tr></td><td>";
$result = dbquery("select * from acme_bilder_typs order by img_typ_name");
echo "<select size = \"1\" name=\"img_typ\">";
if (!isset($img_typ)){echo "<option value=\"\" selected></option>";}
if ( mysql_num_rows($result) > 0 )   {
   while ( $row = mysql_fetch_object($result)) {
   	     $img_count = count_img_from_typ($row->img_typ_id);
         echo "<option value=" . $row->img_typ_id;
         if ( $row->img_typ_id == $img_typ ){ echo " selected ";}
         echo ">" . $row->img_typ_name . "(".$img_count.")</option>";
   }
   mysql_free_result($allgroups);
}
echo "</select>";
echo "</td></tr></table>";

echo "<table class=\"reda_td \">";
echo "<tr></td><td>".$lang["bilder_name"]."</td><td>".$lang["bilder_thumb"]."</td><td>".$lang["bilder_link"]."</td></tr>";
$result = dbquery("select * from acme_bilder where img_typ_id = '" . $img_typ_id . "'");
if ( mysql_num_rows($result) > 0 ){	
   while ($row = mysql_fetch_object($result)){
      echo "<tr>";
      echo "<td>".$row->img_name."</td>";
      echo "<td><img src=\"".$conf["images"]."thumb_".$row->img_real_name."\"></td>";         
      echo "<td>";
      echo "[img]".$row->img_name."[/img]<br>";
      echo "[imgr]".$row->img_name."[/imgr]<br>";
      echo "[imgl]".$row->img_name."[/imgl]";            
      echo "</td>";
      echo "</tr>";
   }
   echo "</table>";
   mysql_free_result($result);
}
?>