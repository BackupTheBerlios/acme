<?php
function getpageheadlinebyid($id)
{
   global $conf, $lang;
   $my_result = dbquery("select page_headline from ".$conf["db_namespace"]."pages where page_id='".$id."'");
   if ( mysql_num_rows($my_result) == 1 )
      {
      $row = mysql_fetch_object($my_result);
      $headline = $row->page_headline;
      mysql_free_result($my_result);
      return $headline;
      }
}
function getpagenamebyid($id)
{
   global $conf, $lang;
   $my_result = dbquery("select page_name from ".$conf["db_namespace"]."pages where page_id='".$id."'");
   if ( mysql_num_rows($my_result) == 1 )
      {
      $row = mysql_fetch_object($my_result);
      $name = $row->page_name;
      mysql_free_result($my_result);
      return $name;
      }
}
      
function getpagenamebyidarray($ids){
   global $conf, $lang;
   
   $names = "";
   $singlegroups = explode(":", $ids);
   while ( list ($key, $value) = each ($singlegroups) ) {
      $my_result = dbquery("select page_name from ".$conf["db_namespace"]."pages where page_id='".$value."'");
      if ( mysql_num_rows($my_result) == 1 ) {
         $row = mysql_fetch_object($my_result);
         if ($names == "") {$names = $row->page_name;}
         else {$names = $names . "<br>" . $row->page_name;}
         mysql_free_result($my_result);
      }
   }       
   return $names;
}
?>
