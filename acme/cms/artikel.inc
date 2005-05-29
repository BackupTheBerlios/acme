<?php
/*

  gültig in {mask:main}
    titel             überschrift des artikels
    left_bar
    right_bar
    top_bar
    foo_bar
    home_img
    home_url
    gültig in {mask:artikel}
       {mask:next}
          url       href für nächste seite
          nr				 seitennummer nächste seite
       {/mask}
       {mask:akt}   
          url        href für aktuelle seite
          nr				 seitennummer aktuelle seite
       {/mask}
       {mask_prev}
          url       href für vorherige seite
          nr				 seitennummer vorherige seite
       {/mask}   
       {mask_first}
          url       href für erste seite
          nr				 seitennummer erste seite
       {/mask}
       {mask_last}
          url       href für letzte seite
          nr				 seitennummer letzte seite
       {/mask}  
       img_small
       img_big
       page_url		 href für seite des artikels
       page           überschrift der seite des artikels
	    headline       überschrift des artikels
	    sub_headline   überschrift2 des artikels
       short_text
	    long_text
	    publish_date
	    create_date
	    create_time
	    modify_date
	    modify_time
	    print_url
	    author			namen des autors



  platzhalter für die Navigation:
   
  gültig innerhalb {mask:main}
    gültig innerhalb {mask:nav_elem}
       nav_elem_url
       nav_elem_text
            
  
*/

if ($page == "artikel"){
   renderartikel($page_id, $artikel_id, $artikel_part, $print);
}

function renderartikel($page_id, $artikel_id, $artikel_part){
   global $conf, $lang;
   if (!isset($artikel_part)){$artikel_part=1;}
   $query = "select * from ".$conf["db_namespace"]."artikel where artikel_id=".$artikel_id;
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
      if ($page_id == "" || $page_id == "0" || !isset($page_id)){
      	 $page_id = getfirstpageid($artikel_page);
      }
      $conf["page_id"] = $page_id;
      $my_result = dbquery("select * from ".$conf["db_namespace"]."pages where page_id='".$page_id."'");
      if (mysql_num_rows($my_result) == 1) {
         $row = mysql_fetch_object($my_result);
         $page_id = $row->page_id;
         $page_name = $row->page_name;
         $page_tpl = $row->page_tpl;
         $page_img_small = $row->page_img_small;
         $page_img_big = $row->page_img_big;
         $page_left_bar = $row->page_left_bar;
         $page_right_bar = $row->page_right_bar;
         $page_top_bar = $row->page_top_bar;
         $page_foo_bar = $row->page_foo_bar;         
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
         
         $artikel_long_text = artikel_getlongtext($artikel_id, $artikel_part);
         $lastpart = artikel_gethighestpart($artikel_id);
         if ($lastpart <> 1) {
            if ($artikel_part < $lastpart){
               $data->artikel->next->url = $conf["indexname"]."artikel/".$page_id."/" . $artikel_id . "/".($artikel_part + 1);
               $data->artikel->next->nr =$artikel_part + 1;
            }
            $data->artikel->akt->nr = $artikel_part;
            $data->artikel->akt->url = $conf["indexname"]."artikel/" . $page_id."/" . $artikel_id . "/".$artikel_part;
            if ($artikel_part > 1)        {
               $data->artikel->prev->url = $conf["indexname"]."artikel/" . $page_id."/" . $artikel_id . "/".($artikel_part - 1);
               $data->artikel->prev->nr =$artikel_part - 1;               
            }
            if ($artikel_part <> 1) {
               $data->artikel->first->nr = "1";
               $data->artikel->first->url = $conf["indexname"]."artikel/".$page_id."/" . $artikel_id . "/1";
            }
            if ($artikel_part <> $lastpart) {            
               $data->artikel->last->nr = $lastpart;
               $data->artikel->last->url = $conf["indexname"]."artikel/".$page_id."/" . $artikel_id . "/".$lastpart;
            }
            $aktpart = 1;
            do {            
               $data->artikel->part[$aktpart]->nr = $aktpart;
               if ($aktpart <> $artikel_part){
                  $data->artikel->part[$aktpart]->url = $conf["indexname"]."artikel/".$page_id."/" . $artikel_id . "/".$aktpart;
               }   
               $aktpart++; 
            } while ($aktpart <= $lastpart);
         }
         $data->artikel->print_url  = $conf["indexname"]."artikel/" . $page_id . "/".$artikel_id."/print";
         $tplfile = $conf["templates"] . gettemplatebyid($page_tpl) . ".tpl";
         
         $bc = get_breadcrumbs("page", $page_id);
         
         $data->left_bar  = parse_bar($page_tpl, $page_left_bar,  "left", $bc);
         $data->right_bar = parse_bar($page_tpl, $page_right_bar, "right", $bc);
         $data->top_bar   = parse_bar($page_tpl, $page_top_bar,   "top", $bc);
         $data->foo_bar   = parse_bar($page_tpl, $page_foo_bar,   "foo", $bc);
         $data->titel                 = $artikel_headline;
         $data->home_img              = gethomeimg();
         $data->home_url              = $conf["indexname"].$conf["home_page_typ"] . "/".$conf["home_page"];
         $data->artikel->img_small    = getimage($page_img_small);
         $data->artikel->img_big      = getimage($page_img_big);
         $data->artikel->page_url     = $conf["indexname"]."page/".$page_id;
         $data->artikel->page         = $page_headline;
         $data->artikel->headline     = $artikel_headline;
         $data->artikel->sub_headline = $artikel_sub_headline;
         $data->artikel->short_text   = parse_bbcode(nltobr($artikel_short_text), $page_tpl);
         $data->artikel->long_text    = parse_bbcode(nltobr($artikel_long_text), $page_tpl);
         $data->artikel->publish_date = mydate2date($artikel_publish_date);		      
         $data->artikel->create_date  = mydate2date($artikel_create_date);		      		   
         $data->artikel->create_time  = mydate2time($artikel_create_date);		      		   
         $data->artikel->modify_date  = mydate2date($artikel_modify_date);
         $data->artikel->modify_time  = mydate2time($artikel_modify_date);		   
         $data->artikel->author       = getauthorbyid($artikel_author);
         $data->artikel->author_url   = $conf["indexname"]."author/".$artikel_author;
         $data->artikel->counter      = $artikel_counter;
         incartikelcounter($artikel_id, $artikel_counter);
         $page_output = sprintt($data, $conf["templates"].gettemplatebyid($page_tpl).".tpl");
         echo $page_output;
      }  else {renderpage($conf["home_404"],0);}
   } else {renderpage($conf["home_404"],0);}
}

