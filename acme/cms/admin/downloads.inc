<?php

include($conf["admbase"] . "/lang/downloads." . $conf["lang"] . ".inc");

switch($action)
{
   case "edit_download":
      download_edit($id);
      break;
   case "edit_download_typ":
      download_typ_edit($id);
      break;
   case "new_download":
       download_new($new_download_name, $new_download_text, $new_download_typ);
       break;
   case "new_download_typ":
       download_typ_new($new_download_typ_name, $new_download_typ_text, $new_download_typ_parent_id, $new_download_typ_tpl, $new_download_typ_img_small,$new_download_typ_img_small_inactive,  $new_download_typ_img_big, $new_download_typ_top_bar, $new_download_typ_left_bar, $new_download_typ_right_bar, $new_download_typ_foo_bar);
       break;
   case "add_download":
       if (count($new_download_typ) == 0){$error .= "typ fehlt";}
       if (!file_exists($HTTP_POST_FILES['datei']['tmp_name'])) { $error .= $lang["downloads_nofile"]."<br>";}       
       if (file_exists($conf["downloads"] . $HTTP_POST_FILES['datei']['name'])) { $error .= $lang["downloads_fileexists"];}
       if ($error <> ""){
          unlink ($HTTP_POST_FILES['datei']['tmp_name']);
          echo $error;
          download_new($new_download_name, $new_download_text, $new_download_typ);
       }
       else {
          download_add($new_download_name, $HTTP_POST_FILES['datei']['tmp_name'],$HTTP_POST_FILES['datei']['name'],$HTTP_POST_FILES['datei']['size'],  $new_download_text, $new_download_typ);
          download_browse();
       }
       break;
   case "add_download_typ":
       download_typ_add($new_download_typ_name, $new_download_typ_text, $new_download_typ_parent_id, $new_download_typ_tpl, $new_download_typ_img_small, $new_download_typ_img_small_inactive, $new_download_typ_img_big, $new_download_typ_top_bar, $new_download_typ_left_bar, $new_download_typ_right_bar, $new_download_typ_foo_bar);
       download_browse();
       break;
   case "update_download":
       download_update($edit_download_id, $edit_download_name, $edit_download_download, $edit_download_text, $edit_download_typ );
       download_browse();
       break;
   case "update_download_typ":
       download_typ_update($edit_download_typ_id, $edit_download_typ_name, $edit_download_typ_text, $edit_download_typ_parent_id, $edit_download_typ_tpl, $edit_download_typ_img_small, $edit_download_typ_img_small_inactive,  $edit_download_typ_img_big, $edit_download_typ_top_bar, $edit_download_typ_left_bar, $edit_download_typ_right_bar, $edit_download_typ_foo_bar);
       download_browse();
       break;
   case "delete_download":
       download_delete($delete_id);
       download_browse();       
       break;
   case "delete_download_typ":
       download_typ_delete($delete_id);
       download_browse();       
       break;
   default:
       download_browse();       
       break;
}

function download_add($new_download_name, $tmpname, $realname, $realsize, $new_download_text, $new_download_typ ){
   global $conf, $lang;

	if ($realsize >= 500000) {echo $lang["downloads_upload_filesizeerror"];}
	else {
		if (is_uploaded_file($tmpname)) {
			echo $lang["downloads_upload_move_rename"]."<br>";
			echo $lang["downloads_upload_copy"]."<br>";
			copy ($tmpname, $conf["downloads"] . $realname);
			echo $lang["downloads_upload_copy_end"]."<br>";
			chmod ($conf["downloads"] . $realname, 0777);
            unlink ($tmpname);
            
            $Statement = "INSERT INTO ".$conf["db_namespace"]."download SET".
                      " download_name = '". $new_download_name . "',".
                      " download_file  = '". $realname . "', ".
                      " download_text = '". $new_download_text . "',".
                      " download_typ  = '". joingrouparray($new_download_typ) . "'";
                      
            $my_result = dbquery($Statement);

            if ($my_result) {echo $lang["downloads_insert_fehlerhaft"];}
            else            {echo $lang["downloads_insert_erfolgreich"];}

		} else {
			echo $lang["downloads_upload_copy_attack"] . $realname;
		}
	}
}

