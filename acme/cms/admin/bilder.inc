<?php
include($conf["admbase"] . "/lang/bilder." . $conf["lang"] . ".inc");

switch ($action) {
  case "img_edit":
     img_edit($img_id);
  break;   
  case "img_typ_edit":
     img_typ_edit($img_typ_id);
  break;   
  case "img_update" :
     img_update($img_id, $edit_img_name, $edit_img_description,$edit_img_desc_long,$img_typ_id);
  break;
  case "img_typ_update" :
     img_typ_update($edit_img_typ_id, $edit_img_typ_name, $edit_img_typ_text, $edit_img_typ_parent_id, $edit_img_typ_tpl, $edit_img_typ_img_small,  $edit_img_typ_img_big, $edit_img_typ_top_bar, $edit_img_typ_left_bar, $edit_img_typ_right_bar, $edit_img_typ_foo_bar, $edit_img_typ_rows, $edit_img_typ_cols, $edit_img_typ_maxheight, $edit_img_typ_maxwidth);
  break;
  case "img_new":
     img_new($img_typ_id);
  break;
  case "img_typ_new":
     img_typ_new($new_img_typ_name, $new_img_typ_text, $new_img_typ_parent_id, $new_img_typ_tpl, $new_img_typ_img_small,  $new_img_typ_img_big, $new_img_typ_top_bar, $new_img_typ_left_bar, $new_img_typ_right_bar, $new_img_typ_foo_bar, $new_img_typ_rows,$new_img_typ_cols,$new_img_typ_maxheight,$new_img_typ_maxwidth);
  break;
  case "img_add":
     if (!file_exists($HTTP_POST_FILES['datei']['tmp_name'])) { $error .= $lang["bilder_nofile"]."<br>";}
     if (file_exists($conf["imagesdir"] . $HTTP_POST_FILES['datei']['name'])) { $error .= $lang["bilder_fileexists"]."<br>";}
     if ($error <> ""){
        unlink ($HTTP_POST_FILES['datei']['tmp_name']);
        echo $error;
        img_new($img_typ_id);
     }
     else {
        img_add($HTTP_POST_FILES['datei']['tmp_name'],$HTTP_POST_FILES['datei']['name'],$HTTP_POST_FILES['datei']['size'], $new_img_name, $new_img_description, $new_img_desc_long, $img_typ_id);
     }
  break;
  case "img_typ_add":
     img_typ_add($new_img_typ_name, $new_img_typ_text, $new_img_typ_parent_id, $new_img_typ_tpl, $new_img_typ_img_small,  $new_img_typ_img_big, $new_img_typ_top_bar, $new_img_typ_left_bar, $new_img_typ_right_bar, $new_img_typ_foo_bar, $new_img_typ_rows,$new_img_typ_cols,$new_img_typ_maxheight,$new_img_typ_maxwidth);
  break;
  case "img_delete":
     img_delete($img_id);
     
  break;  
  case "img_typ_delete":
     img_typ_delete($img_typ_id);
  break;  
  case "img_browse":
     img_browse($img_typ_id);
  break;  
  default: 
     img_typ_browse();
  break;
}

function img_browse($img_typ_id){
   global $conf, $lang;
   
	echo "<h1>".$lang["bilder_verwaltung"]."</h1>";
	echo "<h2>" . get_img_typ_name($img_typ_id) . "</h2>";
	if ( checkgroupcreate($conf["author_groups"], "bilder") == 1){
      echo "<a href=\"" . $conf["admp"] ."&section=bilder&action=img_new&img_typ_id=" . $img_typ_id . "\">".$lang["bilder_neu"]."</a>";
   }
   echo "<table class=\"reda_td \">";
   echo "<tr></td><td>".$lang["bilder_name"]."</td><td>".$lang["bilder_realname"]."</td><td>".$lang["bilder_beschreibung"]."</td><td>".$lang["bilder_thumb"]."</td><td></td><td></td></tr>";
   $result = dbquery("select * from acme_bilder where img_typ_id = '" . $img_typ_id . "'");
   if ( mysql_num_rows($result) > 0 ){	
      while ($row = mysql_fetch_object($result)){
         echo "<td>".$row->img_name."</td>";
         echo "<td>".$row->img_real_name."</td>";         
         echo "<td>".$row->img_description."</td>";
         echo "<td><img src=\"".$conf["images"]."thumb_".$row->img_real_name."\"></td>";         
         echo "<td>";
         if ( checkgroupmodify($conf["author_groups"], "bilder") == 1){echo "<a href=\"" . $conf["admp"] . "&action=img_edit&section=bilder&img_id=" . $row->img_id . "\"><img src=\"" . $conf["images_admin"] . "icon_edit.png\" width=\"25\" height=\"25\"></td>";}
         echo "<td>";
         if ( checkgroupdelete($conf["author_groups"], "bilder") == 1){echo "<a href=\"" . $conf["admp"] . "&action=img_delete&section=bilder&img_id=" . $row->img_id ."\"><img src=\"" . $conf["images_admin"] . "icon_delete.png\" width=\"25\" height=\"25\"></a>";}
         echo "</td>";
         echo "</tr>";
      }
      echo "</table>";
      mysql_free_result($result);
   }
}

