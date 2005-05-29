<?php 
   include($conf["cmsbase"] . "/debuglib.inc"); 
   include($conf["cmsbase"] . "/ets.inc");
   include($conf["cmsbase"] . "/fkt_createsel.inc");
   include($conf["cmsbase"] . "/fkt_groups.inc");
   include($conf["cmsbase"] . "/fkt_db.inc");
   include($conf["cmsbase"] . "/fkt_etc.inc");
   include($conf["cmsbase"] . "/fkt_img.inc");
   include($conf["cmsbase"] . "/fkt_page.inc"); 
   include($conf["cmsbase"] . "/fkt_date." . $conf["lang"] . ".inc");
     
   dbconnect();

   if (!isset($page) or $page =='')  {
      $page = $conf["home_page_typ"];
      $pageid   = $conf["home_page"];
   }
   include($conf["cmsbase"] . "/page.inc");
   if (checkmodul($page) || $page == "forum") {
      if ($page <> "page"){
         include($conf["cmsbase"] . "/" . $page . ".inc");
      }
   } else {
     renderpage($conf["home_404"], 0);
   }
   
   
function checkmodul($page){
   global $conf, $lang;
   
   $found = false;
   $result = dbquery("select modul from ".$conf["db_namespace"]."module order by modul");
   if ( mysql_num_rows($result) > 0 )           {
      while ($row = mysql_fetch_object($result)) {
      	if ($page==$row->modul){$found = true;break;}
      }
   }
   return $found;
}    
?>
