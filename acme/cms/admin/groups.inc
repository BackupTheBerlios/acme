<?php

include($conf["admbase"] . "/lang/groups." . $conf["lang"] . ".inc");

switch($action){
	case "groups_edit":
		groups_edit($edit_id);
		
      break;

	case "groups_update":
      groups_update($edit_group_id, $edit_group_name, $edit_rights_id, $edit_rights_access, $edit_rights_create, $edit_rights_modify, $edit_rights_delete);
		groups_browse();
		
      break;
      
	case "groups_new":
		groups_new();
		
      break;
      
   case "groups_insert":
      groups_insert($new_group_name, $new_rights_modul, $new_rights_access, $new_rights_create, $new_rights_modify, $new_rights_delete);
      groups_browse();
      break;
     
	case "groups_delete":
      groups_delete($delete_id);
      groups_browse();
      
      break;

   default:
      groups_browse();
      
      break;
}

function groups_browse() {
   global $conf, $lang;

   echo "<h1>".$lang["groups_verwaltung"]."</h1>";
	if (checkgroupcreate($conf["user_groups"], "groups") == 1){ 
      echo "<a href=\"" . $conf["admp"] . "&section=groups&action=groups_new\">Neue Gruppe anlegen</a>";
   }
   echo "<table class=\"reda_td\">";
   echo "<tr><td>".$lang["groups_name"]."</td><td width=\"30\"> </td><td width=\"30\"> </td><td width=\"30\"> </td></tr>";
   $result = dbquery("select * from acme_groups order by group_name");
   if ( mysql_num_rows($result) > 0 )           {
      while ($row = mysql_fetch_object($result))              {
         echo "<tr>";
         echo "<td>".$row->group_name."</td>";
         echo "<td>";
         if (checkgroupmodify($conf["user_groups"], "groups") == 1){ 
            echo "<a href=\"" . $conf["admp"] . "&section=groups&action=groups_edit&edit_id=" . $row->group_id . "\"><img src=\"" . $conf["images_admin"] . "icon_edit.png\" width=\"25\" height=\"25\"></a>";
         }
         echo "</td>";
         echo "<td>";
         if (checkingroup($conf["user_groups"], $row->group_id) == 0){
            if (checkgroupdelete($conf["user_groups"], "groups") == 1){ 
               echo "<a href=\"" . $conf["admp"] . "&section=groups&action=groups_delete&delete_id=" . $row->group_id . "\"><img src=\"" . $conf["images_admin"] . "icon_delete.png\" width=\"25\" height=\"25\"></a>";
            }
         }   
         echo "</td>";
         echo "</tr>";
      }
   mysql_free_result($result);
   }
   echo "</table>";
}

