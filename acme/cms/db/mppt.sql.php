# phpMyAdmin MySQL-Dump
# version 2.3.3
# http://www.phpmyadmin.net/ (download page)
#
# Host: localhost
# Erstellungszeit: 05. Mai 2003 um 20:35
# Server Version: 3.23.40
# PHP-Version: 4.2.2
# Datenbank: `mppt`
# --------------------------------------------------------

#
# Tabellenstruktur für Tabelle `acme_archiv`
#

DROP TABLE IF EXISTS acme_archiv;
CREATE TABLE acme_archiv (
  artikel_id int(11) NOT NULL default '0',
  artikel_modul_name varchar(60) NOT NULL default '0',
  artikel_serien_name varchar(60) default '0',
  artikel_publish_date datetime NOT NULL default '0000-00-00 00:00:00',
  artikel_headline varchar(128) NOT NULL default '',
  artikel_short_text tinytext NOT NULL,
  artikel_keywords text NOT NULL,
  artikel_last_update datetime default NULL,
  artikel_groups varchar(200) NOT NULL default ':admin:',
  artikel_username varchar(60) NOT NULL default '',
  artikel_aktive enum('J','N') NOT NULL default 'J',
  artikel_counter int(11) NOT NULL default '0',
  PRIMARY KEY  (artikel_id),
  KEY artikel_modul_id (artikel_modul_name),
  KEY artikel_serien_id (artikel_serien_name)
) TYPE=MyISAM;

#
# Daten für Tabelle `acme_archiv`
#

# --------------------------------------------------------

#
# Tabellenstruktur für Tabelle `acme_archiv_daten`
#

DROP TABLE IF EXISTS acme_archiv_daten;
CREATE TABLE acme_archiv_daten (
  artikel_daten_id int(11) NOT NULL default '0',
  artikel_id int(11) NOT NULL default '0',
  artikel_long_text longtext NOT NULL,
  artikel_counter int(11) NOT NULL default '0',
  PRIMARY KEY  (artikel_daten_id),
  KEY artikel_id (artikel_id)
) TYPE=MyISAM;

#
# Daten für Tabelle `acme_archiv_daten`
#

# --------------------------------------------------------

#
# Tabellenstruktur für Tabelle `acme_artikel`
#

DROP TABLE IF EXISTS acme_artikel;
CREATE TABLE acme_artikel (
  artikel_id int(11) NOT NULL auto_increment,
  artikel_modul int(11) default NULL,
  artikel_serie int(11) default NULL,
  artikel_publish_date datetime NOT NULL default '0000-00-00 00:00:00',
  artikel_headline varchar(128) NOT NULL default '',
  artikel_short_text tinytext NOT NULL,
  artikel_keywords text NOT NULL,
  artikel_last_update datetime default NULL,
  artikel_groups varchar(200) NOT NULL default ':admin:',
  artikel_username varchar(20) NOT NULL default '',
  artikel_aktiv enum('J','N') NOT NULL default 'J',
  artikel_counter int(11) NOT NULL default '0',
  artikel_comments enum('J','I','N') default 'N',
  PRIMARY KEY  (artikel_id),
  KEY artikel_modul_id (artikel_modul),
  KEY artikel_serien_id (artikel_serie)
) TYPE=MyISAM;

#
# Daten für Tabelle `acme_artikel`
#

