<?php
include($conf["admbase"] . "/lang/bar." . $conf["lang"] . ".inc");

switch($action){
	case "bar_edit":
	   bar_edit($edit_id);
   	break;
   	
	case "bar_new":
      bar_new($new_bar_name);
      break;
      
	case "bar_add":
      bar_add($new_bar_name);
      break;
      
	case "bar_update":
      bar_update($edit_bar_id, $edit_bar_name);
      break;
      
	case "bar_delete":
	   bar_delete($delete_id);   
	   break;
	   
	case "topic_move":
      if ($move=="up"){bar_topic_move_up($bar_id, $topic_id);}
      if ($move=="down"){bar_topic_move_down($bar_id, $topic_id);}  
      bar_edit($bar_id);
      break;
      
	case "topic_edit":
      bar_topic_edit($edit_id);
      break;
      
	case "topic_update":
      bar_topic_update($edit_bar_topic_id, $edit_bar_topic_text, $edit_bar_topic_type_and_id);
      break;
      
	case "topic_add":
      bar_topic_insert($bar_id, $new_bar_topic_text, $new_bar_topic_type_and_id);
      bar_edit($bar_id);
      break;
      
	case "topic_new":
      bar_topic_new($bar_id);
      break;
      
	case "topic_delete":
      bar_topic_delete($delete_id);
      bar_edit($bar_id);
      break;
      
   default: 
      bar_browse();
      break;
}

function bar_browse(){
   global $conf, $lang;
   
   echo "<h1>".$lang["bar_verwaltung"]."</h1>".
        "<a href=\"" . $conf["admp"] . "&section=bar&action=bar_new\">".$lang["bar_neu"]."</a>".
        "<table class=\"reda_td\">".
        "<tr><td>".$lang["bar_name"]."</td><td width=\"30\"> </td><td width=\"30\"> </td></tr>";
   $result = dbquery("select * from acme_bar order by bar_name");
   if ( mysql_num_rows($result) > 0 )           {
      while ($row = mysql_fetch_object($result))              {
         echo "<tr>";
         echo "<td>".$row->bar_name."</td>";
         echo "<td><a href=\"" . $conf["admp"] . "&section=bar&action=bar_edit&edit_id=" . $row->bar_id . "\"><img src=\"" . $conf["images_admin"] . "icon_edit.png\" width=\"25\" height=\"25\"></a></td>";
         echo "<td><a href=\"" . $conf["admp"] . "&section=bar&action=bar_delete&delete_id=" . $row->bar_id . "\"><img src=\"" . $conf["images_admin"] . "icon_delete.png\" width=\"25\" height=\"25\"></a></td>";
         echo "</tr>";
      }
      mysql_free_result($result);
   }
   echo "</table>";
}

