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
    {mask:search}
       {mask:searchresult}
          search_url
          search_text
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

if ($page == "search"){
   $searchstring = $search;
   $modul_result = dbquery("select * from acme_module where search ='Y'");
   if ( mysql_num_rows($modul_result) >0)  {
      while ($row = mysql_fetch_object($modul_result) ){
          $modul = $row->modul;
          include("search.$modul.inc");
      }
      mysql_free_result($modul_result);
   }
   
   
   rendersearch($searcharray);
   }
  
function rendersearch($search){
   global $conf, $lang;
   
   $akt=0;

   $data->titel     = "";
   $data->home_img  = gethomeimg();
   $data->home_url  = $conf["indexname"] . $conf["home_page_typ"] . "/".$conf["home_page"];
   $tplfile = "cms/tpl/" . gettemplatebyid($conf["home_tpl"]) . ".tpl";
   if ($conf["home_left_bar"]  <> 0){$data->left_bar  = parse_bar($conf["home_tpl"], $conf["home_left_bar"],  "left");}
   if ($conf["home_right_bar"] <> 0){$data->right_bar = parse_bar($conf["home_tpl"], $conf["home_right_bar"], "right");}
   if ($conf["home_top_bar"]   <> 0){$data->top_bar   = parse_bar($conf["home_tpl"], $conf["home_top_bar"],   "top");}
   if ($conf["home_foo_bar"]   <> 0){$data->foo_bar   = parse_bar($conf["home_tpl"], $conf["home_foo_bar"],   "foo");}

   $data->search->searchstring  = $search;
   
   $akt=1;
   searchIt(&$data, $akt, $search);
   
   $tplfile= "cms/tpl/home.tpl";
   $page_output = sprintt($data, $tplfile);
   echo $page_output;
}

   
function searchIt(&$data, $akt, $search){
   global $conf, $lang;

   $modul_result = dbquery("select * from acme_module where search ='Y'");
   if ( mysql_num_rows($modul_result) >0)  {
      while ($row = mysql_fetch_object($modul_result) ){
          $modul = $row->modul;
          $fktname = 'search_'.$modul;
          if (function_exists($fktname)){
             $data->searchresults->$modul =  call_user_func($fktname, $search);
          }              
      }
      mysql_free_result($modul_result);
   }


}