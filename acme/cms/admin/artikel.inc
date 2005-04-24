<?php

include($conf["admbase"] . "/lang/artikel." . $conf["lang"] . ".inc");

switch($action){
	case "edit":
	   $error = 0;
	   $_SESSION['artikel_edit_page_id'] = $page_id;
       artikel_edit($edit_artikel_id, $edit_artikel_page,$edit_artikel_publish_date_day,$edit_artikel_publish_date_month,$edit_artikel_publish_date_year,$edit_artikel_headline,$edit_artikel_sub_headline,$edit_artikel_short_text,$edit_artikel_long_text,$new_artikel_long_text, $edit_artikel_author_id, $edit_artikel_aktiv,$edit_artikel_comments,$error, $errortext);
		
      break;
      
	case "new":
		artikel_new($new_artikel_page,$new_artikel_publish_date_day,$new_artikel_publish_date_month,$new_artikel_publish_date_year,$new_artikel_headline,$new_artikel_sub_headline,$new_artikel_short_text,$new_artikel_long_text, $new_artikel_author_id,$new_artikel_aktiv,$new_artikel_comments, $error, $errortext);
		
      break;
      
   case "add":
      $error = 0;
      $errortext = "";
      if (!($new_artikel_page <> "")) {
      	$errortext .= $lang["artikel_seite_fehlt"]."<br>"; 
      	$error = 1;
      }
      if ($new_artikel_headline == ""){
      	 $errortext .= $lang["artikel_ueberschrift1_fehlt"]."<br>";
      	 $error = 1;
      }
      if ($new_artikel_sub_headline == ""){
      	$errortext .= $lang["artikel_ueberschrift2_fehlt"]."<br>";
      	$error = 1;
      }            
      if ($new_artikel_short_text == ""){
      	$errortext .= $lang["artikel_kurztext_fehlt"]."<br>";
      	$error = 1;
      }
      if ($new_artikel_publish_date_day == "" || $new_artikel_publish_date_month == "" || $new_artikel_publish_date_year == "" || $new_artikel_publish_date_hour == "" || $new_artikel_publish_date_minute == ""){
        $errortext .= $lang["artikel_veroeffentlichungsdatum_fehlt"];
      	$error = 1;
      }
      if ($error == 0){
         $new_artikel_publish_date = $new_artikel_publish_date_year . "-" . $new_artikel_publish_date_month . "-" . $new_artikel_publish_date_day . "- ".$new_artikel_publish_date_hour. ":".$new_artikel_publish_date_minute.":00";
         $result = artikel_insert($new_artikel_page, $new_artikel_publish_date,$new_artikel_headline,$new_artikel_sub_headline,$new_artikel_short_text, $new_artikel_long_text, $new_artikel_author_id,$new_artikel_aktiv,$new_artikel_comments);
         if ($result) {
            echo $lang["artikel_insert_erfolgreich"];
            artikel_browse($page_id, $author_id);
         }
         else {
         	echo $lang["artikel_insert_fehlgeschlagen"];
         }
      }
      else{
      	 artikel_new($new_artikel_page,$new_artikel_publish_date_day,$new_artikel_publish_date_month,$new_artikel_publish_date_year,$new_artikel_headline,$new_artikel_sub_headline,$new_artikel_short_text,$new_artikel_long_text,$new_artikel_author_id, $new_artikel_aktiv,$new_artikel_comments, $error, $errortext);
      }
		
      break;
      
	case "update":
      $error = 0;
      $count =0;
      $errortext = "";
      if (!(isset($edit_artikel_page))){
      	 $errortext .= $lang["artikel_seite_fehlt"]."<br>";
      	 $error = 1;
      }
      if ($edit_artikel_short_text == ""){
      	 $errortext .= $lang["artikel_kurztext_fehlt"];
      	 $error = 1;
      }
      if ($edit_artikel_headline == ""){
      	 $errortext .= $lang["artikel_ueberschrift1_fehlt"]."<br>";
      	 $error = 1;
      }
      if ($edit_artikel_sub_headline == ""){
      	 $errortext .= $lang["artikel_ueberschrift2_fehlt"]."<br>";
      	 $error = 1;
      }            
      if ($edit_artikel_publish_date_day == "" || $edit_artikel_publish_date_month == "" || $edit_artikel_publish_date_year == "" || $edit_artikel_publish_date_hour == "" || $edit_artikel_publish_date_minute == ""){
         $errortext .= $lang["artikel_veroeffentlichungsdatum_fehlt"]."<br>";
         $error = 1;
      }
      else {
      	 $edit_artikel_publish_date = $edit_artikel_publish_date_year . "-" . $edit_artikel_publish_date_month . "-" . $edit_artikel_publish_date_day . "- ".$new_artikel_publish_date_hour. ":".$new_artikel_publish_date_minute.":00";
      }
      if ($error == 0){
         $result = artikel_update($edit_artikel_id, $edit_artikel_page,$edit_artikel_publish_date, $edit_artikel_headline,$edit_artikel_sub_headline,$edit_artikel_short_text,$edit_artikel_author_id,   $edit_artikel_aktiv,$edit_artikel_comments);
         $count = 0;
         if (isset($edit_artikel_long_text)){
            foreach ($edit_artikel_long_text as $value) {
               $count++;
               $result  = artikel_daten_update( $edit_artikel_id, $value, $count);
            }
         }
         if ($new_artikel_long_text <> ""){
            $count++;
            $result  = artikel_daten_insert($edit_artikel_id, $new_artikel_long_text, $count);
         }
         if ($result) {
         	echo $lang["artikel_update_erfolgreich"]."<br>";
         }
         else {
         	echo $lang["artikel_update_fehlgeschlagen"]."<br>";
         }
         artikel_browse($page_id, $author_id);
      }
      else{artikel_edit($edit_artikel_id, $edit_artikel_page,$edit_artikel_publish_date_day,$edit_artikel_publish_date_month,$edit_artikel_publish_date_year,$edit_artikel_headline,$edit_artikel_sub_headline,$edit_artikel_short_text, $edit_artikel_long_text, $new_artikel_long_text, $edit_artikel_author_id,$edit_artikel_aktiv,$edit_artikel_comments, $error, $errortext);}
		
      break;
      
	case "delete":
      artikel_delete_abfrage($delete_id, $delete_name);
           
      break;

	case "delete_doit":
	   if ($delete_it == $lang["artikel_ja"]) {
         $artikel_result = artikel_delete($delete_id);
         if ($artikel_result){ 
         	$daten_result = artikel_daten_delete($delete_id);
         }
         if ($artikel_result) {
         	echo $lang["artikel_delete_erfolgreich"]; 
         }else {
         	echo $lang["artikel_delete_fehlgeschlagen"];
         }
         if ($daten_result) {
         	echo $lang["artikel_daten_delete_erfolgreich"]; 
         }else {
         	echo $lang["artikel_daten_delete_fehlgeschlagen"];
         }
      }
      artikel_browse($page_id, $author_id);
      
      break;
      
   default:
      artikel_browse($page_id, $author_id);
      
      break;
}

