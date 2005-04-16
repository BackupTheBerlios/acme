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
    {mask:search}
       {mask:searchresult}
          search_url
          search_text
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

include($conf["cmsbase"] . "/lang/search." . $conf["lang"] . ".inc");

if ($page == "search"){
   $searchstring = search_strip_badchars($search);
   $modul_result = dbquery("select * from ".$conf["db_namespace"]."module where search ='Y'");
   if ( mysql_num_rows($modul_result) >0)  {
      while ($row = mysql_fetch_object($modul_result) ){
          $modul = $row->modul;
          include("search.$modul.inc");
      }
      mysql_free_result($modul_result);
   }
   
   
   rendersearch($searchstring);
   }
  
function rendersearch($searchstring){
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

   $data->search->searchstring  = $lang["search_searching"] . $searchstring;
   
   $akt=1;
   if ($searchstring <> "") {
      $anzsearches = searchIt(&$data, $akt, $searchstring);
   }
   if ($anzsearches == 0) {
      $data->search->searchcount  = $lang["search_noresults"];
   } else {
      $data->search->searchcount  = $lang["search_results"] . $anzsearches;   
   }    
   $page_output = sprintt($data, $tplfile);
   echo $page_output;
}

   
function searchIt(&$data, $akt, $search){
   global $conf, $lang;

   $found = 0;

   $modul_result = dbquery("select * from ".$conf["db_namespace"]."module where search ='Y'");
   if ( mysql_num_rows($modul_result) >0)  {
      while ($row = mysql_fetch_object($modul_result) ){
          $modul = $row->modul;
          $fktname = 'search_'.$modul;
          if (function_exists($fktname)){
             $found = $found + call_user_func($fktname, $search, &$data);
          }              
      }
      mysql_free_result($modul_result);
   }
   return $found; 
}
function search_strip_badchars($line) {
// Strips various characters from $line.
// 
 $line = str_replace(".", " ", $line);
 $line = str_replace("\"", " ", $line);
 $line = str_replace("'", "", $line);
 $line = str_replace("+", " ", $line);
 $line = str_replace("-", " ", $line);
 $line = str_replace("*", " ", $line);
 $line = str_replace("/", " ", $line);
 $line = str_replace("!", " ", $line);
 $line = str_replace("%", " ", $line);
 $line = str_replace(">", " ", $line);
 $line = str_replace("<", " ", $line);
 $line = str_replace("^", " ", $line);
 $line = str_replace("(", " ", $line);
 $line = str_replace(")", " ", $line);
 $line = str_replace("[", " ", $line);
 $line = str_replace("]", " ", $line);
 $line = str_replace("{", " ", $line);
 $line = str_replace("}", " ", $line);
 $line = str_replace("\\", " ", $line);
 $line = str_replace("=", " ", $line);
 $line = str_replace("$", " ", $line);
 $line = str_replace("#", " ", $line);
 $line = str_replace("?", " ", $line);
 $line = str_replace("~", " ", $line);
 $line = str_replace(":", " ", $line);
 $line = str_replace("_", " ", $line);
 $line = str_replace("  ", " ", $line);
 $line = str_replace("&amp;", " ", $line);
 $line = str_replace("&copy;", " ", $line);
 $line = str_replace("&nbsp;", " ", $line);
 $line = str_replace("&quot;", " ", $line);
 $line = str_replace("&uuml;", "ü", $line);
 $line = str_replace("&Uuml;", "Ü", $line);
 $line = str_replace("&", " ", $line);
 $line = str_replace(";", " ", $line);
 $line = str_replace("\n", " ", $line);
 return $line;
}
?>