<?php 
/*
  platzhalter für den blog:

  gültig innerhalb{mask:main}
     titel                Seitenüberschrift
     left_bar				  linke Navigation
     right_bar            rechte Navigation
     top_bar              obere Navigation
     foo_bar              untere Navigation
     home_img
     home_url
     gültig innerhalb {mask:blog} 
        titel 				
        img_small
        img_big
        text
        counter
        gültig innerhalb {mask:blog_data} 
           create_date
           create_time
           blog_titel
           blog_text
        gültig innerhalb {mask:blog_archiv}         
           url
           monat
           jahr
           anzahl
 
*/ 
if ($page == "blog") {
   if ((isset($blog_id) && !is_nan($blog_id)) && 
      ((isset($perma) && !is_nan($perma)) ||
       (isset($blog_cat) && !is_nan($blog_cat)) ||
      ((isset($archiv_j) && !is_nan($archiv_j)) &&
       (isset($archiv_m) && !is_nan($archiv_m)))) ||
       (!isset($perma) && !isset($blog_cat) && !isset($archiv_j) && !isset($archiv_m)))
   {    	
      renderblog($blog_id, $archiv_j, $archiv_m, $blog_cat, $perma);
   } else {
   	renderpage($conf["home_404"],0);
   }	
}   
 
function renderblog($bid, $bj, $bm, $cat = 0){
   global $conf, $lang;

   $my_result = dbquery("select * from acme_blog where blog_id='".$bid."'");
   if ( mysql_num_rows($my_result) == 1 )   {
      $row = mysql_fetch_object($my_result);
      $blog_id        = $row->blog_id;
      $blog_name      = $row->blog_name;
      $blog_tpl       = $row->blog_tpl;
      $blog_img_small = $row->blog_img_small;
      $blog_img_big   = $row->blog_img_big;
      $blog_left_bar  = $row->blog_left_bar;
      $blog_right_bar = $row->blog_right_bar;
      $blog_top_bar   = $row->blog_top_bar;
      $blog_foo_bar   = $row->blog_foo_bar;
      $blog_titel     = $row->blog_titel;
      $blog_text      = $row->blog_text;
      $blog_counter   = $row->blog_counter;
      mysql_free_result($my_result);
      $data->blog->img_small    = getimage($blog_img_small);
      $data->blog->img_big      = getimage($blog_img_big);
      $data->blog->text         = parse_bbcode(nltobr($blog_text), $page_tpl);
      $data->blog->counter      = $blog_counter;
      if (!isset($perma)) {
         getblogdata(&$data, $blog_id, $bj, $bm, $blog_tpl, $cat);
      } else {
      	 getblogperma(&$data, $blog_id, $oerma, $blog_tpl);
      }   
      getblogcats(&$data, $blog_id);
      getblogarchiv(&$data, $blog_id);      
      $data->left_bar  = parse_bar($blog_tpl, $blog_left_bar, "left");
      $data->right_bar = parse_bar($blog_tpl, $blog_right_bar,"right");
      $data->top_bar   = parse_bar($blog_tpl, $blog_top_bar,  "top");
      $data->foo_bar   = parse_bar($blog_tpl, $blog_foo_bar,  "foo");
      $data->blog->titel     = $blog_titel;
      $data->home_img  = gethomeimg();
      $data->home_url  = $conf["indexname"]. $conf["home_page_typ"] . "/".$conf["home_page"];
      incblogcounter($blog_id, $blog_counter);
      $page_output = sprintt($data, $conf["templates"].gettemplatebyid($blog_tpl).".tpl");
      echo $page_output;
   } 
   else {renderpage($conf["home_404"],0);}
}

function incblogcounter($blog_id,$blog_counter) {
   global $conf, $lang;
   
   $blog_counter = $blog_counter + 1;
   $inc_query  = "update acme_blog set blog_counter = ".$blog_counter." where blog_id = ".$blog_id;
   dbconnect();
   dbquery($inc_query);
}

function getblognamebyid($id){
   global $conf, $lang;
   
   $my_result = dbquery("select blog_name from acme_blog where blog_id='".$id."'");
   if ( mysql_num_rows($my_result) == 1 )
      {
      $row = mysql_fetch_object($my_result);
      $name = $row->blog_name;
      mysql_free_result($my_result);
      return $name;
      }
}      

