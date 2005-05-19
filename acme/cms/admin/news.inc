<?php

include($conf["admbase"] . "/lang/news." . $conf["lang"] . ".inc");

switch($action){
	case "topic_move":
      if ($move=="up"){news_topic_move_up($topic_id);}
      if ($move=="down"){news_topic_move_down($topic_id);}  
      news_browse();
      break;
      
	case "topic_update":
      news_topic_update($edit_id, $edit_news_topic_rows, $edit_news_topic_top);
      break;
      
	case "topic_insert":
      news_topic_insert($new_news_topic_type_and_id, $new_news_topic_rows);
      news_browse();
      break;
      
	case "topic_new":
      news_topic_new($new_news_topic_type_and_id, $new_news_topic_rows);
      break;

	case "topic_edit":
      news_topic_edit($edit_id, $edit_news_topic_rows, $edit_news_topic_top);
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
   if ( checkgroupcreate($conf["author_groups"], "news") == 1)
      {echo "<a href=\"" . $conf["admp"] . "&section=news&action=topic_new\">Neuen Eintrag anlegen</a>";}
   $news_result = dbquery("select * from ".$conf["db_namespace"]."news_topics order by news_topic_rank");
   if ( mysql_num_rows($news_result) > 0 )  {
      echo "<table class=\"reda_td\">";
      echo "<tr><td>".$lang["news_top"]."</td><td>".$lang["news_typ"]."</td><td>".$lang["news_name"]."</td><td>".$lang["news_artikel"]."</td><td width=\"30\"></td><td width=\"30\"></td><td width=\"30\"></td><td width=\"30\"></td></tr>";
      while ($news = mysql_fetch_object($news_result))  {
          echo "<tr>".
               "<td>" . $news->news_topic_top . "</td>".
               "<td>" . $news->news_topic_type . "</td>".
               "<td>" . getnamebymodulandid($news->news_topic_type, $news->news_topic_type_id) . "</td>".
               "<td>" . $news->news_topic_rows . "</td>";
          if (acl_check("edit", $conf["author_groups"], $conf["author_id"], "news", $news->news_topic_id) == 1) {
             if ($news->page_news_rank == news_getlowest_rank($news->page_id)){echo "<td>&nbsp;</td>";}
             else {echo "<td><a href=\"" . $conf["admp"] . "&section=news&action=topic_move&topic_id=" . $news->news_topic_id . "&move=up\"><img src=\"" . $conf["images_admin"] . "icon_up.png\" width=\"25\" height=\"25\" alt=\"nach oben\"></a></td>";}
             if ($news->page_news_rank == news_gethighest_rank($news->page_id)){echo "<td>&nbsp;</td>";}
             else{echo "<td><a href=\"" . $conf["admp"] . "&section=news&action=topic_move&topic_id=" . $news->news_topic_id . "&move=down\"><img src=\"" . $conf["images_admin"] . "icon_down.png\" width=\"25\" height=\"25\" alt=\"nach unten\"></a></td>";}
             echo "<td><a href=\"" . $conf["admp"] . "&section=news&action=topic_edit&edit_id=" . $news->news_topic_id . "\"><img src=\"" . $conf["images_admin"] . "icon_edit.png\" width=\"25\" height=\"25\" alt=\"bearbeiten\"></a></td>";
             } else {echo "<td></td><td></td><td></td>";}
          if (acl_check("delete", $conf["author_groups"], $conf["author_id"], "news", $news->news_topic_id) == 1)
             {echo "<td><a href=\"" . $conf["admp"] . "&section=news&action=topic_delete&delete_id=" . $news->news_topic_id . "\"><img src=\"" . $conf["images_admin"] . "icon_delete.png\" width=\"25\" height=\"25\" alt=\"l&ouml;schen\"></a></td>";}
          else 
             {echo "<td>&nbsp;</td>";}   
          echo "</tr>";
          }
          mysql_free_result($news_result);
      }
      echo "</table>";
}   

