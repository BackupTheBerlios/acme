<?php
include($conf["admbase"] . "/lang/urls." . $conf["lang"] . ".inc");

switch($action){
   case "edit_url":
      url_edit($id);
      break;
   case "edit_url_typ":
      url_typ_edit($id);
      break;
   case "new_url":
       url_new($new_url_name, $new_url_url, $new_url_text, $new_url_typ);
       break;
   case "new_url_typ":
       url_typ_new($new_url_typ_name, $new_url_typ_text, $new_url_typ_parent_id, $new_url_typ_tpl, $new_url_typ_img_small, $new_url_typ_img_small_inactive,  $new_url_typ_img_big, $new_url_typ_left_bar, $new_url_typ_right_bar, $new_url_typ_topbar, $new_url_typ_foo_bar);
       break;
   case "add_url":
       if (count($new_url_typ) == 0){
          echo $lang["urls_eintrag_urlerror"];
          url_new($new_url_name, $new_url_url, $new_url_text, $new_url_typ);
       }
       else {
       	url_add($new_url_name, $new_url_url, $new_url_text, $new_url_typ);
       	url_browse();
       }
       break;
   case "add_url_typ":
       url_typ_add($new_url_typ_name, $new_url_typ_text, $new_url_typ_parent_id, $new_url_typ_tpl, $new_url_typ_img_small, $new_url_typ_img_small_inactive,  $new_url_typ_img_big, $new_url_typ_left_bar, $new_url_typ_right_bar, $new_url_typ_top_bar, $new_url_typ_foo_bar);
       url_browse();
       break;
   case "update_url":
       if (count($edit_url_typ) == 0){
          echo $lang["urls_eintrag_urlerror"];
          url_edit($edit_url_id);
       }   
       else {   
          url_update($edit_url_id, $edit_url_name, $edit_url_url, $edit_url_text, $edit_url_typ );
       }   
       url_browse();
       break;
   case "update_url_typ":
       url_typ_update($edit_url_typ_id, $edit_url_typ_name, $edit_url_typ_text, $edit_url_typ_parent_id, $edit_url_typ_tpl, $edit_url_typ_img_small, $edit_url_typ_img_small_inactive, $edit_url_typ_img_big, $edit_url_typ_left_bar, $edit_url_typ_right_bar, $edit_url_typ_top_bar, $edit_url_typ_foo_bar);
       url_browse();
       break;
   case "delete_url":
       url_delete($delete_id);
       url_browse();       
       break;
   case "delete_url_typ":
       url_typ_delete($delete_id);
       url_browse();       
       break;
   default:
       url_browse();       
       break;
}

function url_add($new_url_name, $new_url_url, $new_url_text, $new_url_typ ){
   global $conf, $lang;
              
   $Statement = "INSERT INTO ".$conf["db_namespace"]."url SET".
                " url_name = '". $new_url_name . "',".
                " url_url  = '". $new_url_url . "', ".
                " url_text = '". $new_url_text . "',".
                " url_typ  = '". joingrouparray($new_url_typ) . "'";
   $my_result = dbquery($Statement);

   if ($my_result) {echo $lang["urls_eintrag_insert_erfolgreich"];}
   else            {echo $lang["urls_eintrag_insert_fehlgeschlagen"];}
}

