<?php

include($conf["admbase"] . "/lang/glossar." . $conf["lang"] . ".inc");

switch($action){
	case "glossar_edit":
      glossar_edit($glossar_id, $edit_glossar_titel, $edit_glossar_text, $edit_glossar_img, $edit_glossar_tpl);
      break;

	case "glossar_update":
	  $error=0;
	  if ($edit_glossar_titel == ""){
	     $errortext .= $lang["glossar_titel_fehlt"]."<br>";
      	 $error = 1;
	  } 	 
	  if ($edit_glossar_text == ""){
	     $errortext .= $lang["glossar_text_fehlt"]."<br>";
      	 $error = 1;
	  } 	 
	  if ($edit_glossar_tpl== ""){
	     $errortext .= $lang["glossar_tpl_fehlt"]."<br>";
      	 $error = 1;
	  }
	  if ($error==0){  	 
         glossar_update($glossar_id, $edit_glossar_titel, $edit_glossar_text, $edit_glossar_img, $edit_glossar_tpl);
         glossar_browse();
	  }
	  else {
         echo $errortext;	  	
	  	 glossar_edit($glossar_id, $edit_glossar_titel, $edit_glossar_text, $edit_glossar_img, $edit_glossar_tpl);
	  }	   
      break;

	case "glossar_new":
		glossar_new($new_glossar_name, $new_glossar_text, $new_glossar_img, $new_glossar_tpl);
      break;

   case "glossar_insert":
	  $error=0;
	  if ($new_glossar_titel == ""){
	     $errortext .= $lang["glossar_titel_fehlt"]."<br>";
      	 $error = 1;
	  } 	 
	  if ($new_glossar_text == ""){
	     $errortext .= $lang["glossar_text_fehlt"]."<br>";
      	 $error = 1;
	  } 	 
	  if ($new_glossar_tpl== ""){
	     $errortext .= $lang["glossar_tpl_fehlt"]."<br>";
      	 $error = 1;
	  }
	  if ($error==0){  	 
         glossar_insert($new_glossar_titel, $new_glossar_text, $new_glossar_img, $new_glossar_tpl);
         glossar_browse();
	  }
	  else {
         echo $errortext;	  	
	  	 glossar_new($new_glossar_titel, $new_glossar_text, $new_glossar_img, $new_glossar_tpl);
	  }	   
      break;

	case "glossar_delete":
      glossar_delete($glossar_id);
      glossar_browse();

      break;

   default:
      glossar_browse();

      break;
}

function glossar_edit($edit_glossar_id, $edit_glossar_titel, $edit_glossar_text, $edit_glossar_img, $edit_glossar_tpl){

   global $conf, $lang;

   $result = dbquery("select * from acme_glossar where glossar_id=$edit_glossar_id");
   if ($result)  {
      $acme_glossar = mysql_fetch_object($result);
      echo "<h1>".$lang["glossar_bearbeiten"]."</h1>".
           "<form action=\"" . $conf["admp"] . "&section=glossar&action=glossar_update&glossar_id=" . $acme_glossar->glossar_id . "\"  method=POST>".
           "<table class=\"reda_td\">".
           "<tr><td>".$lang["glossar_titel"]."</td></tr>".
           "<tr><td><input name=edit_glossar_titel size=70 maxlength=128 value=\"" . htmlspecialchars($acme_glossar->glossar_titel) . "\"></td></tr>".
           "<tr><td>".$lang["glossar_text"]."</td></tr>".
           "<tr><td><textarea name=\"edit_glossar_text\" wrap=virtual rows=15 cols=75>" . htmlspecialchars($acme_glossar->glossar_text) . "</textarea></td>".
           "<tr><td>".$lang["glossar_bild"]."</td></tr>".
           "<tr><td>";          
      createsel_img("edit_glossar_img", $acme_glossar->glossar_img);
      echo "</td></tr>".
           "<tr><td>".$lang["glossar_tpl"]."</td></tr>".
           "<tr><td>";          
      createsel_glossar_tpl("edit_glossar_tpl",  $acme_glossar->glossar_tpl);
      echo "</td></tr>".     
           "<tr><td><input type=submit name=add value=".$lang["glossar_speichern"]."></td></tr>".
           "</table>".
           "</form>";
      mysql_free_result($result);
   }
   else{echo $lang["glossar_notfound"];}
}

function glossar_update($glossar_id, $glossar_titel, $glossar_text, $glossar_img, $glossar_tpl){
   global $conf, $lang;

   $Statement = "UPDATE acme_glossar SET ".
                "glossar_titel = '". $glossar_titel . "',".
                "glossar_img   = '". $glossar_img   . "',".                
                "glossar_tpl   = '". $glossar_tpl   . "',".                
                "glossar_text  = '". $glossar_text  . "'".
                " WHERE glossar_id = '". $glossar_id . "'";
   $update_result = dbquery($Statement);
   if($update_result){echo $lang["glossar_update_erfolgreich"];}
   else{echo $lang["glossar_update_fehlgeschlagen"];};
}

