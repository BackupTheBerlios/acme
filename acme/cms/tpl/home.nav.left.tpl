{mask:main}
  <div id="navigation">

  <!-- nav name -->
  <!-- <div class="nav_name">{nav_name}</div> -->
  {mask:nav_elem} 
	  <!-- {mask:act} -->
	  <!-- aktiv-bild wird automatisch geparsed, muss also nicht ins template -->
      <!-- {name} -->
	  <!-- <img src="{src}" alt="{desc}" class="nav_img_active"> -->
      <!-- {/mask} -->
         <!-- {name} -->
        <a href="{nav_elem_url}">{mask:nav_elem_img}{mask:pas}<img src="{src}" alt="{desc}" class="nav_img_passive">{/mask}{/mask}</a>
      
    <!-- <div class="nav_element"><a href="{nav_elem_url}">{nav_elem_text}</a></div> -->

    
	{mask:nav_sub_elem} 
	<ul class="nav_sub_list">
       <!-- <div class="nav_sub_element"><a href="{nav_sub_elem_url}">{nav_sub_elem_text}</a></div> -->
		<li><a href="{nav_sub_elem_url}">{nav_sub_elem_text}</a></li>
    </ul>
	{/mask}
	
	
	
  {/mask}
</div>
{/mask}