<?php /* ***** Orca Forum - Body File ************************* */

/* ***************************************************************
* Orca Forum v4.0b
*  A simple threaded forum for a small community
* Copyright (C) 2004 GreyWyvern
*
* This program may be distributed under the terms of the GPL
*   - http://www.gnu.org/licenses/gpl.txt
* 
* See the readme.txt file for installation instructions.
*************************************************************** */

/* ***** Prepare Workspace ************************************ */

$vData['parent'] = "-1";

if (isset($_COOKIE['of_cookie'])) {
  $crumble = explode(" :: ", base64_decode($_COOKIE['of_cookie']));
  $vData['author'] = to_scrn($crumble[0]);
  $vData['email'] = to_scrn($crumble[1]);
  $vData['notify'] = $crumble[2];
  $vData['subject'] = "";
  $vData['message'] = "";
  $vData['image'] = to_scrn($crumble[3]) or $vData['image'] = "http://";
  $vData['date'] = $fData['time'];
  $vData['cookify'] = "Yes";

} else {
  $vData['author'] = "";
  $vData['email'] = "";
  $vData['notify'] = "no";
  $vData['subject'] = "";
  $vData['message'] = "";
  $vData['image'] = "http://";
  $vData['date'] = $fData['time'];
  $vData['cookify'] = "No";

}


if ($_POST['command'] == "Preview") {
  $mData['author'] = to_scrn((strlen($_POST['author']) > 32) ? substr($_POST['author'], 0, 32) : $_POST['author']);
  $mData['email'] = parseEmail(to_scrn($_POST['email']));
  $mData['notify'] = (isset($_POST['notify'])) ? $_POST['notify'] : NULL;
  $mData['subject'] = to_scrn((strlen($_POST['subject']) > 64) ? substr($_POST['subject'], 0, 64) : $_POST['subject']);
  $mData['message'] = parseMessage(str_replace(chr(13), "", $_POST['message']));
    if (!$mData['message']) $mData['subject'] .= " (n/t)";
  $mData['image'] = parseImage(to_scrn($_POST['image']));
  $mData['date'] = $fData['time'];

  $vData['author'] = $mData['author'];
  $vData['email'] = to_scrn($_POST['email']);
  $vData['notify'] = $mData['notify'];
  $vData['subject'] = to_scrn($_POST['subject']);
  $vData['message'] = to_scrn(str_replace(chr(13), "", $_POST['message']));
  $vData['image'] = to_scrn($_POST['image']);
  $vData['cookify'] = (isset($_POST['cookify'])) ? "Yes" : "No";
  $vData['parent'] = $_POST['parent'];

  if ($vData['parent'] != "-1") $mData['prevmsg'] = get_row($vData['parent']);

} else if (isset($_GET['msg'])) {
  $mData['author'] = to_scrn(db_result($fData['message'], 0, "author"));
  $mData['email'] = parseEmail(to_scrn(db_result($fData['message'], 0, "email")));
  $mData['subject'] = to_scrn(db_result($fData['message'], 0, "subject"));
  $mData['message'] = parseMessage(db_result($fData['message'], 0, "message"));
  $mData['image'] = parseImage(to_scrn(db_result($fData['message'], 0, "image")));
  $mData['date'] = db_result($fData['message'], 0, "date") + $fData['offset'];

  $vData['subject'] = (preg_match("/^re:\s/i", $mData['subject'])) ? $mData['subject'] : "Re: {$mData['subject']}";
    $vData['subject'] = preg_replace("/\s\(n\/t\)$/i", "", $vData['subject']);
  $vData['message'] = (db_result($fData['message'], 0, "message")) ? to_scrn("[quote=".db_result($fData['message'], 0, "author")."]\n".db_result($fData['message'], 0, "message")."[/quote]\n") : "";
  $vData['parent'] = $_GET['msg'];

  if (db_result($fData['message'], 0, "parent") != "-1") $mData['prevmsg'] = get_row(db_result($fData['message'], 0, "parent"));

}

