<?php
function search_page($search) {
   $result = dbquery("SELECT page_id, page_name MATCH(page_headline, page_short_text, page_long_text) AGAINST('".$search."' IN BOOLEAN MODE) AS Score FROM acme_pages WHERE MATCH(page_headline, page_short_text, page_long_text) AGAINST ('".$search."' IN BOOLEAN MODE) and page_longtext_typ <> 'P';");
   if ( mysql_num_rows($result) >0)  {
   	  $akt=0;
      while ($row = mysql_fetch_object($result)){
         $page[$akt]->search_url  = $conf["indexname"] . "page/" . $row->page_id;
         $page[$akt]->search_name = $row->page_name;
         $page[$akt]->search_text = $row->page_short_text;
         $akt++;  
      }
      mysql_free_result($main_result);    
   }
   if ($akt > 0) return $page_result;  
}
?>