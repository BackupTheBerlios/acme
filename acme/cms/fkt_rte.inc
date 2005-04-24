<?php 
function write_bbc($f, $ta) {
   write_bbc_heads($f, $ta);
   echo "&nbsp;";
   write_bbc_link($f, $ta);
   write_link($f, $ta);
   echo "&nbsp;";
   write_bbc_glossar($f, $ta);
   echo "<br />";
   write_bbc_textformat($f, $ta);
   echo "&nbsp;";
   write_bbc_color($f, $ta);
   echo "<br />";
}   
   
function write_bbc_heads($f, $ta){
  echo "<input class=\"bbcode-button\" type=\"button\" name=\"h3\" value=\"h3\" title=\"headline 3\" onclick=\"bbcode('" . $f. "', '" . $ta . "', 'h3');\" />".
       "<input class=\"bbcode-button\" type=\"button\" name=\"h4\" value=\"h4\" title=\"headline 4\" onclick=\"bbcode('" . $f. "', '" . $ta . "', 'h4');\" />".
       "<input class=\"bbcode-button\" type=\"button\" name=\"h5\" value=\"h5\" title=\"headline 5\" onclick=\"bbcode('" . $f. "', '" . $ta . "', 'h5');\" />";
}

function write_bbc_textformat($f, $ta){
  echo "<input class=\"bbcode-button\" style = \"font-weight:bold;\"             type=\"button\" name=\"b\" value=\"b\" title=\"fett\" onclick=\"bbcode('" . $f. "', '" . $ta . "', 'b');\" />".
       "<input class=\"bbcode-button\" style = \"font-style:italic;\"            type=\"button\" name=\"i\" value=\"i\" title=\"kursiv\" onclick=\"bbcode('" . $f. "', '" . $ta . "', 'i');\" />". 
       "<input class=\"bbcode-button\" style = \"text-decoration:underline;\"    type=\"button\" name=\"ul\" value=\"ul\" title=\"unterstrichen\" onclick=\"bbcode('" . $f. "', '" . $ta . "', 'ul');\" />".
       "<input class=\"bbcode-button\" style = \"text-decoration:overline;\"     type=\"button\" name=\"ol\" value=\"ol\" title=\"überstrichen\" onclick=\"bbcode('" . $f. "', '" . $ta . "', 'ol');\" />".
       "<input class=\"bbcode-button\" style = \"text-decoration:line-through;\" type=\"button\" name=\"lt\" value=\"lt\" title=\"durchgestrichen\" onclick=\"bbcode('" . $f. "', '" . $ta . "', 'lt');\" />";
}     
function write_bbc_color($f, $ta){
  echo "<input class=\"bbcode-button\" style = \"background-color:red;\"    type=\"button\" name=\"color:red\"    value=\"\"    title=\"color:red\"    onclick=\"bbcode('" . $f. "', '" . $ta . "', 'red');\" />".
       "<input class=\"bbcode-button\" style = \"background-color:green;\"  type=\"button\" name=\"color:green\"  value=\"\"  title=\"color:green\"  onclick=\"bbcode('" . $f. "', '" . $ta . "', 'green');\" />".
       "<input class=\"bbcode-button\" style = \"background-color:blue;\"   type=\"button\" name=\"color:blue\"   value=\"\"   title=\"color:blue\"   onclick=\"bbcode('" . $f. "', '" . $ta . "', 'blue');\" />".
       "<input class=\"bbcode-button\" style = \"background-color:gray;\"   type=\"button\" name=\"color:gray\"   value=\"\"   title=\"color:gray\"   onclick=\"bbcode('" . $f. "', '" . $ta . "', 'gray');\" />". 
       "<input class=\"bbcode-button\" style = \"background-color:yellow;\" type=\"button\" name=\"color:yellow\" value=\"\" title=\"color:yellow\" onclick=\"bbcode('" . $f. "', '" . $ta . "', 'yellow');\" />".
       "<input class=\"bbcode-button\" style = \"background-color:maroon;\" type=\"button\" name=\"color:maroon\" value=\"\" title=\"color:maroon\" onclick=\"bbcode('" . $f. "', '" . $ta . "', 'maroon');\" />";
}     
function write_bbc_glossar($f, $ta){     
  echo "<input class=\"bbcode-button\" type=\"button\" name=\"glossar\" value=\"glossar\" title=\"[glossar]...[/glossar]\" onclick=\"bbcode('" . $f. "', '" . $ta . "', 'glossar');\" />";
}
function write_bbc_link($f, $ta){     
  echo "<input class=\"bbcode-button\" type=\"button\" name=\"ext. link\" value=\"ext. link\" title=\"externer link URL [url=]...[/url]\" onclick=\"insert_link('" . $f. "', '" . $ta . "');\" />";
}
function write_link($f, $ta){ 
	global $conf;
	echo "<input class=\"bbcode-button\" type=\"button\" name=\"int. link\" value=\"int. link\" title=\"interne links\" onclick=\"void window.open('".$conf["indexbase"]."/link.php?name=".$f."&field=".$ta."');\" />";
}
?>