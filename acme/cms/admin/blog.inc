<?php

include($conf["admbase"] . "/lang/blog." . $conf["lang"] . ".inc");

switch($action){
	case "blog_edit":
		blog_edit($blog_id);
		
      break;

	case "blog_update":
      blog_update($edit_blog_id, $edit_blog_name, $edit_blog_tpl, $edit_blog_img_small,$edit_blog_img_small_inactive,  $edit_blog_img_big, $edit_blog_top_bar, $edit_blog_left_bar, $edit_blog_right_bar, $edit_blog_foo_bar, $edit_blog_titel, $edit_blog_text);
		blog_browse();
		
      break;
      
	case "blog_new":
		blog_new($new_blog_name, $new_blog_tpl, $new_blog_img_small, $new_blog_img_small_inactive,  $new_blog_img_big, $new_blog_top_bar, $new_blog_left_bar, $new_blog_right_bar, $new_blog_foo_bar, $new_blog_titel, $new_blog_text);
		
      break;
      
   case "blog_insert":
      blog_insert($new_blog_name, $new_blog_tpl, $new_blog_img_small, $new_blog_img_small_inactive,  $new_blog_img_big, $new_blog_top_bar, $new_blog_left_bar, $new_blog_right_bar, $new_blog_foo_bar, $new_blog_titel, $new_blog_text);
      break;
     
	case "blog_delete":
      blog_delete($blog_id);
      blog_browse();
      
      break;

	case "blog_data_edit":
		blog_data_edit($blog_data_id, $edit_blog_data_headline, $edit_blog_data_content, $edit_blog_cat_id);
		
      break;

	case "blog_data_update":
      blog_data_update($blog_data_id, $edit_blog_data_headline, $edit_blog_data_content, $edit_blog_cat_id);
		blog_browse();
		
      break;
      
	case "blog_data_new":
		blog_data_new($blog_id, $new_blog_data_headline, $new_blog_data_content, $new_blog_cat_id);
		
      break;
      
   case "blog_data_insert":
      blog_data_insert($blog_id, $new_blog_data_headline, $new_blog_data_content, $new_blog_cat_id);
      blog_browse();
      
      break;
     
	case "blog_data_delete":
      blog_data_delete($blog_data_id);
      blog_browse();
      
      break;

	case "blog_cat_edit":
		blog_cat_edit($blog_cat_id, $edit_blog_cat_name, $edit_blog_cat_text);
      break;

	case "blog_cat_update":
      blog_cat_update($blog_cat_id, $edit_blog_cat_name, $edit_blog_cat_text);
		blog_browse();
      break;
      
	case "blog_cat_new":
		blog_cat_new($blog_id, $new_blog_cat_name, $new_blog_cat_text);
      break;
      
   case "blog_cat_insert":
      blog_cat_insert($blog_id, $new_blog_cat_name, $new_blog_cat_text);
      blog_browse();
      
      break;
     
	case "blog_cat_delete":
      blog_cat_delete($blog_cat_id);
      blog_browse();
      
      break;
         
   default:
      blog_browse();
      
      break;
}

function blog_data_edit($edit_blog_data_id, $edit_blog_data_headline, $edit_blog_data_content, $edit_blog_cat_id){
   global $conf, $lang;

   $result = dbquery("select * from acme_blog_data where blog_data_id=$edit_blog_data_id");
       if ($result)  {
          $acme_blog_data = mysql_fetch_object($result);
          echo "<h1>".$lang["blog_eintrag_bearbeiten"]."</h1>";
          echo "<form action=\"" . $conf["admp"] . "&section=blog&action=blog_data_update&blog_data_id=" . $acme_blog_data->blog_data_id . "\"  method=POST>";
          echo "<table class=\"reda_td\">";          
          echo "<tr><td>".$lang["blog_eintrag_titel"]."</td></tr>";
          echo "<tr><td><input name=edit_blog_data_headline size=70 maxlength=128 value=\"" . htmlspecialchars($acme_blog_data->blog_data_headline) . "\"></td></tr>";
          echo "<tr><td>".$lang["blog_kategorie"]."</td></tr>";
          echo "<tr><td>";
          createsel_blogcats("edit_blog_cat_id", $acme_blog_data->blog_cat_id, $acme_blog_data->blog_id);   
          echo "</td></tr>";
          echo "<tr><td>".$lang["blog_eintrag_inhalt"]."</td></tr>";
          echo "<tr><td><textarea name=\"edit_blog_data_content\" wrap=virtual rows=15 cols=75>" . htmlspecialchars($acme_blog_data->blog_data_content) . "</textarea></td>";
          echo "<tr><td><input type=submit name=add value=".$lang["blog_eintrag_speichern"]."></td></tr>";
          echo "</table>";
          echo "</form>";
          mysql_free_result($result);
          }

}
function blog_data_update($blog_data_id, $blog_data_headline, $blog_data_content, $blog_cat_id){
   global $conf, $lang;
   
   $Statement = "UPDATE acme_blog_data SET ".
                     "blog_data_headline = '". $blog_data_headline . "',".
                     "blog_cat_id = '". $blog_cat_id . "',".
                     "blog_data_content = '". $blog_data_content . "'".
                     " WHERE blog_data_id = '". $blog_data_id . "'";
   $update_result = dbquery($Statement);
   if($update_result){echo $lang["blog_eintrag_update_erfolgreich"];}
   else{echo $lang["blog_eintrag_update_fehlerhaft"];};
}

