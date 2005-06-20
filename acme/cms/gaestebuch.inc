<?
/*

  platzhalter f�r die Seite:

  {mask:main}
     titel                Seiten�berschrift
     left_bar             linke Navigation
     right_bar            rechte Navigation
     top_bar              obere Navigation
     foo_bar              untere Navigation
     home_img
     home_url
    {mask:eintrag}
      name
      email
      url
      message
      comment
      date
      time
      ip
      host
    {/mask}    
  {/mask}   
  platzhalter f�r die Navigation:
  {mask:main}
    {mask:nav_elem}
       nav_elem_url
       nav_elem_text
       nav_elem_img
    {/mask}
  {/mask}        

*/

if ($page == "gaestebuch"){
 
   rendergaestebuch($id, $start);
   }
  
function rendergaestebuch($gb_id, $gb_page=1){
   global $conf, $lang;

   if ($_POST["send"] == "Send")	{
      $poster_name   = $_POST["poster_name"];
   	$poster_email  = $_POST["poster_email"];
   	$poster_url    = $_POST["poster_url"];
      $entry_content = $_POST["entry_content"];
      $timestamp     = time();
      $datum         = date("d.m.Y",$timestamp);
      $zeit          = date("H:i",$timestamp);
      $errortext = "";
      if (!eregi("^[_\.0-9a-z-]+@([0-9a-z][0-9a-z-]+\.)+[a-z]{2,4}$", $poster_email)){
         $error = true;
         $errortext .= "ung&uuml;ltige email-Adresse<br />";
         $poster_email = "";
      }
      if ($entry_content == ""){
         $error = true;
         $errortext .= "Beitrag fehlt<br />";
      }   
      if ($poster_name == "") {
         $error = true;
         $errortext .= "Name fehlt<br />";
      }
      if ($error) {
         $data->gaestebuch->post_name      = htmlspecialchars(stripslashes($poster_name));
         $data->gaestebuch->post_email     = htmlspecialchars(stripslashes($poster_email));
         $data->gaestebuch->post_url       = htmlspecialchars(stripslashes($poster_url));
         $data->gaestebuch->post_content   = htmlspecialchars(stripslashes($entry_content));
         $data->gaestebuch->post_errortext = "Fehler<br />".$errortext;
      }
      else {
         if (substr($poster_url, 0, 7) != 'http://') {
            $poster_url="http://".$poster_url;
         }
         if ($poster_url == '' || $poster_url == 'http://www.' || $poster_url == 'http://' || $poster_url == 'http://--') {
            $poster_url = '--';
         }
         $entry_content = ereg_replace("<", "&lt;", $entry_content);
         $entry_content = ereg_replace(">", "&gt;", $entry_content);
         $entry_content = addslashes($entry_content);
         $poster_name = ereg_replace("<", "&lt;", $poster_name);
         $poster_name = ereg_replace(">", "&gt;", $poster_name);
         $hostname = gethostbyaddr("$REMOTE_ADDR");
         dbquery("insert into ".$conf["db_namespace"]."gb_entrys (gb_id, entry_content, entry_comment, entry_date, entry_time, entry_poster, poster_email, poster_url, poster_ip, poster_hostname) values('$gb_id','$entry_content', '--', '$datum', '$zeit', '$poster_name', '$poster_email', '$poster_url', '$REMOTE_ADDR', '$hostname')");
         $data->gaestebuch->post_name    = "";
         $data->gaestebuch->post_email   = "";
         $data->gaestebuch->post_url     = "";
         $data->gaestebuch->post_content = "";
      }
   }
   else {
      $data->gaestebuch->post_name    = "";
      $data->gaestebuch->post_email   = "";
      $data->gaestebuch->post_url     = "";
      $data->gaestebuch->post_content = "";
   }
   
   
   $gb_result = dbquery("select * from ".$conf["db_namespace"]."gb where gb_id='".$gb_id."'");
   if (mysql_num_rows($gb_result) == 1) {
      $gb_row = mysql_fetch_object($gb_result);
      $gb_id        = $gb_row->gb_id;
      $gb_name      = $gb_row->gb_name;
      $gb_img_small = $gb_row->gb_img_small;
      $gb_img_big   = $gb_row->gb_img_big;
      $gb_text      = $gb_row->gb_text;
      $gb_left_bar  = $gb_row->gb_left_bar;
      $gb_right_bar = $gb_row->gb_right_bar;
      $gb_top_bar   = $gb_row->gb_top_bar;
      $gb_foo_bar   = $gb_row->gb_foo_bar;
      
      $data->left_bar  = parse_bar($conf["home_tpl"], $gb_left_bar,  "left");
      $data->right_bar = parse_bar($conf["home_tpl"], $gb_right_bar, "right");
      $data->top_bar   = parse_bar($conf["home_tpl"], $gb_top_bar,   "top");
      $data->foo_bar   = parse_bar($conf["home_tpl"], $gb_foo_bar,   "foo");

      $data->titel     = $gb_name;
      $data->home_img  = gethomeimg();
      $data->home_url  = $conf["indexname"] . $conf["home_page_typ"] . "/".$conf["home_page"];
      $data->gaestebuch->name         = $gb_name;
      $data->gaestebuch->text         = $gb_text;
      $data->gaestebuch->img_small    = getimage($gb_img_small);
      $data->gaestebuch->img_big      = getimage($gb_img_big);
      $data->gaestebuch->self_url     = $conf["indexname"]."gaestebuch/".$gb_id."/".$gb_page;
      $tplfile = $conf["templates"] . gettemplatebyid($conf["home_tpl"]) . ".tpl";

      writegbentrys(&$data, $gb_id, $gb_page);
      $page_output = sprintt($data, $tplfile);
      echo $page_output;
   } 
   else {renderpage($conf["home_404"],0);}
}

