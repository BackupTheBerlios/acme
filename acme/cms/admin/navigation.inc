<?php

include($conf["admbase"] . "/lang/navigation." . $conf["lang"] . ".inc");

switch($action){
	case "nav_edit":
	   nav_edit($edit_id);
   	break;
   	
	case "nav_new":
      nav_new($new_nav_name);
      break;
      
	case "nav_add":
      nav_add($new_nav_name);
      break;
      
	case "nav_update":
      nav_update($edit_nav_id, $edit_nav_name);
      break;
      
	case "nav_delete":
	   nav_delete($delete_id);   
	   break;
	   
	case "topic_move":
      if ($move=="up"){nav_topic_move_up($nav_id, $topic_id);}
      if ($move=="down"){nav_topic_move_down($nav_id, $topic_id);}  
      nav_edit($nav_id);
      break;
      
	case "topic_edit":
      nav_topic_edit($edit_id);
      break;
      
	case "topic_update":
      nav_topic_update($edit_nav_topic_id, $edit_nav_topic_text, $edit_nav_topic_type_and_id);
      break;
      
	case "topic_add":
      nav_topic_insert($nav_id, $new_nav_topic_text, $new_nav_topic_type_and_id);
      nav_edit($nav_id);
      break;
      
	case "topic_new":
      nav_topic_new($nav_id);
      break;
      
	case "topic_delete":
      nav_topic_delete($delete_id);
      nav_edit($nav_id);
      break;
      
   default: 
      nav_browse();
      break;
}

function nav_browse(){
   global $conf, $lang;
   
   echo "<h1>".$lang["navigation_verwaltung"]."</h1>".
        "<a href=\"" . $conf["admp"] . "&section=navigation&action=nav_new\">".$lang["navigation_anlegen"]."</a>".
        "<table class=\"reda_td\">".
        "<tr><td>".$lang["navigation_name"]."</td><td width=\"30\"> </td><td width=\"30\"> </td></tr>";
   $result = dbquery("select * from acme_nav order by nav_name");
   if ( mysql_num_rows($result) > 0 )           {
      while ($row = mysql_fetch_object($result))              {
         echo "<tr>";
         echo "<td>".$row->nav_name."</td>";
         echo "<td><a href=\"" . $conf["admp"] . "&section=navigation&action=nav_edit&edit_id=" . $row->nav_id . "\"><img src=\"" . $conf["images_admin"] . "icon_edit.png\" width=\"25\" height=\"25\"></a></td>";
         echo "<td><a href=\"" . $conf["admp"] . "&section=navigation&action=nav_delete&delete_id=" . $row->nav_id . "\"><img src=\"" . $conf["images_admin"] . "icon_delete.png\" width=\"25\" height=\"25\"></a></td>";
         echo "</tr>";
      }
      mysql_free_result($result);
   }
   echo "</table>";
}