function blog_data_new($blog_id, $blog_data_headline, $blog_data_content) {
   global $conf, $lang;

   echo "<h1>".$lang["blog_eintrag_neu"]."</h1>";
   echo "<form action=\"" .  $conf["admp"] . "&section=blog&action=blog_data_insert\"  method=POST>";
   echo "<table class=\"reda_td\">";
   echo "<tr><td>".$lang["blog_eintrag_titel"]."<input type=\"hidden\" name=\"blog_id\" value=\"" . $blog_id . "\"></td></tr>";
   echo "<tr><td><input name=new_blog_data_headline size=70 maxlength=128 value=\"" . htmlspecialchars(stripslashes($blog_data_headline)) . "\"></td></tr>";
   echo "<tr><td>".$lang["blog_kategorie"]."</td></tr>";
   echo "<tr><td>";
   createsel_blogcats("new_blog_cat_id", $new_blog_cat_id, $blog_id);   
   echo "</td></tr>";
   echo "<tr><td>".$lang["blog_eintrag_inhalt"]."</td></tr>";
   echo "<tr><td><textarea name=\"new_blog_data_content\" wrap=virtual rows=15 cols=75>" . htmlspecialchars(stripslashes($blog_data_content)) . "</textarea></td>";
   echo "<tr><td><input type=submit name=add value=".$lang["blog_eintrag_speichern"]."></td></tr>";
   echo "</table>";
   echo "</form>";
}
function blog_data_insert($blog_id, $blog_data_headline, $blog_data_content, $blog_cat_id){
   global $conf, $lang;
   
   $Statement = "INSERT INTO acme_blog_data  (".
                          " blog_id, ".
                          " blog_data_date, ".
                          " blog_data_headline, ".
                          " blog_cat_id, ".                          
                          " blog_data_content ".
                          ")VALUES (".
                          "'" . $blog_id . "', ".
                          " NOW(), ".
                          "'" . $blog_data_headline ."',".
                          "'" . $blog_cat_id . "', ".                          
                          "'" . $blog_data_content."'".
                          ")";
   $insert_result = dbquery($Statement);
   if($insert_result){echo $lang["blog_eintrag_insert_erfolgreich"];}
   else{echo $lang["blog_eintrag_insert_fehlerhaft"];};
}

function blog_data_delete($blog_data_id) {
   global $conf, $lang;
   $delete_result = dbquery("delete from acme_blog_data where blog_data_id = '". $blog_data_id . "'");
   if($delete_result){echo $lang["blog_eintrag_delete_erfolgreich"];}
   else{echo $lang["blog_eintrag_delete_fehlerhaft"];};
}