function download_typ_add($new_download_typ_name, $new_download_typ_text, $new_download_typ_parent_id, $new_download_typ_tpl, $new_download_typ_img_small, $new_download_typ_img_small_inactive, $new_download_typ_img_big, $new_download_typ_top_bar, $new_download_typ_left_bar, $new_download_typ_right_bar, $new_download_typ_foo_bar){
   global $conf, $lang;

  $Statement = "INSERT INTO ".$conf["db_namespace"]."download_typs SET".
                " download_typ_name = '". $new_download_typ_name . "',".
                " download_typ_text = '". $new_download_typ_text . "',".
                " download_typ_tpl = '". $new_download_typ_tpl . "',".
                " download_typ_img_small = '". $new_download_typ_img_small . "',".
                " download_typ_img_small_inactive = '". $new_download_typ_img_small_inactive . "',".
                " download_typ_img_big = '". $new_download_typ_img_big . "',".
                " download_typ_author_id = '". $conf["author_id"] . "',".
                " download_typ_create_date = NOW(),".
                " download_typ_modify_date = NOW(),".
                " download_typ_left_bar = '". $new_download_typ_left_bar . "',".
                " download_typ_right_bar = '". $new_download_typ_right_bar . "',".
                " download_typ_top_bar = '". $new_download_typ_top_bar . "',".
                " download_typ_foo_bar = '". $new_download_typ_foo_bar . "',".
                " download_typ_parent_id = '". $new_download_typ_parent_id . "'";

  $my_result = dbquery($Statement);
   
   if ($my_result) {
      acl_user_set($conf["author_id"], "downloads", mysql_insert_id(), "Y", "Y", "Y", "Y");
   	  echo $lang["downloads_typ_insert_erfolgreich"];
   }
   else             {echo $lang["downloads_typ_insert_fehlerhaft"];}
}    

function download_update($edit_download_id, $edit_download_name, $edit_download_text, $edit_download_typ ){
   global $conf, $lang;
              
   $Statement = "UPDATE ".$conf["db_namespace"]."download SET".
                " download_name = '". $edit_download_name . "',".
                " download_text = '". $edit_download_text . "',".
                " download_typ = '". joingrouparray($edit_download_typ) . "'".
                " WHERE download_id = '". $edit_download_id . "'";
   $my_result = dbquery($Statement);
   if ($my_result) {echo $lang["downloads_update_erfolgreich"];}
  else            {echo $lang["downloads_update_fehlerhaft"];}
}

function download_typ_update($edit_download_typ_id, $edit_download_typ_name, $edit_download_typ_text, $edit_download_typ_parent_id, $edit_download_typ_tpl, $edit_download_typ_img_small,$edit_download_typ_img_small_inactive,  $edit_download_typ_img_big, $edit_download_typ_top_bar, $edit_download_typ_left_bar, $edit_download_typ_right_bar, $edit_download_typ_foo_bar){
   global $conf, $lang;
              
   $Statement = "UPDATE ".$conf["db_namespace"]."download_typs SET".
                " download_typ_name = '". $edit_download_typ_name . "',".
                " download_typ_text = '". $edit_download_typ_text . "',".
                " download_typ_tpl = '". $edit_download_typ_tpl . "',".
                " download_typ_img_small = '". $edit_download_typ_img_small . "',".
                " download_typ_img_small_inactive = '". $edit_download_typ_img_small_inactive . "',".
                " download_typ_img_big = '". $edit_download_typ_img_big . "',".
                " download_typ_modify_date = NOW(),".
                " download_typ_left_bar = '". $edit_download_typ_left_bar . "',".
                " download_typ_right_bar = '". $edit_download_typ_right_bar . "',".
                " download_typ_top_bar = '". $edit_download_typ_top_bar . "',".
                " download_typ_foo_bar = '". $edit_download_typ_foo_bar . "',".
                " download_typ_parent_id = '". $edit_download_typ_parent_id . "'".
                " WHERE download_typ_id = '". $edit_download_typ_id . "'";
   $my_result = dbquery($Statement);
   if ($my_result) {echo $lang["downloads_typ_update_erfolgreich"];}
  else             {echo $lang["downloads_typ_update_fehlerhaft"];}
}
  
