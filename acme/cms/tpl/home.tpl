{mask:main}<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<link rel="stylesheet" type="text/css" href="/acme-spessart-klinik/medinet.css" title="default" media="screen">
<!-- metas -->
<title>medinet AG - Spessart-Klinik</title>
<meta http-equiv="content-type" content="text/html; charset=ISO-8859-1">
<meta name="author" content="medinet AG, www.medinet-ag.de">
<meta name="description" content="medinet AG - Spessart-Klinik: Wir bieten Ihnen umfassende Rehabilitationsleistungen f�r Kinder, Jugendliche und Erwachsene, umfassende Behandlung von Adipositas und metabolischem Syndrom, sowie Betreuung von Kindern und Jugendlichen bei Suchterkrankungen. All das im erholsamen Ambiete von Bad Orb, einem Kurort im hessischen Spessart. Wir freuen uns auf Sie!">
<meta name="keywords" content="medinet, medinet AG, Spessartklinik, Spessart-Klinik, Spessart, Bad Orb, Hessen, Adipositas, metabolisch, metabolisches Syndrom, �bergewicht, Fett, Fettleibigkeit, Rehabilitation, Kinder, Jugendliche, Betreuung, Sucht, Suchterkrankungen, Suchterkrankung, Kurort, Erholung, Wellness, Anfahrt, Kontakt, Hilfe, Erkrankung, Reha, medizin, medizinische Betreuung">
<meta name="date" content="2005-03-01">
<meta name="robots" content="follow">
<meta http-equiv="Content-Style-Type" content="text/css">
<meta http-equiv="expires" content="0">
</head>
<body>
<!-- rahmentabelle: trennt navigation vom inhalt -->
<table class="rahmentable" >
 <tr>
  <!-- LINKE NAV -->
  <td class="rahmentable_l">
    <div class="home_img"><a href="{home_url}">{home_img}</a></div>
    <div id="left_bar">{left_bar}</div>
  </td>  
  <!-- /LINKE NAV -->

  <!-- INHALT (ALLE FELDER) -->
  <td class="rahmentable_m" rowspan="2">
   <div id="mainContent">

   {mask:downloads} 
   <!-- DOWNLOADS -->
      {mis:img_big:0}<div class="page_img_big">{img_big}</div>{/mis}
      <!-- CONTENT-BEGRENZUNGSMARKER OBEN LINKS -->
      <img src="/acme-spessart-klinik/cms/bilder/cont_border_ul.gif" class="img_cont_begr_ol" alt="grafisches element: inhaltsbegrenzung">
      {mask:parent}<div class="parent"><a href="{url}">{name}</a></div>{/mask}
      <h1>{name}</h1>
      <div class="long_text">{text}</div>
      {mask:download_childs}
        <h2>{name}</h2>
        <div class="long_text">{text}<a href="{url}"><span class = "url">>></span></a></div>
      {/mask} 
      {mask:download_data}
        <h3>{name}</h3>
        <div class="long_text">{text}<a href="{file}"><span class="url">{name}</span></a></div>
      {/mask} 
      <!-- CONTENT-BEGRENZUNGSMARKER UNTEN RECHTS -->
      <img src="/acme-spessart-klinik/cms/bilder/cont_border_lr.gif" class="img_cont_begr_ur" alt="grafisches element: inhaltsbegrenzung">
   <!-- /DOWNLOADS -->
   {/mask}

   {mask:page}
   <!-- PAGE -->
      {mis:img_big:0}<div class="page_img_big">{img_big}</div>{/mis}
      <!-- CONTENT-BEGRENZUNGSMARKER OBEN LINKS -->
      <img src="/acme-spessart-klinik/cms/bilder/cont_border_ul.gif" class="img_cont_begr_ol" alt="grafisches element: inhaltsbegrenzung">
      {mask:parent}<div class="parent"><a href="{url}">{name}</a></div>{/mask}