function url_typ_add($new_url_typ_name, $new_url_typ_text, $new_url_typ_parent_id, $new_url_typ_tpl, $new_url_typ_img_small,$new_url_typ_img_small_inactive,  $new_url_typ_img_big, $new_url_typ_left_bar, $new_url_typ_right_bar, $new_url_typ_top_bar, $new_url_typ_foo_bar){
   global $conf, $lang;
              
   $Statement = "INSERT INTO ".$conf["db_namespace"]."url_typs SET".
                " url_typ_name = '". $new_url_typ_name . "',".
                " url_typ_text = '". $new_url_typ_text . "',".
                " url_typ_tpl = '". $new_url_typ_tpl . "',".
                " url_typ_img_small = '". $new_url_typ_img_small . "',".
                " url_typ_img_small_inactive = '". $new_url_typ_img_small_inactive . "',".
                " url_typ_img_big = '". $new_url_typ_img_big . "',".
                " url_typ_author_id = '". $conf["author_id"] . "',".
                " url_typ_create_date = NOW(),".
                " url_typ_modify_date = NOW(),".
                " url_typ_left_bar = '". $new_url_typ_left_bar . "',".
                " url_typ_right_bar = '". $new_url_typ_right_bar . "',".
                " url_typ_top_bar = '". $new_url_typ_top_bar . "',".
                " url_typ_foo_bar = '". $new_url_typ_foo_bar . "',".
                " url_typ_parent_id = '". $new_url_typ_parent_id . "'";

  $my_result = dbquery($Statement);
   
   if ($my_result) {
   	  $modulid = mysql_insert_id();
      acl_user_set($conf["author_id"], "urls", $modulid, "Y", "Y", "Y", "Y");
      acl_group_set($conf["author_groups"], "urls", $modulid, "Y", "Y", "Y", "Y");
      echo $lang["urls_insert_erfolgreich"];
   }
   else {echo $lang["urls_insert_fehlgeschlagen"];}
}    

function url_update($edit_url_id, $edit_url_name, $edit_url_url, $edit_url_text, $edit_url_typ ){
   global $conf, $lang;
              
   $Statement = "UPDATE ".$conf["db_namespace"]."url SET".
                " url_name = '". $edit_url_name . "',".
                " url_url = '". $edit_url_url . "', ".
                " url_text = '". $edit_url_text . "',".
                " url_typ = '". joingrouparray($edit_url_typ) . "'".
                " WHERE url_id = '". $edit_url_id . "'";
   $my_result = dbquery($Statement);
   if ($my_result) {echo $lang["urls_eintrag_update_erfolgreich"];}
  else            {echo $lang["urls_eintrag_update_fehlgeschlagen"];}
}

function url_typ_update($edit_url_typ_id, $edit_url_typ_name, $edit_url_typ_text, $edit_url_typ_parent_id, $edit_url_typ_tpl, $edit_url_typ_img_small,$edit_url_typ_img_small_inactive,  $edit_url_typ_img_big, $edit_url_typ_left_bar, $edit_url_typ_right_bar, $edit_url_typ_top_bar, $edit_url_typ_foo_bar){
   global $conf, $lang;
              
   $Statement = "UPDATE ".$conf["db_namespace"]."url_typs SET".
                " url_typ_name = '". $edit_url_typ_name . "',".
                " url_typ_text = '". $edit_url_typ_text . "',".
                " url_typ_tpl = '". $edit_url_typ_tpl . "',".
                " url_typ_img_small = '". $edit_url_typ_img_small . "',".
                " url_typ_img_small_inactive = '". $edit_url_typ_img_small_inactive . "',".
                " url_typ_img_big = '". $edit_url_typ_img_big . "',".
                " url_typ_modify_date = NOW(),".
                " url_typ_left_bar = '". $edit_url_typ_left_bar . "',".
                " url_typ_right_bar = '". $edit_url_typ_right_bar . "',".
                " url_typ_top_bar = '". $edit_url_typ_top_bar . "',".
                " url_typ_foo_bar = '". $edit_url_typ_foo_bar . "',".
                " url_typ_parent_id = '". $edit_url_typ_parent_id . "'".
                " WHERE url_typ_id = '". $edit_url_typ_id . "'";
   $my_result = dbquery($Statement);
   if ($my_result) {
   	  echo $lang["urls_update_erfolgreich"];
   }
   else {
   	  echo $lang["urls_update_fehlgeschlagen"];
   }
}
  
function url_delete($delete_id) {
   global $conf, $lang;
   $my_result = dbquery("delete from ".$conf["db_namespace"]."url where url_id = '". $delete_id . "'");
   if ($my_result) {echo $lang["urls_eintrag_delete_erfolgreich"];}
   else            {echo $lang["urls_eintrag_delete_fehlgeschlagen"];}
}

