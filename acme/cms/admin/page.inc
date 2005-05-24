<?php

include($conf["admbase"] . "/lang/page." . $conf["lang"] . ".inc");

switch($action) {
	
   case "edit":
      pagedit($id);
      break;
   case "new":
       pagenew($new_page_name, $new_page_tpl, $new_page_parent, $new_page_img_small, $new_page_img_small_inactive, $new_page_img_big, $new_page_titelbild, $new_page_left_bar, $new_page_right_bar, $new_page_top_bar, $new_page_foo_bar, $new_page_headline, $new_page_short_text, $new_page_long_text, $new_page_long_text_typ, $new_page_author_id,  $new_page_childs,$new_page_comments);
       break;
   case "add":
       $error = 0;
       if ($new_page_name==""){
       	  $errortext .= $lang["page_name_fehlt"]."<br>";
          $error = 1;
       }	
       if ($new_page_tpl == ""){
       	  $errortext .= $lang["page_tpl_fehlt"]."<br>";
          $error = 1;
       }
       if ($error==0) { 	
          pageadd($new_page_name, $new_page_tpl, $new_page_parent, $new_page_img_small,$new_page_img_small_inactive, $new_page_img_big, $new_page_titelbild, $new_page_left_bar, $new_page_right_bar, $new_page_top_bar, $new_page_foo_bar, $new_page_headline, $new_page_short_text, $new_page_long_text, $new_page_long_text_typ, $new_page_author_id,  $new_page_childs,$new_page_comments);
          pagebrowse();
       }
       else{ 
       	  echo $errortext;
       	  pagenew($new_page_name, $new_page_tpl, $new_page_parent, $new_page_img_small,$new_page_img_small_inactive, $new_page_img_big, $new_page_titelbild, $new_page_left_bar, $new_page_right_bar, $new_page_top_bar, $new_page_foo_bar, $new_page_headline, $new_page_short_text, $new_page_long_text, $new_page_long_text_typ, $new_page_author_id,  $new_page_childs,$new_page_comments);
       }	   
       break;
   case "update":
       pageupdate($edit_page_id, $edit_page_name, $edit_page_tpl, $edit_page_parent,$edit_page_img_small, $edit_page_img_small_inactive,$edit_page_img_big, $edit_page_titelbild, $edit_page_left_bar, $edit_page_right_bar, $edit_page_top_bar, $edit_page_foo_bar, $edit_page_headline, $edit_page_short_text, $edit_page_long_text, $edit_page_long_text_typ, $edit_page_author_id, $edit_page_childs,$edit_page_comments);
       pagebrowse();
       break;
   case "delete":
       pagedeletequest($delete_id);  
       break;
   case "dodelete":
       pagedelete($delete_id);
       pagebrowse();       
       break;
   default:
       pagebrowse();       
       break;
}

function pagedeletequest($id){
   global $conf, $lang;
   
   $result = dbquery("select * from ".$conf["db_namespace"]."pages where page_id='" . $id . "'");
   if ($result) {
      $row = mysql_fetch_array($result);
      echo "<h1>".$lang["page_delete_quest"]."</h1>";
      echo "<h2>". $row["page_name"] ."</h2>";
      echo "<form action=\"" . $conf["admp"] . "&section=page&action=dodelete\" ENCTYPE=\"multipart/form-data\" method=POST>";
      echo "<input type=hidden name=delete_id value=\"" . $row["page_id"] . "\">";
      echo "<input type=submit name=delete_page value=".$lang["page_loeschen"].">";
      echo "<input type=reset name=delete_page value=".$lang["page_cancel"].">";
      echo "</form>";
   }
}   