function bar_edit($edit_id){
   global $conf, $lang;   

   $bar_result = dbquery("select * from acme_bar where bar_id='" .$edit_id ."'");
   if ($bar_result) {
      $acme_bar = mysql_fetch_object($bar_result);
      echo "<h1>" . $lang["bar_bearbeiten"] . "</h1>";
      if ( checkgroupcreate($conf["user_groups"], "bar") == 1){
         echo "<a href=\"" . $conf["admp"] . "&section=bar&action=topic_new&bar_id=" . $acme_bar->bar_id . "\">".$lang["bar_eintrag_neu"]."</a>";
      }
      echo "<form action=\"" . $conf["admp"] . "&section=bar&action=bar_update\"  method=\"POST\">";
      echo "<input type=\"hidden\" name=\"edit_bar_id\" value=\"" . $acme_bar->bar_id . "\">";
      echo "<table class=\"reda_td\">";
      echo "<tr><td colspan = \"7\">".$lang["bar_name"]."</td></tr>";
      echo "<tr>";
      echo "<td colspan = \"7\"><input name=\"edit_bar_name\" size=\"30\" maxlength=\"30\" value=\"" . $acme_bar->bar_name . "\"></td>";
      echo "</tr>";
      $topic_result = dbquery("select * from acme_bar_topics where bar_id=$edit_id order by bar_topic_rank");
      if ( mysql_num_rows($topic_result) > 0 )  {
         echo "<tr><td>".$lang["bar_eintrag"]."</td><td>".$lang["bar_typ"]."</td><td>".$lang["bar_name"]."</td><td width=\"30\"></td><td width=\"30\"></td><td width=\"30\"></td><td width=\"30\"></td></tr>";
         while ($acme_bar_topics = mysql_fetch_object($topic_result))  {
            echo "<tr>";
            echo "<td>" . $acme_bar_topics->bar_topic_text . "</td>";
            echo "<td>" . $acme_bar_topics->bar_topic_type . "</td>";
            echo "<td>" . getnamebymodulandid($acme_bar_topics->bar_topic_type, $acme_bar_topics->bar_topic_type_id) . "</td>";
            if ($acme_bar_topics->bar_topic_rank == bar_getlowest_topic($acme_bar_topics->bar_id)){echo "<td>&nbsp;</td>";}
            else {echo "<td><a href=\"" . $conf["admp"] . "&section=bar&action=topic_move&bar_id=" . $acme_bar_topics->bar_id . "&topic_id=" . $acme_bar_topics->bar_topic_id . "&move=up\"><img src=\"" . $conf["images_admin"] . "icon_up.png\" width=\"25\" height=\"25\" alt=\"nach oben\"></a></td>";}
            if ($acme_bar_topics->bar_topic_rank == bar_gethighest_topic($acme_bar_topics->bar_id)){echo "<td>&nbsp;</td>";}
            else{echo "<td><a href=\"" . $conf["admp"] . "&section=bar&action=topic_move&bar_id=" . $acme_bar_topics->bar_id . "&topic_id=" . $acme_bar_topics->bar_topic_id . "&move=down\"><img src=\"" . $conf["images_admin"] . "icon_down.png\" width=\"25\" height=\"25\" alt=\"nach unten\"></a></td>";}
            echo "<td>";
            if ( checkgroupmodify($conf["user_groups"], "bar") == 1){echo "<a href=\"" . $conf["admp"] . "&section=bar&action=topic_edit&bar_id=" . $acme_bar_topics->bar_id . "&edit_id=" .  $acme_bar_topics->bar_topic_id . "\"><img src=\"" . $conf["images_admin"] . "icon_edit.png\" width=\"25\" height=\"25\" alt=\"bearbeiten\"></a>";}
            echo "</td>";
            echo "<td>";
            if ( checkgroupdelete($conf["user_groups"], "bar") == 1){echo "<a href=\"" . $conf["admp"] . "&section=bar&action=topic_delete&bar_id=" . $acme_bar_topics->bar_id . "&delete_id=" . $acme_bar_topics->bar_topic_id . "\"><img src=\"" . $conf["images_admin"] . "icon_delete.png\" width=\"25\" height=\"25\" alt=\"l&ouml;schen\"></a>";}
            echo "</td>";
            echo "</tr>";
         }
         mysql_free_result($topic_result);
      }
      echo "<tr><td colspan=\"4\"><input type=submit name=add value=".$lang["bar_speichern"]."></td></tr>";
      echo "</table>";
      echo "</form>";
      mysql_free_result($bar_result);
   }
}   

function bar_update($edit_bar_id, $edit_bar_name){
   global $conf, $lang;
   
   $Statement = "UPDATE acme_bar SET bar_name = '". $edit_bar_name . "' WHERE bar_id = '". $edit_bar_id . "'";
   $edit_result = dbquery($Statement);
   if($edit_result){echo $lang["bar_update_erfolgreich"];}
   else{echo $lang["bar_update_fehlgeschlagen"];};
}

function bar_add($new_bar_name){
   global $conf, $lang;

   $Statement = "INSERT INTO acme_bar (bar_name) VALUES ('". $new_bar_name ."')";
   $insert_result = dbquery($Statement);
   if($insert_result){echo $lang["bar_insert_erfolgreich"];}
   else{echo $lang["bar_insert_fehlgeschlagen"];};
}