function url_typ_delete($delete_id){
   global $conf, $lang;
   $my_result = dbquery("delete from ".$conf["db_namespace"]."url_typs where url_typ_id = '". $delete_id . "'");
   if ($my_result) {
   	  acl_delete("urls", $delete_id);
      echo $lang["urls_delete_erfolgreich"];
   }
   else            {echo $lang["urls_delete_fehlgeschlagen"];}
}
   
function url_browse() {
   global $conf, $lang;
   
   $parent = 0;
   $h_level = 0;
   echo "<h1>".$lang["urls_verwaltung"]."</h1>\n";
   if (acl_check("insert", $conf["author_groups"], $conf["author_id"], "urls", 0) == 1) {
      echo "<a href=\"". $conf["admp"] . "&section=urls&action=new_url_typ\">".$lang["urls_anlegen"]."</a><br>\n";
      echo "<a href=\"". $conf["admp"] . "&section=urls&action=new_url\">".$lang["urls_eintrag_anlegen"]."</a>\n";
   }
   echo "<table class=\"reda_td\">\n";
   echo "<th><tr><td>".$lang["urls_titel"]."</td><td>".$lang["urls_counter"]."</td></tr><td> </td><td> </td>\n";
   writeurltypchilds($parent,$h_level);
   echo "</table>";
}      

function url_new($new_url_name, $new_url_url, $new_url_text, $new_url_typ){
   global $conf, $lang;

   echo "<h1>".$lang["urls_eintrag_anlegen"]."</h1>";
   echo "<form name = new_url action=\"" . $conf["admp"] . "&section=urls&action=add_url\" ENCTYPE=\"multipart/form-data\" method=\"POST\">";
   echo "<table  class=\"reda_td\">";
   echo "<tr><td colspan = \"4\">".$lang["urls_eintrag_titel"]."</td></tr>";
   echo "<tr><td colspan = \"4\"><input name=new_url_name size=45 maxlength=128 value = \"" . htmlspecialchars(stripslashes($new_url_name)) . "\"></td></tr>";
   echo "<tr><td colspan = \"4\">".$lang["urls_eintrag_url"]."</td></tr>";   
   echo "<tr><td colspan = \"4\"><input name=new_url_url size=45 maxlength=128 value = \"" . htmlspecialchars(stripslashes($new_url_url)) . "\"></td></tr>";
   echo "<tr><td colspan = \"4\">&nbsp;</td></tr>";
   echo "<tr><td colspan = \"3\">".$lang["urls_eintrag_beschreibung"]."</td><td>Typen</td></tr>";
   echo "<tr>";
   echo "<td colspan=\"3\">";
   write_bbc("new_url", "new_url_text");
   echo "<textarea name=new_url_text wrap=virtual rows=15 cols=75>" . htmlspecialchars(stripslashes($new_url_text)) . "</textarea></td>";
   echo "<td>";
   createsel_urltyps("new_url_typ", $new_url_typ);
   echo "</td>";   
   echo "</tr>";
   echo "<tr><td colspan=\"4\"><input type=submit name=edit_page value=".$lang["urls_eintrag_speichern"]."></td></tr>";
   echo "</table>";
   echo "</form>";
}

