<?php

include($conf["admbase"] . "/lang/news." . $conf["lang"] . ".inc");

switch($action){
	case "news_update":
      news_update($old_edit_tt_page_id, $edit_tt_page_id, $edit_tt_page_news_rows);
      break;
	   
	case "topic_move":
      if ($move=="up"){news_topic_move_up($topic_id);}
      if ($move=="down"){news_topic_move_down($topic_id);}  
      news_browse();
      break;
      
	case "topic_update":
      news_topic_update($edit_id, $edit_page_news_rows);
      break;
      
	case "topic_insert":
      news_topic_insert($new_page_id, $new_page_news_rows);
      news_browse();
      break;
      
	case "topic_new":
      news_topic_new();
      break;

	case "topic_edit":
      news_topic_edit($edit_id);
      break;
      
	case "topic_delete":
      news_topic_delete($delete_id);
      news_browse();
      break;
      
   default: 
      news_browse();
      break;
}

function news_browse(){
   global $conf, $lang;   

   echo "<h1>".$lang["news_bearbeiten"]."</h1>";
   $tt_result = dbquery("select * from acme_pages where page_top_thema = 'Y'");
   if (mysql_num_rows($tt_result) > 0 )  {
      $tt = mysql_fetch_object($tt_result);
      $tt_id = $tt->page_id;
      $tt_rows = $tt->page_news_rows;
      mysql_free_result($tt_result);
      }
   echo "<form action=\"" . $conf["admp"] . "&section=news&action=news_update\"  method=\"POST\">".
        "<table class=\"reda_td\">".
        "<tr><td>".$lang["news_seite"]."</td><td>".$lang["news_artikel_anz"]."</td></tr>".
        "<tr>".
        "<td>";
   createsel_news_top_thema("edit_tt_page_id", $tt_id);
   echo "</td>".
        "<td><input name=\"edit_tt_page_news_rows\" value=\"" . $tt_rows . "\"></td>".
        "<td><input type=submit name=add value=".$lang["news_speichern"]."></td>".
        "</tr>".
        "</table>".
        "<form>";
   if ( checkgroupcreate($conf["user_groups"], "news") == 1){echo "<a href=\"" . $conf["admp"] . "&section=news&action=topic_new\">Neuen Eintrag anlegen</a>";}
   $news_result = dbquery("select * from acme_pages where page_news_rank <> 0 order by page_news_rank");
   if ( mysql_num_rows($news_result) > 0 )  {
      echo "<table class=\"reda_td\">";
      echo "<tr><td>".$lang["news_name"]."</td><td>".$lang["news_artikel"]."</td><td width=\"30\"></td><td width=\"30\"></td><td width=\"30\"></td><td width=\"30\"></td></tr>";
      while ($news = mysql_fetch_object($news_result))  {
          echo "<tr>".
               "<td>" . $news->page_name . "</td>".
               "<td>" . $news->page_news_rows . "</td>";
          if ($news->page_news_rank == news_getlowest_rank($news->page_id)){echo "<td>&nbsp;</td>";}
          else {echo "<td><a href=\"" . $conf["admp"] . "&section=news&action=topic_move&topic_id=" . $news->page_id . "&move=up\"><img src=\"" . $conf["images_admin"] . "icon_up.png\" width=\"25\" height=\"25\" alt=\"nach oben\"></a></td>";}
          if ($news->page_news_rank == news_gethighest_rank($news->page_id)){echo "<td>&nbsp;</td>";}
          else{echo "<td><a href=\"" . $conf["admp"] . "&section=news&action=topic_move&topic_id=" . $news->page_id . "&move=down\"><img src=\"" . $conf["images_admin"] . "icon_down.png\" width=\"25\" height=\"25\" alt=\"nach unten\"></a></td>";}
          echo "<td>";
          if ( checkgroupmodify($conf["user_groups"], "news") == 1){echo "<a href=\"" . $conf["admp"] . "&section=news&action=topic_edit&edit_id=" . $news->page_id . "\"><img src=\"" . $conf["images_admin"] . "icon_edit.png\" width=\"25\" height=\"25\" alt=\"bearbeiten\"></a>";}
          echo "</td>".
               "<td>";
          if ( checkgroupdelete($conf["user_groups"], "news") == 1){echo "<a href=\"" . $conf["admp"] . "&section=news&action=topic_delete&delete_id=" . $news->page_id . "\"><img src=\"" . $conf["images_admin"] . "icon_delete.png\" width=\"25\" height=\"25\" alt=\"l&ouml;schen\"></a>";}
          echo "</td>".
               "</tr>";
          }
          mysql_free_result($news_result);
      }
      echo "</table>";
}   

