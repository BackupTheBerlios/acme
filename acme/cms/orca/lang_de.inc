<?php 
/* ***** Orca Forum - Deutsche Sprachdatei ************* */

/* ***************************************************************
* Orca Forum v4.0c
* Ein einfaches Forum für kleine Interessengemeinschaften
* Copyright (C) 2004 GreyWyvern
*
* Dieses Programm kann nach den Richtlinien von GPL frei verteilt werden.
*   - http://www.gnu.org/licenses/gpl.txt
* 
* Die Installations Instruktionen findest Du in der readme.txt .
*
* Deutsche Übersetzung von http://www.Orca-Script.de
*************************************************************** */

$lang['charset'] = "ISO-8859-1";
$pageEncoding = 2;  // Final Page Encoding
                    //  1 - UTF-8
                    //  2 - ISO-8859-1
                    //  3 - Other

/* ***** Success/Error Messages ******************************* */
$lang['avatar1'] = "Avatar Größe max.: 80x80 pixels";
$lang['avatar2'] = "Die Avatar Datei kann nicht gelesen werden";
$lang['avatar3'] = "Avatar URI unzulässig";

$lang['emaila'] = "Falsches Email Format";

$lang['post1'] = "Beitrag %d und alle Antworten wurden gelöscht";
$lang['post2'] = "Beitrag %d existiert nicht oder wurde gelöscht";
$lang['post3'] = "Keine Beitrag ID für Löschung ausgewählt";
$lang['post4'] = "Bei einem Beitrag muss wenigstens die Betreff Zeile ausgefüllt oder ein Nachrichttext geschrieben werden.";
$lang['post5'] = "Du mußt 30 Sekunden warten um wieder zu schreiben.";
$lang['post6'] = "Du hast diesen Beitrag schon eingetragen";
$lang['post7'] = "Deine Beitrag wurde eingetragen";

$lang['get1'] = "Nachricht Nr. %d existiert nicht oder wurde gelöscht.";

/* ***** Email Message **************************************** */
$lang['subject1'] = "Antwort auf Deinen Beitrag!";
$lang['email1'] = "%1\$s,

Dein Beitrag: \"%2\$s\" wurde beantwortet.
Du bekommst diese email weil eine Antwort auf Deinen Beitrag vom: %3\$s %4\$s geschrieben wurde.

Antwort siehe unten:

%5\$s - Geschrieben von: %6\$s, am: %7\$s %4\$s

%8\$s

____________________________________________________________
%9\$s
*** Eine Antwort auf diese Nachricht wird nicht an %6\$s *** gesendet";


/* ***** Body ************************************************* */
$lang['parse1'] = "Zitat";
$lang['parse2'] = "Sagte";

$lang['panel1'] = "Suche";
$lang['panel2'] = "Beitrag jünger als:";
$lang['panel3'] = "Keine Markierung";
$lang['panel4'] = "1 Stunde";
$lang['panel5'] = "3 Stunden";
$lang['panel6'] = "6 Stunden";
$lang['panel7'] = "12 Stunden";
$lang['panel8'] = "1 Tag";
$lang['panel9'] = "3 Tage";
$lang['panela'] = "1 Woche";
$lang['panelb'] = "2 Wochen";
$lang['panelc'] = "1 Monat";
$lang['paneld'] = "Markieren";
$lang['panele'] = "Alles anzeigen";
$lang['panelf'] = "Anworten nicht anzeigen";
$lang['panelg'] = "Forum Startseite";
$lang['panelh'] = "Aktualisieren";
$lang['paneli'] = "Auf Beitrag antworten";
$lang['panelj'] = "Beitrag schreiben";

$lang['search'] = "Suchergebnisse <strong>%s</strong>";

$lang['welcome'] = "<h2>Willkommen im Forum</h2>";

$lang['message1'] = "Aktueller Beitrag:";
$lang['message2'] = " - <em>Vorschau</em>";
$lang['message3'] = "Sende Email an %s";
$lang['message4'] = "Email";
$lang['message5'] = "Avatar";
$lang['message6'] = "Geschrieben am:";
$lang['message7'] = "Diese Nachricht ist eine Antwort auf:";
$lang['message8'] = "Geschrieben von <em>%s</em>.";
$lang['message9'] = "Kein Betreff";
$lang['messagea'] = "Kein Text";
$lang['messageb'] = "Gast";

$lang['list1'] = "<em>Antworten...</em>";
$lang['list2'] = "<em>Keine Ergebnisse</em>";
$lang['list3'] = "<em>Keine Antworten</em>";

$lang['time1'] = "Alle Zeitangaben in";

$lang['pagin1'] = "Letzte Seite";
$lang['pagin2'] = "Zurück";
$lang['pagin3'] = "Gehe zur Seite %d";
$lang['pagin4'] = "Nächste Seite";
$lang['pagin5'] = "Nächste";

$lang['form1'] = "Du musst mindestens einen Betreff oder Nachrichten Text eintragen!";
$lang['form2'] = "Kein Nachrichten Text!  Trotzdem eintragen?";
$lang['form3'] = "Beitrag ohne Name eintragen?";
$lang['form4'] = "Beitrag ohne Betreff eintragen?";
$lang['form5'] = "Auf Beitrag antworten";
$lang['form6'] = "Neuen Beitrag schreiben";
$lang['form7'] = "Name:";
$lang['form8'] = "Email:";
$lang['form9'] = "Betreff:";
$lang['forma'] = "<small>Sende Antworten<br />per Email</small>";
$lang['formb'] = "Nachricht:";
$lang['formc'] = "Zitat";
$lang['formd'] = "Fett";
$lang['forme'] = "Kusiv";
$lang['formf'] = "Link";
$lang['formg'] = "Bild";
$lang['formh'] = "Code";
$lang['formi'] = "Avatar:";
$lang['formj'] = "Zurückstellen";
$lang['formk'] = "Bei jedem Besuch automatisch einloggen:";
$lang['forml'] = "Ja:";
$lang['formm'] = "Nein:";
$lang['formn'] = "Vorschau";
$lang['formo'] = "Eintragen";


while (list($key, $value) = each($lang)) {
  if (!is_array($value) && $key != "charset") {
    if ($pageEncoding == 3) {
      $lang[$key] = htmlentities($value, ENT_COMPAT, $lang['charset']);
      $lang[$key] = str_replace("&gt;", ">", $lang[$key]);
      $lang[$key] = str_replace("&lt;", "<", $lang[$key]);
    } else if ($pageEncoding == 1) $lang[$key] = utf8_encode($value);
  }
}

?>