<?php
   $path = explode("/",$_SERVER[PATH_INFO]);
   array_shift ($path);
   include("cms/config.inc");
   include("cms/cms.inc"); 
?>