function news_update($old_page_id, $edit_page_id, $edit_page_news_rows){
   global $conf, $lang;
   
   $Statement = "UPDATE acme_pages SET page_news_rows = 0, page_top_thema = 'N' WHERE page_id = '". $old_page_id . "'";
   $edit_result = dbquery($Statement);
   if($edit_result){echo $lang["news_update1_erfolgreich"]."</br>";}
   else{echo $lang["news_update1_fehlgeschlagen"]."</br>";};

   $Statement = "UPDATE acme_pages SET page_news_rows = ". $edit_page_news_rows . ", page_top_thema = 'Y' WHERE page_id = '". $edit_page_id . "'";
   $edit_result = dbquery($Statement);
   if($edit_result){echo $lang["news_update2_erfolgreich"];}
   else{echo $lang["news_update2_fehlgeschlagen"];};
}

function news_topic_edit($edit_id){
   global $conf, $lang;
   
   $result = dbquery("select * from acme_pages where page_id=$edit_id");
   if ($result) {
      $news = mysql_fetch_object($result);
      echo "<h1>".$lang["news_bearbeiten"]."</h1>".
           "<form action=\"" .$conf["admp"] . "&section=news&action=topic_update&edit_id=" . $news->page_id ."\"  method=\"POST\">".
           "<table class=\"reda_td\">".
           "<tr><td>".$lang["news_seite"]."</td><td>".$lang["news_artikel_anz"]."</td></tr>".
           "<tr><td>" . $news->page_name . "</td><td><input name=edit_page_news_rows size=2 maxlength=2 value=\"" . $news->page_news_rows . "\"></td>".
           "</tr>".
           "<tr><td><input type=submit name=add value=".$lang["news_speichern"]."></td></tr>".
           "</table>".
           "</form>";
      mysql_free_result($result);
   }
}       

function news_topic_update($page_id, $edit_page_news_rows){
   global $conf, $lang;

   $Statement = "update acme_pages  SET ".
                " page_news_rows = '" . $edit_page_news_rows . "' ".
                " where page_id = '"  . $page_id . "'";
   $update_result = dbquery($Statement);
   if ($update_result){echo $lang["news_update3_erfolgreich"];}
   else{echo $lang["news_update3_fehlgeschlagen"];}
}

function news_topic_new(){

   global $conf, $lang;
   
   echo "<h1>".$lang["news_anlegen"]."</h1>".
        "<form action=\"" .$conf["admp"] . "&section=news&action=topic_insert\"  method=\"POST\">".
        "<table class=\"reda_td\">".
        "<tr><td>".$lang["news_seite"]."</td><td>".$lang["news_artikel_anz"]."</td></tr>".
        "<tr><td>";
   createsel_news_pages_new("new_page_id", "");
   echo "</td>".
        "<td><input name=new_page_news_rows size=2 maxlength=2 value=\"" . $news->page_news_rows . "\"></td>".
        "</tr>".
        "<tr><td><input type=submit name=add value=".$lang["news_speichern"]."></td></tr>".
        "</table>".
        "</form>";
}   

function news_topic_insert($page_id, $new_page_news_rows){

   global $conf, $lang;

   $Statement = "SELECT page_news_rank FROM acme_pages ".
                " where page_news_rank <> 0 order by page_news_rank DESC";
   $maxresult = dbquery($Statement);
   if ($maxresult){
      $maxobj    = mysql_fetch_object($maxresult);
      $max_rank  = $maxobj->bar_topic_rank;   
      $max_rank++;
      }
   else{$max_rank = 1;}

   $Statement = "update acme_pages  SET ".
                " page_news_rows = '" . $new_page_news_rows . "', ".
                " page_news_rank = '" . $max_rank ."' ".
                " where page_id = '"  . $page_id . "'";
   $update_result = dbquery($Statement);
   
   if ($update_result){echo $lang["news_insert_erfolgreich"];}
   else{echo $lang["news_insert_fehlgeschlagen"];}
}
   

function news_topic_move_up($topic_id){
   /* verschiebt newseintrag nach oben */
   
   global $conf, $lang;
      
   $akt_result = dbquery("select page_news_rank from acme_pages where page_id='" . $topic_id . "'");
   if ($akt_result) {
      $akt_topic = mysql_fetch_object($akt_result);
      $akt_pos = $akt_topic->page_news_rank;
      $prev_result = dbquery("select page_id, page_news_rank from acme_pages where page_news_rank < " . $akt_pos . " order by page_news_rank DESC");
      if ($prev_result) {
         $prev_topic = mysql_fetch_object($prev_result);
         $prev_id = $prev_topic->page_id;
         $prev_pos = $prev_topic->page_news_rank;         
         $upd_result1 = dbquery("update acme_pages set page_news_rank = " . $akt_pos  . " where pagec_id = '" . $prev_id . "'");
         $upd_result2 = dbquery("update acme_pages set page_news_rank = " . $prev_pos . " where page_id = '" . $topic_id . "'");
         mysql_free_result($prev_result);
      } 
      else {echo "fehler beim prev lesen";}
      mysql_free_result($akt_result);
   } 
	else {echo "fehler beim akt lesen";}
   if($upd_result1 && $upd_result2){echo $lang["news_moveup_erfolgreich"];}
   else{echo $lang["news_moveup_fehlgeschlagen"];};

}