function url_typ_new($new_url_typ_name, $new_url_typ_parent_id, $new_url_typ_tpl, $new_url_typ_img_big, $new_url_typ_img_small, $new_url_typ_img_small_inactive, $new_url_typ_left_bar, $new_url_typ_right_bar, $new_url_typ_top_bar, $new_url_typ_foo_bar, $new_url_typ_text){
   global $conf, $lang;

   echo "<h1>".$lang["urls_anlegen"]."</h1>";
   echo "<form name = new_url_typ action=\"" . $conf["admp"] . "&section=urls&action=add_url_typ\" ENCTYPE=\"multipart/form-data\" method=\"POST\">";
   echo "<table  class=\"reda_td\">";
   echo "<tr><td colspan = 3>".$lang["urls_name"]."</td><td>".$lang["urls_parent"]."</td></tr>";
   echo "<tr>";
   echo "<td colspan=\"3\"><input name=new_url_typ_name size=45 maxlength=128 value = \"" . htmlspecialchars(stripslashes($new_url_typ_name)) . "\"></td>";
   echo "<td>";
   createsel_urlparent("new_url_typ_parent_id",$new_url_typ_parent_id);
   echo "</td>";   
   echo "</tr>";
   echo "<tr><td>".$lang["urls_tpl"]."</td><td>".$lang["urls_logo_gross"]."</td><td>".$lang["urls_logo_klein"]."</td><td>".$lang["urls_logo_klein_inactive"]."</td></tr>";
   echo "<td>";
   if ($new_url_typ_tpl=="") {$new_url_typ_tpl = $conf["home_tpl"];}
   createsel_tpl("new_url_typ_tpl",  $new_url_typ_tpl);
   echo "</td>";
   echo "<td>";
   createsel_img("new_url_typ_img_big",  $new_url_typ_img_big);
   echo "</td>";
   echo "<td>";
   createsel_img("new_url_typ_img_small",  $new_url_typ_img_small);
   echo "</td>";
   echo "<td>";
   createsel_img("new_url_typ_img_small_inactive",  $new_url_typ_img_small_inactive);
   echo "</td>";
   echo "</tr>";
   echo "<tr><td>".$lang["urls_bar_left"]."</td><td>".$lang["urls_bar_right"]."</td><td>".$lang["urls_bar_top"]."</td><td>".$lang["urls_bar_bottom"]."</td></tr>";
    echo "<tr>";
   echo "<td>";
   createsel_bar("new_url_typ_left_bar", $new_url_typ_left_bar);
   echo "</td>";
   echo "<td>";
   createsel_bar("new_url_typ_right_bar",  $new_url_typ_right_bar);
   echo "</td>";
   echo "<td>";
   createsel_bar("new_url_typ_top_bar",  $new_url_typ_top_bar);
   echo "</td>";
   echo "<td>";
   createsel_bar("new_url_typ_foo_bar",  $new_url_typ_foo_bar);
   echo "</td>";
   echo "</tr>\n";
   echo "<tr><td colspan=\"4\">&nbsp;</td></tr>";
   echo "<tr><td colspan=\"4\">".$lang["urls_beschreibung"]."</td></tr>";
   echo "<tr>";
   echo "<td colspan=\"4\">";
   write_bbc("new_url_typ", "new_url_typ_text");
   echo "<textarea name=new_url_typ_text wrap=virtual rows=15 cols=75>" . htmlspecialchars(stripslashes($new_url_typ_text)) . "</textarea></td>";
   echo "</tr>";
   echo "<tr><td colspan=\"4\"><input type=submit name=edit_page value=".$lang["urls_speichern"]."></td></tr>";
   echo "</table>";
   echo "</form>";
}

