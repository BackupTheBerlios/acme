<?php

function getimage($picid){
   global $conf, $lang;
   	
   if ( $picid ) {
      $getpic = "Select img_real_name, img_description from ".$conf["db_namespace"]."bilder where img_id='".$picid."'";
      dbconnect();
      $result = dbquery($getpic);
      if (mysql_affected_rows() > 0){
         $row = mysql_fetch_object($result);
         return "<img src = \"cms/bilder/" . $row->img_real_name."\" alt = \"" . $row->img_description . "\">";
      }else{
         return "0";
      }
      mysql_free_result($result);
   }else{
      return "0";
   }
}

function getimagenamebyid($picid){
   global $conf, $lang;

   if( $picid ){
      $getpic = "Select img_name from ".$conf["db_namespace"]."bilder where img_id='".$picid."'";
      $result = dbquery($getpic);
      if(mysql_affected_rows() > 0)         {
         $row = mysql_fetch_object($result);
         return $row->img_name;
         mysql_free_result($result);
      }
   }
}      
function getimagebyname($name, $style,$page_tpl){
   global $conf, $lang;

   $getpic = "Select img_real_name, img_name, img_description from ".$conf["db_namespace"]."bilder where img_name  like'%" . $name . "%' ";
   $result = dbquery($getpic);
   if(mysql_affected_rows() == 1)         {
      $row = mysql_fetch_object($result);
      if (file_exists($conf["images"] . $row->img_real_name)){
         // vorsichtshalber wegen altdaten
         if (file_exists($conf["images"] . "small_".$row->img_real_name)){
            list($width, $height, $type, $attr) = getimagesize($conf["images"] . "small_".$row->img_real_name);
         } else {
            list($width, $height, $type, $attr) = getimagesize($conf["images"] . $row->img_real_name);      
         }
         $data->img_width  = $width;
         $data->img_height = $height;
         // vorsichtshalber wegen altdaten
         if (file_exists($conf["images"] . "thumb_".$row->img_real_name)){
            $data->img_small_url    = $conf["images"] . "thumb_" . $row->img_real_name;
         }else{
            $data->img_small_url    = $conf["images"] . $row->img_real_name;
         }
         // vorsichtshalber wegen altdaten
         if (file_exists($conf["images"] . "small_".$row->img_real_name)){
            $data->img_small_url    = $conf["images"] . "small_" . $row->img_real_name;
         }else{
            $data->img_small_url    = $conf["images"] . $row->img_real_name;
         }  
         $data->img_big_url      = $conf["images"] . $row->img_real_name;
         $data->img_name   = $row->img_name;
         $data->img_desc   = $row->img_description;

         if ($style==""){$style="c";}
         $tplfile= $conf["templates"].gettemplatebyid($page_tpl).".imgtbl.". $style .".tpl";
         return " " . sprintt($data, $tplfile) . " ";
      }
      else {
      	 return " ";
      }	
   }   

   mysql_free_result($result);
}