INSERT INTO acme_artikel (artikel_id, artikel_modul, artikel_serie, artikel_publish_date, artikel_headline, artikel_short_text, artikel_keywords, artikel_last_update, artikel_groups, artikel_username, artikel_aktiv, artikel_counter, artikel_comments) VALUES (1, 10, 2, '2002-02-01 00:00:00', 'artikel headline 12', 'artikel short text 12', 'fsdgsdgasdfsadf2', '2002-02-14 19:01:14', ':admin2:', 'rtrz2', 'N', 1402, 'I'),
(2, 1, 0, '0000-00-00 00:00:00', 'artikel headline 2', 'artikel short text 2', '', '2003-03-07 11:55:27', '', '', 'J', 24, NULL),
(3, 11, 0, '0000-00-00 00:00:00', 'artikel headline 3', 'artikel short test 3', '', '2003-03-07 14:09:47', '', '', 'J', 5, NULL),
(4, 12, 0, '0000-00-00 00:00:00', 'artikel headline 4', 'artikel short text 4', '', '2003-03-07 16:12:43', '', '', 'J', 0, NULL),
(5, 10, 0, '0000-00-00 00:00:00', 'test', 'test', 'test', '2003-05-05 12:16:38', 'test', 'test', 'J', 0, 'J'),
(6, 0, 0, '0000-00-00 00:00:00', '', '', '', '0000-00-00 00:00:00', ':admin:', '', 'J', 0, ''),
(7, 174, 0, '0000-00-00 00:00:00', '', 'qwerwqer', '', '0000-00-00 00:00:00', ':admin:', '', 'J', 0, ''),
(8, 0, 0, '0000-00-00 00:00:00', 'tetetteeeeee', '', '', '0000-00-00 00:00:00', ':admin:', '', 'J', 0, ''),
(9, 1, 1, '0000-00-00 00:00:00', '7', 'sdfg63434636', '', '0000-00-00 00:00:00', ':admin:', '', 'J', 0, 'N');
# --------------------------------------------------------

#
# Tabellenstruktur für Tabelle `acme_artikel_daten`
#

DROP TABLE IF EXISTS acme_artikel_daten;
CREATE TABLE acme_artikel_daten (
  artikel_daten_id int(11) NOT NULL auto_increment,
  artikel_id int(11) NOT NULL default '0',
  artikel_part int(11) NOT NULL default '1',
  artikel_long_text longtext NOT NULL,
  artikel_counter int(11) NOT NULL default '0',
  PRIMARY KEY  (artikel_daten_id),
  KEY artikel_id (artikel_id),
  KEY artikel_part (artikel_part)
) TYPE=MyISAM;

#
# Daten für Tabelle `acme_artikel_daten`
#

INSERT INTO acme_artikel_daten (artikel_daten_id, artikel_id, artikel_part, artikel_long_text, artikel_counter) VALUES (1, 1, 1, 'test1-1', 7),
(2, 2, 1, 'test2', 8),
(3, 3, 1, 'test3', 0),
(4, 4, 1, 'test4', 0),
(5, 1, 2, 'test1-2', 8),
(6, 1, 3, 'test1-3\r\n', 7);
# --------------------------------------------------------

#
# Tabellenstruktur für Tabelle `acme_artikel_serien`
#

DROP TABLE IF EXISTS acme_artikel_serien;
CREATE TABLE acme_artikel_serien (
  artikel_serien_id int(11) NOT NULL auto_increment,
  artikel_serien_name varchar(60) NOT NULL default '',
  artikel_serien_modul int(11) NOT NULL default '0',
  artikel_serien_tpl int(11) NOT NULL default '0',
  artikel_serien_img_small int(11) default NULL,
  artikel_serien_img_big int(11) default NULL,
  artikel_serien_left_bar int(11) NOT NULL default '0',
  artikel_serien_right_bar int(11) NOT NULL default '0',
  artikel_serien_top_bar int(11) NOT NULL default '0',
  artikel_serien_foo_bar int(11) NOT NULL default '0',
  artikel_serien_headline tinytext,
  artikel_serien_short_text mediumtext NOT NULL,
  artikel_serien_long_text longtext,
  artikel_serien_counter int(11) NOT NULL default '0',
  artikel_serien_aktiv enum('J','N') NOT NULL default 'J',
  artikel_serien_last_update datetime NOT NULL default '0000-00-00 00:00:00',
  artikel_serien_username varchar(20) NOT NULL default '',
  artikel_serien_groups varchar(200) NOT NULL default 'admin',
  artikel_serien_comments enum('J','N','I') NOT NULL default 'N',
  PRIMARY KEY  (artikel_serien_id),
  UNIQUE KEY modul_name (artikel_serien_name),
  UNIQUE KEY modul_id (artikel_serien_id)
) TYPE=MyISAM;