function bar_new($new_bar_name){
   global $conf, $lang;
   
   echo "<h1>".$lang["bar_neu"]."<h1>".
        "<form action=\"" . $conf["admp"] . "&section=bar&action=bar_add\" method=\"POST\">".
        "<table class=\"reda_td\">".
        "<tr><td>".$lang["bar_name"]."</td></tr>".
        "<tr><td><input name=new_bar_name size=10 maxlength=30></td></tr>".
        "<tr><td><input type=submit name=add value=".$lang["bar_speichern"]."></td></tr>".
        "</table>".
        "</form>";
}

function bar_delete($delete_id){
   global $conf, $lang;
   
   $delete_statement1 = "delete from acme_bar_topics where bar_id = ". $delete_id;
   $delete_result1 = dbquery($delete_statement1);
   if ($delete_result1) {
      $delete_statement2 ="delete from acme_bar where bar_id = ". $delete_id;
      $delete_result2 = dbquery($delete_statement2);           
   }   
   if($delete_result2){echo $lang["bar_delete_erfolgreich"];}
   else{echo $lang["bar_delete_fehlgeschlagen"];};
}

function bar_topic_new($bar_id){
   global $conf, $lang;
   
   echo "<h1>".$lang["bar_eintrag_neu"]."</h1>".
        "<form action=\"" . $conf["admp"] . "&section=bar&action=topic_add\"  method=\"POST\">".
        "<table class=\"reda_td\">".
        "<tr><td>".$lang["bar_eintrag_name"]."<input type=\"hidden\" name=\"bar_id\" value=\"" . $bar_id . "\"></td></tr>".
        "<tr>".
        "<td><input name=new_bar_topic_text size=70 maxlength=128 value=\"" . $new_bar_topic_text . "\"></td>".
        "</tr>".
        "<tr><td>".$lang["bar_eintrag_typ"]."</td></tr>".
        "<tr>".
        "<td>";
   createsel_bartyp("new_bar_topic_type_and_id",  $new_bar_topic_type, $new_bar_topic_type_id);
   echo "</td>".
        "</tr>".
        "<tr><td><input type=submit name=add value=".$lang["bar_speichern"]."></td></tr>".
        "</table>".
        "</form>";
}
function bar_topic_edit($edit_id){
   global $conf, $lang;
   
   $result = dbquery("select * from acme_bar_topics where bar_topic_id=$edit_id");
   if ($result) {
      $acme_bar_topics = mysql_fetch_object($result);
      echo "<h1>".$lang["bar_eintrag_bearbeiten"]."</h1>".
           "<form action=\"" .$conf["admp"] . "&section=bar&action=topic_update&edit_bar_topic_id=" . $acme_bar_topics->bar_topic_id ."\"  method=\"POST\">".
           "<table class=\"reda_td\">".
           "<tr><td>".$lang["bar_eintrag_name"]."</td></tr>".
           "<tr>".
           "<td><input name=edit_bar_topic_text size=70 maxlength=128 value=\"" . $acme_bar_topics->bar_topic_text . "\"></td>".
           "</tr>".
           "<tr><td>".$lang["bar_eintrag_typ"]."</td></tr>".
           "<tr>".
           "<td>";
      createsel_bartyp("edit_bar_topic_type_and_id",  $acme_bar_topics->bar_topic_type, $acme_bar_topics->bar_topic_type_id);
      echo "</td>".
           "</tr>".
           "<tr><td><input type=submit name=add value=".$lang["bar_speichern"]."></td></tr>".
           "</table>".
           "</form>";
        }
       mysql_free_result($result);
}       