function pageadd($new_page_name, $new_page_tpl, $new_page_parent, $new_page_img_small, $new_page_img_small_inactive, $new_page_img_big, $new_page_titelbild, $new_page_left_bar, $new_page_right_bar, $new_page_top_bar, $new_page_foo_bar, $new_page_headline, $new_page_short_text, $new_page_long_text, $new_page_long_text_typ, $new_page_author_id, $new_page_childs,$new_page_comments){
   global $conf, $lang;
   $Statement = "INSERT INTO ".$conf["db_namespace"]."pages SET".
                " page_name = '". $new_page_name . "',".
                " page_tpl = '". $new_page_tpl . "', ".
                " page_parent = '". $new_page_parent . "',".
                " page_img_small = '". $new_page_img_small . "',".
                " page_img_small_inactive = '". $new_page_img_small_inactive . "',".                
                " page_img_big = '". $new_page_img_big . "',".
                " page_titelbild = '". $new_page_titelbild . "',".                
                " page_left_bar = '". $new_page_left_bar . "',".
                " page_right_bar = '". $new_page_right_bar . "',".
                " page_top_bar = '". $new_page_top_bar . "',".
                " page_foo_bar = '". $new_page_foo_bar . "',".
                " page_headline = '". $new_page_headline . "',".
                " page_short_text = '". $new_page_short_text . "',".
                " page_long_text = '". $new_page_long_text . "',".
                " page_long_text_typ = '". $new_page_long_text_typ . "',".
                " page_author_id = '" . $conf["author_id"] ."',".                
                " page_childs = '". $new_page_childs . "',".
                " page_create_date = NOW(),".
                " page_modify_date = NOW(),".                
                " page_comments = '". $new_page_comments . "'";
   $my_result = dbquery($Statement);
   if ($my_result) {
      $modulid = mysql_insert_id();
      acl_user_set($conf["author_id"], "page", $modulid, "Y", "Y", "Y", "Y");
      acl_group_set($conf["author_groups"], "page", $modulid, "Y", "Y", "Y", "Y");
      echo $lang["page_insert_erfolgreich"];   
   }
   else {echo $lang["page_insert_fehlerhaft"];}
}
function pageupdate($edit_page_id, $edit_page_name, $edit_page_tpl, $edit_page_parent, $edit_page_img_small, $edit_page_img_small_inactive, $edit_page_img_big, $edit_page_titelbild, $edit_page_left_bar, $edit_page_right_bar, $edit_page_top_bar, $edit_page_foo_bar, $edit_page_headline, $edit_page_short_text, $edit_page_long_text, $edit_page_long_text_typ, $edit_page_author_id, $edit_page_childs,$edit_page_comments){
   global $conf, $lang;
              
   $Statement = "UPDATE ".$conf["db_namespace"]."pages SET".
                " page_name = '". $edit_page_name . "',".
                " page_tpl = '". $edit_page_tpl . "', ".
                " page_parent = '". $edit_page_parent . "',".
                " page_img_small = '". $edit_page_img_small . "',".
                " page_img_small_inactive = '". $edit_page_img_small_inactive . "',".                
                " page_img_big = '". $edit_page_img_big . "',".
                " page_titelbild = '". $edit_page_titelbild . "',".                
                " page_left_bar = '". $edit_page_left_bar . "',".
                " page_right_bar = '". $edit_page_right_bar . "',".
                " page_top_bar = '". $edit_page_top_bar . "',".
                " page_foo_bar = '". $edit_page_foo_bar . "',".
                " page_headline = '". $edit_page_headline . "',".
                " page_short_text = '". $edit_page_short_text . "',".
                " page_long_text = '". $edit_page_long_text . "',".
                " page_long_text_typ = '". $edit_page_long_text_typ . "',".
                " page_childs = '". $edit_page_childs . "',".
                " page_modify_date = NOW(),".
                " page_comments = '". $edit_page_comments . "'".
                " WHERE page_id = '". $edit_page_id . "'";
   $my_result = dbquery($Statement);
   if ($my_result) {echo $lang["page_update_erfolgreich"];}
  else            {echo $lang["page_update_fehlerhaft"];}
}
function pagedelete($delete_id){
   global $conf, $lang;
   $my_result = dbquery("delete from ".$conf["db_namespace"]."pages where page_id = '". $delete_id . "'");
   if ($my_result) {
   	  acl_delete("page", $delete_id);
   	  echo $lang["page_delete_erfolgreich"];
   }
   else            {echo $lang["page_delete_fehlerhaft"];}
}


