<?php 

  if ((getmodulnamebyid($mid) == "")){ $mid = "404";}
  rendermodul($mid);
  
function rendermodul($mid)
{
   global $conf;
   $my_result = dbquery("select * from acme_modules where modul_id='".$mid."'");
   if ( mysql_num_rows($my_result) == 1 )
      {
      $row = mysql_fetch_object($my_result);
      $modul_id = $row->modul_id;
      $modul_name = $row->modul_name;
      $modul_parent = $row->modul_parent;
      $modul_tpl = $row->modul_tpl;
      $modul_img_small = $row->modul_img_small;
      $modul_img_big = $row->modul_img_big;
      $modul_left_bar = $row->modul_left_bar;
      $modul_right_bar = $row->modul_right_bar;
      $modul_top_bar = $row->modul_top_bar;
      $modul_foo_bar = $row->modul_foo_bar;
      $modul_headline = $row->modul_headline;
      $modul_short_text = $row->modul_short_text;
      $modul_long_text = $row->modul_long_text;
      $modul_long_text_typ= $row->modul_long_text_typ;
      $modul_childs = $row->modul_childs;
      $modul_counter = $row->modul_counter;
      $modul_last_update = $row->modul_last_update;
      mysql_free_result($my_result);

      $data->img_small    = getimage($modul_img_small);
      $data->img_big      = getimage($modul_img_big);
      $data->headline     = $modul_headline;
      if ($modul_long_text_typ == "B") $data->short_text   = parse_bbcode(nltobr($modul_short_text));
      else $data->short_text   = $modul_short_text;
      if ($modul_long_text_typ == "B") $data->long_text    = parse_bbcode(nltobr($modul_long_text));
      else $data->long_text    = $modul_long_text;
      
      $data->counter      = $modul_counter;
      $data->last_update  = mydate2gerdatetime($modul_last_update);
      if ($modul_parent <> ""){$data->modul   = "<a href=\"".$conf["indexname"]."?page=modul&mid=".$modul_parent."\">".getmodulheadlinebyid($modul_parent)."</a>";}
      getmodulchildsforpreview(&$data, $modul_id, $modul_childs);
      $data->left_bar  = getbarfromcache($modul_left_bar);
      $data->right_bar = getbarfromcache($modul_right_bar);
      $data->top_bar   = getbarfromcache($modul_top_bar);
      $data->foo_bar   = getbarfromcache($modul_foo_bar);
      $data->titel     = $modul_headline;
      incmodulcounter($modul_id, $modul_counter);
      $page_output = sprintt($data, "cms/tpl/".gettemplatebyid($modul_tpl).".tpl");
      }
   if ($modul_long_text_typ == "H"){echo $page_output;}
   if ($modul_long_text_typ == "B"){echo $page_output;}
   if ($modul_long_text_typ == "P"){echo OutputPhpDocument($page_output);}
}
?>   