function download_delete($delete_id){
   global $conf, $lang;
   
   $result = dbquery("select download_file from ".$conf["db_namespace"]."download where download_id='" . $delete_id . "'");
   if ($result){
      $row = mysql_fetch_object($result);
      $filename = $row->download_file;
      echo "unlinking: " . $conf["downloads"] . $filename;
      if (unlink ($conf["downloads"] . $filename)){
         $my_result = dbquery("delete from ".$conf["db_namespace"]."download where download_id = '". $delete_id . "'");
         if ($my_result) {echo $lang["downloads_delete_erfolgreich"];}
         else            {echo $lang["downloads_delete_fehlerhaft"];}
      }
      else {echo $lang["downloads_delete_fehlerhaft"];}
   }
}

function download_typ_delete($delete_id){
   global $conf, $lang;
   $my_result = dbquery("delete from ".$conf["db_namespace"]."download_typs where download_typ_id = '". $delete_id . "'");
   if ($my_result) {
   	acl_delete("downloads", $delete_id);
   	echo $lang["downloads_typ_delete_erfolgreich"];
   	}
   else            {echo $lang["downloads_typ_delete_fehlerhaft"];}
}
   
function download_browse(){
   global $conf, $lang;

   echo "<h1>".$lang["downloads_verwaltung"]."</h1>\n";
   if (acl_check("insert", $conf["author_groups"], $conf["author_id"], "downloads", 0) == 1) {
      echo "<a href=\"". $conf["admp"] . "&section=downloads&action=new_download_typ\">".$lang["downloads_typ_neu"]."</a><br>\n";
   }
   if (acl_check("insert", $conf["author_groups"], $conf["author_id"], "downloads", 0) == 1) {   
      echo "<a href=\"". $conf["admp"] . "&section=downloads&action=new_download\">".$lang["downloads_neu"]."</a>\n";
   }
   echo "<table class=\"reda_td\" border = 1 cellpadding = 0 cellspacing = 0>\n";
   echo "<th><tr><td>".$lang["downloads_name"]."</td><td>".$lang["downloads_counter"]."</td></tr><td></td><td></td>\n";
   writedownloadtypchilds($parent,$h_level);
   echo "</table>";
}      

function download_new($new_download_name, $new_download_text, $new_download_typ){
   global $conf, $lang;

   echo "<h1>".$lang["downloads_neu"]."</h1>";
   echo "<form name = new_download action=\"" . $conf["admp"] . "&section=downloads&action=add_download\" ENCTYPE=\"multipart/form-data\" method=\"POST\">";
   echo "<table  class=\"reda_td\" border = 1 cellpadding = 0 cellspacing = 0>";
   echo "<tr><td colspan = \"4\">".$lang["downloads_name"]."</td></tr>";
   echo "<tr><td colspan = \"4\"><input name=new_download_name size=45 maxlength=128 value = \"" . htmlspecialchars(stripslashes($new_download_name)) . "\"></td></tr>";
   echo "<tr><td colspan = \"4\">".$lang["downloads_realname"]."</td></tr>";   
   echo "<tr><td colspan = \"4\"><input type = \"file\" name=\"datei\" size=45 maxlength=128 value = \"\"></td></tr>";
   echo "<tr><td colspan = \"4\">&nbsp;</td></tr>";
   echo "<tr><td colspan = \"3\">".$lang["downloads_beschreibung"]."</td><td>".$lang["downloads_typen"]."</td></tr>";
   echo "<tr>";
   echo "<td colspan=\"3\">";
   write_bbc("new_download", "new_download_text");
   echo "<textarea name=new_download_text wrap=virtual rows=15 cols=75>" . htmlspecialchars(stripslashes($new_download_text)) . "</textarea></td>";
   echo "<td>";
   createsel_downloadtyps("new_download_typ", $new_download_typ);
   echo "</td>";   
   echo "</tr>";
   echo "<tr><td colspan=\"4\"><input type=submit name=edit_page value=".$lang["downloads_speichern"]."></td></tr>";
   echo "</table>";
   echo "</form>";
}