function artikel_insert($new_artikel_page,$new_artikel_publish_date,$new_artikel_headline,$new_artikel_sub_headline,$new_artikel_short_text, $new_artikel_long_text, $new_artikel_author_id,$new_artikel_aktiv,$new_artikel_comments)    {
   global $conf, $lang;
   
   $Statement = "INSERT INTO ".$conf["db_namespace"]."artikel set ".
                " artikel_page = '".         joingrouparray($new_artikel_page) ."' , ".
                " artikel_publish_date = '". $new_artikel_publish_date ."' , ".
                " artikel_headline = '".     $new_artikel_headline ."' , ".
                " artikel_sub_headline = '".  $new_artikel_sub_headline . "' , ".
                " artikel_short_text = '".   $new_artikel_short_text ."' , ".
                " artikel_create_date =  NOW() , ".
                " artikel_modify_date =  NOW() , ".
                " artikel_author_id = '".    $conf["author_id"] ."' , ".
                " artikel_aktiv = '" .       $new_artikel_aktiv ."' , ".
                " artikel_comments = '" .    $new_artikel_comments ."'";
 
   $insert1_result = dbquery($Statement);
   if ($insert1_result) {
      $modulid = mysql_insert_id();
      acl_user_set($conf["author_id"], "artikel", $modulid, "Y", "Y", "Y", "Y");
      $Statement = "INSERT INTO ".$conf["db_namespace"]."artikel_daten (".
                   " artikel_long_text ,  ".
                   " artikel_part, ".
                   " artikel_id ".
                   ") VALUES (  ".
                   " '". $new_artikel_long_text ."' , ".
                   " '" .  1 ."', ".
                   " ". $modulid . ")";
      $insert2_result = dbquery($Statement);
   }

   return $insert1_result && $insert2_result;
}