function nav_edit($edit_id){
   global $conf, $lang;   

   $nav_result = dbquery("select * from acme_nav where nav_id='" .$edit_id ."'");
   if ($nav_result) {
      $acme_nav = mysql_fetch_object($nav_result);
      echo "<h1>".$lang["navigation_bearbeiten"]."</h1>";
      if ( checkgroupcreate($conf["user_groups"], "navigation") == 1){
         echo "<a href=\"" . $conf["admp"] . "&section=navigation&action=topic_new&nav_id=" . $acme_nav->nav_id . "\">neuer Eintrag</a>";
      }
      echo "<form action=\"" . $conf["admp"] . "&section=navigation&action=nav_update\"  method=\"POST\">";
      echo "<input type=\"hidden\" name=\"edit_nav_id\" value=\"" . $acme_nav->nav_id . "\">";
      echo "<table class=\"reda_td\">";
      echo "<tr><td colspan = \"7\">".$lang["navigation_name"]."</td></tr>";
      echo "<tr>";
      echo "<td colspan = \"7\"><input name=\"edit_nav_name\" size=\"30\" maxlength=\"30\" value=\"" . $acme_nav->nav_name . "\"></td>";
      echo "</tr>";
      $topic_result = dbquery("select * from acme_nav_topics where nav_id=$edit_id order by nav_topic_rank");
      if ( mysql_num_rows($topic_result) > 0 )  {
         echo "<tr><td>".$lang["navigation_eintrag"]."</td><td>".$lang["navigation_typ"]."</td><td>".$lang["navigation_name"]."</td><td width=\"30\"></td><td width=\"30\"></td><td width=\"30\"></td><td width=\"30\"></td></tr>";
         while ($acme_nav_topics = mysql_fetch_object($topic_result))  {
            echo "<tr>";
            echo "<td>" . $acme_nav_topics->nav_topic_text . "</td>";
            echo "<td>" . $acme_nav_topics->nav_topic_type . "</td>";
            echo "<td>" . getnamebymodulandid($acme_nav_topics->nav_topic_type, $acme_nav_topics->nav_topic_type_id) . "</td>";
            if ($acme_nav_topics->nav_topic_rank == nav_getlowest_topic($acme_nav_topics->nav_id)){echo "<td>&nbsp;</td>";}
            else {echo "<td><a href=\"" . $conf["admp"] . "&section=navigation&action=topic_move&nav_id=" . $acme_nav_topics->nav_id . "&topic_id=" . $acme_nav_topics->nav_topic_id . "&move=up\"><img src=\"" . $conf["images_admin"] . "icon_up.png\" width=\"25\" height=\"25\" alt=\"nach oben\"></a></td>";}
            if ($acme_nav_topics->nav_topic_rank == nav_gethighest_topic($acme_nav_topics->nav_id)){echo "<td>&nbsp;</td>";}
            else{echo "<td><a href=\"" . $conf["admp"] . "&section=navigation&action=topic_move&nav_id=" . $acme_nav_topics->nav_id . "&topic_id=" . $acme_nav_topics->nav_topic_id . "&move=down\"><img src=\"" . $conf["images_admin"] . "icon_down.png\" width=\"25\" height=\"25\" alt=\"nach unten\"></a></td>";}
            echo "<td>";
            if ( checkgroupmodify($conf["user_groups"], "navigation") == 1){echo "<a href=\"" . $conf["admp"] . "&section=navigation&action=topic_edit&nav_id=" . $acme_nav_topics->nav_id . "&edit_id=" .  $acme_nav_topics->nav_topic_id . "\"><img src=\"" . $conf["images_admin"] . "icon_edit.png\" width=\"25\" height=\"25\" alt=\"bearbeiten\"></a>";}
            echo "</td>";
            echo "<td>";
            if ( checkgroupdelete($conf["user_groups"], "navigation") == 1){echo "<a href=\"" . $conf["admp"] . "&section=navigation&action=topic_delete&nav_id=" . $acme_nav_topics->nav_id . "&delete_id=" . $acme_nav_topics->nav_topic_id . "\"><img src=\"" . $conf["images_admin"] . "icon_delete.png\" width=\"25\" height=\"25\" alt=\"l&ouml;schen\"></a>";}
            echo "</td>";
            echo "</tr>";
         }
         mysql_free_result($topic_result);
      }
      echo "<tr><td colspan=\"4\"><input type=submit name=add value=".$lang["navigation_speichern"]."></td></tr>";
      echo "</table>";
      echo "</form>";
      mysql_free_result($nav_result);
   }
}   

function nav_update($edit_nav_id, $edit_nav_name){
   global $conf, $lang;
   
   $Statement = "UPDATE acme_nav SET nav_name = '". $edit_nav_name . "' WHERE nav_id = '". $edit_nav_id . "'";
   $edit_result = dbquery($Statement);
   if($edit_result){echo $lang["navigation_update_erfolgreich"];}
   else{echo $lang["navigation_update_fehlgeschlagen"];};
}

function nav_add($new_nav_name){
   global $conf, $lang;

   $Statement = "INSERT INTO acme_nav (nav_name) VALUES ('". $new_nav_name ."')";
   $insert_result = dbquery($Statement);
   if($insert_result){echo $lang["navigation_insert_erfolgreich"];}
   else{echo $lang["navigation_insert_fehlgeschlagen"];};
}

