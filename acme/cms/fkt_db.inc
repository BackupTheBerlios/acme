<?php
function dbpconnect()
{
   global $conf, $lang;
   mysql_pconnect($conf["dbhost"],$conf["dbuser"],$conf["dbpass"]) or die("Unable to connect to databases server!");
   return;
}

function admpconnect()
{
   global $conf, $lang;
   mysql_pconnect($conf["dbhost"],$conf["dbadmuser"],$conf["dbadmpass"]) or die("Unable to connect to databases server!");
   return;
}

function dbconnect()
{
   global $conf, $lang;
   mysql_connect($conf["dbhost"],$conf["dbuser"],$conf["dbpass"]) or die("Unable to connect to databases server!");;
   return;
}

function dbquery($sqlcommand)
{
   global $conf, $lang;
   $func_result = mysql_db_query($conf["dbname"], $sqlcommand);
   return $func_result;
}

function checkmodul($page){
   global $conf, $lang;
   
   $found = false;
   $result = dbquery("select modul from acme_module order by modul");
   if ( mysql_num_rows($result) > 0 )           {
      while ($row = mysql_fetch_object($result)) {
      	if ($page==$row->modul){$found = true;break;}
      }
   }
   return $found;
}      	   

function getimage($picid)
{
   if( $picid )
      {
      $getpic = "Select img_real_name, img_description from acme_bilder where img_id='".$picid."'";
      dbconnect();
      $result = dbquery($getpic);
      if(mysql_affected_rows() > 0)
         {
         $row = mysql_fetch_object($result);
         return "<img src = \"cms/bilder/" . $row->img_real_name."\" alt = \"" . $row->img_description . "\">";
         }
      else
         {
         return "<img src = \"cms/bilder/pixel.gif\" alt = \"blank\">";
         }
      mysql_free_result($result);
      }
    else
      {
      return "<img src = \"cms/bilder/pixel.gif\" alt = \"blank\">";
      }
}

function getimagenamebyid($picid){
   global $conf, $lang;

   if( $picid ){
      $getpic = "Select img_name from acme_bilder where img_id='".$picid."'";
      $result = dbquery($getpic);
      if(mysql_affected_rows() > 0)         {
         $row = mysql_fetch_object($result);
         return $row->img_name;
         mysql_free_result($result);
      }
   }
}      

function getbarfromcache($barid)  {
   if( isset($barid)) {
      $getbar = "Select bar_cache from acme_bar where bar_id='$barid'";
      dbconnect();
      $result = dbquery($getbar);
      if(mysql_affected_rows() > 0)
         {
         $row = mysql_fetch_object($result);
         return $row->bar_cache;
         }
      else
         {
         return "<img src = \"cms/bilder/pixel.gif\" alt = \"blank\">";
         }
      mysql_free_result($result);

      }
   else  {return "<img src = \"cms/bilder/pixel.gif\" alt = \"blank\">";}
}


function getpageheadlinebyid($id)
{
   global $conf, $lang;
   $my_result = dbquery("select page_headline from acme_pages where page_id='".$id."'");
   if ( mysql_num_rows($my_result) == 1 )
      {
      $row = mysql_fetch_object($my_result);
      $headline = $row->page_headline;
      mysql_free_result($my_result);
      return $headline;
      }
}

function getpageidbyname($name)
{
   global $conf, $lang;
   $my_result = dbquery("select page_id from acme_pages where page_name='".$name."'");
   if ( mysql_num_rows($my_result) == 1 )
      {
      $row = mysql_fetch_object($my_result);
      $id = $row->page_id;
      mysql_free_result($my_result);
      return $id;
      }
}
function getpagenamebyid($id)
{
   global $conf, $lang;
   $my_result = dbquery("select page_name from acme_pages where page_id='".$id."'");
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
      $my_result = dbquery("select page_name from acme_pages where page_id='".$value."'");
      if ( mysql_num_rows($my_result) == 1 ) {
         $row = mysql_fetch_object($my_result);
         if ($names == "") {$names = $row->page_name;}
         else {$names = $names . "<br>" . $row->page_name;}
         mysql_free_result($my_result);
      }
   }       
   return $names;
}

      
function getbarnamebyid($id)
{
   global $conf, $lang;
   $my_result = dbquery("select bar_name from acme_bar where bar_id='".$id."'");
   if ( mysql_num_rows($my_result) == 1 )
      {
      $row = mysql_fetch_object($my_result);
      $name = $row->bar_name;
      mysql_free_result($my_result);
      return $name;
      }
}

function getblocknamebyid($id)
{
   global $conf, $lang;
   $my_result = dbquery("select block_name from acme_blocks where block_id='".$id."'");
   if ( mysql_num_rows($my_result) == 1 )
      {
      $row = mysql_fetch_object($my_result);
      $name = $row->block_name;
      mysql_free_result($my_result);
      return $name;
      }
}

function getblockcontentbyid($id)
{
   global $conf, $lang;
   $my_result = dbquery("select block_content from acme_blocks where block_id='".$id."'");
   if ( mysql_num_rows($my_result) == 1 )
      {
      $row = mysql_fetch_object($my_result);
      $name = $row->block_content;
      mysql_free_result($my_result);
      return $name;
      }
}



function artikel_gethighestpart($artikel_id){
   global $conf, $lang;
   $my_result = dbquery("select * from acme_artikel_daten where artikel_id='".$artikel_id."'");
   $partmax = mysql_num_rows($my_result);
   mysql_free_result($my_result);
   return $partmax;
}


function gettemplatebyid($tpl_id)
{
   global $conf, $lang;
   $my_result = dbquery("select tpl_name from acme_templates where tpl_id=".$tpl_id);
   if ( mysql_num_rows($my_result) >0)      {
      $row = mysql_fetch_object($my_result);
      $tpl = $row->tpl_name; // sollte mal das template direkt aus der datenbank holen
      mysql_free_result($my_result);
   return $tpl;
   }
}

function getimagedescription($img_id)
{
    $getpic = "Select img_description from acme_bilder where img_id=".$img_id;
    dbconnect();
    $result = dbquery($getpic);
    if(mysql_affected_rows() > 0)
    {
      $row = mysql_fetch_object($result);
      return $row->img_descrition;
	}
	mysql_free_result($result);
}

function getauthorbyid($id)
{
   global $conf, $lang;
   $my_result = dbquery("select * from acme_author where author_id='".$id."'");
   if ( mysql_num_rows($my_result) == 1 ) {
      $row = mysql_fetch_object($my_result);
      $name = $row->author_vorname . " " . $row->author_nachname ;
      mysql_free_result($my_result);
   }
   return $name;
}      


function getuserbyid($id)
{
   global $conf, $lang;
   $my_result = dbquery("select * from acme_user where user_id='".$id."'");
   if ( mysql_num_rows($my_result) == 1 )
      {
      $row = mysql_fetch_object($my_result);
      $name = $row->user_name;
      mysql_free_result($my_result);
      return $name;
      } else return "";
}      

?>
