{mask:main}
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<html>
<head>
<link rel="stylesheet" type="text/css" href="/acme_dev/innomine.css" titel="default" media="screen">
<!-- metas -->
<title>innomine.de</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
</head>
<body>
<div id="top_bar"><a href="{home_url}">{home_img}</a></div>

<div id="left_bar">
{left_bar}</div>
<div id="mainContent">

{mask:news_top_thema}
<h1>{headline}</h1>
<p>{short_text}</p>
{mask:preview}
<h2>{headline}</h2>
<p>{short_text}</p>
{/mask}
{/mask}
{mask:news_page}
<h1>{headline}</h1>
<p>{short_text}</p>
{mask:preview}
<h2>{headline}</h2>
<p>{short_text}</p>
{/mask}
{/mask}

<!-- PAGE -->
{mask:page}
<div class="page_img_big">{img_big}</div>
<div class="page_headline">{headline}</div>
<div class="page_img_titel">{img_titel}</div>
<div class="page_short_text">{short_text}</div>
<div class="page_long_text">{long_text}</div>
  {mask:preview}
    <div class="page_artikel_headline">{headline}</div>
    <div class="page_artikel_sub_headline">{sub_headline}</div>
    <div class="page_artikel_autor">{author}</div>
    <div class="page_artikel_publish_date">{publish_date}</div> 
    <div class="page_artikel_short_text">{short_text}</div>
    <div class="page_artikel_url"><a href="{url}">mehr...</a></div>
  {/mask} 
{mask:parent}
<div class="page_parent"><a href="{url}">zur Übersicht</a></div>
{/mask}
<div class="page_modify_date">letzte Änderung: {modify_date}</div>
{/mask} 
<!-- /PAGE -->
<!-- ARTIKEL -->
{mask:artikel} 
<div class="artikel_img_big">{img_big}</div>
<div class="artikel_headline">{headline}</div>
<div class="artikel_sub_headline">{sub_headline}</div>
<div class="artikel_img_titel">{img_titel}</div>
<div class="artikel_author">{author}</div>
<div class="artikel_publish_date">{publish_date}</div>
<div class="artikel_short_text">{short_text}</div>
<div class="artikel_long_text">{long_text}</div>
<div class="artikel_page"><a href="{page_url}">{page}</a></div>
<div class="artikel_modify_date">letzte Änderung: {modify_date}</div>
{mask:first}
<a href="{url}">{nr}</a>
{/mask}
{mask:prev}
<a href="{url}"><<</a>
{/mask}
{mask:akt}
Seite:{nr}
{/mask}
{mask:next}
<a href="{url}">>></a>
{/mask}
{mask:last}
<a href="{url}">{nr}</a>
{/mask}
{/mask}
<!--- ENDE ARTIKEL -->

<!-- BLOG -->
{mask:blog}
<div class="blog_title">{titel}</div>
<div class="blog_img_big">{img_big}</div>
<div class="blog_text"> {text}
</div>
<div class="blog_long_text">{long_text}</div>
  {mask:blog_data}
    <div class="blog_data">
      <div class="blog_data_titel">{blog_titel}</div>
      <div class="blog_data_cat"><a href = "{blog_cat_url}">{blog_cat_name}</a></div>
      <div class="blog_data_text">{blog_text}
</div>
    </div>
  {/mask} 
<div class="blog_archiv">
  {mask:blog_archiv}
    archiv:<br>
    <a href="{url}">{monat}/{jahr}</a><br>
  {/mask}
</div>  
<div class="blog_last_update">letzte &Auml;nderung: {modify_date}</div>
{/mask} 
<!-- /BLOG -->


<!-- sitemap -->
{mask:sitemap}
   {mask:map_element}
      {map_element_img}
      {map_element_text}
      {map_element_url}<br>
   {/mask}
{/mask} 
<!-- /sitemap -->


<!-- Bilder -->
{mask:img_typ}
<div >{name}</div>
<div >{img_big}</div>
<div > {text}
</div>
  {mask:img_row}
    <!-- zeile -->
    {mask:img_col}
      <div>
        <!-- spalte -->
        <div>{name}</div>
        <div>{desc_short}</div>
        <div<a href = "{url}"><img src="{thumb_src}"></a></div>
        <div><a href = "{url}">{name}</a></div>
      </div>
    {/mask}
  {/mask} 
  {mask:image}
    <div>
      <div>{name}</div>
      <div>{desc_short}</div>
      <div>{desc_long}</div>
      
      <div><img src="{src}"></div>
    </div>
  {/mask} 
