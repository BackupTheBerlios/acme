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
  if($date=="") {
     $day     =  date("d");
     $month   =  date("m");
     $year    =  date("Y");
     $hour    =  date("H");
     $minute  =  date("i");
  } else {
  	$day    = substr ($date, 8,2);
  	$month  = substr ($date, 5,2);
  	$year   = substr ($date, 0,4);  
    $hour   = substr ($date, 11,2);
    $minute = substr ($date, 14,2);
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
?>