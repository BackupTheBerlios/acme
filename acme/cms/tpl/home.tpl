{mask:main}
<html><body>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<head>
<link rel="stylesheet" type="text/css" href="/medinet/medinet.css" title="default" media="screen">
<!-- metas -->
<title>medinet AG - Spessart-Klinik</title>
<meta http-equiv="Content-Type" content="text/html" charset="iso-8859-1">
<meta name="author" content="medinet AG, www.medinet-ag.de">
<meta name="description" content="medinet AG - Spessart-Klinik: Wir bieten Ihnen umfassende Rehabilitationsleistungen für Kinder, Jugendliche und Erwachsene, umfassende Behandlung von Adipositas und metabolischem Syndrom, sowie Betreuung von Kindern und Jugendlichen bei Suchterkrankungen. All das im erholsamen Ambiete von Bad Orb, einem Kurort im hessischen Spessart. Wir freuen uns auf Sie!">
<meta name="keywords" content="medinet, medinet AG, Spessartklinik, Spessart-Klinik, Spessart, Bad Orb, Hessen, Adipositas, metabolisch, metabolisches Syndrom, Übergewicht, Fett, Fettleibigkeit, Rehabilitation, Kinder, Jugendliche, Betreuung, Sucht, Suchterkrankungen, Suchterkrankung, Kurort, Erholung, Wellness, Anfahrt, Kontakt, Hilfe, Erkrankung, Reha, medizin, medizinische Betreuung">
<meta name="date" content="2005-03-01">
<meta name="robots" content="follow">
<meta http-equiv="Content-Style-Type" content="text/css">
<meta http-equiv="expires" content="0">

</head>

<!-- rahmentabelle: trennt navigation vom inhalt -->
<table class="rahmentable" >
  <tr>

    <!-- LINKE NAV -->
    <td class="rahmentable_l">
      <div id="top_bar"><a href="{home_url}">{home_img}</a></div>
         <div id="left_bar">
            {left_bar}
         </div>
    
    </td>  
    <!-- /LINKE NAV -->

    <!-- INHALT (ALLE FELDER) -->
    <td class="rahmentable_m" rowspan="2">
        <div id="mainContent">

<!-- NOCH NICHT ANGEPASST -->
{mask:news_top_thema}
<h1>{headline}</h1>
<p>{short_text}</p>
{mask:preview}
<h2>{headline}</h2>
<p>{short_text}</p>
{/mask}
{/mask}

<!-- NOCH NICHT ANGEPASST -->
{mask:news_page}
<h1>{headline}</h1>
<p>{short_text}</p>
{mask:preview}
<h2>{headline}</h2>
<p>{short_text}</p>
{/mask}
{/mask}

