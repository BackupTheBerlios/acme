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
  $contblock = eregi_replace("\[b\]","<b>",$contblock);
  $contblock = eregi_replace("\[/b\]","</b>",$contblock);
  $contblock = eregi_replace("\[i\]","<i>",$contblock);
  $contblock = eregi_replace("\[/i\]","</i>",$contblock);
  $contblock = eregi_replace("\[u\]","<u>",$contblock);
  $contblock = eregi_replace("\[/u\]","</u>",$contblock);
  // images
  while (ereg("\[imgr\]([^\[]+)\[/imgr\]", $contblock, $match)) {
      $contblock = str_replace("[imgr]".$match[1]."[/imgr]", getimagebyname($match[1], "r", $page_tpl), $contblock);
  }
  while (ereg("\[imgl\]([^\[]+)\[/imgl\]", $contblock, $match)) {
      $contblock = str_replace("[imgl]".$match[1]."[/imgl]", getimagebyname($match[1], "l", $page_tpl), $contblock);
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
  $contblock = eregi_replace("\[iurl=\"([^\"]+)\"]([^\[]+)\[/iurl\]","<a href=\"".$conf["indexname"]."url//" . "\\1\" target=\"_blank\">\\2</a>",$contblock);
  // glossar
  $contblock = eregi_replace("\[glossar\]([^\[]+)\[/glossar\]","<a href=\"".$conf["indexname"]."glossar/" . "\\1\" target=\"_blank\">\\1</a>",$contblock);
  $contblock = eregi_replace("\[\[([^\[]+)\]\]","<a href=\"".$conf["indexname"]."glossar/" . "\\1\" target=\"_blank\">\\1</a>",$contblock);
  // pagelink
  $contblock = eregi_replace("\[page=&quot;","[page=\"",$contblock);
  $contblock = eregi_replace("&quot;\]","\"]",$contblock);
  $contblock = eregi_replace("\[page=\"([^\"]+)\"]([^\[]+)\[/page\]","<a href=\"".$conf["indexname"]."page/" . "\\1\" target=\"_blank\">\\2</a>",$contblock);
  // artikellink
  $contblock = eregi_replace("\[artikel=&quot;","[artikel=\"",$contblock);
  $contblock = eregi_replace("&quot;\]","\"]",$contblock);
  $contblock = eregi_replace("\[artikel=\"([^\"]+)\"]([^\[]+)\[/artikel\]","<a href=\"".$conf["indexname"]."artikel/" . "\\1\" target=\"_blank\">\\2</a>",$contblock);

  return $contblock;

}



function parse_bar($page_tpl, $bar_id, $side){
global $conf, $lang;

if ($bar_id<>""){
   $getbar  = "Select * from acme_bar_topics where bar_id = '" . $bar_id . "' order by bar_topic_rank";
   $result  = dbquery($getbar);
   if (mysql_num_rows($result) > 0) {
      while ( $row = mysql_fetch_object($result) ){
         if ($row->bar_topic_type == "navigation"){$bar .= parse_navigation($page_tpl,  $row->bar_topic_type_id, $side);}
         if ($row->bar_topic_type == "blocks")     {$bar .= parse_block($page_tpl,  $row->bar_topic_type_id, $side);}
      }
      mysql_free_result($result);
   }
   return $bar;
}else {return "<!-- leer -->";}
}

