<?php 
/*

  platzhalter für die Seite:

  {mask:main}
     titel                Seitenüberschrift
     left_bar				  linke Navigation
     right_bar            rechte Navigation
     top_bar              obere Navigation
     foo_bar              untere Navigation
     home_img
     home_url
     {mask:news_top_thema}  				          
        img_small
        img_big
        img_titel
        headline
        short_text
        counter
        author
        create_date
        create_time
        modify_date
        modify_time
        {mask:parent}            
           name	  Überschrift Elternseite
           url		  href Elternseite
        {/mask}            
        self_url		  href diese Seite
        {mask:preview}
           url
           headline
           sub_headline		//nicht existent bei pagespreview
           short_text
           publish_date
           create_date
           create_time
           modify_date           
           modify_time
           author
        {/mask}           
     {/mask}   
     {mask:news_page}  				
        img_small
        img_big
        headline
        short_text
        long_text
        counter
        author   
        create_date
        create_time
        modify_date
        modify_time
        {mask:parent}            
           name	  Überschrift Elternseite
           url		  href Elternseite
        {/mask}            
        self_url    href diese Seite
        {/mask}            
        {mask:preview}
           url
           headline
           sub_headline		//nicht existent bei pagespreview
           short_text
           publish_date
           create_date
           create_time
           modify_date           
           modify_time
           author
        {/mask:preview}           
     {/mask}
  {/mask}   
  platzhalter für die Navigation:
   
  {mask:main}
    {mask:nav_elem}
       nav_elem_url
       nav_elem_text
       nav_elem_img
    {/mask}
  {/mask}        

*/

if ($page == "news"){rendernews();}
  
function rendernews(){
   global $conf, $lang;
   
   $akt=0;

   // sollte dann aus den news kommen!!!
   $data->titel     = "";
   $data->home_img  = gethomeimg();
   $data->home_url  = $conf["indexname"]. $conf["home_page_typ"] . "/".$conf["home_page"];
   $tplfile = "cms/tpl/" . gettemplatebyid($conf["home_tpl"]) . ".tpl";
   $data->left_bar  = parse_bar($conf["home_tpl"], $conf["home_left_bar"],  "left");
   $data->right_bar = parse_bar($conf["home_tpl"], $conf["home_right_bar"], "right");
   $data->top_bar   = parse_bar($conf["home_tpl"], $conf["home_top_bar"],   "top");
   $data->foo_bar   = parse_bar($conf["home_tpl"], $conf["home_foo_bar"],   "foo");

   $query = "select * from acme_pages where page_top_thema = 'Y'";
   $my_result = dbquery($query);
   if ( mysql_num_rows($my_result) == 1 ){
      $row = mysql_fetch_object($my_result);
      $page_id = $row->page_id;
      $page_name = $row->page_name;
      $page_parent = $row->page_parent;
      $page_tpl = $row->page_tpl;
      $page_img_small = $row->page_img_small;
      $page_img_big = $row->page_img_big;
      $page_img_titel = $row->page_titelbild;      
      $page_left_bar = $row->page_left_bar;
      $page_right_bar = $row->page_right_bar;
      $page_top_bar = $row->page_top_bar;
      $page_foo_bar = $row->page_foo_bar;
      $page_headline = $row->page_headline;
      $page_short_text = $row->page_short_text;
      $page_long_text = $row->page_long_text;
      $page_long_text_typ= $row->page_long_text_typ;
      $page_author = getauthorbyid($row->page_author_id);      
      $page_create_date = $row->page_create_date;
      $page_modify_date = $row->page_modify_date; 
      $page_childs = $row->page_childs;
      $page_counter = $row->page_counter;
      $page_news_rows = $row->page_news_rows;            
      $page_last_update = $row->page_last_update;
      $data->news_top_thema->img_small    = getimage($page_img_small);
      $data->news_top_thema->img_big      = getimage($page_img_big);
      $data->news_top_thema->img_titel    = getimage($page_img_titel);      
      $data->news_top_thema->headline     = $page_headline;
      if ($page_long_text_typ == "B"){
         $data->news_top_thema->short_text   = parse_bbcode(nltobr($page_short_text), $page_tpl);
      }
      else{
         $data->top_thema->short_text   = $page_short_text;
      }
      $data->news_top_thema->counter      = $page_counter;
      $data->news_top_thema->author       = $page_author;      
      $data->news_top_thema->create_date  = mydate2date($page_create_date);
      $data->news_top_thema->create_time  = mydate2time($page_create_date);
      $data->news_top_thema->modify_date  = mydate2date($page_modify_date);      
      $data->news_top_thema->modify_time  = mydate2time($page_modify_date);            
      if ($page_parent <> 0){
         $data->news_top_thema->parent->name = getpageheadlinebyid($page_parent);
         $data->news_top_thema->parent->url  = $conf["indexname"]."page/".$page_parent;
      }
      $data->news_top_thema->self_url  = $conf["indexname"]."page/".$page_id;
      getaktuellchildsfornews(&$data, $page_id, $page_tpl, $page_news_rows);
      mysql_free_result($my_result);
   } else {echo "WAAHH".$query;}

   $query = "select * from acme_pages where page_news_rows > 0 and  page_top_thema = 'N' order by page_news_rank ASC";
   $my_result = dbquery($query);
   if ( mysql_num_rows($my_result) > 0 ){
      while ( $row = mysql_fetch_object($my_result) ){
         $akt++;

      $page_id = $row->page_id;
      $page_name = $row->page_name;
      $page_parent = $row->page_parent;
      $page_tpl = $row->page_tpl;
      $page_img_small = $row->page_img_small;
      $page_img_big = $row->page_img_big;
      $page_img_titel = $row->page_titelbild;            
      $page_left_bar = $row->page_left_bar;
      $page_right_bar = $row->page_right_bar;
      $page_top_bar = $row->page_top_bar;
      $page_foo_bar = $row->page_foo_bar;
      $page_headline = $row->page_headline;
      $page_short_text = $row->page_short_text;
      $page_long_text = $row->page_long_text;
      $page_long_text_typ= $row->page_long_text_typ;
      $page_author = getauthorbyid($row->page_author_id);      
      $page_create_date = $row->page_create_date;
      $page_modify_date = $row->page_modify_date; 
      $page_childs = $row->page_childs;
      $page_counter = $row->page_counter;
      $page_news_rows = $row->page_news_rows;      
      $page_last_update = $row->page_last_update;
      $data->news_page[$akt]->img_small    = getimage($page_img_small);
      $data->news_page[$akt]->img_big      = getimage($page_img_big);
      $data->news_page[$akt]->img_titel    = getimage($page_img_titel);      
      $data->news_page[$akt]->headline     = $page_headline;
      if ($page_long_text_typ == "B"){
         $data->news_page[$akt]->short_text   = parse_bbcode(nltobr($page_short_text), $page_tpl);
      }
      else{
         $data->news_page[$akt]->short_text   = $page_short_text;
      }
      $data->news_page[$akt]->counter      = $page_counter;
      $data->news_page[$akt]->author       = $page_author;      
      $data->news_page[$akt]->create_date  = mydate2date($page_create_date);
      $data->news_page[$akt]->create_time  = mydate2time($page_create_date);
      $data->news_page[$akt]->modify_date  = mydate2date($page_modify_date);      
      $data->news_page[$akt]->modify_time  = mydate2time($page_modify_date);            
      if ($page_parent <> 0){
         $data->news_page[$akt]->parent->name = getpageheadlinebyid($page_parent);
         $data->news_page[$akt]->parent->url  = $conf["indexname"]."page/".$page_parent;
      }
      $data->news_page[$akt]->self_url  = $conf["indexname"]."page/".$page_id;
      getpagechildsfornews(&$data, $page_id, $akt, $page_tpl, $page_news_rows);
     $akt++;      
   }
   mysql_free_result($my_result);
   }

   $page_output = sprintt($data, $tplfile);
   echo $page_output;
      
}

