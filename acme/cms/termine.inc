<?php 
/*
  platzhalter für die termine:

  gültig innerhalb{mask:main}
     titel                Seitenüberschrift
     left_bar				  linke Navigation
     right_bar            rechte Navigation
     top_bar              obere Navigation
     foo_bar              untere Navigation
     home_img
     home_url
     gültig innerhalb {mask:termine} 
        titel 				
        img_small
        img_big
        text
        counter
        {mask:parent}            
           name	  Überschrift Elternseite
        {/mask:page_parent}  
        gültig innerhalb {mask:termin_childs}  // unterkategorien
           name
           url
           gültig innerhalb {mask:termin_childs_data}  // und die termine dazu
              von_date
              von_time
              bis_date
              bis_time
              name
              veranstalter
              ort
              url
              text
*/ 

rendertermin($id);
  
function rendertermin($id){
   global $conf, $lang;

   $my_result = dbquery("select * from acme_termin where termin_id='".$id."'");
   if ( mysql_num_rows($my_result) == 1 )   {
      $row = mysql_fetch_object($my_result);
      $termin_id        = $row->termin_id;
      $termin_name      = $row->termin_name;
      $termin_tpl       = $row->termin_tpl;
      $termin_img_small = $row->termin_img_small;
      $termin_img_big   = $row->termin_img_big;
      $termin_left_bar  = $row->termin_left_bar;
      $termin_right_bar = $row->termin_right_bar;
      $termin_top_bar   = $row->termin_top_bar;
      $termin_foo_bar   = $row->termin_foo_bar;
      $termin_titel     = $row->termin_titel;
      $termin_text      = $row->termin_text;
      $termin_counter   = $row->termin_counter;
      mysql_free_result($my_result);
      $data->termine->img_small    = getimage($termin_img_small);
      $data->termine->img_big      = getimage($termin_img_big);
      $data->termine->text         = parse_bbcode(nltobr($termin_text), $page_tpl);
      $data->termine->counter      = $termin_counter;
      getterminchildsdata(&$data, $termin_id, $termin_tpl);
      if ($termin_left_bar  <> 0){$data->left_bar  = parse_bar($termin_tpl, $termin_left_bar, "left");}else{$data->left_bar  = "<!-- leer -->";}
      if ($termin_right_bar <> 0){$data->right_bar = parse_bar($termin_tpl, $termin_right_bar,"right");}else{$data->right_bar  = "<!-- leer -->";}
      if ($termin_top_bar   <> 0){$data->top_bar   = parse_bar($termin_tpl, $termin_top_bar,  "top");}else{$data->top_bar  = "<!-- leer -->";}
      if ($termin_foo_bar   <> 0){$data->foo_bar   = parse_bar($termin_tpl, $termin_foo_bar,  "foo");}else{$data->foo_bar  = "<!-- leer -->";}
      $data->termine->titel     = $termin_titel;
      $data->titel     = $termin_titel;      
      $data->home_img  = gethomeimg();
      $data->home_url  = $conf["indexname"] . $conf["home_page_typ"] . "/".$conf["home_page"];
      if ($termin_parent_id <> 0){
         $data->termine->parent->name = getterminnamebyid($url_typ_parent);
         $data->termine->parent->url  = $conf["indexname"]."urls/".$url_typ_parent;
      }      
      inctermincounter($termin_id, $termin_counter);
      $page_output = sprintt($data, "cms/tpl/".gettemplatebyid($termin_tpl).".tpl");
      echo $page_output;
   } 
   else {renderpage($conf["home_404"],0);}
}

function inctermincounter($termin_id,$termin_counter) {
   global $conf, $lang;
   
   $termin_counter = $termin_counter + 1;
   $inc_query  = "update acme_termin set termin_counter = ".$termin_counter." where termin_id = ".$termin_id;
   dbconnect();
   dbquery($inc_query);
}

