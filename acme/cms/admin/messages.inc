<?php

include($conf["admbase"] . "/lang/messages." . $conf["lang"] . ".inc");

if (!isset($status)) $status = "N";

switch($action){
	case "messages_edit":
      messages_edit($messages_id, $edit_messages_topic, $edit_messages_message, $edit_messages_status);
      break;

	case "messages_update":
      messages_update($messages_id, $edit_messages_status);
      messages_browse($status);
      break;

	case "messages_new":
		messages_new($new_messages_topic, $new_messages_message, $new_messages_tuser);
      break;

   case "messages_insert":
      $error=0;
      if (getuserbyid($new_messages_tuser) == ""){echo $lang["messages_tuser_fehlt"]."<br>";$error=1;}
      if ($new_messages_topic == ""){echo $lang["messages_topic_fehlt"]."<br>";$error=1;}
      if ($new_messages_message == ""){echo $lang["messages_text_fehlt"]."<br>";$error=1;}
      if ($error==1){
         messages_new($new_messages_topic, $new_messages_message, $new_messages_tuser);
      }
      else{ 
         messages_insert($new_messages_topic, $new_messages_message, $new_messages_tuser);
         messages_browse($status);
      }

      break;

	case "messages_delete":
      messages_delete($messages_id);
      messages_browse($status);

      break;

   default:
      messages_browse($status);

      break;
}

function messages_edit($edit_messages_id, $edit_messages_topic, $edit_messages_message, $edit_messages_status){

   global $conf, $lang;

   $result = dbquery("select * from acme_messages where id=$edit_messages_id");
   if ($result)  {
      $acme_messages = mysql_fetch_object($result);
      echo "<h1>".$lang["messages_bearbeiten"]."</h1>".
           "<form action=\"" . $conf["admp"] . "&section=messages&action=messages_update&messages_id=" . $acme_messages->id . "\"  method=POST>".
           "<table class=\"reda_td\">".
           "<tr><td>".$lang["messages_fuser"]. " ". getuserbyid($acme_messages->fuser) . "</td></tr>".           
           "<tr><td>". htmlspecialchars($acme_messages->topic) . "</td></tr>".
           "<tr><td>". htmlspecialchars($acme_messages->message) . "</td>";
      if ($acme_messages->status == "P" || $acme_messages->status == "N"){     
         echo "<tr><td><input type=radio name=edit_messages_status value=P checked>".$lang["messages_status_inbearb"]."</td></tr>";      	
         echo "<tr><td><input type=radio name=edit_messages_status value=F>".$lang["messages_status_abgeschl"]."</td></tr>";
      }
      else {echo "<tr><td></td></tr>";}                      
      echo "<tr><td><input type=submit name=add value=".$lang["messages_speichern"]."></td></tr>".
           "</table>".
           "</form>";
      mysql_free_result($result);
   }
   else{echo $lang["messages_notfound"];}
}

function messages_update($messages_id, $messages_status){
   global $conf, $lang;

   $Statement = "UPDATE acme_messages SET ".
                "status  = '". $messages_status  . "'".
                " WHERE id = '". $messages_id . "'";
   $update_result = dbquery($Statement);
   if($update_result){echo $lang["messages_update_erfolgreich"];}
   else{echo $lang["messages_update_fehlgeschlagen"];};
}