function img_typ_browse(){
   global $conf, $lang;
   
   echo "<h1>".$lang["bilder_verwaltung"]."</h1>";
   if ( checkgroupcreate($conf["author_groups"], "bilder") == 1){
      echo "<a href=\"" . $conf["admp"] ."&section=bilder&action=img_typ_new\">".$lang["bilder_typ_neu"]."</a>";
   }
   echo "<table class=\"reda_td \">";
   echo "<tr></td><td>".$lang["bilder_typ_name"]."</td><td>".$lang["bilder_anzahl"]."</td><td></td><td></tr>";
   $result = dbquery("select * from acme_bilder_typs");
   if ( mysql_num_rows($result) > 0 ){	
      while ($row = mysql_fetch_object($result)){
         $img_count = count_img_from_typ($row->img_typ_id);
         echo "<tr><td>\n";
         if ( checkgroupcreate($conf["author_groups"], "bilder") == 1){
            echo "<a href=\"" . $conf["admp"] . "&action=img_browse&section=bilder&img_typ_id=" . $row->img_typ_id . "\">".$row->img_typ_name."</a>\n";
         }else{
         	echo $row->img_typ_name;
         }
         echo "</td><td>" . $img_count . "</td><td>\n";
         if ( checkgroupmodify($conf["author_groups"], "bilder") == 1){echo "<a href=\"" . $conf["admp"] . "&action=img_typ_edit&section=bilder&img_typ_id=" . $row->img_typ_id . "\"><img src=\"" . $conf["images_admin"] . "icon_edit.png\" width=\"25\" height=\"25\"></a>";}
         echo "</td>";
         echo "<td>";
         if ($img_count == 0 && checkgroupdelete($conf["author_groups"], "bilder") == 1){echo "<a href=\"" . $conf["admp"] . "&action=img_typ_delete&section=bilder&img_typ_id=" . $row->img_typ_id ."\"><img src=\"" . $conf["images_admin"] . "icon_delete.png\" width=\"25\" height=\"25\"></a>";}
         echo "</td>";
         echo "</tr>";
      }
      echo "</table>";
      mysql_free_result($result);
   }
}
   
function img_new($img_typ_id){
   global $conf, $lang;
   
   echo "<h1>".$lang["bilder_neu"]."<h1>\n".
        "<form action=\"" . $conf["admp"] ."&action=img_add&section=bilder&img_typ_id=" . $img_typ_id . "\" ENCTYPE=\"multipart/form-data\" method=\"POST\">\n".
        "<table class=\"reda_td\">\n".
        "<tr><td>".$lang["bilder_name"]."</td><td></td></tr>\n".
        "<tr>\n".
        "<td><input name=\"new_img_name\" size=\"25\" maxlength=\"25\"></td>\n".
        "<td><INPUT type=\"file\" name=\"datei\" size=\"15\"></td>\n".
        "</tr>".
        "<tr><td colspan = \"2\">".$lang["bilder_beschreibung"]."</td></tr>".
        "<tr><td colspan = \"2\"><input name=\"new_img_description\" size=\"50\" maxlength=\"250\" value = \"\"></td></tr>\n".
        "<tr><td colspan = \"2\">".$lang["bilder_beschreibung_lang"]."</td></tr>".
        "<tr><td colspan = \"2\"><textarea name=\"new_img_desc_long\" wrap=virtual rows=15 cols=75></textarea></td></tr>\n".
        "<tr><td colspan = \"2\"><input type=\"submit\" name=\"add\" value=\"add\"></td></tr>\n".
        "</table>\n".
        "</form>\n";
  
}


