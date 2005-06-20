<?php

include($conf["admbase"] . "/lang/gaestebuch." . $conf["lang"] . ".inc");

switch($action)
{
   case "edit":
      gaestebuchedit($edit_gb_id, $edit_gb_name, $edit_gb_img_small, $edit_gb_img_small_inactive, $edit_gb_img_big, $edit_gb_text, $edit_gb_left_bar, $edit_gb_right_bar, $edit_gb_top_bar, $edit_gb_foo_bar);
      break;
   case "new":
      gaestebuchnew($new_gb_name, $new_gb_img_small, $new_gb_img_small_inactive, $new_gb_img_big, $new_gb_text, $new_gb_left_bar, $new_gb_right_bar, $new_gb_top_bar, $new_gb_foo_bar);
      break;
   case "add":
      gaestebuchadd($new_gb_name, $new_gb_img_small, $new_gb_img_small_inactive, $new_gb_img_big, $new_gb_text, $new_gb_left_bar, $new_gb_right_bar, $new_gb_top_bar, $new_gb_foo_bar);
      gaestebuchbrowse();
      break;
   case "update":
      gaestebuchupdate($edit_gb_id, $edit_gb_name, $edit_gb_img_small, $edit_gb_img_small_inactive, $edit_gb_img_big, $edit_gb_text, $edit_gb_left_bar, $edit_gb_right_bar, $edit_gb_top_bar, $edit_gb_foo_bar);
      gaestebuchbrowse();
      break;
   case "delete":
      gaestebuchdelete($delete_id);
      gaestebuchbrowse();       
      break;
   case "entrys":
      gaestebuchentrys($gb_id, $gb_page);   
      break;
   case "entrycomment":
     gaestebuchentrycomment($gb_id, $gb_page, $entry_id);
     break;
   case "entrywritecomment":
     gaestebuchentrywritecomment($gb_id, $entry_id, $entry_comment);
     gaestebuchentrys($gb_id, $gb_page);      
     break;   
   case "entryblock":
      gaestebuchentryblock($gb_id, $entry_id);
      gaestebuchentrys($gb_id, $gb_page);      
      break;
   case "entryunblock":
      gaestebuchentryunblock($gb_id, $entry_id);
      gaestebuchentrys($gb_id, $gb_page);      
      break;      
   case "entrydelete":
      gaestebuchentrydelete($gb_id, $entry_id);
      gaestebuchentrys($gb_id, $gb_page);      
      break;      
   default:
      gaestebuchbrowse();       
      break;
}

function gaestebuchentrycomment($gb_id, $gb_page, $entry_id){
   global $conf, $lang;

   $query = dbquery("SELECT * FROM ".$conf["db_namespace"]."gb_entrys where entry_id = ".$entry_id);
   $fetch = mysql_fetch_array($query);   
   echo "<h1>".$lang["gaestebuch_kommentar_eintragen"]."</h1>";
   echo "<form name = gb_comment_new action=\"" .  $conf["admp"] . "&section=gaestebuch&action=entrywritecomment&gb_id=".$gb_id . "&gb_page=".$gb_page."&entry_id=".$entry_id."\"  method=POST>";
   echo "<table class=\"reda_td\">";
   echo "<textarea name=\"entry_comment\" wrap=virtual rows=15 cols=75>" . htmlspecialchars(stripslashes($fetch[entry_comment])) . "</textarea></td>";
   echo "<tr><td><input type=submit name=add value=speichern></td></tr>";
   echo "</table>";
   echo "</form>";
}

function gaestebuchentrywritecomment($gb_id, $entry_id, $comment){
   global $conf, $lang;
   
   $query = dbquery("update ".$conf["db_namespace"]."gb_entrys set entry_comment = '" . $comment . "' where entry_id = ".$entry_id);
}      

function gaestebuchentryblock($gb_id, $entry_id){
   global $conf, $lang;
   
   $query = dbquery("update ".$conf["db_namespace"]."gb_entrys set entry_blocked = 'Y' where entry_id = ". $entry_id);
}      