#
# Daten für Tabelle `acme_artikel_serien`
#

INSERT INTO acme_artikel_serien (artikel_serien_id, artikel_serien_name, artikel_serien_modul, artikel_serien_tpl, artikel_serien_img_small, artikel_serien_img_big, artikel_serien_left_bar, artikel_serien_right_bar, artikel_serien_top_bar, artikel_serien_foo_bar, artikel_serien_headline, artikel_serien_short_text, artikel_serien_long_text, artikel_serien_counter, artikel_serien_aktiv, artikel_serien_last_update, artikel_serien_username, artikel_serien_groups, artikel_serien_comments) VALUES (1, 'testserie1', 0, 1, 1, 1, 0, 1, 1, 0, 'serien headline1', 'serien short text1', 'serien long text1', 1, 'N', '2002-01-01 00:00:00', '1', 'admin1', 'J'),
(2, '12', 1, 0, 12, 12, 1, 1, 1, 0, '12', '', '', 1, 'J', '0000-00-00 00:00:00', '', ':admin:', ''),
(3, 'tetetet', 0, 0, 0, 0, 0, 0, 0, 0, '', '', '', 0, 'J', '0000-00-00 00:00:00', '', ':admin:', '');
# --------------------------------------------------------

#
# Tabellenstruktur für Tabelle `acme_bar`
#

DROP TABLE IF EXISTS acme_bar;
CREATE TABLE acme_bar (
  bar_id int(11) NOT NULL auto_increment,
  bar_name varchar(60) NOT NULL default '0',
  bar_tpl varchar(60) NOT NULL default '',
  bar_cache longtext NOT NULL,
  PRIMARY KEY  (bar_id)
) TYPE=MyISAM;

#
# Daten für Tabelle `acme_bar`
#

INSERT INTO acme_bar (bar_id, bar_name, bar_tpl, bar_cache) VALUES (1, 'home_left', '', '<a href="/acme/index.php?mid=1">home1</a><br>\r\n<a href="/acme/index.php?mid=10">home2</a><br>\r\n<a href="/acme/index.php?mid=11">home3</a><br>\r\n<a href="/acme/index.php?mid=12">home4</a><br>\r\n<a href="/acme/index.php?mid=admin">admin</a><br>\r\n<form method=post action="/or-cms/index.php?page=modul&name=searchengine">\r\nSearch:<br>\r\n<input type=text size=10 maxlength=40 name=search_term>\r\n</form>');
# --------------------------------------------------------

#
# Tabellenstruktur für Tabelle `acme_bar_groups`
#

DROP TABLE IF EXISTS acme_bar_groups;
CREATE TABLE acme_bar_groups (
  bar_group_id int(11) NOT NULL auto_increment,
  bar_name varchar(60) NOT NULL default '',
  bar_group_name varchar(60) NOT NULL default '0',
  bar_group_rank int(11) default NULL,
  PRIMARY KEY  (bar_group_id)
) TYPE=MyISAM;

#
# Daten für Tabelle `acme_bar_groups`
#

# --------------------------------------------------------

#
# Tabellenstruktur für Tabelle `acme_bar_topics`
#

DROP TABLE IF EXISTS acme_bar_topics;
CREATE TABLE acme_bar_topics (
  bar_topic_id int(11) NOT NULL auto_increment,
  bar_group_name varchar(60) NOT NULL default '',
  bar_modul_name varchar(60) NOT NULL default '0',
  bar_topic_text varchar(128) NOT NULL default '',
  bar_topic_block_name varchar(60) NOT NULL default '0',
  bar_topic_url varchar(200) default NULL,
  bar_topic_type enum('I','M','B','U') NOT NULL default 'M',
  bar_topic_rank int(11) default NULL,
  PRIMARY KEY  (bar_topic_id)
) TYPE=MyISAM;

