<?php
include($conf["admbase"] . "/lang/artikel." . $conf["lang"] . ".inc");

echo "<form action=\"".$conf["indexbase"]."/link.php?modul=artikel\" method=\"post\">";
echo "<table class=\"reda_td\" border = 1 cellpadding = 0 cellspacing = 0>\n";
echo "<tr><td>" . $lang["artikel_der_seite"] ."</td><td>";
createsel_pagenCAs("page_id", $page_id); 
echo "</td><td><input type=\"submit\" value=\"" . $lang["artikel_anzeigen"] . "\"></td></tr>\n";
echo "<tr><td>" . $lang["artikel_des_autors"] . "</td><td colspan = \"2\">";
if ($author_id=="" || !isset($author_id)) {$author_id = $conf["author_id"];}
createsel_author("author_id", $author_id); 
echo "</td></tr>\n";
echo "</table>\n";
echo "</form>\n";
echo "<table  class=\"reda_td\" border = 1 cellpadding = 0 cellspacing = 0>\n";
if ($page_id <> ""){
   echo "<tr><td>".$lang["artikel_id"] . "</td><td>".$lang["artikel_ueberschrift1"] . "</td><td>".$lang["artikel_veroeffentlichungsdatum"] . "</td><td>".$lang["artikel_seite"] . "</td><td>".$lang["artikel_autor"] . "</td><td>".$lang["artikel_counter"] . "</td><td>".$lang["artikel_link"] . "</td></tr>\n";
   $Statement = "select * from ".$conf["db_namespace"]."artikel where artikel_page like '%:" . $page_id . ":%'";
   if ($author_id <> ""){ $Statement .= " and artikel_author_id = '" . $author_id . "'";}
   $Statement .= " order by artikel_publish_date DESC";
   $result = dbquery($Statement);
   if ( mysql_num_rows($result) > 0 ){
      while ($row = mysql_fetch_object($result)){
      	 //if (acl_check("insert", $conf["author_groups"], $conf["author_id"], "artikel", $row->artikel_id) == 1 && $row->url_typ_id <> $selfid) {
            $artikelpage = explode(":", $row->artikel_page);
            $artikelpage = $artikelpage[1];
            echo "<tr><td>". $row->artikel_id . "</td>";
            echo "<td>".$row->artikel_headline."</td>";
 		    echo "<td>". mydate2datetime($row->artikel_publish_date) ."</td>";
		    echo "<td>". getpagenamebyidarray($row->artikel_page)."</td>";
            echo "<td>". getauthorbyid($row->artikel_author_id) ."</td>";
            echo "<td>". $row->artikel_counter."</td>";
            echo "<td>[artikel=\"". $row->artikel_id."\"]".$row->artikel_headline."[/artikel]</td>";
            echo "</tr>\n";
      	 //}   
     }
	 mysql_free_result($result);
   }
}
echo "</table>\n";

function createsel_pagenCAs($select_name,$grouplist){
   global $conf, $lang;

   $allgroups = dbquery("select page_id, page_name from ".$conf["db_namespace"]."pages Where page_childs = 'A' order by page_name");
   echo "<select name=" . $select_name . ">";
   if ( mysql_num_rows($allgroups) > 0 )      {
      while ( $g_row = mysql_fetch_object($allgroups) )         {
         echo "<option value=" . $g_row->page_id;
         if ( eregi ( $g_row->page_id, $grouplist ) ){            echo " selected ";}
         echo ">" . $g_row->page_name . "</option>";
      }
      mysql_free_result($allgroups);
   }
   echo "</select>";
   return;
}
?>