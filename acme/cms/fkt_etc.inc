<?php

function brtonl($str) {
  $str =  preg_replace("=<br(>|([\s/][^>]*)>)\r?\n?=i", "\n", $str);
  return $str;
}
function nltobr($str){
  $str = preg_replace("/\r\n|\r|\n/", "<br />", $str);
  return $str;
}

function parse_bbcode($contblock, $page_tpl){
  global $conf;

  $contblock = eregi_replace("\[list\]","<ul>",$contblock);
  $contblock = eregi_replace("\[/list\]","</ul>",$contblock);
  $contblock = eregi_replace("\[l\]","<li>",$contblock);
  $contblock = eregi_replace("\[/l\]","<li>",$contblock);
  $contblock = eregi_replace("\[h1\]","<h1>",$contblock);
  $contblock = eregi_replace("\[/h1\]","</h1>",$contblock);
  $contblock = eregi_replace("\[h2\]","<h2>",$contblock);
  $contblock = eregi_replace("\[/h2\]","</h2>",$contblock);
  $contblock = eregi_replace("\[h3\]","<h3>",$contblock);
  $contblock = eregi_replace("\[/h3\]","</h3>",$contblock);
  $contblock = eregi_replace("\[h4\]","<h4>",$contblock);
  $contblock = eregi_replace("\[/h4\]","</h4>",$contblock);
  $contblock = eregi_replace("\[h5\]","<h5>",$contblock);
  $contblock = eregi_replace("\[/h5\]","</h5>",$contblock);
  $contblock = eregi_replace("\[p\]","<p>",$contblock);
  $contblock = eregi_replace("\[/p\]","</p>",$contblock);
  $contblock = eregi_replace("\[l\]","<span style = \"font-weight:lighter;\">",$contblock);
  $contblock = eregi_replace("\[/l\]","</span>",$contblock);
  $contblock = eregi_replace("\[b\]","<span style = \"font-weight:bold;\">",$contblock);
  $contblock = eregi_replace("\[/b\]","</b>",$contblock);
  $contblock = eregi_replace("\[bb\]","<span style = \"font-weight:bolder;\">",$contblock);
  $contblock = eregi_replace("\[/bb\]","</span>",$contblock);
  $contblock = eregi_replace("\[i\]","<style = \"font-style:italic;\">",$contblock);
  $contblock = eregi_replace("\[/i\]","</span>",$contblock);
  $contblock = eregi_replace("\[ul\]","<span style = \"text-decoration:underline;\">",$contblock);
  $contblock = eregi_replace("\[/ul\]","</span>",$contblock);
  $contblock = eregi_replace("\[lt\]","<span style = \"text-decoration:line-through;\">",$contblock);
  $contblock = eregi_replace("\[/lt\]","</span>",$contblock);
  $contblock = eregi_replace("\[ol\]","<span style = \"text-decoration:overline;\">",$contblock);
  $contblock = eregi_replace("\[/ol\]","</span>",$contblock);
  $contblock = eregi_replace("\[red\]","<span style = \"color:red;\">",$contblock);
  $contblock = eregi_replace("\[/red\]","</span>",$contblock);
  $contblock = eregi_replace("\[green\]","<span style = \"color:green;\">",$contblock);
  $contblock = eregi_replace("\[/green\]","</span>",$contblock);
  $contblock = eregi_replace("\[blue\]","<span style = \"color:blue;\">",$contblock);
  $contblock = eregi_replace("\[/blue\]","</span>",$contblock);
  $contblock = eregi_replace("\[gray\]","<span style = \"color:gray;\">",$contblock);
  $contblock = eregi_replace("\[/gray\]","</span>",$contblock);
  $contblock = eregi_replace("\[yellow\]","<span style = \"color:yellow;\">",$contblock);
  $contblock = eregi_replace("\[/yellow\]","</span>",$contblock);
  $contblock = eregi_replace("\[maroon\]","<span style = \"color:maroon;\">",$contblock);
  $contblock = eregi_replace("\[/maroon\]","</span>",$contblock);
  $contblock = eregi_replace("\[lime\]","<span style = \"color:lime;\">",$contblock);
  $contblock = eregi_replace("\[/lime\]","</span>",$contblock);
 
  $match = "";
 
  // images
  while (ereg("\[imgright\]([^\[]+)\[/img\]", $contblock, $match)) {
      $contblock = str_replace("[imgright]".$match[1]."[/img]", getimagebyname($match[1], "r", $page_tpl), $contblock);
  }
  while (ereg("\[imgleft\]([^\[]+)\[/img\]", $contblock, $match)) {
      $contblock = str_replace("[imgleft]".$match[1]."[/img]", getimagebyname($match[1], "l", $page_tpl), $contblock);
  }
  while (ereg("\[img\]([^\[]+)\[/img\]", $contblock, $match)) {
      $contblock = str_replace("[img]".$match[1]."[/img]", getimagebyname($match[1], "c", $page_tpl), $contblock);
  }
 
  //$contblock = eregi_replace("\[img\]([^\[]+)\[/img\]", "<img src = \"cms/bilder/\\1\" alt = \"blank\">", $contblock);
  // mail's
  $contblock = eregi_replace("\[mail=&quot;","[mail=\"",$contblock);
  $contblock = eregi_replace("&quot;\]","\"]",$contblock);
  $contblock = eregi_replace("\[mail=\"([^\"]+)\"]([^\[]+)\[/mail\]","<a href=\"mailto:\\1\">\\2</a>",$contblock);
  // url's
  $contblock = eregi_replace("\[url=&quot;","[url=\"",$contblock);
  $contblock = eregi_replace("&quot;\]","\"]",$contblock);
  $contblock = eregi_replace("\[url=\"([^\"]+)\"]([^\[]+)\[/url\]","<a href=\"\\1\" target=\"_blank\">\\2</a>",$contblock);
  // iurl's
  $contblock = eregi_replace("\[iurl=&quot;","[iurl=\"",$contblock);
  $contblock = eregi_replace("&quot;\]","\"]",$contblock);
  $contblock = eregi_replace("\[iurl=\"([^\"]+)\"]([^\[]+)\[/iurl\]","<a href=\"".$conf["indexname"]."url//" . "\\1\">\\2</a>",$contblock);
  // iurllisten ohne ""
  $contblock = eregi_replace("\[iurllist=([0-9]+)\]([^\[]+)\[/iurllist\]","<a href=\"".$conf["indexname"]."urls/" . "\\1\">\\2</a>",$contblock);
  // iurls ohne ""
  $contblock = eregi_replace("\[iurl=([0-9]+)\]([^\[]+)\[/iurl\]","<a href=\"".$conf["indexname"]."url/" . "\\1\">\\2</a>",$contblock);
  // link ohne ""
  $contblock = eregi_replace("\[link=([^\[]+)\]([^\[]+)\[/link\]","<a href=\"\\1\">\\2</a>",$contblock);
  // downloads ohne ""
  $contblock = eregi_replace("\[download=([0-9]+)\]([^\[]+)\[/download\]","<a href=\"".$conf["indexname"]."download/" . "\\1\">\\2</a>",$contblock);
  // downloadlisten ohne ""
  $contblock = eregi_replace("\[downloadlist=([0-9]+)\]([^\[]+)\[/downloadlist\]","<a href=\"".$conf["indexname"]."downloads/" . "\\1\">\\2</a>",$contblock);
  // bilderlisten ohne ""
  $contblock = eregi_replace("\[imglist=([0-9]+)\]([^\[]+)\[/imglist\]","<a href=\"".$conf["indexname"]."bilder/" . "\\1\">\\2</a>",$contblock);
  // glossar
  $contblock = eregi_replace("\[glossar\]([^\[]+)\[/glossar\]","<a href=\"".$conf["indexname"]."glossar/" . "\\1\" target=\"_blank\">\\1</a>",$contblock);
  $contblock = eregi_replace("\[\[([^\[]+)\]\]","<a href=\"".$conf["indexname"]."glossar/" . "\\1\" target=\"_blank\">\\1</a>",$contblock);
  // pagelink
  $contblock = eregi_replace("\[page=&quot;","[page=\"",$contblock);
  $contblock = eregi_replace("&quot;\]","\"]",$contblock);
  $contblock = eregi_replace("\[page=\"([^\"]+)\"]([^\[]+)\[/page\]","<a href=\"".$conf["indexname"]."page/" . "\\1\">\\2</a>",$contblock);
  // pagelink ohne ""
  $contblock = eregi_replace("\[page=([0-9]+)\]([^\[]+)\[/page\]","<a href=\"".$conf["indexname"]."page/" . "\\1\">\\2</a>",$contblock);
  // artikellink
  $contblock = eregi_replace("\[artikel=&quot;","[artikel=\"",$contblock);
  $contblock = eregi_replace("&quot;\]","\"]",$contblock);
  $contblock = eregi_replace("\[artikel=\"([^\"]+)\"]([^\[]+)\[/artikel\]","<a href=\"".$conf["indexname"]."artikel/" . "\\1\">\\2</a>",$contblock);
  // artikellink ohne ""
  $contblock = eregi_replace("\[artikel=([0-9]+)\]([^\[]+)\[/artikel\]","<a href=\"".$conf["indexname"]."artikel/" . "\\1\">\\2</a>",$contblock);
  // artikellink ohne ""
  $contblock = eregi_replace("\[artikel=([0-9]+)-([0-9]+)-([0-9]+)\]([^\[]+)\[/artikel\]","<a href=\"".$conf["indexname"]."artikel/" . "\\1/\\2/\\3\">\\4</a>",$contblock);

  return $contblock;

}

