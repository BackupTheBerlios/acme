<?php

include($conf["admbase"] . "/lang/profile." . $conf["lang"] . ".inc");

switch($action)
   {
   case "edit":
      profileedit($edit_profile_id);

      break;

   case "activate":
      profileactivate($activate_id);
      profilebrowse();
      break;

   case "new":
      profilenew($new_home_name, $new_home_img_id, $new_home_page, $new_home_404, $new_home_style, $new_home_left_bar, $new_home_right_bar, $new_home_top_bar, $new_home_foo_bar);

      break;

   case "add":
      $result = profileadd($new_home_name, $new_home_img_id, $new_home_page, $new_home_404, $new_home_style, $new_home_left_bar, $new_home_right_bar, $new_home_top_bar, $new_home_foo_bar);
      if ($result){
         echo $lang["profile_insert_erfolgreich"];
         profilebrowse();
      }
      else{
      echo $lang["profile_insert_fehlerhaft"];
      // profileadd($new_home_img_id, $new_home_page, $new_home_404, $new_home_style);
      }
      break;

	case "update":
      $result = profileupdate($edit_home_id, $edit_home_name, $edit_home_img_id, $edit_home_page, $edit_home_404, $edit_home_style, $edit_home_left_bar, $edit_home_right_bar, $edit_home_top_bar, $edit_home_foo_bar);
      if ($result){echo $lang["profile_update_erfolgreich"];}
      else{echo $lang["profile_update_fehlerhaft"];}
      profilebrowse();
      
      break;
      
	case "delete":
      $result = profiledelete($delete_id);
      if ($result){echo $lang["profile_delete_fehlerhaft"];}
      else{echo $lang["profile_delete_erfolgreich"];}
      profilebrowse();
      
      break;

   default:
      profilebrowse();
      
      break;
   }
 
function profileactivate($activate_id){
   global $conf, $lang;

   $update_result = dbquery("update ".$conf["db_namespace"]."profile set home_activ = 'N'");
   $update_result = dbquery("update ".$conf["db_namespace"]."profile set home_activ = 'Y' where home_id = '" . $activate_id . "'");
   return $update_result;
} 
   
function profiledelete($delete_id){
   global $conf, $lang;

   $delete_result = dbquery("delete from ".$conf["db_namespace"]."profile where pri = '". $delete_id . "'");
   
   return $delete_result;
}
   
function profileadd($new_home_name, $new_home_img_id, $new_home_page, $new_home_404, $new_home_style, $new_home_left_bar, $new_home_right_bar, $new_home_top_bar, $new_home_foo_bar){ 
   global $conf, $lang;

   $type_and_id    = explode("|", $new_home_page);
   $new_home_page_typ    = $type_and_id[0];
   $new_home_page = $type_and_id[1];
   
   $Statement = "INSERT INTO ".$conf["db_namespace"]."profile SET ".
                " home_img_id = '" . $new_home_img_id . "' , ".
                " home_page_typ   = '" . $new_home_page_typ   ."' , ".
                " home_page   = '" . $new_home_page   ."' , ".                
                " home_404    = '" . $new_home_404    . "' , ".
                " home_style  = '" . $new_home_style  . "', ".
                " home_left_bar  = '" . $new_home_left_bar ."' , ".
                " home_right_bar = '" . $new_home_right_bar ."' , ".
                " home_top_bar   = '" . $new_home_top_bar ."' , ".
                " home_foo_bar   = '" . $new_home_foo_bar ."'  ";             
   $insert_result = dbquery($Statement);
   
   return $insert_result;
}
 
function profileupdate($edit_id, $edit_home_name,  $edit_home_img_id, $edit_home_page, $edit_home_404, $edit_home_style, $edit_home_left_bar, $edit_home_right_bar, $edit_home_top_bar, $edit_home_foo_bar){ 
   global $conf, $lang;
   
   $type_and_id    = explode("|", $edit_home_page);
   $edit_home_page_typ    = $type_and_id[0];
   $edit_home_page = $type_and_id[1];
   
   $Statement = "UPDATE ".$conf["db_namespace"]."profile SET ".
                " home_img_id   = '" . $edit_home_img_id ."' , ".
                " home_page_typ     = '" . $edit_home_page_typ ."' , ".
                " home_page     = '" . $edit_home_page ."' , ".                
                " home_name     = '" . $edit_home_name ."' , ".                
                " home_404      = '" . $edit_home_404 ."' , ".
                " home_style    = '" . $edit_home_style ."' , ".
                " home_left_bar  = '" . $edit_home_left_bar ."' , ".
                " home_right_bar = '" . $edit_home_right_bar ."' , ".
                " home_top_bar   = '" . $edit_home_top_bar ."' , ".
                " home_foo_bar   = '" . $edit_home_foo_bar ."'  ".
                " WHERE home_id = '" . $edit_id . "'";
   $update_result = dbquery($Statement);
   return $update_result;
}
   
