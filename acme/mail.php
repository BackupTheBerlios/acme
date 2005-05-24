<?php
  if ($typ=="stdkontakt") {
  	 $mailadr= "innomine@gmx.net";
     $subject= "Kontaktformular";
  }
  if ($typ=="kochbuchbestellung") {
     $mailadr= "innomine@gmx.net";
     $subject= "Kochbuchbestellung";
  }   
  if ($typ=="pressekontakt") {
     $mailadr= "innomine@gmx.net";
     $subject= "Pressekontaktformular";
  }   
  if ($typ=="geschaeftsleitungkontakt") {
     $mailadr= "innomine@gmx.net";
     $subject= "Pressekontaktformular";
  }   
  $message= 'Nachrichten an '.$admin.' von '.$e-mail.":\n\n";
  foreach($HTTP_POST_VARS as $name=> $value) {
  	if ($value<>""){
       $message.= "$name:$value\n";
  	}   
  }
  mail($mailadr, $subject, $message, "From: $e-mail");
  
  header('Location: http://omikron-webservice.de/medinet/page/29');
?>