function parse_navigation($page_tpl, $nav_id, $side){
   global $conf, $lang;

   $getnav  = "Select * from acme_nav where nav_id = '" . $nav_id . "'";
   $result  = dbquery($getnav);
   if (mysql_num_rows($result) > 0) {
      $row = mysql_fetch_object($result);
      $data->nav_name = $row->nav_name;
      mysql_free_result($result);
   }

   $getnavtopics  = "Select * from acme_nav_topics where nav_id = '" . $nav_id . "' order by nav_topic_rank";
   $result  = dbquery($getnavtopics);
   if (mysql_num_rows($result) > 0) {
      while ( $row = mysql_fetch_object($result) ){
         $akt++;
         $data->nav_elem[$akt]->nav_elem_img  = getnavimg($row->nav_topic_type, $row->nav_topic_type_id);
         if ($row->nav_topic_type == "Inaktiv"){
            $data->nav_elem[$akt]->nav_elem_url  = "";
         } else {   
            $data->nav_elem[$akt]->nav_elem_url  = $conf["indexname"] . $row->nav_topic_type ."/". $row->nav_topic_type_id;
         }   
         $data->nav_elem[$akt]->nav_elem_text = $row->nav_topic_text;
         // sub nav's
         if ($row->nav_topic_type == "page" && $conf["page"] == "page" && ($conf["page_id"] == $row->nav_topic_type_id || $conf["page_parent_id"] == $row->nav_topic_type_id)){
            $getsubnavtopics  = "Select * from acme_pages where page_parent = '" . $row->nav_topic_type_id . "' order by page_name";
            $subresult  = dbquery($getsubnavtopics);
            if (mysql_num_rows($subresult) > 0) {
               while ($subrow = mysql_fetch_object($subresult) ){
                  $subakt++;
                  $data->nav_elem[$akt]->nav_sub_elem[$subakt]->nav_sub_elem_img  = getnavimg($subrow->nav_topic_type, $subrow->nav_topic_type_id);
                  $data->nav_elem[$akt]->nav_sub_elem[$subakt]->nav_sub_elem_url  = $conf["indexname"]."page/".$subrow->page_id;
                  $data->nav_elem[$akt]->nav_sub_elem[$subakt]->nav_sub_elem_text = $subrow->page_name;
               }
               mysql_free_result($subresult);
            }
           
         }
         // end sub nav's
      }
      mysql_free_result($result);
   }
   $tplfile= $conf["templates"].gettemplatebyid($page_tpl).".nav.". $side .".tpl";
   return " " . sprintt($data, $tplfile) . " ";
}

function parse_block($page_tpl, $block_id, $side){
   global $conf, $lang;

   $getblock  = "Select * from acme_blocks where block_id = '" . $block_id . "'";
   $result  = dbquery($getblock);
   if (mysql_num_rows($result) > 0) {
      $row = mysql_fetch_object($result);
      $data->block_name    = $row->block_name;
      if ($row->block_type == "H"){$data->block_content = $row->block_content;}
      if ($row->block_type == "P"){$data->block_content = OutputPhpDocument($row->block_content);}
      mysql_free_result($result);
   }
   $tplfile= $conf["templates"].gettemplatebyid($page_tpl).".block.". $side .".tpl";
   return " " . sprintt($data, $tplfile) . " ";
}


function getnavimg($modul, $id){
   global $conf, $lang;

   $result = dbquery("select * from acme_module where modul = '". $modul . "'");
   if ( mysql_num_rows($result) == 1 )  {
      $row = mysql_fetch_object($result);
      $Statement = "select * from " . $row->tablename . " where " . $row->id . " = '". $id . "'";
      $modul_result = dbquery($Statement);
      if ( mysql_num_rows($modul_result) > 0 )  {
         $modulrow = mysql_fetch_array($modul_result);
         $picid_a = $modulrow[$row->navimg] ;
         $picid_p = $modulrow[$row->navimg."_inactive"] ;
      }
      mysql_free_result($modul_result);
   }

   if ( $picid_a ){
      $getpic = "Select img_name, img_real_name, img_description from acme_bilder where img_id='".$picid_a."'";
      dbconnect();
      $result = dbquery($getpic);
      if(mysql_affected_rows() > 0)         {
         $row = mysql_fetch_object($result);
         $act_pic->name  =  $row->img_name;
         $act_pic->src   =  $conf["images"] . $row->img_real_name;
         $act_pic->desc  =  $row->img_description;
      }
      mysql_free_result($result);
   }
   if ( $picid_p ){
      $getpic = "Select img_name, img_real_name, img_description from acme_bilder where img_id='".$picid_p."'";
      dbconnect();
      $result = dbquery($getpic);
      if(mysql_affected_rows() > 0)         {
         $row = mysql_fetch_object($result);
         $pas_pic->name  =  $row->img_name;
         $pas_pic->src   =  $conf["images"] . $row->img_real_name;
         $pas_pic->desc  =  $row->img_description;
      }
      mysql_free_result($result);
   }
   
   $navimg->act = $act_pic;
   $navimg->pas = $pas_pic;
   return $navimg;
}

function gethomeimg(){
   global $conf, $lang;

   $getpic = "Select img_real_name, img_description from acme_bilder where img_id='".$conf["home_img"]."'";
   $result = dbquery($getpic);
   if(mysql_affected_rows() > 0)         {
      $row = mysql_fetch_object($result);
      return "<img class = \"logo\"src = \"" . $conf["images"] . $row->img_real_name."\" alt = \"" . $row->img_description . "\">";
   }
   else{
      return "<img src = \"" . $conf["images"]."pixel.gif\" alt = \"blank\">";
   }
   mysql_free_result($result);
}