<!--      {set:bread}<div class="bread">{/set}
      {mask:bread}
         {set:url}<a href="{url}">{name}</a> {/set}
         {mis:url}{name} {/mis}
      {/mask}
      {set:bread}</div>{/set} -->
      <h1 class = "page">{headline}</h1>
      {mis:img_titel:0}<div class="page_img_titel">{img_titel}</div>{/mis}
      <p class="page_short_text">{short_text}</p>
      <div class="page_long_text">{long_text}</div>
      {mask:artikel_preview}
        <h4 class="page_artikel_headline">{headline}-{sub_headline}</h4>
        <p  class="page_artikel_short_text">{short_text}</p>
        <a href="{url}"><div class="page_artikel_url">mehr >></div></a>
      {/mask} 
      {mask:page_preview}
        <h4 class="page_artikel_headline">{headline}</h4>
        <p  class="page_artikel_short_text">{short_text}</p>
        <a href="{url}"><div class="page_artikel_url">mehr >></div></a>
      {/mask} 
      <div class="page_modify_date">letzte &Auml;nderung: {modify_date}</div>
      <!-- CONTENT-BEGRENZUNGSMARKER UNTEN RECHTS -->
      <img src="/acme-spessart-klinik/cms/bilder/cont_border_lr.gif" class="img_cont_begr_ur" alt="grafisches element: inhaltsbegrenzung">
   <!-- /PAGE -->
   {/mask} 

   {mask:artikel} 
   <!-- ARTIKEL -->
      {mis:img_big:0}<div class="artikel_img_big">{img_big}</div>{/mis}
      <!-- CONTENT-BEGRENZUNGSMARKER OBEN LINKS -->
      <img src="/acme-spessart-klinik/cms/bilder/cont_border_ul.gif" class="img_cont_begr_ol" alt="grafisches element: inhaltsbegrenzung">
      <div class="parent"><a href="{page_url}">{page}</a></div>
      <h1 class="artikel">{headline}</h1>
      <h2 class="artikel">{sub_headline}</h2>
      {mis:img_titel:0}<div class="artikel_img_titel">{img_titel}</div>{/mis}
      <p class="artikel_short_text">{short_text}</p>
      <p class="artikel_long_text">{long_text}</p>
      <div class="artikel_modify_date">letzte &Auml;nderung: {modify_date}</div>
      Seite:{mask:prev} <a href="{url}"><<</a>{/mask} 
      {mask:part} {set:url}<a href="{url}">{/set}{nr}{set:url}</a>{/set}{/mask} 
      {mask:next} <a href="{url}">>></a>{/mask}
      <!-- CONTENT-BEGRENZUNGSMARKER UNTEN RECHTS -->
      <img src="/acme-spessart-klinik/cms/bilder/cont_border_lr.gif" class="img_cont_begr_ur" alt="grafisches element: inhaltsbegrenzung">
   <!--- ENDE ARTIKEL -->
   {/mask}

   {mask:blog}
   <!-- NOCH NICHT ANGEPASST -->
   <!-- BLOG -->
      <div class="blog_title">{titel}</div>
      <div class="blog_img_big">{img_big}</div>
      <div class="blog_text"> {text}</div>
      <div class="blog_long_text">{long_text}</div>
      {mask:blog_data}
         <div class="blog_data">
           <div class="blog_data_titel">{blog_titel}</div>
           <div class="blog_data_cat"><a href = "{blog_cat_url}">{blog_cat_name}</a></div>
           <div class="blog_data_text">{blog_text}</div>
         </div>
      {/mask} 
      <div class="blog_archiv">
      {mask:blog_archiv}
        archiv:<br> <a href="{url}">{monat}/{jahr}</a><br>
      {/mask}
      </div>  
      <div class="blog_categorien">
      {mask:blog_cat}
        cat:<br><a href="{url}">{name}</a><br>
      {/mask}
      </div>  
      <div class="blog_last_update">letzte &Auml;nderung: {modify_date}</div>
   <!-- /BLOG -->
   {/mask} 



   {mask:sitemap}
   <!-- sitemap -->
      <h1 class="sitemap">{name}</h1>
      {mis:img_big:0}<div class="artikel_img_big">{img_big}</div>{/mis}
      {mask:map_element}
      {choose:map_element_h_level}
         {when:0}<div class="sitemap_h_0">{/when}
         {when:1}<div class="sitemap_h_1">{/when}
         {when:2}<div class="sitemap_h_2">{/when}
         {when:3}<div class="sitemap_h_3">{/when}
         {when:4}<div class="sitemap_h_4">{/when}
         {when:5}<div class="sitemap_h_5">{/when}
         {when:6}<div class="sitemap_h_6">{/when}
         {when:7}<div class="sitemap_h_7">{/when}                                                      
         {when:8}<div class="sitemap_h_8">{/when}
         {when:9}<div class="sitemap_h_9">{/when}
      {/choose}
      {set:map_element_img}{map_element_img}{/set}
      {set:map_element_url}<a href="{map_element_url}">{map_element_text}</a>{/set}
      </div>
      {/mask}
   <!-- /sitemap -->
   {/mask} 
   
   
   {mask:gaestebuch}
    <h1>{name}</h1>
    <p>{text}</p>
    {set:prevpage}<a href='{prevpage}'>&lt;&lt;</a>{/set} Seite: {page} von {pages} {set:nextpage}<a href='{nextpage}'>&gt;&gt;</a>{/set}
    {mask:eintrag}
		   <table align='center' border='0' width='400'>
		    <tr>
		     <td width='50%' valign='top' align='left'>
		       <b>{name}</b>&nbsp;
		       {set:email}<a href='mailto:{email}'><img src='/acme-spessart-klinik/cms/bilder/gb_email.gif' border='0' alt='Schreiben Sie {name} ein E-Mail&raquo;&nbsp;{email}'></a>&nbsp;{/set}
		       {set:url}<a href='{url}' target='_blank'><img src='/acme-spessart-klinik/cms/bilder/gb_homepage.gif' border='0' alt='Besuchen Sie {name} Homepage&raquo;&nbsp;{url}'></a>{/set}
		     </td>
		      <td width='50%' valign='top' align='right'><small><b>{date} &raquo; {time}</b></small></td>
		   </tr>
		    <tr>
		     <td colspan='2' valign='top'><div class='gb_messagebox'>{message}</div></td>
		    </tr> 
		    {set:commment}
		    <tr>
		     <td colspan='2' valign='top'><div class='gb_commentbox'>{comment}</div></td>
		    </tr>
		    {/set}
		   </table>
      <br>
    {/mask}
    <form name='gbook_form' method='post' action="{self_url}">
    <p>{post_errortext}</p>
    <table align='center' border='0' width='398'>
     <tr><td colspan = 2><hr></td></tr>
     <tr><td>Name:</td><td><input class='gb_box'  name=poster_name size=45 maxlength=59 value = "{post_name}"></td></tr>
     <tr><td>email:</td><td><input class='gb_box' name=poster_email size=45 maxlength=59 value = "{post_email}"></td></tr>
     <tr><td>URL:</td><td><input class='gb_box' name=poster_url size=45 maxlength=59 value = "{post_url}"></td></tr>
     <tr><td colspan = 2>Beitrag</td></tr>
     <tr><td colspan = 2><textarea class='gb_box' name=entry_content wrap=virtual rows=5 cols=53>{post_content}</textarea></td></tr>
     <tr><td colspan = 2><input class='gb_box' type='submit' name='send' value='Send'>&nbsp;<input  style = 'border-color:#00A88E;color:#000000;border:1px solid #000000;' type='reset' name='reset' value='Reset'></td></tr>
    </table>
    </form>
   {/mask}

   {mask:search}
   <!-- search -->
      <h1>Suchergebnisse zum Stichwort:</h1>
      <p>{searchstring}</p>
      {mis:searchresults}Kein Treffer.{/mis}
      {mask:searchresults}
        {mask:result}
        <ul class="search_ul">
	    <a href="{search_url}">{search_name}</a><br>
        <span class="search_description">{search_text}</span>
	    </ul>
        {/mask}  
      {/mask}
   <!-- /search -->
   {/mask} 