function artikel_update($edit_artikel_id, $edit_artikel_page,$edit_artikel_publish_date,$edit_artikel_headline,$edit_artikel_sub_headline,$edit_artikel_short_text, $edit_artikel_author_id,	$edit_artikel_aktiv,$edit_artikel_comments){
   global $conf, $lang;
   
   $Statement = "UPDATE ".$conf["db_namespace"]."artikel SET ".
                " artikel_page         = '". joingrouparray($edit_artikel_page) ."',".
                " artikel_publish_date = '". $edit_artikel_publish_date ."',".
                " artikel_headline     = '". $edit_artikel_headline ."',".
                " artikel_sub_headline = '". $edit_artikel_sub_headline ."',".
                " artikel_short_text   = '". $edit_artikel_short_text ."',".
                " artikel_modify_date  = NOW(),".
                " artikel_aktiv        = '". $edit_artikel_aktiv ."',".
                " artikel_comments     = '". $edit_artikel_comments ."'".
                " WHERE artikel_id = '". $edit_artikel_id."'";
   $update_result = dbquery($Statement);
   return $update_result;
}
function artikel_daten_update($edit_artikel_id, $edit_artikel_long_text, $edit_artikel_part){
   global $conf, $lang;
   $Statement = "UPDATE ".$conf["db_namespace"]."artikel_daten SET ".
                " artikel_long_text = '". $edit_artikel_long_text ."'".
                " WHERE artikel_id = '". $edit_artikel_id."' ".
                " AND artikel_part = '".$edit_artikel_part . "'";
   $update_result = dbquery($Statement);
   return $update_result;
}

function artikel_daten_insert($edit_artikel_id, $new_artikel_long_text, $part){
   global $conf, $lang;
   
   $Statement = "INSERT INTO ".$conf["db_namespace"]."artikel_daten (".
                " artikel_long_text ,  ".
                " artikel_part, ".
                " artikel_id ".
                ") VALUES (  ".
                " '". $new_artikel_long_text ."' , ".
                " '" .  $part ."', ".
                " '". $edit_artikel_id ."' )";
   $insert_result = dbquery($Statement);
   
   return $insert_result;
}


function artikel_delete_abfrage($delete_id){
   global $conf, $lang;

   $result = dbquery("select artikel_headline from ".$conf["db_namespace"]."artikel where artikel_id = '" . $delete_id . "'");
   if ($result)  {
      $row = mysql_fetch_object($result);
      echo "<h1>" . $lang["artikel_loeschen"] . "</h1>";
      echo "<form action=\"" . $conf["admp"] . "&section=artikel&action=delete_doit&delete_id=" . $delete_id . "\" ENCTYPE=\"multipart/form-data\" method=\"POST\">";
      echo "<table class=\"reda_td\" border = 1 cellpadding = 0 cellspacing = 0>";
      echo "<tr><td>". htmlspecialchars($row->artikel_headline) . "</td></tr>";   
      echo "<tr><td><input type=\"submit\" name=\"delete_it\" value=\"". $lang["artikel_ja"] . "\"> <input type=\"submit\" name=\"delete_it\" value=\"". $lang["artikel_nein"] . "\"></td></tr>";
      echo "</table>";
      echo "</form>";
      mysql_free_result($result);
   }
}

function artikel_delete($delete_id){
   global $conf, $lang;
   
   $delete_result = dbquery("delete from ".$conf["db_namespace"]."artikel where artikel_id = '". $delete_id . "'");
   acl_delete("artikel", $delete_id);   
   return $delete_result;
}