function parse_bar($page_tpl, $bar_id, $side, $bc=""){
   global $conf, $lang;

   $bar = "";

   if ($bar_id <> ""){
      $getbar  = "Select * from ".$conf["db_namespace"]."bar_topics where bar_id = '" . $bar_id . "' order by bar_topic_rank";
      $result  = dbquery($getbar);
      if (mysql_num_rows($result) > 0) {
         while ( $row = mysql_fetch_object($result) ){
            if ($row->bar_topic_type == "navigation") {$bar .= parse_navigation($page_tpl,  $row->bar_topic_type_id, $side, $bc);}
            if ($row->bar_topic_type == "blocks")     {$bar .= parse_block($page_tpl,  $row->bar_topic_type_id, $side);}
         }
         mysql_free_result($result);
      }
      return $bar;
   } else {
   	  return "<!-- leer -->";
   }
}

function get_parent_id($modul, $id){
   global $conf, $lang;
   
   $Statement = "select * from ".$conf["db_namespace"]."module where modul = '" . $modul . "'";
   $result = dbquery($Statement);
   if (mysql_num_rows($result) == 1)  { 
      $row = mysql_fetch_array($result);
      if ($row["parent"] <> ""){
         $Statement = "select ".$row["parent"]." from  ".$conf["db_namespace"].$row["tablename"]." where " . $row["id"] . " = '" . $id ."'";
         $modul_result = dbquery($Statement);
         if (mysql_num_rows($modul_result) == 1)  {
            $modulrow = mysql_fetch_array($modul_result);
            $parent = $modulrow[$row["parent"]];
            mysql_free_result($modul_result);
            return $parent;
         }   
      }
   } 
}

