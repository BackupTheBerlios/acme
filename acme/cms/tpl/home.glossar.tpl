{mask:main}
<html>
<head>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
</head>
<body>
<table>
<tr>
{mask:glossar_parts}
   <td><a href = "{url}">{part}</a></td>
{/mask}
</tr>
</table>
<table>
<tr>
<td>
<table>
{mask:glossar_eintr}
 <tr><td><a href = "{url}">{titel}</a></td></tr>
{/mask}         
</table>
</td>
<td>
{mask:glossar}
   <h1>{titel}</h1>
   {subtpl}
{/mask}
</td>
</tr>
</table>
</body>
</html>
{/mask}