<?php
switch($action)
{
   case "edit":
      $result = dbquery("select * from acme_blocks where block_id=$edit_id");
      if ($result)
            {
            $row = mysql_fetch_object($result);
            ?>
            <h1>Block bearbeiten</h1>
            <form action="<?php echo $conf["admp"]; ?>&section=blocks&action=update"  method=POST>
            <input type=hidden name=edit_block_id value="<?php echo $row->block_id; ?>">
            <table class="reda_td">
              <tr><td>Name</td><td>Typ</td></tr>
              <tr>
                 <td><input  name=edit_block_name  size=45 maxlength=80 value = "<?php echo $row->block_name; ?>"></td>
                 <td><?php createsel_btyp("edit_block_type", $row->block_type); ?></td>
              </tr>
              <tr><td colspan="3">Inhalt</td></tr>
              <tr><td colspan="3"><textarea name=edit_block_content wrap=virtual rows=4 cols=60><?php echo $row->block_content; ?></textarea></td></tr>
              <tr><td colspan="3" align="right"><input type=submit name=edit value=Speichern></td></tr>
            </table>
            </form>
            <?php
            }
      mysql_free_result($result);
      break;
      
   case "new":
        ?>
        <h1>Neuen Block anlegen</h1>
        <form action="<?php echo $conf["admp"]; ?>&section=blocks&action=add" method=POST>
        <table class="reda_td">
         <tr><td>Name</td><td>Typ</td></tr>
         <tr>
             <td><input  name=new_block_name  size=45 maxlength=80></td>
             <td><?php createsel_btyp("new_block_type",$new_block_type); ?></td>
         </tr>
         <tr><td>&nbsp;</td></tr>
         <tr><td>Inhalt</td></tr>
         <tr><td><textarea name=new_block_content wrap=virtual rows=4 cols=60><?php echo $new_block_content; ?></textarea></td></tr>
         <tr><td align="right"><input type=submit name=add value=anlegen></td></tr>
        </table>
        </form>
        <?php
        
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
            if ($my_result) {echo "Block einf&uuml;gen gelungen";block_browse($conf["admp"], $user_groups);}
            else            {echo "Block einf&ouml;gen fehlgeschlagen\n";block_browse($conf["admp"], $user_groups);}

            break;

    case "update":
         $Statement = "UPDATE acme_blocks SET".
                      " block_name = '". $edit_block_name . "',".
                      " block_type = '". $edit_block_type . "',".
                      " block_content = '". $edit_block_content . "'".
                      " WHERE block_id = '". $edit_block_id . "'";
         $my_result = dbquery($Statement);
         if ($my_result) {echo "Block update gelungen";block_browse($conf["admp"], $user_groups);}
         else            {echo "Block update fehlgeschlagen\n".$Statement;}
         
         break;

    case "delete":
          $my_result = dbquery("delete from acme_blocks where block_id = '". $delete_id . "'");
          if ($my_result) {echo "Block l&ouml;schen gelungen";block_browse($conf["admp"], $user_groups);}
          else            {echo "Block l&ouml;schen fehlgeschlagen";block_browse($conf["admp"], $user_groups);}
          
          break;
      
    default:
        block_browse();

        break;
}
function block_browse(){
   global $conf, $lang;

   echo "<h1>Block Management</h1>";
   if ( checkgroupcreate($conf["user_groups"], "blocks") == 1){
      echo "<a href=\"" . $conf["admp"] . "&section=blocks&action=new\">Neuen Block anlegen</a>";
   }
   echo "<table class=\"reda_td\">";
   echo "<tr><td>Name</td><td>Typ</td><td width=\"30\"></td><td width=\"30\"></td></tr>";
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
         if ( checkgroupmodify($conf["user_groups"], "blocks") == 1){
            echo "<a href=" . $conf["admp"] . "&section=blocks&action=edit&edit_id=" . $row->block_id . "><img src=\"cms/bilder/icon_edit.png\" width=\"25\" height=\"25\"></a>";
         }
         echo "</td>";
         echo "<td>";
         if ( checkgroupdelete($conf["user_groups"], "blocks") == 1){
            echo "<a href=" . $conf["admp"] . "&section=blocks&action=delete&delete_id=" . $row->block_id ."><img src=\"cms/bilder/icon_delete.png\" width=\"25\" height=\"25\"></a>";
         }
         echo "</td>";                 
         echo "</tr>\n";
         }
      }
      mysql_free_result($result);
      echo "</table>";
      echo $conf["user_groups"];
}
?>
