<?php
if( !$included["config.inc"] ) {
      $conf["lang"]    = "de";        /* de or en */	
   $conf["dbhost"] 	= "localhost";         // database server
   $conf["dbname"]   = "acme";         // database name

   $conf["dbuser"] 	= "root";         // standard database user
   $conf["dbpass"] 	= "";         // password

   $conf["dbauth"] 	= "mysql";    // authentification method
   $conf["dbadmuser"] 	= "root";      // database user with admin rights
   $conf["dbadmpass"] 	= "";      // password
   
   $conf["htdocs"]		 = "/store/eclipse-ws/acme";      // complete path to www dir
   $conf["domain"]    	 = "http://localhost";      // complete domainname
   $conf["subdir"] 	    = "/";      // subdirectory in htdocs path
   $conf["db_namespace"] = "acme_"; // table prefix 4 database tables
   
   // complete url 
   $conf["indexbase"]   = $conf["domain"]  . $conf["subdir"];
   // complete path with /cms used 4 includes
   $conf["cmsbase"]  	= $conf["htdocs"]  . $conf["subdir"] . "/cms";
   // path 4 auth and language includes
   $conf["admbase"]     = $conf["cmsbase"] . "/admin";
   // url base 4 hrefs 
   $conf["cmsurl"]    	= $conf["domain"]  . $conf["subdir"]  . "/cms";
   $conf["admurl"]      = $conf["cmsurl"]  . "/admin";
   
   
   $conf["indexname"]    = $conf["domain"].$conf["subdir"]. "acme/";
   
   $conf["templates"]    = $conf["cmsbase"]."/tpl/";
   
   $conf["images"]       = $conf["cmsurl"]."/bilder/";
   $conf["imagesdir"]    = $conf["htdocs"] . $conf["subdir"] . "/cms/bilder/";
   
   $conf["downloads"]    = $conf["cmsurl"]."/downloads/";
   $conf["downloadsdir"] = $conf["htdocs"] . $conf["subdir"] . "/cms/downloads/";
   
   // css include, unused now 
   $conf["styles"]       = $conf["cmsurl"]."/styles";
   // urls 4 images in admin section
   $conf["images_admin"] = $conf["images"] . "admin/";
      
   $conf["page"] 	  = "";
   $conf["page_id"] = "";
   
   $conf["img_max_size"] = 180000;
   $conf["download_max_size"] = 500000;

   
   mysql_pconnect($conf["dbhost"],$conf["dbuser"],$conf["dbpass"]);
   $result = mysql_db_query($conf["dbname"], "select * from ".$conf["db_namespace"]."profile where home_activ='Y'");
   if ( mysql_num_rows($result) > 0 )	   {
   	while ($row = mysql_fetch_object($result))	   	{
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
	} else {
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
