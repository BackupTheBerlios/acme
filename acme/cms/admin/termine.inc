<?php
include($conf["admbase"] . "/lang/termine." . $conf["lang"] . ".inc");

switch($action){
   case "termin_edit":
      termin_edit($edit_id, $edit_termin_parent_id, $edit_termin_name, $edit_termin_tpl, $edit_termin_img_small,$edit_termin_img_small_inactive,  $edit_termin_img_big, $edit_termin_top_bar, $edit_termin_left_bar, $edit_termin_right_bar, $edit_termin_foo_bar, $edit_termin_titel, $edit_termin_text, $edit_termin_groups);
      break;
   case "termin_update":
      termin_update($edit_termin_id, $edit_termin_parent_id, $edit_termin_name, $edit_termin_tpl, $edit_termin_img_small,$edit_termin_img_small_inactive,  $edit_termin_img_big, $edit_termin_top_bar, $edit_termin_left_bar, $edit_termin_right_bar, $edit_termin_foo_bar, $edit_termin_titel, $edit_termin_text, $edit_termin_groups);
	  termin_browse();
      break;
   case "termin_new":
      termin_new($new_termin_parent_id, $new_termin_name, $new_termin_tpl, $new_termin_img_small,$new_termin_img_small_inactive,  $new_termin_img_big, $new_termin_top_bar, $new_termin_left_bar, $new_termin_right_bar, $new_termin_foo_bar, $new_termin_titel, $new_termin_text, $new_termin_groups);
      break;
   case "termin_insert":
      termin_insert($new_termin_parent_id, $new_termin_name, $new_termin_tpl, $new_termin_img_small, $new_termin_img_small_inactive, $new_termin_img_big, $new_termin_top_bar, $new_termin_left_bar, $new_termin_right_bar, $new_termin_foo_bar, $new_termin_titel, $new_termin_text, $new_termin_groups);
	  termin_browse();
      break;
   case "termin_delete":
      termin_delete($delete_id);
      termin_browse();
      break;
   case "termin_data_edit":
      termin_data_edit($edit_id);
      break;
   case "termin_data_update":
      $edit_termin_data_date_von = $edit_termin_data_date_von_year . "-" . 
    	                           $edit_termin_data_date_von_month . "-" . 
    	                           $edit_termin_data_date_von_day . " ".
    	                           $edit_termin_data_date_von_time_hour . ":".
    	                           $edit_termin_data_date_von_time_minute . ":00";
      $edit_termin_data_date_bis = $edit_termin_data_date_bis_year . "-" . 
    	                           $edit_termin_data_date_bis_month . "-" . 
    	                           $edit_termin_data_date_bis_day  . " ".
    	                           $edit_termin_data_date_bis_time_hour . ":".
    	                           $edit_termin_data_date_bis_time_minute . ":00";
      termin_data_update($edit_termin_data_id, $edit_termin_typ, $edit_termin_data_headline,$edit_termin_data_date_von, $edit_termin_data_date_bis, $edit_termin_data_Veranstalter, $edit_termin_data_Ort, $edit_termin_data_URL, $edit_termin_data_content);
      termin_browse();
      break;
   case "termin_data_new":
      termin_data_new($new_termin_typ, $new_termin_data_headline, $new_termin_data_date_von, $new_termin_data_date_bis, $new_termin_data_Veranstalter, $new_termin_data_Ort, $new_termin_data_URL, $new_termin_data_content);
      break;
   case "termin_data_insert":
      $new_termin_data_date_von = $new_termin_data_date_von_year . "-" .
    	                          $new_termin_data_date_von_month . "-" . 
    	                          $new_termin_data_date_von_day . " ".
    	                          $new_termin_data_date_von_time_hour . ":".
    	                          $new_termin_data_date_von_time_minute . ":00";
      $new_termin_data_date_bis = $new_termin_data_date_bis_year . "-" .
    	                          $new_termin_data_date_bis_month . "-" . 
    	                          $new_termin_data_date_bis_day . " ".
    	                          $new_termin_data_date_bis_time_hour . ":".
    	                          $new_termin_data_date_bis_time_minute . ":00";
      if (count($new_termin_typ) == 0){    	                            
         echo "typ fehlt";
         termin_data_new($new_termin_typ, $new_termin_data_headline, $new_termin_data_date_von, $new_termin_data_date_bis, $new_termin_data_Veranstalter, $new_termin_data_Ort, $new_termin_data_URL, $new_termin_data_content);
      }
      else {   
         termin_data_insert($termin_id, $new_termin_typ, $new_termin_data_headline, $new_termin_data_date_von, $new_termin_data_date_bis, $new_termin_data_Veranstalter, $new_termin_data_Ort, $new_termin_data_URL, $new_termin_data_content);
         termin_browse();
      }
      break;
   case "termin_data_delete":
      termin_data_delete($delete_id);
      termin_browse();
      break;
   default:
      termin_browse();
      break;
}