function artikel_daten_delete($delete_id){
   global $conf, $lang;
  
   $delete_result = dbquery("delete from ".$conf["db_namespace"]."artikel_daten where artikel_id = '". $delete_id . "'");
   
   return $delete_result;
}

function artikel_new($new_artikel_page,$new_artikel_publish_date_day,$new_artikel_publish_date_month,$new_artikel_publish_date_year,$new_artikel_headline,$new_artikel_sub_headline,$new_artikel_short_text,$new_artikel_long_text,$new_artikel_author_id,$new_artikel_aktiv,$new_artikel_comments, $error, $errortext){
   global $conf, $lang;
  
   echo "<h1>" . $lang["artikel_neu"]. "</h1>\n";
   if ($error == 1){echo "<p>" . $errortext . "</p>\n";}
   echo "<form name = artikel_new action=\"" . $conf["admp"] . "&action=add&section=artikel\" ENCTYPE=\"multipart/form-data\" method=\"POST\" onsubmit=\"return submitForm();\">\n";    
   echo "<table class=\"reda_td\" border = 1 cellpadding = 0 cellspacing = 0>\n";
   echo "<tr><td colspan=\"3\">" . $lang["artikel_ueberschrift1"]. "</td></tr>\n";
   echo "<tr><td colspan=\"3\"><input  name=\"new_artikel_headline\" size=\"45\" maxlength=\"128\" value = \"" . htmlspecialchars(stripslashes($new_artikel_headline)) ."\"></td></tr>";
   echo "<tr><td colspan=\"3\">" . $lang["artikel_ueberschrift2"]. "</td></tr>";
   echo "<tr><td colspan=\"3\"><input  name=\"new_artikel_sub_headline\" size=\"45\" maxlength=\"255\" value = \"" . htmlspecialchars(stripslashes($new_artikel_sub_headline)) . "\"></td></tr>";
   echo "<tr><td colspan=\"1\" width = 33%>" . $lang["artikel_veroeffentlichungsdatum"] . "</td><td colspan=\"1\" width = 33%>" . $lang["artikel_aktiv"] . "</td><td colspan=\"1\" width = 33%>" . $lang["artikel_seite_zuordnen"] . "</td></tr>\n";
   echo "<tr>";
   echo "<td colspan=\"1\">";
   createdatetimeinput("new_artikel_publish_date", $new_artikel_publish_date, "");
   echo "</td>";
   echo " <td colspan=\"1\">";
   createsel_aktiv("new_artikel_aktiv",$new_artikel_aktiv);  
   echo "</td>";
   echo "<td colspan=\"1\">";
   createsel_pagenCAm("new_artikel_page",$new_artikel_page);
   echo "</td>";
   echo "</tr>\n";
   echo " <tr><td colspan=\"3\">&nbsp;</td></tr>\n";
   echo "<tr><td colspan=\"3\">" . $lang["artikel_kurztext"]."</td></tr>\n";
   echo "<tr><td colspan=\"3\">";
   write_bbc("artikel_new", "new_artikel_short_text");
   echo "<textarea name=\"new_artikel_short_text\" wrap=virtual rows=15 cols=75>" . htmlspecialchars($new_artikel_short_text) . "</textarea></td></tr>\n";
   echo "</td></tr>\n";
   echo "<tr><td colspan=\"3\">" . $lang["artikel_langtext"] . "</td></tr>\n";
   echo "<tr><td colspan=\"3\">";
   write_bbc("artikel_new", "new_artikel_long_text");
   echo "<textarea name=\"new_artikel_long_text\" wrap=virtual rows=15 cols=75>" . htmlspecialchars($new_artikel_long_text) . "</textarea></td></tr>\n";
   echo "</td></tr>\n";
   echo "<tr><td colspan=\"3\" align=\"right\"><input type=\"submit\" name=\"add\" value=\"" . $lang["artikel_anlegen"] . "\"></td></tr>\n";
   echo "</table>\n";
   echo "</form>\n";
}