function url_edit($id){
   global $conf, $lang;

   $result = dbquery("select * from ".$conf["db_namespace"]."url where url_id='" . $id . "'");
   if ($result) {
      $row = mysql_fetch_object($result);
      echo "<h1>".$lang["urls_eintrag_bearbeiten"]."</h1>\n";
      echo "<form name = \"edit_url\" action=\"" . $conf["admp"] . "&section=urls&action=update_url\" ENCTYPE=\"multipart/form-data\" method=\"POST\">\n";
      echo "<input type=hidden name=edit_url_id value=\"" . $row->url_id . "\">\n";      
      echo "<table  class=\"reda_td\">\n";
      echo "<tr><td colspan = 4>".$lang["urls_eintrag_titel"]."</td></tr>";
      echo "<tr><td colspan=4><input name=edit_url_name size=45 maxlength=128 value = \"" . htmlspecialchars($row->url_name) . "\"></td></tr>";
      echo "<tr><td colspan = 4>".$lang["urls_eintrag_url"]."</td></tr>";
      echo "<tr><td colspan=4><input name=edit_url_url size=45 maxlength=128 value = \"" . htmlspecialchars($row->url_url) . "\"></td></tr>";
      echo "</tr>";
      echo "<tr><td colspan=\"4\">&nbsp;</td></tr>";
      echo "<tr><td colspan=\"3\">".$lang["urls_eintrag_beschreibung"]."</td><td>".$lang["urls_eintrag_url_typ"]."</td></tr>";
      echo "<tr>";
      echo "<td colspan=\"3\">";
      write_bbc("edit_url", "edit_url_text");
      echo "<textarea name=\"edit_url_text\" wrap=virtual rows=15 cols=75>" . htmlspecialchars($row->url_text) . "</textarea></td>";
      echo "<td>";
      createsel_urltyps("edit_url_typ", explodegroup($row->url_typ));
      echo "</td>";   
      echo "</tr>";
      echo "<tr><td colspan=\"4\"><input type=submit name=edit_page value=".$lang["urls_eintrag_speichern"]."></td></tr>";
      echo "</table>";
      echo "</form>";
   }
}

function url_typ_edit($id){
   global $conf, $lang;
   
   $result = dbquery("select * from ".$conf["db_namespace"]."url_typs where url_typ_id='" . $id . "'");
   if ($result) {
      $row = mysql_fetch_object($result);
      echo "<h1>".$lang["urls_bearbeiten"]."</h1>";
      echo "<form name = edit_url_typ action=\"" . $conf["admp"] . "&section=urls&action=update_url_typ\" ENCTYPE=\"multipart/form-data\" method=\"POST\">";
      echo "<input type=hidden name=edit_url_typ_id value=\"" . $row->url_typ_id . "\">";
      echo "<table  class=\"reda_td\">";
      echo "<tr><td colspan=\"3\">".$lang["urls_titel"]."</td><td>".$lang["urls_parent"]."</td></tr>";
      echo "<tr><td colspan=\"3\"><input name=edit_url_typ_name size=45 maxlength=128 value = \"" . htmlspecialchars($row->url_typ_name) . "\"></td>";
      echo "<td>";
      createsel_urlparent("edit_url_typ_parent_id",$row->url_typ_parent_id);
      echo "</td>";   
      echo "</tr>";
      echo "<tr><td>".$lang["urls_tpl"]."</td><td>".$lang["urls_logo_gross"]."</td><td>".$lang["urls_logo_klein"]."</td></tr>";
      echo "<td>";
      createsel_tpl("edit_url_typ_tpl",  $row->url_typ_tpl);
      echo "</td>";
      echo "<td>";
      createsel_img("edit_url_typ_img_big",  $row->url_typ_img_big);
      echo "</td>";
      echo "<td>";
      createsel_img("edit_url_typ_img_small",  $row->url_typ_img_small);
      echo "</td>";
      echo "<td>";
      createsel_img("edit_url_typ_img_small_inactive",  $row->url_typ_img_small_inactive);
      echo "</td>";
      echo "</tr>";
      echo "<tr><td>".$lang["urls_bar_left"]."</td><td>".$lang["urls_bar_right"]."</td><td>".$lang["urls_bar_top"]."</td><td>".$lang["urls_bar_bottom"]."</td></tr>";
      echo "<tr>";
      echo "<td>";
      createsel_bar("edit_url_typ_left_bar", $row->url_typ_left_bar);
      echo "</td>";
      echo "<td>";
      createsel_bar("edit_url_typ_right_bar",  $row->url_typ_right_bar);
      echo "</td>";
      echo "<td>";
      createsel_bar("edit_url_typ_top_bar",  $row->url_typ_top_bar);
      echo "</td>";
      echo "<td>";
      createsel_bar("edit_url_typ_foo_bar",  $row->url_typ_foo_bar);
      echo "</td>";
      echo "</tr>\n";
      echo "<tr><td colspan=\"4\">".$lang["urls_beschreibung"]."</td></tr>";
      echo "<tr>";
      echo "<td colspan=\"4\">";
      write_bbc("edit_url_typ", "edit_url_typ_text");
      echo "<textarea name=edit_url_typ_text wrap=virtual rows=15 cols=75>" . htmlspecialchars($row->url_typ_text) . "</textarea></td>";
      echo "<tr><td colspan=\"4\"><input type=submit name=edit_page value=".$lang["urls_speichern"]."></td></tr>";
      echo "</table>";
      echo "</form>";
      mysql_free_result($result);
   }
}


