<?php

include($conf["admbase"] . "/lang/messages." . $conf["lang"] . ".inc");

if (!isset($status)) $status = "N";

switch($action){
	case "messages_edit":
      messages_edit($status, $messages_id, $edit_messages_topic, $edit_messages_message, $edit_messages_status);
      break;
      
	case "messages_answer":
      messages_answer($status, $messages_id);
      break;
      
	case "messages_update":
      messages_update($status, $messages_id, $edit_messages_status);
      messages_browse($status);
      break;

	case "messages_new":
		messages_new($status, $new_messages_topic, $new_messages_message, $new_messages_tuser);
      break;

   case "messages_insert":
      $error=0;
      if (getauthorbyid($new_messages_tuser) == ""){echo $lang["messages_tuser_fehlt"]."<br>";$error=1;}
      if ($new_messages_topic == ""){echo $lang["messages_topic_fehlt"]."<br>";$error=1;}
      if ($new_messages_message == ""){echo $lang["messages_text_fehlt"]."<br>";$error=1;}
      if ($error==1){
         messages_new($status, $new_messages_topic, $new_messages_message, $new_messages_tuser);
      }
      else{ 
         messages_insert($status, $new_messages_topic, $new_messages_message, $new_messages_tuser);
         messages_browse($status);
      }

      break;

	case "messages_delete":
      messages_delete($status, $messages_id);
      messages_browse($status);

      break;

   default:
      messages_browse($status);

      break;
}

function messages_edit($status, $edit_messages_id, $edit_messages_topic, $edit_messages_message, $edit_messages_status){

   global $conf, $lang;

   $result = dbquery("select * from ".$conf["db_namespace"]."messages where id=$edit_messages_id");
   if ($result)  {
   	  dbquery("update ".$conf["db_namespace"]."messages set new_m='N' where id=$edit_messages_id");
      $messages = mysql_fetch_object($result);
      echo "<h1>".$lang["messages_bearbeiten"]."</h1>".
           "<form action=\"" . $conf["admp"] . "&section=messages&status=".$status."&action=messages_update&messages_id=" . $messages->id . "\"  method=POST>".
           "<table class=\"reda_td\">".
           "<tr><td>".$lang["messages_fuser"]. ": ". getauthorbyid($messages->fuser) . "</td></tr>".           
           "<tr><td>".$lang["messages_topic"]. ": ". htmlspecialchars($messages->topic) . "</td></tr>".
           "<tr><td>". nltobr(htmlspecialchars($messages->message)) . "</td>";
      if ($messages->status == "P" || $messages->status == "N"){
         echo "<tr><td>". $lang["messages_status"]."</td></tr>";
         echo "<tr><td><input type=radio name=edit_messages_status value=P checked>".$lang["messages_status_inbearb"]."</td></tr>";      	
         echo "<tr><td><input type=radio name=edit_messages_status value=F>".$lang["messages_status_abgeschl"]."</td></tr>";
      }
      else {echo "<tr><td></td></tr>";}                      
      echo "<tr><td><input type=submit name=add value=".$lang["messages_speichern"]."></td></tr>".
           "</table>".
           "</form>";
      echo "<form action=\"" . $conf["admp"] . "&section=messages&status=".$status."&action=messages_answer&messages_id=" . $messages->id . "\"  method=POST>".           
           "<input type=submit name=add value=".$lang["messages_answer"].">".
           "</form>";           
      mysql_free_result($result);
   }
   else{echo $lang["messages_notfound"];}
}

function messages_answer($status, $messages_id){

   global $conf, $lang;

   $result = dbquery("select * from ".$conf["db_namespace"]."messages where id=$messages_id");
   if ($result)  {
      $messages = mysql_fetch_object($result);
      echo "<h1>".$lang["messages_answer"]."</h1>".
           "<form action=\"" . $conf["admp"] . "&section=messages&status=".$status."&action=messages_insert&messages_id=" . $messages->id . "\"  method=POST>".
           "<table class=\"reda_td\">".
        "<tr><td><input name=new_messages_topic size=70 maxlength=128 value=\"" . $lang["messages_anwsertopic"] . " " .  htmlspecialchars(stripslashes($messages->topic)) . "\"></td></tr>".
        "<tr><td>".$lang["messages_text"]."</td></tr>".
        "<tr><td><textarea name=\"new_messages_message\" wrap=virtual rows=15 cols=75>" . $lang["messages_anwsermsg"] . htmlspecialchars(stripslashes($messages->message)) . "</textarea></td>";
      echo "<tr><td><input type=hidden name=new_messages_tuser size=70 maxlength=128 value=\"" .$messages->fuser . "\"></td></tr>";
      echo "<tr><td><input type=submit name=add value=".$lang["messages_speichern"]."></td></tr>".
           "</table>".
           "</form>";
      mysql_free_result($result);
   }
   else{echo $lang["messages_notfound"];}
}