function gaestebuchentryunblock($gb_id, $entry_id){
   global $conf, $lang;
   
   $query = dbquery("update ".$conf["db_namespace"]."gb_entrys set entry_blocked = 'N' where entry_id = ". $entry_id);
}      
function gaestebuchentrydelete($gb_id, $entry_id){
   global $conf, $lang;
   
   $query = dbquery("delete from ".$conf["db_namespace"]."gb_entrys where entry_id = ". $entry_id);
} 
function gaestebuchentrys($gb_id, $gb_page){
   global $conf, $lang;

   $headresult = dbquery("select * from ".$conf["db_namespace"]."gb where gb_id = ".$gb_id."");
   if ( mysql_num_rows($headresult) > 0 )           {
      while ($row = mysql_fetch_object($headresult))              {
         echo "<h1>".$row->gb_name."</h1>";
      }
   }      

   
   $gb_ppp = 10;
   if(empty($gb_page)) {$gb_page = 1;}
   $limitfrom = ($gb_page * $gb_ppp) - $gb_ppp;
   $limitto   = $gb_ppp;

   $num   = mysql_num_rows(dbquery("SELECT * FROM ".$conf["db_namespace"]."gb_entrys where gb_id= ". $gb_id ." ORDER BY entry_id DESC"));

   if ($num > $limitto)   {
      $seiten = intval($num / $limitto);
      if ($num % $limitto) {$seiten++;}
   }
   
   if($gb_page > 1)                {$prev = $gb_page - 1;}
   if(($num / $gb_ppp) > $gb_page) {$next = $gb_page + 1;}

   if (isset($prev)){echo "<a href=\"" . $conf["admp"] . "&section=gaestebuch&action=entrys&gb_id=" . $gb_id . "&gb_page=" . $prev . "\">zur&uuml;ck</a> ";}
   echo "Seite: ".$gb_page;
   if (isset($next)){echo "<a href=\"" . $conf["admp"] . "&section=gaestebuch&action=entrys&gb_id=" . $gb_id . "&gb_page=" . $next . "\">weiter</a>";}

   $query = dbquery("SELECT * FROM ".$conf["db_namespace"]."gb_entrys where gb_id= ". $gb_id ." ORDER BY entry_id DESC  LIMIT $limitfrom, $limitto");
   echo "<table class=\"reda_td\">\n";
   echo "<tr><td colspan = 7>".$lang["gaestebuch_eintraege"]."</td></tr>";
   while($fetch = mysql_fetch_array($query)) {
      echo "<tr><td colspan = 7><hr></td></tr>";
      if($fetch["poster_url"] != "--") {
         $fetched_url = $fetch["poster_url"];
      }
      else{
         $fetched_url = "";
      }
      if($fetch["poster_email"] != "--"){
         $fetched_mail = $fetch["poster_email"];
      }
      else{
         $fetched_mail = "";
      }
      if($fetch["entry_comment"] == "--"){
         $fetched_comment = "";
      }
      else{
         $fetched_comment = $fetch["entry_comment"];
      }
      echo "<tr>";
      echo "<td>poster</td>";
      echo "<td>poster_mail</td>";
      echo "<td>poster_url</td>";
      echo "<td>post_date</td>";
      echo "<td>post_time</td>";
      echo "<td>poster_ip</td>";
      echo "<td>hostname</td>";
      echo "</tr>";
      echo "<tr>";
      echo "<td>".$fetch["entry_poster"]."</td>";
      echo "<td>".$fetched_mail."</td>";
      echo "<td>".$fetched_url."</td>";
      echo "<td>".$fetch["entry_date"]."</td>";
      echo "<td>".$fetch["entry_time"]."</td>";
      echo "<td>".$fetch["poster_ip"]."</td>";
      echo "<td>".$fetch["poster_hostname"]."</td>";
      echo "</tr>";
      echo "<tr>";
      echo "<td colspan = 4>content</td>";
      echo "<td colspan = 3>comment</td>";
      echo "</tr>";
      echo "<tr>";
      echo "<td colspan = 4>".nl2br($fetch["entry_content"])."</td>";
      echo "<td colspan = 3>".nl2br($fetched_comment)."</td>";
      echo "</tr>";
      echo "<tr>";
      echo "<td colspan = 4>";
      if ($fetch["entry_blocked"] == "N") {echo "<a href=\"" . $conf["admp"] . "&section=gaestebuch&action=entryblock&gb_id=" .   $gb_id . "&entry_id=" . $fetch["entry_id"] . "&gb_page=" . $gb_page . "\">". $lang["gaestebuch_block_entry"]. "</a> ";}
      if ($fetch["entry_blocked"] == "Y") {echo "<a href=\"" . $conf["admp"] . "&section=gaestebuch&action=entryunblock&gb_id=" . $gb_id . "&entry_id=" . $fetch["entry_id"] . "&gb_page=" . $gb_page . "\">". $lang["gaestebuch_unblock_entry"]."</a> ";}
      echo "<a href=\"" . $conf["admp"] . "&section=gaestebuch&action=entrydelete&gb_id=" . $gb_id . "&entry_id=" . $fetch["entry_id"] . "&gb_page=" . $gb_page . "\">". $lang["gaestebuch_delete_entry"]."</a> ";
      echo "</td>";
      echo "<td colspan = 3>";
      echo "<a href=\"" . $conf["admp"] . "&section=gaestebuch&action=entrycomment&gb_id=" . $gb_id . "&entry_id=" . $fetch["entry_id"] . "&gb_page=" . $gb_page . "\">comment entry</a> ";
      echo "</td>";
      echo "</tr>";
   }   
}      

