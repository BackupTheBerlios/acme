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
     {mask:authoren}  				          
       nachname  	 
       vorname  	 
       img  	 
       url  	 
       email  	 
       text
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

if ($page == "autor"){
   $id     = array_shift($path);   
   renderautor($id);
}
  
function renderautor($id){
   global $conf, $lang;
   
   $data->home_img  = gethomeimg();
   $data->home_url  = $conf["indexname"].$conf["home_page_typ"] . "/".$conf["home_page"];
   $tplfile = "cms/tpl/" . gettemplatebyid($conf["home_tpl"]) . ".tpl";
   if ($conf["home_left_bar"]  <> 0) {$data->left_bar  = parse_bar($conf["home_tpl"], $conf["home_left_bar"],  "left");}
   if ($conf["home_right_bar"] <> 0) {$data->right_bar = parse_bar($conf["home_tpl"], $conf["home_right_bar"], "right");}
   if ($conf["home_top_bar"]   <> 0) {$data->top_bar   = parse_bar($conf["home_tpl"], $conf["home_top_bar"],   "top");}
   if ($conf["home_foo_bar"]   <> 0) {$data->foo_bar   = parse_bar($conf["home_tpl"], $conf["home_foo_bar"],   "foo");}

   $query = "select * from acme_author where author_id = '".$id."'";
   $my_result = dbquery($query);
   if ( mysql_num_rows($my_result) == 1 ){
      $row = mysql_fetch_object($my_result);
      $author_id = $row->author_id;
      $author_vorname  = $row->author_vorname;
      $author_nachname = $row->author_nachname;
      $author_img  	  = $row->author_img;
      $author_url  	  = $row->author_url;
      $author_email    = $row->author_email;
      $author_text     = $row->author_url;
      $data->titel     = $author_vorname . ", " . $author_nachname;
      $data->author->vorname = $author_vorname;
      $data->author->nachname = $author_nachname;
      $data->author->email = $author_email;
      $data->author->url   = $author_url;
      $data->author->img   = getimage($author_img);
      $data->author->text  = parse_bbcode(nltobr($author_text), $page_tpl);
   }
   $page_output = sprintt($data, $tplfile);
   echo $page_output;
      
}