function download_typ_new($new_download_typ_name, $new_download_typ_text, $new_download_typ_parent_id, $new_download_typ_tpl, $new_download_typ_img_small,$new_download_typ_img_small_inactive, $new_download_typ_img_small_inactive,  $new_download_typ_img_big, $new_download_typ_top_bar, $new_download_typ_left_bar, $new_download_typ_right_bar, $new_download_typ_foo_bar){
   global $conf, $lang;

   echo "<h1>".$lang["downloads_neu"]."</h1>";
   echo "<form name = new_download_typ action=\"" . $conf["admp"] . "&section=downloads&action=add_download_typ\" ENCTYPE=\"multipart/form-data\" method=\"POST\">";
   echo "<table  class=\"reda_td\" border = 1 cellpadding = 0 cellspacing = 0>";
   echo "<tr><td colspan = 3>".$lang["downloads_name"]."</td><td>".$lang["downloads_typ_parent"]."</td></tr>";
   echo "<tr><td colspan=\"3\"><input name=new_download_typ_name size=45 maxlength=128 value = \"" . htmlspecialchars(stripslashes($new_download_typ_name)) . "\"></td>";
   echo "<td>";
   createsel_downloadparent("new_download_typ_parent_id",$new_download_typ_parent_id);
   echo "</td>";   
   echo "</tr>";
   echo "<tr><td>".$lang["downloads_typ_tpl"]."</td><td>".$lang["downloads_typ_logo_gross"]."</td><td>".$lang["downloads_typ_logo_klein"]."</td><td>".$lang["downloads_typ_logo_klein_inactive"]."</td></tr>\n";   
   echo "<tr>";
   echo "<td>";
   if ($new_download_typ_tpl=="") {$new_download_typ_tpl = $conf["home_tpl"];}
   createsel_tpl("new_download_typ_tpl",  $new_download_typ_tpl);
   echo "</td>";
   echo "<td>";
   createsel_img("new_download_typ_img_big",  $new_download_typ_img_big);
   echo "</td>";
   echo "<td>";
   createsel_img("new_download_typ_img_small",  $new_download_typ_img_small);
   echo "</td>";
   echo "<td>";
   createsel_img("new_download_typ_img_small_inactive",  $new_download_typ_img_small_inactive);
   echo "</td>";
   echo "</tr>";
   echo "<tr><td>".$lang["downloads_typ_bar_left"]."</td><td>".$lang["downloads_typ_bar_right"]."</td><td>".$lang["downloads_typ_bar_top"]."</td><td>".$lang["downloads_typ_bar_bottom"]."</td></tr>";
   echo "<tr>";
   echo "<td>";
   createsel_bar("new_download_typ_left_bar", $new_download_typ_left_bar);
   echo "</td>";
   echo "<td>";
   createsel_bar("new_download_typ_right_bar",  $new_download_typ_right_bar);
   echo "</td>";
   echo "<td>";
   createsel_bar("new_download_typ_top_bar",  $new_download_typ_top_bar);
   echo "</td>";
   echo "<td>";
   createsel_bar("new_download_typ_foo_bar",  $new_download_typ_foo_bar);
   echo "</td>";
   echo "</tr>\n";
   echo "<tr><td colspan=\"4\">".$lang["downloads_beschreibung"]."</td></tr>";
   echo "<tr>";
   echo "<td colspan=\"4\">";
   write_bbc("new_download_typ", "new_download_typ_text");
   echo "<textarea name=new_download_typ_text wrap=virtual rows=15 cols=75>" . htmlspecialchars(stripslashes($new_download_typ_text)) . "</textarea></td>";
   echo "</tr>";
   echo "<tr><td colspan=\"4\"><input type=submit name=edit_page value=".$lang["downloads_typ_speichern"]."></td></tr>";
   echo "</table>";
   echo "</form>";
}

