<?php
switch($action)
   {
   case "edit":
      useredit($edit_user_id);

      break;

   case "new":
      usernew($new_user_name, $new_user_groups, $new_user_passwd, $new_user_active);

      break;

   case "add":
      $result = useradd($new_user_name, $new_user_groups, $new_user_passwd, $new_user_active);
      if ($result){
         echo "insert erfolgreich";
         userbrowse();
      }
      else{
      echo "insert misslungen";
      // useradd($admp, $user_groups, $new_user_name, $new_user_groups, $new_user_passwd, $new_user_active, $new_allow_module, $new_allow_artikel, $new_allow_glossar, $new_allow_pics, $new_allow_bars, $new_allow_blocks, $new_allow_user, $new_allow_groups, $new_allow_prefs);
      }
      break;

	case "update":
      $result = userupdate($edit_user_id, $edit_user_name, $edit_user_groups, $edit_user_passwd, $edit_user_active);
      if ($result){echo "update erfolgreich";}
      else{echo "update misslungen";}
      userbrowse();
      
      break;
      
	case "delete":
      $result = userdelete($delete_id);
      if ($result){echo "delele erfolgreich";}
      else{echo "delete misslungen";}
      userbrowse();
      
      break;

   default:
      userbrowse();
      
      break;
   }
   
function userdelete($delete_id){
   global $conf, $lang;

   $delete_result = dbquery("delete from acme_user where user_id = '". $delete_id . "'");
   
   return $delete_result;
}
   
function useradd($new_user_name, $new_user_groups, $new_user_passwd, $new_user_active){ 
   global $conf, $lang;
   
   $Statement = "INSERT INTO acme_user SET ".
                " user_name   = '" . $new_user_name . "' , ".
                " user_groups = '" . joingrouparray($new_user_groups) ."' , ".
                " user_passwd = '" . $new_user_passwd . "' , ".
                " user_active = '" . $new_user_active . "'";
   $insert_result = dbquery($Statement);
   
   return $insert_result;
}
 
function userupdate($edit_user_id, $edit_user_name, $edit_user_groups, $edit_user_passwd, $edit_user_active){ 
   global $conf, $lang;
   $Statement = "UPDATE acme_user SET ".
                " user_name   = '" . $edit_user_name . "' , ".
                " user_groups = '" . joingrouparray($edit_user_groups) . "' , ".
                " user_passwd = '" . $edit_user_passwd . "' , ".
                " user_active = '" . $edit_user_active . "'  ".
                " WHERE user_id = '" . $edit_user_id . "'";
   $update_result = dbquery($Statement);
   return $update_result;
}
   
function userbrowse(){
   global $conf, $lang;
   
   echo "<h1>User managemant</h1>\n";
	if (checkgroupcreate($conf["user_groups"], "user") == 1){ 
      echo "<a href=\"" . $conf["admp"] . "&action=new&section=user\">Neuen User anlegen</a>\n";
   }
   echo "<table class=\"reda_td\">\n";
   echo "<tr>";
   echo "<td>Username</td>";
   echo "<td>Group</td>";
   echo "<td>Active</td>";
   echo "<td width=\"30\">&nbsp;</td>";
   echo "<td width=\"30\">&nbsp;</td>";
   echo "</tr>\n";
   $result = dbquery("select * from acme_user");
   if ( mysql_num_rows($result) > 0 )
      {	
      while ($row = mysql_fetch_object($result)) 
	      {
         echo "<tr>";	   
         echo "<td>$row->user_name</td>";
         echo "<td>";
         echo getgroupnamesbyarray($row->user_groups);
         echo "</td>";
         echo "<td>" . $row->user_active . "</td>";
         echo "<td>";
         if (checkgroupmodify($conf["user_groups"], "user") == 1){ echo "<a href=\"" . $conf["admp"] . "&section=user&action=edit&edit_user_id=" . $row->user_id . "\"><img src=\"" . $conf["images_admin"] . "icon_edit.png\" width=\"25\" height=\"25\"></a>";}
         echo "</td>";
         echo "<td>";
         if ( $row->user_name != $conf["user_name"] ){
            if (checkgroupdelete($conf["user_groups"], "user") == 1){
               echo "<a href=\"" . $conf["admp"] . "&action=delete&section=user&delete_id=" . $row->user_id . "&delname=" . $row->user_name . "\"><img src=\"" . $conf["images_admin"] . "con_delete.png\" width=\"25\" height=\"25\"></a>";
            }
         }
         else {echo "--you--";}
         echo "</td>";
         echo "</tr>\n"; 
      }
   mysql_free_result($result);
   } 
   echo "</table>";   
} 
  
function usernew(){
   global $conf, $lang;
   
   echo "<h1>Add a new user</h1>";
   echo "<form action=\"" . $conf["admp"] . "&action=add&section=user\" method= \"POST\">";
   echo "<table class=\"reda_td\">";
   echo "<tr><td>Username</td><td><input name=new_user_name size=10 maxlength=20></td></tr>";
   echo "<tr><td>Password:</td><td><input name=new_user_passwd type=password size=8 maxlength=20></td></tr>";
   if (checkgroupcreate($conf["user_groups"], "user") == 1){
      echo "<tr><td>Usergroup</td>";
      echo "<td>";
      createsel_groups("new_user_groups","null");
      echo "</td></tr>";
   }
   echo "<tr><td>Active</td><td><input type=radio name=new_user_active value=\"Y\" checked>Y</input><input type=radio name=new_user_active value=\"N\">N</input></td></tr>";
   echo "<tr><td colspan = \"2\"><input type=submit name=add value=add></td></tr>";
   echo "</table>";
   echo "</form>";
   echo "</table";
}   

function useredit($edit_id){
   global $conf, $lang;
   
   $result = dbquery("select * from acme_user where user_id='". $edit_id . "'");
   if ($result){
      $row = mysql_fetch_object($result);
      echo "\n<h1>Edit User</h1>\n";
      echo "<form action=\"" . $conf["admp"] . "&action=update&section=user&edit_user_id=" . $row->user_id . "\" method=\"POST\">\n";
      echo "<table class=\"reda_td\">\n";
      echo "<tr><td>Username:</td><td><input name=edit_user_name value=\"" . $row->user_name . "\"></td></tr>\n";
      echo "<tr><td>Password:</td><td><input type=password name=edit_user_passwd value=\"" . $row->user_passwd . "\"></td></tr>\n";
      echo "<tr><td>Groups</td><td>\n";
      createsel_groups("edit_user_groups",$row->user_groups);
      echo "</td></tr>\n";
      if ($row->user_name != $conf["user_name"]){
         echo "<tr><td>Active</td><td>";
         echo "<input type=radio name=edit_user_active value=\"Y\""; 
         if ($row->user_active == "Y" ) echo "checked";
         echo ">Y";
         echo "<input type=radio name=edit_user_active value=\"N\""; 
         if ($row->user_active == "N" ) echo "checked";
         echo ">N</td></tr>\n";
      } 
      else {
         echo "<tr><td colspan = \"2\"><input type=hidden name=edit_user_active value=Y></td></tr>";
      }
      echo "<tr><td><input type=submit name=my_edit_user value=Submit></td></tr>\n";
      echo "</table>";
      echo "</form>";
      mysql_free_result($result);
   }
   
}
?>
 