<?php

include($conf["admbase"] . "/lang/sitemap." . $conf["lang"] . ".inc");

switch($action)
{
   case "edit":
      sitemapedit($edit_sitemap_id, $edit_sitemap_name, $edit_sitemap_img_small, $edit_sitemap_img_small_inactive, $edit_sitemap_img_big, $edit_sitemap_nav_id, $edit_sitemap_left_bar, $edit_sitemap_right_bar, $edit_sitemap_top_bar, $edit_sitemap_foo_bar);
      break;
   case "new":
       sitemapnew($new_sitemap_name, $new_sitemap_img_small, $new_sitemap_img_small_inactive, $new_sitemap_img_big, $new_sitemap_nav_id, $new_sitemap_left_bar, $new_sitemap_right_bar, $new_sitemap_top_bar, $new_sitemap_foo_bar);
       break;
   case "add":
       sitemapadd($new_sitemap_name, $new_sitemap_img_small, $new_sitemap_img_small_inactive, $new_sitemap_img_big, $new_sitemap_nav_id, $new_sitemap_left_bar, $new_sitemap_right_bar, $new_sitemap_top_bar, $new_sitemap_foo_bar);
       sitemapbrowse();
       break;
   case "update":
       sitemapupdate($edit_sitemap_id, $edit_sitemap_name, $edit_sitemap_img_small, $edit_sitemap_img_small_inactive, $edit_sitemap_img_big, $edit_sitemap_nav_id, $edit_sitemap_left_bar, $edit_sitemap_right_bar, $edit_sitemap_top_bar, $edit_sitemap_foo_bar);
       sitemapbrowse();
       break;
   case "delete":
       sitemapdelete($delete_id);
       sitemapbrowse();       
       break;
   default:
       sitemapbrowse();       
       break;
}

function sitemapadd($new_sitemap_name, $new_sitemap_img_small, $new_sitemap_img_small_inactive, $new_sitemap_img_big, $new_sitemap_nav_id, $new_sitemap_left_bar, $new_sitemap_right_bar, $new_sitemap_top_bar, $new_sitemap_foo_bar){
   global $conf, $lang;

   $Statement = "INSERT INTO ".$conf["db_namespace"]."sitemap SET".
                " sitemap_name = '". $new_sitemap_name . "',".
                " sitemap_img_small = '". $new_sitemap_img_small . "',".
                " sitemap_img_small_inactive = '". $new_sitemap_img_small_inactive . "',".                
                " sitemap_img_big = '". $new_sitemap_img_big . "',".
                " sitemap_top_bar = '". $new_sitemap_top_bar . "',".
                " sitemap_foo_bar = '". $new_sitemap_foo_bar . "',".
                " sitemap_right_bar = '". $new_sitemap_right_bar . "',".
                " sitemap_left_bar = '". $new_sitemap_left_bar . "',".
                " sitemap_nav_id = '" . $new_sitemap_nav_id ."'";
   $my_result = dbquery($Statement);
   if ($my_result) {
   	echo $lang["sitemap_insert_erfolgreich"];
   	$modulid = mysql_insert_id();
   	acl_user_set($conf["author_id"], "sitemap", $modulid, "Y", "Y", "Y", "Y");
   	acl_group_set($conf["author_groups"], "sitemap", $modulid, "Y", "Y", "Y", "Y");
   	}
   else            {echo $lang["sitemap_insert_fehlerhaft"];}
}
function sitemapupdate($edit_sitemap_id, $edit_sitemap_name, $edit_sitemap_img_small, $edit_sitemap_img_small_inactive, $edit_sitemap_img_big, $edit_sitemap_nav_id, $edit_sitemap_left_bar, $edit_sitemap_right_bar, $edit_sitemap_top_bar, $edit_sitemap_foo_bar){
   global $conf, $lang;
              
   $Statement = "UPDATE ".$conf["db_namespace"]."sitemap SET".
                " sitemap_name = '". $edit_sitemap_name . "',".
                " sitemap_nav_id = '". $edit_sitemap_nav_id . "',".
                " sitemap_img_small = '". $edit_sitemap_img_small . "',".
                " sitemap_img_small_inactive = '". $edit_sitemap_img_small_inactive . "',".                
                " sitemap_top_bar = '". $edit_sitemap_top_bar . "',".
                " sitemap_foo_bar = '". $edit_sitemap_foo_bar . "',".
                " sitemap_right_bar = '". $edit_sitemap_right_bar . "',".
                " sitemap_left_bar = '". $edit_sitemap_left_bar . "',".
                " sitemap_img_big = '". $edit_sitemap_img_big . "' ".
                " WHERE sitemap_id = '". $edit_sitemap_id . "'";
   $my_result = dbquery($Statement);
   if ($my_result) {echo $lang["sitemap_update_erfolgreich"];}
  else            {echo $lang["sitemap_update_fehlerhaft"];}
}
function sitemapdelete($delete_id){
   global $conf, $lang;
   
   $my_result = dbquery("delete from ".$conf["db_namespace"]."sitemap where sitemap_id = '". $delete_id . "'");
   if ($my_result) {echo $lang["sitemap_delete_erfolgreich"];}
   else            {echo $lang["sitemap_delete_fehlerhaft"];}
}

