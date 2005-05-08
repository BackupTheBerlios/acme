<?php
/*
{mask:main}
   titel
   left_bar
   right_bar
   top_bar
   foo_bar
   home_img
   home_url
   {mask:img_typ}
      img_small
      img_big
      name
      text
	  create_date
	  create_time
	  modify_date
	  modify_time
	  {mask:parent}
	     name
	     url
      {mask:img_row}
         {mask:img_col}
            name
            desc_short
            thumb_src
            url
      {mask:img_typ_url_first}
         url
      {mask:img_typ_url_prev}
         url
      {mask:img_typ_url_seiten}
         nr
         url
      {mask:img_typ_url_next}
         url
      {mask:img_typ_url_last}
         url
      {mask:image}
         name
         desc_short
         desc_long
         src
*/

renderbilder($img_typ_id, $image_id, $img_typ_anfang);
   

function renderbilder($img_typ_id, $img_id, $anfang){
   global $conf, $lang;

   if (($img_typ_id==0 || !isset($img_typ_id)) && ($img_id==0 || !isset($img_id))) {
      $query = "select * from ".$conf["db_namespace"]."bilder order by img_id LIMIT 1,1";
      $my_result = dbquery($query);
      if ( mysql_num_rows($my_result) > 0 ){
         $row = mysql_fetch_object($my_result);
         $img_typ_id = $row->img_typ_id;
         $img_id = $row->img_id;
      }
   }
   if (($img_typ_id==0 || !isset($img_typ_id)) && isset($img_id)) {
      $query = "select * from ".$conf["db_namespace"]."bilder where img_id = " . $img_id;
      $my_result = dbquery($query);
      if ( mysql_num_rows($my_result) > 0 ){
         $row = mysql_fetch_object($my_result);
         $img_typ_id = $row->img_typ_id;
      }
   }

   $img_typ_result = dbquery("select * from ".$conf["db_namespace"]."bilder_typs where img_typ_id='".$img_typ_id."'");
   if (mysql_num_rows($img_typ_result) == 1) {
      $img_typ_row = mysql_fetch_object($img_typ_result);
      $img_typ_id = $img_typ_row->img_typ_id;
      $img_typ_parent = $img_typ_row->img_typ_parent_id;      
      $img_typ_name = $img_typ_row->img_typ_name;
      $img_typ_tpl = $img_typ_row->img_typ_tpl;
      $img_typ_img_small = $img_typ_row->img_typ_img_small;
      $img_typ_img_big = $img_typ_row->img_typ_img_big;
      $img_typ_left_bar = $img_typ_row->img_typ_left_bar;
      $img_typ_right_bar = $img_typ_row->img_typ_right_bar;
      $img_typ_top_bar = $img_typ_row->img_typ_top_bar;
      $img_typ_foo_bar = $img_typ_row->img_typ_foo_bar;         
      $img_typ_name = $img_typ_row->img_typ_name;
      $img_typ_text = $img_typ_row->img_typ_text;
      $img_typ_counter = $img_typ_row->img_typ_counter;
      $img_typ_create_date = $img_typ_row->img_typ_create_date;
      $img_typ_modify_date = $img_typ_row->img_typ_modify_date;
      $img_typ_author_id = $img_typ_row->img_typ_author_id;
      mysql_free_result($img_typ_result);

      $tplfile = $conf["templates"] . gettemplatebyid($img_typ_tpl) . ".tpl";
      $data->left_bar  = parse_bar($img_typ_tpl, $img_typ_left_bar,  "left");
      $data->right_bar = parse_bar($img_typ_tpl, $img_typ_right_bar, "right");
      $data->top_bar   = parse_bar($img_typ_tpl, $img_typ_top_bar,   "top");
      $data->foo_bar   = parse_bar($img_typ_tpl, $img_typ_foo_bar,   "foo");
      $data->titel                 = $img_typ_name;
      $data->home_img              = gethomeimg();
      $data->home_url              = $conf["indexname"]. $conf["home_page_typ"] . "/".$conf["home_page"];
      $data->img_typ->img_small    = getimage($img_typ_img_small);
      $data->img_typ->img_big      = getimage($img_typ_img_big);
      $data->img_typ->name         = $img_typ_name;
      $data->img_typ->text         = parse_bbcode(nltobr($img_typ_text), $img_typ_tpl);
      $data->img_typ->create_date  = mydate2date($img_typ_create_date);   
      $data->img_typ->create_time  = mydate2time($img_typ_create_date);
      $data->img_typ->modify_date  = mydate2date($img_typ_modify_date);
      $data->img_typ->modify_time  = mydate2time($img_typ_modify_date);
      $data->img_typ->counter      = $artikel_counter;
      if ($img_typ_parent <> 0){
         $data->img_typ->parent->name = getimg_typnamebyid($img_typ_parent);
         $data->img_typ->parent->url  = $conf["indexname"]."bilder/".$img_typ_parent;
      }      
      if ($anfang == "" or !isset($anfang))$anfang = 1;
      incimg_typcounter($img_typ_id, $img_typ_counter);
      getimgsforpreview(&$data, $img_typ_id, $img_typ_tpl, $anfang);
      getbigimage(&$data, $img_id, $img_typ_tpl);
      $page_output = sprintt($data, $tplfile);
      echo $page_output;
   } 
   else {renderpage($conf["home_404"],0);}
}

