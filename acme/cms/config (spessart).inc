<?php
if( !$included["config.inc"] )
   {
   $conf["lang"]    = "de"; /* oder en */	
   $conf["dbhost"] 	= "db402.1und1.de";
   $conf["dbuser"] 	= "dbo117112156";
   $conf["dbpass"] 	= "gzNuBHvC";
   $conf["dbname"] 	= "db117112156";
   $conf["dbauth"] 	= "mysql";
   $conf["dbadmuser"] 	= "dbo117112156";
   $conf["dbadmpass"] 	= "gzNuBHvC";
   
   $conf["htdocs"]		= "/homepages/15/d113883177/htdocs";
   $conf["domain"]    	= "http://www.omikron-webservice.de";
   $conf["subdir"] 	    = "/medinet";
   $conf["db_namespace"]= "acme_";
   $conf["indexbase"]   = $conf["domain"] . $conf["subdir"];
   $conf["cmsbase"]  	= $conf["htdocs"] . $conf["subdir"] . "/cms";
   $conf["admbase"] 	= $conf["cmsbase"] . "/admin";
   $conf["cmsurl"]    	= $conf["domain"]. $conf["subdir"]  . "/cms";
   $conf["admurl"]      = $conf["cmsurl"] . "/admin";
   
   $conf["indexname"]    = $conf["subdir"]. "/";
   $conf["templates"]    = $conf["cmsbase"]."/tpl/";
   $conf["images"]       = $conf["cmsurl"]."/bilder/";
   $conf["images_admin"] = $conf["images"] . "admin/"; 
   $conf["imagesdir"]    = $conf["htdocs"] . $conf["subdir"] . "/cms/bilder/";
   $conf["downloads"]    = $conf["cmsurl"]."/downloads/";
   $conf["downloadsdir"] = $conf["htdocs"] . $conf["subdir"] . "/cms/downloads/";
   $conf["styles"]       = $conf["cmsurl"]."/styles";
   
   $conf["page"] 	  = "";
   $conf["page_id"] = "";


   mysql_pconnect($conf["dbhost"],$conf["dbuser"],$conf["dbpass"]);
   $result = mysql_db_query($conf["dbname"], "select * from ".$conf["db_namespace"]."profile where home_activ='Y'");
   if ( mysql_num_rows($result) > 0 )	   {
   	while ($row = mysql_fetch_object($result))
	   	{
         $conf["home_img"]      = $row->home_img_id;
         $conf["home_page"]     = $row->home_page;
         $conf["home_page_typ"] = $row->home_page_typ;  
         $conf["home_frame"]      = $row->home_frame;
         $conf["home_left_bar"]      = $row->home_left_bar;                  
         $conf["home_right_bar"]      = $row->home_right_bar;                  
         $conf["home_top_bar"]      = $row->home_top_bar;                  
         $conf["home_foo_bar"]      = $row->home_foo_bar;                  
         $conf["home_404"]      = $row->home_404;
         $conf["home_style"]    = $row->home_style;
         $conf["home_tpl"]    = $row->home_tpl;
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