function groups_edit($edit_id) {
   global $conf, $lang;
   
   $groups_result = dbquery("select * from acme_groups where group_id=$edit_id");
   if ($groups_result) {
      $acme_groups = mysql_fetch_object($groups_result);
      echo "<h1>".$lang["groups_bearbeiten"]."</h1>\n";
      echo "<form action=\"" . $conf["admp"] . "&section=groups&action=groups_update&edit_group_id=" . $acme_groups->group_id . "\" method=\"POST\">\n";
      echo "<table class=\"reda_td\">\n";
      echo "<tr><td colspan = \"5\">".$lang["groups_name"]."</td></tr>\n";
      echo "<tr><td colspan = \"5\"><input name=\"edit_group_name\" size=\"25\" maxlength=\"25\" value=\"" . $acme_groups->group_name . "\"></td></tr>";
      $rights_result = dbquery("select * from acme_rights where group_id='" . $acme_groups->group_id . "' order by modul");
      if ( mysql_num_rows($rights_result) > 0 )  {
          echo "<tr><td>".$lang["groups_modul"]."</td><td>".$lang["groups_zugriff"]."</td><td>".$lang["groups_erstellen"]."</td><td>".$lang["groups_aendern"]."</td><td>".$lang["groups_loeschen"]."</td></tr>\n";
          $line = 0;
          while ($acme_rights = mysql_fetch_object($rights_result))  {
             echo "<tr>";
             echo "<td><input type=hidden name=edit_rights_id[" . $line . "] value=\"" . $acme_rights->rights_id . "\">" . $acme_rights->modul . "</td>";
             echo "<td>";
             echo "<input type=radio name=edit_rights_access[" . $line . "] value=\"Y\""; 
             if ($acme_rights->rights_access == "Y" ) echo " checked ";
             echo ">Y";
             echo "<input type=radio name=edit_rights_access[" . $line . "] value=\"N\""; 
             if ($acme_rights->rights_access == "N" ) echo " checked ";
             echo ">N";
             echo "</td>\n<td>";
             echo "<input type=radio name=edit_rights_create[" . $line . "] value=\"Y\""; 
             if ($acme_rights->rights_create == "Y" ) echo " checked ";
             echo ">Y";
             echo "<input type=radio name=edit_rights_create[" . $line . "] value=\"N\""; 
             if ($acme_rights->rights_create == "N" ) echo " checked ";
             echo ">N";
             echo "</td>\n<td>";
             echo "<input type=radio name=edit_rights_modify[" . $line . "] value=\"Y\""; 
             if ($acme_rights->rights_modify == "Y" ) echo " checked ";
             echo ">Y";
             echo "<input type=radio name=edit_rights_modify[" . $line . "] value=\"N\""; 
             if ($acme_rights->rights_modify == "N" ) echo " checked ";
             echo ">N";
             echo "</td>\n<td>";
             echo "<input type=radio name=edit_rights_delete[" . $line . "] value=\"Y\""; 
             if ($acme_rights->rights_delete == "Y" ) echo " checked ";
             echo ">Y";
             echo "<input type=radio name=edit_rights_delete[" . $line . "] value=\"N\""; 
             if ($acme_rights->rights_delete == "N" ) echo " checked ";
             echo ">N";
             echo "</td>\n";
             echo "</tr>\n";
             $line++;
         }
         mysql_free_result($rights_result);
     } 
     echo "<tr><td colspan=\"5\"><input type=submit name=add value=".$lang["groups_speichern"]."></td></tr>\n";
     echo "</table>\n";
     echo "</form>\n";
     mysql_free_result($groups_result);
   }
}   

function groups_update($edit_group_id, $edit_group_name, $edit_rights_id, $edit_rights_access, $edit_rights_create, $edit_rights_modify, $edit_rights_delete){
   global $conf, $lang;
   
   $Statement = "UPDATE acme_groups SET ".
                           " group_name = '" . $edit_group_name . "'".
                           " WHERE group_id = '". $edit_group_id . "'";
   $update_result = dbquery($Statement);
   for ($c=0;$c<count($edit_rights_id);$c++){
        $Statement = "UPDATE acme_rights SET ".
                     " rights_access = '" . $edit_rights_access[$c] . "', ".
                     " rights_create = '" . $edit_rights_create[$c] . "', ".
                     " rights_modify = '" . $edit_rights_modify[$c] . "', ".
                     " rights_delete = '" . $edit_rights_delete[$c] . "' ".                                                                                 
                     " WHERE rights_id = '" . $edit_rights_id[$c] . "'";
        $update_result = dbquery($Statement);
        }
   if($update_result){echo $lang["groups_update_erfolgreich"];}
   else{echo $lang["groups_update_fehlgeschlagen"];};
}

