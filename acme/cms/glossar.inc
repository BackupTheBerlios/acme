<?php
/*

  platzhalter fÃ¼r die Seite:

  {mask:main}
     titel                SeitenÃ¼berschrift
     {mask:glossar}
        img_titel
        titel
        text
     {/mask}
  {/mask}

   1 Bild oben zentriert
   2 Bild unten zentriert
   3 Bild rechts oben
   4 Bild rechts unten
   5 Bild links oben
   6 Bild links unten
   7 Bild links
   8 Bild rechts


*/

if ($page == "glossar"){
   $titel     = array_shift($path);
   $part = array_shift($path);
   if (!isset($titel)){$titel = "";}
   if (!isset($part)){$part = substr($titel,0,1);}   
   renderglossar($titel, $part);
}

function renderglossar($titel, $part){

   global $conf, $lang;

   if ($part == ""){$part = substr($titel,0,1);}

   $query = "select * from acme_glossar where glossar_titel like '".$part."%' order by glossar_titel";
   $my_result = dbquery($query);
   if ( mysql_num_rows($my_result) > 0 ){
      while ($row = mysql_fetch_object($my_result)){
         $akt++;
         $data->glossar_eintr[$akt]->url   = $conf["indexname"] . "glossar/" . $row->glossar_titel . "/" . $part;
         $data->glossar_eintr[$akt]->titel = $row->glossar_titel;
      }
      mysql_free_result($my_result);
   }

   $data->glossar_parts[1]->url   = $conf["indexname"] . "glossar//a";
   $data->glossar_parts[1]->part  = "A";
   $data->glossar_parts[2]->url   = $conf["indexname"] . "glossar//ä";
   $data->glossar_parts[2]->part  = "&Auml;";
   $data->glossar_parts[3]->url   = $conf["indexname"] . "glossar//b";
   $data->glossar_parts[3]->part  = "B";
   $data->glossar_parts[4]->url   = $conf["indexname"] . "glossar//c";
   $data->glossar_parts[4]->part  = "C";
   $data->glossar_parts[5]->url   = $conf["indexname"] . "glossar//d";
   $data->glossar_parts[5]->part  = "D";
   $data->glossar_parts[6]->url   = $conf["indexname"] . "glossar//e";
   $data->glossar_parts[6]->part  = "E";
   $data->glossar_parts[7]->url   = $conf["indexname"] . "glossar//f";
   $data->glossar_parts[7]->part  = "F";
   $data->glossar_parts[8]->url   = $conf["indexname"] . "glossar//g";
   $data->glossar_parts[8]->part  = "G";
   $data->glossar_parts[9]->url   = $conf["indexname"] . "glossar//h";
   $data->glossar_parts[9]->part  = "H";
   $data->glossar_parts[10]->url   = $conf["indexname"] . "glossar//i";
   $data->glossar_parts[10]->part  = "I";
   $data->glossar_parts[11]->url   = $conf["indexname"] . "glossar//j";
   $data->glossar_parts[11]->part  = "J";
   $data->glossar_parts[12]->url   = $conf["indexname"] . "glossar//k";
   $data->glossar_parts[12]->part  = "K";
   $data->glossar_parts[13]->url   = $conf["indexname"] . "glossar//l";
   $data->glossar_parts[13]->part  = "L";
   $data->glossar_parts[14]->url   = $conf["indexname"] . "glossar//m";
   $data->glossar_parts[14]->part  = "M";
   $data->glossar_parts[15]->url   = $conf["indexname"] . "glossar//n";
   $data->glossar_parts[15]->part  = "N";
   $data->glossar_parts[16]->url   = $conf["indexname"] . "glossar//o";
   $data->glossar_parts[16]->part  = "O";
   $data->glossar_parts[17]->url   = $conf["indexname"] . "glossar//ö";
   $data->glossar_parts[17]->part  = "&OumL";
   $data->glossar_parts[18]->url   = $conf["indexname"] . "glossar//p";
   $data->glossar_parts[18]->part  = "P";
   $data->glossar_parts[19]->url   = $conf["indexname"] . "glossar//q";
   $data->glossar_parts[19]->part  = "Q";
   $data->glossar_parts[20]->url   = $conf["indexname"] . "glossar//r";
   $data->glossar_parts[20]->part  = "R";
   $data->glossar_parts[21]->url   = $conf["indexname"] . "glossar//s";
   $data->glossar_parts[21]->part  = "S";
   $data->glossar_parts[22]->url   = $conf["indexname"] . "glossar//t";
   $data->glossar_parts[22]->part  = "T";
   $data->glossar_parts[23]->url   = $conf["indexname"] . "glossar//u";
   $data->glossar_parts[23]->part  = "U";
   $data->glossar_parts[24]->url   = $conf["indexname"] . "glossar//ü";
   $data->glossar_parts[24]->part  = "&Uuml;";
   $data->glossar_parts[25]->url   = $conf["indexname"] . "glossar//v";
   $data->glossar_parts[25]->part  = "V";
   $data->glossar_parts[26]->url   = $conf["indexname"] . "glossar//w";
   $data->glossar_parts[26]->part  = "W";
   $data->glossar_parts[27]->url   = $conf["indexname"] . "glossar//x";
   $data->glossar_parts[27]->part  = "X";
   $data->glossar_parts[28]->url   = $conf["indexname"] . "glossar//y";
   $data->glossar_parts[28]->part  = "Y";
   $data->glossar_parts[29]->url   = $conf["indexname"] . "glossar//z";
   $data->glossar_parts[29]->part  = "Z";

   if ($titel <> ""){
      $query = "select * from acme_glossar where glossar_titel Like '%".$titel."%'";
      $my_result = dbquery($query);
      if ( mysql_num_rows($my_result) == 1 ){
         $row = mysql_fetch_object($my_result);
         $glossar_id    = $row->glossar_id;
         $glossar_titel = $row->glossar_titel;
         $glossar_text  = $row->glossar_text;
         $glossar_img   = $row->glossar_img;
         $glossar_tpl   = $row->glossar_tpl;

         $data->titel    = "Glossar " . $glossar_titel;
         $data->home_img = gethomeimg();

         $data->glossar->titel = $glossar_titel;
         
         $text  = parse_bbcode(nltobr($glossar_text), gettemplatebyid($conf["home_tpl"]));
         get_glossar_img($glossar_img, &$sub_data);
         
         $sub_data->text = $text; 
         
         $sub_tplfile = "cms/tpl/" . gettemplatebyid($conf["home_tpl"]) . ".sub." . $glossar_tpl .".tpl";
         $sub_page_output = sprintt($sub_data, $sub_tplfile);

         $data->glossar->subtpl = $sub_page_output;
         mysql_free_result($my_result);
      }
   }

   $tplfile = "cms/tpl/" . gettemplatebyid($conf["home_tpl"]) . ".glossar.tpl";
   $page_output = sprintt($data, $tplfile);
   echo $page_output;
}

function get_glossar_img($img_id, $sub_data){
   global $conf, $lang;

   $getpic = "Select img_real_name, img_name, img_description from acme_bilder where img_id  = '" . $img_id . "'";
   $result = dbquery($getpic);
   if(mysql_affected_rows() == 1)         {
      $row = mysql_fetch_object($result);
      list($width, $height, $type, $attr) = getimagesize("cms/bilder/small_".$row->img_real_name);
      $sub_data->img_width  = $width;
      $sub_data->img_height = $height;
      $sub_data->img_thumb_url    = "cms/bilder/thumb_" . $row->img_real_name;
      $sub_data->img_small_url    = "cms/bilder/small_" . $row->img_real_name;
      $sub_data->img_big_url      = "cms/bilder/" . $row->img_real_name;
      $sub_data->img_name   = $row->img_name;
      $sub_data->img_desc   = $row->img_description;
      mysql_free_result($result);
   }
}
?>

