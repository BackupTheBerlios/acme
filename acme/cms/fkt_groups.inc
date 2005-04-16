<?php
function acl_check($acltyp, $usergroups, $user, $modul, $modulid){
   global $conf, $lang;
   
   // echo "<p>aclcheck: user '" . $user . "' gruppen ". $usergroups . " with acl '". $acltyp."'\n<br>"."select ".$acltyp." from ".$conf["db_namespace"]."acl where modul_name = '" .  $modul . "' and modul_id = '" . $modulid . "' and author_id = '" . $user  . "'"."</p>";   
   
   $acltyp = "acl_".$acltyp;
   $access = 0;
   $result = dbquery("select ".$acltyp." from ".$conf["db_namespace"]."acl where modul_name = '" .  $modul . "' and modul_id = " . $modulid . " and author_id = " . $user  . "");
   if ( mysql_num_rows($result) > 0 )  {
   	  $row = mysql_fetch_object($result);
   	  if($row->$acltyp == "Y") {
//   	  	echo "<p>found user '" . $user ."' in acl '". $acltyp."'\n</p>";
   	  	$aclresult = 1;
   	  	} 
   } else {
     $singlegroups = explode(":", $usergroups);
     while ( list ($key, $value) = each ($singlegroups) ) {
         if ( $value != "" ){
            $result = dbquery("select ".$acltyp." from ".$conf["db_namespace"]."acl where modul_name = '" .  $modul . "' and modul_id = " . $modulid . " and group_id = " . $value  . "");
            if ( mysql_num_rows($result) > 0 )  {
               $row = mysql_fetch_object($result);
               if($row->$acltyp == "Y") {
//              	echo "<p>found group '" . $value ."' in acl '". $acltyp."'\n</p>";
               	$aclresult = 1;
               	}
            } 
         } 
      }
   }
   return $aclresult;
}

function acl_user_set($user, $modul, $modulid, $rights, $insert, $edit, $delete){
   global $conf, $lang;
   
   $result = dbquery("select author_id from ".$conf["db_namespace"]."acl where modul_name = '" .  $modul . "' and modul_id = '" . $modulid . "' and author_id = '" . $user  . "'");
   if ( mysql_num_rows($result) > 0 )  {
      $result = dbquery("update ".$conf["db_namespace"]."acl set acl_rights = '".$rights."', acl_insert = '".$insert."', acl_edit = '".$edit."', acl_delete = '".$delete."' where  modul_name = '" .  $modul . "' and modul_id = '" . $modulid . "' and author_id = '".$user."'");
   } else {
      $result = dbquery("insert into ".$conf["db_namespace"]."acl set acl_rights = '".$rights."', acl_insert = '".$insert."', acl_edit = '".$edit."', acl_delete = '".$delete."', modul_name = '" .  $modul . "', modul_id = '" . $modulid . "', author_id = '".$user."'");
   }
   if (!$result) {
   die('Ungültige Abfrage: ' . mysql_error());
}
   
   return $result; 
}

function acl_group_set($group, $modul, $modulid, $rights, $insert, $edit, $delete){
   global $conf, $lang;
   
   $result = dbquery("select author_id from ".$conf["db_namespace"]."acl where modul_name = '" .  $modul . "' and modul_id = '" . $modulid . "' and group_id = '" . $group  . "''");
   if ( mysql_num_rows($result) > 0 )  {
      $result = dbquery("update ".$conf["db_namespace"]."acl set acl_rights = '".$rights."', acl_insert = '".$insert."', acl_edit = '".$edit."', acl_delete = '".$delete."' where  modul_name = '" .  $modul . "' and modul_id = '" . $modulid . "' and group_id = '".$group."'");
   } else {
      $result = dbquery("insert into ".$conf["db_namespace"]."acl (acl_rights = '".$rights."', acl_insert = '".$insert."', acl_edit = '".$edit."', acl_delete = '".$delete."', modul_name = '" .  $modul . "', modul_id = '" . $modulid . "', group_id = '".$group."')");
   }
   return $result; 
}
function acl_delete($modul, $modulid){
   global $conf, $lang;
   
   $access = 0;
   $result = dbquery("select * from ".$conf["db_namespace"]."acl where modul_name = '" .  $modul . "' and modul_id = '" . $modulid . "'");
   if ( mysql_num_rows($result) > 0 )  {
      $result = dbquery("delete from ".$conf["db_namespace"]."acl where modul_name = '" .  $modul . "' and modul_id = '" . $modulid . "'");
   } else {
   	  return true;
   }
   return $result; 
}

