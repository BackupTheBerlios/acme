<?php 
/*

  platzhalter für die Seite:

  gültig innerhalb{mask:main}
     titel                Seitenüberschrift
     left_bar				  linke Navigation
     right_bar            rechte Navigation
     top_bar              obere Navigation
     foo_bar              untere Navigation
     home_img
     home_url
     gültig innerhalb {mask:page}  				
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

        self_url		  href der seite
       
        {mask:parent}            
           name	  Überschrift Elternseite
           url		  href Elternseite
        {/mask:parent}            
        
        {mask:page_url_next}
           url
        {/mask:page_url_next}           
        
        {mask:page_url_prev}
           url
        {/mask:page_url_prev}           
        
        {mask:page_url_first}      
           url
        {/mask:page_url_first}                 
        
        {mask:page_url_last}    
           url
        {/mask:page_url_last}               
        
        page_url_aktpage	// nummer der aktuellen seite        
                 
        {mask:page_url_seiten}   nicht existent bei pagespreview
           nr					Seitennummer
           url					und href dazu
        {/mask:page_url_seiten}           
        
        {mask:preview}
           url
           headline
           sub_headline		//nicht existent bei pagespreview
           short_text
           publish_date
           create_date
           modify_date
           author
        {/mask:preview}           

  platzhalter für die Navigation:
   
  gültig innerhalb {mask:main}
    gültig innerhalb {mask:nav_elem}
       nav_elem_url
       nav_elem_text
       nav_elem_img
            
  

*/

if ($page == "page"){
   $id     = array_shift($path);
   $anfang = array_shift($path);
   if (!isset($anfang)){$anfang = 0;}
   if (!isset($id)){$id = 0;}   
   $conf["page"]    = "page";
   $conf["page_id"] = $id;
   renderpage($id, $anfang);
}

function renderpage($id, $anfang){
   global $conf, $lang;
   
   $my_result = dbquery("select * from acme_pages where page_id='".$id."'");
   if ( mysql_num_rows($my_result) == 1 )      {
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
      $page_author_id = $row->page_author_id;
      $page_create_date = $row->page_create_date;
      $page_modify_date = $row->page_modify_date; 
      $page_childs = $row->page_childs;
      $page_counter = $row->page_counter;
      $page_last_update = $row->page_last_update;
      mysql_free_result($my_result);
      
      $conf["page_parent_id"] = $page_parent;

      $data->page->img_small      = getimage($page_img_small);
      $data->page->img_big        = getimage($page_img_big);
      $data->page->img_titel      = getimagebyid($page_img_titel, "r", $page_tpl);
      $data->page->headline     = $page_headline;
      if ($page_long_text_typ == "B"){
         $data->page->short_text   = parse_bbcode(nltobr($page_short_text), $page_tpl);
      }
      else {
         $data->page->short_text   = $page_short_text;
      }
      if ($page_long_text_typ == "B"){
         $data->page->long_text    = parse_bbcode(nltobr($page_long_text), $page_tpl);
      }
      else {
         $data->page->long_text    = $page_long_text;
      }
      
      $data->page->counter      = $page_counter;
      $data->page->author       = $page_author;      
      $data->page->author_url   = $page_author_id;            
      $data->page->create_date  = mydate2date($page_create_date);
      $data->page->create_time  = mydate2time($page_create_date);
      $data->page->modify_date  = mydate2date($page_modify_date);      
      $data->page->modify_time  = mydate2time($page_modify_date);            
      if ($page_parent <> 0){
         $data->page->parent->name = getpageheadlinebyid($page_parent);
         $data->page->parent->url  = $conf["indexname"]."page/".$page_parent;
      }
      $data->page->self_url  = $conf["indexname"]."page/".$page_id;
      $data->titel     = $page_headline;
      $data->home_img = gethomeimg();
      $data->home_url = "index/".$conf["home_page_typ"] ."/". $conf["home_page"];
      incpagecounter($page_id, $page_counter);
      $tplfile = "cms/tpl/" . gettemplatebyid($page_tpl) . ".tpl";
      $data->left_bar  = parse_bar($page_tpl, $page_left_bar,  "left");
      $data->right_bar = parse_bar($page_tpl, $page_right_bar, "right");
      $data->top_bar   = parse_bar($page_tpl, $page_top_bar,   "top");
      $data->foo_bar   = parse_bar($page_tpl, $page_foo_bar,   "foo");
      getpagechildsforpreview(&$data, $page_id, $page_childs, $anfang, $page_tpl);
      $page_output = sprintt($data, $tplfile);
      if ($page_long_text_typ == "H"){echo $page_output;}
      if ($page_long_text_typ == "B"){echo $page_output;}
      if ($page_long_text_typ == "P"){echo OutputPhpDocument($page_output);}
   } else {renderpage($conf["home_404"], 0);}

}

function incpagecounter($page_id,$page_counter) {
   global $conf, $lang;
   
   $page_counter = $page_counter + 1;
   $inc_query  = "update acme_pages set page_counter = ".$page_counter." where page_id = ".$page_id;
   dbconnect();
   dbquery($inc_query);
}