<!-- WEITGEHEND ANGEPASST (headline, subheadline noch checken -->
<!-- PAGE -->
{mask:page}
<div class="page_img_big">{img_big}</div>
<!-- CONTENT-BEGRENZUNGSMARKER OBEN LINKS -->
<img src="/medinet/cms/bilder/cont_border_ol.gif" class="img_cont_begr_ol" alt="grafisches element: inhaltsbegrenzung">
<div class="page_headline">{headline}</div>
<div class="page_img_titel">{img_titel}</div>
<div class="page_short_text">{short_text}</div>
<div class="page_long_text">{long_text}</div>
  {mask:preview}
    <div class="page_artikel_headline">{headline}</div>
    <div class="page_artikel_sub_headline">{sub_headline}</div>
    <!-- AUSKOMMENTIERT: AUTOR UND DATUM <span class="page_artikel_autor">{author}&nbsp;</span>
    <span class="page_artikel_publish_date">({publish_date})</span> -->
    <div class="page_artikel_short_text">{short_text}</div>
    <a href="{url}"><div class="page_artikel_url">mehr >></div></a>
  {/mask} 
{mask:parent}
<div class="page_parent"><a href="{url}">zur Übersicht</a></div>
{/mask}
<div class="page_modify_date">letzte Änderung: {modify_date}</div>
<!-- CONTENT-BEGRENZUNGSMARKER UNTEN RECHTS -->
<img src="/medinet/cms/bilder/cont_border_ur.gif" class="img_cont_begr_ur" alt="grafisches element: inhaltsbegrenzung">
{/mask} 



<!-- /PAGE -->


<!-- ARTIKEL -->

{mask:artikel} 
<div class="artikel_img_big">{img_big}</div>
<!-- CONTENT-BEGRENZUNGSMARKER OBEN LINKS -->
<img src="/medinet/cms/bilder/cont_border_ol.gif" class="img_cont_begr_ol" alt="grafisches element: inhaltsbegrenzung">
<div class="artikel_headline">{headline}</div>
<div class="artikel_sub_headline">{sub_headline}</div>
<div class="artikel_img_titel">{img_titel}</div>
<!-- AUSKOMMENTIERT: AUTOR UND DATUM <span class="artikel_author">{author}&nbsp;</span>
<span class="artikel_publish_date">({publish_date})</span> -->
<div class="artikel_short_text">{short_text}</div>
<div class="artikel_long_text">{long_text}</div>
<div class="artikel_div_modifydate_and_page">
	<span class="artikel_page"><a href="{page_url}"><< Zurück zur Seite "{page}"</a></span>
	<span class="artikel_modify_date">letzte Änderung: {modify_date}</span>
</div>
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

<!-- CONTENT-BEGRENZUNGSMARKER UNTEN RECHTS -->
<img src="/medinet/cms/bilder/cont_border_ur.gif" class="img_cont_begr_ur" alt="grafisches element: inhaltsbegrenzung">
{/mask}


<!--- ENDE ARTIKEL -->


<!-- NOCH NICHT ANGEPASST -->
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

<!-- NOCH NICHT ANGEPASST; styles stehen schon -->
<!-- sitemap -->
{mask:sitemap}
<div >{name}</div>
<div >{img_big}</div>
   {mask:map_element}
      {map_element_h_level}
      {map_element_img}
      <!-- set fragt ab ob die variable gefüllt ist und gibt nur dann aus... -->
      {set:map_element_url}<a href="{map_element_url}">{map_element_text}</a>{/set}
   {/mask}
{/mask} 
<!-- /sitemap -->

<!-- NOCH NICHT ANGEPASST; styles stehen schon -->
<!-- search -->
{mask:search}
<div >looking 4: {searchstring}</div>
   {mask:searchresults}
     {mask:result}
      {search_url}      
      {search_name}
      {search_text}<br>
     {/mask}  
   {/mask}
{/mask} 
<!-- /search -->


<!-- TEILWEISE ANGEPASST: styles angefangen. noch keine tables angelegt! -->
<!-- BILDER -->
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
        <div><a href = "{url}"><img src="{thumb_src}"></a></div>
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

{/mask} 
<!-- /BILDER -->



<!-- NOCH NICHT ANGEPASST -->
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
          
		  
		  <!-- URL-LISTE INHALT -->
		  
		  
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
		 <!-- /URL-LISTE INHALT -->
		  
		  
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


<!-- NOCH NICHT ANGEPASST -->
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






<!-- /INHALT -->
</td>


<!-- RECHTER RAND -->
<td class="rahmentable_r" rowspan="2">
	<!-- KEY VISUAL: NOCH STATISCH -->
	<img src="/medinet/cms/bilder/spessartklinik_wasserglas_200w.jpg" alt="grafisches Deko-Element" width="200" class="img_key_visual">

<!-- /RECHTER RAND -->
</td>
</tr>

<!-- FARBBOX LINKS -->
<tr>
    <td class="nav_l_farbbox">
	</td>
</tr>


<!-- FOOTER -->
<tr><td class="footer_td" colspan="3">Impressum | Sitemap | Presse | Haftungsausschluss</td>
</tr>
<!-- /RAHMENTABLE -->
</table>





</body>
</html>
{/mask}