function messages_update($status, $messages_id, $messages_status){
   global $conf, $lang;

   $Statement = "UPDATE ".$conf["db_namespace"]."messages SET ".
                "status  = '". $messages_status  . "'".
                " WHERE id = '". $messages_id . "'";
   $update_result = dbquery($Statement);
   if($update_result){echo $lang["messages_update_erfolgreich"];}
   else{echo $lang["messages_update_fehlgeschlagen"];};
}

function messages_new($status, $new_messages_topic, $new_messages_message, $new_messages_tuser) {
   global $conf, $lang;

   echo "<h1>".$lang["messages_neu"]."</h1>".
        "<form action=\"" .  $conf["admp"] . "&section=messages&status=".$status."&action=messages_insert\"  method=POST>".
        "<table class=\"reda_td\">".
        "<tr><td>".$lang["messages_topic"]."</td></tr>".
        "<tr><td><input name=new_messages_topic size=70 maxlength=128 value=\"" . htmlspecialchars(stripslashes($new_messages_topic)) . "\"></td></tr>".
        "<tr><td>".$lang["messages_text"]."</td></tr>".
        "<tr><td><textarea name=\"new_messages_message\" wrap=virtual rows=15 cols=75>" . htmlspecialchars(stripslashes($new_messages_message)) . "</textarea></td>";
   echo "</tr>".
        "<tr><td>";
   createsel_author("new_messages_tuser", $new_messages_tuser); 
   echo "</td></tr>".
        "<tr><td>";          
   echo "</td></tr>".     
        "<tr><td><input type=submit name=add value=".$lang["messages_speichern"]."></td></tr>".
        "</table>".
        "</form>";
}
function messages_insert($status, $topic, $message, $tuser){
   global $conf, $lang;

   $Statement = "INSERT INTO ".$conf["db_namespace"]."messages SET ".
                "topic = '". $topic . "', ".
                "message = '". $message . "', ".
                "status = 'N', ".                
                "tuser = ". $tuser . ", ".  
                "created = now(),".
                "fuser = ". $conf["author_id"];
   $insert_result = dbquery($Statement);
   if($insert_result){echo $lang["messages_insert_erfolgreich"];}
   else{echo $lang["messages_insert_fehlgeschlagen"];};
}