function messages_new($new_messages_topic, $new_messages_message, $new_messages_tuser) {
   global $conf, $lang;

   echo "<h1>".$lang["messages_neu"]."</h1>".
        "<form action=\"" .  $conf["admp"] . "&section=messages&action=messages_insert\"  method=POST>".
        "<table class=\"reda_td\">".
        "<tr><td>".$lang["messages_topic"]."</td></tr>".
        "<tr><td><input name=new_messages_topic size=70 maxlength=128 value=\"" . htmlspecialchars(stripslashes($new_messages_topic)) . "\"></td></tr>".
        "<tr><td>".$lang["messages_text"]."</td></tr>".
        "<tr><td><textarea name=\"new_messages_message\" wrap=virtual rows=15 cols=75>" . htmlspecialchars(stripslashes($new_messages_message)) . "</textarea></td>";
   echo "</tr>".
        "<tr><td>";
   createsel_user("new_messages_tuser", $message_tuser); 
   echo "</td></tr>".
        "<tr><td>";          
   echo "</td></tr>".     
        "<tr><td><input type=submit name=add value=".$lang["messages_speichern"]."></td></tr>".
        "</table>".
        "</form>";
}
function messages_insert($topic, $message, $tuser){
   global $conf, $lang;

   $Statement = "INSERT INTO acme_messages SET ".
                "topic = '". $topic . "', ".
                "message = '". $message . "', ".
                "status = 'N', ".                
                "tuser = ". $tuser . ", ".  
                "created = now(),".
                "fuser = ". $conf["user_id"];
   $insert_result = dbquery($Statement);
   if($insert_result){echo $lang["messages_insert_erfolgreich"];}
   else{echo $lang["messages_insert_fehlgeschlagen"];};
}

function messages_browse($status) {
   global $conf, $lang;

   echo "<h1>".$lang["messages_verwaltung"]."</h1>\n";
   echo "<a href=\"" . $conf["admp"] . "&section=messages&action=messages_new\">".$lang["messages_neu"]."</a>";
   $nresult = dbquery("select * from acme_messages where status = 'N' and tuser = " . $conf["user_id"]. " order by created DESC");
   $presult = dbquery("select * from acme_messages where status = 'P' and tuser = " . $conf["user_id"]. " order by created DESC");
   $fresult = dbquery("select * from acme_messages where status = 'F' and tuser = " . $conf["user_id"]. " order by created DESC");
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
   echo "<td></td></tr>\n";
   echo "<tr><td>".$lang["messages_topic"]."</td><td>".$lang["messages_created"]."</td><td>".$lang["messages_fuser"]."</td><td width=\"30\"> </td></tr>\n";
   if ($status == "N"){
   while ($row = mysql_fetch_object($nresult)) {
      echo "<tr>";
      echo "<td>". $row->topic ."</td>";
      echo "<td>". mydate2datetime($row->created) ."</td>";
      echo "<td>". getuserbyid($row->fuser) ."</td>";
      echo "<td>";
      echo "<a href=\"" . $conf["admp"] . "&section=messages&action=messages_edit&messages_id=" . $row->id . "\"><img src=\"" . $conf["images_admin"] . "icon_edit.png\" width=\"25\" height=\"25\"></a>";
      echo "</td>";
      echo "</tr>\n";
   }
   }
   if ($status == "P"){
   while ($row = mysql_fetch_object($presult)) {
      echo "<tr>";
      echo "<td>". $row->topic ."</td>";
      echo "<td>". mydate2datetime($row->created) ."</td>";
      echo "<td>". getuserbyid($row->fuser) ."</td>";
      echo "<td>";
      echo "<a href=\"" . $conf["admp"] . "&section=messages&action=messages_edit&messages_id=" . $row->id . "\"><img src=\"" . $conf["images_admin"] . "icon_edit.png\" width=\"25\" height=\"25\"></a>";
      echo "</td>";
      echo "</tr>\n";
   }
   }	
   if ($status == "F"){   	
   while ($row = mysql_fetch_object($fresult)) {
      echo "<tr>";
      echo "<td>". $row->topic ."</td>";
      echo "<td>". mydate2datetime($row->created) ."</td>";
      echo "<td>". getuserbyid($row->fuser) ."</td>";
      echo "<td>";
      echo "<a href=\"" . $conf["admp"] . "&section=messages&action=messages_edit&messages_id=" . $row->id . "\"><img src=\"" . $conf["images_admin"] . "icon_edit.png\" width=\"25\" height=\"25\"></a>";
      echo "</td>";
      echo "</tr>\n";
   }
   }
   mysql_free_result($nresult);
   mysql_free_result($presult);
   mysql_free_result($fresult);
   echo "</table>\n";   
}
?>
