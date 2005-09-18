{mask:main}
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<html>
<head>
</head>
<body>
{mask:artikel}
 <h2><i>{page}:</i></h2> 
 <h2>{headline}</h2>
 <h1>{sub_headline}</h1>
 <p class="teaser"> <font class="autor">({author}, {create_date})</font>&nbsp; 
 {short_text}</p>
 {mask:long_text}<p>{text}</p>{/mask}
 <p> letzte Aktualisierung: {modify_date}</p>
{/mask}
</body>
</html>
{/mask} 