#
# Daten für Tabelle `acme_bar_topics`
#

# --------------------------------------------------------

#
# Tabellenstruktur für Tabelle `acme_bilder`
#

DROP TABLE IF EXISTS acme_bilder;
CREATE TABLE acme_bilder (
  img_id int(11) NOT NULL auto_increment,
  img_name varchar(128) NOT NULL default '',
  img_description varchar(255) default NULL,
  img_tstamp timestamp(14) NOT NULL,
  img_blob longblob NOT NULL,
  img_typ varchar(20) NOT NULL default '',
  img_username varchar(20) NOT NULL default '',
  img_groups varchar(200) NOT NULL default ':admin:',
  PRIMARY KEY  (img_id),
  UNIQUE KEY img_name (img_name)
) TYPE=MyISAM;

#
# Daten für Tabelle `acme_bilder`
#

INSERT INTO acme_bilder (img_id, img_name, img_description, img_tstamp, img_blob, img_typ, img_username, img_groups) VALUES (1, 'test', 'testeintrag', 20030410191811, '', '', 'admin', ':admin:');
# --------------------------------------------------------

#
# Tabellenstruktur für Tabelle `acme_blocks`
#

DROP TABLE IF EXISTS acme_blocks;
CREATE TABLE acme_blocks (
  block_id int(11) NOT NULL auto_increment,
  block_name varchar(60) NOT NULL default '',
  block_type enum('H','P') NOT NULL default 'H',
  block_content longtext NOT NULL,
  block_username varchar(20) NOT NULL default '',
  block_groups varchar(200) NOT NULL default '',
  PRIMARY KEY  (block_id)
) TYPE=MyISAM;

#
# Daten für Tabelle `acme_blocks`
#

INSERT INTO acme_blocks (block_id, block_name, block_type, block_content, block_username, block_groups) VALUES (1, 'test', 'H', '<p>testtesttest</p>', 'admin', ':admin:');
# --------------------------------------------------------

#
# Tabellenstruktur für Tabelle `acme_comment`
#

DROP TABLE IF EXISTS acme_comment;
CREATE TABLE acme_comment (
  comment_id int(11) NOT NULL auto_increment,
  artikel_id int(11) default '0',
  modul_id int(11) default '0',
  comment_headline varchar(128) NOT NULL default '',
  comment_text longtext NOT NULL,
  comment_date datetime NOT NULL default '0000-00-00 00:00:00',
  comment_username varchar(60) NOT NULL default '',
  PRIMARY KEY  (comment_id),
  KEY artikel_id (artikel_id),
  KEY modul_id (modul_id),
  KEY comment_username (comment_username)
) TYPE=MyISAM;

#
# Daten für Tabelle `acme_comment`
#

# --------------------------------------------------------

#
# Tabellenstruktur für Tabelle `acme_glossar`
#

DROP TABLE IF EXISTS acme_glossar;
CREATE TABLE acme_glossar (
  glossar_id int(11) NOT NULL default '0',
  glossar_titel varchar(80) NOT NULL default '',
  glossar_text longtext NOT NULL,
  glossar_user varchar(25) NOT NULL default 'admin',
  glossar_groups varchar(200) NOT NULL default ':admin:',
  PRIMARY KEY  (glossar_id)
) TYPE=MyISAM;

#
# Daten für Tabelle `acme_glossar`
#

INSERT INTO acme_glossar (glossar_id, glossar_titel, glossar_text, glossar_user, glossar_groups) VALUES (0, 'test', 'testtext', 'admin', ':admin:');
# --------------------------------------------------------

#
# Tabellenstruktur für Tabelle `acme_groups`
#

DROP TABLE IF EXISTS acme_groups;
CREATE TABLE acme_groups (
  group_id int(11) NOT NULL auto_increment,
  group_name varchar(25) NOT NULL default '',
  PRIMARY KEY  (group_id),
  UNIQUE KEY mygroup (group_name)
) TYPE=MyISAM;

#
# Daten für Tabelle `acme_groups`
#