function writegbentrys($data, $gb_id, $gb_page){
  global $conf, $lang;
  
   $gb_ppp = "10";
   if(empty($gb_page)) {$gb_page=1;}
   $limitfrom = ($gb_page*$gb_ppp)-$gb_ppp;
   $limitto = $gb_ppp;
   $query = dbquery("SELECT * FROM ".$conf["db_namespace"]."gb_entrys where gb_id= ". $gb_id ." and entry_blocked = 'N' ORDER BY entry_id DESC LIMIT $limitfrom, $limitto");
   $num   = mysql_num_rows(dbquery("SELECT * FROM ".$conf["db_namespace"]."gb_entrys where gb_id= ". $gb_id ." and entry_blocked = 'N' ORDER BY entry_id DESC"));

   if ($num>$limitto)   {
      $seiten=intval($num/$limitto);
      if ($num%$limitto) {$seiten++;}
   }
   
   if($seiten == "")   {$seiten = "1";}

  // $data->gaestebuch->eintraege = $num;

   if($gb_page>1)              {$data->gaestebuch->prevpage = $conf["indexname"]."gaestebuch/".$gb_id."/".($gb_page-1);}
   $data->gaestebuch->page  = $gb_page;
   $data->gaestebuch->pages = $seiten;
   if($num/$gb_ppp > $gb_page) {$data->gaestebuch->nextpage = $conf["indexname"]."gaestebuch/".$gb_id."/".($gb_page+1);}

   $akt = 0;
   while($fetch=mysql_fetch_array($query)) {
   	  $akt++;
      if($fetch[poster_url] != "--") {$fetched_url=$fetch[poster_url];}
      else{$fetched_url="";}
      if($fetch[poster_email] != "--"){$fetched_mail=$fetch[poster_email];}
      else{$fetched_mail="";}
      if($fetch[entry_comment] == "--"){$fetched_comment = "";}
      else{$fetched_comment = $fetch[entry_comment];}
      $data->gaestebuch->eintrag[$akt]->name    = $fetch[entry_poster];
      $data->gaestebuch->eintrag[$akt]->email   = eregi_replace("@"," at ",$fetched_mail);
      $data->gaestebuch->eintrag[$akt]->url     = $fetched_url;
      $data->gaestebuch->eintrag[$akt]->message = nl2br($fetch[entry_content]);
      $data->gaestebuch->eintrag[$akt]->comment = $fetched_comment;
      $data->gaestebuch->eintrag[$akt]->date    = $fetch[entry_date];
      $data->gaestebuch->eintrag[$akt]->time    = $fetch[entry_time];
      $data->gaestebuch->eintrag[$akt]->ip      = $fetch[poster_ip];
      $data->gaestebuch->eintrag[$akt]->host    = $fetch[poster_hostname];
   }
}
?>