function news_topic_move_down($topic_id){
   /* verschiebt newseintrag nach unten */
   
   global $conf, $lang;
      
   $akt_result = dbquery("select page_news_rank from acme_pages where page_id='" . $topic_id . "'");
   if ($akt_result) {
      $akt_topic = mysql_fetch_object($akt_result);
      $akt_pos = $akt_topic->page_news_rank;
      $next_result = dbquery("select page_id, page_news_rank from acme_pages where page_news_rank > '" . $akt_pos . "' order by page_news_rank ASC LIMIT 0,1");
      if ($next_result) {
         $next_topic = mysql_fetch_object($next_result);
         $next_id = $next_topic->page_id;
         $next_pos = $next_topic->page_news_rank;         
         $upd_result1 = dbquery("update acme_pages set page_news_rank = '" . $akt_pos  . "' where bar_topic_id = '" . $next_id . "'");
         $upd_result2 = dbquery("update acme_pages set page_news_rank = '" . $next_pos . "' where bar_topic_id = '" . $topic_id . "'");
         mysql_free_result($next_result);
      } 
      else {echo "fehler beim next lesen";}
      mysql_free_result($akt_result);
   } 
	else {echo "fehler beim akt lesen";}
   if($upd_result1 && $upd_result2){echo $lang["news_movedown_erfolgreich"];}
   else{echo $lang["news_movedown_fehlgeschlagen"];};

}


function news_topic_delete($delete_id){
   /* 'loescht' newseintrag */
   
   global $conf, $lang;
   
   $delete_result = dbquery("update from acme_pages set page_news_rank = 0, page_news_rows = 0 where page_id = '". $delete_id . "'");
   if($delete_result){
      echo $lang["news_delete_erfolgreich"];
   }
   else{
      echo $lang["news_delete_fehlgeschlagen"];
   };
}

function createsel_news_top_thema($select_name,$grouplist) {
   /* select fuer topthema */

   global $conf, $lang;

   $allgroups = dbquery("select * from acme_pages where page_childs = 'A'");
   echo "<input type=\"hidden\" name=\"old_" . $select_name . "\" value = \"". $grouplist ."\">";
   echo "<select name=" . $select_name . ">";
   if ($grouplist == "") echo "<option value = '' selected>";
   else echo "<option value = ''>";
   if ( mysql_num_rows($allgroups) > 0 )      {
      while ( $g_row = mysql_fetch_object($allgroups) )         {
         echo "<option value=" . $g_row->page_id;
         if ( eregi ( $g_row->page_id, $grouplist ) ){  echo " selected "; }
         echo ">" . $g_row->page_name. "</option>";
         }
      mysql_free_result($allgroups);
      }
   echo "</select>";
   return;
}

function createsel_news_pages_new($select_name,$grouplist) {
   /* select fuer neuen neweintrag */

   global $conf, $lang;

   $allgroups = dbquery("select * from acme_pages where page_childs = 'A'");
   echo "<select name=" . $select_name . ">";
   echo "<option value = '' selected>";
   if ( mysql_num_rows($allgroups) > 0 )      {
      while ( $g_row = mysql_fetch_object($allgroups) ) {
         echo "<option value=" . $g_row->page_id . ">" . $g_row->page_name. "</option>";         
         }
      mysql_free_result($allgroups);
      }
   echo "</select>";
   return;
}

function news_getlowest_rank(){
   /* liefert den niedrigsten eintrag */
   
   global $conf, $lang;
   
   $my_result = dbquery("select page_news_rank from acme_pages where page_news_rank <> 0 order by page_news_rank ASC");
   $row = mysql_fetch_object($my_result);
   $rank = $row->page_news_rank;
   mysql_free_result($my_result);
   return $rank;
}

function news_gethighest_rank(){
   /* liefert den hoechsten eintrag */

   global $conf, $lang;
   
   $my_result = dbquery("select page_news_rank from acme_pages where page_news_rank <> 0 order by page_news_rank DESC");
   $row = mysql_fetch_object($my_result);
   $rank = $row->page_news_rank;
   mysql_free_result($my_result);
   return $rank;
}
?>