INSERT INTO acme_groups (group_id, group_name) VALUES (1, 'admin'),
(2, 'stduser'),
(3, 'artikler');
# --------------------------------------------------------

#
# Tabellenstruktur für Tabelle `acme_modules`
#

DROP TABLE IF EXISTS acme_modules;
CREATE TABLE acme_modules (
  modul_id int(11) NOT NULL auto_increment,
  modul_name varchar(60) NOT NULL default '',
  modul_tpl int(11) default NULL,
  modul_parent int(11) default NULL,
  modul_img_small int(11) default NULL,
  modul_img_big int(11) default NULL,
  modul_left_bar int(11) default NULL,
  modul_right_bar int(11) default NULL,
  modul_top_bar int(11) default NULL,
  modul_foo_bar int(11) default NULL,
  modul_headline tinytext,
  modul_short_text mediumtext,
  modul_long_text longtext,
  modul_long_text_typ enum('P','H','B') NOT NULL default 'B',
  modul_groups varchar(200) NOT NULL default ':admin:',
  modul_childs enum('N','M','A','S') NOT NULL default 'N',
  modul_counter int(11) NOT NULL default '0',
  modul_last_update datetime NOT NULL default '0000-00-00 00:00:00',
  modul_comments enum('J','N','I') NOT NULL default 'N',
  PRIMARY KEY  (modul_id),
  UNIQUE KEY modul_id (modul_id),
  UNIQUE KEY modul_name (modul_name)
) TYPE=MyISAM;

#
# Daten für Tabelle `acme_modules`
#

INSERT INTO acme_modules (modul_id, modul_name, modul_tpl, modul_parent, modul_img_small, modul_img_big, modul_left_bar, modul_right_bar, modul_top_bar, modul_foo_bar, modul_headline, modul_short_text, modul_long_text, modul_long_text_typ, modul_groups, modul_childs, modul_counter, modul_last_update, modul_comments) VALUES (1, 'home111', 0, 0, 0, 0, 1, 0, 0, 0, 'modul headline 1', '', '', '', ':admin:', '', 32, '0000-00-00 00:00:00', ''),
(174, 'tetet', 0, 0, 0, 0, 0, 0, 0, 0, '', '', '', 'H', ':admin:', 'N', 0, '0000-00-00 00:00:00', 'N'),
(16, '404', 404, 0, NULL, NULL, 0, 0, 0, NULL, '404', 'file not found', 'file not found', 'H', ':admin:', 'N', 15, '0000-00-00 00:00:00', 'N'),
(173, 'asdf', 0, 0, 0, 0, 0, 0, 0, 0, '', '', '', 'H', ':admin:', 'N', 0, '0000-00-00 00:00:00', 'N');
# --------------------------------------------------------

#
# Tabellenstruktur für Tabelle `acme_profile`
#

DROP TABLE IF EXISTS acme_profile;
CREATE TABLE acme_profile (
  pri int(11) NOT NULL auto_increment,
  home_img_name varchar(128) default NULL,
  home_modul varchar(60) NOT NULL default '',
  home_template varchar(60) NOT NULL default '',
  home_style varchar(60) NOT NULL default '',
  PRIMARY KEY  (pri)
) TYPE=MyISAM;

#
# Daten für Tabelle `acme_profile`
#

INSERT INTO acme_profile (pri, home_img_name, home_modul, home_template, home_style) VALUES (1, 'test', '1', 'home', '1'),
(2, 'test', 'test', 'test', 'test');
# --------------------------------------------------------

#
# Tabellenstruktur für Tabelle `acme_styles`
#

DROP TABLE IF EXISTS acme_styles;
CREATE TABLE acme_styles (
  style_id int(11) NOT NULL auto_increment,
  style_name varchar(60) NOT NULL default '',
  style_text longtext NOT NULL,
  PRIMARY KEY  (style_id)
) TYPE=MyISAM;

#
# Daten für Tabelle `acme_styles`
#

# --------------------------------------------------------