function nav_new($new_nav_name){
   global $conf, $lang;
   
   echo "<h1>".$lang["navigation_anlegen"]."<h1>".
        "<form action=\"" . $conf["admp"] . "&section=navigation&action=nav_add\" method=\"POST\">".
        "<table class=\"reda_td\">".
        "<tr><td>".$lang["navigation_name"]."</td></tr>".
        "<tr><td><input name=new_nav_name size=10 maxlength=30></td></tr>".
        "<tr><td><input type=submit name=add value=".$lang["navigation_speichern"]."></td></tr>".
        "</table>".
        "</form>";
}

function nav_delete($delete_id){
   global $conf, $lang;
   
   $delete_statement1 = "delete from acme_nav_topics where nav_id = ". $delete_id;
   $delete_result1 = dbquery($delete_statement1);
   if ($delete_result1) {
      $delete_statement2 ="delete from acme_nav where nav_id = ". $delete_id;
      $delete_result2 = dbquery($delete_statement2);           
   }   
   if($delete_result2){echo $lang["navigation_delete_erfolgreich"];}
   else {echo $lang["navigation_delete_fehlgeschlagen"];}
}

function nav_topic_new($nav_id){
   global $conf, $lang;
   
   echo "<h1>".$lang["navigation_anlegen"]."</h1>".
        "<form action=\"" . $conf["admp"] . "&section=navigation&action=topic_add\"  method=\"POST\">".
        "<table class=\"reda_td\">".
        "<tr><td>".$lang["navigation_name"]."<input type=\"hidden\" name=\"nav_id\" value=\"" . $nav_id . "\"></td></tr>".
        "<tr>".
        "<td><input name=new_nav_topic_text size=70 maxlength=128 value=\"" . $new_nav_topic_text . "\"></td>".
        "</tr>".
        "<tr><td>".$lang["navigation_typ"]."</td></tr>".
        "<tr>".
        "<td>";
   createsel_navtyp("new_nav_topic_type_and_id",  $new_nav_topic_type, $new_nav_topic_type_id);
   echo "</td>".
        "</tr>".
        "<tr><td><input type=submit name=add value=".$lang["navigation_speichern"]."></td></tr>".
        "</table>".
        "</form>";
}
function nav_topic_edit($edit_id){
   global $conf, $lang;
   
   $result = dbquery("select * from acme_nav_topics where nav_topic_id=$edit_id");
   if ($result) {
      $acme_nav_topics = mysql_fetch_object($result);
      echo "<h1>".$lang["navigation_bearbeiten"]."</h1>".
           "<form action=\"" .$conf["admp"] . "&section=navigation&action=topic_update&edit_nav_topic_id=" . $acme_nav_topics->nav_topic_id ."\"  method=\"POST\">".
           "<table class=\"reda_td\">".
           "<tr><td>".$lang["navigation_name"]."</td></tr>".
           "<tr>".
           "<td><input name=edit_nav_topic_text size=70 maxlength=128 value=\"" . $acme_nav_topics->nav_topic_text . "\"></td>".
           "</tr>".
           "<tr><td>".$lang["navigation_typ"]."</td></tr>".
           "<tr>".
           "<td>";
      createsel_navtyp("edit_nav_topic_type_and_id",  $acme_nav_topics->nav_topic_type, $acme_nav_topics->nav_topic_type_id);
      echo "</td>".
           "</tr>".
           "<tr><td><input type=submit name=add value=".$lang["navigation_speichern"]."></td></tr>".
           "</table>".
           "</form>";
        }
       mysql_free_result($result);
}       