function termin_data_edit($termin_data_id){
   global $conf, $lang;

   $result = dbquery("select * from acme_termin_data where termin_data_id=$termin_data_id");
       if ($result)  {
          $acme_termin_data = mysql_fetch_object($result);
          echo "<h1>".$lang["termin_eintrag_bearbeiten"]."</h1>".
               "<form action=\"" . $conf["admp"] . "&section=termine&action=termin_data_update&edit_termin_data_id=" . $acme_termin_data->termin_data_id . "\"  method=POST>".
               "<table class=\"reda_td\">".          
               "<tr><td>".$lang["termin_eintrag_titel"]."</td></tr>".
               "<tr><td><input name=edit_termin_data_headline size=70 maxlength=128 value=\"" . htmlspecialchars($acme_termin_data->termin_data_headline) . "\"></td></tr>".
               "<tr><td>".$lang["termin_eintrag_von"].
               "<input  name=\"edit_termin_data_date_von_day\" size=\"2\" maxlength=\"2\"  value=\"" .  substr ($acme_termin_data->termin_data_date_von, 8,2) . "\">.".
               "<input  name=\"edit_termin_data_date_von_month\" size=\"2\" maxlength=\"2\" value=\"" . substr ($acme_termin_data->termin_data_date_von, 5,2) . "\">.".
               "<input  name=\"edit_termin_data_date_von_year\" size=\"4\" maxlength=\"4\" value=\"" . substr ($acme_termin_data->termin_data_date_von, 0,4) . "\">".
  	           "<input  name=\"edit_termin_data_date_von_time_hour\" size=\"2\" maxlength=\"2\" value=\"" . substr ($acme_termin_data->termin_data_date_bis, 11,2) . "\">:".
  	           "<input  name=\"edit_termin_data_date_von_time_minute\" size=\"2\" maxlength=\"2\" value=\"" . substr ($acme_termin_data->termin_data_date_bis, 14,2) . "\">".
               "</td></tr>".
               "<tr><td>".$lang["termin_eintrag_bis"].
               "<input  name=\"edit_termin_data_date_bis_day\" size=\"2\" maxlength=\"2\"  value=\"" .  substr ($acme_termin_data->termin_data_date_bis, 8,2) . "\">.".
               "<input  name=\"edit_termin_data_date_bis_month\" size=\"2\" maxlength=\"2\" value=\"" . substr ($acme_termin_data->termin_data_date_bis, 5,2) . "\">.".
               "<input  name=\"edit_termin_data_date_bis_year\" size=\"4\" maxlength=\"4\" value=\"" . substr ($acme_termin_data->termin_data_date_bis, 0,4) . "\">".
  	            "<input  name=\"edit_termin_data_date_bis_time_hour\" size=\"2\" maxlength=\"2\" value=\"" . substr ($acme_termin_data->termin_data_date_bis, 11,2) . "\">:".
               "<input  name=\"edit_termin_data_date_bis_time_minute\" size=\"2\" maxlength=\"2\" value=\"" . substr ($acme_termin_data->termin_data_date_bis, 14,2) . "\">".
               "</td></tr>";
          echo "<tr><td>";
          createsel_termin("edit_termin_typ", $acme_termin_data->termin_typ);
          echo "</td></tr>".                 
               "<tr><td>".$lang["termin_eintrag_veranstalter"]."</td></tr>".
               "<tr><td><input name=edit_termin_data_Veranstalter size=70 maxlength=128 value=\"" . htmlspecialchars($acme_termin_data->termin_data_Veranstalter) . "\"></td></tr>".
               "<tr><td>".$lang["termin_eintrag_ort"]."</td></tr>".
               "<tr><td><input name=edit_termin_data_Ort size=70 maxlength=128 value=\"" . htmlspecialchars($acme_termin_data->termin_data_Ort) . "\"></td></tr>".
               "<tr><td>".$lang["termin_eintrag_url"]."</td></tr>".
               "<tr><td><input name=edit_termin_data_URL size=70 maxlength=128 value=\"" . htmlspecialchars($acme_termin_data->termin_data_URL) . "\"></td></tr>".
               "<tr><td>".$lang["termin_eintrag_beschreibung"]."</td></tr>".
               "<tr><td><textarea name=\"edit_termin_data_content\" wrap=virtual rows=15 cols=75>" . htmlspecialchars($acme_termin_data->termin_data_content) . "</textarea></td>".
               "<tr><td><input type=submit name=add value=".$lang["termin_eintrag_speichern"]."></td></tr>".
               "</table>".
               "</form>";
          mysql_free_result($result);
          }

}
function termin_data_update($termin_data_id, $termin_typ, $termin_data_headline, $termin_data_date_von, $termin_data_date_bis, $termin_data_Veranstalter, $termin_data_Ort, $termin_data_URL, $termin_data_content){
   global $conf, $lang;
   
   $Statement = "UPDATE acme_termin_data SET ".
                "termin_data_headline = '". $termin_data_headline . "', ".
                "termin_data_date_von = '". $termin_data_date_von . "', ".
                "termin_data_date_bis = '". $termin_data_date_bis . "', ".
                "termin_data_Veranstalter = '". $termin_data_Veranstalter . "', ".
                "termin_data_Ort = '". $termin_data_Ort . "', ".
                "termin_data_URL = '". $termin_data_URL . "', ".
                "termin_data_content   = '". $termin_data_content . "', ".
                "termin_data_author_id = '" . $conf["author_id"] . "', ".
                "termin_typ  = '". joingrouparray($termin_typ) . "' ".
                "WHERE termin_data_id = '". $termin_data_id . "'";
   $update_result = dbquery($Statement);
   if($update_result){echo $lang["termin_eintrag_update_erfolgreich"];}
   else{echo $lang["termin_eintrag_update_fehlgeschlagen"];};
}

