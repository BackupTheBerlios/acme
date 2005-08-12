<?php
function mydate2datetime($date){
	 return substr ($date, 5,2)  .  "/". substr ($date, 8,2) . "/" . substr ($date, 0,4) . " " . substr ($date, 11,5);
}
function mydate2date($date){  
	return substr ($date, 5,2)  .  "/". substr ($date, 8,2) . "/" . substr ($date, 0,4);
}
function mydate2time($date){  
	return substr ($date, 11,5);
}
function createdateinput($name, $date, $style) {
  if($date=="") {
     $day   =  date("d");
     $month =  date("m");
     $year  =  date("Y");
  } else {
  	$day   = substr ($date, 8,2);
  	$month = substr ($date, 5,2);
  	$year  = substr ($date, 0,4);  
  }
  if ($style <> "") {	
     echo "<input  name=\"".$name."_month\" size=\"2\" maxlength=\"2\" value=\"" . $month . "\" style=\"". $style ."\">/";
     echo "<input  name=\"".$name."_day\" size=\"2\" maxlength=\"2\" value=\"" . $day . "\" style=\"". $style ."\">/";
  	 echo "<input  name=\"".$name."_year\" size=\"4\" maxlength=\"4\" value=\"" . $year . "\" style=\"". $style ."\">";
  } else {
  	 echo "<input  name=\"".$name."_month\" size=\"2\" maxlength=\"2\" value=\"" . $month . "\">/";
  	 echo "<input  name=\"".$name."_day\" size=\"2\" maxlength=\"2\" value=\"" . $day . "\">/";  	 
  	 echo "<input  name=\"".$name."_year\" size=\"4\" maxlength=\"4\" value=\"" . $year . "\">";
  }
}  
function createdatetimeinput($name, $datetime, $style) {
  if($datetime=="") {
     $day     =  date("d");
     $month   =  date("m");
     $year    =  date("Y");
     $hour    =  date("H");
     $minute  =  date("i");
  } else {
  	$day    = substr ($datetime, 8,2);
  	$month  = substr ($datetime, 5,2);
  	$year   = substr ($datetime, 0,4);  
    $hour   = substr ($datetime, 11,2);
    $minute = substr ($datetime, 14,2);
  }
  if ($style <> "") {	
     echo "<input  name=\"".$name."_month\" size=\"2\" maxlength=\"2\" value=\"" . $month . "\" style=\"". $style ."\">/";
     echo "<input  name=\"".$name."_day\" size=\"2\" maxlength=\"2\" value=\"" . $day . "\" style=\"". $style ."\">/";
  	 echo "<input  name=\"".$name."_year\" size=\"4\" maxlength=\"4\" value=\"" . $year . "\" style=\"". $style ."\">&nbsp;&nbsp;";
  	 echo "<input  name=\"".$name."_hour\" size=\"2\" maxlength=\"2\" value=\"" . $year . "\" style=\"". $style ."\">:";
  	 echo "<input  name=\"".$name."_minute\" size=\"2\" maxlength=\"2\" value=\"" . $year . "\" style=\"". $style ."\">";  	 
  } else {
  	 echo "<input  name=\"".$name."_month\" size=\"2\" maxlength=\"2\" value=\"" . $month . "\">/";
  	 echo "<input  name=\"".$name."_day\" size=\"2\" maxlength=\"2\" value=\"" . $day . "\">/";
  	 echo "<input  name=\"".$name."_year\" size=\"4\" maxlength=\"4\" value=\"" . $year . "\">&nbsp;&nbsp;";
  	 echo "<input  name=\"".$name."_hour\" size=\"4\" maxlength=\"4\" value=\"" . $hour . "\">:";
  	 echo "<input  name=\"".$name."_minute\" size=\"4\" maxlength=\"4\" value=\"" . $minute . "\">";
  }
}

function month_name($month){
  switch($month) {
   case 0: return "Month is between 1-12!";
   case 1: return "January";
   case 2: return "February";
   case 3: return "March";
   case 4: return "April";
   case 5: return "May";
   case 6: return "June";
   case 7: return "July";
   case 8: return "August";
   case 9: return "September";
   case 10: return "October";
   case 11: return "November";
   case 12: return "December";
  }
  return "unknown-month($m)";
}

function month_short_name($month){
  switch($month) {
   case 0: return "";
   case 1: return "Jan";
   case 2: return "Feb";
   case 3: return "Mar";
   case 4: return "Apr";
   case 5: return "May";
   case 6: return "Jun";
   case 7: return "Jul";
   case 8: return "Aug";
   case 9: return "Sep";
   case 10: return "Oct";
   case 11: return "Nov";
   case 12: return "Dec";
  }
  return "($m)";
}


// Return the full weekday name
// $weekday_value - weekday (0=Sunday,...,6=Saturday)
function weekday_name($weekday_value)
{
  switch($weekday_value) {
   case 0: return "Sunday";
   case 1: return "Monday";
   case 2: return "Tuesday";
   case 3: return "Wednesday";
   case 4: return "Thursday";
   case 5: return "Friday";
   case 6: return "Saturday";
  }
  return "unknown-weekday($w)";
}

// Return the abbreviated weekday name
// $weekday_value - weekday (0=Sunday,...,6=Saturday)
function weekday_short_name($weekday_value)
{
  switch($weekday_value) {
   case 0: return "Sun";
   case 1: return "Mon";
   case 2: return "Tue";
   case 3: return "Wed";
   case 4: return "Thu";
   case 5: return "Fri";
   case 6: return "Sat";
  }
  return "unknown-weekday($w)";
}

?>