function nav_topic_update($edit_nav_topic_id, $edit_nav_topic_text, $edit_nav_topic_type_and_id){
   global $conf, $lang;

   $topic_type_and_id    = explode("|", $edit_nav_topic_type_and_id);
   $edit_topic_type    = $topic_type_and_id[0];
   $edit_topic_type_id = $topic_type_and_id[1];

   $Statement = "UPDATE acme_nav_topics  SET ".
                " nav_topic_text ='"       . $edit_nav_topic_text ."',".
                " nav_topic_type = '"     . $edit_topic_type . "',".
                " nav_topic_type_id = '"  . $edit_topic_type_id . "'".
                " WHERE nav_topic_id = '" . $edit_nav_topic_id . "'";
   $update_result = dbquery($Statement);
   if ($update_result){echo $lang["navigation_update_erfolgreich"];}
   else{echo $lang["navigation_update_fehlgeschlagen"];}
}

function nav_topic_insert($nav_id, $new_nav_topic_text, $new_nav_topic_type_and_id){
   global $conf, $lang;

   $topic_type_and_id    = explode("|", $new_nav_topic_type_and_id);
   $new_topic_type    = $topic_type_and_id[0];
   $new_topic_type_id = $topic_type_and_id[1];

   $Statement = "SELECT nav_topic_rank FROM acme_nav_topics ".
                " WHERE nav_id = '" . $nav_id . "' order by nav_topic_rank DESC";
   $maxresult = dbquery($Statement);
   if ($maxresult){
      $maxobj    = mysql_fetch_object($maxresult);
      $max_rank  = $maxobj->nav_topic_rank;   
      $max_rank++;
   }
   else{
      $max_rank = 1;
   }

   $Statement = "INSERT INTO acme_nav_topics  SET ".
                " nav_topic_text = '"       . $new_nav_topic_text ."',".
                " nav_topic_type = '"     . $new_topic_type . "',".
                " nav_topic_type_id = '"  . $new_topic_type_id . "',".
                " nav_id = '"             . $nav_id . "',".
                " nav_topic_rank = '". $max_rank ."'";
   $update_result = dbquery($Statement);
   
   if ($update_result){echo $lang["navigation_insert_erfolgreich"];}
   else{echo $lang["navigation_insert_fehlgeschlagen"];}
}
   

function nav_topic_move_up($nav_id, $topic_id){
   global $conf, $lang;
   
   $akt_result = dbquery("select * from acme_nav_topics where nav_topic_id='" . $topic_id . "'");
   if ($akt_result) {
      $akt_topic = mysql_fetch_object($akt_result);
      $akt_pos = $akt_topic->nav_topic_rank;
      $prev_result = dbquery("select * from acme_nav_topics where nav_id='".$nav_id."' and nav_topic_rank = '" .($akt_pos - 1) . "'");
      if ($prev_result) {
         $prev_topic = mysql_fetch_object($prev_result);
         $prev_id = $prev_topic->nav_topic_id;
         $upd_result1 = dbquery("update acme_nav_topics set nav_topic_rank = '" . ($akt_pos ) . "' where nav_id='" . $nav_id . "' and nav_topic_id = '" . $prev_id ."'");
         $upd_result2 = dbquery("update acme_nav_topics set nav_topic_rank = '" . ($akt_pos - 1) . "' where nav_id='" . $nav_id . "' and nav_topic_id = '" . $topic_id . "'");
         mysql_free_result($prev_result);
         if ($upd_result1 && $upd_result2){
            echo $lang["navigation_move_up_erfolgreich"];
         } 
         else{
            echo $lang["navigation_move_up_fehlgeschlagen"];
         }
      } 
      mysql_free_result($akt_result);
   }
}
function nav_topic_move_down($nav_id, $topic_id){
   global $conf, $lang;
      
   $akt_result = dbquery("select * from acme_nav_topics where nav_topic_id='" . $topic_id . "'");
   if ($akt_result) {
      $akt_topic = mysql_fetch_object($akt_result);
      $akt_pos = $akt_topic->nav_topic_rank;
      $next_result = dbquery("select * from acme_nav_topics where nav_id='" . $nav_id . "' and nav_topic_rank = '" . ($akt_pos + 1) . "'");
      if ($next_result) {
         $next_topic = mysql_fetch_object($next_result);
         $next_id = $next_topic->nav_topic_id;
         $upd_result1 = dbquery("update acme_nav_topics set nav_topic_rank = '" . $akt_pos  . "' where nav_id='" . $nav_id . "' and nav_topic_id = '" . $next_id . "'");
         $upd_result2 = dbquery("update acme_nav_topics set nav_topic_rank = '" . ($akt_pos + 1) . "' where nav_id='" . $nav_id . "' and nav_topic_id = '" . $topic_id . "'");
         mysql_free_result($next_result);
      } 
      mysql_free_result($akt_result);
   } 
   if($upd_result1 && $upd_result2){echo $lang["navigation_move_down_erfolgreich"];}
   else{echo $lang["navigation_move_down_fehlgeschlagen"];};

}
function nav_topic_delete($delete_id){
   global $conf, $lang;
   
   $delete_result = dbquery("delete from acme_nav_topics where nav_topic_id = '". $delete_id . "'");
   if($delete_result){
      echo $lang["navigation_delete_erfolgreich"];
   }
   else{
      echo $lang["navigation_delete_fehlgeschlagen"];
   };
}