function glossar_new($new_glossar_titel, $new_glossar_text, $new_glossar_img, $new_glossar_tpl) {
   global $conf, $lang;

   echo "<h1>".$lang["glossar_neu"]."</h1>".
        "<form action=\"" .  $conf["admp"] . "&section=glossar&action=glossar_insert\"  method=POST>".
        "<table class=\"reda_td\">".
        "<tr><td>".$lang["glossar_titel"]."</td></tr>".
        "<tr><td><input name=new_glossar_titel size=70 maxlength=128 value=\"" . htmlspecialchars(stripslashes($new_glossar_titel)) . "\"></td></tr>".
        "<tr><td>".$lang["glossar_text"]."</td></tr>".
        "<tr><td><textarea name=\"new_glossar_text\" wrap=virtual rows=15 cols=75>" . htmlspecialchars(stripslashes($new_glossar_text)) . "</textarea></td>".
        "<tr><td>".$lang["glossar_bild"]."</td></tr>".
        "<tr><td>";          
   createsel_img("new_glossar_img",  $new_glossar_img);
   echo "</td></tr>".
        "<tr><td>".$lang["glossar_tpl"]."</td></tr>".
        "<tr><td>";          
   createsel_glossar_tpl("new_glossar_tpl",  $new_glossar_tpl);
   echo "</td></tr>".     
        "<tr><td><input type=submit name=add value=".$lang["glossar_speichern"]."></td></tr>".
        "</table>".
        "</form>";
}
function glossar_insert($glossar_titel, $glossar_text, $glossar_img, $glossar_tpl){
   global $conf, $lang;

   $Statement = "INSERT INTO acme_glossar SET ".
                "glossar_titel = '". $glossar_titel . "', ".
                "glossar_img = '". $glossar_img . "', ".                
                "glossar_tpl = '". $glossar_tpl . "', ".                
                "glossar_text = '". $glossar_text . "' ";
   $insert_result = dbquery($Statement);
   if($insert_result){echo $lang["glossar_insert_erfolgreich"];}
   else{echo $lang["glossar_insert_fehlgeschlagen"];};
}

function glossar_delete($glossar_id) {
   global $conf, $lang;
   $delete_result = dbquery("delete from acme_glossar where glossar_id = '". $glossar_id . "'");
   if($delete_result){echo $lang["glossar_delete_erfolgreich"];}
   else{echo $lang["glossar_delete_fehlgeschlagen"];};
}

function glossar_browse() {
   global $conf, $lang;

   echo "<h1>".$lang["glossar_verwaltung"]."</h1>";
   if (checkgroupcreate($conf["author_groups"], "glossar") == 1){
      echo "<a href=\"" . $conf["admp"] . "&section=glossar&action=glossar_new\">".$lang["glossar_neu"]."</a>";
   }
   echo "<table class=\"reda_td\">";
   echo "<tr><td>".$lang["glossar_titel"]."</td><td width=\"30\"> </td><td width=\"30\"> </td><td width=\"30\"> </td></tr>";
   $result = dbquery("select * from acme_glossar order by glossar_titel");
   if ( mysql_num_rows($result) > 0 )           {
      while ($row = mysql_fetch_object($result))              {
         echo "<tr>";
         echo "<td>".$row->glossar_titel."</td>";
         echo "<td>";
         if (checkgroupmodify($conf["author_groups"], "glossar") == 1){
            echo "<a href=\"" . $conf["admp"] . "&section=glossar&action=glossar_edit&glossar_id=" . $row->glossar_id . "\"><img src=\"" . $conf["images_admin"] . "icon_edit.png\" width=\"25\" height=\"25\"></a>";
         }
         echo "</td>";
         echo "<td>";
         if (checkgroupdelete($conf["author_groups"], "glossar") == 1){
            echo "<a href=\"" . $conf["admp"] . "&section=glossar&action=glossar_delete&glossar_id=" . $row->glossar_id . "\"><img src=\"" . $conf["images_admin"] . "icon_delete.png\" width=\"25\" height=\"25\"></a>";
         }
         echo "</td>";
         echo "</tr>";
      }
   mysql_free_result($result);
   }
   echo "</table>";
}

function createsel_glossar_tpl($select_name,$grouplist){

   global $conf, $lang;

   echo "<select name=\"" . $select_name . "\">";

   echo "<option";
   if ($grouplist == "1"){echo " selected";};
   echo " value=\"1\">".$lang["glossar_tpl_imgzo"]."</option>";

   echo "<option";
   if ($grouplist == "2"){echo " selected";};
   echo " value=\"2\">".$lang["glossar_tpl_imgzu"]."</option>";

   echo "<option";
   if ($grouplist == "3"){echo " selected";};
   echo " value=\"3\">".$lang["glossar_tpl_imgro"]."</option>";

   echo "<option";
   if ($grouplist == "4"){echo " selected";};
   echo " value=\"4\">".$lang["glossar_tpl_imgru"]."</option>";

   echo "<option";
   if ($grouplist == "5"){echo " selected";};
   echo " value=\"5\">".$lang["glossar_tpl_imgol"]."</option>";

   echo "<option";
   if ($grouplist == "6"){echo " selected";};
   echo " value=\"6\">".$lang["glossar_tpl_imglu"]."</option>";

   echo "<option";
   if ($grouplist == "7"){echo " selected";};
   echo " value=\"7\">".$lang["glossar_tpl_imgl"]."</option>";
   
   echo "<option";
   if ($grouplist == "8"){echo " selected";};
   echo " value=\"8\">".$lang["glossar_tpl_imgr"]."</option>";

   echo "<option";
   if ($grouplist == "9" || $grouplist == ""){echo " selected";};
   echo " value=\"9\">".$lang["glossar_tpl_nurtext"]."</option>";

   echo "</select>";
   return;
}
?>