function pagenew($new_page_name, $new_page_tpl, $new_page_parent, $new_page_img_small,$new_page_img_small_inactive, $new_page_img_big, $new_page_titelbild, $new_page_left_bar, $new_page_right_bar, $new_page_top_bar, $new_page_foo_bar, $new_page_headline, $new_page_short_text, $new_page_long_text, $new_page_long_text_typ, $new_page_author_id,  $new_page_childs,$new_page_comments){
   global $conf, $lang;

   if ($new_page_long_text_typ=="")$new_page_long_text_typ = "B";

   echo "<h1>".$lang["page_neu"]."</h1>";
   echo "<form name = \"page_new\" id = \"page_new\" action=\"" . $conf["admp"] . "&section=page&action=add\" ENCTYPE=\"multipart/form-data\" method=\"POST\">";
   echo "<table  class=\"reda_td\">";
   echo "<tr><td colspan=3>".$lang["page_name"]."</td><td>".$lang["page_parent"]."</td><td>".$lang["page_childs"]."</td></tr>";
   echo "<tr>";
   echo "<td colspan=3><input name=new_page_name size=45 maxlength=59 value = \"" . htmlspecialchars(stripslashes($new_page_name)) . "\"></td>";
   echo "<td colspan=1>";
   createsel_pagenCPs("new_page_parent", $new_page_parent);
   echo "</td>";
   echo "<td>";
   createsel_childs("new_page_childs", $new_page_childs);
   echo "</td>";
   echo "</tr>";
   echo "<tr><td colspan=5>&nbsp;</td></tr>\n";   
   echo "<tr><td>".$lang["page_frame"]."</td><td>".$lang["page_bar_left"]."</td><td>".$lang["page_bar_right"]."</td><td>".$lang["page_bar_top"]."</td><td>".$lang["page_bar_bottom"]."</td></tr>";
   echo "<tr>";
   echo "<td>";
   echo "&nbsp;";  // createsel_frame("new_page_frame", $new_page_frame);
   echo "</td>";
   echo "<td>";
   createsel_bar("new_page_left_bar", $new_page_left_bar);
   echo "</td>";
   echo "<td>";
   createsel_bar("new_page_right_bar", $new_page_right_bar);
   echo "</td>";
   echo "<td>";
   createsel_bar("new_page_top_bar", $new_page_top_bar);
   echo "</td>";
   echo "<td>";
   createsel_bar("new_page_foo_bar", $new_page_foo_bar);
   echo "</td>";
   echo "</tr>";
   echo "<tr><td colspan=5>&nbsp;</td></tr>\n";
   echo "<tr><td>".$lang["page_tpl"]."</td><td>".$lang["page_titelbild"]."</td><td>".$lang["page_logo_klein"]."</td><td>".$lang["page_logo_klein_inactive"]."</td><td>".$lang["page_logo_gross"]."</td></tr>";
   echo "<tr>";
   echo "<td>";
   if ($new_page_tpl=="") {$new_page_tpl = $conf["home_tpl"];}
   createsel_tpl("new_page_tpl", $new_page_tpl);
   echo "</td>";
   echo "<td>";
   createsel_img("new_page_img_small",  $new_page_img_small);
   echo "</td>";
   echo "<td>";
   createsel_img("new_page_img_small_inactive",  $new_page_img_small_inactive);
   echo "</td>";
   echo "<td>";
   createsel_img("new_page_img_big",  $new_page_img_big);
   echo "</td>";
   echo "<td>";
   createsel_img("new_page_titelbild",  $new_page_titelbild);
   echo "</td>";   
   echo "</tr>";
   echo "<tr><td colspan=5>&nbsp;</td></tr>\n";
   echo "<tr><td colspan=4>".$lang["page_ueberschrift"]."</td><td>".$lang["page_langtexttyp"]."</td></tr>";
   echo "<tr><td colspan=4><input name=new_page_headline size=75 maxlength=127 value = \"" . htmlspecialchars(stripslashes($new_page_headline)) . "\"></td>";
   echo "<td colspan = 1>";
   createsel_ltt("new_page_long_text_typ",$new_page_long_text_typ);
   echo "</td>";
   echo "</tr>";
   echo "<tr><td colspan=5>".$lang["page_kurztext"]."</td></tr>";
   echo "<tr><td colspan=5>";
   write_bbc("page_new", "new_page_short_text");
   echo "<textarea name=new_page_short_text id=new_page_short_text wrap=virtual rows=5 cols=75>" . htmlspecialchars(stripslashes($new_page_short_text)) . "</textarea>\n";
   echo "</td></tr>";
   echo "<tr><td colspan=5>&nbsp;</td></tr>\n";
   echo "<tr><td colspan=5>".$lang["page_langtext"]."</td></tr>\n";
   echo "<tr><td colspan=5>";
   write_bbc("page_new", "new_page_long_text");
   echo "<textarea name=new_page_long_text id=new_page_long_text wrap=virtual rows=15 cols=75>" . htmlspecialchars(stripslashes($new_page_long_text)) . "</textarea>\n";
   echo "</td></tr>\n";
   echo "<tr><td colspan=3>&nbsp;</td><td><input type=submit name=edit_page value=".$lang["page_speichern"]."></td><td><input type=reset name=edit_page value=".$lang["page_verwerfen"]."></td></tr>\n";
   echo "</table>\n";
   echo "</form>\n";
}
function pagedit($id){
   global $conf, $lang;
   $result = dbquery("select * from ".$conf["db_namespace"]."pages where page_id='" . $id . "'");
   if ($result) {
      $row = mysql_fetch_array($result);
      echo "<h1>".$lang["page_bearbeiten"]."</h1>";
      echo "<form name = \"page_edit\" id = \"page_edit\" action=\"" . $conf["admp"] . "&section=page&action=update\" ENCTYPE=\"multipart/form-data\" method=POST>";
      echo "<input type=hidden name=edit_page_id value=\"" . $row["page_id"] . "\">";
      echo "<table  class=\"reda_td\">";
      echo "<tr><td colspan = 3>".$lang["page_name"]."</td><td>".$lang["page_parent"]."</td><td>".$lang["page_childs"]."</td></tr>";
      echo "<tr>";
      echo "<td colspan = 3><input name=edit_page_name size=45 maxlength=59 value = \"" . htmlspecialchars($row["page_name"]) . "\"></td>";
      echo "<td>";
      createsel_pagenCPs("edit_page_parent", $row["page_parent"]);
      echo "</td>";
      echo "<td>";
      createsel_childs("edit_page_childs", $row["page_childs"]);
      echo "</td>";      
      echo "</tr>";
      echo "<tr><td colspan = 5>&nbsp;</td></tr>";
      echo "<tr><td>".$lang["page_frame"]."</td><td>".$lang["page_bar_left"]."</td><td>".$lang["page_bar_right"]."</td><td>".$lang["page_bar_top"]."</td><td>".$lang["page_bar_bottom"]."</td></tr>";
      echo "<tr>";
      echo "<td>";
      echo "&nbsp;"; // createsel_frame("edit_page_frame", $row["page_frame"]);
      echo "</td>";
      echo "<td>";
      createsel_bar("edit_page_left_bar", $row["page_left_bar"]);
      echo "</td>";
      echo "<td>";
      createsel_bar("edit_page_right_bar",  $row["page_right_bar"]);
      echo "</td>";
      echo "<td>";
      createsel_bar("edit_page_top_bar",  $row["page_top_bar"]);
      echo "</td>";
      echo "<td>";
      createsel_bar("edit_page_foo_bar",  $row["page_foo_bar"]);
      echo "</td>";
      echo "</tr>\n";
      echo "<tr><td colspan=5>&nbsp;</td></tr>\n";   
      echo "<tr><td>".$lang["page_tpl"]."</td><td>".$lang["page_logo_klein"]."</td><td>".$lang["page_logo_klein_inactive"]."</td><td>".$lang["page_logo_gross"]."</td><td>".$lang["page_titelbild"]."</td></tr>";
      echo "<tr>";
      echo "<td>";
      createsel_tpl("edit_page_tpl",  $row["page_tpl"]);
      echo "</td>";
      echo "<td>";
      createsel_img("edit_page_img_small",  $row["page_img_small"]);
      echo "</td>";
      echo "<td>";
      createsel_img("edit_page_img_small_inactive",  $row["page_img_small_inactive"]);
      echo "</td>";
      echo "<td>";
      createsel_img("edit_page_img_big",  $row["page_img_big"]);
      echo "</td>";
      echo "<td>";
      createsel_img("edit_page_titelbild",  $row["page_titelbild"]);
      echo "</td>";      
      echo "</tr>\n";
      echo "<tr><td colspan=5>&nbsp;</td></tr>\n";      
      echo "<tr><td colspan=4>".$lang["page_ueberschrift"]."</td><td>".$lang["page_langtexttyp"]."</td></tr>\n";
      echo "<tr><td colspan=4><input name=edit_page_headline size=70 maxlength=127 value = \"" . htmlspecialchars($row["page_headline"]) . "\"></td>\n";
      echo "<td colspan = 1>";
      createsel_ltt("edit_page_long_text_typ",$row["page_long_text_typ"]);
      echo "</td></tr>\n";      
      echo "<tr><td colspan=5>".$lang["page_kurztext"]."</td></tr>\n";
      echo "<tr><td colspan=5>";
      write_bbc("page_edit", "edit_page_short_text");
      echo "<textarea name=edit_page_short_text wrap=virtual rows=5 cols=75>" . htmlspecialchars($row["page_short_text"]) . "</textarea>\n";
      echo "</td></tr>\n";
      echo "<tr><td colspan=5>".$lang["page_langtext"]."</td></tr>\n";
      echo "<tr><td colspan=5>";
      write_bbc("page_edit", "edit_page_long_text");
      echo "<textarea name=edit_page_long_text wrap=virtual rows=15 cols=75>" . htmlspecialchars($row["page_long_text"]) . "</textarea>\n";
      echo "</td></tr>\n";
      echo "<tr><td colspan=3 class=\"button_td_submit\"></td><td><input type=submit name=edit_page value=".$lang["page_speichern"]."></td><td><input type=reset name=edit_page value=".$lang["page_verwerfen"]."></td></tr>\n";
      echo "</table>\n";
      echo "</form>\n";
      mysql_free_result($result);
   }
}   

