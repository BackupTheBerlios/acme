{mask:main}
{mask:block}
 {mis:typ:I}
   <div class="block_name">{name}</div>
   <div class="block_content">{content}</div>
 {/mis}
 {set:typ:I}
   {mask:image}
     <div class="block_image">
     <img src="{src}" alt="{desc}">
     </div> 
   {/mask}
 {/set}
{/mask}
{/mask}