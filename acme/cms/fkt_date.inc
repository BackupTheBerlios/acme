<?
function last_day_of_the_month($mon,$year) {
    for ($tday=28; $tday <= 31; $tday++) {
        $tdate = getdate(mktime(0,0,0,$mon,$tday,$year));
        if ($tdate["mon"] != $mon){ break; }
    }
    $tday--;
    return $tday;
}

function number_of_days_in_month($year, $month){
  $days_in_the_month = array (31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31);
  if ($month != 2) return $days_in_the_month[$month - 1];
  return (checkdate($month, 29, $year)) ? 29 : 28;
}

function check_valid_date($date){
  list($year, $month, $day) = explode("-", $date);
  if ($year < 1900 || $year > 2050) { return false; }
  $days_in_month = number_of_days_in_month($year, $month);
  if ($day+0 > $days_in_month+0) { return false; }
  return true;
}

function beginning_date_of_week($year, $week) {
   $searchdate = mktime(0,0,0,12,20,$year-1);
   $searchdate = strtotime("+".($week-1)." week",$searchdate);
   $found=false;
   while ($found==false){
      if (date("W",$searchdate) == $week) {$found = true;}
      else {$searchdate = strtotime("+1 day",$searchdate);}
   }
   return date('Y-m-d 00:00:00', $searchdate);
} 

function ending_date_of_week($year, $week) {
   $date = beginning_date_of_week($year, $week); 
   return add_delta_ymd($date, 0, 0, 6);
} 


function beginning_weekday_of_the_month($year, $month) {
  return date("w", mktime(0, 0, 0, $month, 1, $year));
}

function ending_weekday_of_the_month($year, $month) {
  return date("w", mktime(1, 0, 0, $month, last_day_of_the_month($month,$year), $year));
}

function weekday_by_date($date) {
  list($year, $month, $day) = explode("-", $date);
  return date("w", mktime(1, 0, 0, $month, $day, $year));
}

function sunday_before_date($date) {
  list($year, $month, $day) = explode("-", $date);
  $day_of_the_week = date("w", mktime(1, 0, 0, $month, $day, $year));
  return date('Y-m-d', mktime(1, 0, 0, $month, $day - $day_of_the_week, $year));
}

function monday_before_date($date) {
  list($year, $month, $day) = explode("-", $date);
  $day_of_the_week = date("w", mktime(1, 0, 0, $month, $day, $year));
  if ($day_of_the_week == 0) {
    return date('Y-m-d', mktime(1, 0, 0, $month, $day - 6, $year));
  } elseif ($day_of_the_week == 1) {
    return date('Y-m-d', mktime(1, 0, 0, $month, $day, $year));
  } else {
    return date('Y-m-d', mktime(1, 0, 0, $month, $day - $day_of_the_week + 1, $year));
  }
}

function sunday_after_date($date) {
  return add_delta_ymd($date, 0,0,6);
}

function add_delta_ymd($date, $delta_years = 0, $delta_months = 0, $delta_days = 0) {
  if ($delta_years != 0) {
   list($year, $month, $day) = explode("-", $date);
   if ($month == 2 && $day == 29) {
      $tmp_date = date("Y-m", mktime(1, 0, 0, $month, 1, $year + $delta_years));
      list($new_year, $new_month) = explode("-", $tmp_date);
      $days_in_month = number_of_days_in_month($new_year, $new_month);
      if ($days_in_month < $day) { $day = $days_in_month; }
      $date = $new_year . '-' . $month . '-' . $day;
    } else {
      $new_year = $year + $delta_years;
      $date = sprintf("%04d-%02d-%02d", $new_year, $month, $day);
   }
  }
  if ($delta_months != 0) {
   list($year, $month, $day) = explode("-", $date);
   $new_year = $year;
   $new_month = $month + $delta_months;
   if ($delta_months < -840 || $delta_months > 840) { $new_month = $month; } // Bad Delta
   if ($delta_months > 0) { // Adding Months
      while ($new_month > 12) {
         $new_year++;
         $new_month -= 12;
      }
   } elseif ($delta_months < 0) {
      while ($new_month < 1) {
         $new_year--;
         $new_month += 12;
      }
   }
   $days_in_month = number_of_days_in_month($new_year, $new_month);
   if ($days_in_month < $day) { $day = $days_in_month; }
   $date = sprintf("%04d-%02d-%02d", $new_year, $new_month, $day);
  }
  if ($delta_days != 0) {
   list($year, $month, $day) = explode("-", $date);
   $date = date("Y-m-d", mktime(1, 0, 0, $month, $day, $year) + $delta_days*24*60*60);
  }
  return $date;
}

function week_number($year, $month, $day) {
  if (WEEK_START == 0) { $day++; } // Add one to get to Monday.
  $timestamp = mktime(1, 0, 0, $month, $day, $year);
  $week = "";
  $week = strftime("%V", $timestamp); // ISO Weeks start on Mondays
  if ($week == "") {$week = ISOWeek($year, $month, $day);}
  return $week + 0;
}

function ISOWeek($y, $m, $d){
  $week = strftime("%W", mktime(0, 0, 0, $m, $d, $y));
  $dow0101 = getdate(mktime(0, 0, 0, 1, 1, $y));
  $next0101 = getdate(mktime(0, 0, 0, 1, 1, $y+1));
  if ($dow0101["wday"] > 1 && $dow0101["wday"] < 5) { $week++; }
  if ($next0101["wday"] > 1 && $next0101["wday"] < 5 && $week == 53) { $week = 1; }
  if ($week == 0) { $week = ISOWeek($y-1,12,31); }
  return substr("00" . $week, -2); 
} 

function days_span($start_date, $end_date) {
  list($year, $month, $day) = explode("-", $start_date);
  $start_time_stamp = mktime(1, 0, 0, $month, $day, $year);
  list($year, $month, $day) = explode("-", $end_date);
  $end_time_stamp = mktime(1, 0, 0, $month, $day, $year);
  return round(($end_time_stamp - $start_time_stamp)/(24*60*60))+1;
}
?>