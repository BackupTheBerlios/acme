<?php
include("lang/autoren." . $conf["lang"] . ".inc");

switch ($action)  {
   case "edit":
      authoredit($edit_author_id);
      break;
   case "new":
      authornew($new_author_nachname, $new_author_vorname, $new_author_img, $author_url,$new_author_email, $new_author_text);
      break;
   case "add":
      $result = authoradd($new_author_nachname, $new_author_vorname, $new_author_img, $author_url,$new_author_email, $new_author_text);
      if ($result){
         echo $lang["autoren_insert_erfolgreich"];
         authorbrowse();
      }else{
         echo $lang["autoren_insert_fehlgeschlagen"];
         authornew($new_author_nachname, $new_author_vorname, $new_author_img, $author_url,$new_author_email, $new_author_text);
      }
      break;
	case "update":
      $result = authorupdate($edit_author_id, $edit_author_nachname, $edit_author_vorname,$edit_author_img, $edit_author_url,$edit_author_email, $edit_author_text);
      if ($result){
      	 echo $lang["autoren_update_erfolgreich"];
      	 authorbrowse();
      }else{
         echo $lang["autoren_update_fehlgeschlagen"];
         authoredit($edit_author_id);
      }
      break;
	case "delete":
      $result = authordelete($delete_id);
      if ($result){
      	 echo $lang["autoren_delete_erfolgreich"];
      }
      else{
         echo $lang["autoren_delete_fehlgeschlagen"];
      }
      authorbrowse();
      break;
   default:
      authorbrowse();
      break;
}
   
function authordelete($delete_id){
   global $conf, $lang;

   $delete_result = dbquery("delete from acme_author where author_id = '". $delete_id . "'");
  
   return $delete_result;
}
   
function authoradd($new_author_nachname, $new_author_vorname, $new_author_img, $author_url,$new_author_email, $new_author_text){ 
   global $conf, $lang;
   
   $Statement = "INSERT INTO acme_author SET ".
                " author_nachname = '" . $new_author_nachname . "', ".
                " author_vorname = '" . $new_author_vorname . "', ".
                " author_img = '". $new_author_img ."',".
                " author_url = '". $new_author_url ."',".
                " author_email = '". $new_author_email ."',".
                " author_text = '". $new_author_text ."'";
   $insert_result = dbquery($Statement);
   
   return $insert_result;
}
 
function authorupdate($edit_author_id, $edit_author_nachname, $edit_author_vorname,$edit_author_img, $edit_author_url,$edit_author_email, $edit_author_text){ 
   global $conf, $lang;
   $Statement = "UPDATE acme_author SET ".
                " author_nachname = '" . $edit_author_nachname . "', ".
                " author_vorname = '" . $edit_author_vorname . "', ".
                " author_img = '". $edit_author_img ."',".
                " author_url = '". $edit_author_url ."',".
                " author_email = '". $edit_author_email ."',".
                " author_text = '". $edit_author_text ."' ".
                " WHERE author_id = '" . $edit_author_id . "'";
   $update_result = dbquery($Statement);
   return $update_result;
}
   
function authorbrowse(){
   global $conf, $lang;
   
   echo "<h1>".$lang["autoren_management"]."</h1>\n";
   echo "<a href=\"" . $conf["admp"] . "&action=new&section=autoren\">".$lang["autoren_neu_anlegen"]."</a>\n";
   echo "<table class=\"reda_td\">\n";
   echo "<tr>";
   echo "<td>".$lang["autoren_nachname"]."</td>";
   echo "<td>".$lang["autoren_vorname"]."</td>";
   echo "<td width=\"30\">&nbsp;</td>";
   echo "<td width=\"30\">&nbsp;</td>";
   echo "</tr>\n";
   $result = dbquery("select * from acme_author");
   if ( mysql_num_rows($result) > 0 ){	
      while ($row = mysql_fetch_object($result)) {
         echo "<tr>";	   
         echo "<td>" . $row->author_nachname . "</td>";
         echo "<td>" . $row->author_vorname  . "</td>";
         echo "<td>";
         if (checkgroupmodify($conf["user_groups"], "autoren") == 1){echo "<a href=\"" . $conf["admp"] . "&section=autoren&action=edit&edit_author_id=" . $row->author_id . "\"><img src=\"" . $conf["images_admin"] . "icon_edit.png\" width=\"25\" height=\"25\"></a>";}
         echo "</td>";
         echo "<td>";
         if (checkgroupdelete($conf["user_groups"], "autoren") == 1){echo "<a href=\"" . $conf["admp"] . "&action=delete&section=autoren&delete_id=" . $row->author_id . "\"><img src=\"" . $conf["images_admin"] . "icon_delete.png\" width=\"25\" height=\"25\"></a>";}
         echo "</td>";
         echo "</tr>\n"; 
      }
   mysql_free_result($result);
   }
   echo "</table>";   
} 
  