if (isset($mData['prevmsg'])) {
  $mData['prevsubject'] = to_scrn(db_result($mData['prevmsg'], 0, "subject"));
  $mData['prevauthor'] = to_scrn(db_result($mData['prevmsg'], 0, "author"));
  $mData['prevpid'] = to_scrn(db_result($mData['prevmsg'], 0, "pid"));

}

$lData['top'] = get_kids($vData['parent']);
$lData['toprows'] = db_numrows($lData['top']);
if ($maxThreads != 0 && $vData['parent'] == "-1" && $lData['toprows'] > $maxThreads) {
  for ($x = $maxThreads; $x < $lData['toprows']; $x++) snipThread(db_result($lData['top'], $x, "pid"));
}

if (isset($fData['search'])) {
  $lData['top'] = $fData['schlist'];
  $lData['toprows'] = $fData['schlistrows'];
}

if ($fData['start'] > $lData['toprows']) $fData['start'] = 0;

?>


<div id="of_main">

  <div id="of_controls">
    <div class="of_controlrow">
      <form action="<?php echo $_SERVER['PHP_SELF']; ?>" method="post" class="of_form">
        <div>
          <span>
            <label for="of_time"><?php echo $lang['panel2']; ?></label>
            <select name="time" id="of_time" size="1">
              <option value="0"<?php if ($_COOKIE['of_mark'] == 0) echo " selected=\"selected\""; ?>><?php echo $lang['panel3']; ?></option>
              <option value="3600"<?php if ($_COOKIE['of_mark'] == 3600) echo " selected=\"selected\""; ?>><?php echo $lang['panel4']; ?></option>
              <option value="10800"<?php if ($_COOKIE['of_mark'] == 10800) echo " selected=\"selected\""; ?>><?php echo $lang['panel5']; ?></option>
              <option value="21600"<?php if ($_COOKIE['of_mark'] == 21600) echo " selected=\"selected\""; ?>><?php echo $lang['panel6']; ?></option>
              <option value="43200"<?php if ($_COOKIE['of_mark'] == 43200) echo " selected=\"selected\""; ?>><?php echo $lang['panel7']; ?></option>
              <option value="86400"<?php if ($_COOKIE['of_mark'] == 86400) echo " selected=\"selected\""; ?>><?php echo $lang['panel8']; ?></option>
              <option value="259200"<?php if ($_COOKIE['of_mark'] == 259200) echo " selected=\"selected\""; ?>><?php echo $lang['panel9']; ?></option>
              <option value="604800"<?php if ($_COOKIE['of_mark'] == 604800) echo " selected=\"selected\""; ?>><?php echo $lang['panela']; ?></option>
              <option value="1209600"<?php if ($_COOKIE['of_mark'] == 1209600) echo " selected=\"selected\""; ?>><?php echo $lang['panelb']; ?></option>
              <option value="2592000"<?php if ($_COOKIE['of_mark'] == 2592000) echo " selected=\"selected\""; ?>><?php echo $lang['panelc']; ?></option>
            </select>
            <input type="submit" name="command_mark" value="<?php echo $lang['paneld']; ?>" />
          </span>
        </div>
      </form>
      <form action="<?php echo $_SERVER['PHP_SELF']; ?>" method="get" class="of_form">
        <div>
          <input type="text" name="s" <?php if (isset($_GET['s'])) echo "value=\"".to_scrn($_GET['s'])."\" "; ?>/>
          <input type="submit" value="<?php echo $lang['panel1']; ?>" <?php if (!$fData['msgtotal']) echo "disabled=\"disabled\" "; ?>/>
        </div>
      </form>
    </div>
    <div class="of_controlrow">
      <span>
        <a href="<?php echo $_SERVER['PHP_SELF']; ?>"><?php echo (isset($_GET['msg']) || $_POST['command'] == "Preview" || $fData['start']) ? $lang['panelg'] : $lang['panelh']; ?></a> |
        <a href="#of_post"><?php echo (isset($_GET['msg'])) ? $lang['paneli'] : $lang['panelj']; ?></a>
      </span>
      <script type="text/javascript"><!--
        function expcol_all(dir) {
          for (var x = 0; x < <?php echo $lData['toprows']; ?>; x++) {
            try {
              document.getElementById('of_gen' + x).style.display = dir;
              if (dir == "none") {
                document.getElementById('of_switch' + x).innerHTML = "+";
              } else document.getElementById('of_switch' + x).innerHTML = "&ndash;";
            } catch(err) {}
          }
        }

        document.write("<input type=\"button\" value=\"<?php echo $lang['panele']; ?>\" <?php echo ($lData['toprows']) ? "onclick=\\\"expcol_all('block')\\\"" : "disabled=\\\"disabled\\\""; ?> />");
        document.write("<input type=\"button\" value=\"<?php echo $lang['panelf']; ?>\" <?php echo ($lData['toprows']) ? "onclick=\\\"expcol_all('none')\\\"" : "disabled=\\\"disabled\\\""; ?> />");
      // --></script>
      <noscript>
        <div>
          <input type="button" value="<?php echo $lang['panele']; ?>" disabled="disabled" />
          <input type="button" value="<?php echo $lang['panelf']; ?>" disabled="disabled" />
        </div>
      </noscript>
    </div>
  </div>

  <?php if (isset($fData['error'])) { ?> 
    <div id="of_error">
      <?php echo $fData['error']; ?> 
    </div>
  <?php } ?>

  <?php if (isset($fData['success'])) { ?> 
    <div id="of_success">
      <?php echo $fData['success']; ?> 
    </div>
  <?php } ?>

  <?php if (isset($fData['search'])) { ?> 
     <div id="of_search">
       <?php printf($lang['search'], to_scrn($fData['search'])); ?>
     </div>
  <?php } ?>


  <?php if ($_POST['command'] == "Preview" || isset($_GET['msg'])) {

    if (isset($fData['matron'])) { ?> 
      <div id="of_threadtop">
        <?php echo $lang['message1']; ?> 
        <a class="of_post_subject" href="<?php echo $_SERVER['PHP_SELF']."?msg={$fData['matron'][3]}"; ?>"><?php echo to_scrn($fData['matron'][0]); ?></a>
        <span class="of_post_author" title="<?php echo $fData['matron'][4]; ?>"><?php echo to_scrn($fData['matron'][1]); ?></span>
        <span class="of_post_date<?php if ($fData['matron'][2] > time() - $_COOKIE['of_mark']) echo "_new"; ?>"><?php echo gmdate($dateFormat, $fData['matron'][2] + $fData['offset']); ?></span>
      </div>
    <?php } ?>

    <table id="of_message" cellpadding="3" cellspacing="0" border="0">
      <tr>
        <th colspan="2"><?php echo $mData['subject'].(($_POST['command'] == "Preview") ? $lang['message2'] : ""); ?></th>
      </tr>
      <tr>
        <td id="of_message_column">
          <strong id="of_author"><?php echo $mData['author']; ?></strong><br />

          <?php if (isset($mData['email'])) { ?>
            <a id="of_emaillink" href="mailto:<?php echo $mData['email']; ?>" title="<?php printf($lang['message3'], $mData['author']); ?>"><?php echo $lang['message4']; ?></a><br />
          <?php } ?>

          <?php if (isset($mData['image'])) { ?> 
            <img id="of_avatar" src="<?php echo $mData['image']; ?>" alt="<?php echo $lang['message5']; ?>" /><br />
          <?php } ?>

          <small id="of_date">
            <?php echo $lang['message6']; ?><br />
            <?php echo gmdate($dateFormat, $mData['date']); ?> 
          </small>

        </td>
        <td id="of_message_text">
          <?php echo nl2br($mData['message']); ?> &nbsp;
        </td>
      </tr>
      <?php if (isset($mData['prevmsg'])) { ?> 
        <tr>
          <td id="of_message_footer" colspan="2">
            <?php echo $lang['message7']; ?>  
            <a href="<?php echo $_SERVER['PHP_SELF']."?msg=".$mData['prevpid']; ?>"><strong><?php echo $mData['prevsubject']; ?></strong></a>
            <?php printf($lang['message8'], $mData['prevauthor']); ?> 
          </td>
        </tr>
      <?php } ?>
    </table>
  <?php } 
  
   if ($_POST['command'] != "Preview" && $fData['msgtotal']) { ?>
    <div id="of_messages">
      <script type="text/javascript"><!--
        function vis_tog(id, swt) {
          if (document.getElementById(id).style.display == "" || document.getElementById(id).style.display == "none") {
            document.getElementById(id).style.display = "block";
            document.getElementById(swt).innerHTML = "&ndash;";
          } else {
            document.getElementById(id).style.display = "none";
            document.getElementById(swt).innerHTML = "+";
          }
        }
      // --></script>

      <?php /* ***** Print Message List *********************** */

      if ($lData['toprows']) {

        if (isset($_GET['msg'])) { ?> 
          <p><?php echo $lang['list1']; ?></p>
        <?php }

        $lData['threadlimit'] = ($threadsPerPage + $fData['start'] > $lData['toprows']) ? $lData['toprows'] : $threadsPerPage + $fData['start'];

        for ($x = $fData['start']; $x < $lData['threadlimit']; $x++) {
          $lData['replies'] = 0;
          $thisList = "";

          $lData['next'] = get_kids(db_result($lData['top'], $x, "pid"));
          if (db_numrows($lData['next'])) {
            ob_start();

            for ($y = 0; $y < db_numrows($lData['next']); $y++) listChildren(db_result($lData['next'], $y, "pid"));

            $thisList = ob_get_contents();
            ob_end_clean();
          } ?> 

          <div class="of_topLevelPost">
            <?php if (trim($thisList)) { ?> 
              <script type="text/javascript"><!--
                document.write("<span class=\"of_post_expand\" id=\"of_switch<?php echo $x; ?>\" onclick=\"vis_tog('of_gen<?php echo $x; ?>', 'of_switch<?php echo $x; ?>');\"><?php echo ($threadCollapse) ? "+" : "&ndash;"; ?></span>");
              // --></script>
            <?php } else { ?>
              <script type="text/javascript"><!--
                document.write("<span class=\"of_post_expand\">&ndash;</span>");
              // --></script>
            <?php } ?>

            <a class="of_post_subject" href="<?php echo $_SERVER['PHP_SELF']."?msg=".db_result($lData['top'], $x, "pid"); ?>"><?php echo to_scrn(db_result($lData['top'], $x, "subject")); ?></a>
            <span class="of_post_author" title="<?php echo db_result($lData['top'], $x, "ip"); ?>"><?php echo to_scrn(db_result($lData['top'], $x, "author")); ?></span>
            <span class="of_post_date<?php if (db_result($lData['top'], $x, "date") > time() - $_COOKIE['of_mark']) echo "_new"; ?>"><?php echo gmdate($dateFormat, db_result($lData['top'], $x, "date") + $fData['offset']); ?></span>
            <span class="of_post_replies">(<?php echo $lData['replies']; ?>)</span>
          </div>
          <?php if (trim($thisList)) { ?> 
            <div class="of_collapse" id="of_gen<?php echo $x; ?>" style="display:<?php echo ($threadCollapse) ? "none" : "block"; ?>;">
              <?php echo $thisList; ?> 
            </div>
          <?php }

        } ?>

        <div id="of_timekeeper">
          <?php echo $lang['time1']; ?> GMT <?php echo (($adjustForDaylightSavings) ? ($timeZoneOffset + date("I")).((date("I")) ? " (DLS)" : "") : $timeZoneOffset)." / $timeZone"; ?> 
        </div>

      <?php } else if (isset($fData['search'])) { ?> 
 
        <p><?php echo $lang['list2']; ?></p>

      <?php } else { ?> 
 
        <p><?php echo $lang['list3']; ?></p>

      <?php } ?> 
    </div>

    <?php if ($fData['start'] != 0 || $lData['toprows'] > $threadsPerPage) { ?> 
      <table id="of_pagination" cellpadding="2" cellspacing="0" border="0"><tr>
        <td id="of_pagin_prev">
          <?php if ($fData['start'] != 0) {
            $linkPrev = "?";
            if ($fData['start'] - $threadsPerPage > 0) $linkPrev .= "start=".($fData['start'] - $threadsPerPage)."&amp;";
            $linkPrev = paginURI($linkPrev); ?>

            <a href="<?php echo $_SERVER['PHP_SELF'].$linkPrev; ?>" title="<?php echo $lang['pagin1']; ?>">&lt;&lt; <?php echo $lang['pagin2']; ?></a>
          <?php } else echo "&nbsp;"; ?> 
        </td>

        <td id="of_pagin_page">
          <?php for ($x = 0; $x < ceil($lData['toprows'] / $threadsPerPage); $x++) {
            if ($x * $threadsPerPage == $fData['start']) { ?> 
              <strong><?php echo ($x + 1); ?></strong>
            <?php } else {
              $linkPage = "?";
              if ($x != 0) $linkPage .= "start=".($x * $threadsPerPage)."&amp;";
              $linkPage = paginURI($linkPage); ?>

              <a href="<?php echo $_SERVER['PHP_SELF'].$linkPage; ?>" title="<?php printf($lang['pagin3'], $x + 1); ?>"><?php echo ($x + 1); ?></a>
            <?php }
          } ?> 
        </td>

        <td id="of_pagin_next">
          <?php if ($fData['start'] + $threadsPerPage < $lData['toprows']) {
            $linkNext = "?start=".($fData['start'] + $threadsPerPage)."&amp;";
            $linkNext = paginURI($linkNext); ?>

            <a href="<?php echo $_SERVER['PHP_SELF'].$linkNext; ?>" title="<?php echo $lang['pagin4']; ?>"><?php echo $lang['pagin5']; ?> &gt;&gt;</a>
          <?php } else echo "&nbsp;"; ?> 
        </td>
      </tr></table>
    <?php }
  }

  if (!$fData['msgtotal'] && $_POST['command'] != "Preview") { ?>
    <div style="padding:0px 15%;">
      <?php echo $lang['welcome']; ?> 
    </div>

  <?php } 
  ?> 


  <script type="text/javascript"><!--
    function of_validate() {
      if (!document.getElementById('of_postform').message.value) {
        if (!document.getElementById('of_postform').subject.value) {
          alert("<?php echo addcslashes(unhtmlentities($lang['form1']), "\0..\37!@\177..\377"); ?>");
          return false;
        }
        if (!confirm("<?php echo addcslashes(unhtmlentities($lang['form2']), "\0..\37!@\177..\377"); ?>")) return false;
      }

      if (!document.getElementById('of_postform').author.value)
       if (!confirm("<?php echo addcslashes(unhtmlentities($lang['form3']), "\0..\37!@\177..\377"); ?>")) return false;

      if (!document.getElementById('of_postform').subject.value)
        if (!confirm("<?php echo addcslashes(unhtmlentities($lang['form4']), "\0..\37!@\177..\377"); ?>")) return false;

      return true;
    }
  // --></script>

  <a name="of_post"></a>
  <form id="of_postform" action="<?php echo $_SERVER['PHP_SELF']; ?>" method="post" onsubmit="return of_validate();">
    <h4><?php echo ($vData['parent'] != "-1") ? $lang['form5'] : $lang['form6']; ?></h4>
    <div>
      <span>
        <label for="of_pstauthor"><?php echo $lang['form7']; ?></label>
        <input name="author" id="of_pstauthor" type="text" value="<?php echo $vData['author']; ?>" />
      </span>
      <label for="of_pstemail"><?php echo $lang['form8']; ?></label> &nbsp; 
      <input name="email" id="of_pstemail" type="text" size="30" value="<?php echo $vData['email']; ?>" />
      <input name="notify" id="of_pstnotify" type="checkbox" <?php if ($vData['notify'] == "yes") echo "checked=\"checked\" "; ?>/>
    </div>
    <div>
      <span>
        <label for="of_pstsubject"><?php echo $lang['form9']; ?></label>
        <input name="subject" id="of_pstsubject" type="text" size="60" value="<?php echo $vData['subject']; ?>" />
      </span>
      <label for="of_pstnotify"><?php echo $lang['forma']; ?></label>
    </div>
    <div>
      <span>
        <label for="of_msgarea"><?php echo $lang['formb']; ?></label>
      </span>
      <script type="text/javascript"><!--
        var of_msgarea = document.getElementById('of_msgarea');
        document.write("<input type=\"button\" value=\"<?php echo $lang['formc']; ?>\" onclick=\"of_msgarea.value+='[quote][/quote]';\" /> ");
        document.write("<input type=\"button\" value=\"<?php echo $lang['formd']; ?>\" onclick=\"of_msgarea.value+='[b][/b]';\" /> ");
        document.write("<input type=\"button\" value=\"<?php echo $lang['forme']; ?>\" onclick=\"of_msgarea.value+='[i][/i]';\" /> ");
        document.write("<input type=\"button\" value=\"<?php echo $lang['formf']; ?>\" onclick=\"of_msgarea.value+='[link=http://][/link]';\" /> ");
        document.write("<input type=\"button\" value=\"<?php echo $lang['formg']; ?>\" onclick=\"of_msgarea.value+='[img=http://]';\" /> ");
        document.write("<input type=\"button\" value=\"<?php echo $lang['formh']; ?>\" onclick=\"of_msgarea.value+='[code][/code]';\" /> ");
      // --></script>
      <noscript>
        <div>
          <input type="button" value="<?php echo $lang['formc']; ?>" disabled="disabled" />
          <input type="button" value="<?php echo $lang['formd']; ?>" disabled="disabled" />
          <input type="button" value="<?php echo $lang['forme']; ?>" disabled="disabled" />
          <input type="button" value="<?php echo $lang['formf']; ?>" disabled="disabled" />
          <input type="button" value="<?php echo $lang['formg']; ?>" disabled="disabled" />
          <input type="button" value="<?php echo $lang['formh']; ?>" disabled="disabled" />
        </div>
      </noscript>
    </div>
    <div class="of_text">
      <textarea id="of_msgarea" name="message" rows="7" cols="53"><?php echo $vData['message']; ?></textarea>
    </div>
    <div>
      <span>
        <label for="of_pstimage"><?php echo $lang['formi']; ?></label>
        <input name="image" id="of_pstimage" type="text" size="60" value="<?php echo $vData['image']; ?>" />
      </span>
      <input type="reset" value="<?php echo $lang['formj']; ?>" />
    </div>
    <div>
      <span>
        <label for="of_pstcookify"><?php echo $lang['formk']; ?></label>
        <input name="cookify" id="of_pstcookify" type="checkbox" <?php if ($vData['cookify'] == "Yes") echo "checked=\"checked\" "; ?>/>
      </span>
      <input type="hidden" name="parent" value="<?php echo $vData['parent']; ?>" />
      <input type="submit" name="command_prev" value="<?php echo $lang['formn']; ?>" />
      <input type="submit" name="command_post" value="<?php echo $lang['formo']; ?>" />
    </div>
  </form>

  <div style="text-align:center;font:italic 80% Arial,sans-serif;">
    <hr style="width:60%;margin:10px auto 2px auto;" />
    Ein <a href="http://www.greywyvern.com/" title="GreyWyvern.com">Orca</a> Script - Deutsche Version von <a href="http://www.orca-script.de" title="Orca-Script.de">Orca-Script.de</a>
  </div>

</div>