function blog_cat_edit($edit_blog_cat_id, $edit_blog_cat_name, $edit_blog_cat_text){
   global $conf, $lang;

   $result = dbquery("select * from acme_blog_cat where blog_cat_id=$edit_blog_cat_id");
   if ($result)  {
      $acme_blog_cat = mysql_fetch_object($result);
      echo "<h1>".$lang["blog_kategorie_bearbeiten"]."</h1>";
      echo "<form action=\"" . $conf["admp"] . "&section=blog&action=blog_cat_update&blog_cat_id=" . $acme_blog_cat->blog_cat_id . "\"  method=POST>";
      echo "<table class=\"reda_td\">";          
      echo "<tr><td>".$lang["blog_kategorie_name"]."</td></tr>";
      echo "<tr><td><input name=edit_blog_cat_name size=70 maxlength=128 value=\"" . htmlspecialchars($acme_blog_cat->blog_cat_name) . "\"></td></tr>";
      echo "<tr><td>".$lang["blog_kategorie_text"] . "</td></tr>";
      echo "<tr><td><textarea name=\"edit_blog_cat_text\" wrap=virtual rows=15 cols=75>" . htmlspecialchars($acme_blog_cat->blog_cat_text) . "</textarea></td>";
      echo "<tr><td><input type=submit name=add value=".$lang["blog_kategorie_speichern"]."></td></tr>";
      echo "</table>";
      echo "</form>";
      mysql_free_result($result);
      }
}

function blog_cat_update($blog_cat_id, $blog_cat_name, $blog_cat_text){
   global $conf, $lang;
   
   $Statement = "UPDATE acme_blog_cat SET ".
                "blog_cat_name = '". $blog_cat_name . "',".
                "blog_cat_text = '". $blog_cat_text . "'".
                " WHERE blog_cat_id = '". $blog_cat_id . "'";
   $update_result = dbquery($Statement);
   if ($update_result){echo $lang["blog_kategorie_update_erfolgreich"];}
   else {echo $lang["blog_kategorie_update_fehlerhaft"];};
}

function blog_cat_new($blog_id, $blog_cat_name, $blog_cat_text) {
   global $conf, $lang;

   echo "<h1>".$lang["blog_kategorie_neu"]."</h1>";
   echo "<form action=\"" .  $conf["admp"] . "&section=blog&action=blog_cat_insert\"  method=POST>";
   echo "<table class=\"reda_td\">";
   echo "<tr><td>".$lang["blog_kategorie_name"]."<input type=\"hidden\" name=\"blog_id\" value=\"" . $blog_id . "\"></td></tr>";
   echo "<tr><td><input name=new_blog_cat_name size=70 maxlength=128 value=\"" . htmlspecialchars(stripslashes($blog_cat_name)) . "\"></td></tr>";
   echo "<tr><td>".$lang["blog_kategorie_text"]."</td></tr>";
   echo "<tr><td><textarea name=\"new_blog_cat_text\" wrap=virtual rows=15 cols=75>" . htmlspecialchars(stripslashes($blog_cat_text)) . "</textarea></td>";
   echo "<tr><td><input type=submit name=add value=".$lang["blog_kategorie_speichern"]."></td></tr>";
   echo "</table>";
   echo "</form>";
}
function blog_cat_insert($blog_id, $blog_cat_name, $blog_cat_text){
   global $conf, $lang;
   
   $Statement = "INSERT INTO acme_blog_cat  (".
                " blog_cat_name, ".
                " blog_cat_text, ".
                " blog_cat_blog_id ".
                ")VALUES (".
                "'" . $blog_cat_name . "', ".                          
                "'" . $blog_cat_text."', ".
                "'" . $blog_id . "' ".
                ")";
   $insert_result = dbquery($Statement);
   if($insert_result){echo $lang["blog_kategorie_insert_erfolgreich"];}
   else{echo $lang["blog_kategorie_insert_fehlerhaft"];};
}

function blog_cat_delete($blog_cat_id) {
   global $conf, $lang;
   $delete_result = dbquery("delete from acme_blog_cat where blog_cat_id = ". $blog_cat_id);
   $sub_delete_result = dbquery("update acme_blog_data set blog_cat_id = 0 where blog_cat_id = ". $blog_cat_id);
   if($delete_result && $sub_delete_result){echo $lang["blog_kategorie_delete_erfolgreich"];}
   else{echo $lang["blog_kategorie_delete_fehlerhaft"];};
}

