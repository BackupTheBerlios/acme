<?php
include("lang/autoren." . $conf["lang"] . ".inc");

switch ($action)  {
   case "edit":
      authoredit($edit_author_id);
      break;
   case "new":
      authornew($new_author_nachname, $new_author_vorname, $new_author_img, $author_url,$new_author_email, $new_author_text, $new_author_name, $new_author_groups, $new_author_passwd1, $new_author_passwd2,$new_author_active,$new_author_lang);
      break;
   case "add":
      $error = 0;
      $errors="";
      if ($new_author_passwd1 != $new_author_passwd2){$errors.=$lang["autoren_pw_error"]."<br>";$error=1;}
      if ($new_author_groups==""){$errors.=$lang["autoren_group_error"]."<br>";$error=1;}
      if ($new_author_name==""){$errors.=$lang["autoren_name_fehlt"]."<br>";$error=1;}
      if ($new_author_nachname==""){$errors.=$lang["autoren_nn_fehlt"]."<br>";$error=1;}
      if ($new_author_vorname==""){$errors.=$lang["autoren_vn_fehlt"]."<br>";$error=1;}
      if ($new_author_lang==""){$errors.=$lang["autoren_lang_fehlt"]."<br>";$error=1;}
      if($error!=1) {	
        $result = authoradd($new_author_name,$new_author_passwd1,$new_author_groups,$new_author_active,$new_author_nachname,$new_author_vorname,$new_author_email,$new_author_url,$new_author_img,$new_author_text,$new_author_lang);
        if ($result){
           echo $lang["autoren_insert_erfolgreich"];
           authorbrowse();
        }else{
           echo $lang["autoren_insert_fehlgeschlagen"];
           authornew($new_author_nachname, $new_author_vorname, $new_author_img, $author_url,$new_author_email, $new_author_text, $new_author_name, $new_author_groups, $new_author_passwd1, $new_author_passwd2, $new_author_active,$new_author_lang);
        }
      } else {
        echo $errors;
      	authornew($new_author_nachname, $new_author_vorname, $new_author_img, $author_url,$new_author_email, $new_author_text, $new_author_name, $new_author_groups, $new_author_passwd1, $new_author_passwd2, $new_author_active,$new_author_lang);
      }
      break;
	case "update":
	  $error = 0;
	  $errors="";
      if ($edit_author_groups==""){$errors.=$lang["autoren_group_error"]."<br>";$error=1;}
      if ($edit_author_name==""){$errors.=$lang["autoren_name_fehlt"]."<br>";$error=1;}
      if ($edit_author_nachname==""){$errors.=$lang["autoren_nn_fehlt"]."<br>";$error=1;}
      if ($edit_author_vorname==""){$errors.=$lang["autoren_vn_fehlt"]."<br>";$error=1;}
      if ($edit_author_lang==""){$errors.=$lang["autoren_lang_fehlt"]."<br>";$error=1;}
      if($error!=1) {	
         $result = authorupdate($edit_author_id, $edit_author_nachname, $edit_author_vorname,$edit_author_img, $edit_author_url,$edit_author_email, $edit_author_text, $edit_author_name, $edit_author_groups, $edit_author_active,$edit_author_lang);
         if ($result){
         	echo $lang["autoren_update_erfolgreich"];
      	    authorbrowse();
         }else{
            echo $lang["autoren_update_fehlgeschlagen"];
            authoredit($edit_author_id);
         }
      } else {
        echo $errors;
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
     case "chpasswd":
      authorchpw($edit_author_id);
     break; 
     case "pwupdate":
       $error = 0;
       $errors="";
       if (checkoldpw($edit_author_id, $old_author_passwd)==0){$errors.=$lang["autoren_pwo_error"]."<br>";$error=1;}
       if ($new_author_passwd1 != $new_author_passwd2){$errors.=$lang["autoren_pw_error"]."<br>";$error=1;}
       if ($error == 0) {
          $result = authorupdatepw($edit_author_id, $new_author_passwd1);
         if ($result){
         	echo $lang["autoren_update_erfolgreich"];
      	    authorbrowse();
         }else{
            echo $lang["autoren_update_fehlgeschlagen"];
            authorchpw($edit_author_id);
         }
       }
       else {
       	echo $errors;
       	authorchpw($edit_author_id);
       }	   
       break; 
     
   default:
      authorbrowse();
      break;
}
   
function authordelete($delete_id){
   global $conf, $lang;

   $delete_result = dbquery("delete from ".$conf["db_namespace"]."author where author_id = '". $delete_id . "'");
  
   return $delete_result;
}
   
function authoradd($new_author_name,$new_author_passwd,$new_author_groups,$new_author_active,$new_author_nachname,$new_author_vorname,$new_author_email,$new_author_url,$new_author_img,$new_author_text,$new_author_lang){ 
   global $conf, $lang;
   
   $Statement = "INSERT INTO ".$conf["db_namespace"]."author SET ".
                " author_name   = '" . $new_author_name . "',". 
                " author_groups = '" . joingrouparray($new_author_groups) ."',".
                " author_passwd = '" . $new_author_passwd     ."',".
                " author_active = '" . $new_author_active     ."',".   
                " author_nachname = '" . $new_author_nachname ."',".
                " author_vorname = '"  . $new_author_vorname  ."',".
                " author_img = '".       $new_author_img      ."',".
                " author_url = '".       $new_author_url      ."',".
                " author_lang = '".      $new_author_lang     ."',".
                " author_email = '".     $new_author_email    ."',".
                " author_text = '".      $new_author_text     ."'";
   $insert_result = dbquery($Statement);
   
   return $insert_result;
}
 
function authorupdate($edit_author_id, $edit_author_nachname, $edit_author_vorname,$edit_author_img, $edit_author_url,$edit_author_email, $edit_author_text, $edit_author_name, $edit_author_groups, $edit_author_active,$edit_author_lang){ 
   global $conf, $lang;
   $Statement = "UPDATE ".$conf["db_namespace"]."author SET ".
                " author_name   = '" .  $edit_author_name . "' , ".
                " author_groups = '" .  joingrouparray($edit_author_groups) . "' , ".
                " author_active = '" .  $edit_author_active    ."',".
                " author_nachname = '". $edit_author_nachname  ."',".
                " author_vorname = '" . $edit_author_vorname   ."',".
                " author_img = '".      $edit_author_img       ."',".
                " author_lang = '".     $edit_author_lang      ."',".
                " author_url = '".      $edit_author_url       ."',".
                " author_email = '".    $edit_author_email     ."',".
                " author_text = '".     $edit_author_text      ."' ".
                " WHERE author_id = '". $edit_author_id        . "'";
   $update_result = dbquery($Statement);
   return $update_result;
}

function authorupdatepw($edit_author_id, $edit_author_password){ 
   global $conf, $lang;
   
   $Statement = "UPDATE ".$conf["db_namespace"]."author SET ".
                " author_passwd = '". $edit_author_password ."' ".
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
   echo "<td>".$lang["autoren_name"]."</td>";
   echo "<td>".$lang["autoren_gruppe"]."</td>";
   echo "<td>".$lang["autoren_aktiv"]."</td>";
   echo "<td>".$lang["autoren_nachname"]."</td>";
   echo "<td>".$lang["autoren_vorname"]."</td>";
   echo "<td width=\"30\">&nbsp;</td>";
   echo "<td width=\"30\">&nbsp;</td>";
   echo "</tr>\n";
   $result = dbquery("select * from ".$conf["db_namespace"]."author");
   if ( mysql_num_rows($result) > 0 ){	
      while ($row = mysql_fetch_object($result)) {
         echo "<tr>";	  
         echo "<td>$row->author_name</td>";
         echo "<td>";
         echo getgroupnamesbyarray($row->author_groups);
         echo "</td>";
         echo "<td>" . $row->author_active . "</td>";
         echo "<td>" . $row->author_nachname . "</td>";
         echo "<td>" . $row->author_vorname  . "</td>";
         echo "<td>";
         if (checkgroupmodify($conf["author_groups"], "autoren") == 1){echo "<a href=\"" . $conf["admp"] . "&section=autoren&action=edit&edit_author_id=" . $row->author_id . "\"><img src=\"" . $conf["images_admin"] . "icon_edit.png\" width=\"25\" height=\"25\"></a>";}
         echo "</td>";
         echo "<td>";
         if ( $row->author_name != $conf["author_name"] ){         
            if (checkgroupdelete($conf["author_groups"], "autoren") == 1){echo "<a href=\"" . $conf["admp"] . "&action=delete&section=autoren&delete_id=" . $row->author_id . "\"><img src=\"" . $conf["images_admin"] . "icon_delete.png\" width=\"25\" height=\"25\"></a>";}
         }
         else {echo $lang["autoren_self"];}            
         echo "</td>";
         echo "</tr>\n"; 
      }
   mysql_free_result($result);
   }
   echo "</table>";   
} 
  
function authornew($new_author_nachname, $new_author_vorname, $new_author_img, $author_url,$new_author_email, $new_author_text, $new_author_name, $new_author_groups, $new_author_passwd1, $new_author_passwd2, $new_author_active,$new_author_lang){
   global $conf, $lang;
   
   echo "<h1>".$lang["autoren_neu_anlegen"]."</h1>\n";
   echo "<form action=\"" . $conf["admp"] . "&action=add&section=autoren\" method= \"POST\">\n";
   echo "<table class=\"reda_td\">\n";
   echo "<tr><td>".$lang["autoren_name"]."</td><td><input name=new_author_name></td></tr>\n";
   echo "<tr><td>".$lang["autoren_pass"]."</td><td><input name=new_author_passwd1 type=password></td></tr>\n";
   echo "<tr><td>".$lang["autoren_passw"]."</td><td><input name=new_author_passwd2 type=password></td></tr>\n";
   if (checkgroupcreate($conf["author_groups"], "autoren") == 1){
      echo "<tr><td>".$lang["autoren_gruppe"]."</td>\n";
      echo "<td>\n";
      createsel_groups("new_author_groups","null");
      echo "</td></tr>\n";
   }
   echo "<tr><td>".$lang["autoren_lang"]."</td><td>";
   echo "<select name = new_author_lang>";
   echo "<option value = de>de</option>";
   echo "<option value = en>en</option>";
   echo "</select>";
   echo "</td></tr>\n";
   echo "<tr><td>".$lang["autoren_aktiv"]."</td><td><input type=radio name=new_author_active value=\"Y\" checked>Y</input><input type=radio name=new_author_active value=\"N\">N</input></td></tr>\n";
   echo "<tr><td>".$lang["autoren_nachname"]."</td><td><input name=new_author_nachname size=30 maxlength=128></td></tr>\n";
   echo "<tr><td>".$lang["autoren_vorname"]."</td><td><input name=new_author_vorname size=30 maxlength=128></td></tr>\n";
   echo "<tr><td>".$lang["autoren_email"]."</td><td><input name=new_author_email size=30 maxlength=128></td></tr>\n";
   echo "<tr><td>".$lang["autoren_url"]."</td><td><input name=new_author_url size=30 maxlength=128></td></tr>\n";
   echo "<tr><td>".$lang["autoren_img"]."</td><td><input name=new_author_img size=30 maxlength=128></td></tr>\n";
   echo "<tr><td>".$lang["autoren_text"]."</td><td><textarea  name=new_author_text  wrap=virtual rows=4 cols=60></textarea></td></tr>\n";            
   echo "<tr><td colspan = \"2\"><input type=submit name=add value=\"".$lang["autoren_speichern"]."\"></td></tr>\n";
   echo "</table>\n";
   echo "</form>\n";
}   

function authoredit($edit_id){
   global $conf, $lang;
   
   $result = dbquery("select * from ".$conf["db_namespace"]."author where author_id='". $edit_id . "'");
   if ($result){
      $row = mysql_fetch_object($result);
      echo "<h1>".$lang["autoren_bearbeiten"]."</h1>\n";
      echo "<a href=\"" . $conf["admp"] . "&action=chpasswd&section=autoren&edit_author_id=" . $row->author_id . "\">".$lang["autoren_chpasswd"]."</a>\n";   
      echo "<form action=\"" . $conf["admp"] . "&action=update&section=autoren&edit_author_id=" . $row->author_id . "\" method=\"POST\">\n";
      echo "<table class=\"reda_td\">\n";
      echo "<tr><td>".$lang["autoren_name"]."</td><td><input name=edit_author_name value=\"" . $row->author_name . "\"></td></tr>\n";
      echo "<tr><td>".$lang["autoren_gruppe"]."</td><td>\n";
      createsel_groups("edit_author_groups",$row->author_groups);
      echo "</td></tr>\n";
      echo "<tr><td>".$lang["autoren_lang"]."</td><td>";
      echo "<select name = edit_author_lang>";
      if ($row->author_lang=="de"){echo "<option value = de selected>de</option>";}else{echo "<option value = de>de</option>";}
      if ($row->author_lang=="en"){echo "<option value = en selected>en</option>";}else{echo "<option value = en>en</option>";}
      echo "</select>";
      echo "</td></tr>\n";
      if ($row->author_name != $conf["author_name"]){
         echo "<tr><td>".$lang["autoren_aktiv"]."</td><td>";
         echo "<input type=radio name=edit_author_active value=\"Y\""; 
         if ($row->author_active == "Y" ) echo "checked";
         echo ">Y";
         echo "<input type=radio name=edit_author_active value=\"N\""; 
         if ($row->author_active == "N" ) echo "checked";
         echo ">N</td></tr>\n";
      } 
      else {
         echo "<tr><td colspan = \"2\"><input type=hidden name=edit_author_active value=Y></td></tr>";
      }
      echo "<tr><td>".$lang["autoren_nachname"]."</td><td><input name=edit_author_nachname value=\"" . $row->author_nachname . "\"></td></tr>\n";
      echo "<tr><td>".$lang["autoren_vorname"]."</td><td><input name=edit_author_vorname value=\"" . $row->author_vorname . "\"></td></tr>\n";
      echo "<tr><td>".$lang["autoren_email"]."</td><td><input name=edit_author_email size=30 maxlength=128  value=\"" . $row->author_email . "\"></td></tr>";
      echo "<tr><td>".$lang["autoren_url"]."</td><td><input name=edit_author_url size=30 maxlength=128  value=\"" . $row->author_url . "\"></td></tr>";
      echo "<tr><td>".$lang["autoren_img"]."</td><td><input name=edit_author_img size=30 maxlength=128  value=\"" . $row->author_img . "\"></td></tr>";
      echo "<tr><td>".$lang["autoren_text"]."</td><td><textarea  name=edit_author_text  wrap=virtual rows=4 cols=60>" . $row->author_text . "</textarea></td></tr>";            
      echo "<tr><td><input type=submit name=my_edit_author value=\"".$lang["autoren_speichern"]."\"></td></tr>\n";
      echo "</table>";
      echo "</form>";
      mysql_free_result($result);
   }
}
function authorchpw($edit_id){
   global $conf, $lang;
   
   $result = dbquery("select * from ".$conf["db_namespace"]."author where author_id='". $edit_id . "'");
   if ($result){
      $row = mysql_fetch_object($result);
      echo "<h1>".$lang["autoren_chpasswd"]."</h1>\n";
      echo "<form action=\"" . $conf["admp"] . "&action=pwupdate&section=autoren&edit_author_id=" . $row->author_id . "\" method=\"POST\">\n";
      echo "<table class=\"reda_td\">\n";
      echo "<tr><td>".$lang["autoren_passo"]."</td><td><input name=old_author_passwd  type=password></td></tr>";      
      echo "<tr><td>".$lang["autoren_pass"] ."</td><td><input name=new_author_passwd1 type=password></td></tr>";
      echo "<tr><td>".$lang["autoren_passw"]."</td><td><input name=new_author_passwd2 type=password></td></tr>";
      echo "<tr><td><input type=submit name=my_edit_author value=\"".$lang["autoren_speichern"]."\"></td></tr>\n";
      echo "</table>";
      echo "</form>";
      mysql_free_result($result);
   }
}
function checkoldpw ($id, $pw) {
	global $conf, $lang;
	
    $query = "SELECT author_id FROM ".$conf["db_namespace"]."author WHERE author_passwd = '" . $pw . "' AND author_id = '" . $id . "';";
    $result = dbquery($query);   
    if ( mysql_num_rows($result) > 0 ) {return 1;}
    else {return 0;}
    
	
}	
function createsel_groups($select_name,$grouplist){
   global $conf, $lang;
   
   $allgroups = dbquery("select * from ".$conf["db_namespace"]."groups order by group_name");
   echo "<select multiple size = \"5\" name=\"" . $select_name . "[]\">";
   if ( mysql_num_rows($allgroups) > 0 )
      {
      while ( $g_row = mysql_fetch_object($allgroups) )
         {
         echo "<option value=" . $g_row->group_id;
         if ( eregi ( $g_row->group_id, $grouplist ) )
            echo " selected ";
         echo ">" . $g_row->group_name . "</option>";
         }
      mysql_free_result($allgroups);
      }
   echo "</select>";
   return;
}
?>