function gethomenavimg(){
   global $conf, $lang;

   $Statement = "select page_img_small from acme_pages where page_id = '". $conf["home_page"] . "'";
   $modul_result = dbquery($Statement);
   if ( mysql_num_rows($modul_result) > 0 )  {
      $modulrow = mysql_fetch_array($modul_result);
      $picid = $modulrow["page_img_small"] ;
   }
   $getpic = "Select img_real_name, img_description from acme_bilder where img_id='".$picid."'";
   $result = dbquery($getpic);
   if(mysql_affected_rows() > 0)         {
      $row = mysql_fetch_object($result);
      return "<img class = \"nav_elem_img\"src = \"" . $conf["images"] . $row->img_real_name."\" alt = \"" . $row->img_description . "\">";
   }
   else{
      return "<img src = \"" . $conf["images"]."pixel.gif\" alt = \"blank\">";
   }
   mysql_free_result($result);
}

function getimagebyname($name, $style,$page_tpl){
   global $conf, $lang;

   $getpic = "Select img_real_name, img_name, img_description from acme_bilder where img_name  like'%" . $name . "%' ";
   $result = dbquery($getpic);
   if(mysql_affected_rows() == 1)         {
      $row = mysql_fetch_object($result);
      if (file_exists($conf["images"] . $row->img_real_name)){
         // vorsichtshalber wegen altdaten
         if (file_exists($conf["images"] . "small_".$row->img_real_name)){
            list($width, $height, $type, $attr) = getimagesize($conf["images"] . "small_".$row->img_real_name);
         } else {
            list($width, $height, $type, $attr) = getimagesize($conf["images"] . $row->img_real_name);      
         }
         $data->img_width  = $width;
         $data->img_height = $height;
         // vorsichtshalber wegen altdaten
         if (file_exists($conf["images"] . "thumb_".$row->img_real_name)){
            $data->img_small_url    = $conf["images"] . "thumb_" . $row->img_real_name;
         }else{
            $data->img_small_url    = $conf["images"] . $row->img_real_name;
         }
         // vorsichtshalber wegen altdaten
         if (file_exists($conf["images"] . "small_".$row->img_real_name)){
            $data->img_small_url    = $conf["images"] . "small_" . $row->img_real_name;
         }else{
            $data->img_small_url    = $conf["images"] . $row->img_real_name;
         }  
         $data->img_big_url      = $conf["images"] . $row->img_real_name;
         $data->img_name   = $row->img_name;
         $data->img_desc   = $row->img_description;

         if ($style==""){$style="c";}
         $tplfile= $conf["templates"].gettemplatebyid($page_tpl).".imgtbl.". $style .".tpl";
         return " " . sprintt($data, $tplfile) . " ";
      }
      else {
      	 return " ";
      }	
   }   

   mysql_free_result($result);
}

function getimagebyid($id, $style,$page_tpl){
   global $conf, $lang;

   $getpic = "Select img_real_name, img_name, img_description from acme_bilder where img_id = '" . $id . "'";
   $result = dbquery($getpic);
   if(mysql_affected_rows() == 1)         {
      $row = mysql_fetch_object($result);
      // vorsichtshalber wegen altdaten
      if (file_exists($conf["images"] . "small_".$row->img_real_name)){
         list($width, $height, $type, $attr) = getimagesize($conf["images"] . "small_".$row->img_real_name);
      } else {
         list($width, $height, $type, $attr) = getimagesize($conf["images"] . $row->img_real_name);      
      }
      $data->img_width  = $width;
      $data->img_height = $height;
      // vorsichtshalber wegen altdaten
      if (file_exists($conf["images"] . "thumb_".$row->img_real_name)){
         $data->img_small_url    = $conf["images"] . "thumb_" . $row->img_real_name;
      }else{
         $data->img_small_url    = $conf["images"] . $row->img_real_name;
      }
      // vorsichtshalber wegen altdaten
      if (file_exists($conf["images"] . "small_".$row->img_real_name)){
         $data->img_small_url    = $conf["images"] . "small_" . $row->img_real_name;
      }else{
         $data->img_small_url    = $conf["images"] . $row->img_real_name;
      }  
      $data->img_big_url      = $conf["images"] . $row->img_real_name;
      $data->img_name   = $row->img_name;
      $data->img_desc   = $row->img_description;
   }
   if ($style==""){$style="c";}
   $tplfile= $conf["templates"].gettemplatebyid($page_tpl).".imgtbl.". $style .".tpl";
   return " " . sprintt($data, $tplfile) . " ";

   mysql_free_result($result);
}

?>