function bar_topic_update($edit_bar_topic_id, $edit_bar_topic_text, $edit_bar_topic_type_and_id){
   global $conf, $lang;

   $topic_type_and_id    = explode("|", $edit_bar_topic_type_and_id);
   $edit_topic_type    = $topic_type_and_id[0];
   $edit_topic_type_id = $topic_type_and_id[1];

   $Statement = "UPDATE acme_bar_topics  SET ".
                " bar_topic_text ='"       . $edit_bar_topic_text ."',".
                " bar_topic_type = '"     . $edit_topic_type . "',".
                " bar_topic_type_id = '"  . $edit_topic_type_id . "'".
                " WHERE bar_topic_id = '" . $edit_bar_topic_id . "'";
   $update_result = dbquery($Statement);
   if ($update_result){
      echo $lang["bar_eintrag_update_erfolgreich"];
   }
   else{
      echo $lang["bar_eintrag_update_fehlgeschlagen"];
   }
}

function bar_topic_insert($bar_id, $new_bar_topic_text, $new_bar_topic_type_and_id){
   global $conf, $lang;

   $topic_type_and_id    = explode("|", $new_bar_topic_type_and_id);
   $new_topic_type    = $topic_type_and_id[0];
   $new_topic_type_id = $topic_type_and_id[1];

   $Statement = "SELECT bar_topic_rank FROM acme_bar_topics ".
                " WHERE bar_id = '" . $bar_id . "' order by bar_topic_rank DESC";
   $maxresult = dbquery($Statement);
   if ($maxresult){
      $maxobj    = mysql_fetch_object($maxresult);
      $max_rank  = $maxobj->bar_topic_rank;   
      $max_rank++;
   }
   else{
      $max_rank = 1;
   }

   $Statement = "INSERT INTO acme_bar_topics  SET ".
                " bar_topic_text = '"       . $new_bar_topic_text ."',".
                " bar_topic_type = '"     . $new_topic_type . "',".
                " bar_topic_type_id = '"  . $new_topic_type_id . "',".
                " bar_id = '"             . $bar_id . "',".
                " bar_topic_rank = '". $max_rank ."'";
   $update_result = dbquery($Statement);
   
   if ($update_result){
      echo $lang["bar_eintrag_insert_erfolgreich"];
   }
   else{
      echo $lang["bar_eintrag_insert_fehlgeschlagen"];
   }
}
   

function bar_topic_move_up($bar_id, $topic_id){
   global $conf, $lang;
   
   $akt_result = dbquery("select * from acme_bar_topics where bar_topic_id='" . $topic_id . "'");
   if ($akt_result) {
      $akt_topic = mysql_fetch_object($akt_result);
      $akt_pos = $akt_topic->bar_topic_rank;
      $prev_result = dbquery("select * from acme_bar_topics where bar_id='".$bar_id."' and bar_topic_rank = '" .($akt_pos - 1) . "'");
      if ($prev_result) {
         $prev_topic = mysql_fetch_object($prev_result);
         $prev_id = $prev_topic->bar_topic_id;
         $upd_result1 = dbquery("update acme_bar_topics set bar_topic_rank = '" . ($akt_pos ) . "' where bar_id='" . $bar_id . "' and bar_topic_id = '" . $prev_id ."'");
         $upd_result2 = dbquery("update acme_bar_topics set bar_topic_rank = '" . ($akt_pos - 1) . "' where bar_id='" . $bar_id . "' and bar_topic_id = '" . $topic_id . "'");
         mysql_free_result($prev_result);
         if ($upd_result1 && $upd_result2){
            echo $lang["bar_eintrag_move_erfolgreich"];
         } 
         else{
            echo $lang["bar_eintrag_move_fehlgeschlagen"];
         }
      } 
      else {echo $lang["bar_eintrag_move_fehlgeschlagen"];}
      mysql_free_result($akt_result);
   }
   else {echo $lang["bar_eintrag_move_fehlgeschlagen"];}
}
function bar_topic_move_down($bar_id, $topic_id){
   global $conf, $lang;
      
   $akt_result = dbquery("select * from acme_bar_topics where bar_topic_id='" . $topic_id . "'");
   if ($akt_result) {
      $akt_topic = mysql_fetch_object($akt_result);
      $akt_pos = $akt_topic->bar_topic_rank;
      $next_result = dbquery("select * from acme_bar_topics where bar_id='" . $bar_id . "' and bar_topic_rank = '" . ($akt_pos + 1) . "'");
      if ($next_result) {
         $next_topic = mysql_fetch_object($next_result);
         $next_id = $next_topic->bar_topic_id;
         $upd_result1 = dbquery("update acme_bar_topics set bar_topic_rank = '" . $akt_pos  . "' where bar_id='" . $bar_id . "' and bar_topic_id = '" . $next_id . "'");
         $upd_result2 = dbquery("update acme_bar_topics set bar_topic_rank = '" . ($akt_pos + 1) . "' where bar_id='" . $bar_id . "' and bar_topic_id = '" . $topic_id . "'");
         mysql_free_result($next_result);
      } 
      else {echo $lang["bar_eintrag_move_fehlgeschlagen"];}
      mysql_free_result($akt_result);
   } 
	else {echo $lang["bar_eintrag_move_fehlgeschlagen"];}
   if($upd_result1 && $upd_result2){echo $lang["bar_eintrag_move_erfolgreich"];}
   else{echo $lang["bar_eintrag_move_fehlgeschlagen"];};

}