function gaestebuchadd($new_gb_name, $new_gb_img_small, $new_gb_img_small_inactive, $new_gb_img_big, $new_gb_text, $new_gb_left_bar, $new_gb_right_bar, $new_gb_top_bar, $new_gb_foo_bar){
   global $conf, $lang;

   $Statement = "INSERT INTO ".$conf["db_namespace"]."gb SET".
                " gb_name = '". $new_gb_name . "',".
                " gb_img_small = '". $new_gb_img_small . "',".
                " gb_img_small_inactive = '". $new_gb_img_small_inactive . "',".                
                " gb_img_big = '". $new_gb_img_big . "',".
                " gb_top_bar = '". $new_gb_top_bar . "',".
                " gb_foo_bar = '". $new_gb_foo_bar . "',".
                " gb_right_bar = '". $new_gb_right_bar . "',".
                " gb_left_bar = '". $new_gb_left_bar . "',".
                " gb_text = '" . $new_gb_text ."'";
   $my_result = dbquery($Statement);
   if ($my_result) {
   	echo $lang["gaestebuch_insert_erfolgreich"];
   	$modulid = mysql_insert_id();
   	acl_user_set($conf["author_id"], "gaestebuch", $modulid, "Y", "Y", "Y", "Y");
   	acl_group_set($conf["author_groups"], "gaestebuch", $modulid, "Y", "Y", "Y", "Y");
   	}
   else            {echo $lang["gaestebuch_insert_fehlerhaft"];}
}
function gaestebuchupdate($edit_gb_id, $edit_gb_name, $edit_gb_img_small, $edit_gb_img_small_inactive, $edit_gb_img_big, $edit_gb_text, $edit_gb_left_bar, $edit_gb_right_bar, $edit_gb_top_bar, $edit_gb_foo_bar){
   global $conf, $lang;
              
   $Statement = "UPDATE ".$conf["db_namespace"]."gb SET".
                " gb_name = '". $edit_gb_name . "',".
                " gb_text = '". $edit_gb_text . "',".
                " gb_img_small = '". $edit_gb_img_small . "',".
                " gb_img_small_inactive = '". $edit_gb_img_small_inactive . "',".                
                " gb_top_bar = '". $edit_gb_top_bar . "',".
                " gb_foo_bar = '". $edit_gb_foo_bar . "',".
                " gb_right_bar = '". $edit_gb_right_bar . "',".
                " gb_left_bar = '". $edit_gb_left_bar . "',".
                " gb_img_big = '". $edit_gb_img_big . "' ".
                " WHERE gb_id = '". $edit_gb_id . "'";
   $my_result = dbquery($Statement);
   if ($my_result) {echo $lang["gaestebuch_update_erfolgreich"];}
  else            {echo $lang["gaestebuch_update_fehlerhaft"];}
}
function gaestebuchdelete($delete_id){
   global $conf, $lang;

   $my_result = dbquery("delete from ".$conf["db_namespace"]."gb_entrys where gb_id = '". $delete_id . "'");   
   
   if ($my_result) {
      $my_result1 = dbquery("delete from ".$conf["db_namespace"]."gb where gb_id = '". $delete_id . "'");
	  if ($my_result1) {
	     echo $lang["gaestebuch_delete_erfolgreich"];
	  }   
   	}
   else            {echo $lang["gaestebuch_delete_fehlerhaft"];}
}

