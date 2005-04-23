<?php 
function write_bbc($f, $ta) {
   write_bbc_heads($f, $ta);
   write_bbc_textformat($f, $ta);
   write_bbc_glossar($f, $ta);
   write_bbc_link($f, $ta);
   write_link($f, $ta);
   echo "<br />";
   write_bbc_color($f, $ta);
   echo "<br />";
}   
   
function write_bbc_heads($f, $ta){
  echo "<input class=\"bbcode-button\" type=\"button\" name=\"h3\" value=\"h3\" title=\"[h3]...[/h3]\" onclick=\"bbcode('" . $f. "', '" . $ta . "', 'h3');\" />".
       "<input class=\"bbcode-button\" type=\"button\" name=\"h4\" value=\"h4\" title=\"[h4]...[/h4]\" onclick=\"bbcode('" . $f. "', '" . $ta . "', 'h4');\" />".
       "<input class=\"bbcode-button\" type=\"button\" name=\"h5\" value=\"h5\" title=\"[h5]...[/h5]\" onclick=\"bbcode('" . $f. "', '" . $ta . "', 'h5');\" />";
     echo "\n";
}

function write_bbc_textformat($f, $ta){
  echo "<input class=\"bbcode-button\" style = \"font-weight:lighter;\"          type=\"button\" name=\"l\" value=\"l\" title=\"[l]...[/l]\" onclick=\"bbcode('" . $f. "', '" . $ta . "', 'l');\" />".
       "<input class=\"bbcode-button\" style = \"font-weight:bold;\"             type=\"button\" name=\"b\" value=\"b\" title=\"[b]...[/b]\" onclick=\"bbcode('" . $f. "', '" . $ta . "', 'b');\" />".
       "<input class=\"bbcode-button\" style = \"font-weight:bolder;\"           type=\"button\" name=\"bb\" value=\"bb\" title=\"[bb]...[/bb]\" onclick=\"bbcode('" . $f. "', '" . $ta . "', 'bb');\" />".
       "<input class=\"bbcode-button\" style = \"font-style:italic;\"            type=\"button\" name=\"i\" value=\"i\" title=\"[i]...[/i]\" onclick=\"bbcode('" . $f. "', '" . $ta . "', 'i');\" />". 
       "<input class=\"bbcode-button\" style = \"text-decoration:overline;\"     type=\"button\" name=\"ol\" value=\"ol\" title=\"[ol]...[/ol]\" onclick=\"bbcode('" . $f. "', '" . $ta . "', 'ol');\" />".
       "<input class=\"bbcode-button\" style = \"text-decoration:line-through;\" type=\"button\" name=\"lt\" value=\"lt\" title=\"[lt]...[/lt]\" onclick=\"bbcode('" . $f. "', '" . $ta . "', 'lt');\" />".
       "<input class=\"bbcode-button\" style = \"text-decoration:underline;\"    type=\"button\" name=\"ul\" value=\"ul\" title=\"[ul]...[/ul]\" onclick=\"bbcode('" . $f. "', '" . $ta . "', 'ul');\" />";
     echo "\n";
     
}     
function write_bbc_color($f, $ta){
  echo "<input class=\"bbcode-button\" style = \"color:red;\"    type=\"button\" name=\"color:red\"    value=\"red\"    title=\"color:red\"    onclick=\"bbcode('" . $f. "', '" . $ta . "', 'red');\" />".
       "<input class=\"bbcode-button\" style = \"color:green;\"  type=\"button\" name=\"color:green\"  value=\"green\"  title=\"color:green\"  onclick=\"bbcode('" . $f. "', '" . $ta . "', 'green');\" />".
       "<input class=\"bbcode-button\" style = \"color:blue;\"   type=\"button\" name=\"color:blue\"   value=\"blue\"   title=\"color:blue\"   onclick=\"bbcode('" . $f. "', '" . $ta . "', 'blue');\" />".
       "<input class=\"bbcode-button\" style = \"color:gray;\"   type=\"button\" name=\"color:gray\"   value=\"gray\"   title=\"color:gray\"   onclick=\"bbcode('" . $f. "', '" . $ta . "', 'gray');\" />". 
       "<input class=\"bbcode-button\" style = \"color:yellow;\" type=\"button\" name=\"color:yellow\" value=\"yellow\" title=\"color:yellow\" onclick=\"bbcode('" . $f. "', '" . $ta . "', 'yellow');\" />".
       "<input class=\"bbcode-button\" style = \"color:maroon;\" type=\"button\" name=\"color:maroon\" value=\"maroon\" title=\"color:maroon\" onclick=\"bbcode('" . $f. "', '" . $ta . "', 'maroon');\" />".
       "<input class=\"bbcode-button\" style = \"color:lime;\"   type=\"button\" name=\"color:lime\"   value=\"lime\"   title=\"color:lime\"   onclick=\"bbcode('" . $f. "', '" . $ta . "', 'lime');\" />";
     echo "\n";
     
}     
function write_bbc_glossar($f, $ta){     
  echo "<input class=\"bbcode-button\" type=\"button\" name=\"glossar\" value=\"glossar\" title=\"[glossar]...[/glossar]\" onclick=\"bbcode('" . $f. "', '" . $ta . "', 'glossar');\" />";
  echo "\n";
}
function write_bbc_link($f, $ta){     
  echo "<input class=\"bbcode-button\" type=\"button\" name=\"link\" value=\"link\" title=\"[link=]...[/link]\" onclick=\"insert_link('" . $f. "', '" . $ta . "');\" />";
  echo "\n";
}
function write_link($f, $ta){ 
	global $conf;
	echo "<input class=\"bbcode-button\" type=\"button\" name=\"links\" value=\"links\" title=\"...\" onclick=\"void window.open('".$conf["indexbase"]."/link.php?name=".$f."&field=".$ta."');\" />";
}
?>