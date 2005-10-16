<?php
/**
* Socket functions -  Testing string with special patterns.    
*
* @author	Thomas Weinert	<subjective@subjective.de>
* @version	1.4.3
* @package  Netzbrett
* @modulegroup    Netzbrett_Program
* @module   Netzbrett_Program_Check
*/

 
/**
* Checks a string with a regular expression
*@access public
*@param string $str2chk string to check
*@param string $type2chk type of regular expression to use
*@param boolean $mustfilled $str2chk must contain data
*
*@return boolean check result
*/ 
function chkinput($str2chk,$type2chk="alpha",$mustfilled=false) {

   if (strlen($str2chk)>0) {
      switch ($type2chk) {
            case "alpha"  :return (chkvalalpha($str2chk));
            case "email"  :return (chkvalemail($str2chk));
            case "http"   :return (chkvalhttp($str2chk));
            case "chars"  :return (chkvalchars($str2chk));
            case "nohtml" :return (chkNoHTML($str2chk));
            default       :return (chkvalalphanum($str2chk));
          }
        } else {
          if ($mustfilled) {
            return false;
          } else {
             return true;
          }
        }
  }

 
/**
* String can contain letters language specific special chars ".", "," and "-".
*@param string $str2chk string to check
*@return boolean result of check
*/
  function chkvalalpha($str2chk) {
    return (ereg("^[a-zA-Z�������������������������������������������������������������\. ,-]+$", $str2chk));
  }

/**
* String can contain letters, numbers language specific special chars ".", "," and "-".
*@param string $str2chk string to check
*@return boolean result of check
*/
  function chkvalalphanum($str2chk) {
    return (ereg("^[a-zA-Z0-9�������������������������������������������������������������:\. ,?!-]+$", $str2chk));
  }

/**
* String should not contain HTML
* @param string $str2chk string to check
* @return boolean result of check
*/  
  function chkNoHTML($str2chk) {
    return (ereg("^[^<>\"]+$", $str2chk));
  }

/**
* String should be an email address
*@param string $str2chk string to check
*@return boolean result of check
*/
  function chkvalemail($str2chk) {
    return (ereg('^[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+'.
                 '@'.
                 '[-!#$%&\'*+\\/0-9=?A-Z^_`a-z{|}~]+\.'.
                 '[-!#$%&\'*+\\./0-9=?A-Z^_`a-z{|}~]+$', $str2chk));
  }

/**
* String should be an http address
*@param string $str2chk string to check
*@return boolean result of check
*/
  function chkvalhttp($str2chk) {
    return ((eregi('^http://[a-z0-9_-]+\.[a-z0-9_-]*\.?[a-z0-9_-]+[a-z0-9/\._-]*$',$str2chk)) ||
            (eregi('^www\.[a-z0-9_-]+\.[a-z0-9_-]+[a-z0-9/\._-]*$',$str2chk)));

  } 

/**
* String should contain one Letter minimum
*@param string $str2chk string to check
*@return boolean result of check
*/
  function chkvalchars($str2chk) {
    return (eregi('[a-zA-Z]+',$str2chk));
  }


?>