function get_modultable($modul){
   global $conf, $lang;
   
   $Statement = "select * from ".$conf["db_namespace"]."module where modul = '" . $modul . "'";
   $result = dbquery($Statement);
   if (mysql_num_rows($result) == 1)  { 
      $row = mysql_fetch_array($result);
      $table = $row["tablename"];
      return $table;
   }
}
function get_modulname($modul){
   global $conf, $lang;
   
   $Statement = "select * from ".$conf["db_namespace"]."module where modul = '" . $modul . "'";
   $result = dbquery($Statement);
   if (mysql_num_rows($result) == 1)  { 
      $row = mysql_fetch_array($result);
      $table = $row["name"];
      return $table;
   }
}
function get_modulid($modul){
   global $conf, $lang;
   
   $Statement = "select * from ".$conf["db_namespace"]."module where modul = '" . $modul . "'";
   $result = dbquery($Statement);
   if (mysql_num_rows($result) == 1)  { 
      $row = mysql_fetch_array($result);
      $id = $row["id"];
      return $id;
   }
}
function get_modulparent($modul){
   global $conf, $lang;
   
   $Statement = "select * from ".$conf["db_namespace"]."module where modul = '" . $modul . "'";
   $result = dbquery($Statement);
   if (mysql_num_rows($result) == 1)  { 
      $row = mysql_fetch_array($result);
      $parent = $row["parent"];
      return $parent;
   }
    
}
function get_breadcrumbs($modul, $id) {
   global $conf, $lang;

   $queue = array($id);
   $parent = $id;
   do {
     $parent = get_parent_id($modul, $parent);
     if($parent <> "" && $parent <> "0") {array_unshift($queue, $parent);}
   } while ($parent <> "");
   array_unshift($queue, $modul);
   return $queue;
}