<div class="blog_last_update">letzte &Auml;nderung: {modify_date}</div>
{/mask} 
<!-- /BLOG -->
<!-- URL-LISTE -->
{mask:urls}
	<table class="art_cont_table" cellspacing="0" >	
		  <tr> 
          <td class="art_top_left"> 
            <p>&nbsp;</p>
          </td>
          <td class="art_top_centerright" colspan="2"><font class="title">{titel}&nbsp;</font></td>
        </tr>
		<tr> 
          <td class="art_middle_left">{img_big}</td>
          
		  
		  <!-- INHALT -->
		  
		  
 <td class="art_middle_center"> 
            
		  {mask:page_parent}
		  <a href="{url}">{name}</a><br>
  		  {/mask}
				
			
			{mask:url_childs}
		<a href="{url}">{name}</a><br>
			{/mask}	
					
				<ul>
				{mask:url_data}
					<li><a href="{url}">{name}</a><br>
					{text}</li>
				{/mask}
				</ul>
			
				
			
		  
		  
		
			
		
		</td>
			
			  
         
		  
		  
		  
		  <!-- /INHALT -->
		  
		  
          <td class="art_middle_right"> 
		  
		  
					  <a href="{print_url}">drucken</a><br>
          
				
				<br>				
            <br>
		<a href="{parent_url}">zur Übersicht</a><br>
          </td>
        </tr>

        <tr> 
          <td class="art_bottom_left">&nbsp;</td>
          <td class="art_bottom_center">letzte Aktualisierung: {modify_date}</td>
          <td class="art_bottom_right">&nbsp;</td>
        </tr>
		
		</table>

{/mask} 
<!-- /URL-LISTE -->



<!-- KALENDER -->
{mask:termine}
   <table class="art_cont_table" cellspacing="0" >	
      <tr> 
         <td class="art_top_left"><p>&nbsp;</p>
</td>
         <td class="art_top_centerright" colspan="2"><font class="title">{titel}&nbsp;</font></td>
      </tr>
      <tr> 
         <td class="art_middle_left">{img_big}</td>
         <!-- INHALT -->
         <td class="art_middle_center"> 
          {img_small}
          <p>{text}
</p>
         {mask:termin_data}
               <h4>{name}</h4>
	       <strong>Veranstalter</strong>: {veranstalter}<br>
	       <strong>Ort:</strong> {ort}<br>
	       <strong>Datum:</strong> {von_date} -  {bis_date}<br>
               <strong>Zeit:</strong> {von_time} bis {bis_time}<br>
	       <strong>Website:<a href = " {url}">{name}</a></strong>
	       
	       <p>{text}</p>	  
          {/mask}
          {mask:termin_childs} 
    	    <h3>{name}</h3>
            {mask:termin_childs_data}
               <h4>{name}</h4>
	       <strong>Veranstalter</strong>: {veranstalter}<br>
	       <strong>Ort:</strong> {ort}<br>
	       <strong>Datum:</strong> {von_date} -  {bis_date}<br>
               <strong>Zeit:</strong> {von_time} bis {bis_time}<br>
	       <strong>Website:<a href = " {url}">{name}</a></strong>
	       <p>{text}</p>	  
            {/mask}
	  {/mask}
        </td>
	<!-- /INHALT -->
          <td class="art_middle_right"> 
	  <a href="{print_url}">drucken</a><br>
	<br>				
        <br>
	<a href="{parent_url}">zur Übersicht</a><br>
      </td>
    </tr>
    <tr> 
      <td class="art_bottom_left">&nbsp;</td>
      <td class="art_bottom_center">letzte Aktualisierung: {modify_date}</td>
      <td class="art_bottom_right">&nbsp;</td>
    </tr>
</table>

{/mask} 
<!-- /KALENDER -->
</div>
<div id="right_bar">
{right_bar}
</div>
</body>
</html>
{/mask}
