{mask:main}
<div id="navigation">
<div class="nav_name">{nav_name}</div>
{mask:nav_elem} 
  <div class="nav_element"><a href="{nav_elem_url}">{nav_elem_text}</a></div>
  {mask:nav_sub_elem} 
   <div class="nav_sub_element"><a href="{nav_sub_elem_url}">{nav_sub_elem_text}</a></div>
  {/mask}
{/mask}
</div>
{/mask}