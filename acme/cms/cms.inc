<?php
   include($conf["cmsbase"] . "/debuglib.inc"); 
   include($conf["cmsbase"] . "/ets.inc");
   include($conf["cmsbase"] . "/fkt_createsel.inc");
   include($conf["cmsbase"] . "/fkt_groups.inc");
   include($conf["cmsbase"] . "/fkt_db.inc");
   include($conf["cmsbase"] . "/fkt_etc.inc");
   include($conf["cmsbase"] . "/fkt_date." . $conf["lang"] . ".inc");
     
   dbconnect();

   if (!isset($page) or $page =='')  {
      $page = $conf["home_page_typ"];
      $pageid   = $conf["home_page"];
   }
   include($conf["cmsbase"] . "/page.inc");
   if (checkmodul($page)) {
      if ($page <> "page"){
         include($conf["cmsbase"] . "/" . $page . ".inc");
      }
   } else {
     renderpage($conf["home_404"], 0);
   }
?>