function termin_data_new($new_termin_typ, $new_termin_data_headline, $new_termin_data_date_von, $new_termin_data_date_bis, $new_termin_data_Veranstalter, $new_termin_data_Ort, $new_termin_data_URL, $new_termin_data_content){

   global $conf, $lang;

   echo "<h1>".$lang["termin_eintrag_anlegen"]."</h1>".
        "<form action=\"" .  $conf["admp"] . "&section=termine&action=termin_data_insert\"  method=POST>".
        "<table class=\"reda_td\">".
        "<tr><td>".$lang["termin_eintrag_titel"]."<input type=\"hidden\" name=\"termin_id\" value=\"" . $termin_id . "\"></td></tr>".
        "<tr><td><input name=new_termin_data_headline size=70 maxlength=128 value=\"" . htmlspecialchars(stripslashes($new_termin_data_headline)) . "\"></td></tr>".
        "<tr><td>".$lang["termin_eintrag_von"].
        "<input  name=\"new_termin_data_date_von_day\" size=\"2\" maxlength=\"2\"  value=\"" .  substr (date("Ymd"), 6,2) . "\">.".
        "<input  name=\"new_termin_data_date_von_month\" size=\"2\" maxlength=\"2\" value=\"" . substr (date("Ymd"), 4,2) . "\">.".
        "<input  name=\"new_termin_data_date_von_year\" size=\"4\" maxlength=\"4\" value=\"" . substr (date("Ymd"), 0,4) . "\">".
        "<input  name=\"new_termin_data_date_von_time_hour\" size=\"2\" maxlength=\"2\" value=\"00\">:".
        "<input  name=\"new_termin_data_date_von_time_minute\" size=\"2\" maxlength=\"2\" value=\"00\">".  	
        "</td></tr>".
        "<tr><td>".$lang["termin_eintrag_bis"].
        "<input  name=\"new_termin_data_date_bis_day\" size=\"2\" maxlength=\"2\"  value=\"" .  substr (date("Ymd"), 6,2) . "\">.".
        "<input  name=\"new_termin_data_date_bis_month\" size=\"2\" maxlength=\"2\" value=\"" . substr (date("Ymd"), 4,2) . "\">.".
        "<input  name=\"new_termin_data_date_bis_year\" size=\"4\" maxlength=\"4\" value=\"" . substr (date("Ymd"), 0,4) . "\">".
        "<input  name=\"new_termin_data_date_bis_time_hour\" size=\"2\" maxlength=\"2\" value=\"23\">:".
        "<input  name=\"new_termin_data_date_bis_time_minute\" size=\"2\" maxlength=\"2\" value=\"59\">".  	
        "</td></tr>";
   echo "<tr><td>";
   createsel_termin("new_termin_typ", $new_termin_typ);
   echo "</td></tr>".           
        "<tr><td>".$lang["termin_eintrag_veranstalter"]."</td></tr>".
        "<tr><td><input name=new_termin_data_Veranstalter size=70 maxlength=128 value=\"" . htmlspecialchars(stripslashes($new_termin_data_Veranstalter)) . "\"></td></tr>".
        "<tr><td>".$lang["termin_eintrag_ort"]."</td></tr>".
        "<tr><td><input name=new_termin_data_Ort size=70 maxlength=128 value=\"" . htmlspecialchars(stripslashes($new_termin_data_Ort)) . "\"></td></tr>".
        "<tr><td>".$lang["termin_eintrag_url"]."</td></tr>".
        "<tr><td><input name=new_termin_data_URL size=70 maxlength=128 value=\"" . htmlspecialchars(stripslashes($new_termin_data_URL)) . "\"></td></tr>".
        "<tr><td>".$lang["termin_eintrag_beschreibung"]."</td></tr>".
        "<tr><td><textarea name=\"new_termin_data_content\" wrap=virtual rows=15 cols=75>" . htmlspecialchars(stripslashes($new_termin_data_content)) . "</textarea></td>".
        "<tr><td><input type=submit name=add value=".$lang["termin_eintrag_speichern"]."></td></tr>".
        "</table>".
        "</form>";
}
function termin_data_insert($termin_id, $termin_typ, $termin_data_headline, $termin_data_date_von, $termin_data_date_bis, $termin_data_Veranstalter, $termin_data_Ort, $termin_data_URL, $termin_data_content){
   global $conf, $lang;
   
   $Statement = "INSERT INTO acme_termin_data  SET ".
                     "termin_data_headline = '". $termin_data_headline . "',".
                     "termin_data_date_von = '". $termin_data_date_von . "',".
                     "termin_data_date_bis = '". $termin_data_date_bis . "',".
                     "termin_data_Veranstalter = '". $termin_data_Veranstalter . "',".
                     "termin_data_Ort = '". $termin_data_Ort . "',".
                     "termin_data_URL = '". $termin_data_URL . "',".
                     "termin_data_content   = '". $termin_data_content . "',".
                     "termin_typ  = '". joingrouparray($termin_typ) . "', ".
                     "termin_data_author_id = '" . $conf["author_id"] . "'";
   $insert_result = dbquery($Statement);
   if($insert_result){echo $lang["termin_eintrag_insert_erfolgreich"];}
   else{echo $lang["termin_eintrag_insert_fehlgeschlagen"];};
}