function parse_navigation($page_tpl, $nav_id, $side, $bc){
   global $conf, $lang;

   $akt=0;

   $getnav  = "Select * from ".$conf["db_namespace"]."nav where nav_id = '" . $nav_id . "'";
   $result  = dbquery($getnav);
   if (mysql_num_rows($result) > 0) {
      $row = mysql_fetch_object($result);
      $data->nav_name = $row->nav_name;
      mysql_free_result($result);
   }

   $getnavtopics  = "Select * from ".$conf["db_namespace"]."nav_topics where nav_id = '" . $nav_id . "' order by nav_topic_rank";
   $result  = dbquery($getnavtopics);
   if (mysql_num_rows($result) > 0) {
      while ( $row = mysql_fetch_object($result) ){
         $akt++;
         $data->nav_elem[$akt]->nav_elem_img  = getnavimg($row->nav_topic_type, $row->nav_topic_type_id);
         if ($row->nav_topic_type == "Inaktiv"){
            $data->nav_elem[$akt]->nav_elem_url  = "";
            } 
         else {
            $data->nav_elem[$akt]->nav_elem_url  = $conf["indexname"] . $row->nav_topic_type ."/". $row->nav_topic_type_id;
            }   
         $data->nav_elem[$akt]->nav_elem_text = $row->nav_topic_text;
         $data->nav_elem[$akt]->nav_elem_h = 0;
         // sub nav's
         $test = 0;
         $modul = $bc[0];
         if ($row->nav_topic_type == $modul){
            $pos=0; 
            $found=0;
            $modultable  = get_modultable($modul);
            $modulid     = get_modulid($modul);
            $modulparent = get_modulparent($modul);
            $modulname   = get_modulname($modul);
            // suchen und position bestimmen
            foreach($bc as $element) {
               if ($element == $row->nav_topic_type_id) {
                  $found = $pos;
               }
               $pos++;
            }
            // was gefunden dann von dort aus die nav weiter aufklappen
            if ($found <> 0){
               $h_level=1;
               parsenavtree(&$data, $modul, $modultable, $modulparent, $modulid, $modulname, $bc, &$akt, &$found, &$h_level);
            }           
        }
      // end sub nav's
      }
      mysql_free_result($result);
   }
   
   $tplfile= $conf["templates"].gettemplatebyid($page_tpl).".nav.". $side .".tpl";
   return " " . sprintt($data, $tplfile) . " ";
}

function parsenavtree(&$data, $modul, $modultable, $modulparent, $modulid, $modulname, $bc, &$akt, &$walk, &$h_level) {
   global $conf, $lang;

   $walkId = $bc[$walk];
   $lastnav  = "Select ". $modulid . " from ".$conf["db_namespace"].$modultable." where ". $modulparent ." = '" . $walkId . "' and ". $modulparent ." <> '0' order by " . $modulname . "";
   $lastresult  = dbquery($lastnav);
   if (mysql_num_rows($lastresult) > 0) {
      $h_level++;
      while ($lastrow = mysql_fetch_array($lastresult)){
         $akt++;
         $data->nav_elem[$akt]->nav_elem_img  = getnavimg($modul, $lastrow[$modulid]);
         $data->nav_elem[$akt]->nav_elem_url  = $conf["indexname"].$modul."/".$lastrow[$modulid];
         $data->nav_elem[$akt]->nav_elem_text = getnamebymodulandid($modul, $lastrow[$modulid]);
         $data->nav_elem[$akt]->nav_elem_h = $h_level;
         if ($walk < (count($bc)-1)) {
            $walk++;
            if ($bc[$walk] == $lastrow[$modulid]){
               parsenavtree(&$data, $modul, $modultable, $modulparent, $modulid, $modulname, $bc, &$akt, &$walk, &$h_level);
            } else {$walk--;}
         }
      }
      $h_level--;   
   } 
}
function parse_breadcrumbs($data, $bcs){
   global $conf, $lang;
   
   $modul = array_shift($bcs);

   $akt = 0;
   
   if (count($bcs) > 1 || ($bcs[0] <> $conf["home_page"] && $modul == $conf["home_page_typ"])){    
      $data->$modul->bread[$akt]->name = getnamebymodulandid($conf["home_page_typ"], $conf["home_page"]);
      $data->$modul->bread[$akt]->url  = $conf["indexname"].$conf["home_page_typ"] ."/". $conf["home_page"];;
   }
   while (count($bcs) > 0){
   	  $akt++;
  	     $crumb = array_shift($bcs);
 	     if (count($bcs) == 0){
  	  	     $data->$modul->bread[$akt]->name = getnamebymodulandid($modul, $crumb);
  	  	     $data->$modul->bread[$akt]->url  = "";
  	     } else {
  	  	     $data->$modul->bread[$akt]->name = getnamebymodulandid($modul, $crumb);
           $data->$modul->bread[$akt]->url  = $conf["indexname"].$modul."/".$crumb;
    	  }		
   }
}   

