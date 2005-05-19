<?php 
/*

  platzhalter f�r die Seite:

  {mask:main}
     titel                Seiten�berschrift
     left_bar             linke Navigation
     right_bar            rechte Navigation
     top_bar              obere Navigation
     foo_bar              untere Navigation
     home_img
     home_url
    {mask:sitemap}
       {mask:map_element}
          map_element_url
          map_element_text
          map_element_img
       {/mask}
    {/mask}
  {/mask}   
  platzhalter f�r die Navigation:
  {mask:main}
    {mask:nav_elem}
       nav_elem_url
       nav_elem_text
       nav_elem_img
    {/mask}
  {/mask}        

*/

if ($page == "sitemap"){
   rendersitemap($id);
   }
  
function rendersitemap($id){
   global $conf, $lang;
   
   $akt=0;

   $sitemap_result = dbquery("select * from ".$conf["db_namespace"]."sitemap where sitemap_id='".$id."'");
   if (mysql_num_rows($sitemap_result) == 1) {
      $sitemap_row = mysql_fetch_object($sitemap_result);
      $sitemap_id = $sitemap_row->sitemap_id;
      $sitemap_name = $sitemap_row->sitemap_name;
      $sitemap_img_small = $sitemap_row->sitemap_img_small;
      $sitemap_img_big = $sitemap_row->sitemap_img_big;
      $sitemap_nav_id = $sitemap_row->sitemap_nav_id;


      $data->titel     = $sitemap_name;
      $data->home_img  = gethomeimg();
      $data->home_url  = $conf["indexname"] . $conf["home_page_typ"] . "/".$conf["home_page"];
      $data->sitemap->name         = $sitemap_name;
      $data->sitemap->img_small    = getimage($sitemap_img_small);
      $data->sitemap->img_big      = getimage($sitemap_img_big);

      $tplfile = $conf["templates"] . gettemplatebyid($conf["home_tpl"]) . ".tpl";
      $data->left_bar  = parse_bar($conf["home_tpl"], $conf["home_left_bar"],  "left");
      $data->right_bar = parse_bar($conf["home_tpl"], $conf["home_right_bar"], "right");
      $data->top_bar   = parse_bar($conf["home_tpl"], $conf["home_top_bar"],   "top");
      $data->foo_bar   = parse_bar($conf["home_tpl"], $conf["home_foo_bar"],   "foo");

      $getnavtopics  = "Select * from ".$conf["db_namespace"]."nav_topics where nav_topic_type <> 'sitemap' and nav_id = '" . $sitemap_nav_id . "' order by nav_topic_rank";
      $result  = dbquery($getnavtopics);
      if (mysql_num_rows($result) > 0) {
         while ( $row = mysql_fetch_object($result) ){
            $akt++;
            $data->sitemap->map_element[$akt]->map_element_url  = $conf["indexname"] . $row->nav_topic_type . "/". $row->nav_topic_type_id;
            $data->sitemap->map_element[$akt]->map_element_text = $row->nav_topic_text;
            $data->sitemap->map_element[$akt]->map_element_h_level = "0";
            $h_level = "1";
            writesitemaptopics(&$data, &$akt, $row->nav_topic_type, $row->nav_topic_type_id, &$h_level);
         }
         mysql_free_result($result);
      }
      $page_output = sprintt($data, $tplfile);
      echo $page_output;
   } 
   else {renderpage($conf["home_404"],0);}
}

   
function writesitemaptopics(&$data, &$akt, $type, $type_id, &$h_level){
   global $conf, $lang;
   
   $modul_result = dbquery("select * from ".$conf["db_namespace"]."module where modul ='".$type."'");
   if ( mysql_num_rows($modul_result) >0)  {
      while ($row = mysql_fetch_object($modul_result) ){
         $modul = $row->modul;
         $table = $row->tablename;
         $id    = $row->id;
         $parent= $row->parent;
         $name  = $row->name;
  
         if ($parent <> "") {
            $query = "select ".$id.", ".$name." from ".$conf["db_namespace"]."".$table." where ".$parent." = '" . $type_id . "' order by ".$name;
            $result = dbquery($query);
            if ( mysql_num_rows($result) > 0 ){
               while ($row = mysql_fetch_object($result)){
                  $akt++;
                  $data->sitemap->map_element[$akt]->map_element_url  = $conf["indexname"] . $modul ."/" . $row->$id;
                  $data->sitemap->map_element[$akt]->map_element_text = $row->$name;
                  $data->sitemap->map_element[$akt]->map_element_h_level = $h_level;
                  $h_level++;
                  writesitemaptopics($data, $akt, $type, $row->$id, $h_level);
                  $h_level--;
               }  
               mysql_free_result($result);
            }  
         } else {
            $query = "select ".$id.", ".$name." from ".$conf["db_namespace"]."".$table." order by ".$name;
            $result = dbquery($query);
            if ( mysql_num_rows($result) > 0 ){
               while ($row = mysql_fetch_object($result)){
                  $akt++;
                  $data->sitemap->map_element[$akt]->map_element_url  = $conf["indexname"] . $modul ."/" . $row->$id;
                  $data->sitemap->map_element[$akt]->map_element_text = $row->$name;
                  $data->sitemap->map_element[$akt]->map_element_h_level = $h_level;
               }  
               mysql_free_result($result);
            }           	
         }	
      }
   } 
}