function groups_new() {
   global $conf, $lang;
   
   echo "<h1>".$lang["groups_anlegen"]."</h1>";
   echo "<form action=\"" . $conf["admp"] . "&section=groups&action=groups_insert\" method=\"POST\">";
   echo "<table class=\"reda_td\">";
   echo "<tr><td colspan = \"5\">".$lang["groups_name"]."</td></tr>";
   echo "<tr><td colspan = \"5\"><input name=\"new_group_name\" size=\"35\" maxlength=\"35\" value=\"" . $new_group_name . "\"></td></tr>";
   $modul_result = dbquery("select * from acme_module order by modul");
   if ( mysql_num_rows($modul_result) > 0 )  {
      echo "<tr><td>".$lang["groups_modul"]."</td><td>".$lang["groups_zugriff"]."</td><td>".$lang["groups_erstellen"]."</td><td>".$lang["groups_aendern"]."</td><td>".$lang["groups_loeschen"]."</td></tr>\n";
      $line = 0;
      while ($acme_modul = mysql_fetch_array($modul_result))  {
             echo "<tr>";
             echo "<td><input type=hidden name=new_rights_modul[" . $line . "] value=\"" . $acme_modul["modul"] . "\">" . $acme_modul["modul"] . "</td>";
             echo "<td><input type=radio name=new_rights_access[" . $line . "] value=\"Y\">Y<input type=radio name=new_rights_access[" . $line . "] value=\"N\" checked >N</td>\n";
             echo "<td><input type=radio name=new_rights_create[" . $line . "] value=\"Y\">Y<input type=radio name=new_rights_create[" . $line . "] value=\"N\" checked >N</td>\n";
             echo "<td><input type=radio name=new_rights_modify[" . $line . "] value=\"Y\">Y<input type=radio name=new_rights_modify[" . $line . "] value=\"N\" checked >N</td>\n";
             echo "<td><input type=radio name=new_rights_delete[" . $line . "] value=\"Y\">Y<input type=radio name=new_rights_delete[" . $line . "] value=\"N\" checked >N</td>\n";
             echo "</tr>\n";
             $line++;
         }
         mysql_free_result($modul_result);
     } 
   echo "<tr><td colspan=\"5\"><input type=submit name=add value=".$lang["groups_speichern"]."></td></tr>";
   echo "</table>";
   echo "</form>";
}   
   
function groups_insert($new_group_name, $new_rights_modul, $new_rights_access, $new_rights_create, $new_rights_modify, $new_rights_delete){
   global $conf, $lang;
   
   $Statement = "INSERT INTO acme_groups  (".
                           " group_name ".
                           " ) VALUES ( ".
                           " '" . $new_group_name . "') ";
                        
   $insert_result = dbquery($Statement);
   
   if ($insert_result){
      $newgroup_result = dbquery("select * from acme_groups where group_name = '" . $new_group_name . "'");
      if ( mysql_num_rows($newgroup_result) == 1 )  {
         $newgroup = mysql_fetch_array($newgroup_result);
         $group_id = $newgroup["group_id"];
         
         for ($c=0;$c<count($new_rights_modul);$c++){
            $Statement = "INSERT INTO acme_rights SET ".  
                         " modul = '" . $new_rights_modul[$c] . "', ".
                         " group_id = '" . $group_id . "', ".                                       
                         " rights_access = '" . $new_rights_access[$c] . "', ".
                         " rights_create = '" . $new_rights_create[$c] . "', ".
                         " rights_modify = '" . $new_rights_modify[$c] . "', ".
                         " rights_delete = '" . $new_rights_delete[$c] . "'";
           $insert_result = dbquery($Statement);
           if (!$insert_result){$c=count($new_rights_modul);}
         }
      }
   }   
   if($insert_result){echo $lang["groups_insert_erfolgreich"];}
   else{echo $lang["groups_insert_fehlgeschlagen"];};
}



function groups_delete($delete_id){
   global $conf, $lang;
   
   $delete_statement1 ="delete from acme_groups where group_id = ". $delete_id;
   $delete_result1 = dbquery($delete_statement1);
   if ($delete_result1){
      $delete_statement2 ="delete from acme_rights where group_id = ". $delete_id;
      $delete_result2 = dbquery($delete_statement2);
   }
   if ($delete_result1 && $delete_result2){echo $lang["groups_delete_erfolgreich"];}
   else{ echo $lang["groups_delete_fehlgeschlagen"];};
}

?>  