#
# Tabellenstruktur für Tabelle `acme_templates`
#

DROP TABLE IF EXISTS acme_templates;
CREATE TABLE acme_templates (
  tpl_id int(11) NOT NULL auto_increment,
  tpl_name varchar(60) NOT NULL default '',
  tpl_content longtext NOT NULL,
  PRIMARY KEY  (tpl_id)
) TYPE=MyISAM;

#
# Daten für Tabelle `acme_templates`
#

INSERT INTO acme_templates (tpl_id, tpl_name, tpl_content) VALUES (1, 'home', '{mask:main}\r\n<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">\r\n<html>\r\n<head>\r\n <link rel="stylesheet" href="acme.css" type="text/css">\r\n <!-- metas -->\r\n  <META NAME="AUTHOR"         CONTENT="Thomas Lacher">\r\n  <META NAME="Generator"      CONTENT="ACME">\r\n <!-- Titel -->\r\n  <title>ORBIT GmbH Karlsruhe - {titel}</title>\r\n</head>\r\n<body>\r\n<table border="0" cellspacing="0" cellpadding="0">\r\n  <tr>\r\n   <td width="120" align="left" valign="top">{left_bar}</td>\r\n   <td valign="top" align="left">\r\n     <table>\r\n      <tr><td>{top_bar}</td></tr>\r\n      <tr><td>\r\n        <table>\r\n          <tr><td><h1>{headline}</h1></td><td>{modul}<br />{serie}<br />{prev}-{akt}-{next}</td></tr>\r\n          <tr><td colspan = "2">{short_text}</td></tr>\r\n          <tr><td colspan = "2">{long_text}</td></tr>\r\n          <tr><td>&nbsp;</td><td>{last_update}</td></tr>\r\n          <tr><td colspan = "2">\r\n            <table>\r\n             {mask:preview}\r\n               <tr>\r\n                <td>{headline}</td>\r\n               </tr>\r\n               <tr>\r\n                <td>\r\n                {short_text}\r\n                </td>\r\n               </tr>\r\n            {/mask}\r\n          </table>\r\n         </td></tr>\r\n         <tr><td>&nbsp;</td><td>PI\'s: {counter}</td></tr>\r\n       </table>\r\n      </td></tr>\r\n     </table>\r\n   </td>\r\n  </tr>\r\n</table>\r\n</body>\r\n</html>\r\n{/mask}');
# --------------------------------------------------------

#
# Tabellenstruktur für Tabelle `acme_user`
#

DROP TABLE IF EXISTS acme_user;
CREATE TABLE acme_user (
  user_id int(11) NOT NULL auto_increment,
  user_name varchar(25) NOT NULL default '',
  user_passwd varchar(25) NOT NULL default '',
  user_groups varchar(200) NOT NULL default '',
  user_active enum('Y','N') NOT NULL default 'Y',
  allow_module enum('Y','N') NOT NULL default 'N',
  allow_pics enum('Y','N') NOT NULL default 'Y',
  allow_artikel enum('Y','N') NOT NULL default 'Y',
  allow_bars enum('Y','N') NOT NULL default 'N',
  allow_user enum('Y','N') NOT NULL default 'N',
  allow_prefs enum('Y','N') NOT NULL default 'N',
  allow_groups enum('Y','N') NOT NULL default 'N',
  allow_serien enum('Y','N') NOT NULL default 'N',
  allow_blocks enum('Y','N') NOT NULL default 'N',
  allow_glossar enum('Y','N') NOT NULL default 'N',
  PRIMARY KEY  (user_name),
  KEY user_id (user_id)
) TYPE=MyISAM;

#
# Daten für Tabelle `acme_user`
#

INSERT INTO acme_user (user_id, user_name, user_passwd, user_groups, user_active, allow_module, allow_pics, allow_artikel, allow_bars, allow_user, allow_prefs, allow_groups, allow_serien, allow_blocks, allow_glossar) VALUES (1, 'admin', 'admin', 'admin', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y');