function blog_browse() {
   global $conf, $lang;

   echo "<h1>".$lang["blog_verwaltung"]."</h1>";
   if (acl_check("insert", $conf["author_groups"], $conf["author_id"], "blog", 0) == 1) {
      echo "<a href=\"" . $conf["admp"] . "&section=blog&action=blog_new\">Neuen Blog anlegen</a>";
   }
   echo "<table class=\"reda_td\">";
   echo "<tr><td>".$lang["blog_name"]."</td><td width=\"30\"> </td><td width=\"30\"> </td><td width=\"30\"> </td></tr>";
   $result = dbquery("select * from acme_blog order by blog_name");
   if ( mysql_num_rows($result) > 0 )           {
      while ($row = mysql_fetch_object($result))              {
         echo "<tr>";
         echo "<td>".$row->blog_name."</td>";
         echo "<td>";
         if (acl_check("insert", $conf["author_groups"], $conf["author_id"], "blog", $row->blog_id) == 1) {
            echo "<a href=\"" . $conf["admp"] . "&section=blog&action=blog_data_new&blog_id=" . $row->blog_id . "\"><img src=\"" . $conf["images_admin"] . "icon_nbe.png\" width=\"25\" height=\"25\"></a>";
         }else{
         	echo "&nbsp;";
         }	
         echo "</td>";         
         echo "<td>";
         if (acl_check("edit", $conf["author_groups"], $conf["author_id"], "blog", $row->blog_id) == 1) { 
            echo "<a href=\"" . $conf["admp"] . "&section=blog&action=blog_edit&blog_id=" . $row->blog_id . "\"><img src=\"" . $conf["images_admin"] . "icon_edit.png\" width=\"25\" height=\"25\"></a>";
         }else{
         	echo "&nbsp;";
         }	
         echo "</td>";
         echo "<td>";
         if (acl_check("delete", $conf["author_groups"], $conf["author_id"], "blog", $row->blog_id) == 1) {
            echo "<a href=\"" . $conf["admp"] . "&section=blog&action=blog_delete&blog_id=" . $row->blog_id . "\"><img src=\"" . $conf["images_admin"] . "icon_delete.png\" width=\"25\" height=\"25\"></a>";
         }else{
         	echo "&nbsp;";
         }	
         echo "</td>";
         echo "<td>";	
         if (acl_check("rights", $conf["author_groups"], $conf["author_id"], "blog", $row->blog_id) == 1){
         	echo "<a href=" . $conf["admp"] . "&section=rights&modul_name=blog&modul_id=".$row->blog_id."><img src=\"" . $conf["images_admin"] . "icon_rights.png\" width=\"25\" height=\"25\"></a>";
         }else{
         	echo "&nbsp;";
         }	
         echo "</td>";
         echo "</tr>";
      }
   mysql_free_result($result);
   }
   echo "</table>";
}