function download_edit($id){
   global $conf, $lang;

   $result = dbquery("select * from ".$conf["db_namespace"]."download where download_id='" . $id . "'");
   if ($result) {
      $row = mysql_fetch_object($result);
      echo "<h1>".$lang["downloads_bearbeiten"]."</h1>";
      echo "<form name = edit_download action=\"" . $conf["admp"] . "&section=downloads&action=update_download\" ENCTYPE=\"multipart/form-data\" method=\"POST\">";
      echo "<input type=hidden name=edit_download_id value=\"" . $row->download_id . "\">";      
      echo "<table  class=\"reda_td\" border = 1 cellpadding = 0 cellspacing = 0>";
      echo "<tr><td colspan = 4>".$lang["downloads_name"]."</td></tr>";
      echo "<tr><td colspan=4><input name=edit_download_name size=45 maxlength=128 value = \"" . htmlspecialchars($row->download_name) . "\"></td></tr>";
      echo "</tr>";
      echo "<tr><td colspan=\"4\">&nbsp;</td></tr>";
      echo "<tr><td colspan=\"3\">".$lang["downloads_beschreibung"]."</td><td>Typen</td></tr>";
      echo "<tr>";
      echo "<td colspan=\"3\">";
      write_bbc("edit_download", "edit_download_text");
      echo "<textarea name=edit_download_text wrap=virtual rows=15 cols=75>" . htmlspecialchars($row->download_text) . "</textarea></td>";
      echo "<td>";
      createsel_downloadtyps("edit_download_typ",$row->download_typ);
      echo "</td>";   
      echo "</tr>";
      echo "<tr><td colspan=\"4\"><input type=submit name=edit_page value=".$lang["downloads_speichern"]."></td></tr>";
      echo "</table>";
      echo "</form>";
   }
}

function download_typ_edit($id){
   global $conf, $lang;
   
   $result = dbquery("select * from ".$conf["db_namespace"]."download_typs where download_typ_id='" . $id . "'");
   if ($result) {
      $row = mysql_fetch_object($result);
      echo "<h1>".$lang["downloads_typ_bearbeiten"]."</h1>";
      echo "<form name = edit_download_typ action=\"" . $conf["admp"] . "&section=downloads&action=update_download_typ\" ENCTYPE=\"multipart/form-data\" method=\"POST\">";
      echo "<input type=hidden name=edit_download_typ_id value=\"" . $row->download_typ_id . "\">";
      echo "<table  class=\"reda_td\" border = 1 cellpadding = 0 cellspacing = 0>";
      echo "<tr><td colspan=\"3\">".$lang["downloads_typ_name"]."</td><td>".$lang["downloads_typ_parent"]."</td></tr>";
      echo "<tr><td colspan=\"3\"><input name=edit_download_typ_name size=45 maxlength=128 value = \"" . htmlspecialchars($row->download_typ_name) . "\"></td>";
      echo "<td>";
      createsel_downloadparent("edit_download_typ_parent_id",$row->download_typ_parent_id);
      echo "</td></tr>";   
      echo "<tr><td>".$lang["downloads_typ_tpl"]."</td><td>".$lang["downloads_typ_logo_gross"]."</td><td>".$lang["downloads_typ_logo_klein"]."</td><td>".$lang["downloads_typ_logo_klein_inactive"]."</td></tr>\n";   
      echo "<td>";
      createsel_tpl("edit_download_typ_tpl",  $row->download_typ_tpl);
      echo "</td>";
      echo "<td>";
      createsel_img("edit_download_typ_img_big",  $row->download_typ_img_big);
      echo "</td>";
      echo "<td>";
      createsel_img("edit_download_typ_img_small",  $row->download_typ_img_small);
      echo "</td>";
      echo "<td>";
      createsel_img("edit_download_typ_img_small_inactive",  $row->download_typ_img_small_inactive);
      echo "</td>";
      echo "</tr>";
      echo "<tr><td>".$lang["downloads_typ_bar_left"]."</td><td>".$lang["downloads_typ_bar_right"]."</td><td>".$lang["downloads_typ_bar_top"]."</td><td>".$lang["downloads_typ_bar_bottom"]."</td></tr>";
      echo "<tr>";
      echo "<td>";
      createsel_bar("edit_download_typ_left_bar", $row->download_typ_left_bar);
      echo "</td>";
      echo "<td>";
      createsel_bar("edit_download_typ_right_bar",  $row->download_typ_right_bar);
      echo "</td>";
      echo "<td>";
      createsel_bar("edit_download_typ_top_bar",  $row->download_typ_top_bar);
      echo "</td>";
      echo "<td>";
      createsel_bar("edit_download_typ_foo_bar",  $row->download_typ_foo_bar);
      echo "</td>";
      echo "</tr>\n";
      echo "<tr><td colspan=\"4\">".$lang["downloads_typ_text"]."</td></tr>";
      echo "<tr>";
      echo "<td colspan=\"4\">",
      write_bbc("edit_download_typ", "edit_download_typ_text");
      echo "<textarea name=edit_download_typ_text wrap=virtual rows=15 cols=75>" . htmlspecialchars($row->download_typ_text) . "</textarea></td>";
      echo "</tr>";
      echo "<tr><td colspan=\"4\"><input type=submit name=edit_page value=".$lang["downloads_typ_speichern"]."></td></tr>";
      echo "</table>";
      echo "</form>";
      mysql_free_result($result);
   }
}


