<?php
/*
   gets the fields mail forms an sends a mail depending on the var $typ 
*/
  if ($typ=="stdkontakt") {
    $mailadr= "info@spessartklinik.de";
     $subject= "Kontaktformular";
  }
  if ($typ=="kiklikontakt") {
    $mailadr= "info@spessartklinik.de";
     $subject= "Kontaktformular Kinderklinik";
  }
  if ($typ=="hgzkontakt") {
    $mailadr= "info@spessartklinik.de"; // hpz@spessart-klinik.de
     $subject= "Kontaktformular HGZ";
  }
  if ($typ=="kochbuchbestellung") {
     $mailadr= "info@spessartklinik.de";
     $subject= "Kochbuchbestellung";
  }   
  if ($typ=="pressekontakt") {
     $mailadr= "info@spessartklinik.de";
     $subject= "Pressekontaktformular";
  }   
  if ($typ=="geschaeftsleitungkontakt") {
     $mailadr= "info@spessartklinik.de";
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