function img_typ_new($new_img_typ_name, $new_img_typ_text, $new_img_typ_parent_id, $new_img_typ_tpl, $new_img_typ_img_small,  $new_img_typ_img_big, $new_img_typ_top_bar, $new_img_typ_left_bar, $new_img_typ_right_bar, $new_img_typ_foo_bar, $new_img_typ_rows,$new_img_typ_cols,$new_img_typ_maxheight,$new_img_typ_maxwidth){
   global $conf, $lang;

   echo "<h1>".$lang["bilder_typ_neu"]."</h1>".
        "<form action=\"" . $conf["admp"] . "&section=bilder&action=img_typ_add\" ENCTYPE=\"multipart/form-data\" method=\"POST\">".
        "<table  class=\"reda_td\" border = 1 cellpadding = 0 cellspacing = 0>".
        "<tr><td colspan = 4>".$lang["bilder_typ_name"]."</td></tr>".
        "<tr>".
        "<td colspan=\"4\"><input name=new_img_typ_name size=45 maxlength=128 value = \"" . htmlspecialchars(stripslashes($new_img_typ_name)) . "\"></td>".
        "</tr>".
        "<tr><td>".$lang["bilder_typ"]."</td><td>".$lang["bilder_typ_tpl"]."</td><td>".$lang["bilder_typ_logo_gross"]."</td><td>".$lang["bilder_typ_logo_klein"]."</td></tr>\n".
        "<tr>".
        "<td>";
   createsel_img_typ_parent("new_img_typ_parent_id",$new_img_typ_parent_id);
   echo "</td>".
        "<td";
   createsel_tpl("new_img_typ_tpl",  $new_img_typ_tpl);
   echo "</td>".
        "<td>";
   createsel_img("new_img_typ_img_big",  $new_img_typ_img_big);
   echo "</td>".
        "<td>";
   createsel_img("new_img_typ_img_small",  $new_img_typ_img_small);
   echo "</td>".
        "</tr>".
        "<tr><td>".$lang["bilder_typ_bar_left"]."</td><td>".$lang["bilder_typ_bar_right"]."</td><td>".$lang["bilder_typ_bar_top"]."</td><td>".$lang["bilder_typ_bar_bottom"]."</td></tr>".
        "<tr>".
        "<td>";
   createsel_bar("new_img_typ_left_bar", $new_img_typ_left_bar);
   echo "</td>".
        "<td>";
   createsel_bar("new_img_typ_right_bar",  $new_img_typ_right_bar);
   echo "</td>".
        "<td>";
   createsel_bar("new_img_typ_top_bar",  $new_img_typ_top_bar);
   echo "</td>".
        "<td>";
   createsel_bar("new_img_typ_foo_bar",  $new_img_typ_foo_bar);
   echo "</td>".
        "</tr>\n".
        "<tr><td>".$lang["bilder_typ_cols"]."</td><td>".$lang["bilder_typ_rows"]."</td><td>".$lang["bilder_typ_maxwidth"]."</td><td>".$lang["bilder_typ_maxheight"]."</td></tr>".
        "<tr>".
        "<td><input name=new_img_typ_cols size=5 maxlength=5 value = \"" . $new_img_typ_cols . "\"></td>".
        "<td><input name=new_img_typ_rows size=5 maxlength=5 value = \"" . $new_img_typ_rows . "\"></td>".
        "<td><input name=new_img_typ_maxwidth size=5 maxlength=5 value = \"" . $new_img_typ_maxwidth . "\"></td>".
        "<td><input name=new_img_typ_maxheight size=5 maxlength=5 value = \"" . $new_img_typ_maxheight . "\"></td>".
        "</tr>".
        "<tr><td colspan=\"4\">&nbsp;</td></tr>".
        "<tr><td colspan=\"4\">".$lang["bilder_typ_text"]."</td></tr>".
        "<tr>".
        "<td colspan=\"4\"><textarea name=new_img_typ_text wrap=virtual rows=15 cols=75>" . htmlspecialchars(stripslashes($new_img_typ_text)) . "</textarea></td>".
        "</tr>".
        "<tr><td colspan=\"4\"><input type=submit name=edit_page value=".$lang["bilder_speichern"]."></td></tr>".
        "</table>".
        "</form>";
}

