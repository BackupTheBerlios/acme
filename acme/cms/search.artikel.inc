<?php
function search_artikel($search) {
   $result = dbquery("SELECT artikel_id, artikel_headline, artikel_sub_headline  MATCH(artikel_headline, artikel_sub_headline,artikel_short_text) AGAINST('".$search."' IN BOOLEAN MODE) AS Score FROM acme_artikel WHERE MATCH(artikel_headline, artikel_sub_headline,artikel_short_text) AGAINST ('".$search."' IN BOOLEAN MODE) and artikel_publish_date >= now() or artikel_publish_date is null;");
   if ( mysql_num_rows($result) >0)  {
   	  $akt=0;
      while ($row = mysql_fetch_object($result)){
         $page[$akt]->search_url  = $conf["indexname"] . "artikel//" . $row->artikel_id;
         $page[$akt]->search_name = $row->artikel_headline;
         $page[$akt]->search_text = $row->artikel_sub_headline;
         $akt++;  
      }
      mysql_free_result($main_result);    
   }
   $result = dbquery("SELECT artikel_id, artikel_part  MATCH(artikel_headline, artikel_long_text) AGAINST('".$search."' IN BOOLEAN MODE) AS Score FROM acme_artikel_daten WHERE MATCH(artikel_headline, artikel_long_text) AGAINST ('".$search."' IN BOOLEAN MODE);");
   if ( mysql_num_rows($result) >0)  {
   	  $akt=0;
      while ($row = mysql_fetch_object($result)){
         $parentresult = dbquery("SELECT artikel_id, artikel_sub_headline from acme_artikel where artikel_id = ".$row->artikel_id." and  artikel_publish_date >= now() or artikel_publish_date is null;");
         if (mysql_num_rows($parentresult) >0)  {
   	        if ($parentrow = mysql_fetch_object($parentresult)){
               $artikel[$akt]->search_url  = $conf["indexname"] . "artikel//" . $row->artikel_id."/" . $row->artikel_part;
               $artikel[$akt]->search_name = $parentrow->artikel_headline;
               $artikel[$akt]->search_text = $parentrow->artikel_sub_headline;
               $akt++;  
   	        }
         }   	
      }
      mysql_free_result($main_result);    
   }
   if ($akt > 0) return $artikel_result;  
}