function sitemapbrowse(){
   global $conf, $lang;

   echo "<h1>".$lang["sitemap_verwaltung"]."</h1>\n";
   if (acl_check("insert", $conf["author_groups"], $conf["author_id"], "sitemap", 0) == 1) {
      echo "<a href=\"". $conf["admp"] . "&section=sitemap&action=new\">".$lang["sitemap_anlegen"]."</a>\n";
   }
   echo "<table class=\"reda_td\">\n";
   echo "<th><tr><td>".$lang["sitemap_name"]."</td><td>".$lang["sitemap_nav"]."</td></td><td> </td><td> </td></tr></th>\n";
   $result = dbquery("select * from ".$conf["db_namespace"]."sitemap order by sitemap_name");
   if ( mysql_num_rows($result) > 0 )           {
      while ($row = mysql_fetch_object($result))              {
         echo "<tr>";
         echo "<td>".$row->sitemap_name."</td>";
         echo "<td>".$row->sitemap_nav_id."</td>";
         echo "<td>";
         if (acl_check("edit", $conf["author_groups"], $conf["author_id"], "sitemap", $row->sitemap_id) == 1) {
            echo "<a href=\"" . $conf["admp"] . "&section=sitemap&action=edit&edit_sitemap_id=" . $row->sitemap_id . "\"><img src=\"" . $conf["images_admin"] . "icon_edit.png\" width=\"25\" height=\"25\"></a>";
         }
         echo "</td>";
         echo "<td>";
         if (acl_check("delete", $conf["author_groups"], $conf["author_id"], "sitemap", $row->sitemap_id) == 1) { 
            echo "<a href=\"" . $conf["admp"] . "&section=sitemap&action=delete&delte_id=" . $row->sitemap_id . "\"><img src=\"" . $conf["images_admin"] . "icon_delete.png\" width=\"25\" height=\"25\"></a>";
         }
         echo "</td>";
         echo "</tr>";
      }
   mysql_free_result($result);
   }
   echo "</table>";
}      
function sitemapnew($new_sitemap_name, $new_sitemap_img_small, $new_sitemap_img_small_inactive, $new_sitemap_img_big, $new_sitemap_nav_id, $new_sitemap_left_bar, $new_sitemap_right_bar, $new_sitemap_top_bar, $new_sitemap_foo_bar){
   global $conf, $lang;

   echo "<h1>".$lang["sitemap_anlegen"]."</h1>";
   echo "<form action=\"" . $conf["admp"] . "&section=sitemap&action=add\" ENCTYPE=\"multipart/form-data\" method=\"POST\">";
   echo "<table  class=\"reda_td\">";
   echo "<tr><td colspan=5>".$lang["sitemap_name"]."</td></tr>";
   echo "<tr>";
   echo "<td colspan=5><input name=new_sitemap_name size=45 maxlength=59 value = \"" . htmlspecialchars(stripslashes($new_sitemap_name)) . "\"></td>";
   echo "</tr>";
   echo "<tr><td colspan=2>".$lang["sitemap_nav"]."</td><td>".$lang["sitemap_logo_klein"]."</td><td>".$lang["sitemap_logo_klein_inactive"]."</td><td>".$lang["sitemap_logo_gross"]."</td></tr>";
   echo "<tr>";
   echo "<td colspan=2>";
   createsel_navid("new_sitemap_nav_id", $new_sitemap_nav_id);
   echo "</td>";
   echo "<td colspan=1>";
   createsel_img("new_sitemap_img_small",  $new_sitemap_img_small);
   echo "</td>";
   echo "<td colspan=1>";
   createsel_img("new_sitemap_img_small_inactive",  $new_sitemap_img_small_inactive);
   echo "</td>";
   echo "<td colspan=1>";
   createsel_img("new_sitemap_img_big",  $new_sitemap_img_big);
   echo "</td>";
   echo "</tr>";
   echo "<tr><td colspan=5>&nbsp;</td></tr>\n";   
   echo "<tr><td>".$lang["sitemap_frame"]."</td><td>".$lang["sitemap_bar_left"]."</td><td>".$lang["sitemap_bar_right"]."</td><td>".$lang["sitemap_bar_top"]."</td><td>".$lang["sitemap_bar_bottom"]."</td></tr>";
   echo "<tr>";
   echo "<td>";
   echo "&nbsp;";  // createsel_frame("new_page_frame", $new_page_frame);
   echo "</td>";
   echo "<td>";
   createsel_bar("new_sitemap_left_bar", $new_sitemap_left_bar);
   echo "</td>";
   echo "<td>";
   createsel_bar("new_sitemap_right_bar", $new_sitemap_right_bar);
   echo "</td>";
   echo "<td>";
   createsel_bar("new_sitemap_top_bar", $new_sitemap_top_bar);
   echo "</td>";
   echo "<td>";
   createsel_bar("new_sitemap_foo_bar", $new_sitemap_foo_bar);
   echo "</td>";
   echo "</tr>";
   echo "<tr><td colspan=5><input type=submit name=edit_sitemap value=".$lang["sitemap_speichern"]."></td></tr>";
   echo "</table>";
   echo "</form>";
}