function profilebrowse(){
   global $conf, $lang;
   
   echo "<h1>".$lang["profile_verwaltung"]."</h1>\n";
	if (checkgroupcreate($conf["author_groups"], "profile") == 1){ 
      echo "<a href=\"" . $conf["admp"] . "&action=new&section=profile\">Neuen profile anlegen</a>\n";
   }
   echo "<table class=\"reda_td\">\n";
   echo "<tr>";
   echo "<td>".$lang["profile_aktiv"]."</td>";
   echo "<td>".$lang["profile_name"]."</td>";   
   echo "<td>".$lang["profile_start"]."</td>";
   echo "<td>".$lang["profile_404"]."</td>";
   echo "<td>".$lang["profile_bild"]."</td>";
   echo "<td width=\"30\">&nbsp;</td>";
   echo "<td width=\"30\">&nbsp;</td>";
   echo "</tr>\n";
   $result = dbquery("select * from ".$conf["db_namespace"]."profile");
   if ( mysql_num_rows($result) > 0 )      {	
      while ($row = mysql_fetch_object($result)) 	      {
         echo "<tr>";	   
         echo "<td>$row->home_activ ";
         if (checkgroupcreate($conf["author_groups"], "profile") == 1){ 
           echo "<a href=\"" . $conf["admp"] . "&action=activate&section=profile&activate_id=" . $row->home_id . "\">akt</a>\n";
         }
         echo "</td>";
         echo "<td>". $row->home_name . "</td>";
         echo "<td>". $row->home_page_typ . "|" . $row->home_page . "</td>";
         echo "<td>". getpageheadlinebyid($row->home_404)  . "</td>";
         echo "<td>". getimagenamebyid($row->home_img_id)  . "</td>";         
         echo "<td>";
         if (checkgroupmodify($conf["author_groups"], "profile") == 1){ 
            echo "<a href=\"" . $conf["admp"] . "&section=profile&action=edit&edit_profile_id=" . $row->home_id . "\"><img src=\"" . $conf["images_admin"] . "icon_edit.png\" width=\"25\" height=\"25\"></a>";
         }
         echo "</td>";
         echo "<td>";
         if (checkgroupdelete($conf["author_groups"], "profile") == 1){
               echo "<a href=\"" . $conf["admp"] . "&action=delete&section=profile&delete_id=" . $row->home_id . "&delname=" . $row->home_name . "\"><img src=\"" . $conf["images_admin"] . "icon_delete.png\" width=\"25\" height=\"25\"></a>";
         }
         echo "</td>";
         echo "</tr>\n"; 
      }
   mysql_free_result($result);
   } 
   echo "</table>";   
} 
  
function profilenew(){
   global $conf, $lang;
   
   echo "<h1>".$lang["profile_neu"]."</h1>";
   echo "<form action=\"" . $conf["admp"] . "&action=add&section=profile\" method= \"POST\">";
   echo "<table class=\"reda_td\">";
   echo "<tr><td colspan = \"4\">".$lang["profile_name"]."</td></tr>";
   echo "<tr><td colspan = \"4\"><input name=new_home_name size=20 maxlength=128></td></tr>";
   echo "<tr><td>".$lang["profile_start"]."</td><td>404</td><td>Logo</td></tr>";
   echo "<tr>";
   echo "<td>";
   createsel_startpagewtyp("new_home_page", "null", "null");
   echo "</td>";
   echo "<td>";
   createsel_startpage("new_home_404", "null");
   echo "</td>";
   echo "<td>";
   createsel_img("new_home_img_id", "null");
   echo "</td>";
   echo "</tr>";
   echo "<tr><td>".$lang["profile_bar_left"]."</td><td>".$lang["profile_bar_right"]."</td><td>".$lang["profile_bar_top"]."</td><td>".$lang["profile_bar_bottom"]."</td></tr>";
   echo "<tr>";
   echo "<td>";
   createsel_bar("new_home_left_bar", $new_home_left_bar);
   echo "</td>";
   echo "<td>";
   createsel_bar("new_home_right_bar",  $new_home_right_bar);
   echo "</td>";
   echo "<td>";
   createsel_bar("new_home_top_bar",  $new_home_top_bar);
   echo "</td>";
   echo "<td>";
   createsel_bar("new_home_foo_bar",  $new_home_foo_bar);
   echo "</td>";
   echo "</tr>\n";
   echo "<tr><td colspan = \"4\"><input type=submit name=add value=".$lang["profile_speichern"]."></td></tr>";
   echo "</table>";
   echo "</form>";
   echo "</table";
}   