function img_typ_add($new_img_typ_name, $new_img_typ_text, $new_img_typ_parent_id,  $new_img_typ_img_big, $new_img_typ_top_bar, $new_img_typ_left_bar, $new_img_typ_right_bar, $new_img_typ_foo_bar, $new_img_typ_rows,$new_img_typ_cols,$new_img_typ_maxheight,$new_img_typ_maxwidth){
   global $conf, $lang;

  $Statement = "INSERT INTO acme_bilder_typs SET".
                " img_typ_name = '". $new_img_typ_name . "',".
                " img_typ_text = '". $new_img_typ_text . "',".
                " img_typ_tpl = '". $new_img_typ_tpl . "',".
                " img_typ_cols = '". $new_img_typ_cols . "',".
                " img_typ_rows = '". $new_img_typ_rows . "',".
                " img_typ_img_small = '". $new_img_typ_img_small . "',".
                " img_typ_img_big = '". $new_img_typ_img_big . "',".
                " img_typ_left_bar = '". $new_img_typ_left_bar . "',".
                " img_typ_right_bar = '". $new_img_typ_right_bar . "',".
                " img_typ_top_bar = '". $new_img_typ_top_bar . "',".
                " img_typ_foo_bar = '". $new_img_typ_foo_bar . "',".
                " img_typ_maxheight = '". $new_img_typ_maxheight . "',".
                " img_typ_maxwidth = '". $new_img_typ_maxwidth . "',".
                " img_typ_parent_id = '". $new_img_typ_parent_id . "'";

  $my_result = dbquery($Statement);
   
   if ($my_result) {echo $lang["bilder_typ_insert_erfolgreich"]."\n";}
   else            {echo $lang["bilder_typ_insert_fehlerhaft"]."\n<br>".$Statement;}
   img_typ_browse();
}    
   
   
function img_edit($img_id){
	global $conf, $lang;
   $result = dbquery("select * from acme_bilder where img_id='$img_id'");

   if ($result){
      $row = mysql_fetch_object($result);
      echo "<h1>".$lang["bilder_bearbeiten"]."<h1>\n".
           "<form action=\"" . $conf["admp"] . "&action=img_update&section=bilder&img_id=" . $img_id . "&img_typ_id=" . $row->img_typ_id . "\" ENCTYPE=\"multipart/form-data\" method=\"POST\">\n".
           "<table class=\"reda_td\">\n".
           "<tr><td>".$lang["bilder_name"]."</td><td>".$lang["bilder_realname"]."</td></tr>\n".
           "<tr><td><input name=\"edit_img_name\" size=\"25\" maxlength=\"25\" value = \"" . $row->img_name . "\"></td>\n".
           "<td>" . $row->img_real_name . "</td></tr>\n".
           "<tr><td colspan = \"1\">".$lang["bilder_beschreibung"]."</td>".
           "<td rowspan = \"4\"><img src=\"cms/bilder/thumb_".$row->img_real_name."\"></td>".
           "</tr>".
           "<tr><td colspan = \"1\"><input name=\"edit_img_description\" size=\"50\" maxlength=\"250\" value = \"" . $row->img_description . "\"></td></tr>\n".
           "<tr><td colspan = \"1\">".$lang["bilder_beschreibung_lang"]."</td></tr>".
           "<tr><td colspan = \"1\"><textarea name=\"edit_img_desc_long\" wrap=virtual rows=15 cols=75>" . $row->img_desc_long . "</textarea></td></tr>\n".
           "<tr><td colspan = \"2\"><input type=\"submit\" name=\"update\" value=\"update\"></td></tr>\n".
           "</table>\n".
           "</form>\n";
      mysql_free_result($result);
   }  

} 