function termin_data_delete($delete_id) {
   global $conf, $lang;
   
   $delete_result = dbquery("delete from acme_termin_data where termin_data_id = '". $delete_id . "'");
   if($delete_result){echo $lang["termin_eintrag_delete_erfolgreich"];}
   else{echo $lang["termin_eintrag_delete_fehlgeschlagen"];};
}
function termin_browse() {
   global $conf, $lang;

   echo "<h1>".$lang["termin_verwaltung"]."</h1>";
   if (acl_check("insert", $conf["author_groups"], $conf["author_id"], "termine", 0) == 1) {
      echo "<a href=\"" . $conf["admp"] . "&section=termine&action=termin_new\">".$lang["termin_anlegen"]."</a><br>\n";
   }
   if (acl_check("insert", $conf["author_groups"], $conf["author_id"], "termine", 0) == 1) {
        echo "<a href=\"" . $conf["admp"] . "&section=termine&action=termin_data_new\">".$lang["termin_eintrag_anlegen"]."</a><br>\n";         
   }
   echo "<table class=\"reda_td\">";
   echo "<tr><td>".$lang["termin_termine"]."</td><td width=\"30\"> </td><td width=\"30\"> </td><td width=\"30\"> </td></tr>";
   writeterminchilds($parent,$h_level);
   echo "</table>";
}