function artikel_edit($edit_artikel_id, $edit_artikel_page,$edit_artikel_publish_date_day,$edit_artikel_publish_date_month,$edit_artikel_publish_date_year,$edit_artikel_headline,$edit_artikel_sub_headline,$edit_artikel_short_text,$edit_artikel_long_text,$new_artikel_long_text, $edit_artikel_author_id,$edit_artikel_aktiv,$edit_artikel_comments, $error, $errortext){
   global $conf, $lang;
   
   if ($error == "0"){
      $result = dbquery("select * from ".$conf["db_namespace"]."artikel where artikel_id = '" . $edit_artikel_id . "'");
      if ($result)  {
         $row = mysql_fetch_object($result);
         $edit_artikel_id           = $row->artikel_id;
         $edit_artikel_page         = $row->artikel_page;
         $edit_artikel_publish_date = $row->artikel_publish_date;
         $edit_artikel_headline     = $row->artikel_headline;
         $edit_artikel_sub_headline = $row->artikel_sub_headline;
         $edit_artikel_short_text   = $row->artikel_short_text;
         $edit_artikel_author_id    = $row->artikel_author_id;
         $edit_artikel_aktiv        = $row->artikel_aktiv;
         $edit_artikel_comments     = $row->artikel_comments;
         mysql_free_result($result);
         $dataresult = dbquery("select * from ".$conf["db_namespace"]."artikel_daten where artikel_id='". $edit_artikel_id . "' order by artikel_part");
         if ($dataresult)    {
            $edit_artikel_long_text      = array();         
            while ($datarow = mysql_fetch_object($dataresult))  {
               array_push($edit_artikel_long_text, $datarow->artikel_long_text);
            }
            mysql_free_result($dataresult);
         }
     } 
   }
   echo "<h1>" . $lang["artikel_bearbeiten"] . "</h1>\n";
   if ($error == 1){ 
   	  echo "<p>" . $errortext . "</p>\n";
   }
   echo "<form name = artikel_edit action=\"" . $conf["admp"] . "&section=artikel&action=update\"  ENCTYPE=\"multipart/form-data\" method=\"POST\" onsubmit=\"return submitForm();\">\n";     
   echo "<input type=hidden name=edit_artikel_id value=" . $edit_artikel_id . ">".
        "<table class=\"reda_td\" border = 1 cellpadding = 0 cellspacing = 0>\n".
        "<tr>".
        "<td colspan=\"3\">" . $lang["artikel_ueberschrift1"] . "</td>".
        "</tr>\n".
        "<tr>".
        "<td colspan=\"3\"><input  name=\"edit_artikel_headline\" size=\"45\" maxlength=\"128\" value = \"" . htmlspecialchars(stripslashes($edit_artikel_headline)) . "\"></td>".
        "</tr>\n".
        "<tr>".
        "<td colspan=\"3\">" . $lang["artikel_ueberschrift2"] . "</td>".
        "</tr>\n".
        "<tr>".
        "<td colspan=\"3\"><input  name=\"edit_artikel_sub_headline\" size=\"45\" maxlength=\"255\" value = \"" . htmlspecialchars(stripslashes($edit_artikel_sub_headline)) . "\"></td>".
        "</tr>\n".
        "<tr>".
        "<td>" . $lang["artikel_veroeffentlichungsdatum"] . "</td><td>" . $lang["artikel_aktiv"]. "</td><td>" . $lang["artikel_seite"] . "</td>".
        "</tr>\n".
        "<tr>".
        "<td colspan=\"1\">";
   createdatetimeinput("edit_artikel_publish_date", $edit_artikel_publish_date, "");
   echo "</td>".
        "<td>";
   createsel_aktiv("edit_artikel_aktiv",$edit_artikel_aktiv);   
   echo "</td>".
        "<td>";
   createsel_pagenCAm("edit_artikel_page",$edit_artikel_page);
   echo "</td>".
        "</tr>\n".
        "<tr><td colspan=\"3\">&nbsp;</td></tr>\n".
        "<tr><td colspan=\"3\">" . $lang["artikel_kurztext"] . "</td></tr>\n".
        "<tr><td colspan=\"3\">\n";
   write_bbc("artikel_edit", "edit_artikel_short_text");
   echo "<textarea name=\"edit_artikel_short_text\" wrap=virtual rows=15 cols=75>" . htmlspecialchars($edit_artikel_short_text) . "</textarea></td></tr>\n";
   echo "</td></tr>";
   $seite=0;     
   foreach ($edit_artikel_long_text as $long_text)  {
      $seite++;
      echo "<tr><td colspan=\"3\">" . $lang["artikel_seite"] . " " . $seite . "</td></tr>\n".
           "<tr><td colspan=\"3\">\n";
      write_bbc("artikel_edit", "edit_artikel_long_text[".$seite."]");
      echo "<textarea name=\"edit_artikel_long_text[".$seite."]\" wrap=virtual rows=15 cols=75>" . htmlspecialchars($long_text) . "</textarea></td></tr>\n";
      echo "</td></tr>\n";
   }
   echo "<tr><td colspan=\"3\">" . $lang["artikel_neue_seite"] . "</td></tr>\n".
        "<tr><td colspan=\"3\">\n";
   write_bbc("artikel_edit", "new_artikel_long_text");
   echo "<textarea name=\"new_artikel_long_text\" wrap=virtual rows=15 cols=75>" . htmlspecialchars($new_artikel_short_text) . "</textarea></td></tr>\n";
   echo "</td></tr>\n".
        "<tr><td colspan=\"3\" align=\"right\"><input type=\"submit\" name=\"todo\" value=\"" . $lang["artikel_speichern"] . "\"></td></tr>\n".
        "</table>\n".
        "</form>\n";
}
function artikel_browse($page_id, $author_id){
	global $conf,$lang;

    if (isset($_SESSION['artikel_edit_page_id'])){$page_id= $_SESSION['artikel_edit_page_id'];}
    if ($author_id=="" || !isset($author_id)) {$author_id = $conf["author_id"];}

	echo "\n<h1>" . $lang["artikel_verwaltung"] . "</h1>\n";
	if (checkgroupcreate($conf["author_groups"], "artikel") == 1){ echo "<a href=\"" . $conf["admp"] . "&action=new&section=artikel\">" . $lang["artikel_anlegen"] ."</a>\n";}
	echo "<form action=\"" . $conf["admp"] . "&section=artikel\" method=\"post\">\n";
    echo "<table class=\"reda_td\" border = 1 cellpadding = 0 cellspacing = 0>\n";
    echo "<tr><td>" . $lang["artikel_der_seite"] ."</td><td>";
    createsel_pagenCAs("page_id", $page_id); 
    echo "</td><td><input type=\"submit\" value=\"" . $lang["artikel_anzeigen"] . "\"></td></tr>\n";
	echo "<tr><td>" . $lang["artikel_des_autors"] . "</td><td colspan = \"2\">";
	createsel_author("author_id", $author_id); 
	echo "</td></tr>\n";
    echo "</table>\n";
    echo "</form>\n";
    echo "<table  class=\"reda_td\" border = 1 cellpadding = 0 cellspacing = 0>\n";
    if ($page_id <> ""){
	  echo "<tr><td>".$lang["artikel_id"] . "</td><td>".$lang["artikel_ueberschrift1"] . "</td><td>".$lang["artikel_veroeffentlichungsdatum"] . "</td><td>".$lang["artikel_seite"] . "</td><td>".$lang["artikel_autor"] . "</td><td>".$lang["artikel_counter"] . "</td><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td></tr>\n";
	  $Statement = "select * from ".$conf["db_namespace"]."artikel where artikel_page like '%:" . $page_id . ":%'";
	  if ($author_id <> ""){ $Statement .= " and artikel_author_id = '" . $author_id . "'";}
	  $Statement .= " order by artikel_publish_date DESC";
	  $result = dbquery($Statement);
	  if ( mysql_num_rows($result) > 0 ){
         while ($row = mysql_fetch_object($result)){
      	    echo "<td>". $row->artikel_id . "</td>";
            echo "<td><a href=\"" . $conf["indexname"] . "artikel/".$row->artikel_id."\" target=\"new_window\">".$row->artikel_headline."</a></td>";
 		    echo "<td>". mydate2datetime($row->artikel_publish_date) ."</td>";
		    echo "<td>". getpagenamebyidarray($row->artikel_page)."</td>";
            echo "<td>". getauthorbyid($row->artikel_author_id) ."</td>";
            echo "<td>". $row->artikel_counter."</td>";
		    echo "<td>";
		    if (acl_check("edit", $conf["author_groups"], $conf["author_id"], "artikel", $row->artikel_id) == 1) {
		       echo "<a href=\"" . $conf["admp"] . "&action=edit&section=artikel&edit_artikel_id=" . $row->artikel_id . "&page_id=".$page_id."\"><img src=\"" . $conf["images_admin"] . "icon_edit.png\" width=\"25\" height=\"25\" alt = \"".$lang["artikel_bearbeiten_kurz"] . "\"></a>";
		    } else {
	           echo "&nbsp;";
	        }
		    echo "</td>";
		    echo "<td>";
            if (acl_check("delete", $conf["author_groups"], $conf["author_id"], "artikel", $row->artikel_id) == 1) {
		       echo "<a href=\"" . $conf["admp"] . "&action=delete&section=artikel&delete_id=" . $row->artikel_id . "\"><img src=\"" . $conf["images_admin"] . "icon_delete.png\" width=\"25\" height=\"25\" alt = \"".$lang["artikel_loeschen_kurz"] . "\"></a>";
		    } else {
		      echo "&nbsp;";
		    } 
		    echo "</td>";
		    echo "<td>";
            if (acl_check("rights", $conf["author_groups"], $conf["author_id"], "artikel", $row->artikel_id) == 1) {
		       echo "<a href=" . $conf["admp"] . "&section=rights&modul_name=artikel&modul_id=" . $row->artikel_id . "\"><img src=\"" . $conf["images_admin"] . "icon_rights.png\" width=\"25\" height=\"25\" alt = \"".$lang["artikel_loeschen_kurz"] . "\"></a>";
		    }else{
		       echo "&nbsp;";
		    } 
		    echo "</td>";
		    
		    echo "</tr>\n";
		 }
		 mysql_free_result($result);
	  }
  }
  echo "</table>\n";
}
function createsel_aktiv($select_name,$grouplist)
{
   global $conf, $lang;
   echo "<select name=\"" . $select_name . "\">\n";
   echo "<option";
   if ($grouplist == "J"){echo " selected";};
   echo " value=\"J\">Ja</option>";
   echo "<option";
   if ($grouplist == "N"){echo " selected";};
   echo " value=\"N\">Nein</option>\n";
   echo "</select>\n";
   return;
}
function createsel_pagenCAm($select_name,$grouplist)
{
   global $conf, $lang;
   $allgroups = dbquery("select page_id, page_name from ".$conf["db_namespace"]."pages Where page_childs = 'A' order by page_name");
   echo "<select multiple size = \"8\" name=\"" . $select_name . "[]\">\n";
   if ( mysql_num_rows($allgroups) > 0 ){
      while ( $g_row = mysql_fetch_object($allgroups) ){
         echo "<option value=" . $g_row->page_id;
         if (!is_array($grouplist)){$grouplist = explodegroup($grouplist);}
         foreach ($grouplist as $value){
            if ( eregi ( $g_row->page_id, $value ) ){echo " selected ";}
         }
         if (acl_check("insert", $conf["author_groups"], $conf["author_id"], "page", $g_row->page_id) == 1) {
            echo ">";
         } else {
         	echo " disabled style = \"color:gray;font-style:italic;\" >";
         }	
         echo $g_row->page_name . "</option>\n";
      }
      mysql_free_result($allgroups);
   }
   echo "</select>\n";
   return;
}
function createsel_pagenCAs($select_name,$grouplist){
   global $conf, $lang;
   $allgroups = dbquery("select page_id, page_name from ".$conf["db_namespace"]."pages Where page_childs = 'A' order by page_name");
   echo "<select name=" . $select_name . ">\n";
   if ( mysql_num_rows($allgroups) > 0 )      {
      while ( $g_row = mysql_fetch_object($allgroups) )         {
         echo "<option value=" . $g_row->page_id;
         if ( eregi ( $g_row->page_id, $grouplist ) ){            echo " selected ";}
         echo ">" . $g_row->page_name . "</option>\n";
      }
      mysql_free_result($allgroups);
   }
   echo "</select>\n";
   return;
}
?>