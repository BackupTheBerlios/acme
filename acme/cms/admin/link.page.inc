<?php
include($conf["admbase"] . "/lang/page." . $conf["lang"] . ".inc");

echo "<table class=\"reda_td\" border = 1 cellpadding = 0 cellspacing = 0>";
echo "<th><tr><td>".$lang["page_name"]."</td><td>".$lang["page_ueberschrift"]."</td><td>".$lang["page_erstellt"]."</td><td>".$lang["page_geaendert"]."</td><td>".$lang["page_autor"]."</td><td>".$lang["page_user"]."</td><td>".$lang["page_counter"]."</td><td>".$lang["page_childs"]."</td><td>".$lang["page_link"]."</td></tr></th>\n";

writepagechilds($parent,$h_level);
echo "</table>";

function writepagechilds($parent, &$h_level){
   global $conf, $lang;
   $result = dbquery("select * from acme_pages where  page_parent = '" . $parent . "' order by page_name");
   if ( mysql_num_rows($result) > 0 ){
      while ($row = mysql_fetch_object($result)){
         echo "<tr>";
         echo "<td>";
         for ($count = 0;$count < $h_level; $count++){echo "-";}
         echo $row->page_name."</td>";
         echo "<td>". $row->page_headline."</td>";
         echo "<td>". mydate2date($row->page_create_date) ."</td>";         
         echo "<td>". mydate2date($row->page_modify_date) ."</td>";
         echo "<td>". getauthorbyid($row->page_author_id) ."</td>";
         echo "<td>". getuserbyid($row->page_user_id) ."</td>";                  
         echo "<td>". $row->page_counter."</td>";
         echo "<td>". $row->page_childs."</td>";
         echo "<td>[page=\"". $row->page_id. "\"]". $row->page_headline."[/page]</td>";                  
         echo "</tr>\n";
         $h_level++;
         writepagechilds($row->page_id, $h_level);
         $h_level--;
      }
      mysql_free_result($result);
   }
}
?>