function writeurltypchilds($parent, &$h_level){
   global $conf, $lang;
   
   $result = dbquery("select * from ".$conf["db_namespace"]."url_typs where url_typ_parent_id = '" . $parent . "' order by url_typ_name");
   if ( mysql_num_rows($result) > 0 ){
      while ($row = mysql_fetch_object($result)){
         echo "<tr><td>";
         for ($count = 0;$count < $h_level; $count++){echo "-";}
         echo $row->url_typ_name."</td>";
         echo "<td>&nbsp;</td>";
         echo "<td>";
         if (acl_check("edit", $conf["author_groups"], $conf["author_id"], "urls", $row->url_typ_id) == 1) {
            echo "<a href=" . $conf["admp"] . "&section=urls&action=edit_url_typ&id=".$row->url_typ_id."><img src=\"" . $conf["images_admin"] . "icon_edit.png\" width=\"25\" height=\"25\"></a>";       
         }
         echo "</td>";
         echo "<td>";
         if (acl_check("delete", $conf["author_groups"], $conf["author_id"], "urls", $row->url_typ_id) == 1) {
            if (checkurltypchilds($row->url_typ_id) == 0){
               if (checkurltypentrys($row->url_typ_id) == 0){
                  echo "<a href=" . $conf["admp"] . "&section=urls&action=delete_url_typ&delete_id=".$row->url_typ_id."><img src=\"" . $conf["images_admin"] . "icon_delete.png\" width=\"25\" height=\"25\"></a>";      			
               } else {echo "&nbsp;";}
            } else {echo "&nbsp;";}
         } else {echo "&nbsp;";}
         echo "<td>";
         if (acl_check("rights", $conf["author_groups"], $conf["author_id"], "urls", $row->url_typ_id) == 1) {
            echo "<a href=" . $conf["admp"] . "&section=rights&modul_name=urls&modul_id=".$row->url_typ_id."><img src=\"" . $conf["images_admin"] . "icon_rights.png\" width=\"25\" height=\"25\"></a>";      			
         } else {echo "&nbsp;";}
         echo "</td>";
         
         echo "</td>";
         echo "</tr>\n";

         // eintraege
         $entry_result = dbquery("select * from ".$conf["db_namespace"]."url where url_typ like '%:" . $row->url_typ_id . ":%' order by url_name");
         if ( mysql_num_rows($entry_result) > 0 ){
            while ($entry_row = mysql_fetch_object($entry_result)){
               echo "<tr><td>";
               for ($count = 0;$count < $h_level; $count++){echo "-";}
               echo "-url: ". $entry_row->url_name    . "</td>";
               echo "<td>" . $entry_row->url_counter . "</td>";
               echo "<td>";
               if (acl_check("edit", $conf["author_groups"], $conf["author_id"], "urls", $row->url_typ_id) == 1) {
                  echo "<a href=" . $conf["admp"] . "&section=urls&action=edit_url&id=".$entry_row->url_id."><img src=\"" . $conf["images_admin"] . "icon_edit.png\" width=\"25\" height=\"25\"></a>";       
               }
               echo "</td>";
               echo "<td>";
               if (acl_check("delete", $conf["author_groups"], $conf["author_id"], "urls", $row->url_typ_id) == 1) {
                  echo "<a href=" . $conf["admp"] . "&section=urls&action=delete_url&delete_id=".$entry_row->url_id."><img src=\"" . $conf["images_admin"] . "icon_delete.png\" width=\"25\" height=\"25\"></a>";      			
               } else {echo "&nbsp;";}
               echo "</td>";
               echo "</tr>\n";
            }
            mysql_free_result($entry_result);
         } 
         $h_level++;
         writeurltypchilds($row->url_typ_id, $h_level);
         $h_level--;
      }
      mysql_free_result($result);
   } 
}   
function checkurltypchilds($parent_id){
   global $conf, $lang;
   
   $childs = 0;
   $result = dbquery("select * from ".$conf["db_namespace"]."url_typs where url_typ_parent_id  = '" . $parent_id . "'");
   if (mysql_num_rows($result) > 0 ){
      $childs = 1;
      mysql_free_result($result);
   }
   return $childs;   
} 