function img_typ_edit($id){
   global $conf, $lang;
   
   $result = dbquery("select * from acme_bilder_typs where img_typ_id='" . $id . "'");
   if ($result) {
      $row = mysql_fetch_object($result);
      echo "<h1>".$lang["bilder_typ_bearbeiten"]."</h1>".
           "<form action=\"" . $conf["admp"] . "&section=bilder&action=img_typ_update\" ENCTYPE=\"multipart/form-data\" method=\"POST\">".
           "<input type=hidden name=edit_img_typ_id value=\"" . $row->img_typ_id . "\">".
           "<table  class=\"reda_td\" border = 1 cellpadding = 0 cellspacing = 0>".
           "<tr><td colspan=\"4\">".$lang["bilder_typ_name"]."</td></tr>".
           "<tr><td colspan=\"4\"><input name=edit_img_typ_name size=45 maxlength=128 value = \"" . htmlspecialchars($row->img_typ_name) . "\"></td></tr>".
           "<tr><td colspan=\"4\">&nbsp;</td></tr>".
           "<tr><td>".$lang["bilder_typ"]."</td><td>".$lang["bilder_typ_tpl"]."</td><td>".$lang["bilder_typ_logo_gross"]."</td><td>".$lang["bilder_typ_logo_klein"]."</td></tr>\n".
           "<td>";
      createsel_img_typ_parent("edit_img_typ_parent_id",$row->img_typ_parent_id,$row->img_typ_id);
      echo "</td>".   
           "<td>";
      createsel_tpl("edit_img_typ_tpl",  $row->img_typ_tpl);
      echo "</td>".
           "<td>";
      createsel_img("edit_img_typ_img_big",  $row->img_typ_img_big);
      echo "</td>".
           "<td>";
      createsel_img("edit_img_typ_img_small",  $row->img_typ_img_small);
      echo "</td>".
           "</tr>".
           "<tr><td>".$lang["bilder_typ_bar_left"]."</td><td>".$lang["bilder_typ_bar_right"]."</td><td>".$lang["bilder_typ_bar_top"]."</td><td>".$lang["bilder_typ_bar_bottom"]."</td></tr>".
           "<tr>".
           "<td>";
      createsel_bar("edit_img_typ_left_bar", $row->img_typ_left_bar);
      echo "</td>".
           "<td>";
      createsel_bar("edit_img_typ_right_bar",  $row->img_typ_right_bar);
      echo "</td>".
           "<td>";
      createsel_bar("edit_img_typ_top_bar",  $row->img_typ_top_bar);
      echo "</td>".
           "<td>";
      createsel_bar("edit_img_typ_foo_bar",  $row->img_typ_foo_bar);
      echo "</td>".
           "</tr>\n".
           "<tr><td>".$lang["bilder_typ_cols"]."</td><td>".$lang["bilder_typ_rows"]."</td><td>".$lang["bilder_typ_maxwidth"]."</td><td>".$lang["bilder_typ_maxheight"]."</td></tr>".
           "<tr>".
           "<td><input name=edit_img_typ_cols size=5 maxlength=5 value = \"" . $row->img_typ_cols . "\"></td>".
           "<td><input name=edit_img_typ_rows size=5 maxlength=5 value = \"" . $row->img_typ_rows . "\"></td>".
           "<td><input name=edit_img_typ_maxwidth size=5 maxlength=5 value = \"" . $row->img_typ_maxwidth . "\"></td>".
           "<td><input name=edit_img_typ_maxheight size=5 maxlength=5 value = \"" . $row->img_typ_maxheight . "\"></td>".
           "</tr>".
           "<tr><td colspan=\"4\">".$lang["bilder_typ_text"]."</td></tr>".
           "<tr>".
           "<td colspan=\"4\"><textarea name=edit_img_typ_text wrap=virtual rows=15 cols=75>" . htmlspecialchars($row->img_typ_text) . "</textarea></td>".
           "</tr>".
           "<tr><td colspan=\"4\"><input type=submit name=edit_page value=Speichern></td></tr>".
           "</table>".
           "</form>";
      mysql_free_result($result);
   }
}   