function gaestebuchbrowse(){
   global $conf, $lang;

   echo "<h1>".$lang["gaestebuch_verwaltung"]."</h1>\n";
   if (acl_check("insert", $conf["author_groups"], $conf["author_id"], "gaestebuch", 0) == 1) {
      echo "<a href=\"". $conf["admp"] . "&section=gaestebuch&action=new\">".$lang["gaestebuch_anlegen"]."</a>\n";
   }
   echo "<table class=\"reda_td\">\n";
   echo "<th><tr><td>".$lang["gaestebuch_name"]."</td><td> </td><td> </td><td> </td></tr></th>\n";
   $result = dbquery("select * from ".$conf["db_namespace"]."gb order by gb_name");
   if ( mysql_num_rows($result) > 0 )           {
      while ($row = mysql_fetch_object($result))              {
         echo "<tr>";
         echo "<td>".$row->gb_name."</td>";
         echo "<td><a href=\"" . $conf["admp"] . "&section=gaestebuch&action=entrys&gb_id=" . $row->gb_id . "\"><img src=\"" . $conf["images_admin"] . "icon_nbe.png\" width=\"25\" height=\"25\"></a></td>";
         echo "<td>";
         if (acl_check("edit", $conf["author_groups"], $conf["author_id"], "gaestebuch", $row->gb_id) == 1) {
            echo "<a href=\"" . $conf["admp"] . "&section=gaestebuch&action=edit&edit_gb_id=" . $row->gb_id . "\"><img src=\"" . $conf["images_admin"] . "icon_edit.png\" width=\"25\" height=\"25\"></a>";
         }
         echo "</td>";
         echo "<td>";
         if (acl_check("delete", $conf["author_groups"], $conf["author_id"], "gaestebuch", $row->gb_id) == 1) { 
            echo "<a href=\"" . $conf["admp"] . "&section=gaestebuch&action=delete&delte_id=" . $row->gb_id . "\"><img src=\"" . $conf["images_admin"] . "icon_delete.png\" width=\"25\" height=\"25\"></a>";
         }
         echo "</td>";
         echo "</tr>";
      }
   mysql_free_result($result);
   }
   echo "</table>";
}      
function gaestebuchnew($new_gb_name, $new_gb_img_small, $new_gb_img_small_inactive, $new_gb_img_big, $new_gb_text, $new_gb_left_bar, $new_gb_right_bar, $new_gb_top_bar, $new_gb_foo_bar){
   global $conf, $lang;

   echo "<h1>".$lang["gaestebuch_anlegen"]."</h1>";
   echo "<form name = gbnew action=\"" . $conf["admp"] . "&section=gaestebuch&action=add\" ENCTYPE=\"multipart/form-data\" method=\"POST\">";
   echo "<table  class=\"reda_td\">";
   echo "<tr><td colspan=5>".$lang["gaestebuch_name"]."</td></tr>";
   echo "<tr>";
   echo "<td colspan=5><input name=new_gb_name size=45 maxlength=59 value = \"" . htmlspecialchars(stripslashes($new_gb_name)) . "\"></td>";
   echo "</tr>";
   echo "<tr><td>".$lang["gaestebuch_logo_klein"]."</td><td>".$lang["gaestebuch_logo_klein_inactive"]."</td><td>".$lang["gaestebuch_logo_gross"]."</td><td>&nbsp;</td><td>&nbsp;</td></tr>";
   echo "<tr>";
   echo "<td colspan=1>";
   createsel_img("new_gb_img_small",  $new_gb_img_small);
   echo "</td>";
   echo "<td colspan=1>";
   createsel_img("new_gb_img_small_inactive",  $new_gb_img_small_inactive);
   echo "</td>";
   echo "<td colspan=1>";
   createsel_img("new_gb_img_big",  $new_gb_img_big);
   echo "</td>";
   echo "<td>&nbsp;</td><td>&nbsp;</td>";
   echo "</tr>";
   echo "<tr><td colspan=5>&nbsp;</td></tr>\n";   
   echo "<tr><td>".$lang["gaestebuch_frame"]."</td><td>".$lang["gaestebuch_bar_left"]."</td><td>".$lang["gaestebuch_bar_right"]."</td><td>".$lang["gaestebuch_bar_top"]."</td><td>".$lang["gaestebuch_bar_bottom"]."</td></tr>";
   echo "<tr>";
   echo "<td>";
   echo "&nbsp;";  // createsel_frame("new_page_frame", $new_page_frame);
   echo "</td>";
   echo "<td>";
   createsel_bar("new_gb_left_bar", $new_gb_left_bar);
   echo "</td>";
   echo "<td>";
   createsel_bar("new_gb_right_bar", $new_gb_right_bar);
   echo "</td>";
   echo "<td>";
   createsel_bar("new_gb_top_bar", $new_gb_top_bar);
   echo "</td>";
   echo "<td>";
   createsel_bar("new_gb_foo_bar", $new_gb_foo_bar);
   echo "</td>";
   echo "</tr>";
   echo "<tr><td colspan=5>";
   write_bbc("gbnew", "new_gb_text");
   echo "<textarea name=new_gb_text id=new_gb_text wrap=virtual rows=15 cols=75>" . htmlspecialchars(stripslashes($new_gb_text)) . "</textarea>\n";
   echo "</td></tr>\n";
   echo "<tr><td colspan=5><input type=submit name=edit_gaestebuch value=".$lang["gaestebuch_speichern"]."></td></tr>";
   echo "</table>";
   echo "</form>";
}