function messages_browse($status) {
   global $conf, $lang;

   echo "<h1>".$lang["messages_verwaltung"]."</h1>\n";
   echo "<a href=\"" . $conf["admp"] . "&section=messages&action=messages_new\">".$lang["messages_neu"]."</a>";
   $nresult = dbquery("select * from ".$conf["db_namespace"]."messages where status = 'N' and tuser = " . $conf["author_id"]. " order by created DESC");
   $presult = dbquery("select * from ".$conf["db_namespace"]."messages where status = 'P' and tuser = " . $conf["author_id"]. " order by created DESC");
   $fresult = dbquery("select * from ".$conf["db_namespace"]."messages where status = 'F' and tuser = " . $conf["author_id"]. " order by created DESC");
   $sresult = dbquery("select * from ".$conf["db_namespace"]."messages where fuser = " . $conf["author_id"]. " order by created DESC");
   echo "<table class=\"reda_td\">\n\n";
   echo "<tr>\n";
   if ($status == "N"){
      echo "<td class=\"message_nav_td_active\"><a class=\"message_nav_link_active\" href=\"" . $conf["admp"] . "&section=messages&status=N\">".$lang["messages_status_neu"]."(". mysql_num_rows($nresult) .")</a></td>\n";
   }else{
   	  echo "<td class=\"message_nav_td_passive\"><a class=\"message_nav_link_passive\" href=\"" . $conf["admp"] . "&section=messages&status=N\">".$lang["messages_status_neu"]."(". mysql_num_rows($nresult) .")</a></td>\n";
   }	  
   if ($status == "P"){   
      echo "<td class=\"message_nav_td_active\"><a class=\"message_nav_link_active\" href=\"" . $conf["admp"] . "&section=messages&status=P\">".$lang["messages_status_inbearb"]."(". mysql_num_rows($presult) .")</a></td>\n";
   }else{      
      echo "<td class=\"message_nav_td_passive\"><a class=\"message_nav_link_passive\" href=\"" . $conf["admp"] . "&section=messages&status=P\">".$lang["messages_status_inbearb"]."(". mysql_num_rows($presult) .")</a></td>\n";
   }   
   if ($status == "F"){            
      echo "<td class=\"message_nav_td_active\"><a class=\"message_nav_link_active\" href=\"" . $conf["admp"] . "&section=messages&status=F\">".$lang["messages_status_abgeschl"]."(". mysql_num_rows($fresult) .")</a></td>\n";
   }else{      
      echo "<td class=\"message_nav_td_passive\"><a class=\"message_nav_link_passive\" href=\"" . $conf["admp"] . "&section=messages&status=F\">".$lang["messages_status_abgeschl"]."(". mysql_num_rows($fresult) .")</a></td>\n";
   }
   if ($status == "S"){            
      echo "<td class=\"message_nav_td_active\"><a class=\"message_nav_link_active\" href=\"" . $conf["admp"] . "&section=messages&status=S\">".$lang["messages_status_gesendet"]."(". mysql_num_rows($sresult) .")</a></td>\n";
   }else{      
      echo "<td class=\"message_nav_td_passive\"><a class=\"message_nav_link_passive\" href=\"" . $conf["admp"] . "&section=messages&status=S\">".$lang["messages_status_gesendet"]."(". mysql_num_rows($sresult) .")</a></td>\n";
   }
            
   echo "</tr>\n";
   echo "</table>\n";

   echo "<br>\n";

   echo "<table class=\"reda_td\">\n\n";
   
   if ($status == "S"){echo "<tr><td><font class=\"subhead\">".$lang["messages_topic"]."</font></td><td><font class=\"subhead\">".$lang["messages_created"]."</font></td><td><font class=\"subhead\">".$lang["messages_tuser"]."</font></td><td>".$lang["messages_status"]."</td><td width=\"30\"> </td></tr>\n";
      echo "<tr><td colspan=\"5\"><hr></tr>\n";}
   else{echo "<tr><td><font class=\"subhead\">".$lang["messages_topic"]."</font></td><td><font class=\"subhead\">".$lang["messages_created"]."</font></td><td><font class=\"subhead\">".$lang["messages_fuser"]."</font></td><td width=\"30\"> </td></tr>\n";
   echo "<tr><td colspan=\"4\"><hr></tr>\n";}

   if ($status == "N"){
   while ($row = mysql_fetch_object($nresult)) {
      echo "<tr>";
      if ($row->new_m == 'N') {
         echo "<td>". $row->topic ."</td>";
      } else {
      	 echo "<td><b>". $row->topic ."</b></td>";
      }   
      echo "<td>". mydate2datetime($row->created) ."</td>";
      echo "<td>". getauthorbyid($row->fuser) ."</td>";
      echo "<td>";
      echo "<a href=\"" . $conf["admp"] . "&section=messages&status=".$status."&action=messages_edit&messages_id=" . $row->id . "\"><img src=\"" . $conf["images_admin"] . "icon_edit.png\" width=\"25\" height=\"25\"></a>";
      echo "</td>";
      echo "</tr>\n";
     echo "<tr><td colspan=\"4\"><hr></td></tr>\n";
    }
   }
   if ($status == "P"){
   while ($row = mysql_fetch_object($presult)) {
      echo "<tr>";
      echo "<td>". $row->topic ."</td>";
      echo "<td>". mydate2datetime($row->created) ."</td>";
      echo "<td>". getauthorbyid($row->fuser) ."</td>";
      echo "<td>";
      echo "<a href=\"" . $conf["admp"] . "&section=messages&status=".$status."&action=messages_edit&messages_id=" . $row->id . "\"><img src=\"" . $conf["images_admin"] . "icon_edit.png\" width=\"25\" height=\"25\"></a>";
      echo "</td>";
      echo "</tr>\n";
     echo "<tr><td colspan=\"4\"><hr></td></tr>\n";
   }
   }	
   if ($status == "F"){   	
   while ($row = mysql_fetch_object($fresult)) {
      echo "<tr>";
      echo "<td>". $row->topic ."</td>";
      echo "<td>". mydate2datetime($row->created) ."</td>";
      echo "<td>". getauthorbyid($row->fuser) ."</td>";
      echo "<td>";
      echo "<a href=\"" . $conf["admp"] . "&section=messages&status=".$status."&action=messages_edit&messages_id=" . $row->id . "\"><img src=\"" . $conf["images_admin"] . "icon_edit.png\" width=\"25\" height=\"25\"></a>";
      echo "</td>";
      echo "</tr>\n";
     echo "<tr><td colspan=\"4\"><hr></td></tr>\n";
   }
   }
   if ($status == "S"){   	
   while ($row = mysql_fetch_object($sresult)) {
      echo "<tr>";
      if ($row->new_m == 'N') {
         echo "<td>". $row->topic ."</td>";
      } else {
      	 echo "<td><b>". $row->topic ."</b></td>";
      }  
      echo "<td>". mydate2datetime($row->created) ."</td>";
      echo "<td>". getauthorbyid($row->tuser) ."</td>";
      echo "<td>";
      if ($row->status == "N"){echo $lang["messages_status_neu"];}
      if ($row->status == "P"){echo $lang["messages_status_inbearb"];}
      if ($row->status == "F"){echo $lang["messages_status_abgeschl"];}
      echo "</td>";
      echo "<td>";
      echo "<a href=\"" . $conf["admp"] . "&section=messages&status=".$status."&action=messages_edit&messages_id=" . $row->id . "\"><img src=\"" . $conf["images_admin"] . "icon_edit.png\" width=\"25\" height=\"25\"></a>";
      echo "</td>";
      echo "</tr>\n";
     echo "<tr><td colspan=\"5\"><hr></td></tr>\n";
   }
   }

   mysql_free_result($nresult);
   mysql_free_result($presult);
   mysql_free_result($fresult);
   mysql_free_result($sresult);   
   echo "</table>\n";   
}
?>
