<?php

include($conf["admbase"] . "/lang/rights." . $conf["lang"] . ".inc");
include($conf["admbase"] . "/lang/admin." . $conf["lang"] . ".inc");

switch($action){
   case "rights_update":
      rights_update($modul_name, $modul_id, $edit_acl_id, $edit_acl_insert, $edit_acl_edit, $edit_acl_delete, $edit_acl_rights, $edit_acl_deleteit,$new_acl_user_insertit,$new_acl_user, $new_acl_user_insert, $new_acl_user_edit, $new_acl_user_delete, $new_acl_user_rights, $new_acl_group_insertit, $new_acl_group, $new_acl_group_insert, $new_acl_group_edit, $new_acl_group_delete, $new_acl_group_rights);
      rights_browse($modul_name, $modul_id);
      break;
   default:
      rights_browse($modul_name, $modul_id);
      break;
}

function rights_browse($modul_name, $modul_id) {
   global $conf, $lang;

   echo "<h1>".$lang["rights_verwaltung"]."</h1>\n";
   echo "<h2>" .$lang["admin_$modul_name"] .  "-" .getnamebymodulandid($modul_name, $modul_id). "</h2>";
   echo "<a href=\"". $conf["admp"] . "&section=".$modul_name. "\">".$lang["rights_zurueck"]."</a>\n";
   echo "<form action=\"" . $conf["admp"] . "&section=rights&modul_name=".$modul_name."&modul_id=".$modul_id. "&action=rights_update\" method=\"POST\">\n";
   echo "<table class=\"reda_td\">\n";
   $rights_result = dbquery("select * from acme_acl where modul_name='" . $modul_name . "' and modul_id = '".$modul_id."'");
   if ( mysql_num_rows($rights_result) > 0 )  {
      echo "<tr><td>".$lang["rights_username"]."</td><td>".$lang["rights_groupname"]."</td><td>".$lang["rights_erstellen"]."</td><td>".$lang["rights_aendern"]."</td><td>".$lang["rights_loeschen"]."</td><td>".$lang["rights_rechte"]."</td><td>".$lang["rights_acl_delete"]."</td></tr>\n";
      $line = 0;
      while ($acme_rights = mysql_fetch_object($rights_result))  {
         echo "<tr>";
         echo "<td><input type=hidden name=edit_acl_id[" . $line . "] value=\"" . $acme_rights->acl_id . "\">" . getauthorbyid($acme_rights->author_id) . "</td>";
         echo "<td>" . getgroupnamebyid($acme_rights->group_id) . "</td>";
         echo "<td>";
         echo "<input type=radio name=edit_acl_insert[" . $line . "] value=\"Y\""; 
         if ($acme_rights->acl_insert == "Y" ) echo " checked ";
         echo ">Y";
         echo "<input type=radio name=edit_acl_insert[" . $line . "] value=\"N\""; 
         if ($acme_rights->acl_insert == "N" ) echo " checked ";
         echo ">N";
         echo "</td><td>\n";
         echo "<input type=radio name=edit_acl_edit[" . $line . "] value=\"Y\""; 
         if ($acme_rights->acl_edit == "Y" ) echo " checked ";
         echo ">Y";
         echo "<input type=radio name=edit_acl_edit[" . $line . "] value=\"N\""; 
         if ($acme_rights->acl_edit == "N" ) echo " checked ";
         echo ">N";
         echo "</td>\n";
         echo "<td>";
         echo "<input type=radio name=edit_acl_delete[" . $line . "] value=\"Y\""; 
         if ($acme_rights->acl_delete == "Y" ) echo " checked ";
         echo ">Y";
         echo "<input type=radio name=edit_acl_delete[" . $line . "] value=\"N\""; 
         if ($acme_rights->acl_delete == "N" ) echo " checked ";
         echo ">N";
         echo "</td>\n";
         echo "<td>";
         echo "<input type=radio name=edit_acl_rights[" . $line . "] value=\"Y\""; 
         if ($acme_rights->acl_rights == "Y" ) echo " checked ";
         echo ">Y";
         echo "<input type=radio name=edit_acl_rights[" . $line . "] value=\"N\""; 
         if ($acme_rights->acl_rights == "N" ) echo " checked ";
         echo ">N";
         echo "</td>\n";
         echo "<td>";
         if ($acme_rights->author_id == $conf["author_id"]){
         	echo "&nbsp;";
         } else {	
            echo "<input type=checkbox name=edit_acl_deleteit[" . $line . "] value = deleteit>";
         }   
	     echo "</td>";
         echo "</tr>\n";
         $line++;
      }
      mysql_free_result($rights_result);

      echo "<tr><td colspan=6>".$lang["rights_newacl"]."</td><td>".$lang["rights_newaclinsert"]."</td></tr>";
      echo "<tr>";
      echo "<td>";
      getauthor4select("new_acl_user", 0);
      echo "</td>";
      echo "<td>";
      echo "&nbsp;";
      echo "</td>";
      echo "<td>";
      echo "<input type=radio name=new_acl_user_insert value=\"Y\""; 
      echo ">Y";
      echo "<input type=radio name=new_acl_user_insert value=\"N\" checked "; 
      echo ">N";
      echo "</td>\n";
      echo "<td><input type=radio name=new_acl_user_edit value=\"Y\""; 
      echo ">Y";
      echo "<input type=radio name=new_acl_user_edit value=\"N\" checked "; 
      echo ">N";
      echo "</td>\n";
      echo "<td>";
      echo "<input type=radio name=new_acl_user_delete value=\"Y\""; 
      echo ">Y";
      echo "<input type=radio name=new_acl_user_delete value=\"N\" checked "; 
      echo ">N";
      echo "</td>\n";
      echo "<td>";
      echo "<input type=radio name=new_acl_user_rights value=\"Y\""; 
      echo ">Y";
      echo "<input type=radio name=new_acl_user_rights value=\"N\" checked "; 
      echo ">N";
      echo "</td>\n";
      echo "<td><input type=checkbox name=new_acl_user_insertit value = insertit></td>";
      echo "</tr>\n";
      echo "<tr>";
      echo "<td>";
      echo "&nbsp;";
      echo "</td>";
      echo "<td>";
      getgroup4select("new_acl_group", 0);
      echo "</td>";
      echo "<td>";
      echo "<input type=radio name=new_acl_group_insert value=\"Y\""; 
      echo ">Y";
      echo "<input type=radio name=new_acl_group_insert value=\"N\" checked "; 
      echo ">N";
      echo "</td>\n";
      echo "<td><input type=radio name=new_acl_group_edit value=\"Y\""; 
      echo ">Y";
      echo "<input type=radio name=new_acl_group_edit value=\"N\" checked "; 
      echo ">N";
      echo "</td>\n";
      echo "<td>";
      echo "<input type=radio name=new_acl_group_delete value=\"Y\""; 
      echo ">Y";
      echo "<input type=radio name=new_acl_group_delete value=\"N\" checked "; 
      echo ">N";
      echo "</td>\n";
      echo "<td>";
      echo "<input type=radio name=new_acl_group_rights value=\"Y\""; 
      echo ">Y";
      echo "<input type=radio name=new_acl_group_rights value=\"N\" checked "; 
      echo ">N";
      echo "</td>\n";
      echo "<td><input type=checkbox name=new_acl_group_insertit value = insertit></td>";
      echo "</tr>\n";

   } 
   echo "<tr><td colspan=\"7\"><input type=submit name=add value=".$lang["rights_speichern"]."></td></tr>\n";
   echo "</table>\n";
   echo "</form>\n";
}   

