<?php 
/*

  platzhalter für die Seite:

  {mask:main}
     titel                Seitenüberschrift
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
  platzhalter für die Navigation:
  {mask:main}
    {mask:nav_elem}
       nav_elem_url
       nav_elem_text
       nav_elem_img
    {/mask}
  {/mask}        

*/

if ($page == "sitemap"){
   $navid = array_shift($path);
   rendersitemap($navid);
   }
  
function rendersitemap($nav_id){
   global $conf, $lang;
   
   $akt=0;

   $data->titel     = "";
   $data->home_img  = gethomeimg();
   $data->home_url  = $conf["indexname"] . $conf["home_page_typ"] . "/".$conf["home_page"];
   $tplfile = $conf["templates"] . gettemplatebyid($conf["home_tpl"]) . ".tpl";
   $data->left_bar  = parse_bar($conf["home_tpl"], $conf["home_left_bar"],  "left");
   $data->right_bar = parse_bar($conf["home_tpl"], $conf["home_right_bar"], "right");
   $data->top_bar   = parse_bar($conf["home_tpl"], $conf["home_top_bar"],   "top");
   $data->foo_bar   = parse_bar($conf["home_tpl"], $conf["home_foo_bar"],   "foo");

   $getnavtopics  = "Select * from acme_nav_topics where nav_id = '" . $nav_id . "'";
   $result  = dbquery($getnavtopics);
   if (mysql_num_rows($result) > 0) {
      while ( $row = mysql_fetch_object($result) ){
         $akt++;
         $data->sitemap->map_element[$akt]->map_element_url  = $conf["indexname"] . $row->nav_topic_type . "/". $row->nav_topic_type_id;
         $data->sitemap->map_element[$akt]->map_element_text = $row->nav_topic_text;
         $data->sitemap->map_element[$akt]->map_element_h_level = "0";
         $h_level = "1";
         writesitemaptopics(&$data, &$akt, $row->nav_topic_type, $row->nav_topic_type_id, $h_level);
             
      }
      mysql_free_result($result);
   }
   $tplfile= "cms/tpl/home.tpl";
   $page_output = sprintt($data, $tplfile);
   echo $page_output;
}

   
function writesitemaptopics(&$data, &$akt, $type, $type_id, &$h_level){
   global $conf, $lang;

   $modul_result = dbquery("select * from acme_module where name ='".$type."'");
   if ( mysql_num_rows($modul_result) >0)  {
      while ($row = mysql_fetch_object($modul_result) ){
          $modul = $row->modul;
          $table = $row->table;
          $id    = $row->id;
          $parent= $row->parent;
          $name  = $row->name;

          $result = dbquery("select ".$id.", ".$name." from ".$table." where ".$parent." = '" . $type_id . "' order by ".$name);
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
      }
         }   
}