function writedownloadtypchilds($parent, &$h_level){
   global $conf, $lang;
   
   $result = dbquery("select * from ".$conf["db_namespace"]."download_typs where download_typ_parent_id = '" . $parent . "' order by download_typ_name");
   if ( mysql_num_rows($result) > 0 ){
      while ($row = mysql_fetch_object($result)){
         echo "<tr><td>";
         for ($count = 0;$count < $h_level; $count++){echo "-";}
         echo $row->download_typ_name."</td>";
         echo "<td>&nbsp;</td>";
         echo "<td>";
         if (acl_check("edit", $conf["author_groups"], $conf["author_id"], "downloads", $row->download_typ_id) == 1) {
            echo "<a href=" . $conf["admp"] . "&section=downloads&action=edit_download_typ&id=".$row->download_typ_id."><img src=\"" . $conf["images_admin"] . "icon_edit.png\" width=\"25\" height=\"25\"></a>";       
         }
         echo "</td>";
         echo "<td>";
         if (acl_check("delete", $conf["author_groups"], $conf["author_id"], "downloads", $row->download_typ_id) == 1) {
            if (checkdownloadtypchilds($row->download_typ_id) == 0){
               if (checkdownloadtypentrys($row->download_typ_id) == 0){
                  echo "<a href=" . $conf["admp"] . "&section=downloads&action=delete_download_typ&delete_id=".$row->download_typ_id."><img src=\"" . $conf["images_admin"] . "icon_delete.png\" width=\"25\" height=\"25\"></a>";      			
               } else {echo "&nbsp;";}
            } else {echo "&nbsp;";}
         } else {echo "&nbsp;";}
         echo "</td>";
         echo "<td>";
         if (acl_check("rights", $conf["author_groups"], $conf["author_id"], "downloads", $row->download_typ_id) == 1) {
            echo "<a href=" . $conf["admp"] . "&section=rights&modul_name=downloads&modul_id=".$row->download_id."><img src=\"" . $conf["images_admin"] . "icon_rights.png\" width=\"25\" height=\"25\"></a>";      			
         } else {echo "&nbsp;";}
         echo "</td>";
         echo "</tr>\n";

         // eintraege
         $entry_result = dbquery("select * from ".$conf["db_namespace"]."download where download_typ like '%:" . $row->download_typ_id . ":%' order by download_name");
         if ( mysql_num_rows($entry_result) > 0 ){
            while ($entry_row = mysql_fetch_object($entry_result)){
               echo "<tr><td>";
               for ($count = 0;$count < $h_level; $count++){echo "-";}
               echo "-download: ". $entry_row->download_name    . "</td>";
               echo "<td>" . $entry_row->download_counter . "</td>";
               echo "<td>";
               if (acl_check("edit", $conf["author_groups"], $conf["author_id"], "downloads", $row->download_typ_id) == 1) {
                  echo "<a href=" . $conf["admp"] . "&section=downloads&action=edit_download&id=".$entry_row->download_id."><img src=\"" . $conf["images_admin"] . "icon_edit.png\" width=\"25\" height=\"25\"></a>";       
               }
               echo "</td>";
               echo "<td>";
               if (acl_check("delete", $conf["author_groups"], $conf["author_id"], "downloads", $row->download_typ_id) == 1) {
                  echo "<a href=" . $conf["admp"] . "&section=downloads&action=delete_download&delete_id=".$entry_row->download_id."><img src=\"" . $conf["images_admin"] . "icon_delete.png\" width=\"25\" height=\"25\"></a>";      			
               } else {echo "&nbsp;";}
               echo "</td>";
               echo "</tr>\n";
            }
            mysql_free_result($entry_result);
         } 
         $h_level++;
         writedownloadtypchilds($row->download_typ_id, $h_level);
         $h_level--;
      }
      mysql_free_result($result);
   } 
}   
function checkdownloadtypchilds($parent_id){
   global $conf, $lang;
   
   $childs = 0;
   $result = dbquery("select * from ".$conf["db_namespace"]."download_typs where download_typ_parent_id  = '" . $parent_id . "'");
   if (mysql_num_rows($result) > 0 ){
      $childs = 1;
      mysql_free_result($result);
   }
   return $childs;   
} 

