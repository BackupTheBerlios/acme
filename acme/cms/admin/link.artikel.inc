<?php

include($conf["admbase"] . "/lang/artikel." . $conf["lang"] . ".inc");

echo "<form action=\"admin/link.php?modul=artikel\" method=\"post\">";
echo "<table class=\"reda_td\" border = 1 cellpadding = 0 cellspacing = 0>\n";
echo "<tr><td>" . $lang["artikel_der_seite"] ."</td><td>";
createsel_pagenCAs("page_id", $page_id); 
echo "</td><td><input type=\"submit\" value=\"" . $lang["artikel_anzeigen"] . "\"></td></tr>\n";
echo "<tr><td>" . $lang["artikel_des_autors"] . "</td><td colspan = \"2\">";
createsel_author("author_id", $author_id); 
echo "</td></tr>\n";
echo "<tr><td>" . $lang["artikel_des_users"] . "</td><td colspan = \"2\">";
createsel_user("user_id", $user_id); 
echo "</td></tr>\n";
echo "</table>\n";
echo "</form>\n";
echo "<table  class=\"reda_td\" border = 1 cellpadding = 0 cellspacing = 0>\n";
if ($page_id <> ""){
   echo "<tr><td>".$lang["artikel_id"] . "</td><td>".$lang["artikel_ueberschrift1"] . "</td><td>".$lang["artikel_veroeffentlichungsdatum"] . "</td><td>".$lang["artikel_seite"] . "</td><td>".$lang["artikel_autor"] . "</td><td>".$lang["artikel_user"] . "</td><td>".$lang["artikel_counter"] . "</td><td>".$lang["artikel_link"] . "</td></tr>\n";
   $Statement = "select * from acme_artikel where artikel_page like '%:" . $page_id . ":%'";
   if ($author_id <> ""){ $Statement .= " and artikel_author_id = '" . $author_id . "'";}
   if ($user_id <> ""){ $Statement .= " and artikel_user_id = '" . $user_id . "'";}
   $Statement .= " order by artikel_publish_date DESC";
   $result = dbquery($Statement);
   if ( mysql_num_rows($result) > 0 ){
      while ($row = mysql_fetch_object($result)){
         $artikelpage = explode(":", $row->artikel_page);
         $artikelpage = $artikelpage[1];
         echo "<td>". $row->artikel_id . "</td>";
         echo "<td>".$row->artikel_headline."</td>";
 		 echo "<td>". mydate2datetime($row->artikel_publish_date) ."</td>";
		 echo "<td>". getpagenamebyidarray($row->artikel_page)."</td>";
         echo "<td>". getauthorbyid($row->artikel_author_id) ."</td>";
         echo "<td>". getuserbyid($row->artikel_user_id) ."</td>";                  
         echo "<td>". $row->artikel_counter."</td>";
         echo "<td>[artikel=\"". $row->artikel_id."\"]".$row->artikel_headline."[/artikel]</td>";
         echo "</tr>\n";
		 }
	 mysql_free_result($result);
    }
}
echo "</table>\n";

function createsel_pagenCAs($select_name,$grouplist){
   global $conf, $lang;

   $allgroups = dbquery("select page_id, page_name from acme_pages Where page_childs = 'A' order by page_name");
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