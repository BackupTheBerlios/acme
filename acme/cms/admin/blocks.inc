<?php

include($conf["admbase"] . "/lang/blocks." . $conf["lang"] . ".inc");

switch($action){
   case "edit":
   
      $result = dbquery("select * from acme_blocks where block_id=$edit_id");
      if ($result)            {
         $row = mysql_fetch_object($result);
         echo "<h1>".$lang["blocks_bearbeiten"]."</h1>".
              "<form action=\"" . $conf["admp"] . "&section=blocks&action=update\"  method=POST>".
              "<input type=hidden name=edit_block_id value=" . $row->block_id . ">".
              "<table class=\"reda_td\">".
              "<tr><td>".$lang["blocks_name"]."</td><td>".$lang["blocks_typ"]."</td></tr>".
              "<tr>".
              "<td><input  name=edit_block_name  size=45 maxlength=80 value = \"" . htmlspecialchars($row->block_name) ."\"></td>".
              "<td>";
         createsel_btyp("edit_block_type", $row->block_type); 
         echo "</td>".
              "</tr>".
              "<tr><td colspan=\"3\">".$lang["blocks_inhalt"]."</td></tr>".
              "<tr><td colspan=\"3\"><textarea name=edit_block_content wrap=virtual rows=4 cols=60>" . htmlspecialchars($row->block_content) . "</textarea></td></tr>".
              "<tr><td colspan=\"3\" align=\"right\"><input type=submit name=edit value=".$lang["blocks_speichern"]."</td></tr>".
              "</table>".
              "</form>";
         mysql_free_result($result);
      }
   break;
      
   case "new":

      echo "<h1>".$lang["blocks_neu"]."</h1>".
           "<form action=\"" . $conf["admp"] . "&section=blocks&action=add\" method=POST>".
           "<table class=\"reda_td\">".
           "<tr><td>".$lang["blocks_name"]."</td><td>".$lang["blocks_typ"]."</td></tr>".
           "<tr>".
           "<td><input  name=new_block_name  size=45 maxlength=80></td>".
           "<td>";
      createsel_btyp("new_block_type",$new_block_type);
      echo "</td>".
           "</tr>".
           "<tr><td>&nbsp;</td></tr>".
           "<tr><td>".$lang["blocks_inhalt"]."</td></tr>".
           "<tr><td><textarea name=new_block_content wrap=virtual rows=4 cols=60>" . htmlspecialchars(stripslashes($new_block_content)) . "</textarea></td></tr>".
           "<tr><td align=\"right\"><input type=submit name=add value=".$lang["blocks_speichern"]."></td></tr>".
           "</table>".
           "</form>";

   break;

   case "add":
           $Statement = "INSERT INTO acme_blocks (".
                           " block_name ,".
                           " block_type ,".
                           " block_content ".
                           ") VALUES (".
                           " '". $new_block_name ."' ,".
                           " '". $new_block_type ."' ,".
                           " '". $new_block_content ."' )";
            $my_result = dbquery($Statement);
            if ($my_result) {
               echo $lang["blocks_insert_erfolgreich"];
               block_browse();
            }
            else {
               echo $lang["blocks_insert_fehlerhaft"];
               block_browse();
            }

            break;

    case "update":
         $Statement = "UPDATE acme_blocks SET".
                      " block_name = '". $edit_block_name . "',".
                      " block_type = '". $edit_block_type . "',".
                      " block_content = '". $edit_block_content . "'".
                      " WHERE block_id = '". $edit_block_id . "'";
         $my_result = dbquery($Statement);
         if ($my_result) {
            echo $lang["blocks_update_erfolgreich"];
            block_browse();
         }
         else            {
            echo $lang["blocks_update_fehlerhaft"];
            block_browse();
         }
         
    break;

    case "delete":
          $my_result = dbquery("delete from acme_blocks where block_id = '". $delete_id . "'");
          if ($my_result) {
             echo $lang["blocks_delete_erfolgreich"];
             block_browse($conf["admp"], $user_groups);
          }
          else            {
             echo $lang["blocks_delete_fehlerhaft"];
             block_browse($conf["admp"], $user_groups);
          }
          
    break;
      
    default:
        block_browse();

    break;
}
function block_browse(){
   global $conf, $lang;

   echo "<h1>".$lang["blocks_verwaltung"]."</h1>";
   if ( checkgroupcreate($conf["author_groups"], "blocks") == 1){
      echo "<a href=\"" . $conf["admp"] . "&section=blocks&action=new\">Neuen Block anlegen</a>";
   }
   echo "<table class=\"reda_td\">";
   echo "<tr><td>".$lang["blocks_name"]."</td><td>".$lang["blocks_typ"]."</td><td width=\"30\"></td><td width=\"30\"></td></tr>";
   $result = dbquery("select * from acme_blocks");
   if ( mysql_num_rows($result) > 0 )
      {
      while ($row = mysql_fetch_object($result))
         {
         echo "<tr>";
         echo "<td>".$row->block_name."</td>";
         if ($row->block_type == "H"){echo "<td>HTML</td>";}
         if ($row->block_type == "P"){echo "<td>PHP</td>";}
         echo "<td>";
         if ( checkgroupmodify($conf["author_groups"], "blocks") == 1){
            echo "<a href=" . $conf["admp"] . "&section=blocks&action=edit&edit_id=" . $row->block_id . "><img src=\"" . $conf["images_admin"] . "icon_edit.png\" width=\"25\" height=\"25\"></a>";
         }
         echo "</td>";
         echo "<td>";
         if ( checkgroupdelete($conf["author_groups"], "blocks") == 1){
            echo "<a href=" . $conf["admp"] . "&section=blocks&action=delete&delete_id=" . $row->block_id ."><img src=\"" . $conf["images_admin"] . "icon_delete.png\" width=\"25\" height=\"25\"></a>";
         }
         echo "</td>";                 
         echo "</tr>\n";
         }
      }
      mysql_free_result($result);
      echo "</table>";
}
function createsel_btyp($select_name,$grouplist)
{
   global $conf, $lang;
   echo "<select name=\"" . $select_name . "\">";
   echo "<option";
   if ($grouplist == "P"){echo " selected";};
   echo " value=\"P\">PHP</option>";
   echo "<option";
   if ($grouplist == "H" || $grouplist == ""){echo " selected";};
   echo " value=\"H\">HTML</option>";
   echo "</select>";
   return;
}
?>