function parse_block($page_tpl, $block_id, $side){
   global $conf, $lang;

   $getblock  = "Select * from ".$conf["db_namespace"]."blocks where block_id = '" . $block_id . "'";
   $result  = dbquery($getblock);
   if (mysql_num_rows($result) > 0) {
      $row = mysql_fetch_object($result);
      $data->block->name    = $row->block_name;
      $data->block->typ     = $row->block_type;
      if ($row->block_type == "H"){$data->block->content = $row->block_content;}
      if ($row->block_type == "P"){$data->block->content = OutputPhpDocument($row->block_content);}
      if ($row->block_type == "B"){$data->block->content = parse_bbcode($row->block_content, $page_tpl);}
      if ($row->block_type == "I"){
         $getpic = "Select img_name, img_real_name, img_description from ".$conf["db_namespace"]."bilder where img_id='".$row->block_image."'";
         $result = dbquery($getpic);
         if (mysql_affected_rows() > 0)         {
            $row = mysql_fetch_object($result);
            $data->block->image->name  =  $row->img_name;
            $data->block->image->src   =  $conf["images"] . $row->img_real_name;
            $data->block->image->desc  =  $row->img_description;
         }
         mysql_free_result($result);
      }   
   }
   $tplfile= $conf["templates"].gettemplatebyid($page_tpl).".block.". $side .".tpl";
   return " " . sprintt($data, $tplfile) . " ";
}




function getnamebymodulandid($modul, $id){
   global $conf, $lang;

   $Statement = "select * from ".$conf["db_namespace"]."module where modul = '" . $modul . "'";
   $result = dbquery($Statement);
   if (mysql_num_rows($result) > 0)  { 
      $row = mysql_fetch_array($result);
      $Statement = "select * from  ".$conf["db_namespace"].$row["tablename"]." where " . $row["id"] . " = '" . $id ."'";
      $modul_result = dbquery($Statement);
      if (mysql_num_rows($modul_result) > 0 )  {
         $modulrow = mysql_fetch_array($modul_result);
         $name = $modulrow[$row[name]];
         mysql_free_result($modul_result);
         return $name;
      }
   } 
}


function gettemplatebyid($tpl_id){
   global $conf, $lang;
   
   $tpl = "";
   $my_result = dbquery("select tpl_name from ".$conf["db_namespace"]."templates where tpl_id=".$tpl_id);
   if ( mysql_num_rows($my_result) >0)      {
      $row = mysql_fetch_object($my_result);
      $tpl = $row->tpl_name; // sollte mal das template direkt aus der datenbank holen
      mysql_free_result($my_result);
   }
   return $tpl;
}
function getauthorbyid($id){
   global $conf, $lang;
   $my_result = dbquery("select * from ".$conf["db_namespace"]."author where author_id='".$id."'");
   if ( mysql_num_rows($my_result) == 1 ) {
      $row = mysql_fetch_object($my_result);
      $name = $row->author_vorname . " " . $row->author_nachname ;
      mysql_free_result($my_result);
   }
   return $name;
}   
?>