function pagebrowse(){
   global $conf, $lang;

   echo "<h1>".$lang["page_verwaltung"]."</h1>\n";
   if (acl_check("insert", $conf["author_groups"], $conf["author_id"], "page", 0) == 1) {
      echo "<a href=\"". $conf["admp"] . "&section=page&action=new\">".$lang["page_neu"]."</a>\n";
   }
   echo "<table class=\"reda_td\">\n";
   echo "<th><tr><td>".$lang["page_id"]."</td><td>".$lang["page_name"]."</td><td>".$lang["page_ueberschrift"]."</td><td>".$lang["page_erstellt"]."</td><td>".$lang["page_geaendert"]."</td><td>".$lang["page_autor"]."</td><td>".$lang["page_counter"]."</td><td>".$lang["page_childs"]."</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td></tr></th>\n";
   writepagechilds($parent,$h_level);
   echo "</table>";
}      

function writepagechilds($parent, &$h_level){
   global $conf, $lang;
   
   $result = dbquery("select * from ".$conf["db_namespace"]."pages where  page_parent = '" . $parent . "' order by page_name");
   if ( mysql_num_rows($result) > 0 ){
      while ($row = mysql_fetch_object($result)){
         echo "<tr><td>" . $row->page_id . "</td>";
         echo "<td>";
         for ($count = 0;$count < $h_level; $count++){echo "-";}
         echo "<a href=\"" . $conf["indexname"] . "page/".$row->page_id."\" target=\"new_window\">".$row->page_name."</a></td>";
         echo "<td>". $row->page_headline."</td>";
         echo "<td>". mydate2date($row->page_create_date) ."</td>";         
         echo "<td>". mydate2date($row->page_modify_date) ."</td>";
         echo "<td>". getauthorbyid($row->page_author_id) ."</td>";
         echo "<td>". $row->page_counter."</td>";
         echo "<td>". $row->page_childs."</td>";         
         echo "<td>";
         if (acl_check("edit", $conf["author_groups"], $conf["author_id"], "page", $row->page_id) == 1) {
            echo "<a href=" . $conf["admp"] . "&action=edit&section=page&id=".$row->page_id."><img src=\"" . $conf["images_admin"] . "icon_edit.png\" width=\"25\" height=\"25\"></a>";       
         }
         echo "</td>";
         echo "<td>";
         if (acl_check("delete", $conf["author_groups"], $conf["author_id"], "page", $row->page_id) == 1) {
            if (checkpagechilds($row->page_id, $row->page_childs) == 0){
               echo "<a href=" . $conf["admp"] . "&section=page&action=delete&delete_id=".$row->page_id."><img src=\"" . $conf["images_admin"] . "icon_delete.png\" width=\"25\" height=\"25\"></a>";      			
            } else {echo "&nbsp;";}
         } else {echo "&nbsp;";}
         echo "</td>";
         echo "<td>";
         if (acl_check("rights", $conf["author_groups"], $conf["author_id"], "page", $row->page_id) == 1) {
            echo "<a href=" . $conf["admp"] . "&section=rights&modul_name=page&modul_id=".$row->page_id."><img src=\"" . $conf["images_admin"] . "icon_rights.png\" width=\"25\" height=\"25\"></a>";      			
         } else {echo "&nbsp;";}
         echo "</td>";
         echo "</tr>\n";
         $h_level++;
         writepagechilds($row->page_id, $h_level);
         $h_level--;
      }
      mysql_free_result($result);
   }
}   
function checkpagechilds($parent, $typ){
   global $conf, $lang;
   
   $childs = 0;
   if ($typ <> "N"){
      if ($typ == "P"){$result = dbquery("select * from ".$conf["db_namespace"]."pages   where page_parent  = '" . $parent . "'");}
      if ($typ == "A"){$result = dbquery("select * from ".$conf["db_namespace"]."artikel where artikel_page like '%:" . $parent . ":%'");}
      if ( mysql_num_rows($result) > 0 ){$childs = 1;}
      mysql_free_result($result);
   }
   return $childs;   
}      
function createsel_childs($select_name,$grouplist) {
   global $conf, $lang;

   echo "<select name=\"" . $select_name . "\">";
   echo "<option";
   if ($grouplist == "N" || $grouplist == ""){echo " selected";};
   echo " value=\"N\">".$lang["page_child_none"]."</option>";
   echo "<option";
   if ($grouplist == "P"){echo " selected";};
   echo " value=\"P\">".$lang["page_child_page"]."</option>";
   echo "<option";
   if ($grouplist == "A"){echo " selected";};
   echo " value=\"A\">".$lang["page_child_artikel"]."</option>";
   return;
}
function createsel_ltt($select_name,$grouplist)
{
   global $conf, $lang;
   echo "<select name=\"" . $select_name . "\">";
   echo "<option";
   if ($grouplist == "B"){echo " selected";};
   echo " value=\"B\">BBC</option>";
   echo "<option";
   if ($grouplist == "P"){echo " selected";};
   echo " value=\"P\">PHP</option>";
   echo "<option";
   if ($grouplist == "H" || $grouplist == ""){echo " selected";};
   echo " value=\"H\">HTML</option>";
   echo "</select>";
   return;
}
function createsel_pagenCPs($select_name,$grouplist){
   global $conf, $lang;

   echo "<select name=" . $select_name . ">";
   echo "<option value= \"\"></option>";
   getpages4select($parent, &$h_level, $grouplist);
   echo "</select>";
   return;
}
function getpages4select($parent, &$h_level, $grouplist){
   global $conf, $lang;
   
   $result = dbquery("select * from ".$conf["db_namespace"]."pages where page_childs = 'P' and page_parent = '" . $parent . "' order by page_name");
   if ( mysql_num_rows($result) > 0 ){
      while ($row = mysql_fetch_object($result)){
      	 echo "<option value=" . $row->page_id;
         if ( eregi ( $row->page_id, $grouplist ) ){echo " selected ";}
         if (acl_check("insert", $conf["author_groups"], $conf["author_id"], "page", $row->page_id) == 1) {
            echo ">";
         } else {
         	echo " disabled style = \"color:gray;font-style:italic;\">";
         }	
         for ($count = 0;$count < $h_level; $count++){echo "-";} 
         echo $row->page_name . "</option>";
         $h_level++;
         getpages4select($row->page_id, $h_level, $grouplist);
         $h_level--;
      }
      mysql_free_result($result);
   }
}   
?>