function getimgsforpreview($data, $img_typ_id, $img_typ_tpl, $StartImg){
   global $conf, $lang;

   $query = "select img_typ_rows, img_typ_cols from ".$conf["db_namespace"]."bilder_typs where img_typ_id = '".$img_typ_id."'";
   $my_result = dbquery($query);
   if (mysql_num_rows($my_result)>0){
      $row = mysql_fetch_object($my_result);
      $Bilder_pro_Seite = ($row->img_typ_rows * $row->img_typ_cols);
      $Bilder_Rows = $row->img_typ_rows;
      $Bilder_Cols = $row->img_typ_cols;
      }
   mysql_free_result($my_result);   

   $Bilder_pro_Seite = img_anzahlbilder($img_typ_id);
   
   $akt_row=1;
   $akt_col=0;
   $query = "select * from ".$conf["db_namespace"]."bilder where img_typ_id = '".$img_typ_id."' order by img_id LIMIT " . $StartImg . ", " . $Bilder_pro_Seite . " ";
   $my_result = dbquery($query);
   if ( mysql_num_rows($my_result) > 0 ){
      while ( $row = mysql_fetch_object($my_result) ){
          if ($akt_col >= $Bilder_Cols){$akt_col=0;$akt_row++;}          
          if ($akt_row > $Bilder_Rows){break;}
          $akt_col++;          
          $data->img_typ->img_row[$akt_row]->img_col[$akt_col]->name        = $row->img_name;
          $data->img_typ->img_row[$akt_row]->img_col[$akt_col]->desc_short  = parse_bbcode(nltobr($row->img_description), $img_typ_tpl);
          $data->img_typ->img_row[$akt_row]->img_col[$akt_col]->thumb_src   = $conf["images"]."thumb_" . $row->img_real_name;
          $data->img_typ->img_row[$akt_row]->img_col[$akt_col]->url         = $conf["indexname"]."bilder/". $img_typ_id . "/". $row->img_id;
      }
   }
   
   
   if ($anfang > 0) {
      $data->img_typ->img_typ_url_first->url = $conf["indexname"]."bilder/".$img_typ_id."/0/" . $img_id;
      $back=$anfang-$Bilder_pro_Seite;
      if ($back < 0) {$back = 0;}
         $data->img_typ->img_typ_url_prev->url = $conf["indexname"]."bilder/".$img_typ_id."/". $back ."/" . $img_id;
      }
      if ($Anzahl>$Bilder_pro_Seite) {
         $Seiten=intval($Anzahl/$Bilder_pro_Seite);
         if ($Anzahl%$Bilder_pro_Seite) {
            $Seiten++;
         }  
      }
      $count = 0;
      for ($i=1;$i<=$Seiten;$i++) {
          $fwd=($i-1)*$Bilder_pro_Seite;
          $data->img_typ->img_typ_url_seiten[$count]->nr  = $i;           
          $data->img_typ->img_typ_url_seiten[$count]->url = $conf["indexname"]."bilder/" . $img_typ_id . "/" . $fwd . "/" . $img_id;
          if ($fwd == $anfang){$data->img_typ->img_typ_url_aktpage = $i;}
          $count++;
      }
      
      if ($anfang < $Anzahl-$Bilder_pro_Seite) {
         $fwd=$anfang+$Bilder_pro_Seite;
         $data->img_typ->img_typ_url_next->url = $conf["indexname"]."bilder/".$img_typ_id."/".$fwd."/". $img_id;
         $fwd=$Anzahl-$Bilder_pro_Seite;
         $data->img_typ->img_typ_url_last->url = $conf["indexname"]."bilder/".$img_typ_id."/".$fwd."/". $img_id;
      }   
}
   
function getbigimage($data, $img_id, $img_typ_tpl){
   global $conf, $lang;
   
   $akt=0;
   if ($img_id==0) {$query = "select * from ".$conf["db_namespace"]."bilder order by img_id LIMIT 1,1";}
   else {$query = "select * from ".$conf["db_namespace"]."bilder where img_id = '".$img_id."'";}
   $my_result = dbquery($query);
   if ( mysql_num_rows($my_result) > 0 ){
      while ( $row = mysql_fetch_object($my_result) ){
          $akt++;
          $data->img_typ->image->name        = $row->img_name;
          $data->img_typ->image->desc_short  = parse_bbcode(nltobr($row->img_description), $img_typ_tpl);
          $data->img_typ->image->desc_long   = parse_bbcode(nltobr($row->img_desc_long), $img_typ_tpl);
          $data->img_typ->image->src         = $conf["images"] . $row->img_real_name;
      }
   }
}   
      
function incimg_typcounter($img_typ_id,$img_typ_counter) {
   global $conf, $lang;
   $img_typ_counter = $img_typ_counter + 1;
   $inc_query  = "update ".$conf["db_namespace"]."bilder_typs set img_typ_counter = ".$img_typ_counter." where img_typ_id=".$img_typ_id;
   dbconnect();
   dbquery($inc_query);
}


function img_anzahlbilder($img_typ_id){
   global $conf, $lang;	
   $query = "select img_id from ".$conf["db_namespace"]."bilder where img_typ_id = '".$img_typ_id."'";
   $my_result = dbquery($query);
   return mysql_num_rows($my_result);
   mysql_free_result($my_result);
}   

function getimg_typnamebyid($id){
   global $conf, $lang;
   
   $my_result = dbquery("select img_typ_name from ".$conf["db_namespace"]."bilder_typs where img_typ_id='".$id."'");
   if ( mysql_num_rows($my_result) == 1 )
      {
      $row = mysql_fetch_object($my_result);
      $name = $row->img_typ_name;
      mysql_free_result($my_result);
      return $name;
      }
}    
?>