function gaestebuchedit($id){
   global $conf, $lang;
   
   $result = dbquery("select * from ".$conf["db_namespace"]."gb where gb_id='" . $id . "'");
   if ($result) {
      $row = mysql_fetch_array($result);
      echo "<h1>".$lang["gaestebuch_bearbeiten"]."</h1>";
      echo "<form name = gbedit action=\"" . $conf["admp"] . "&section=gaestebuch&action=update\" ENCTYPE=\"multipart/form-data\" method=POST>";
      echo "<input type=hidden name=edit_gb_id value=\"" . $row["gb_id"] . "\">";
      echo "<table  class=\"reda_td\">";
      echo "<tr><td colspan = 5>".$lang["gaestebuch_name"]."</td></tr>";
      echo "<tr>";
      echo "<td colspan = 5><input name=edit_gb_name size=45 maxlength=59 value = \"" . htmlspecialchars($row["gb_name"]) . "\"></td>";
      echo "</tr>";
      echo "<tr><td>".$lang["gaestebuch_logo_klein"]."</td><td>".$lang["gaestebuch_logo_klein_inactive"]."</td><td>".$lang["gaestebuch_logo_gross"]."</td><td>&nbsp;</td><td>&nbsp;</td></tr>";
      echo "<tr>";
      echo "<td>";
      createsel_img("edit_gb_img_small",  $row["gb_img_small"]);
      echo "</td>";
      echo "<td>";
      createsel_img("edit_gb_img_small_inactive",  $row["gb_img_small_inactive"]);
      echo "</td>";
      echo "<td>";
      createsel_img("edit_gb_img_big",  $row["gb_img_big"]);
      echo "</td>";
      echo "<td>&nbsp;</td><td>&nbsp;</td>";
      echo "</tr>\n";
      echo "<tr><td colspan=5>&nbsp;</td></tr>\n";   
      echo "<tr><td>".$lang["gaestebuch_frame"]."</td><td>".$lang["gaestebuch_bar_left"]."</td><td>".$lang["gaestebuch_bar_right"]."</td><td>".$lang["gaestebuch_bar_top"]."</td><td>".$lang["gaestebuch_bar_bottom"]."</td></tr>";
      echo "<tr>";
      echo "<td>";
      echo "&nbsp;";  // createsel_frame("new_page_frame", $new_page_frame);
      echo "</td>";
      echo "<td>";
      createsel_bar("edit_gb_left_bar", $row["gb_left_bar"]);
      echo "</td>";
      echo "<td>";
      createsel_bar("edit_gb_right_bar", $row["gb_right_bar"]);
      echo "</td>";
      echo "<td>";
      createsel_bar("edit_gb_top_bar", $row["gb_top_bar"]);
      echo "</td>";
      echo "<td>";
      createsel_bar("edit_gb_foo_bar", $row["gb_foo_bar"]);
      echo "</td>";
      echo "</tr>";
      echo "<tr><td colspan=5>";
      write_bbc("gbedit", "edit_gb_text");
      echo "<textarea name=edit_gb_text id=new_gb_text wrap=virtual rows=15 cols=75>" . htmlspecialchars(stripslashes($row["gb_text"])) . "</textarea>\n";
      echo "</td></tr>\n";
      echo "<tr><td colspan=5 class=\"button_td_submit\"><input type=submit name=edit_gaestebuch value=".$lang["gaestebuch_speichern"]."></td></tr>\n";
      echo "</table>\n";
      echo "</form>\n";
      mysql_free_result($result);
   }
}   
?>