function blog_edit($blog_id) {
   global $conf, $lang;
   
   $blog_result = dbquery("select * from acme_blog where blog_id=$blog_id");
   if ($blog_result) {
      $acme_blog = mysql_fetch_object($blog_result);
      echo "<h1>".$lang["blog_bearbeiten"]."</h1>\n";
      if (acl_check("insert", $conf["author_groups"], $conf["author_id"], "blog", $blog_id) == 1) {
         echo "<a href=\"" . $conf["admp"] . "&section=blog&action=blog_data_new&blog_id=" . $acme_blog->blog_id . "\">Neuer Eintrag</a>\n|";
      }         
      if (acl_check("insert", $conf["author_groups"], $conf["author_id"], "blog", $blog_id) == 1) {
         echo "<a href=\"" . $conf["admp"] . "&section=blog&action=blog_cat_new&blog_id=" . $acme_blog->blog_id . "\">Neue Kategorie</a>\n";
      }                
      echo "<form action=\"" . $conf["admp"] . "&section=blog&action=blog_update&edit_blog_id=" . $acme_blog->blog_id . "\" method=\"POST\">\n";
      echo "<table class=\"reda_td\">\n";
      echo "<tr><td colspan = 4>".$lang["blog_name"]."</td></tr>\n";
      echo "<tr><td colspan = 4><input name=\"edit_blog_name\" size=\"30\" maxlength=\"128\" value=\"" . htmlspecialchars($acme_blog->blog_name) . "\"></td></tr>";
      echo "<tr><td>".$lang["blog_tpl"]."</td><td>".$lang["blog_logo_gross"]."</td><td>".$lang["blog_logo_klein"]."</td><td>".$lang["blog_logo_klein_inactive"]."</td></tr>";
      echo "<tr><td>";
      createsel_tpl("edit_blog_tpl",  $acme_blog->blog_tpl);
      echo "</td>";
      echo "<td>";
      createsel_img("edit_blog_img_small",  $acme_blog->blog_img_small);
      echo "</td>";
      echo "<td>";
      createsel_img("edit_blog_img_small_inactive",  $acme_blog->blog_img_small_inactive);
      echo "</td>";
      echo "<td>";
      createsel_img("edit_blog_img_big",  $acme_blog->blog_img_big);
      echo "</td>";
      echo "</tr>\n";
      echo "<tr><td>".$lang["blog_bar_left"]."</td><td>".$lang["blog_bar_right"]."</td><td>".$lang["blog_bar_top"]."</td><td>".$lang["blog_bar_bottom"]."</td></tr>";
      echo "<tr>";
      echo "<td>";
      createsel_bar("edit_blog_left_bar", $acme_blog->blog_left_bar);
      echo "</td>";
      echo "<td>";
      createsel_bar("edit_blog_right_bar",  $acme_blog->blog_right_bar);
      echo "</td>";
      echo "<td>";
      createsel_bar("edit_blog_top_bar",  $acme_blog->blog_top_bar);
      echo "</td>";
      echo "<td>";
      createsel_bar("edit_blog_foo_bar",  $acme_blog->blog_foo_bar);
      echo "</td>";
      echo "</tr>\n";
      echo "<tr><td colspan = \"4\">".$lang["blog_name"]."</td></tr>\n";         
      echo "<tr><td colspan = \"4\"><input name=\"edit_blog_titel\" size=\"30\" maxlength=\"200\" value=\"" . htmlspecialchars($acme_blog->blog_titel) . "\"></td>";
      echo "<tr><td colspan = \"4\">".$lang["blog_inhalt"]."</td></tr>";
      echo "<tr><td colspan = \"4\"><textarea name=\"edit_blog_text\" wrap=virtual rows=15 cols=75>" . htmlspecialchars($acme_blog->blog_text) . "</textarea></td>";      
      echo "</tr>\n";
      echo "<tr><td colspan=\"4\"><input type=submit name=add value=".$lang["blog_speichern"]."></td></tr>\n";
      echo "</form>\n";
      echo "<tr><td colspan = 4>".$lang["blog_kategorien"]."</td></tr>";      
      $data_result = dbquery("select * from acme_blog_cat where blog_cat_blog_id='" . $acme_blog->blog_id . "' order by blog_cat_name");
      if ( mysql_num_rows($data_result) > 0 )  {
          echo "<tr><td>".$lang["blog_kategorie_name"]."</td><td>&nbsp;</td><td width=\"30\"></td><td width=\"30\"></td></tr>\n";
          while ($acme_blog_cat = mysql_fetch_object($data_result))  {
             echo "<tr>";
             echo "<td>" . $acme_blog_cat->blog_cat_name . "</td>";
             echo "<td>&nbsp;</td>";
             if (acl_check("edit", $conf["author_groups"], $conf["author_id"], "blog", $blog_id) == 1) {
                echo "<td><a href=\"" . $conf["admp"] . "&section=blog&action=blog_cat_edit&blog_cat_id=" . $acme_blog_cat->blog_cat_id . "\"><img src=\"" . $conf["images_admin"] . "icon_edit.png\" width=\"25\" height=\"25\" alt=\"bearbeiten\"></a></td>";
             }else{echo "<td></td>";}
             if (acl_check("delete", $conf["author_groups"], $conf["author_id"], "blog", $blog_id) == 1) {
                echo "<td><a href=\"" . $conf["admp"] . "&section=blog&action=blog_cat_delete&blog_cat_id=" . $acme_blog_cat->blog_cat_id . "\"><img src=\"" . $conf["images_admin"] . "icon_delete.png\" width=\"25\" height=\"25\" alt=\"l&ouml;schen\"></a></td>";
             }else{echo "<td></td>";}   
             echo "</tr>\n";
         }
         mysql_free_result($data_result);
      } 
      echo "<tr><td colspan = 4>".$lang["blog_eintraege"]."</td></tr>";
      $data_result = dbquery("select * from acme_blog_data where blog_id='" . $blog_id . "' order by blog_data_date DESC");
      if ( mysql_num_rows($data_result) > 0 )  {
          echo "<tr><td>".$lang["blog_eintrag_titel"]."</td><td>".$lang["blog_eintrag_datum"]."</td><td width=\"30\"></td><td width=\"30\"></td></tr>\n";
          while ($acme_blog_data = mysql_fetch_object($data_result))  {
             echo "<tr>";
             echo "<td>" . $acme_blog_data->blog_data_headline . "</td>";
             echo "<td>" . mydate2datetime($acme_blog_data->blog_data_date) . "</td>";
             if (acl_check("edit", $conf["author_groups"], $conf["author_id"], "blog", $blog_id) == 1) {
                echo "<td><a href=\"" . $conf["admp"] . "&section=blog&action=blog_data_edit&blog_data_id=" . $acme_blog_data->blog_data_id . "\"><img src=\"" . $conf["images_admin"] . "icon_edit.png\" width=\"25\" height=\"25\" alt=\"bearbeiten\"></a></td>";
             }else{echo "<td></td>";}   
             if (acl_check("delete", $conf["author_groups"], $conf["author_id"], "blog", $blog_id) == 1) {
                echo "<td><a href=\"" . $conf["admp"] . "&section=blog&action=blog_data_delete&blog_data_id=" . $acme_blog_data->blog_data_id . "\"><img src=\"" . $conf["images_admin"] . "icon_delete.png\" width=\"25\" height=\"25\" alt=\"l&ouml;schen\"></a></td>";
             }else{echo "<td></td>";}   
             echo "</tr>\n";
         }
         mysql_free_result($data_result);
      } 
      echo "</table>\n";
      mysql_free_result($blog_result);
   }
}   