function getimagebyid($id, $style,$page_tpl){
   global $conf, $lang;

   $getpic = "Select img_real_name, img_name, img_description from ".$conf["db_namespace"]."bilder where img_id = '" . $id . "'";
   $result = dbquery($getpic);
   if(mysql_affected_rows() == 1)         {
      $row = mysql_fetch_object($result);
      // vorsichtshalber wegen altdaten
      if (file_exists($conf["images"] . "small_".$row->img_real_name)){
         list($width, $height, $type, $attr) = getimagesize($conf["images"] . "small_".$row->img_real_name);
      } else {
         list($width, $height, $type, $attr) = getimagesize($conf["images"] . $row->img_real_name);      
      }
      $data->img_width  = $width;
      $data->img_height = $height;
      // vorsichtshalber wegen altdaten
      if (file_exists($conf["images"] . "thumb_".$row->img_real_name)){
         $data->img_small_url    = $conf["images"] . "thumb_" . $row->img_real_name;
      }else{
         $data->img_small_url    = $conf["images"] . $row->img_real_name;
      }
      // vorsichtshalber wegen altdaten
      if (file_exists($conf["images"] . "small_".$row->img_real_name)){
         $data->img_small_url    = $conf["images"] . "small_" . $row->img_real_name;
      }else{
         $data->img_small_url    = $conf["images"] . $row->img_real_name;
      }  
      $data->img_big_url      = $conf["images"] . $row->img_real_name;
      $data->img_name   = $row->img_name;
      $data->img_desc   = $row->img_description;
   
      if ($style==""){$style="c";}
      $tplfile= $conf["templates"].gettemplatebyid($page_tpl).".imgtbl.". $style .".tpl";
      return " " . sprintt($data, $tplfile) . " ";

   } else { return "0";}


   mysql_free_result($result);
}
function getnavimg($modul, $id){
   global $conf, $lang;

   $result = dbquery("select * from ".$conf["db_namespace"]."module where modul = '". $modul . "'");
   if ( mysql_num_rows($result) == 1 )  {
      $row = mysql_fetch_object($result);
      $Statement = "select ".$row->navimg.", ".$row->navimg."_inactive"."  from ".$conf["db_namespace"]."" . $row->tablename . " where " . $row->id . " = '". $id . "'";
      $modul_result = dbquery($Statement);
      if ( mysql_num_rows($modul_result) > 0 )  {
         $modulrow = mysql_fetch_array($modul_result);
         $picid_a = $modulrow[$row->navimg] ;
         $picid_p = $modulrow[$row->navimg."_inactive"] ;
         if ($conf["page_id"] == $id) {
            $active = 1;
         } else {
         	$active = 0;
         }	   
      }
      mysql_free_result($modul_result);
   }

   if ( $picid_a ){
      $getpic = "Select img_name, img_real_name, img_description from ".$conf["db_namespace"]."bilder where img_id='".$picid_a."'";
      dbconnect();
      $result = dbquery($getpic);
      if(mysql_affected_rows() > 0)         {
         $row = mysql_fetch_object($result);
         $act_pic->name  =  $row->img_name;
         $act_pic->src   =  $conf["images"] . $row->img_real_name;
         $act_pic->desc  =  $row->img_description;
      } else {
         $act_pic->name  =  "";
         $act_pic->src   =  "";
         $act_pic->desc  =  "";
      }      
      mysql_free_result($result);
   }
   if ( $picid_p ){
      $getpic = "Select img_name, img_real_name, img_description from ".$conf["db_namespace"]."bilder where img_id='".$picid_p."'";
      dbconnect();
      $result = dbquery($getpic);
      if(mysql_affected_rows() > 0)         {
         $row = mysql_fetch_object($result);
         $pas_pic->name  =  $row->img_name;
         $pas_pic->src   =  $conf["images"] . $row->img_real_name;
         $pas_pic->desc  =  $row->img_description;
      } else {
         $pas_pic->name  =  "";
         $pas_pic->src   =  "";
         $pas_pic->desc  =  "";
      }
      mysql_free_result($result);
   }
   if ($active==1) {
      $navimg->name = $act_pic->name; 
      $navimg->src  = $act_pic->src;
      $navimg->desc = $act_pic->desc;
   } else {
      $navimg->name = $pas_pic->name; 
      $navimg->src  = $pas_pic->src;
      $navimg->desc = $pas_pic->desc;
   }	           	
   
   $navimg->act = $act_pic;
   $navimg->pas = $pas_pic;
   
   if ($pas_pic->src == "" && $act_pic->src == "") {
      return NULL;
   } else {
   	  return $navimg;
   }	   
}

function gethomeimg(){
   global $conf, $lang;

   $getpic = "Select img_real_name, img_description from ".$conf["db_namespace"]."bilder where img_id='".$conf["home_img"]."'";
   $result = dbquery($getpic);
   if(mysql_affected_rows() > 0)         {
      $row = mysql_fetch_object($result);
      return "<img class = \"logo\"src = \"" . $conf["images"] . $row->img_real_name."\" alt = \"" . $row->img_description . "\">";
   }
   else{
      return "<img src = \"" . $conf["images"]."pixel.gif\" alt = \"blank\">";
   }
   mysql_free_result($result);
}

function gethomenavimg(){
   global $conf, $lang;

   $Statement = "select page_img_small from ".$conf["db_namespace"]."pages where page_id = '". $conf["home_page"] . "'";
   $modul_result = dbquery($Statement);
   if ( mysql_num_rows($modul_result) > 0 )  {
      $modulrow = mysql_fetch_array($modul_result);
      $picid = $modulrow["page_img_small"] ;
   }
   $getpic = "Select img_real_name, img_description from ".$conf["db_namespace"]."bilder where img_id='".$picid."'";
   $result = dbquery($getpic);
   if(mysql_affected_rows() > 0)         {
      $row = mysql_fetch_object($result);
      return "<img class = \"nav_elem_img\"src = \"" . $conf["images"] . $row->img_real_name."\" alt = \"" . $row->img_description . "\">";
   }
   else{
      return "<img src = \"" . $conf["images"]."pixel.gif\" alt = \"blank\">";
   }
   mysql_free_result($result);
}

?>
