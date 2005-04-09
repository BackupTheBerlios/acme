<?php
// Erstellt Selects


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

   echo "\n<select name=" . $select_name . ">\n";
   if ($grouplist == "") echo "<option value = '' selected>\n";
   else echo "<option value = ''>\n";
   
   $imggroups = dbquery("select * from acme_bilder_typs order by img_typ_name");
   if ( mysql_num_rows($imggroups) > 0 ) {
      while ( $imggrouprow = mysql_fetch_object($imggroups) ){
      	 if (acl_check("insert", $conf["author_groups"], $conf["author_id"], "bilder", $imggrouprow->img_typ_id) == 1) {
      	 	echo "<optgroup label=\"" . $imggrouprow->img_typ_name .  "\">\n";
            $imgentrys = dbquery("select * from acme_bilder where img_typ_id = " . $imggrouprow->img_typ_id . " order by img_name");
            if ( mysql_num_rows($imgentrys) > 0 ) {
               while ( $imgentryrow = mysql_fetch_object($imgentrys) ) {
                  echo "<option value=" . $imgentryrow->img_id;
                  echo " label=" . $imgentryrow->img_name. " ";
                  if ( eregi ( $imgentryrow->img_id, $grouplist ) )
                  echo " selected ";
                  echo ">" . $imgentryrow->img_name. "</option>\n";
               }
            }
            echo "</optgroup>\n";   
      	 } else {
      	 	echo "<optgroup label=\"" . $imggrouprow->img_typ_name .  "\" style = \"color:gray;font-style:italic;\">\n";
      	 	echo "</optgroup>\n";
      	 }		
      }
      mysql_free_result($imggroups);
   }   
   echo "</select>\n";
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