function blog_update($blog_id, $blog_name, $blog_tpl, $blog_img_small,$blog_img_small_inactive,  $blog_img_big, $blog_top_bar, $blog_left_bar, $blog_right_bar, $blog_foo_bar, $blog_titel, $blog_text){
   global $conf, $lang;
   
   $Statement = "UPDATE acme_blog SET ".
                           " blog_name = '" . $blog_name . "', ".
                           " blog_tpl = '" . $blog_tpl . "', ".
                           " blog_img_small = '" . $blog_img_small . "', ".
                           " blog_img_small_inactive = '" . $blog_img_small_inactive . "', ".
                           " blog_modify_date = NOW(). ".
                           " blog_img_big = '" . $blog_img_big. "', ".
                           " blog_top_bar = '" . $blog_top_bar. "', ".
                           " blog_left_bar = '" . $blog_left_bar . "', ".
                           " blog_right_bar = '" . $blog_right_bar . "', ".
                           " blog_foo_bar = '" . $blog_foo_bar . "', ".                                                                                                                                                                  
                           " blog_titel = '". $blog_titel . "', ".
                           " blog_text = '" . $blog_text . "' ".
                           " WHERE blog_id = '". $blog_id . "'";
   $update_result = dbquery($Statement);
   if($update_result){echo $lang["blog_update_erfolgreich"];}
   else{echo $lang["blog_update_fehlerhaft"];};
}

function blog_new() {
   global $conf, $lang;
   
   echo "<h1>".$lang["blog_neu"]."</h1>";
   echo "<form action=\"" . $conf["admp"] . "&section=blog&action=blog_insert\" method=\"POST\">";
   echo "<table class=\"reda_td\">";
   echo "<tr><td colspan = 4>".$lang["blog_name"]."</td></tr>";
   echo "<tr><td colspan = 4><input name=\"new_blog_name\" size=\"30\" maxlength=\"128\" value=\"" . $new_blog_name . "\"></td></tr>";
   echo "<tr><td>".$lang["blog_tpl"]."</td><td>".$lang["blog_logo_gross"]."</td><td>".$lang["blog_logo_klein"]."</td><td>".$lang["blog_logo_klein_inactive"]."</td></tr>";
   echo "<td>";
   createsel_tpl("new_blog_tpl",  $new_blog_tpl);
   echo "</td>";
   echo "<td colspan=1>";
   createsel_img("new_blog_img_big",  $new_img_big);
   echo "</td>";
   echo "<td colspan=1>";
   createsel_img("new_blog_img_small",  $new_img_small);
   echo "</td>";
   echo "<td colspan=1>";
   createsel_img("new_blog_img_small_inactive",  $new_img_small_inactive);
   echo "</td>";
   echo "</tr>";
   echo "<tr><td>".$lang["blog_bar_left"]."</td><td>".$lang["blog_bar_right"]."</td><td>".$lang["blog_bar_top"]."</td><td>".$lang["blog_bar_bottom"]."</td></tr>";
   echo "<tr>";
   echo "<td>";
   createsel_bar("new_blog_left_bar", $new_blog_left_bar);
   echo "</td>";
   echo "<td>";
   createsel_bar("new_blog_right_bar",  $new_blog_right_bar);
   echo "<td>";
   echo "<td>";
   createsel_bar("new_blog_top_bar",  $new_blog_top_bar);
   echo "</td>";
   echo "<td>";
   createsel_bar("new_blog_foo_bar",  $new_blog_foo_bar);
   echo "</td>";
   echo "</tr>";
   echo "<tr><td colspan = \"4\">".$lang["blog_name"]."</td></tr>";   
   echo "<tr><td colspan = \"4\"><input name=\"new_blog_titel\" size=\"30\" maxlength=\"200\" value=\"" . htmlspecialchars(stripslashes($new_blog_titel)) . "\"></td></tr>";
   echo "<tr><td colspan = \"4\">".$lang["blog_inhalt"]."</td></tr>";   
   echo "<tr><td colspan = \"4\"><textarea name=\"new_blog_text\" wrap=virtual rows=15 cols=75>" . htmlspecialchars(stripslashes($new_blog_text)) . "</textarea></td></tr>";      
   echo "<tr>";            
   echo "<tr><td colspan = \"4\"><input type=submit name=add value=".$lang["blog_speichern"]."></td></tr>";
   echo "</table>";
   echo "</form>";
}   
   
