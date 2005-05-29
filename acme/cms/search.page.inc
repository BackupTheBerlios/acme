<?php
function search_page($search, $data, $akt) {
   global $conf, $lang;

  if ($search = preg_replace("/[^\s\w]/i", "", preg_replace("/\s{2,}/i", " ", stripslashes(trim($search))))) {
     $searchList = explode(" ", $search);
     $buildq = "";
     foreach($searchList as $term) $pagestmt     .= "(`page_headline` LIKE '%".addslashes($term)."%' OR `page_short_text` LIKE '%".addslashes($term)."%' OR `page_short_text` LIKE '%".addslashes($term)."%') AND ";
   
     $query = "SELECT page_id, page_name from ".$conf["db_namespace"]."pages where (".$pagestmt.") and page_long_text_typ <> 'P'";
     $result = dbquery($query);
     if ( mysql_num_rows($result) >0)  {
   	    $akt=0;
        while ($row = mysql_fetch_object($result)){
           $akt++;
           $data->search->searchresults->result[$akt]->search_url  = $conf["indexname"] . "page/" . $row->page_id;
           $data->search->searchresults->result[$akt]->search_name = $row->page_name;
           $data->search->searchresults->result[$akt]->search_text = $row->page_short_text;
        }
     }
     return mysql_num_rows($result);
  } else {
  	return 0;
  }	  
}
?>