function img_typ_update($edit_img_typ_id, $edit_img_typ_name, $edit_img_typ_text, $edit_img_typ_parent_id, $edit_img_typ_tpl, $edit_img_typ_img_small,  $edit_img_typ_img_big, $edit_img_typ_top_bar, $edit_img_typ_left_bar, $edit_img_typ_right_bar, $edit_img_typ_foo_bar, $edit_img_typ_rows,$edit_img_typ_cols,$edit_img_typ_maxheight, $edit_img_typ_maxwidth){
   global $conf, $lang;
              
   $Statement = "UPDATE acme_bilder_typs SET".
                " img_typ_name = '". $edit_img_typ_name . "',".
                " img_typ_text = '". $edit_img_typ_text . "',".
                " img_typ_tpl = '". $edit_img_typ_tpl . "',".
                " img_typ_cols = '". $edit_img_typ_cols . "',".
                " img_typ_rows = '". $edit_img_typ_rows . "',".
                " img_typ_img_small = '". $edit_img_typ_img_small . "',".
                " img_typ_img_big = '". $edit_img_typ_img_big . "',".
                " img_typ_left_bar = '". $edit_img_typ_left_bar . "',".
                " img_typ_right_bar = '". $edit_img_typ_right_bar . "',".
                " img_typ_top_bar = '". $edit_img_typ_top_bar . "',".
                " img_typ_foo_bar = '". $edit_img_typ_foo_bar . "',".
                " img_typ_maxwidth = '". $edit_img_typ_maxwidth . "',".
                " img_typ_maxheight = '". $edit_img_typ_maxheight . "',".
                " img_typ_parent_id = '". $edit_img_typ_parent_id . "'".
                " WHERE img_typ_id = '". $edit_img_typ_id . "'";
   $my_result = dbquery($Statement);
   if ($my_result) {echo $lang["bilder_typ_update_erfolgreich"]."\n";}
  else             {echo  $lang["bilder_typ_update_fehlerhaft"]."\n";}
     img_typ_browse();
}
    
function img_update($img_id, $img_name, $img_description, $img_desc_long,$img_typ_id){
   global $conf, $lang;

	$Statement = "UPDATE acme_bilder Set ".
	                           " img_name = '" . $img_name . "', ".
                              " img_description = '". $img_description . "', ".
                              " img_desc_long = '". $img_desc_long . "', ".
                              " img_author_id = '". $conf["author_id"] . "' ".
                              " WHERE img_id = '" . $img_id . "'";
   $result = dbquery($Statement);
   if ($result){echo $lang["bilder_update_erfolgreich"]."<br>";}
   else {echo $lang["bilder_update_fehlerhaft"]."<br>\n";}
   img_browse($img_typ_id);
}

function img_delete($img_id){
   global $conf, $lang;

   $result = dbquery("select img_real_name, img_typ_id from acme_bilder where img_id='$img_id'");
   if ($result){
      $row = mysql_fetch_object($result);
      $imagename = $row->img_real_name;
      $img_typ_id = $row->img_typ_id;      
      echo "<h2>".$lang["bilder_loesche_datei"] ." ". $bild. "</h2><P>";
      if (unlink ($conf["imagesdir"] . $imagename) && unlink ($conf["imagesdir"] ."thumb_". $imagename) && unlink ($conf["imagesdir"] ."small_". $imagename)){
         echo $lang["bilder_datei_geloescht"]."<br>";
      	 $Statement = "DELETE FROM acme_bilder WHERE img_id = '" . $img_id . "'";
         $delete_result = dbquery($Statement);
         if ($delete_result){echo $lang["bilder_datei_entfernt"] . "<br>";}
         else {echo $lang["bilder_datei_nicht_entfernt"];}
         } 
      else {echo $lang["bilder_datei_nicht_geloescht"];}
      mysql_free_result($result);
   }
   img_browse($img_typ_id);
}

function img_typ_delete($img_typ_id){
   global $conf, $lang;

  	$Statement = "DELETE FROM acme_bilder_typs WHERE img_typ_id = '" . $img_typ_id . "'";
   $delete_result = dbquery($Statement);
   if ($delete_result){echo $lang["bilder_typ_delete_erfolgreich"];}
   else {echo $lang["bilder_typ_delete_fehlerhaft"];}
   img_typ_browse();
}