function blog_insert($blog_name, $blog_tpl, $blog_img_small,$blog_img_small_inactive,  $blog_img_big, $blog_top_bar, $blog_left_bar, $blog_right_bar, $blog_foo_bar, $blog_titel, $blog_text){
   global $conf, $lang;
   
   $Statement = "INSERT INTO acme_blog  (".
                           " blog_name , ".
                           " blog_tpl  , ".
                           " blog_img_small , ".
                           " blog_img_small_inactive , ".
                           " blog_img_big  , ".
                           " blog_top_bar  , ".
                           " blog_left_bar  , ".
                           " blog_right_bar , ".
                           " blog_foo_bar , ".                                                                                                                                                                  
                           " blog_titel ,".
                           " blog_text  ".
                           " blog_author_id  ".
                           " blog_create_date  ".
                           " blog_modify_date  ".
                           " ) VALUES ( ".
                           " '" . $blog_name . "', ".
                           " '" . $blog_tpl . "', ".
                           " '" . $blog_img_small . "', ".
                           " '" . $blog_img_small_inactive . "', ".
                           " '" . $blog_img_big. "', ".
                           " '" . $blog_top_bar. "', ".
                           " '" . $blog_left_bar . "', ".
                           " '" . $blog_right_bar . "', ".
                           " '" . $blog_foo_bar . "', ".                                                                                                                                                                  
                           " '" . $blog_titel . "', ".
                           " '" . $blog_text . "'," .
                           " '". $conf["author_id"] .  "',".
                           " NOW(),  ".
                           " NOW()) ";
   echo $Statement;                           
   $edit_result = dbquery($Statement);
   if ($edit_result){
      acl_user_set($conf["author_id"], "blog", mysql_insert_id(), "Y", "Y", "Y", "Y");
      echo $lang["blog_update_erfolgreich"];
   }
   else{echo $lang["blog_update_fehlerhaft"];};
}



function blog_delete($delete_id){
   global $conf, $lang;
   
   $delete_statement1 ="delete from acme_blog_data where blog_id = ". $delete_id;
   $delete_result1 = dbquery($delete_statement1);
   if ($delete_result1){
      $delete_statement2 ="delete from acme_blog where blog_id = ". $delete_id;
      $delete_result2 = dbquery($delete_statement2);
   }
   if($delete_result1 && $delete_result2){
   	acl_delete("blog", $delete_id);
   	echo $lang["blog_delete_erfolgreich"];}
   else{echo $lang["blog_delete_fehlerhaft"];};
}
function createsel_blogcats($select_name,$grouplist, $blog_id)
{
   global $conf, $lang;
   $allgroups = dbquery("select * from acme_blog_cat where blog_cat_blog_id = '".$blog_id."' order by blog_cat_name");
   echo "<select size = \"1\" name=\"" . $select_name . "\">";
   if ( mysql_num_rows($allgroups) > 0 ) {
      while ( $g_row = mysql_fetch_object($allgroups) ) {
         echo "<option value=" . $g_row->blog_cat_id;
         if ( eregi ( $g_row->blog_cat_id, $grouplist ) ){ echo " selected ";}
         echo ">" . $g_row->blog_cat_name . "</option>";
      }
      mysql_free_result($allgroups);
   }
   echo "</select>";
   return;
}
?>
