<?php
function search_artikel($search, $data) {
   $result1 = dbquery("SELECT artikel_id, artikel_headline, artikel_sub_headline from acme_artikel where (artikel_headline like '%".$search."%' or  artikel_sub_headline like '%".$search."%' or artikel_short_text like '%".$search."%') and artikel_publish_date <= now() or artikel_publish_date is null;");
   if ( mysql_num_rows($result1) > 0)  {
      while ($row = mysql_fetch_object($result1)){
         $data->search->searchresults->result[$akt]->search_url  = $conf["indexname"] . "artikel/" . $row->artikel_id;
         $data->search->searchresults->result[$akt]->search_name = $row->artikel_headline;
         $data->search->searchresults->result[$akt]->search_text = $row->artikel_sub_headline;
         $akt++;  
      }
   } 
   $result2 = dbquery("SELECT artikel_id, artikel_part from acme_artikel_daten  where (artikel_headline  like '%".$search."%' or  artikel_long_text like '%".$search."%')");
   if ( mysql_num_rows($result2) >0)  {
      while ($row = mysql_fetch_object($result2)){
         $parentresult = dbquery("SELECT artikel_id, artikel_sub_headline from acme_artikel where artikel_id = ".$row->artikel_id." and  artikel_publish_date >= now() or artikel_publish_date is null;");
         if (mysql_num_rows($parentresult) >0)  {
   	        if ($parentrow = mysql_fetch_object($parentresult)){
               $data->search->searchresults->result[$akt]->search_url  = $conf["indexname"] . "artikel/0/" . $row->artikel_id."/" . $row->artikel_part;
               $data->search->searchresults->result[$akt]->search_name = $row->artikel_headline;
               $data->search->searchresults->result[$akt]->search_text = $row->artikel_sub_headline;
               $akt++;  
   	        }
         }   	
      }
   }
   return mysql_num_rows($result1) + mysql_num_rows($result2);
}
?>