function checkurltypentrys($urltyp){
   global $conf, $lang;
   
   $childs = 0;
   $result = dbquery("select * from ".$conf["db_namespace"]."url where url_typ like '%:" . $urltyp . ":%'");
   if (mysql_num_rows($result) > 0 ){
      $childs = 1;
      mysql_free_result($result);
   }
   return $childs;   
}      

function createsel_urltyps($select_name, $id = 0){
   global $conf, $lang;

   echo "<select multiple size = \"5\"  name=\"" . $select_name . "[]\">";
   $h_level = 0;
   geturltyp4select(0, $h_level, $id);
   echo "</select>";
   return;
}
function geturltyp4select($parent, &$h_level, $grouplist){
   global $conf, $lang;
   
   $result = dbquery("select * from ".$conf["db_namespace"]."url_typs where url_typ_parent_id = '" . $parent . "' order by url_typ_name");
   if (mysql_num_rows($result) > 0){
      while ($row = mysql_fetch_object($result)){
      	 echo "<option value=" . $row->url_typ_id;
      	 if (is_array($grouplist)){foreach ($grouplist as $value){if ($row->url_typ_id == $value){echo " selected ";}}
         }
         if (acl_check("insert", $conf["author_groups"], $conf["author_id"], "urls", $row->url_typ_id) == 1) {
            echo ">";
         } else {
         	echo " disabled style = \"color:gray;font-style:italic;\">";
         }	
         for ($count = 0;$count < $h_level; $count++){echo "-";} 
         echo $row->url_typ_name . "</option>";
         $h_level++;
         geturltyp4select($row->url_typ_id, $h_level, $grouplist);
         $h_level--;
      }
      mysql_free_result($result);
   }
}   

function createsel_urlparent($select_name,$id,$selfid="0"){
   global $conf, $lang;

   echo "\n<select name=" . $select_name . ">\n";
   echo "<option value= \"\"></option>\n";
   geturlparent4select(0, &$h_level, $id, $selfid);
   echo "</select>\n";
   return;
}
function geturlparent4select($parent, &$h_level, $grouplist, $selfid){
   global $conf, $lang;

   $result = dbquery("select * from ".$conf["db_namespace"]."url_typs where url_typ_parent_id = " . $parent . " order by url_typ_name");
   if ( mysql_num_rows($result) > 0 ){
      while ($row = mysql_fetch_object($result)){
      	 echo "<option value=" . $row->url_typ_id;
         if ( eregi ( $row->url_typ_id, $grouplist ) ){echo " selected ";}
         if (acl_check("insert", $conf["author_groups"], $conf["author_id"], "urls", $row->url_typ_id) == 1 && $row->url_typ_id <> $selfid) {
            echo ">";
         } else {
         	echo " disabled style = \"color:gray;font-style:italic;\">";
         }	
         for ($count = 0;$count < $h_level; $count++){echo "-";} 
         echo $row->url_typ_name . "</option>\n";
         $h_level++;
         geturlparent4select($row->url_typ_id, $h_level, $grouplist, $selfid);
         $h_level--;
      }
      mysql_free_result($result);
   }
}   

?>             