function sitemapedit($id){
   global $conf, $lang;
   
   $result = dbquery("select * from ".$conf["db_namespace"]."sitemap where sitemap_id='" . $id . "'");
   if ($result) {
      $row = mysql_fetch_array($result);
      echo "<h1>".$lang["sitemap_bearbeiten"]."</h1>";
      echo "<form action=\"" . $conf["admp"] . "&section=sitemap&action=update\" ENCTYPE=\"multipart/form-data\" method=POST>";
      echo "<input type=hidden name=edit_sitemap_id value=\"" . $row["sitemap_id"] . "\">";
      echo "<table  class=\"reda_td\">";
      echo "<tr><td colspan = 5>".$lang["sitemap_name"]."</td></tr>";
      echo "<tr>";
      echo "<td colspan = 5><input name=edit_sitemap_name size=45 maxlength=59 value = \"" . htmlspecialchars($row["sitemap_name"]) . "\"></td>";
      echo "</tr>";
      echo "<tr><td colspan=2>".$lang["sitemap_nav"]."</td><td>".$lang["sitemap_logo_klein"]."</td><td>".$lang["sitemap_logo_klein_inactive"]."</td><td>".$lang["sitemap_logo_gross"]."</td></tr>";
      echo "<tr>";
      echo "<td colspan=2>";
      createsel_navid("edit_sitemap_nav_id", $row["sitemap_nav_id"]);
      echo "</td>";
      echo "<td>";
      createsel_img("edit_sitemap_img_small",  $row["sitemap_img_small"]);
      echo "</td>";
      echo "<td>";
      createsel_img("edit_sitemap_img_small_inactive",  $row["sitemap_img_small_inactive"]);
      echo "</td>";
      echo "<td>";
      createsel_img("edit_sitemap_img_big",  $row["sitemap_img_big"]);
      echo "</td>";
      echo "</tr>\n";
      echo "<tr><td colspan=5>&nbsp;</td></tr>\n";   
      echo "<tr><td>".$lang["sitemap_frame"]."</td><td>".$lang["sitemap_bar_left"]."</td><td>".$lang["sitemap_bar_right"]."</td><td>".$lang["sitemap_bar_top"]."</td><td>".$lang["sitemap_bar_bottom"]."</td></tr>";
      echo "<tr>";
      echo "<td>";
      echo "&nbsp;";  // createsel_frame("new_page_frame", $new_page_frame);
      echo "</td>";
      echo "<td>";
      createsel_bar("edit_sitemap_left_bar", $row["sitemap_left_bar"]);
      echo "</td>";
      echo "<td>";
      createsel_bar("edit_sitemap_right_bar", $row["sitemap_right_bar"]);
      echo "</td>";
      echo "<td>";
      createsel_bar("edit_sitemap_top_bar", $row["sitemap_top_bar"]);
      echo "</td>";
      echo "<td>";
      createsel_bar("edit_sitemap_foo_bar", $row["sitemap_foo_bar"]);
      echo "</td>";
      echo "</tr>";
      echo "<tr><td colspan=5 class=\"button_td_submit\"><input type=submit name=edit_sitemap value=".$lang["sitemap_speichern"]."></td></tr>\n";
      echo "</table>\n";
      echo "</form>\n";
      mysql_free_result($result);
   }
}   

function createsel_navid($select_name, $id) {
   global $conf, $lang;

   echo "\n<select name=\"" . $select_name . "\">";
   echo "\n<option";
   $result = dbquery("select * from ".$conf["db_namespace"]."bar order by bar_name");
   if ( mysql_num_rows($result) > 0 )  { 
      while ($row = mysql_fetch_object($result)){
          echo "<option value=\"" . $row->bar_id  . "\"";
          if ($row->bar_id == $id)  echo " selected ";
          echo ">" . $row->bar_name . "</option>\n";                
      }
      mysql_free_result($modul_result);
   }
   echo "</select>\n";
   
   return;
}
?>



