<?php
// Erstellt Selects
function createsel_groups($select_name,$grouplist){
   global $conf, $lang;
   
   $allgroups = dbquery("select * from acme_groups order by group_name");
   echo "<select multiple size = \"5\" name=\"" . $select_name . "[]\">";
   if ( mysql_num_rows($allgroups) > 0 )
      {
      while ( $g_row = mysql_fetch_object($allgroups) )
         {
         echo "<option value=" . $g_row->group_id;
         if ( eregi ( $g_row->group_id, $grouplist ) )
            echo " selected ";
         echo ">" . $g_row->group_name . "</option>";
         }
      mysql_free_result($allgroups);
      }
   echo "</select>";
   return;
}

function createsel_author($select_name, $id){
   global $conf, $lang;
   
   $allgroups = dbquery("select * from acme_author order by author_nachname, author_vorname");
   echo "<select size = \"1\" name=\"" . $select_name . "\">";
   if (!isset($id)){echo "<option value=\"\" selected></option>";}
   else {echo "<option value=\"\" ></option>";}
   if ( mysql_num_rows($allgroups) > 0 )      {
      while ( $g_row = mysql_fetch_object($allgroups) )         {
         echo "<option value=" . $g_row->author_id;
         if ( $g_row->author_id == $id ){ echo " selected ";}
         echo ">" . $g_row->author_nachname . ", " . $g_row->author_vorname . "</option>";
      }
      mysql_free_result($allgroups);
   }
   echo "</select>";
   return;
}

function createsel_user($select_name, $id){
   global $conf, $lang;
   
   $allgroups = dbquery("select * from acme_user order by user_name");
   echo "<select size = \"1\" name=\"" . $select_name . "\">";
   if (!isset($id)){echo "<option value=\"\" selected></option>";}
   else {echo "<option value=\"\" ></option>";}
   if ( mysql_num_rows($allgroups) > 0 )   {
      while ( $g_row = mysql_fetch_object($allgroups) )         {
         echo "<option value=" . $g_row->user_id;
         if ( $g_row->user_id == $id ){ echo " selected ";}
         echo ">" . $g_row->user_name . "</option>";
      }
      mysql_free_result($allgroups);
   }
   echo "</select>";
   return;
}
function createsel_startpage($select_name,$grouplist){
   global $conf, $lang;
   
   $allgroups = dbquery("select * from acme_pages Where page_parent = '' order by page_name");
   echo "<select size = \"1\" name=\"" . $select_name . "\">";
   if ( mysql_num_rows($allgroups) > 0 )      {
      while ( $g_row = mysql_fetch_object($allgroups) )         {
         echo "<option value=" . $g_row->page_id;
         if ( eregi ( $g_row->page_id, $grouplist ) ){            echo " selected ";}
         echo ">" . $g_row->page_name . "</option>";
      }
      mysql_free_result($allgroups);
   }
   echo "</select>";
   return;
}
function createsel_bar($select_name,$grouplist){
   global $conf, $lang;
   
   $allgroups = dbquery("select * from acme_bar order by bar_name");
   echo "<select name=" . $select_name . ">";
   if ($grouplist == "") echo "<option value = '' selected>";
   else echo "<option value = ''>";
   if ( mysql_num_rows($allgroups) > 0 )
      {
      while ( $g_row = mysql_fetch_object($allgroups) )
         {
         echo "<option value=" . $g_row->bar_id;
         if ( eregi ( $g_row->bar_id, $grouplist ) )
            echo " selected ";
         echo ">" . $g_row->bar_name. "</option>";
         }
      mysql_free_result($allgroups);
      }
   echo "</select>";
   return;
}

function createsel_nav($select_name,$grouplist){
   global $conf, $lang;
   
   $allgroups = dbquery("select * from acme_nav order by nav_name");
   echo "<select name=" . $select_name . ">";
   if ($grouplist == "") echo "<option value = '' selected>";
   else echo "<option value = ''>";
   if ( mysql_num_rows($allgroups) > 0 )      {
      while ( $g_row = mysql_fetch_object($allgroups) )         {
         echo "<option value=" . $g_row->bar_id;
         if ( eregi ( $g_row->nav_id, $grouplist ) ) echo " selected ";
         echo ">" . $g_row->nav_name. "</option>";
         }
      mysql_free_result($allgroups);
      }
   echo "</select>";
   return;
}

function createsel_tpl($select_name,$grouplist){
   global $conf, $lang;
   
   $allgroups = dbquery("select * from acme_templates order by tpl_name");
   echo "<select name=" . $select_name . ">";
   if ($grouplist == "") echo "<option value = '' selected>";
   else echo "<option value = ''>";
   if ( mysql_num_rows($allgroups) > 0 )
      {
      while ( $g_row = mysql_fetch_object($allgroups) )
         {
         echo "<option value=" . $g_row->tpl_id;
         if ( eregi ( $g_row->tpl_id, $grouplist ) )
            echo " selected ";
         echo ">" . $g_row->tpl_name. "</option>";
         }
      mysql_free_result($allgroups);
      }
   echo "</select>";
   return;
}

function createsel_img($select_name, $grouplist){
   global $conf, $lang;
   
   $allgroups = dbquery("select * from acme_bilder order by img_name");
   echo "<select name=" . $select_name . ">";
   if ($grouplist == "") echo "<option value = '' selected>";
   else echo "<option value = ''>";
   if ( mysql_num_rows($allgroups) > 0 )
      {
      while ( $g_row = mysql_fetch_object($allgroups) )
         {
         echo "<option value=" . $g_row->img_id;
         if ( eregi ( $g_row->img_id, $grouplist ) )
            echo " selected ";
         echo ">" . $g_row->img_name. "</option>";
         }
      mysql_free_result($allgroups);
      }
   echo "</select>";
   return;
}
function createsel_frame($select_name,$grouplist){
   global $conf, $lang;
   
   $allgroups = dbquery("select * from acme_frames order by frame_name");
   echo "<select name=" . $select_name . ">";
   if ($grouplist == "") echo "<option value = '' selected>";
   else echo "<option value = ''>";
   if ( mysql_num_rows($allgroups) > 0 )
      {
      while ( $g_row = mysql_fetch_object($allgroups) )
         {
         echo "<option value=" . $g_row->frame_id;
         if ( eregi ( $g_row->tpl_id, $grouplist ) )
            echo " selected ";
         echo ">" . $g_row->frame_name. "</option>";
         }
      mysql_free_result($allgroups);
      }
   echo "</select>";
   return;
}
?>
