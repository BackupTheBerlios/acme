<?php
function search_page($search, $data) {
   $query = "SELECT page_id, page_name from ".$conf["db_namespace"]."pages where (page_headline like '%".$search."%' Or page_short_text like '%".$search."%' or page_long_text like '%".$search."%') and page_long_text_typ <> 'P'";
   $result = dbquery($query);
   if ( mysql_num_rows($result) >0)  {
   	  $akt=0;
      while ($row = mysql_fetch_object($result)){
         $data->search->searchresults->result[$akt]->search_url  = $conf["indexname"] . "page/" . $row->page_id;
         $data->search->searchresults->result[$akt]->search_name = $row->page_name;
         $data->search->searchresults->result[$akt]->search_text = $row->page_short_text;
         $akt++;  
      }

   }
   return mysql_num_rows($result);
}
?>