<?php
function search_artikel($search, $data, $akt) {
   global $conf, $lang;
   
  if ($search = preg_replace("/[^\s\w]/i", "", preg_replace("/\s{2,}/i", " ", stripslashes(trim($search))))) {
     $searchList = explode(" ", $search);
     $buildq = "";
     foreach($searchList as $term) $artikelstmt     .= "(`artikel_headline` LIKE '%".addslashes($term)."%' OR `artikel_sub_headline` LIKE '%".addslashes($term)."%' OR `artikel_short_text` LIKE '%".addslashes($term)."%') AND ";
     foreach($searchList as $term) $artikeldatastmt .= "(`artikel_headline` LIKE '%".addslashes($term)."%' OR `artikel_long_text` LIKE '%".addslashes($term)."%') AND ";
     
     $result1 = dbquery("SELECT artikel_id, artikel_headline, artikel_sub_headline from ".$conf["db_namespace"]."artikel where (".preg_replace("/\sAND\s$/i", "", $artikelstmt).") and artikel_publish_date <= now() or artikel_publish_date is null;");
     if ( mysql_num_rows($result1) > 0)  {
        while ($row = mysql_fetch_object($result1)){
           $akt++; 
           $data->search->searchresults->result[$akt]->search_url  = $conf["indexname"] . "artikel/" . $row->artikel_id;
           $data->search->searchresults->result[$akt]->search_name = $row->artikel_headline;
           $data->search->searchresults->result[$akt]->search_text = $row->artikel_sub_headline;
        }
     } 
     $result2 = dbquery("SELECT artikel_id, artikel_part from ".$conf["db_namespace"]."artikel_daten  where (".preg_replace("/\sAND\s$/i", "", $artikelstmt).")");
     if ( mysql_num_rows($result2) >0)  {
        while ($row = mysql_fetch_object($result2)){
           $parentresult = dbquery("SELECT artikel_id, artikel_sub_headline from ".$conf["db_namespace"]."artikel where artikel_id = ".$row->artikel_id." and  artikel_publish_date >= now() or artikel_publish_date is null;");
           if (mysql_num_rows($parentresult) >0)  {
   	          if ($parentrow = mysql_fetch_object($parentresult)){
                 $akt++;
                 $data->search->searchresults->result[$akt]->search_url  = $conf["indexname"] . "artikel/0/" . $row->artikel_id."/" . $row->artikel_part;
                 $data->search->searchresults->result[$akt]->search_name = $row->artikel_headline;
                 $data->search->searchresults->result[$akt]->search_text = $row->artikel_sub_headline;
  	          }
           }   	
        }
     }
     return mysql_num_rows($result1) + mysql_num_rows($result2);
  } else {
  	return 0;
  }
}
?>