function authornew(){
   global $conf, $lang;
   
   echo "<h1>".$lang["autoren_neu_anlegen"]."</h1>";
   echo "<form action=\"" . $conf["admp"] . "&action=add&section=autoren\" method= \"POST\">";
   echo "<table class=\"reda_td\">";
   echo "<tr><td>".$lang["autoren_nachname"]."</td><td><input name=new_author_nachname size=30 maxlength=128></td></tr>";
   echo "<tr><td>".$lang["autoren_vorname"]."</td><td><input name=new_author_vorname size=30 maxlength=128></td></tr>";
   echo "<tr><td>".$lang["autoren_email"]."</td><td><input name=new_author_email size=30 maxlength=128></td></tr>";
   echo "<tr><td>".$lang["autoren_url"]."</td><td><input name=new_author_url size=30 maxlength=128></td></tr>";
   echo "<tr><td>".$lang["autoren_img"]."</td><td><input name=new_author_img size=30 maxlength=128></td></tr>";
   echo "<tr><td>".$lang["autoren_text"]."</td><td><textarea  name=new_author_text  wrap=virtual rows=4 cols=60></textarea></td></tr>";            
   echo "<tr><td colspan = \"2\"><input type=submit name=add value=\"add\"></td></tr>";
   echo "</table>";
   echo "</form>";
}   

function authoredit($edit_id){
   global $conf, $lang;
   
   $result = dbquery("select * from acme_author where author_id='". $edit_id . "'");
   if ($result){
      $row = mysql_fetch_object($result);
      echo "<h1>".$lang["autoren_bearbeiten"]."</h1>\n";
      echo "<form action=\"" . $conf["admp"] . "&action=update&section=autoren&edit_author_id=" . $row->author_id . "\" method=\"POST\">\n";
      echo "<table class=\"reda_td\">\n";
      echo "<tr><td>".$lang["autoren_nachname"]."</td><td><input name=edit_author_nachname value=\"" . $row->author_nachname . "\"></td></tr>\n";
      echo "<tr><td>".$lang["autoren_vorname"]."</td><td><input name=edit_author_vorname value=\"" . $row->author_vorname . "\"></td></tr>\n";
      echo "<tr><td>".$lang["autoren_email"]."</td><td><input name=edit_author_email size=30 maxlength=128  value=\"" . $row->author_email . "\"></td></tr>";
      echo "<tr><td>".$lang["autoren_url"]."</td><td><input name=edit_author_url size=30 maxlength=128  value=\"" . $row->author_url . "\"></td></tr>";
      echo "<tr><td>".$lang["autoren_img"]."</td><td><input name=edit_author_img size=30 maxlength=128  value=\"" . $row->author_img . "\"></td></tr>";
      echo "<tr><td>".$lang["autoren_text"]."</td><td><textarea  name=edit_author_text  wrap=virtual rows=4 cols=60>" . $row->author_text . "</textarea></td></tr>";            
      echo "<tr><td><input type=submit name=my_edit_author value=Submit></td></tr>\n";
      echo "</table>";
      echo "</form>";
      mysql_free_result($result);
   }
}
?>