function getterminchildsdata($data, $termin_id, $termin_tpl, $range="week"){
   global $conf, $lang;
   
   $today = date('m-d-Y'); 
   $dateParts = split('-', $today); 
   $week = date('W', mktime(0, 0, 0, $dateParts[0], $dateParts[1], $dateParts[2])); 
   $weekDay = date('w', mktime(0, 0, 0, $dateParts[0], $dateParts[1], $dateParts[2])); 
   $weekStart = date('Y-m-d', mktime(0, 0, 0, $dateParts[0], ($dateParts[1] - $weekDay), $dateParts[2])); 
   $weekEnd = date('Y-m-d', mktime(0, 0, 0, $dateParts[0], ($dateParts[1] + (6 - $weekDay)), $dateParts[2]));
   $weekStart .= " 00:00:00";
   $weekEnd .= " 00:00:00";
   
   if ($range=="week")  {$Start = $weekStart; $End = $weekEnd;}
   if ($range=="month") {$Start = $weekStart; $End = $weekEnd;}

   $dataquery = "select * from acme_termin_data where termin_typ like '%:".$termin_id.":%' and termin_data_date_von >= '" . $Start . "' and termin_data_date_bis <= '" . $End . "' order by termin_data_date_von ASC";
   $dataresult = dbquery($dataquery);
   if ( mysql_num_rows($dataresult) > 0 ){
      $akt = 0;
      while ( $datarow = mysql_fetch_object($dataresult) ){
          $akt++;
          $data->termine->termin_data[$akt]->von_date   = mydate2date($datarow->termin_data_date_von);
          $data->termine->termin_data[$akt]->von_time   = mydate2time($datarow->termin_data_date_von);         
          $data->termine->termin_data[$akt]->bis_date   = mydate2date($datarow->termin_data_date_bis);
          $data->termine->termin_data[$akt]->bis_time   = mydate2time($datarow->termin_data_date_bis);         
          $data->termine->termin_data[$akt]->name      = $datarow->termin_data_headline;
          $data->termine->termin_data[$akt]->veranstalter   = $datarow->termin_data_Veranstalter;
          $data->termine->termin_data[$akt]->ort        = $datarow->termin_data_Ort;
          $data->termine->termin_data[$akt]->url        = $datarow->termin_data_URL;                           
          $data->termine->termin_data[$akt]->text       = parse_bbcode(nltobr($datarow->termin_data_content), $termin_tpl);                  
      }
      mysql_free_result($dataresult);     
   }
   
   $query = "select * from acme_termin where termin_parent_id = '".$termin_id."' order by termin_name ASC";
   $result = dbquery($query);
   if ( mysql_num_rows($result) > 0 ){
      $akt = 0;
      while ( $row = mysql_fetch_object($result) ){
         $akt++;
         $data->termine->termin_childs[$akt]->name   = $row->termin_name;
         $dataquery = "select * from acme_termin_data where termin_typ like '%:".$row->termin_id.":%' and termin_data_date_von >= '" . $Start . "' and termin_data_date_bis <= '" . $End . "' order by termin_data_date_von ASC";
         $dataresult = dbquery($dataquery);
         if ( mysql_num_rows($dataresult) > 0 ){
            $data_akt = 0;
            while ( $datarow = mysql_fetch_object($dataresult) ){
               $data_akt++;
               $data->termine->termin_childs[$akt]->termin_childs_data[$data_akt]->von_date   = mydate2date($datarow->termin_data_date_von);
               $data->termine->termin_childs[$akt]->termin_childs_data[$data_akt]->von_time   = mydate2time($datarow->termin_data_date_von);         
               $data->termine->termin_childs[$akt]->termin_childs_data[$data_akt]->bis_date   = mydate2date($datarow->termin_data_date_bis);
               $data->termine->termin_childs[$akt]->termin_childs_data[$data_akt]->bis_time   = mydate2time($datarow->termin_data_date_bis);         
               $data->termine->termin_childs[$akt]->termin_childs_data[$data_akt]->name      = $datarow->termin_data_headline;
               $data->termine->termin_childs[$akt]->termin_childs_data[$data_akt]->veranstalter   = $datarow->termin_data_Veranstalter;
               $data->termine->termin_childs[$akt]->termin_childs_data[$data_akt]->ort        = $datarow->termin_data_Ort;
               $data->termine->termin_childs[$akt]->termin_childs_data[$data_akt]->url        = $datarow->termin_data_URL;                           
               $data->termine->termin_childs[$akt]->termin_childs_data[$data_akt]->text       = parse_bbcode(nltobr($datarow->termin_data_content), $termin_tpl);                  
            }
            mysql_free_result($dataresult);     
         }
      }
 	mysql_free_result($result);  
   }

}
  
 
function getterminnamebyid($id){
   global $conf, $lang;
   
   $my_result = dbquery("select termin_name from acme_termin where termin_id='".$id."'");
   if ( mysql_num_rows($my_result) == 1 )
      {
      $row = mysql_fetch_object($my_result);
      $name = $row->termin_name;
      mysql_free_result($my_result);
      return $name;
      }
}       
?>            