{mask:main}
<div id="navigation">
{mask:nav_elem} 
{set:nav_elem_img}<div class="nav_i_farbbox_{nav_elem_h}"><a href="{nav_elem_url}">{mask:nav_elem_img}<img src="{src}" alt="{desc}">{/mask}</a></div>{/set} 
{mis:nav_elem_img}<div  class="nav_l_farbbox_{nav_elem_h}"><a class="nav_l_link" href="{nav_elem_url}">{nav_elem_text}</a></div>{/mis}
{/mask}
</div>
{/mask}