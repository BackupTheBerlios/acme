<?php
   include($conf["cms"] . "/debuglib.inc"); 
   include($conf["cms"] . "/ets.inc");
   include($conf["cms"] . "/fkt_createsel.inc");
   include($conf["cms"] . "/fkt_groups.inc");
   include($conf["cms"] . "/fkt_db.inc");
   include($conf["cms"] . "/fkt_etc.inc");
   include($conf["cms"] . "/fkt_date." . $conf["lang"] . ".inc");
     
   dbconnect();

   $page = array_shift($path);         
   if (!isset($page) or $page =='')  {
      $page = $conf["home_page_typ"];
      $id   = $conf["home_page"];
   }
   include($conf["cms"] . "/page.inc");
   if (checkmodul($page)) {
      if ($page <> "page"){
         include($conf["cms"] . "/" . $page . ".inc");
      }
   } else {
     renderpage($conf["home_404"], 0);
   }
?>