function img_add($tmpname, $realname, $realsize, $new_img_name, $new_img_description, $new_img_desc_long, $new_img_typ_id){
   global $conf, $lang;

   if ($realsize >= 180000) {
   	  echo $lang["bilder_upload_filesizeerror"];
   } else {
      if (is_uploaded_file($tmpname)) {
         echo "<br><br>";
         echo $lang["bilder_upload_move_rename"];
         echo "<br>";
         echo $lang["bilder_upload_copy"];
         
         $tmpimagename = $conf["imagesdir"] . "tmp_".$realname;
         copy ($tmpname, $tmpimagename);
         unlink ($tmpname);
         
         $image = new thumbnail($tmpimagename);
         $mix = get_img_typ_maxwidth($new_img_typ_id);
         $miy = get_img_typ_maxheight($new_img_typ_id);
         if ($mix > 0){$image->size_width($mix);}
         if ($miy > 0){$image->size_height($miy);}
         $imagename = $conf["imagesdir"] . $realname;
         if ($mix > 0 && $miy > 0){
            $image->save($imagename);
         } else {
           copy ($tmpimagename, $conf["imagesdir"] . $realname);
         }   
         
         $thumb = new thumbnail($tmpimagename);
         $thumb->size_width(60);
         $thumb->save($conf["imagesdir"] . "thumb_" . $realname);
         
         $small = new thumbnail($tmpimagename);
         $small->size_width(200);
         $small->save($conf["imagesdir"] . "small_". $realname);
         
         echo $lang["bilder_upload_copy_end"]."<br>";
         chmod ($conf["imagesdir"] . $realname, 0777);
         unlink ($tmpimagename);

         $Statement = "INSERT INTO acme_bilder SET ".
                              " img_name = '". $new_img_name . "', ".
                              " img_real_name = '". $realname ."', ".
                              " img_description = '". $new_img_description ."', ".
                              " img_desc_long  = '". $new_img_desc_long ."', ".
                              " img_typ_id  =  '". $new_img_typ_id ."', ".
                              " img_author_id =  '". $conf["author_id"]."'";
         $insert_result = dbquery($Statement);
         if ($insert_result){
         	echo $lang["bilder_upload_copy_finished"];
         } else {
         	echo $lang["bilder_upload_copy_break"];
               unlink ($conf["imagesdir"].$realname);
         }
      } else {
         echo $lang["bilder_upload_copy_attack"] . $realname;
	  }
   }
   img_browse($new_img_typ_id);
}

class thumbnail{
	var $img;

	function thumbnail($imgfile)	{
		//detect image format
		$this->img["format"]=ereg_replace(".*\.(.*)$","\\1",$imgfile);
		$this->img["format"]=strtoupper($this->img["format"]);
		if ($this->img["format"]=="JPG" || $this->img["format"]=="JPEG") {
			//JPEG
			$this->img["format"]="JPEG";
			$this->img["src"] = ImageCreateFromJPEG ($imgfile);
		} 
		elseif ($this->img["format"]=="PNG") {
			//PNG
			$this->img["format"]="PNG";
			$this->img["src"] = ImageCreateFromPNG ($imgfile);
		} 
		elseif ($this->img["format"]=="GIF") {
			//GIF
			$this->img["format"]="GIF";
			$this->img["src"] = ImageCreateFromGIF ($imgfile);
		} 
		elseif ($this->img["format"]=="WBMP") {
			//WBMP
			$this->img["format"]="WBMP";
			$this->img["src"] = ImageCreateFromWBMP ($imgfile);
		} 
		else {
			//DEFAULT
			echo "Not Supported File";
			exit();
		}
		@$this->img["width"] = imagesx($this->img["src"]);
		@$this->img["height"] = imagesy($this->img["src"]);
        @$this->img["height_thumb"]= $this->img["height"];
        @$this->img["width_thumb"] = $this->img["width"];
		//default quality jpeg
		$this->img["quality"]=75;
	}

	function size_height($size)	{
		if ($this->img["height"] > $size) {
       	   $this->img["height_thumb"]=$size;
      	   @$this->img["width_thumb"] = ($this->img["height_thumb"]/$this->img["height"])*$this->img["width"];
        }
	}

	function size_width($size)	{
		if ($this->img["width"] > $size) {
    		$this->img["width_thumb"]=$size;
            @$this->img["height_thumb"] = ($this->img["width_thumb"]/$this->img["width"])*$this->img["height"];
        }
	}

	function size_auto($size)	{
		if ($this->img["width"]>=$this->img["height"]) {
    	   $this->img["width_thumb"]=$size;
    	   @$this->img["height_thumb"] = ($this->img["width_thumb"]/$this->img["width"])*$this->img["height"];
		} else {
	       $this->img["height_thumb"]=$size;
    	   @$this->img["width_thumb"] = ($this->img["height_thumb"]/$this->img["height"])*$this->img["width"];
 		}
	}

