<?php 
/*
  platzhalter für die urls:

  gültig innerhalb{mask:main}
     titel                Seitenüberschrift
     left_bar				  linke Navigation
     right_bar            rechte Navigation
     top_bar              obere Navigation
     foo_bar              untere Navigation
     home_img
     home_url
     gültig innerhalb {mask:urls} 
        titel 				
        img_small
        img_big
        text
        {mask:parent}            
           name	  Überschrift Elternseite
           url		  href Elternseite
        {/mask:page_parent}  
        gültig innerhalb {mask:url_childs}  // unterkategorien
           name
           url
        gültig innerhalb {mask:url_data}    // urls zu dieser kategorie
           name
           url
           text

*/ 

if ($page="urls"){
   $id  = array_shift($path);
   if(!isset($id)){$uid = "0";}
   $uid = array_shift($path);
   if(!isset($uid)){$uid = "0";}
   renderurls($id, $uid);
   }
  
function renderurls($id,$uid){
   global $conf, $lang;

   $my_result = dbquery("select * from acme_url_typs where url_typ_id='".$id."'");
   if ( mysql_num_rows($my_result) == 1 )   {
      $row = mysql_fetch_object($my_result);
      $url_typ_id        = $row->url_typ_id;
      $url_typ_parent    = $row->url_typ_parent_id;
      $url_typ_name      = $row->url_typ_name;
      $url_typ_tpl       = $row->url_typ_tpl;
      $url_typ_img_small = $row->url_typ_img_small;
      $url_typ_img_big   = $row->url_typ_img_big;
      $url_typ_left_bar  = $row->url_typ_left_bar;
      $url_typ_right_bar = $row->url_typ_right_bar;
      $url_typ_top_bar   = $row->url_typ_top_bar;
      $url_typ_foo_bar   = $row->url_typ_foo_bar;
      $url_typ_titel     = $row->url_typ_titel;
      $url_typ_text      = $row->url_typ_text;
      $url_typ_counter   = $row->url_typ_counter;
      mysql_free_result($my_result);
      $data->urls->img_small    = getimage($url_typ_img_small);
      $data->urls->img_big      = getimage($url_typ_img_big);
      $data->urls->text         = parse_bbcode(nltobr($url_typ_text), $page_tpl);
      if ($url_typ_parent <> 0){
         $data->urls->parent->name = geturl_typnamebyid($url_typ_parent);
         $data->urls->parent->url  = $conf["indexname"]."urls/".$url_typ_parent;
      }
      geturl_typdata(&$data, $url_typ_id, $uid);
      $data->left_bar  = parse_bar($url_typ_tpl, $url_typ_left_bar, "left");
      $data->right_bar = parse_bar($url_typ_tpl, $url_typ_right_bar,"right");
      $data->top_bar   = parse_bar($url_typ_tpl, $url_typ_top_bar,  "top");
      $data->foo_bar   = parse_bar($url_typ_tpl, $url_typ_foo_bar,  "foo");
      $data->urls->titel = $url_typ_titel;
      $data->titel       = $url_typ_titel;      
      $data->home_img    = gethomeimg();
      $data->home_url    = $conf["indexname"].$conf["home_page_typ"] . "/".$conf["home_page"];
      $page_output = sprintt($data, "cms/tpl/".gettemplatebyid($url_typ_tpl).".tpl");
      echo $page_output;
   } 
   else {renderpage($conf["home_404"],0);}
}

function geturl_typnamebyid($id){
   global $conf, $lang;
   
   $my_result = dbquery("select url_typ_name from acme_url_typs where url_typ_id='".$id."'");
   if ( mysql_num_rows($my_result) == 1 )
      {
      $row = mysql_fetch_object($my_result);
      $name = $row->url_typ_name;
      mysql_free_result($my_result);
      return $name;
      }
}      

function geturl_typdata($data, $url_typ_id, $uid){
   global $conf, $lang;

   $stmt = "order by url_typ_name ASC";
   $akt=0;
   $query = "select * from acme_url_typs where url_typ_parent_id = '".$url_typ_id."' " . $stmt;
   $result = dbquery($query);
   if ( mysql_num_rows($result) > 0 ){
      while ( $row = mysql_fetch_object($result) ){
         $akt++;
         $data->urls->url_childs[$akt]->name   = $row->url_typ_name;
         $data->urls->url_childs[$akt]->url    = $conf["indexname"]."urls/".$row->url_typ_id;
         }
      }
 	mysql_free_result($result);     

   if($uid = "0") {
      $stmt = "order by url_name ASC";
      $akt=0;
      $query = "select * from acme_url where url_typ like '%:".$url_typ_id.":%' " . $stmt;
      $result = dbquery($query);
      if ( mysql_num_rows($result) > 0 ){
         while ( $row = mysql_fetch_object($result) ){
            $akt++;
            $data->urls->url_data[$akt]->name   = $row->url_name;
            $data->urls->url_data[$akt]->url    = $row->url_url;
            $data->urls->url_data[$akt]->text   = parse_bbcode(nltobr($row->url_text), $page_tpl);                           
         }
         mysql_free_result($result);     
      }
   } 
   else {
      $stmt = "order by url_name ASC";
      $akt=1;
      $query = "select * from acme_url where url_id=".$uid;
      $result = dbquery($query);
      if ( mysql_num_rows($result) > 0 ){
         while ( $row = mysql_fetch_object($result) ){
            $data->urls->url_data[$akt]->name   = $row->url_name;
            $data->urls->url_data[$akt]->url    = $row->url_url;
            $data->urls->url_data[$akt]->text   = parse_bbcode(nltobr($row->url_text), $page_tpl);                           
         }
         mysql_free_result($result);     
      }
   }


}      
?>            