function rights_update($modul_name, $modul_id, $edit_acl_id, $edit_acl_insert, $edit_acl_edit, $edit_acl_delete, $edit_acl_rights, $edit_acl_deleteit,$new_acl_user_insertit,$new_acl_user, $new_acl_user_insert, $new_acl_user_edit, $new_acl_user_delete, $new_acl_user_rights, $new_acl_group_insertit, $new_acl_group, $new_acl_group_insert, $new_acl_group_edit, $new_acl_group_delete, $new_acl_group_rights){
   global $conf, $lang;
   
   for ($c=0;$c<count($edit_acl_id);$c++){
   	  if ($edit_acl_deleteit[$c] == "deleteit") {
   	  	 $delete_statement ="delete from acme_acl where acl_id = '". $edit_acl_id[$c]."'";
         $delete_result = dbquery($delete_statement);
         if($delete_result){echo $lang["rights_delete_erfolgreich"];}
         else{echo $lang["rights_delete_fehlgeschlagen"];echo mysql_errno() . ": " . mysql_error() . "\n";};
   	  } else {
         $Statement = "select acl_id from acme_acl where ".
                      " acl_insert = '" . $edit_acl_insert[$c] . "' and ".
                      " acl_edit   = '" . $edit_acl_edit[$c]   . "' and ".
                      " acl_delete = '" . $edit_acl_delete[$c] . "' and ".
                      " acl_rights = '" . $edit_acl_rights[$c] . "' and ".                                                                                 
                      " acl_id     = '" . $edit_acl_id[$c]     . "'";
                      $cr = dbquery($Statement);
                      $checkres = mysql_num_rows($cr);
    	 if ($checkres==0) { 	
         $Statement = "UPDATE acme_acl SET ".
                      " acl_insert = '" . $edit_acl_insert[$c] . "', ".
                      " acl_edit   = '" . $edit_acl_edit[$c]   . "', ".
                      " acl_delete = '" . $edit_acl_delete[$c] . "', ".
                      " acl_rights = '" . $edit_acl_rights[$c] . "' ".                                                                                 
                      " WHERE acl_id = '" . $edit_acl_id[$c]   . "'";
         $update_result = dbquery($Statement);
         if($update_result){echo $lang["rights_update_erfolgreich"];}
         else{echo $lang["rights_update_fehlgeschlagen"];};
    	 }
      }
   }
   if ($new_acl_user_insertit == "insertit") {
      if (isset($new_acl_user) && $new_acl_user <> "") {
      	 // gibts schon rechte?
      	 $cr = dbquery("select * from acme_acl where modul_name = '" . $modul_name . "' and modul_id = '" . $modul_id . "' And author_id = '" . $new_acl_user . "'");
         $checkres = mysql_num_rows($cr);        	
         if ($checkres == 0) {  	
      	    $Statement = "INSERT INTO acme_acl SET ".  
                     " modul_name = '" . $modul_name . "', ".
                      " modul_id = '" . $modul_id . "', ".
                    " author_id = '" . $new_acl_user . "', ".                                       
                   " acl_insert = '" . $new_acl_user_insert . "', ".
                   " acl_edit =   '" . $new_acl_user_edit . "', ".
                   " acl_delete = '" . $new_acl_user_delete . "', ".
                   " acl_rights = '" . $new_acl_user_rights . "' ";
         }          
   	  } 
      if ($checkres == 0){	                                                    
         $insert_result = dbquery($Statement);
         if($insert_result){echo $lang["rights_insert_erfolgreich"];}
         else{echo $lang["rights_insert_fehlgeschlagen"];};
      } else {
         echo $lang["rights_insert_fehlgeschlagen"];
      }
   }   	     	  
   if ($new_acl_group_insertit == "insertit") {
   	 if (isset($new_acl_group) && $new_acl_group <> "") {
      	 // gibts schon rechte?
      	 $cr = dbquery("select * from acme_acl where modul_name = '" . $modul_name . "' and modul_id = '" . $modul_id . "' And group_id = '" . $new_acl_group . "'");
         $checkres = mysql_num_rows($cr);        	
         if ($checkres == 0) {  	
   	        $Statement = "INSERT INTO acme_acl SET ".  
                   " modul_name = '" . $modul_name . "', ".
                   " modul_id = '" . $modul_id . "', ".
                   " group_id = '" . $new_acl_group . "', ".                                       
                   " acl_insert = '" . $new_acl_group_insert . "', ".
                   " acl_edit =   '" . $new_acl_group_edit . "', ".
                   " acl_delete = '" . $new_acl_group_delete . "', ".
                   " acl_rights = '" . $new_acl_group_rights . "' ";
         }          
      }
      if ($checkres == 0){	                                                    
         $insert_result = dbquery($Statement);
         if($insert_result){echo $lang["rights_insert_erfolgreich"];}
         else{echo $lang["rights_insert_fehlgeschlagen"];};
      } else {
         echo $lang["rights_insert_fehlgeschlagen"];
      }	   
   } 
  
}

function getauthor4select($select_name, $user){
   global $conf, $lang;

   echo "<select name=" . $select_name . ">";
   echo "<option value=\"\" selected></option>";
   $result = dbquery("select * from acme_author order by author_nachname,author_vorname");
   if ( mysql_num_rows($result) > 0 ){
      while ($row = mysql_fetch_object($result)){
         echo "<option value=" . $row->author_id . ">";
         echo $row->author_nachname . " " . $row->author_vorname;
         echo "</option>";
      }
      mysql_free_result($result);
   }
   echo "</select>";
} 
function getgroup4select($select_name, $group){
   global $conf, $lang;
   
   echo "<select name=" . $select_name . ">";
   echo "<option value=\"\" selected></option>";
   $result = dbquery("select * from acme_groups  order by group_name");
   if ( mysql_num_rows($result) > 0 ){
      while ($row = mysql_fetch_object($result)){
         echo "<option value=" . $row->group_id .">";
         echo $row->group_name . "</option>";
      }
      mysql_free_result($result);
   }
   echo "</select>";
} 
?>  