function getblogdata($data, $blog_id, $bj, $bm, $page_tpl, $cat){
   global $conf, $lang;

   if ($cat<>0) {$stmt = "and blog_cat_id = '".$cat."' order by blog_data_date DESC";}
   else {   
      if (!isset($bm)){$stmt = " order by blog_data_date DESC LIMIT 0, 50";}
      else{$stmt = "and month(blog_data_date) = " . $bm . " and year(blog_data_date) = " . $bj . " order by blog_data_date DESC";}
   }
     
   $akt=0;
   $query = "select * from acme_blog_data where blog_id = '".$blog_id."' " . $stmt;
   $result = dbquery($query);
   if ( mysql_num_rows($result) > 0 ){
      while ( $row = mysql_fetch_object($result) ){
         $akt++;
         $data->blog->blog_data[$akt]->create_date   = mydate2date($row->blog_data_date);
         $data->blog->blog_data[$akt]->create_time   = mydate2time($row->blog_data_date);         
         $data->blog->blog_data[$akt]->blog_titel    = $row->blog_data_headline;
         $blog_cat_id = $row->blog_cat_id;         
         $blogcatname = getblogcatname($blog_cat_id);
         $data->blog->blog_data[$akt]->blog_cat_name = $blogcatname;         
         $data->blog->blog_data[$akt]->blog_cat_url  = $conf["indexname"]."blog/".$blog_id."/".$blog_cat_id."";
         $data->blog->blog_data[$akt]->blog_text     = parse_bbcode(nltobr($row->blog_data_content), $page_tpl);                  
         }
      }
 	mysql_free_result($result);     
}      

function getblogperma($data, $blog_id, $perma, $page_tpl){
   global $conf, $lang;

   $akt=0;
   $query = "select * from acme_blog_data where blog_id = '".$blog_id. "' and blog_data_id = '". $perma ."'";
   $result = dbquery($query);
   if ( mysql_num_rows($result) > 0 ){
      while ( $row = mysql_fetch_object($result) ){
         $akt++;
         $data->blog->blog_data[$akt]->create_date   = mydate2date($row->blog_data_date);
         $data->blog->blog_data[$akt]->create_time   = mydate2time($row->blog_data_date);         
         $data->blog->blog_data[$akt]->blog_titel    = $row->blog_data_headline;
         $blog_cat_id = $row->blog_cat_id;         
         $blogcatname = getblogcatname($blog_cat_id);
         $data->blog->blog_data[$akt]->blog_cat_name = $blogcatname;         
         $data->blog->blog_data[$akt]->blog_cat_url  = $conf["indexname"]."blog/".$blog_id."/".$blog_cat_id."";
         $data->blog->blog_data[$akt]->blog_text     = parse_bbcode(nltobr($row->blog_data_content), $page_tpl);                  
         }
      }
 	mysql_free_result($result);     
}  

function getblogarchiv($data, $blog_id){
   global $conf, $lang;

   $akt=0;
   $query = "select month(blog_data_date) as monat, year(blog_data_date) as jahr, count(*) as anzahl from acme_blog_data where blog_id = '".$blog_id."' group by month(blog_data_date), year(blog_data_date) order by month(blog_data_date), year(blog_data_date)";
   $result = dbquery($query);
   if ( mysql_num_rows($result) > 0 ){
      while ( $row = mysql_fetch_object($result) ){
         $akt++;
         $data->blog->blog_archiv[$akt]->url    = $conf["indexname"]."blog/".$blog_id."/" . $row->jahr . "/" . $row->monat . "";
         $data->blog->blog_archiv[$akt]->monat  = $row->monat;                  
         $data->blog->blog_archiv[$akt]->jahr   = $row->jahr;                  
         $data->blog->blog_archiv[$akt]->anzahl = $row->anzahl;                                    
      }
 	   mysql_free_result($result);     
   }
}  

function getblogcats($data, $blog_id){
   global $conf, $lang;

   $akt=0;
   $query = "select * from acme_blog_cat where blog_cat_blog_id = '".$blog_id."' order by blog_cat_name";
   $result = dbquery($query);
   if ( mysql_num_rows($result) > 0 ){
      while ( $row = mysql_fetch_object($result) ){
         $akt++;
         $data->blog->blog_cat[$akt]->url    = $conf["indexname"]."blog/".$blog_id."/". $row->blog_cat_id . "";
         $data->blog->blog_cat[$akt]->name   = $row->blog_cat_name;                  
      }
 	   mysql_free_result($result);     
   }
}   
    
function getblogcatname($blog_cat_id){
   global $conf, $lang;

   $query = "select * from acme_blog_cat where blog_cat_id = '".$blog_cat_id."'";
   $result = dbquery($query);
   if ( mysql_num_rows($result) > 0 ){
      $row = mysql_fetch_object($result);
      $blogcatname = $row->blog_cat_name;
      mysql_free_result($result);     
   }
 
   return $blogcatname;
}      

?>   