function profileedit($edit_id){
   global $conf, $lang;
   
   $result = dbquery("select * from ".$conf["db_namespace"]."profile where home_id='". $edit_id . "'");
   if ($result){
      $row = mysql_fetch_object($result);
      echo "\n<h1>".$lang["profile_bearbeiten"]."</h1>\n";
      echo "<form action=\"" . $conf["admp"] . "&action=update&section=profile&edit_home_id=" . $row->home_id . "\" method=\"POST\">\n";
      echo "<table class=\"reda_td\">\n";
      echo "<tr><td colspan = \"4\">".$lang["profile_name"]."</td></tr>";
      echo "<tr><td colspan = \"4\"><input name=edit_home_name size=20 maxlength=128 value = \"" . $row->home_name . "\"></td></tr>";
      echo "<tr><td>".$lang["profile_start"]."</td><td>404</td><td>".$lang["profile_bild"]."</td></tr>";
      echo "<tr>";
      echo "<td>";
      createsel_startpagewtyp("edit_home_page",$row-> home_page_typ, $row->home_page);
      echo "</td>";
      echo "<td>";
      createsel_startpage("edit_home_404",$row->home_404);
      echo "</td>";
      echo "<td>";  
      createsel_img("edit_home_img_id",$row->home_img_id);
      echo "</td>";
      echo "</tr>";
      echo "<tr><td>".$lang["profile_bar_left"]."</td><td>".$lang["profile_bar_right"]."</td><td>".$lang["profile_bar_top"]."</td><td>".$lang["profile_bar_bottom"]."</td></tr>";
      echo "<tr>";
      echo "<td>";
      createsel_bar("edit_home_left_bar", $row->home_left_bar);
      echo "</td>";
      echo "<td>";
      createsel_bar("edit_home_right_bar",  $row->home_right_bar);
      echo "</td>";
      echo "<td>";
      createsel_bar("edit_home_top_bar",  $row->home_top_bar);
      echo "</td>";
      echo "<td>";
      createsel_bar("edit_home_foo_bar",  $row->home_foo_bar);
      echo "</td>";
      echo "</tr>\n";
      echo "<tr><td colspan = \"4\"><input type=submit name=my_edit_profile value=".$lang["profile_speichern"]."></td></tr>\n";
      echo "</table>";
      echo "</form>";
      mysql_free_result($result);
   }
   
}
function createsel_startpagewtyp($select_name, $type, $type_id) {
   global $conf, $lang;

   $check   = $type . "|" . $type_id;
   echo "\n<select name=\"" . $select_name . "\">";
   echo "\n<option";
   $result = dbquery("select * from ".$conf["db_namespace"]."module where nav = 'Y'");
   if ( mysql_num_rows($result) > 0 )  { 
      while ($row = mysql_fetch_array($result)){
         $Statement = "select * from " . $row[tablename] . "";
         $modul_result = dbquery($Statement);
         if ( mysql_num_rows($modul_result) > 0 )  { 
            while ($modulrow = mysql_fetch_array($modul_result)){
               $entry   = $row[modul] . "|" . $modulrow[$row[name]] ;
               $tocheck = $row[modul] . "|" . $modulrow[$row[id]] ;
               echo "<option value=\"" . $tocheck  . "\"";
               if ($tocheck == $check)  echo " selected ";
               echo ">" . $entry . "</option>\n";                
            }
            mysql_free_result($modul_result);
         }
      } 
   }
   
   echo "</select>\n";
   
   return;
}
function createsel_startpage($select_name, $grouplist){
   global $conf, $lang;
   
   $allgroups = dbquery("select * from ".$conf["db_namespace"]."pages Where page_parent = '' order by page_name");
   echo "<select size = \"1\" name=\"" . $select_name . "\">";
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