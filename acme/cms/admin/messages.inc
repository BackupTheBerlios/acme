<?php

include($conf["admbase"] . "/lang/messages." . $conf["lang"] . ".inc");

switch($action){
	case "messages_edit":
      messages_edit($messages_id, $edit_messages_topic, $edit_messages_message, $edit_messages_status);
      break;

	case "messages_update":
      messages_update($messages_id, $edit_messages_status);
      messages_browse();
      break;

	case "messages_new":
		messages_new($new_messages_topic, $new_messages_message, $new_messages_tuser);
      break;

   case "messages_insert":
      if (getuserbyid($new_messages_tuser) == ""){
      	echo $lang["messages_tusernotfound"];
      	messages_new($new_messages_topic, $new_messages_message, $new_messages_tuser);
      }
      else{ 
         messages_insert($new_messages_topic, $new_messages_message, $new_messages_tuser);
         messages_browse();
      }

      break;

	case "messages_delete":
      messages_delete($messages_id);
      messages_browse();

      break;

   default:
      messages_browse();

      break;
}

function messages_edit($edit_messages_id, $edit_messages_topic, $edit_messages_message, $edit_messages_status){

   global $conf, $lang;

   $result = dbquery("select * from acme_messages where id=$edit_messages_id");
   if ($result)  {
      $acme_messages = mysql_fetch_object($result);
      echo "<h1>".$lang["messages_bearbeiten"]."</h1>".
           "<form action=\"" . $conf["admp"] . "&section=messages&action=messages_update&messages_id=" . $acme_messages->messages_id . "\"  method=POST>".
           "<table class=\"reda_td\">".
           "<tr><td>".$lang["messages_fuser"]. " ". getuserbyid($acme_messages->messages_topic) . "</td></tr>".           
           "<tr><td>". htmlspecialchars($acme_messages->messages_topic) . "</td></tr>".
           "<tr><td>". htmlspecialchars($acme_messages->messages_message) . "</td>";
      if ($acme_messages->status == "P" || $acme_messages->status == "N"){     
         echo "<tr><td><input type=checkbox name=messages_status value=P selected>".$lang["messages_status_inbearb"]."</td></tr>";      	
         echo "<tr><td><input type=checkbox name=messages_status value=F>".$lang["messages_status_abgeschl"]."</td></tr>";
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

   $result = dbquery("select * from acme_messages where id=$edit_messages_id");
   if ($result)  {
      $acme_messages = mysql_fetch_object($result);
      if ($acme_messages->status == 'N' && $messages_status == ''){
      	 $messages_status = 'P';
      }
   }   
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
                "fuser = ". $conf["user_id"];
                echo $Statement;
   $insert_result = dbquery($Statement);
   if($insert_result){echo $lang["messages_insert_erfolgreich"];}
   else{echo $lang["messages_insert_fehlgeschlagen"];};
}

function messages_browse() {
   global $conf, $lang;

   echo "<h1>".$lang["messages_verwaltung"]."</h1>";
   echo "<a href=\"" . $conf["admp"] . "&section=messages&action=messages_new\">".$lang["messages_neu"]."</a>";
   echo "<table class=\"reda_td\">";
   echo "<tr><td>".$lang["messages_topic"]."</td><td width=\"30\"> </td><td width=\"30\">".$lang["admin_user"]."</td><td width=\"30\"> </td></tr>";
   $result = dbquery("select * from acme_messages where status = 'N' order by created DESC");
   if ( mysql_num_rows($result) > 0 )           {
      while ($row = mysql_fetch_object($result))              {
         echo "<tr>";
         echo "<td>!".$row->topic."</td>";
         echo "<td>";
         echo "<a href=\"" . $conf["admp"] . "&section=messages&action=messages_edit&messages_id=" . $row->id . "\"><img src=\"" . $conf["images_admin"] . "icon_edit.png\" width=\"25\" height=\"25\"></a>";
         echo "</td>";
         echo "<td>";
         echo "<td>".getuserbyid($row->fuser)."</td>";
         echo "<td>";

         echo "</tr>";
      }
   mysql_free_result($result);
   }
   
   echo "</table>";
   echo "<table class=\"reda_td\">";
   echo "<tr><td>".$lang["messages_topic"]."</td><td width=\"30\"> </td><td width=\"30\">".$lang["admin_user"]."</td><td width=\"30\"> </td></tr>";
   $result = dbquery("select * from acme_messages where status = 'P' order by created DESC");
   if ( mysql_num_rows($result) > 0 )           {
      while ($row = mysql_fetch_object($result))              {
         echo "<tr>";
         echo "<td>#".$row->topic."</td>";
         echo "<td>";
         echo "<a href=\"" . $conf["admp"] . "&section=messages&action=messages_edit&messages_id=" . $row->id . "\"><img src=\"" . $conf["images_admin"] . "icon_edit.png\" width=\"25\" height=\"25\"></a>";
         echo "</td>";
         echo "<td>";
         echo "<td>".getuserbyid($row->fuser)."</td>";
         echo "<td>";

         echo "</tr>";
      }
   mysql_free_result($result);
   }
   echo "</table>";
      
   echo "<table class=\"reda_td\">";
   echo "<tr><td>".$lang["messages_topic"]."</td><td width=\"30\"> </td><td width=\"30\">".$lang["admin_user"]."</td><td width=\"30\"> </td></tr>";
   $result = dbquery("select * from acme_messages where status = 'F' order by created DESC");
   if ( mysql_num_rows($result) > 0 )           {
      while ($row = mysql_fetch_object($result))              {
         echo "<tr>";
         echo "<td>".$row->topic."</td>";
         echo "<td>";
         echo "<a href=\"" . $conf["admp"] . "&section=messages&action=messages_edit&messages_id=" . $row->id . "\"><img src=\"" . $conf["images_admin"] . "icon_edit.png\" width=\"25\" height=\"25\"></a>";
         echo "</td>";
         echo "<td>";
         echo "<td>".getuserbyid($row->fuser)."</td>";
         echo "<td>";

         echo "</tr>";
      }
   mysql_free_result($result);
   }
   echo "</table>";   
}
?>