function termin_edit($edit_id) {
   global $conf, $lang;
   
   $termin_result = dbquery("select * from acme_termin where termin_id=$edit_id");
   if ($termin_result) {
      $acme_termin = mysql_fetch_object($termin_result);
      echo "<h1>".$lang["termin_bearbeiten"]."</h1>\n";
      echo "<form action=\"" . $conf["admp"] . "&section=termine&action=termin_update&edit_termin_id=" . $acme_termin->termin_id . "\" method=\"POST\">\n";
      echo "<table class=\"reda_td\">\n";
      echo "<tr colspan = \"4\"><td>".$lang["termin_name"]."</td></tr>";
      echo "<tr>";
      echo "<td colspan = \"4\"><input name=\"edit_termin_name\" size=\"30\" maxlength=\"128\" value=\"" . $acme_termin->termin_name . "\"></td>";
      echo "</tr>";      
      echo "<tr><td>".$lang["termin_parent"]."</td><td>".$lang["termin_tpl"]."</td><td>".$lang["termin_logo_gross"]."</td><td>".$lang["termin_logo_klein"]."</td></tr>";
      echo "<td>";
      createsel_terminparent("edit_termin_parent_id",$row->termin_parent_id);
      echo "</td>";    
      echo "<td>";
      createsel_tpl("edit_termin_tpl",  $acme_termin->termin_tpl);
      echo "</td>";
      echo "<td>";
      createsel_img("edit_termin_img_big",  $acme_termin->termin_img_big);
      echo "</td>";
      echo "<td>";
      createsel_img("edit_termin_img_small",  $acme_termin->termin_img_small);
      echo "</td>";
      echo "<td>";
      createsel_img("edit_termin_img_small_inactive",  $acme_termin->termin_img_small_inactive);
      echo "</td>";      
      echo "</tr>\n";
      echo "<tr><td>".$lang["termin_bar_left"]."</td><td>".$lang["termin_bar_right"]."</td><td>".$lang["termin_bar_top"]."</td><td>".$lang["termin_bar_bottom"]."</td></tr>";
      echo "<tr>";
      echo "<td>";
      createsel_bar("edit_termin_left_bar", $acme_termin->termin_left_bar);
      echo "</td>";
      echo "<td>";
      createsel_bar("edit_termin_right_bar",  $acme_termin->termin_right_bar);
      echo "</td>";
      echo "<td>";
      createsel_bar("edit_termin_top_bar",  $acme_termin->termin_top_bar);
      echo "</td>";
      echo "<td>";
      createsel_bar("edit_termin_foo_bar",  $acme_termin->termin_foo_bar);
      echo "</td>";
      echo "</tr>\n";
      echo "<tr colspan = \"4\"><td>".$lang["termin_titel"]."</td></tr>\n";         
      echo "<tr><td colspan = \"4\"><input name=\"edit_termin_titel\" size=\"30\" maxlength=\"200\" value=\"" . htmlspecialchars($acme_termin->termin_titel) . "\"></td>";
      echo "<tr><td colspan = \"4\">".$lang["termin_beschreibung"]."</td></tr>\n";               
      echo "<tr><td colspan = \"2\"><textarea name=\"edit_termin_text\" wrap=virtual rows=15 cols=75>" . htmlspecialchars($acme_termin->termin_text) . "</textarea></td></tr>\n";
     echo "<tr><td colspan=\"4\"><input type=submit name=add value=".$lang["termin_speichern"]."></td></tr>\n";
     echo "</table>\n";
     echo "</form>\n";
     mysql_free_result($termin_result);
   }
}   