function acl_user_delete($user, $modul, $modulid){
   global $conf, $lang;
   
   $access = 0;
   $result = dbquery("select author_id from ".$conf["db_namespace"]."acl where modul_name = '" .  $modul . "' and modul_id = '" . $modulid . "' and author_id = '" . $user  . "'");
   if ( mysql_num_rows($result) > 0 )  {
      $result = dbquery("delete from ".$conf["db_namespace"]."acl where modul_name = '" .  $modul . "' and modul_id = '" . $modulid . "' and author_id = '".$user."'");
   } else {
   	  return true;
   }
   return $result; 
}

function acl_group_delete($group, $modul, $modulid){
   global $conf, $lang;
   
   $access = 0;
   $result = dbquery("select author_id from ".$conf["db_namespace"]."acl where modul_name = '" .  $modul . "' and modul_id = '" . $modulid . "' and group_id = '" . $group  . "''");
   if ( mysql_num_rows($result) > 0 )  {
      $result = dbquery("delete from ".$conf["db_namespace"]."acl where modul_name = '" .  $modul . "' and modul_id = '" . $modulid . "' and group_id = '".$group."'");
   } else {
   	  return true;
   }
   return $result; 
}

function joingrouparray($grouparray){
   
   global $conf, $lang;
   
    while ( list ($key, $value) = each ($grouparray) )      {
         $returnstring .= ":$value";
         }
   $returnstring .= ":";
   return $returnstring;
}

function acl_checkuseringroup($usergroups, $group){
   $result = 0;
   $usergroups = explode(":", $usergroups);
   foreach ($usergroups as $sgroup){
     if ($sgroup == $group) {$result = 1;}
   }
   return $result;
}
function checkgroupaccess($usergroups, $modul){   return 1;}
function checkgroupcreate($usergroups, $modul){   return 1;}
function checkgroupmodify($usergroups, $modul){   return 1;}
function checkgroupdelete($usergroups, $modul){   return 1;}

function explodegroup($grouplist)
{
   global $conf, $lang;
   $grouparray = explode(":", $grouplist);
   return($grouparray);
}



function getgroupsbyarray($groups){
   global $conf, $lang;
   
   $singlegroups = explode(":", $groups);
   while (list ($key, $value) = each ($singlegroups) ) {
        if ($value <> "") $names = $names . $value . "<br>";
         }
   return substr($names, 0, strlen($names) - 4);
}

function getgroupnamesbyarray($groups) {
   global $conf, $lang;
   
   $groupnames = "";
   $allgroups = dbquery("select * from ".$conf["db_namespace"]."groups");
   if ( mysql_num_rows($allgroups) > 0 ) {
      while ($g_row = mysql_fetch_object($allgroups)) {
         if (eregi ($g_row->group_id, $groups)) { 
            $groupnames = $groupnames . $g_row->group_name; 
            $groupnames = $groupnames . "<br>";
         }
      }
      mysql_free_result($allgroups);
   }
   return $groupnames;
}   


function getgroupnamebyid($group) {
   global $conf, $lang;
   
   $groupnames = "";
   $allgroups = dbquery("select * from ".$conf["db_namespace"]."groups where group_id = '" . $group . "'");
   if ( mysql_num_rows($allgroups) > 0 ) {
      while ($g_row = mysql_fetch_object($allgroups)) {
         $groupnames = $groupnames . $g_row->group_name; 
      }
      mysql_free_result($allgroups);
   }
   return $groupnames;
}  
?>