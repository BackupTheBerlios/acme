<?php

function joingrouparray($grouparray)
{
   global $conf, $lang;

    while ( list ($key, $value) = each ($grouparray) )      {
         $returnstring .= ":$value";
         }
   $returnstring .= ":";
   return $returnstring;
}

function checkingroup($usergroups, $group)
{
   global $conf, $lang;

   $result = 0;
   
   $usergroups = explode(":", $usergroups);
   if (eregi ($group, $usergroups)) { $result = 1;}
   
   return $result;
}

function checkgroupaccess($usergroups, $modul)
{
   global $conf, $lang;
   $groupaccess = 0;
   $singlegroups = explode(":", $usergroups);
   while ( list ($key, $value) = each ($singlegroups) )
      {
      if ( $value != "" )
         {
         $result = dbquery("select rights_access from acme_rights where modul = '" .  $modul . "' and group_id = '" . $value  . "'");
         if ( mysql_num_rows($result) > 0 )  { 
            $row = mysql_fetch_object($result);  
            if($row->rights_access == "Y"){ $groupaccess = 1;}
            } 
         }
      }
   return $groupaccess;
}

function checkgroupcreate($usergroups, $modul)
{
   global $conf, $lang;
   $groupcreate = 0;
   $singlegroups = explode(":", $usergroups);
   while ( list ($key, $value) = each ($singlegroups) )
      {
      if ( $value != "" )
         {
         $result = dbquery("select rights_create from acme_rights where modul = '" .  $modul . "' and group_id = '" . $value  . "'");
         if ( mysql_num_rows($result) > 0 )  {
             $row = mysql_fetch_object($result);
             if($row->rights_create== "Y") {$groupcreate = 1;}
             } 
         }
      }
   return $groupcreate;
}

function checkgroupmodify($usergroups, $modul)
{
   global $conf, $lang;
   $groupmodify = 0;
   $singlegroups = explode(":", $usergroups);
   while ( list ($key, $value) = each ($singlegroups) )
      {
      if ( $value != "" )
         {
         $result = dbquery("select rights_modify from acme_rights where modul = '" .  $modul . "' and group_id = '" . $value  . "'");
         if ( mysql_num_rows($result) > 0 )  { 
            $row = mysql_fetch_object($result);
            if($row->rights_modify == "Y"){ $groupmodify = 1;}
            } 
         }
      }
   return $groupmodify;
}

function checkgroupdelete($usergroups, $modul)
{
   global $conf, $lang;
   $groupdelete = 0;
   $singlegroups = explode(":", $usergroups);
   while ( list ($key, $value) = each ($singlegroups) )
      {
      if ( $value != "" )
         {
         $result = dbquery("select rights_delete from acme_rights where modul = '" .  $modul . "' and group_id = '" . $value  . "'");
         if ( mysql_num_rows($result) > 0 )  { 
            $row = mysql_fetch_object($result);
            if($row->rights_delete == "Y"){ $groupdelete = 1;}
            } 
         }
      }
   return $groupdelete;
}

function explodegroup($grouplist)
{
   global $conf, $lang;
   $grouparray = explode(":", $grouplist);
   return($grouparray);
}

function getfirstpageid($list)
{
   global $conf, $lang;
   
   $listarray = explode(":", $list);
   while (list ($key, $value) = each ($listarray) ) {
      if ($value <> "") {return $value;}
      }
}

function getgroupsbyarray($groups)
{
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
   $allgroups = dbquery("select * from acme_groups");
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
   $allgroups = dbquery("select * from acme_groups where group_id = '" . $group . "'");
   if ( mysql_num_rows($allgroups) > 0 ) {
      while ($g_row = mysql_fetch_object($allgroups)) {
         $groupnames = $groupnames . $g_row->group_name; 
      }
      mysql_free_result($allgroups);
   }
   return $groupnames;
}  

function getgrouprights($modul,$usergroups)
{
   global $conf, $lang;
   $groupaccess = "";
   $singlegroups = explode(":", $usergroups);
   while ( list ($key, $value) = each ($singlegroups) ){
      if ( $value != "" ){
         $result = dbquery("select * from acme_rights where modul = '" .  $modul . "' and group_id = '" . $value  . "'");
         if ( mysql_num_rows($result) > 0 )  { 
            //$groupaccess .= getgroupnamebyid($value);
            $row = mysql_fetch_object($result);  
            if($row->rights_create == "Y"){ $groupaccess .= " C:Y";} else { $groupaccess .= " C:N";}
            if($row->rights_modify == "Y"){ $groupaccess .= " M:Y";} else { $groupaccess .= " M:N";}
            if($row->rights_delete == "Y"){ $groupaccess .= " D:Y";} else { $groupaccess .= " D:N";}
            $groupaccess .= "<br>";         
         } 
      }

   }
   return $groupaccess;
}
?>