function checkdownloadtypentrys($downloadtyp){
   global $conf, $lang;
   
   $childs = 0;
   $result = dbquery("select * from ".$conf["db_namespace"]."download where download_typ like '%:" . $downloadtyp . ":%'");
   if (mysql_num_rows($result) > 0 ){
      $childs = 1;
      mysql_free_result($result);
   }
   return $childs;   
}  





function createsel_downloadtyps($select_name,$id){
   global $conf, $lang;

   echo "<select multiple size = \"5\"  name=\"" . $select_name . "[]\">";
   echo "<option value= \"\"></option>";
   getdownloadtyp4select($parent, &$h_level, $id);
   echo "</select>";
   return;
}
function getdownloadtyp4select($parent, &$h_level, $grouplist){
   global $conf, $lang;
   
   $result = dbquery("select * from ".$conf["db_namespace"]."download_typs where download_typ_parent_id = '" . $parent . "' order by download_typ_name");
   if ( mysql_num_rows($result) > 0 ){
      while ($row = mysql_fetch_object($result)){
      	 echo "<option value=" . $row->download_typ_id;
      	 if (is_array($grouplist)){
            foreach ($grouplist as $value){
              if ( eregi ( $row->download_typ_id, $value ) ){echo " selected ";}
            }
         }
         if (acl_check("insert", $conf["author_groups"], $conf["author_id"], "downloads", $row->download_typ_id) == 1 && $row->download_typ_id <> $selfid) {
            echo ">";
         } else {
         	echo " disabled style = \"color:gray;font-style:italic;\">";
         }	
         for ($count = 0;$count < $h_level; $count++){echo "-";} 
         echo $row->download_typ_name . "</option>";
         $h_level++;
         getdownloadtyp4select($row->download_typ_id, $h_level, $grouplist, $selfid);
         $h_level--;
      }
      mysql_free_result($result);
   }
}   

function createsel_downloadparent($select_name,$id,$selfid="0"){
   global $conf, $lang;

   echo "\n<select name=" . $select_name . ">\n";
   echo "<option value= \"\"></option>\n";
   getdownloadparent4select(0, &$h_level, $id, $selfid);
   echo "</select>\n";
   return;
}
function getdownloadparent4select($parent, &$h_level, $grouplist, $selfid){
   global $conf, $lang;

   $result = dbquery("select * from ".$conf["db_namespace"]."download_typs where download_typ_parent_id = " . $parent . " order by download_typ_name");
   if ( mysql_num_rows($result) > 0 ){
      while ($row = mysql_fetch_object($result)){
      	 echo "<option value=" . $row->download_typ_id;
         if ( eregi ( $row->download_typ_id, $grouplist ) ){echo " selected ";}
         if (acl_check("insert", $conf["author_groups"], $conf["author_id"], "downloads", $row->download_typ_id) == 1 && $row->download_typ_id <> $selfid) {
            echo ">";
         } else {
         	echo " disabled style = \"color:gray;font-style:italic;\">";
         }	
         for ($count = 0;$count < $h_level; $count++){echo "-";} 
         echo $row->download_typ_name . "</option>\n";
         $h_level++;
         getdownloadparent4select($row->download_typ_id, $h_level, $grouplist, $selfid);
         $h_level--;
      }
      mysql_free_result($result);
   }
}   
?>             