<?php
/*

  gültig in {mask:main}
    home_img
    gültig in {mask:artikel}
       img_small
       img_big
       page           überschrift der seite des artikels
	    page_url       
	    headline       überschrift des artikels
	    sub_headline   überschrift2 des artikels
       short_text
	    {mask:long_text}
	       text
	    {/mask}
	    self_url
	    {/mask}
	    page_url
	    {/mask}
	    publish_date
	    create_date
	    create_time
	    modify_date
	    modify_time
	    author			namen des autors
  
*/

if ($page == "aprint"){
   $id     = array_shift($path);
   $aid = array_shift($path);
   renderaprint($id, $aid);
}

function renderaprint($page_id, $artikel_id){
   global $conf, $lang;
   
   $query = "select * from acme_artikel where artikel_id=".$artikel_id;
   $my_result = dbquery($query);
   if ( mysql_num_rows($my_result) == 1 ){
      $row = mysql_fetch_object($my_result);
      $artikel_id = $row->artikel_id;
      $artikel_page = $row->artikel_page;
      $artikel_headline = $row->artikel_headline;
      $artikel_sub_headline = $row->artikel_sub_headline;
      $artikel_short_text = $row->artikel_short_text;
      $artikel_keywords = $row->artikel_keywords;
      $artikel_create_date = $row->artikel_create_date;
      $artikel_modify_date = $row->artikel_modify_date;
      $artikel_publish_date =  $row->artikel_publish_date;
      $artikel_author = $row->artikel_author_id;
      $artikel_active = $row->artikel_active;
      $artikel_counter = $row->artikel_counter;
      mysql_free_result($my_result);
      $my_result = dbquery("select * from acme_pages where page_id='".$page_id."'");
      if (mysql_num_rows($my_result) == 1) {
         $row = mysql_fetch_object($my_result);
         $page_id = $row->page_id;
         $page_name = $row->page_name;
         $page_tpl = $row->page_tpl;
         $page_img_small = $row->page_img_small;
         $page_img_big = $row->page_img_big;
         $page_headline = $row->page_headline;
         $page_short_text = $row->page_short_text;
         $page_long_text = $row->page_long_text;
         $page_long_text_typ= $row->page_long_text_typ;
         $page_artikel = $row->page_artikel;
         $page_childs = $row->page_childs;
         $page_counter = $row->page_counter;
         $page_create_date = $row->page_create_date;
         $page_modify_date = $row->page_modify_date;         
         mysql_free_result($my_result);
         $tplfile = $conf["templates"] . gettemplatebyid($page_tpl) . ".tpl";
         $data->titel                 = $artikel_headline;
         $data->home_img              = gethomeimg();
         $data->home_url              = $conf["indexname"]. $conf["home_page_typ"] . "/".$conf["home_page"];
         $data->artikel->img_small    = getimage($page_img_small);
         $data->artikel->img_big      = getimage($page_img_big);
         $data->artikel->page_url     = $conf["indexname"]."page/".$page_id;
         $data->artikel->page         = getpageheadlinebyid($page_id);
         $data->artikel->headline     = $artikel_headline;
         $data->artikel->sub_headline = $artikel_sub_headline;
         $data->artikel->short_text   = parse_bbcode(nltobr($artikel_short_text), $page_tpl);
         $data->artikel->publish_date = mydate2date($artikel_publish_date);   
         $data->artikel->create_date  = mydate2date($artikel_create_date);
         $data->artikel->create_time  = mydate2time($artikel_create_date);
         $data->artikel->modify_date  = mydate2date($artikel_modify_date);
         $data->artikel->modify_time  = mydate2time($artikel_modify_date);
         $data->artikel->author       = getauthorbyid($artikel_author);
         $data->artikel->author_url   = $conf["indexname"]."author/".$id;       
         $data->artikel->counter      = $artikel_counter;
         $data->artikel->self_url    = $conf["indexname"]."artikel/" . $page_id . "/".$artikel_id."/1";
         artikel_getlongtext(&$data, $artikel_id, $page_tpl);
         $page_output = sprintt($data, $conf["templates"].gettemplatebyid($page_tpl).".print.tpl");
         echo $page_output;
      }  
      else {renderpage($conf["home_404"],0);}
   } 
   else {renderpage($conf["home_404"],0);}
}

function artikel_getlongtext($data, $artikel_id, $page_tpl){
   global $conf, $lang;
   $my_result = dbquery("select * from acme_artikel_daten where artikel_id='".$artikel_id."' order by artikel_part ASC");
   $akt=0;
   while ($row = mysql_fetch_object($my_result)){
      $data->artikel->long_text[$akt]->text = parse_bbcode(nltobr($row->artikel_long_text), $page_tpl);
      $akt++;
   }
   mysql_free_result($my_result);
}
?>