function termin_update($termin_id, $termin_parent_id, $termin_name, $termin_tpl, $termin_img_small,$termin_img_small_inactive,  $termin_img_big, $termin_top_bar, $termin_left_bar, $termin_right_bar, $termin_foo_bar, $termin_titel, $termin_text, $termin_groups){
   global $conf, $lang;
   
   $Statement = "UPDATE acme_termin SET ".
                           " termin_name = '" . $termin_name . "', ".
                           " termin_tpl = '" . $termin_tpl . "', ".
                           " termin_parent_id = '" . $termin_parent_id . "', ".                           
                           " termin_img_small = '" . $termin_img_small . "', ".
                           " termin_img_small_inactive = '" . $termin_img_small_inactive . "', ".
                           " termin_img_big = '" . $termin_img_big. "', ".
                           " termin_top_bar = '" . $termin_top_bar. "', ".
                           " termin_left_bar = '" . $termin_left_bar . "', ".
                           " termin_right_bar = '" . $termin_right_bar . "', ".
                           " termin_foo_bar = '" . $termin_foo_bar . "', ".                                                                                                                                                                  
                           " termin_titel = '". $termin_titel . "', ".
                           " termin_text = '" . $termin_text . "', ".
                           " termin_modify_date = NOW(), ".
                           " termin_author_id = '" . $conf["author_id"] . "' ".
                           " WHERE termin_id = '". $termin_id . "'";
   $update_result = dbquery($Statement);
   if($update_result){echo $lang["termin_update_erfolgreich"];}
   else{echo $lang["termin_update_fehlgeschlagen"];};
}

function termin_new($new_termin_parent_id, $new_termin_name, $new_termin_tpl, $new_termin_img_small,$new_termin_img_small_inactive,  $new_termin_img_big, $new_termin_top_bar, $new_termin_left_bar, $new_termin_right_bar, $new_termin_foo_bar, $new_termin_titel, $new_termin_text, $new_termin_groups) {
   global $conf, $lang;
   
   echo "<h1>".$lang["termin_anlegen"]."</h1>";
   echo "<form action=\"" . $conf["admp"] . "&section=termine&action=termin_insert\" method=\"POST\">";
   echo "<table class=\"reda_td\">";
   echo "<tr colspan = \"3\"><td>".$lang["termin_name"]."</td><td>".$lang["termin_parent"]."</td></tr>";
   echo "<tr>";
   echo "<td colspan = \"3\"><input name=\"new_termin_name\" size=\"30\" maxlength=\"128\" value=\"" . htmlspecialchars(stripslashes($new_termin_name)) . "\"></td>";
   echo "<td>";
   createsel_terminparent("new_termin_parent_id", $new_termin_parent_id);
   echo "</td>";    
   echo "</tr>";
   echo "<tr><td>".$lang["termin_tpl"]."</td><td>".$lang["termin_logo_gross"]."</td><td>".$lang["termin_logo_klein"]."</td><td>".$lang["termin_logo_klein_inactive"]."</td></tr>";
   echo "<tr>";
   echo "<td>";
   createsel_tpl("new_termin_tpl",  $new_termin_tpl);
   echo "</td>";
   echo "<td colspan=1>";
   createsel_img("new_termin_img_big",  $new_img_big);
   echo "</td>";
   echo "<td colspan=1>";
   createsel_img("new_termin_img_small",  $new_img_small);
   echo "</td>";
   echo "<td colspan=1>";
   createsel_img("new_termin_img_small_inactive",  $new_img_small_inactive);
   echo "</td>";
   echo "</tr>";
   echo "<tr><td>".$lang["termin_bar_left"]."</td><td>".$lang["termin_bar_right"]."</td><td>".$lang["termin_bar_top"]."</td><td>".$lang["termin_bar_bottom"]."</td></tr>";
   echo "<tr>";
   echo "<td>";
   createsel_bar("new_termin_left_bar", $new_termin_left_bar);
   echo "</td>";
   echo "<td>";
   createsel_bar("new_termin_right_bar",  $new_termin_right_bar);
   echo "<td>";
   echo "<td>";
   createsel_bar("new_termin_top_bar",  $new_termin_top_bar);
   echo "</td>";
   echo "<td>";
   createsel_bar("new_termin_foo_bar",  $new_termin_foo_bar);
   echo "</td>";
   echo "</tr>";
   echo "<tr><td colspan = \"4\">".$lang["termin_titel"]."</td></tr>";   
   echo "<tr><td colspan = \"4\"><input name=\"new_termin_titel\" size=\"30\" maxlength=\"200\" value=\"" . htmlspecialchars(stripslashes($new_termin_titel)) . "\"></td></tr>";
   echo "<tr><td colspan = \"4\">".$lang["termin_beschreibung"]."</td></tr>";   
   echo "<tr><td colspan = \"4\"><textarea name=\"new_termin_text\" wrap=virtual rows=15 cols=75>" . htmlspecialchars(stripslashes($new_termin_text)) . "</textarea></td></tr>";      
   echo "<tr><td colspan = \"4\"><input type=submit name=add value=".$lang["termin_speichern"]."></td></tr>";
   echo "</table>";
   echo "</form>";
}   
   