function news_topic_edit($edit_id){
   global $conf, $lang;
   
   $result = dbquery("select * from ".$conf["db_namespace"]."news_topics where news_topic_id=$edit_id");
   if ($result) {
      $news = mysql_fetch_object($result);
      echo "<h1>".$lang["news_bearbeiten"]."</h1>".
           "<form action=\"" .$conf["admp"] . "&section=news&action=topic_update&edit_id=" . $news->news_topic_id ."\"  method=\"POST\">".
           "<table class=\"reda_td\">".
           "<tr><td>".$lang["news_typ"]."</td><td>".$lang["news_name"]."</td><td>".$lang["news_artikel"]."</td><td>".$lang["news_top"]."</td></tr>".
           "<tr>".
           "<td>" . $news->news_topic_type . "</td>".
           "<td>" . getnamebymodulandid($news->news_topic_type, $news->news_topic_type_id) . "</td>".
           "<td><input name=edit_news_topic_rows size=2 maxlength=2 value=\"" . $news->news_topic_rows . "\"></td>".
           "<td>";
      if ($news->news_topic_top == "N") {
      	  echo "<input type=checkbox name=edit_news_topic_top value=Y></td>";
      }
      echo "</td>".	  
           "</tr>".
           "<tr><td><input type=submit name=add value=".$lang["news_speichern"]."></td></tr>".
           "</table>".
           "</form>";
      mysql_free_result($result);
   }
}       

function news_topic_update($edit_news_topic_id, $edit_news_topic_rows, $edit_news_topic_top){
   global $conf, $lang;

   if ($edit_news_topic_top == "Y") {
      $Statement = "UPDATE ".$conf["db_namespace"]."news_topics SET news_topic_top = 'N' WHERE news_topic_top = 'Y'";
      $edit_result = dbquery($Statement);
      if($edit_result){echo $lang["news_update1_erfolgreich"]."</br>";}
      else{echo $lang["news_update1_fehlgeschlagen"]."</br>";};
      $Statement = "UPDATE ".$conf["db_namespace"]."news_topics SET news_topic_top = 'Y' WHERE news_topic_id = '". $edit_news_topic_id . "'";
      $edit_result = dbquery($Statement);
      if($edit_result){echo $lang["news_update2_erfolgreich"];}
      else{echo $lang["news_update2_fehlgeschlagen"];};
   }   
   $Statement = "UPDATE ".$conf["db_namespace"]."news_topics SET news_topic_rows = ". $edit_news_topic_rows . " WHERE news_topic_id = '". $edit_news_topic_id . "'";
   $edit_result = dbquery($Statement);
   if($edit_result){echo $lang["news_update3_erfolgreich"];}
   else{echo $lang["news_update3_fehlgeschlagen"];};

}

function news_topic_new(){

   global $conf, $lang;
   
   echo "<h1>".$lang["news_anlegen"]."</h1>".
        "<form action=\"" .$conf["admp"] . "&section=news&action=topic_insert\"  method=\"POST\">".
        "<table class=\"reda_td\">".
        "<tr><td>".$lang["news_name"]."</td><td>".$lang["news_artikel_anz"]."</td></tr>".
        "<tr><td>";
   createsel_news_topic_type("new_news_topic_type_and_id", "", 0);
   echo "</td>".
        "<td><input name=new_news_topic_rows size=2 maxlength=2 value=\"" . $new_news_topic_rows . "\"></td>".
        "</tr>".
        "<tr><td><input type=submit name=add value=".$lang["news_speichern"]."></td></tr>".
        "</table>".
        "</form>";
}   

function news_topic_insert($new_news_topic_type_and_id, $new_news_topic_rows){
   global $conf, $lang;

   $type_and_id    = explode("|", $new_news_topic_type_and_id);
   $topic_type    = $type_and_id[0];
   $topic_type_id = $type_and_id[1];

   $Statement = "SELECT news_topic_rank FROM ".$conf["db_namespace"]."news_topics ".
                "  order by news_topic_rank DESC";
   $maxresult = dbquery($Statement);
   if ($maxresult){
      $maxobj    = mysql_fetch_object($maxresult);
      $max_rank  = $maxobj->news_topic_rank;   
      $max_rank++;
      }
   else{$max_rank = 1;}

   $Statement = "insert ".$conf["db_namespace"]."news_topics  SET ".
                " news_topic_type = '" . $topic_type . "', ".
                " news_topic_type_id = '" . $topic_type_id . "', ".
                " news_topic_rows = '" . $new_news_topic_rows . "', ".
                " news_topic_rank = '" . $max_rank ."' ";
   $update_result = dbquery($Statement);
   
   if ($update_result){
   	$modulid = mysql_insert_id();
   	acl_user_set($conf["author_id"], "news", $modulid, "Y", "Y", "Y", "Y");
   	acl_group_set($conf["author_groups"], "news", $modulid, "Y", "Y", "Y", "Y");
   	echo $lang["news_insert_erfolgreich"];}
   else{echo $lang["news_insert_fehlgeschlagen"];}
}
   