{mask:img_typ}
<!-- TEILWEISE ANGEPASST: styles angefangen. noch keine tables angelegt! -->
<!-- BILDER -->
<h1>{name}</h1>
{mis:img_big:0}<div class="page_img_big">{img_big}</div>{/mis}
<p>{text}</p>
  {mask:img_row}
    <!-- zeile -->
    {mask:img_col}
      <div>
        <!-- spalte -->
        <div>{name}</div>
        <div>{desc_short}</div>
        <div><a href = "{url}"><img src="{thumb_src}" alt="{desc_short}"></a></div>
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

<!-- /BILDER -->
{/mask} 

{mask:urls}
<!-- URL-LISTE -->
 {mask:parent}<div class="parent"><a href="{url}">{name}</a></div>{/mask}
 <h1>{name}&nbsp;</h1>
 <p>{text}&nbsp;</p>
 {mask:url_childs}
   <a href="{url}">{name}</a><br>
   <p>{text}</p>
 {/mask}	

  {mask:url_data}
   <h4>{name}</h4>
   <div class="long_text">{text}</div>
   <a href="{url}"><span class="url">{name}</span></a>
  {/mask}

<!-- /URL-LISTE -->
{/mask} 





{mask:termine}
<!-- KALENDER -->
   <table class="art_cont_table" cellspacing="0" >	
      <tr> 
         <td class="art_top_left"><p>&nbsp;</p></td>
         <td class="art_top_centerright" colspan="2"><font class="parent">{titel}&nbsp;</font></td>
      </tr>
      <tr> 
         <td class="art_middle_left">{mis:img_big:0}<div class="page_img_big">{img_big}</div>{/mis}</td>
         <td class="art_middle_center"> 
          <p>{text}</p>
         {mask:termin_data}
           <h4>{name}</h4>
	       <strong>Veranstalter</strong>: {veranstalter}<br>
	       <strong>Ort:</strong> {ort}<br>
	       <strong>Datum:</strong> {von_date} -  {bis_date}<br>
           <strong>Zeit:</strong> {von_time} bis {bis_time}<br>
	       <strong>Website:<a href = "{url}">{name}</a></strong>
	       <p>{text}</p>	  
          {/mask}
          {mask:termin_childs} 
    	    <a href = "{url}"><h3>{name}</h3></a>
          {/mask}
        </td>
        
        <td class="calender">
         {mask:Kalender}
          <table>
          <tr>
          <td colspan = 2 class = "calender_prev"><a href = "{prev_url}">&lt;</a></td>
          <td colspan = 4 class = "calender_month">{akt_monat}</td>
          <td colspan = 2 class = "calender_next"><a href = "{next_url}">&gt;</a></td>
          </tr>
          {mask:week}
            <tr>
            {mask:weeknum}
             {choose:akt}
               {when:0}<td class = "calender_week"><a href = "{url}">{kw}</a></td>{/when}
               {when:1}<td class = "calender_week_akt"><a href = "{url}">{kw}</a></td>{/when}
             {/choose}  
            {/mask}
            {mask:day}
              {choose:akt}
                {when:0}<td class = "calender_day"><a href = "{url}">{day}</a></td>{/when}
                {when:1}<td class = "calender_day_akt"><a href = "{url}">{day}</a></td>{/when}
              {/choose}   
            {/mask}
            </tr>
          {/mask}
          </table>
         {/mask}
      </td>
    </tr>
</table>
<!-- /KALENDER -->

{/mask} 
   </div>
  </td>
  <!-- /INHALT -->
  
  <!-- RECHTER SEITENBEREICH -->
  <td class="rahmentable_r">
   <div class ="home_img_counterweight" >&nbsp;</div>
   <div class ="greenback" id="right_bar">{right_bar}</div>
  </td> 
  <!-- /RECHTER SEITENBEREICH --> 
    
 </tr>
 <!-- FARBBOX LINKS -->
 <tr><td class="nav_l_farbbox"></td></tr>
 <!-- FOOTER -->
 <tr><td class="footer_td" colspan="3">{foo_bar}</td></tr>
</table>
<!-- /RAHMENTABLE -->
</body>
</html>
{/mask}