function termin_insert($termin_parent_id, $termin_name, $termin_tpl, $termin_img_small,$termin_img_small_inactive,  $termin_img_big, $termin_top_bar, $termin_left_bar, $termin_right_bar, $termin_foo_bar, $termin_titel, $termin_text){
   global $conf, $lang;
   
   $Statement = "INSERT INTO acme_termin  SET ".
                           " termin_name = '" . $termin_name . "', ".
                           " termin_tpl = '" . $termin_tpl . "', ".
                           " termin_parent_id = '" . $termin_parent_id . "', ".
                           " termin_img_small = '" . $termin_img_small . "', ".
                           " termin_img_small_inactive = '" . $termin_img_small_inactive . "', ".
                           " termin_img_big = '" . $termin_img_big. "', ".
                           " termin_top_bar = '" . $termin_top_bar. "', ".
                           " termin_left_bar = '" . $termin_left_bar . "', ".
                           " termin_right_bar = '" . $termin_right_bar . "', ".
                           " termin_foo_bar = '" . $termin_foo_bar . "', ".                                                                                                                                                                  
                           " termin_titel = '". $termin_titel . "', ".
                           " termin_text = '" . $termin_text . "', ".
                           " termin_create_date = NOW(), ".
                           " termin_modify_date = NOW(), ".
                           " termin_author_id = '" . $conf["author_id"] . "' ";
   $edit_result = dbquery($Statement);
   if ($edit_result){
   	  acl_user_set($conf["author_id"], "termine", mysql_insert_id(), "Y", "Y", "Y", "Y");
      echo $lang["termin_insert_erfolgreich"];
   }
   else{echo $lang["termin_insert_fehlgeschlagen"];};
}



function termin_delete($delete_id){
   global $conf, $lang;
   
   $delete_statement ="delete from acme_termin where termin_id = ". $delete_id;
   $delete_result = dbquery($delete_statement2);
   if($delete_result){echo $lang["termin_delete_erfolgreich"];}
   else{echo $lang["termin_delete_fehlgeschlagen"];};
}


function writeterminchilds($parent, &$h_level){
   global $conf, $lang;

   $result = dbquery("select * from acme_termin where termin_parent_id = '" . $parent . "' order by termin_name");
   if ( mysql_num_rows($result) > 0 ){
      while ($row = mysql_fetch_object($result)){
         echo "<tr><td>";
         for ($count = 0;$count < $h_level; $count++){echo "-";}
         echo $row->termin_name."</td>";
         echo "<td>&nbsp;</td>";
         echo "<td>";
         if (acl_check("edit", $conf["author_groups"], $conf["author_id"], "termine", $row->termin_id) == 1) {
            echo "<a href=" . $conf["admp"] . "&section=termine&action=termin_edit&edit_id=".$row->termin_id."><img src=\"" . $conf["images_admin"] . "icon_edit.png\" width=\"25\" height=\"25\"></a>";       
         }
         echo "</td>";
         echo "<td>";
         if (acl_check("delete", $conf["author_groups"], $conf["author_id"], "termine", $row->termin_id) == 1) {
            if (checkterminchilds($row->termin_id) == 0){
               if (checkterminentrys($row->termin_id) == 0){
                  echo "<a href=" . $conf["admp"] . "&section=termine&action=termin_delete&delete_id=".$row->termin_id."><img src=\"" . $conf["images_admin"] . "icon_delete.png\" width=\"25\" height=\"25\"></a>";      			
               } else {echo "&nbsp;";}
            } else {echo "&nbsp;";}
         } else {echo "&nbsp;";}
         echo "</td>";
         echo "</tr>\n";

         // eintraege
         $entry_result = dbquery("select * from acme_termin_data where termin_typ like '%:" . $row->termin_id . ":%' order by termin_data_headline");
         if ( mysql_num_rows($entry_result) > 0 ){
            while ($entry_row = mysql_fetch_object($entry_result)){
               echo "<tr><td>";
               for ($count = 0;$count < $h_level; $count++){echo "-";}
               echo "-termin: ". $entry_row->termin_data_headline . "</td>";
               echo "<td></td>";
               echo "<td>";
               if (acl_check("edit", $conf["author_groups"], $conf["author_id"], "termine", $row->termin_id) == 1) {
                  echo "<a href=" . $conf["admp"] . "&section=termine&action=termin_data_edit&edit_id=".$entry_row->termin_data_id."><img src=\"" . $conf["images_admin"] . "icon_edit.png\" width=\"25\" height=\"25\"></a>";       
               }
               echo "</td>";
               echo "<td>";
               if (acl_check("delete", $conf["author_groups"], $conf["author_id"], "termine", $row->termin_id) == 1) {
                  echo "<a href=" . $conf["admp"] . "&section=termine&action=termin_data_delete&delete_id=".$entry_row->termin_data_id."><img src=\"" . $conf["images_admin"] . "icon_delete.png\" width=\"25\" height=\"25\"></a>";      			
               } else {echo "&nbsp;";}
               echo "</td>";
               echo "</tr>\n";
            }
            mysql_free_result($entry_result);
         } 
         $h_level++;
         writeterminchilds($row->termin_id, $h_level);
         $h_level--;
      }
      mysql_free_result($result);
   }
}

