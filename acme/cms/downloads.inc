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
        titel 				
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
   $id  = array_shift($path);
   if(!isset($id)){$id = "0";}
   $did = array_shift($path);
   if(!isset($did)){$did = "0";}
   renderdownloads($id, $did);
   }
  
function renderdownloads($id, $did){
   global $conf, $lang;

   $my_result = dbquery("select * from acme_download_typs where download_typ_id='".$id."'");
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
      $download_typ_titel     = $row->download_typ_titel;
      $download_typ_text      = $row->download_typ_text;
      $download_typ_counter   = $row->download_typ_counter;
      mysql_free_result($my_result);
      $data->downloads->img_small    = getimage($download_typ_img_small);
      $data->downloads->img_big      = getimage($download_typ_img_big);
      $data->downloads->text         = parse_bbcode(nltobr($download_typ_text), $page_tpl);
      if ($download_typ_parent <> 0){
         $data->downloads->parent->name = getdownload_typnamebyid($download_typ_parent);
         $data->downloads->parent->url  = $conf["indexname"]."downloads/".$download_typ_parent;
      }
      getdownload_typdata(&$data, $download_typ_id, $did);
      $data->left_bar  = parse_bar($download_typ_tpl, $download_typ_left_bar, "left");
      $data->right_bar = parse_bar($download_typ_tpl, $download_typ_right_bar,"right");
      $data->top_bar   = parse_bar($download_typ_tpl, $download_typ_top_bar,  "top");
      $data->foo_bar   = parse_bar($download_typ_tpl, $download_typ_foo_bar,  "foo");
      $data->downloads->titel = $download_typ_titel;
      $data->titel       = $download_typ_titel;      
      $data->home_img    = gethomeimg();
      $data->home_url    = $conf["indexname"]. $conf["home_page_typ"] . "/".$conf["home_page"];
      $page_output = sprintt($data, $conf["templates"].gettemplatebyid($download_typ_tpl).".tpl");
      echo $page_output;
   } 
   else {renderpage($conf["home_404"],0);}
}

function getdownload_typnamebyid($id){
   global $conf, $lang;
   
   $my_result = dbquery("select download_typ_name from acme_download_typs where download_typ_id='".$id."'");
   if ( mysql_num_rows($my_result) == 1 )
      {
      $row = mysql_fetch_object($my_result);
      $name = $row->download_typ_name;
      mysql_free_result($my_result);
      return $name;
      }
}      

function getdownload_typdata($data, $download_typ_id){
   global $conf, $lang;

   $stmt = "order by download_typ_name ASC";
   $akt=0;
   $query = "select * from acme_download_typs where download_typ_parent_id = '".$download_typ_id."' " . $stmt;
   $result = dbquery($query);
   if ( mysql_num_rows($result) > 0 ){
      while ( $row = mysql_fetch_object($result) ){
         $akt++;
         $data->downloads->download_childs[$akt]->name   = $row->download_typ_name;
         $data->downloads->download_childs[$akt]->url    = $conf["indexname"]."downloads/".$row->download_typ_id;
         }
      }
 	mysql_free_result($result);     

   if ($did = "0"){
      $stmt = "order by url_name ASC";
      $akt=0;
      $query = "select * from acme_url where download_typ like '%:".$download_typ_id.":%' " . $stmt;
      $result = dbquery($query);
      if ( mysql_num_rows($result) > 0 ){
         while ( $row = mysql_fetch_object($result) ){
            $akt++;
            $data->downloads->download_data[$akt]->name   = $row->download_name;
            $data->downloads->download_data[$akt]->file   = $conf["downloads"].$row->download_file;
            $data->downloads->download_data[$akt]->text   = parse_bbcode(nltobr($row->download_text), $page_tpl);                           
         }
      	mysql_free_result($result);     
      }
    } 
    else { 
      $stmt = "order by url_name ASC";
      $akt=1;
      $query = "select * from acme_url where download_id =".$did;
      $result = dbquery($query);
      if ( mysql_num_rows($result) > 0 ){
         while ( $row = mysql_fetch_object($result) ){
            $data->downloads->download_data[$akt]->name   = $row->download_name;
            $data->downloads->download_data[$akt]->file   = $conf["downloads"].$row->download_file;
            $data->downloads->download_data[$akt]->text   = parse_bbcode(nltobr($row->download_text), $page_tpl);                           
         }
      	mysql_free_result($result);     
      }
    }   

}      
?>                     