	function jpeg_quality($quality=75)	{
		$this->img["quality"]=$quality;
	}

	function save($save="")	{
		if (!empty($save)) {
           $this->img["des"] = ImageCreateTrueColor($this->img["width_thumb"],$this->img["height_thumb"]);
           @imagecopyresized ($this->img["des"], $this->img["src"], 0, 0, 0, 0, $this->img["width_thumb"], $this->img["height_thumb"], $this->img["width"], $this->img["height"]);
           if ($this->img["format"]=="JPG" || $this->img["format"]=="JPEG") {
              imageJPEG($this->img["des"],"$save",$this->img["quality"]);
           } elseif ($this->img["format"]=="PNG")  {
              imagePNG($this->img["des"],"$save");
           } elseif ($this->img["format"]=="GIF")  {
              imageGIF($this->img["des"],"$save");
           } elseif ($this->img["format"]=="WBMP") {
              imageWBMP($this->img["des"],"$save");
           }
        }
     }   
}

function get_img_typ_name($img_typ_id){
   global $conf, $lang;
   
   $query = dbquery("select * from acme_bilder_typs where img_typ_id = '" . $img_typ_id . "'");
   if (mysql_num_rows($query) > 0 ) {
      $g_row = mysql_fetch_object($query);
      return $g_row->img_typ_name;
   }
}
function get_img_typ_maxheight($img_typ_id){
   global $conf, $lang;
   
   $query = dbquery("select img_typ_maxheight from acme_bilder_typs where img_typ_id = '" . $img_typ_id . "'");
   if (mysql_num_rows($query) > 0 ) {
      $g_row = mysql_fetch_object($query);
      return $g_row->img_typ_maxheight;
   }
}           
function get_img_typ_maxwidth($img_typ_id){
   global $conf, $lang;
   
   $query = dbquery("select img_typ_maxwidth from acme_bilder_typs where img_typ_id = '" . $img_typ_id . "'");
   if (mysql_num_rows($query) > 0 ) {
      $g_row = mysql_fetch_object($query);
      return $g_row->img_typ_maxwidth;
   }
}           
function count_img_from_typ($img_typ_id){
   global $conf, $lang;
   
   $query = dbquery("select img_id from acme_bilder where img_typ_id = '" . $img_typ_id . "'");
   return mysql_num_rows($query);
}      
function createsel_img_typ($select_name,$grouplist){
   global $conf, $lang;
   
   $grouplist=explode(":", $grouplist);
   $allgroups = dbquery("select * from acme_bilder_typs order by img_typ_name");
   echo "<select multiple size = \"5\" name=\"" . $select_name . "[]\">";
   if ( mysql_num_rows($allgroups) > 0 ) {
      while ( $g_row = mysql_fetch_object($allgroups) ) {
         echo "<option value=" . $g_row->img_typ_id;
         if (is_array($grouplist)){
            foreach ($grouplist as $value){
              if ( eregi ( $g_row->img_typ_id, $value ) ){echo " selected ";}
            }
         }
         echo ">" . $g_row->img_typ_name . "</option>";
      }
      mysql_free_result($allgroups);
   }
   echo "</select>";
   return;
}
function createsel_img_typ_parent($select_name,$id,$selfid="0"){
   global $conf, $lang;
   
   $allgroups = dbquery("select * from acme_bilder_typs where img_typ_parent_id = '' and img_typ_id <> ".$selfid." order by img_typ_name");
   echo "<select size = \"1\" name=\"" . $select_name . "\">";
   if (!isset($id)){echo "<option value=\"\" selected></option>";}
   else {echo "<option value=\"\" ></option>";}
   if ( mysql_num_rows($allgroups) > 0 ) {
      while ( $g_row = mysql_fetch_object($allgroups) ) {
         echo "<option value=" . $g_row->img_typ_id;
         if ( eregi ( $g_row->img_typ_id, $id ) ){ echo " selected ";}
         echo ">" . $g_row->img_typ_name . "</option>";
      }
      mysql_free_result($allgroups);
   }
   echo "</select>";
   return;
}
?>