function getpagechildsforpreview($data, $page_id, $page_childs, $anfang, $page_tpl){
   global $conf, $lang;
   
   $Zeilen_pro_Seite = 10;
   $akt=0;
   if ($page_childs == "P"){
      $query = "select * from acme_pages where page_parent = '".$page_id."' order by page_create_date DESC";
      $my_result = dbquery($query);
      if ( mysql_num_rows($my_result) > 0 ){
         while ( $row = mysql_fetch_object($my_result) ){
            $akt++;
            $data->page->preview[$akt]->url         = $conf["indexname"]."page/".$row->page_id;
            $data->page->preview[$akt]->headline    = $row->page_headline;
            if ($row->page_long_text_typ == "B"){$data->page->preview[$akt]->short_text  = parse_bbcode(nltobr($row->page_short_text), $page_tpl);}
            else                                {$data->page->preview[$akt]->short_text  = $row->$page_short_text;}            
            $data->page->preview[$akt]->create_date = mydate2date($row->page_create_date);
            $data->page->preview[$akt]->create_time = mydate2time($row->page_create_date);
            $data->page->preview[$akt]->modify_date = mydate2date($row->page_modify_date);
            $data->page->preview[$akt]->modify_time = mydate2time($row->page_modify_date);
            $data->page->preview[$akt]->author      = getauthorbyid($row->page_author_id);             
         }
      }
  }
      
  if ($page_childs == "A"){
     $query = "select artikel_id from acme_artikel where artikel_page like '%:".$page_id.":%' and artikel_aktiv = 'J' and artikel_publish_date <= now() order by artikel_publish_date DESC";
     $my_result = dbquery($query);
     $Anzahl = mysql_num_rows($my_result);
     mysql_free_result($my_result);
     $query = "select * from acme_artikel where artikel_page like '%:".$page_id.":%' and artikel_aktiv = 'J'  and artikel_publish_date <= now()  order by artikel_publish_date DESC LIMIT " . $anfang . ", ". $Zeilen_pro_Seite . " ";
     $my_result = dbquery($query);
     if ( mysql_num_rows($my_result) > 0 ){
        while ( $row = mysql_fetch_object($my_result) ){
           $akt++;
           $data->page->preview[$akt]->url          = $conf["indexname"]."artikel/". $page_id ."/". $row->artikel_id ."/1";
           $data->page->preview[$akt]->headline     = $row->artikel_headline;
           $data->page->preview[$akt]->sub_headline = $row->artikel_sub_headline;           
           $data->page->preview[$akt]->short_text   = parse_bbcode(nltobr($row->artikel_short_text), $page_tpl);
           $data->page->preview[$akt]->publish_date = mydate2date($row->artikel_publish_date);
           $data->page->preview[$akt]->create_date  = mydate2date($row->artikel_create_date);
           $data->page->preview[$akt]->create_time  = mydate2time($row->artikel_create_date);
           $data->page->preview[$akt]->modify_date  = mydate2date($row->artikel_modify_date);
           $data->page->preview[$akt]->modify_time  = mydate2time($row->artikel_modify_date);           
           $data->page->preview[$akt]->author       = getauthorbyid($row->artikel_author_id); 
        }
        mysql_free_result($my_result);
     }
     if($anfang > 0) {
       $data->page->page_url_first->url = $conf["indexname"]."page/".$page_id."/0";
       $back=$anfang-$Zeilen_pro_Seite;
       if ($back < 0) {$back = 0;}
       $data->page->page_url_prev->url = $conf["indexname"]."page/".$page_id."/".$back;
     }
     if ($Anzahl>$Zeilen_pro_Seite) {
        $Seiten=intval($Anzahl/$Zeilen_pro_Seite);
        if($Anzahl%$Zeilen_pro_Seite) {
          $Seiten++;
        }  
     }
     $count = 0;
     for ($i=1;$i<=$Seiten;$i++) {
        $fwd=($i-1)*$Zeilen_pro_Seite;
        $data->page->page_url_seiten[$count]->nr  = $i;           
        $data->page->page_url_seiten[$count]->url = $conf["indexname"]."page/".$page_id."/".$fwd;
        if ($fwd == $anfang){$data->page->page_url_aktpage = $i;}
        $count++;
     }
     if($anfang < $Anzahl-$Zeilen_pro_Seite) {
       $fwd=$anfang+$Zeilen_pro_Seite;
       $data->page->page_url_next->url = $conf["indexname"]."page/".$page_id."/".$fwd;
       $fwd=$Anzahl-$Zeilen_pro_Seite;
       $data->page->page_url_last->url = $conf["indexname"]."page/".$page_id."/".$fwd;
     }
  }
}
function OutputPhpDocument($phpDocument)
{
   reset ($GLOBALS);
   while (list ($key, $val) = each ($GLOBALS))
      {
      eval("\$" . "\$key = \"$val\";");
      }
   $questMark = "?";
   $phpOpenTag = "<${questMark}php";
   $phpCloseTag = "${questMark}>";
   return eval("$phpCloseTag" . stripslashes($phpDocument) . "$phpOpenTag ");
}
?>   