function getpagechildsfornews($data, $page_id, $aktpage, $page_tpl, $rows){
   global $conf, $lang;
   
   $query = "select * from acme_artikel where artikel_page like '%:".$page_id.":%' and artikel_aktiv = 'J'  and artikel_publish_date <= now()  order by artikel_publish_date DESC LIMIT 0,".$rows;
   $my_result = dbquery($query);
   if ( mysql_num_rows($my_result) > 0 ){
      while ( $row = mysql_fetch_object($my_result) ){
         $akt++;
         $data->news_page[$aktpage]->preview[$akt]->url          = $conf["indexname"]."artikel/".$page_id."/".$row->artikel_id."/1";
         $data->news_page[$aktpage]->preview[$akt]->headline     = $row->artikel_headline;
         $data->news_page[$aktpage]->preview[$akt]->sub_headline = $row->artikel_sub_headline;           
         $data->news_page[$aktpage]->preview[$akt]->short_text   = parse_bbcode(nltobr($row->artikel_short_text), $page_tpl);
         $data->news_page[$aktpage]->preview[$akt]->publish_date = mydate2date($row->artikel_publish_date);         
         $data->news_page[$aktpage]->preview[$akt]->create_date  = mydate2date($row->artikel_create_date);
         $data->news_page[$aktpage]->preview[$akt]->create_time  = mydate2time($row->artikel_create_date);
         $data->news_page[$aktpage]->preview[$akt]->modify_date  = mydate2date($row->artikel_modify_date);
         $data->news_page[$aktpage]->preview[$akt]->modify_time  = mydate2time($row->artikel_modify_date);           
         $data->news_page[$aktpage]->preview[$akt]->author       = getauthorbyid($row->artikel_author_id); 
      }
      mysql_free_result($my_result);
   }
}

function getaktuellchildsfornews($data, $page_id, $page_tpl, $rows){
   global $conf, $lang;
   
   $query = "select * from acme_artikel where artikel_page like '%:".$page_id.":%' and artikel_aktiv = 'J'  and artikel_publish_date <= now()  order by artikel_publish_date DESC LIMIT 0,".$rows;
   $my_result = dbquery($query);
   if ( mysql_num_rows($my_result) > 0 ){
      while ( $row = mysql_fetch_object($my_result) ){
         $akt++;
         $data->news_top_thema->preview[$akt]->url          = $conf["indexname"]."artikel/".$page_id."/".$row->artikel_id."/1";
         $data->news_top_thema->preview[$akt]->headline     = $row->artikel_headline;
         $data->news_top_thema->preview[$akt]->sub_headline = $row->artikel_sub_headline;           
         $data->news_top_thema->preview[$akt]->short_text   = parse_bbcode(nltobr($row->artikel_short_text), $page_tpl);
         $data->news_top_thema->preview[$akt]->publish_date = mydate2date($row->artikel_publish_date);
         $data->news_top_thema->preview[$akt]->create_date  = mydate2date($row->artikel_create_date);
         $data->news_top_thema->preview[$akt]->create_time  = mydate2time($row->artikel_create_date);
         $data->news_top_thema->preview[$akt]->modify_date  = mydate2date($row->artikel_modify_date);
         $data->news_top_thema->preview[$akt]->modify_time  = mydate2time($row->artikel_modify_date);           
         $data->news_top_thema->preview[$akt]->author       = getauthorbyid($row->artikel_author_id); 
      }
      mysql_free_result($my_result);
   }
}   
?>   