function bar_topic_delete($delete_id){
   global $conf, $lang;
   
   $delete_result = dbquery("delete from acme_bar_topics where bar_topic_id = '". $delete_id . "'");
   if($delete_result){
      echo $lang["bar_eintrag_delete_erfolgreich"];
   }
   else{
      echo $lang["bar_eintrag_move_fehlgeschlagen"];
   };
}


function createsel_bartyp($select_name, $type, $type_id) {
   global $conf, $lang;

   $check   = $type . "|" . $type_id;
   echo "\n<select name=\"" . $select_name . "\">";
   echo "\n<option";
   if ($type == "Inaktiv"){echo " selected";};
   echo " value=\"Inaktiv|\">Inaktiv</option>\n";
   $result = dbquery("select * from acme_module where bar = 'Y'");
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
                   " from  " . $row["table"] . 
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

function createsel_bartopics($select_name,$grouplist, $bar_id) {
   global $conf, $lang;
   $allgroups = dbquery("select * from acme_bar_topics where bar_id = '" . $bar_id . "' order by bar_topic_rank");
   echo "<select name=" . $select_name . ">";
   echo "<option value=\"anf\">".$lang["bar_eintrag_am_anfang"]."</option>";
   echo "<option value=\"end\">".$lang["bar_eintrag_am_ende"]."</option>";
   if ($grouplist == "") echo "<option value = '' selected>";
   else echo "<option value = ''>";
   if ( mysql_num_rows($allgroups) > 0 )
      {
      while ( $g_row = mysql_fetch_object($allgroups) )
         {
         echo "<option value=" . $g_row->bar_topic_id;
         if ( eregi ( $g_row->bar_topic_id, $grouplist ) )
            echo " selected ";
         echo ">nach " . $g_row->bar_topic_text. "</option>";
         }
      mysql_free_result($allgroups);
      }
   echo "</select>";
   return;
}

function bar_getlowest_topic($bar_id){
   global $conf, $lang;
   $my_result = dbquery("select bar_topic_rank  from acme_bar_topics where bar_id='".$bar_id."' order by bar_topic_rank ASC");
   $row = mysql_fetch_object($my_result);
   $rank = $row->bar_topic_rank;
   mysql_free_result($my_result);
   return $rank;
}

function bar_gethighest_topic($bar_id){
   global $conf, $lang;
   $my_result = dbquery("select bar_topic_rank  from acme_bar_topics where bar_id='".$bar_id."' order by bar_topic_rank DESC");
   $row = mysql_fetch_object($my_result);
   $rank = $row->bar_topic_rank;
   mysql_free_result($my_result);
   return $rank;
}
?>