<?php
if( !$included["config.inc"] )
   {
   $conf["lang"]    = "de"; /* oder en */	
   $conf["dbhost"] 	= "localhost";
   $conf["dbuser"] 	= "acme";
   $conf["dbpass"] 	= "bop80cms";
   $conf["dbname"] 	= "acme";
   $conf["dbauth"] 	= "mysql";
   $conf["dbadmuser"] 	= "acme";
   $conf["dbadmpass"] 	= "bop80cms";
   
   $conf["www"] 	= "www.doerrstadt.org";   
   $conf["wwwdir"] 	= "/var/www";
   $conf["indexbase"] 	= "/acme_dev";
   $conf["base"] 		= $conf["indexbase"] . "";
   $conf["dir"] 		= $conf["wwwdir"] . $conf["base"];
   $conf["cms"] 		= $conf["dir"] . "/cms";
   $conf["admbase"] 	= $conf["cms"] . "/admin";

   $conf["indexname"]    = "/acme_dev/index/";
   $conf["templates"]    = "cms/tpl/";
   $conf["images"]       = "http://www.doerrstadt.org/acme_dev/cms/bilder/";
   $conf["images_admin"] = $conf["images"] . "admin/"; 
   $conf["downloads"]    = "/acme_dev/index/downloads/";
   $conf["styles"]       = "/acme_dev/index/styles";
   
   $conf["page"] 	  = "";
   $conf["page_id"] = "";


   mysql_pconnect($conf["dbhost"],$conf["dbuser"],$conf["dbpass"]);
   $result = mysql_db_query($conf["dbname"], "select * from acme_profile where home_activ='Y'");
   if ( mysql_num_rows($result) > 0 )	   {
   	while ($row = mysql_fetch_object($result))
	   	{
         $conf["home_img"]      = $row->home_img_id;
         $conf["home_page"]     = $row->home_page;
         $conf["home_page_typ"] = $row->home_page_typ;  
         $conf["home_tpl"]      = $row->home_tpl;  
         $conf["home_frame"]      = $row->home_frame;
         $conf["home_left_bar"]      = $row->home_left_bar;                  
         $conf["home_right_bar"]      = $row->home_right_bar;                  
         $conf["home_top_bar"]      = $row->home_top_bar;                  
         $conf["home_foo_bar"]      = $row->home_foo_bar;                  
         $conf["home_404"]      = $row->home_404;
         $conf["home_style"]    = $row->style;
   	   }
	   mysql_free_result($result);
	   }
   else
	   {
      $conf["home_img"]      = "";
      $conf["home_page"]     = "1";
      $conf["home_page_typ"] = "page";      
      $conf["home_404"]      = "1";
      $conf["home_style"]    = "1";
	   }
   $conf["search"] = "";
   $included["config.inc"] = 1;
   }
?>