function news_topic_move_up($topic_id){
   /* verschiebt newseintrag nach oben */
   
   global $conf, $lang;
      
   $akt_result = dbquery("select news_topic_rank from ".$conf["db_namespace"]."news_topics where news_topic_id='" . $topic_id . "'");
   if ($akt_result) {
      $akt_topic = mysql_fetch_object($akt_result);
      $akt_pos = $akt_topic->news_topic_rank;
      $prev_result = dbquery("select news_topic_id, news_topic_rank from ".$conf["db_namespace"]."news_topics where news_topic_rank < " . $akt_pos . " order by news_topic_rank DESC");
      if ($prev_result) {
         $prev_topic = mysql_fetch_object($prev_result);
         $prev_id = $prev_topic->news_topic_id;
         $prev_pos = $prev_topic->news_topic_rank;         
         $upd_result1 = dbquery("update ".$conf["db_namespace"]."news_topics set news_topic_rank = " . $akt_pos  . " where news_topic_id = '" . $prev_id . "'");
         $upd_result2 = dbquery("update ".$conf["db_namespace"]."news_topics set news_topic_rank = " . $prev_pos . " where news_topic_id = '" . $topic_id . "'");
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
      
   $akt_result = dbquery("select news_topic_rank from ".$conf["db_namespace"]."news_topics where news_topic_id='" . $topic_id . "'");
   if ($akt_result) {
      $akt_topic = mysql_fetch_object($akt_result);
      $akt_pos = $akt_topic->page_news_rank;
      $next_result = dbquery("select news_topic_id, news_topic_rank from ".$conf["db_namespace"]."news_topics where news_topic_rank > '" . $akt_pos . "' order by news_topic_rank ASC LIMIT 0,1");
      if ($next_result) {
         $next_topic = mysql_fetch_object($next_result);
         $next_id = $next_topic->news_topic_id;
         $next_pos = $next_topic->news_topic_rank;         
         $upd_result1 = dbquery("update ".$conf["db_namespace"]."news_topics set news_topic_rank = '" . $akt_pos  . "' where news_topic_id = '" . $next_id . "'");
         $upd_result2 = dbquery("update ".$conf["db_namespace"]."news_topics set news_topic_rank = '" . $next_pos . "' where news_topic_id = '" . $topic_id . "'");
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
   
   $delete_result = dbquery("delete from ".$conf["db_namespace"]."news_topics where news_topic_id = '". $delete_id . "'");
   if($delete_result){
      echo $lang["news_delete_erfolgreich"];
   }
   else{
      echo $lang["news_delete_fehlgeschlagen"];
   };
}

function createsel_news_topic_type($select_name, $type, $type_id) {
   global $conf, $lang;

   $check   = $type . "|" . $type_id;
   echo "\n<select name=\"" . $select_name . "\">";
   $result = dbquery("select * from ".$conf["db_namespace"]."module where nav = 'Y' and modul = 'page'");
   if ( mysql_num_rows($result) > 0 )  { 
      while ($row = mysql_fetch_array($result)){
         $Statement = "select * from " . $row[tablename] . "";
         $modul_result = dbquery($Statement);
         if ( mysql_num_rows($modul_result) > 0 )  { 
            while ($modulrow = mysql_fetch_array($modul_result)){
               $entry   = $row[modul] . "|" . $modulrow[$row[name]] ;
               $tocheck = $row[modul] . "|" . $modulrow[$row[id]] ;
               echo "<option value=\"" . $tocheck  . "\"";
               if ($tocheck == $check)  echo " selected ";
               echo ">" . $entry . "</option>\n";                
            }
            mysql_free_result($modul_result);
         }
      } 
   }
   
   echo "</select>\n";
   
   return;
   
}

function news_getlowest_rank(){
   /* liefert den niedrigsten eintrag */
   
   global $conf, $lang;
   
   $my_result = dbquery("select news_topic_rank from ".$conf["db_namespace"]."news_topics order by news_topic_rank ASC");
   $row = mysql_fetch_object($my_result);
   $rank = $row->news_topic_rank;
   mysql_free_result($my_result);
   return $rank;
}

function news_gethighest_rank(){
   /* liefert den hoechsten eintrag */

   global $conf, $lang;
   
   $my_result = dbquery("select news_topic_rank from ".$conf["db_namespace"]."news_topics order by news_topic_rank DESC");
   $row = mysql_fetch_object($my_result);
   $rank = $row->news_topic_rank;
   mysql_free_result($my_result);
   return $rank;
}
?>