function artikel_getlongtext($artikel_id, $artikel_part){
   global $conf, $lang;
   $my_result = dbquery("select * from ".$conf["db_namespace"]."artikel_daten where artikel_id='".$artikel_id."' AND artikel_part='".$artikel_part."'");
   if ( mysql_num_rows($my_result) == 1 ){
      $row = mysql_fetch_object($my_result);
      $long_text = $row->artikel_long_text;
      $artikel_daten_id = $row->artikel_daten_id;
      $artikel_counter = $row->artikel_counter;
   }
   mysql_free_result($my_result);
   incartikeldatencounter($artikel_daten_id, $artikel_counter);

  return $long_text;
}

function incartikelcounter($artikel_id,$artikel_counter) {
   global $conf, $lang;
   $artikel_counter = $artikel_counter + 1;
   $inc_query  = "update ".$conf["db_namespace"]."artikel set artikel_counter = ".$artikel_counter." where artikel_id=".$artikel_id;
   dbconnect();
   dbquery($inc_query);
}

function incartikeldatencounter($artikel_daten_id,$artikel_counter) {
   global $conf, $lang;
   $artikel_counter = $artikel_counter + 1;
   $inc_query  = "update ".$conf["db_namespace"]."artikel_daten set artikel_counter = ".$artikel_counter." where artikel_daten_id=".$artikel_daten_id;
   dbconnect();
   dbquery($inc_query);
}
function getfirstpageid($list){
   global $conf, $lang;
   
   $listarray = explode(":", $list);
   while (list ($key, $value) = each ($listarray) ) {
      if ($value <> "") {return $value;}
      }
}
function artikel_gethighestpart($artikel_id){
   global $conf, $lang;
   
   $my_result = dbquery("select * from ".$conf["db_namespace"]."artikel_daten where artikel_id='".$artikel_id."'");
   $partmax = mysql_num_rows($my_result);
   mysql_free_result($my_result);
   return $partmax;
}
?>