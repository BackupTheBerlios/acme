<?php 
/*
  platzhalter für die downloads:

  gültig innerhalb{mask:main}
     titel                Seitenüberschrift
     left_bar				  linke Navigation
     right_bar            rechte Navigation
     top_bar              obere Navigation
     foo_bar              untere Navigation
     home_img
     home_url
     gültig innerhalb {mask:downloads} 
        name 				
        img_small
        img_big
        text
        {mask:parent}            
           name	  Überschrift Elternseite
           url		  href Elternseite
        {/mask:page_parent}  
        gültig innerhalb {mask:download_childs}  // unterkategorien
           name
           url
        gültig innerhalb {mask:download_data}    // downloads zu dieser kategorie
           name
           file
           text

*/ 
if ($page="download"){
   renderdownloads($download_typ_id, $download_id);
   }
  
function renderdownloads($id, $download_id){
   global $conf, $lang;
        
   if (($id == "" || $id == "0") && isset($did)){
   	  $query = "select * from ".$conf["db_namespace"]."download where download_id =".$download_id;
      $result = dbquery($query);
      if ( mysql_num_rows($result) > 0 ){
         $row = mysql_fetch_object($result);
         $id = getfirstdownloadtypid($row->download_typ);
      }   
   	  
   } 

   $my_result = dbquery("select * from ".$conf["db_namespace"]."download_typs where download_typ_id='".$id."'");
   if ( mysql_num_rows($my_result) == 1 )   {
      $row = mysql_fetch_object($my_result);
      $download_typ_id        = $row->download_typ_id;
      $download_typ_parent    = $row->download_typ_parent_id;
      $download_typ_name      = $row->download_typ_name;
      $download_typ_tpl       = $row->download_typ_tpl;
      $download_typ_img_small = $row->download_typ_img_small;
      $download_typ_img_big   = $row->download_typ_img_big;
      $download_typ_left_bar  = $row->download_typ_left_bar;
      $download_typ_right_bar = $row->download_typ_right_bar;
      $download_typ_top_bar   = $row->download_typ_top_bar;
      $download_typ_foo_bar   = $row->download_typ_foo_bar;
      $download_typ_text      = $row->download_typ_text;
      $download_typ_counter   = $row->download_typ_counter;
      mysql_free_result($my_result);
      $data->downloads->name = $download_typ_name;
      $data->downloads->img_small    = getimage($download_typ_img_small);
      $data->downloads->img_big      = getimage($download_typ_img_big);
      $data->downloads->text         = parse_bbcode(nltobr($download_typ_text), $page_tpl);
      if ($download_typ_parent <> 0){
         $data->downloads->parent->name = getdownload_typnamebyid($download_typ_parent);
         $data->downloads->parent->url  = $conf["indexname"]."downloads/".$download_typ_parent;
      }
      getdownload_typ(&$data, $download_typ_tpl, $download_typ_id, $download_id);
      getdownload_data(&$data, $download_typ_tpl, $download_typ_id, $download_id);
      getdownload_download(&$data, $download_typ_tpl, $download_typ_id, $download_id);
      $data->left_bar  = parse_bar($download_typ_tpl, $download_typ_left_bar, "left");
      $data->right_bar = parse_bar($download_typ_tpl, $download_typ_right_bar,"right");
      $data->top_bar   = parse_bar($download_typ_tpl, $download_typ_top_bar,  "top");
      $data->foo_bar   = parse_bar($download_typ_tpl, $download_typ_foo_bar,  "foo");
      
      $data->titel       = $download_typ_name;      
      $data->home_img    = gethomeimg();
      $data->home_url    = $conf["indexname"]. $conf["home_page_typ"] . "/".$conf["home_page"];
      $page_output = sprintt($data, $conf["templates"].gettemplatebyid($download_typ_tpl).".tpl");
      echo $page_output;
   } 
   else {renderpage($conf["home_404"],0);}
}

function getfirstdownloadtypid($list){
   global $conf, $lang;
   
   $listarray = explode(":", $list);
   while (list ($key, $value) = each ($listarray) ) {
      if ($value <> "") {return $value;}
   }
}

function getdownload_typnamebyid($id){
   global $conf, $lang;
   
   $my_result = dbquery("select download_typ_name from ".$conf["db_namespace"]."download_typs where download_typ_id='".$id."'");
   if ( mysql_num_rows($my_result) == 1 )
      {
      $row = mysql_fetch_object($my_result);
      $name = $row->download_typ_name;
      mysql_free_result($my_result);
      return $name;
      }
}      

function getdownload_typ($data, $tpl, $download_typ_id, $download_id){
   global $conf, $lang;

   $query = "select * from ".$conf["db_namespace"]."download_typs where download_typ_parent_id = '".$download_typ_id."' order by download_typ_name ASC";
   $result = dbquery($query);
   if ( mysql_num_rows($result) > 0 ){
      $akt=0;
      while ( $row = mysql_fetch_object($result) ){
         $akt++;
         $data->downloads->download_childs[$akt]->name   = $row->download_typ_name;
         $data->downloads->download_childs[$akt]->url    = $conf["indexname"]."downloads/".$row->download_typ_id;
         $data->downloads->download_childs[$akt]->text   = parse_bbcode(nltobr($row->download_typ_text), $tpl);
      }
      mysql_free_result($result);
   }
}     
function getdownload_data($data, $tpl, $download_typ_id, $download_id){
   global $conf, $lang;

   $query = "select * from ".$conf["db_namespace"]."download where download_typ like '%:".$download_typ_id.":%' order by download_name ASC";
   $result = dbquery($query);
   if (mysql_num_rows($result) > 0 ){
      $akt=0;

      while ( $row = mysql_fetch_object($result) ){
         $akt++;
         $data->downloads->download_data[$akt]->name   = $row->download_name;
         $data->downloads->download_data[$akt]->file   = $conf["downloads"].$row->download_file;
         $data->downloads->download_data[$akt]->text   = parse_bbcode(nltobr($row->download_text), $tpl);                           
      }
      mysql_free_result($result);     
   }
}
function getdownload_download($data, $tpl, $download_typ_id, $download_id){
   global $conf, $lang;

   if (isset($download_id)|| $download_id<>""|| $download_id<>0){
   $query = "select * from ".$conf["db_namespace"]."download where download_id =".$download_id;
   $result = dbquery($query);
   if ( mysql_num_rows($result) > 0 ){
      $akt=1;
      while ( $row = mysql_fetch_object($result) ){
         $data->downloads->download_data[$akt]->name   = $row->download_name;
         $data->downloads->download_data[$akt]->file   = $conf["downloads"].$row->download_file;
         $data->downloads->download_data[$akt]->text   = parse_bbcode(nltobr($row->download_text), $tpl);                           
      }
      mysql_free_result($result);     
   }
   }
}   
?>                     