<?php 
/*
  platzhalter für die termine:


termine/$id/woche/$woche/$jahr
p=byweek  
id
woche
jahr

termine/$id/tag/$tag/$monat/$jahr
p=bydate  
id
tag
monat
jahr

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

    if ($p == "byweek"){
       $y = (!$y) ? date("Y") : "$y";
       $date = beginning_date_of_week($y, $w);
       $dateParts = split('-', $date); 
       $m = $dateParts[1];
    }
    if (!$p){
       $p = "byweek";
       $d = (!$d) ? date("j") : "$d";
       $m = (!$m) ? date("n") : "$m";
       $y = (!$y) ? date("Y") : "$y";
       $w =  week_number($y, $m, $d);
    }

rendertermin($id, $p, $d, $m, $y, $w);
  
function rendertermin($id, $p, $day, $month, $year, $week){
   global $conf, $lang;

   $my_result = dbquery("select * from ".$conf["db_namespace"]."termin where termin_id='".$id."'");
   if ( mysql_num_rows($my_result) == 1 )   {
      $row = mysql_fetch_object($my_result);
      $termin_id        = $row->termin_id;
      $termin_parent_id = $row->termin_parent_id;
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
      $data->termine->text         = parse_bbcode(nltobr($termin_text), $termin_tpl);
      $data->termine->counter      = $termin_counter;
      
      getterminchildsdata(&$data, $termin_id, $termin_tpl, $p, $week, $day, $month, $year);
      
      drawCalendar(&$data, $p, $week, $day, $month, $year, $termin_id);
      
      $bc = get_breadcrumbs("termine", $termin_id);
      
      $data->left_bar  = parse_bar($termin_tpl, $termin_left_bar, "left", $bc);
      $data->right_bar = parse_bar($termin_tpl, $termin_right_bar,"right", $bc);
      $data->top_bar   = parse_bar($termin_tpl, $termin_top_bar,  "top", $bc);
      $data->foo_bar   = parse_bar($termin_tpl, $termin_foo_bar,  "foo", $bc);
      $data->termine->titel     = $termin_titel;
      $data->titel     = $termin_titel;      
      $data->home_img  = gethomeimg();
      $data->home_url  = $conf["indexname"] . $conf["home_page_typ"] . "/".$conf["home_page"];
      if ($termin_parent_id <> 0){
         $data->termine->parent->name = getterminnamebyid(termin_parent_id);
         $data->termine->parent->url  = $conf["indexname"]."termine/".$termin_parent_id;
      }      
      inctermincounter($termin_id, $termin_counter);
      $page_output = sprintt($data, $conf["templates"].gettemplatebyid($termin_tpl).".tpl");
      echo $page_output;
   } 
   else {renderpage($conf["home_404"],0);}
}

function inctermincounter($termin_id,$termin_counter) {
   global $conf, $lang;
   
   $termin_counter = $termin_counter + 1;
   $inc_query  = "update ".$conf["db_namespace"]."termin set termin_counter = ".$termin_counter." where termin_id = ".$termin_id;
   dbconnect();
   dbquery($inc_query);
}



function getterminchildsdata($data, $termin_id, $termin_tpl, $p, $week, $day, $month, $year){
   global $conf, $lang;

   // get start and end date 4 query depending on $p
   // TODO: $p bymonth, to show all date of month   
   if ($p == "byweek") {
      getStartEndByWeek($week, $year, &$Start, &$End);
   }
   if ($p == "bydate") {
      getStartEndByDate($day, $month, $year, &$Start, &$End);
      $weekday = weekday_by_date($Start);
   }
   $dataquery = "select * from ".$conf["db_namespace"]."termin_data where termin_typ like '%:".$termin_id.":%' and termin_data_date_von <= '" . $End . "' and termin_data_date_bis >= '" . $Start . "' order by termin_data_date_von ASC";   
   $dataresult = dbquery($dataquery);
   if ( mysql_num_rows($dataresult) > 0 ){
      $akt = 0;
      while ( $datarow = mysql_fetch_object($dataresult) ){
          $print = false;
          if ($datarow->termin_data_typ == "T") {
             $von_date       = mydate2date($datarow->termin_data_date_von);
             $bis_date       = mydate2date($datarow->termin_data_date_bis);
             $print = true;
          }
          if ($datarow->termin_data_typ == "P") {
             $p_date_weekday = $datarow->termin_data_typ_day; 
             if ($p == "bydate"){
                $wd = weekday_by_date($Start);
                if ($wd == $weekday) {
                   $von_date       = mydate2date($Start);
                   $bis_date       = mydate2date($Start);
                   $print = true;
                }   
             }
             if ($p == "byweek"){
                $year  = getYearFromDate($Start);
                $von_date = datefromweeknr($year,$week, $p_date_weekday);
                $bis_date = von_date;
                $print = true;
             }     
          }
            
          if($print){  
             $akt++;
             $data->termine->termin_data[$akt]->von_date       = $von_date;
             $data->termine->termin_data[$akt]->bis_date       = $bis_date;
             $data->termine->termin_data[$akt]->von_time       = mydate2time($datarow->termin_data_date_von);
             $data->termine->termin_data[$akt]->bis_time       = mydate2time($datarow->termin_data_date_bis);         
             $data->termine->termin_data[$akt]->name           = $datarow->termin_data_headline;
             $data->termine->termin_data[$akt]->veranstalter   = $datarow->termin_data_Veranstalter;
             $data->termine->termin_data[$akt]->ort            = $datarow->termin_data_Ort;
             $data->termine->termin_data[$akt]->url            = $datarow->termin_data_URL;                           
             $data->termine->termin_data[$akt]->text           = parse_bbcode(nltobr($datarow->termin_data_content), $termin_tpl);      
          }                
      }
      mysql_free_result($dataresult);     
   }
   
   $query = "select * from ".$conf["db_namespace"]."termin where termin_parent_id = '".$termin_id."' order by termin_name ASC";
   $result = dbquery($query);
   if ( mysql_num_rows($result) > 0 ){
      $akt = 0;
      while ( $row = mysql_fetch_object($result) ){
         $akt++;
         $data->termine->termin_childs[$akt]->name   = $row->termin_name;
         $data->termine->termin_childs[$akt]->url    = $conf["indexname"]."termine/".$row->termin_id;
      }
 	mysql_free_result($result);  
   }

}
  
 
function getterminnamebyid($id){
   global $conf, $lang;
   
   $my_result = dbquery("select termin_name from ".$conf["db_namespace"]."termin where termin_id='".$id."'");
   if ( mysql_num_rows($my_result) == 1 )      {
      $row = mysql_fetch_object($my_result);
      $name = $row->termin_name;
      mysql_free_result($my_result);
      return $name;
   }
}       

function drawCalendar($data, $p, $w, $d, $m, $y, $termin_id) {
   global $conf, $lang;
            
   $ldm = last_day_of_the_month($m,$y);   
      
      
   if ($p == "bydate") {  // termine/$id/tag/$tag/$monat/$jahr
      if ($ldm < $d){$d=$ldm;}
      $nm = (($m+1)>12) ?  1 : $m+1;
      $nj = (($m+1)>12) ? $y+1 : $y;
      $pm = (($m-1)< 1) ? 12 : $m-1;
      $pj = (($m-1)< 1) ? $y-1 : $y;
      $data->termine->Kalender->prev_url =  $conf["indexname"]."termine/".$termin_id ."/tag/". $d ."/". $pm . "/". $pj;
      $data->termine->Kalender->next_url =  $conf["indexname"]."termine/".$termin_id ."/tag/". $d ."/". $nm . "/". $nj;
   } 
   if ($p == "byweek") {  // termine/$id/woche/$woche/$jahr
      $pw = (($w-1) < 1) ? week_number($y-1, 12, 31) : $w-1;
      $pj = (($w-1) < 1) ? $y-1 : $y;
      $nw = (($w+1) > week_number($y, 12,31)) ? week_number($y+1,  1,  1) : $w+1;
      $nj = (($w+1) > week_number($y, 12,31)) ? $y+1 : $y;
      $data->termine->Kalender->prev_url =  $conf["indexname"]."termine/".$termin_id ."/woche/" . $pw . "/". $pj;
      $data->termine->Kalender->next_url =  $conf["indexname"]."termine/".$termin_id ."/woche/" . $nw . "/". $nj;

   }
   $data->termine->Kalender->akt_monat = month_name($m);
   $bwm = beginning_weekday_of_the_month($y, $m);
   $ewm = ending_weekday_of_the_month($y, $m);
   
   $data->termine->Kalender->week[0]->day[0]->url = weekday_short_name(1); 
   $data->termine->Kalender->week[0]->day[1]->url = weekday_short_name(2);
   $data->termine->Kalender->week[0]->day[2]->url = weekday_short_name(3);
   $data->termine->Kalender->week[0]->day[3]->url = weekday_short_name(4);
   $data->termine->Kalender->week[0]->day[4]->url = weekday_short_name(5);
   $data->termine->Kalender->week[0]->day[5]->url = weekday_short_name(6);
   $data->termine->Kalender->week[0]->day[6]->url = weekday_short_name(0);

   $aktday = 0;
   $aktweek = 1;
   $day = 0;
   
   $kw = week_number($y, $m, 1);
   $data->termine->Kalender->week[1]->weeknum->url = $conf["indexname"]."termine/".$termin_id ."/woche/" . $kw . "/". $y;
   $data->termine->Kalender->week[1]->weeknum->kw =  $kw;
   if ($kw==$w) {$data->termine->Kalender->week[1]->weeknum->akt =  "1";}
   else {$data->termine->Kalender->week[1]->weeknum->akt =  "0";}
   
   for ($i=1; $i < $bwm; $i++){ 
       $aktday++;
       $data->termine->Kalender->week[$aktweek]->day[$aktday]->url = "&nbsp;";
   }

   while ($day < $ldm) {
      $day++;
      $aktday++;
      $data->termine->Kalender->week[$aktweek]->day[$aktday]->url = $conf["indexname"]."termine/".$termin_id ."/tag/".$day."/".$m."/".$y;
      $data->termine->Kalender->week[$aktweek]->day[$aktday]->day = $day;
      if ($day==$d) {$data->termine->Kalender->week[$aktweek]->day[$aktday]->akt =  "1";}
      else {$data->termine->Kalender->week[$aktweek]->day[$aktday]->akt =  "0";}

      if ($aktday>6) { 
         $aktweek++;
         $aktday=0;
         $kw++;
         if($kw>53)$kw=1;
         $data->termine->Kalender->week[$aktweek]->weeknum->url = $conf["indexname"]."termine/".$termin_id ."/woche/" . $kw . "/". $y;
         $data->termine->Kalender->week[$aktweek]->weeknum->kw =  $kw;
         if ($kw==$w) {$data->termine->Kalender->week[$aktweek]->weeknum->akt =  "1";}
         else {$data->termine->Kalender->week[$aktweek]->weeknum->akt =  "0";}
      }

   }
   for ($i=$aktday; $i<7; $i++){ 
      $aktday++;
      $data->termine->Kalender->week[$aktweek]->day[$aktday]->url = "&nbsp;";
   }   
}
?>            