function createsel_navtyp($select_name, $type, $type_id) {
   global $conf, $lang;

   $check   = $type . "|" . $type_id;
   echo "\n<select name=\"" . $select_name . "\">";
   echo "\n<option";
   if ($type == "Inaktiv"){echo " selected";};
   echo " value=\"Inaktiv|\">".$lang["navigation_inaktiv"]."</option>\n";
   $result = dbquery("select * from acme_module where nav = 'Y'");
   if ( mysql_num_rows($result) > 0 )  { 
      while ($row = mysql_fetch_array($result)){
         $Statement = "select * from " . $row[table] . "";
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

function getnamebymodulandid($modul, $id){
   global $conf, $lang;

   $Statement = "select * from acme_module where modul = '" . $modul . "'";
   $result = dbquery($Statement);
   if (mysql_num_rows($result) > 0)  { 
      $row = mysql_fetch_array($result);
      $Statement = "select *" . 
                   " from  " . $row["tablename"] . 
                   " where " . $row["id"] . " = " . $id;
      $modul_result = dbquery($Statement);
      if (mysql_num_rows($modul_result) > 0 )  {
         $modulrow = mysql_fetch_array($modul_result);
         $name = $modulrow[$row[name]];
         mysql_free_result($modul_result);
         return $name;
      }
   } 
}

function createsel_navtopics($select_name,$grouplist, $nav_id) {
   global $conf, $lang;
   $allgroups = dbquery("select * from acme_nav_topics where nav_id = '" . $nav_id . "' order by nav_topic_rank");
   echo "<select name=" . $select_name . ">";
   echo "<option value=\"anf\">".$lang["navigation_anfang"]."</option>";
   echo "<option value=\"end\">".$lang["navigation_ende"]."</option>";
   if ($grouplist == "") echo "<option value = '' selected>";
   else echo "<option value = ''>";
   if ( mysql_num_rows($allgroups) > 0 )
      {
      while ( $g_row = mysql_fetch_object($allgroups) )
         {
         echo "<option value=" . $g_row->nav_topic_id;
         if ( eregi ( $g_row->nav_topic_id, $grouplist ) )
            echo " selected ";
         echo ">nach " . $g_row->nav_topic_text. "</option>";
         }
      mysql_free_result($allgroups);
      }
   echo "</select>";
   return;
}

function nav_getlowest_topic($nav_id){
   global $conf, $lang;
   $my_result = dbquery("select nav_topic_rank  from acme_nav_topics where nav_id='".$nav_id."' order by nav_topic_rank ASC");
   $row = mysql_fetch_object($my_result);
   $rank = $row->nav_topic_rank;
   mysql_free_result($my_result);
   return $rank;
}

function nav_gethighest_topic($nav_id){
   global $conf, $lang;
   
   $my_result = dbquery("select nav_topic_rank  from acme_nav_topics where nav_id='".$nav_id."' order by nav_topic_rank DESC");
   $row = mysql_fetch_object($my_result);
   $rank = $row->nav_topic_rank;
   mysql_free_result($my_result);
   return $rank;
}

?>