function checkterminchilds($parent_id){
   global $conf, $lang;
   
   $childs = 0;
   $result = dbquery("select * from acme_termin where termin_parent_id  = '" . $parent_id . "'");
   if (mysql_num_rows($result) > 0 ){
      $childs = 1;
      mysql_free_result($result);
   }
   return $childs;   
} 

function checkterminentrys($termin){
   global $conf, $lang;
   
   $childs = 0;
   $result = dbquery("select * from acme_termin_data where termin_typ like '%:" . $termin . ":%'");
   if (mysql_num_rows($result) > 0 ){
      $childs = 1;
      mysql_free_result($result);
   }
   return $childs;   
}      

function createsel_termin($select_name,$id){
   global $conf, $lang;

   echo "<select multiple size = \"5\"  name=\"" . $select_name . "[]\">";
   echo "<option value= \"\"></option>";
   gettermin4select($parent, &$h_level, $id);
   echo "</select>";
   return;
}
function gettermin4select($parent, &$h_level, $grouplist){
   global $conf, $lang;
   
   $result = dbquery("select * from acme_termin where termin_parent_id = '" . $parent . "' order by termin_name");
   if ( mysql_num_rows($result) > 0 ){
      while ($row = mysql_fetch_object($result)){
      	 echo "<option value=" . $row->termin_id;
      	 if (is_array($grouplist)){
            foreach ($grouplist as $value){
              if ( eregi ( $row->termin_id, $value ) ){echo " selected ";}
            }
         }
         if (acl_check("insert", $conf["author_groups"], $conf["author_id"], "termine", $row->termin_id) == 1 && $row->url_typ_id <> $selfid) {
            echo ">";
         } else {
         	echo " disabled style = \"color:gray;font-style:italic;\">";
         }	
         for ($count = 0;$count < $h_level; $count++){echo "-";} 
         echo $row->termin_name . "</option>";
         $h_level++;
         gettermin4select($row->termin_id, $h_level, $grouplist, $selfid);
         $h_level--;
      }
      mysql_free_result($result);
   }
} 

function createsel_terminparent($select_name,$id,$selfid="0"){
   global $conf, $lang;

   echo "\n<select name=" . $select_name . ">\n";
   echo "<option value= \"\"></option>\n";
   getterminparent4select(0, &$h_level, $id, $selfid);
   echo "</select>\n";
   return;
}
function getterminparent4select($parent, &$h_level, $grouplist, $selfid){
   global $conf, $lang;

   $result = dbquery("select * from acme_termin where termin_parent_id = " . $parent . " order by termin_name");
   if ( mysql_num_rows($result) > 0 ){
      while ($row = mysql_fetch_object($result)){
      	 echo "<option value=" . $row->termin_id;
         if ( eregi ( $row->termin_id, $grouplist ) ){echo " selected ";}
         if (acl_check("insert", $conf["author_groups"], $conf["author_id"], "termine", $row->termin_id) == 1 && $row->url_typ_id <> $selfid) {
            echo ">";
         } else {
         	echo " disabled style = \"color:gray;font-style:italic;\">";
         }	
         for ($count = 0;$count < $h_level; $count++){echo "-";} 
         echo $row->termin_name . "</option>\n";
         $h_level++;
         getterminparent4select($row->termin_id, $h_level, $grouplist, $selfid);
         $h_level--;
      }
      mysql_free_result($result);
   }
}   
?>