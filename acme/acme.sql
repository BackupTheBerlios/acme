# phpMyAdmin MySQL-Dump
# version 2.2.3
# http://phpwizard.net/phpMyAdmin/
# http://phpmyadmin.sourceforge.net/ (download page)
#
# Host: localhost
# Generation Time: Nov 11, 2004 at 08:12 PM
# Server version: 3.23.49
# PHP Version: 4.1.2
# Database : `acme`
# --------------------------------------------------------

#
# Table structure for table `acme_artikel`
#

CREATE TABLE acme_artikel (
  artikel_id int(11) NOT NULL auto_increment,
  artikel_page varchar(200) default NULL,
  artikel_publish_date datetime default NULL,
  artikel_headline varchar(128) NOT NULL default '',
  artikel_sub_headline varchar(200) NOT NULL default '',
  artikel_short_text text NOT NULL,
  artikel_keywords text NOT NULL,
  artikel_create_date datetime default NULL,
  artikel_modify_date datetime default NULL,
  artikel_author_id int(11) NOT NULL default '0',
  artikel_user_id int(11) NOT NULL default '0',
  artikel_aktiv enum('J','N') NOT NULL default 'J',
  artikel_counter int(11) NOT NULL default '0',
  artikel_comments enum('J','I','N') default 'N',
  PRIMARY KEY  (artikel_id),
  FULLTEXT KEY artikel_headline (artikel_headline),
  FULLTEXT KEY artikel_sub_headline (artikel_sub_headline),
  FULLTEXT KEY artikel_short_text (artikel_short_text),
  FULLTEXT KEY artikel_keywords (artikel_keywords)
) TYPE=MyISAM;
# --------------------------------------------------------

#
# Table structure for table `acme_artikel_daten`
#

CREATE TABLE acme_artikel_daten (
  artikel_daten_id int(11) NOT NULL auto_increment,
  artikel_id int(11) NOT NULL default '0',
  artikel_part int(11) NOT NULL default '1',
  artikel_headline varchar(128) NOT NULL default '',
  artikel_long_text longtext NOT NULL,
  artikel_counter int(11) NOT NULL default '0',
  PRIMARY KEY  (artikel_daten_id),
  FULLTEXT KEY artikel_long_text (artikel_long_text)
) TYPE=MyISAM;
# --------------------------------------------------------

#
# Table structure for table `acme_author`
#

CREATE TABLE acme_author (
  author_id int(11) NOT NULL auto_increment,
  author_nachname varchar(128) NOT NULL default 'Y',
  author_vorname varchar(128) NOT NULL default '',
  author_img int(11) NOT NULL default '0',
  author_url text NOT NULL,
  author_email text NOT NULL,
  author_text longtext NOT NULL,
  PRIMARY KEY  (author_id)
) TYPE=MyISAM;
# --------------------------------------------------------

#
# Table structure for table `acme_bar`
#

CREATE TABLE acme_bar (
  bar_id int(11) NOT NULL auto_increment,
  bar_name varchar(60) NOT NULL default '0',
  bar_cache longtext NOT NULL,
  PRIMARY KEY  (bar_id)
) TYPE=MyISAM;
# --------------------------------------------------------

#
# Table structure for table `acme_bar_topics`
#

CREATE TABLE acme_bar_topics (
  bar_topic_id int(11) NOT NULL auto_increment,
  bar_id int(11) NOT NULL default '0',
  bar_topic_text varchar(128) NOT NULL default '',
  bar_topic_type varchar(128) NOT NULL default 'M',
  bar_topic_type_id int(11) NOT NULL default '0',
  bar_topic_rank int(11) default NULL,
  PRIMARY KEY  (bar_topic_id)
) TYPE=MyISAM;
# --------------------------------------------------------

#
# Table structure for table `acme_bilder`
#

CREATE TABLE acme_bilder (
  img_id int(11) NOT NULL auto_increment,
  img_typ enum('L','S') NOT NULL default 'S',
  img_typ_id int(11) NOT NULL default '0',
  img_name varchar(25) NOT NULL default '',
  img_real_name varchar(100) NOT NULL default '',
  img_description varchar(255) default NULL,
  img_desc_long text NOT NULL,
  img_user_id int(11) NOT NULL default '0',
  PRIMARY KEY  (img_id),
  FULLTEXT KEY img_name (img_name),
  FULLTEXT KEY img_description (img_description),
  FULLTEXT KEY img_desc_long (img_desc_long)
) TYPE=MyISAM;
# --------------------------------------------------------

#
# Table structure for table `acme_bilder_typs`
#

CREATE TABLE acme_bilder_typs (
  img_typ_id int(11) NOT NULL auto_increment,
  img_typ_parent_id int(11) NOT NULL default '0',
  img_typ_tpl int(11) NOT NULL default '0',
  img_typ_rows int(11) NOT NULL default '0',
  img_typ_cols int(11) NOT NULL default '0',
  img_typ_img_small int(11) NOT NULL default '0',
  img_typ_img_big int(11) NOT NULL default '0',
  img_typ_frame int(4) NOT NULL default '0',
  img_typ_left_bar int(11) NOT NULL default '0',
  img_typ_right_bar int(11) NOT NULL default '0',
  img_typ_top_bar int(11) NOT NULL default '0',
  img_typ_foo_bar int(11) NOT NULL default '0',
  img_typ_name varchar(128) NOT NULL default '',
  img_typ_text text NOT NULL,
  img_typ_create_date datetime NOT NULL default '0000-00-00 00:00:00',
  img_typ_modify_date datetime NOT NULL default '0000-00-00 00:00:00',
  img_typ_user_id int(11) NOT NULL default '0',
  img_typ_counter int(11) NOT NULL default '0',
  PRIMARY KEY  (img_typ_id),
  FULLTEXT KEY img_typ_text (img_typ_text),
  FULLTEXT KEY img_typ_name (img_typ_name)
) TYPE=MyISAM;
# --------------------------------------------------------

#
# Table structure for table `acme_blocks`
#

CREATE TABLE acme_blocks (
  block_id int(11) NOT NULL auto_increment,
  block_name varchar(60) NOT NULL default '',
  block_type enum('H','P') NOT NULL default 'H',
  block_content longtext NOT NULL,
  block_user_id int(11) NOT NULL default '0',
  PRIMARY KEY  (block_id)
) TYPE=MyISAM;
# --------------------------------------------------------

#
# Table structure for table `acme_blog`
#

CREATE TABLE acme_blog (
  blog_id int(11) NOT NULL auto_increment,
  blog_name varchar(128) NOT NULL default '0000-00-00 00:00:00',
  blog_tpl int(11) NOT NULL default '0',
  blog_img_small int(11) NOT NULL default '0',
  blog_img_big int(11) NOT NULL default '0',
  blog_frame int(11) NOT NULL default '0',
  blog_left_bar int(11) NOT NULL default '0',
  blog_right_bar int(11) NOT NULL default '0',
  blog_top_bar int(11) NOT NULL default '0',
  blog_foo_bar int(11) NOT NULL default '0',
  blog_titel varchar(200) NOT NULL default '',
  blog_text text NOT NULL,
  blog_counter int(11) NOT NULL default '0',
  blog_user_id int(11) NOT NULL default '0',
  PRIMARY KEY  (blog_id),
  FULLTEXT KEY blog_text (blog_text),
  FULLTEXT KEY blog_titel (blog_titel)
) TYPE=MyISAM;
# --------------------------------------------------------

#
# Table structure for table `acme_blog_cat`
#

CREATE TABLE acme_blog_cat (
  blog_cat_id int(11) NOT NULL auto_increment,
  blog_cat_blog_id int(11) NOT NULL default '0',
  blog_cat_name text NOT NULL,
  blog_cat_text text NOT NULL,
  UNIQUE KEY blog_cat_id (blog_cat_id),
  KEY blog_cat_blog_id (blog_cat_blog_id)
) TYPE=MyISAM;
# --------------------------------------------------------

#
# Table structure for table `acme_blog_data`
#

CREATE TABLE acme_blog_data (
  blog_data_id int(11) NOT NULL auto_increment,
  blog_id int(11) NOT NULL default '0',
  blog_cat_id int(11) NOT NULL default '0',
  blog_data_date datetime NOT NULL default '0000-00-00 00:00:00',
  blog_data_headline varchar(128) NOT NULL default '',
  blog_data_content longtext NOT NULL,
  PRIMARY KEY  (blog_data_id),
  KEY blog_data_id (blog_data_id),
  KEY blog_id (blog_id)
) TYPE=MyISAM;
# --------------------------------------------------------

#
# Table structure for table `acme_comment`
#

CREATE TABLE acme_comment (
  comment_id int(11) NOT NULL auto_increment,
  comment_headline varchar(128) NOT NULL default '',
  comment_text longtext NOT NULL,
  comment_date datetime NOT NULL default '0000-00-00 00:00:00',
  PRIMARY KEY  (comment_id)
) TYPE=MyISAM;
# --------------------------------------------------------

#
# Table structure for table `acme_download`
#

CREATE TABLE acme_download (
  download_id int(11) NOT NULL auto_increment,
  download_name varchar(128) NOT NULL default '0',
  download_file varchar(200) NOT NULL default '',
  download_text text NOT NULL,
  download_typ varchar(200) NOT NULL default '0',
  download_counter int(11) NOT NULL default '0',
  PRIMARY KEY  (download_id),
  FULLTEXT KEY download_text (download_text),
  FULLTEXT KEY download_name (download_name)
) TYPE=MyISAM;
# --------------------------------------------------------

#
# Table structure for table `acme_download_typs`
#

CREATE TABLE acme_download_typs (
  download_typ_id int(11) NOT NULL auto_increment,
  download_typ_parent_id int(11) NOT NULL default '0',
  download_typ_tpl int(11) NOT NULL default '0',
  download_typ_img_small int(11) NOT NULL default '0',
  download_typ_img_big int(11) NOT NULL default '0',
  download_typ_frame int(11) NOT NULL default '0',
  download_typ_left_bar int(11) NOT NULL default '0',
  download_typ_right_bar int(11) NOT NULL default '0',
  download_typ_top_bar int(11) NOT NULL default '0',
  download_typ_foo_bar int(11) NOT NULL default '0',
  download_typ_name varchar(128) NOT NULL default '',
  download_typ_text text NOT NULL,
  PRIMARY KEY  (download_typ_id),
  FULLTEXT KEY download_typ_name (download_typ_name),
  FULLTEXT KEY download_typ_text (download_typ_text)
) TYPE=MyISAM;
# --------------------------------------------------------

#
# Table structure for table `acme_frame`
#

CREATE TABLE acme_frame (
  frame_id int(11) NOT NULL auto_increment,
  frame_name varchar(128) NOT NULL default '',
  frame_left_bar int(11) NOT NULL default '0',
  frame_right_bar int(11) NOT NULL default '0',
  frame_top_bar int(11) NOT NULL default '0',
  frame_foo_bar int(11) NOT NULL default '0',
  frame_tpl varchar(128) NOT NULL default '',
  PRIMARY KEY  (frame_id),
  UNIQUE KEY name (frame_name),
  KEY name_2 (frame_name)
) TYPE=MyISAM;
# --------------------------------------------------------

#
# Table structure for table `acme_glossar`
#

CREATE TABLE acme_glossar (
  glossar_id int(11) NOT NULL auto_increment,
  glossar_titel varchar(80) NOT NULL default '',
  glossar_text text NOT NULL,
  glossar_img int(11) NOT NULL default '0',
  glossar_tpl int(11) NOT NULL default '0',
  glossar_user_id int(11) NOT NULL default '0',
  glossar_groups varchar(200) NOT NULL default ':admin:',
  PRIMARY KEY  (glossar_id),
  FULLTEXT KEY glossar_titel (glossar_titel),
  FULLTEXT KEY glossar_text (glossar_text)
) TYPE=MyISAM;
# --------------------------------------------------------

#
# Table structure for table `acme_groups`
#

CREATE TABLE acme_groups (
  group_id int(11) NOT NULL auto_increment,
  group_name varchar(25) NOT NULL default '',
  PRIMARY KEY  (group_id)
) TYPE=MyISAM;
# --------------------------------------------------------

#
# Table structure for table `acme_module`
#

CREATE TABLE acme_module (
  modul varchar(128) NOT NULL default '',
  nav enum('Y','N') NOT NULL default 'Y',
  search enum('Y','N') NOT NULL default 'N',
  typ enum('L','C','A') NOT NULL default 'L',
  bar enum('Y','N') NOT NULL default 'N',
  table varchar(128) NOT NULL default '',
  id varchar(128) NOT NULL default '',
  name varchar(128) NOT NULL default '',
  navimg varchar(128) NOT NULL default '',
  logo varchar(128) NOT NULL default ''
) TYPE=MyISAM;
# --------------------------------------------------------

#
# Table structure for table `acme_nav`
#

CREATE TABLE acme_nav (
  nav_id int(11) NOT NULL auto_increment,
  nav_name varchar(60) NOT NULL default '0',
  nav_cache longtext NOT NULL,
  PRIMARY KEY  (nav_id)
) TYPE=MyISAM;
# --------------------------------------------------------

#
# Table structure for table `acme_nav_topics`
#

CREATE TABLE acme_nav_topics (
  nav_topic_id int(11) NOT NULL auto_increment,
  nav_id int(11) NOT NULL default '0',
  nav_topic_text varchar(128) NOT NULL default '',
  nav_topic_type varchar(128) NOT NULL default 'M',
  nav_topic_type_id int(11) NOT NULL default '0',
  nav_topic_rank int(11) default NULL,
  PRIMARY KEY  (nav_topic_id)
) TYPE=MyISAM;
# --------------------------------------------------------

#
# Table structure for table `acme_news_topics`
#

CREATE TABLE acme_news_topics (
  news_topic_id int(11) NOT NULL auto_increment,
  news_topic_type varchar(128) NOT NULL default '',
  news_topic_type_id int(11) NOT NULL default '0',
  news_topic_rank int(11) default NULL,
  PRIMARY KEY  (news_topic_id)
) TYPE=MyISAM;
# --------------------------------------------------------

#
# Table structure for table `acme_pages`
#

CREATE TABLE acme_pages (
  page_id int(11) NOT NULL auto_increment,
  page_name varchar(60) NOT NULL default '',
  page_tpl int(11) default NULL,
  page_parent int(11) default NULL,
  page_titelbild int(11) NOT NULL default '0',
  page_img_small int(11) default NULL,
  page_img_big int(11) default NULL,
  page_frame int(11) NOT NULL default '0',
  page_left_bar int(11) default NULL,
  page_right_bar int(11) default NULL,
  page_top_bar int(11) default NULL,
  page_foo_bar int(11) default NULL,
  page_headline text,
  page_short_text text,
  page_long_text text,
  page_long_text_typ enum('P','H','B') NOT NULL default 'B',
  page_author_id int(11) NOT NULL default '0',
  page_user_id int(11) NOT NULL default '0',
  page_childs varchar(128) NOT NULL default 'N',
  page_counter int(11) NOT NULL default '0',
  page_create_date datetime NOT NULL default '0000-00-00 00:00:00',
  page_modify_date datetime NOT NULL default '0000-00-00 00:00:00',
  page_comments enum('J','N','I') NOT NULL default 'N',
  PRIMARY KEY  (page_id),
  FULLTEXT KEY page_long_text (page_long_text),
  FULLTEXT KEY page_short_text (page_short_text),
  FULLTEXT KEY page_headline (page_headline)
) TYPE=MyISAM;
# --------------------------------------------------------

#
# Table structure for table `acme_profile`
#

CREATE TABLE acme_profile (
  home_id int(11) NOT NULL auto_increment,
  home_name varchar(128) NOT NULL default '',
  home_activ enum('Y','N') NOT NULL default 'N',
  home_img_id int(11) default NULL,
  home_page int(11) NOT NULL default '0',
  home_page_typ varchar(80) NOT NULL default '',
  home_frame int(11) NOT NULL default '0',
  home_tpl int(11) NOT NULL default '0',
  home_404 int(11) NOT NULL default '0',
  home_style varchar(60) NOT NULL default '',
  home_left_bar int(11) NOT NULL default '0',
  home_right_bar int(11) NOT NULL default '0',
  home_top_bar int(11) NOT NULL default '0',
  home_foo_bar int(11) NOT NULL default '0',
  PRIMARY KEY  (home_id)
) TYPE=MyISAM;
# --------------------------------------------------------

#
# Table structure for table `acme_rights`
#

CREATE TABLE acme_rights (
  rights_id int(11) NOT NULL auto_increment,
  group_id char(200) NOT NULL default '0',
  modul char(128) NOT NULL default '',
  rights_access char(1) NOT NULL default 'Y',
  rights_create char(1) NOT NULL default 'Y',
  rights_modify char(1) NOT NULL default 'Y',
  rights_delete char(1) NOT NULL default 'Y',
  PRIMARY KEY  (rights_id)
) TYPE=MyISAM;
# --------------------------------------------------------

#
# Table structure for table `acme_styles`
#

CREATE TABLE acme_styles (
  style_id int(11) NOT NULL auto_increment,
  style_name varchar(60) NOT NULL default '',
  style_text longtext NOT NULL,
  PRIMARY KEY  (style_id)
) TYPE=MyISAM;
# --------------------------------------------------------

#
# Table structure for table `acme_templates`
#

CREATE TABLE acme_templates (
  tpl_id int(11) NOT NULL auto_increment,
  tpl_name varchar(60) NOT NULL default '',
  tpl_content longtext NOT NULL,
  PRIMARY KEY  (tpl_id)
) TYPE=MyISAM;
# --------------------------------------------------------

#
# Table structure for table `acme_termin`
#

CREATE TABLE acme_termin (
  termin_id int(11) NOT NULL auto_increment,
  termin_parent_id int(11) NOT NULL default '0',
  termin_name varchar(128) NOT NULL default '0000-00-00 00:00:00',
  termin_tpl int(11) NOT NULL default '0',
  termin_img_small int(11) NOT NULL default '0',
  termin_img_big int(11) NOT NULL default '0',
  termin_frame int(11) NOT NULL default '0',
  termin_left_bar int(11) NOT NULL default '0',
  termin_right_bar int(11) NOT NULL default '0',
  termin_top_bar int(11) NOT NULL default '0',
  termin_foo_bar int(11) NOT NULL default '0',
  termin_titel varchar(200) NOT NULL default '',
  termin_text text NOT NULL,
  termin_counter int(11) NOT NULL default '0',
  termin_user_id int(11) NOT NULL default '0',
  PRIMARY KEY  (termin_id),
  FULLTEXT KEY termin_titel (termin_titel),
  FULLTEXT KEY termin_text (termin_text)
) TYPE=MyISAM;
# --------------------------------------------------------

#
# Table structure for table `acme_termin_data`
#

CREATE TABLE acme_termin_data (
  termin_typ varchar(200) NOT NULL default '0',
  termin_data_id int(11) NOT NULL auto_increment,
  termin_data_date_von datetime NOT NULL default '0000-00-00 00:00:00',
  termin_data_date_bis datetime NOT NULL default '0000-00-00 00:00:00',
  termin_data_headline varchar(128) NOT NULL default '',
  termin_data_Veranstalter text NOT NULL,
  termin_data_Ort text NOT NULL,
  termin_data_URL text NOT NULL,
  termin_data_content text NOT NULL,
  termin_data_user_id int(11) NOT NULL default '0',
  PRIMARY KEY  (termin_data_id),
  KEY blog_data_id (termin_data_id),
  FULLTEXT KEY termin_data_headline (termin_data_headline),
  FULLTEXT KEY termin_data_Veranstalter (termin_data_Veranstalter),
  FULLTEXT KEY termin_data_Ort (termin_data_Ort),
  FULLTEXT KEY termin_data_content (termin_data_content)
) TYPE=MyISAM;
# --------------------------------------------------------

#
# Table structure for table `acme_url`
#

CREATE TABLE acme_url (
  url_id int(11) NOT NULL auto_increment,
  url_name varchar(128) NOT NULL default '0',
  url_url text NOT NULL,
  url_text text NOT NULL,
  url_typ varchar(200) NOT NULL default '0',
  url_counter int(11) NOT NULL default '0',
  PRIMARY KEY  (url_id),
  FULLTEXT KEY url_name (url_name),
  FULLTEXT KEY url_text (url_text)
) TYPE=MyISAM;
# --------------------------------------------------------

#
# Table structure for table `acme_url_typs`
#

CREATE TABLE acme_url_typs (
  url_typ_id int(11) NOT NULL auto_increment,
  url_typ_parent_id int(11) NOT NULL default '0',
  url_typ_tpl int(11) NOT NULL default '0',
  url_typ_img_small int(11) NOT NULL default '0',
  url_typ_img_big int(11) NOT NULL default '0',
  url_typ_frame int(11) NOT NULL default '0',
  url_typ_left_bar int(11) NOT NULL default '0',
  url_typ_right_bar int(11) NOT NULL default '0',
  url_typ_top_bar int(11) NOT NULL default '0',
  url_typ_foo_bar int(11) NOT NULL default '0',
  url_typ_name varchar(128) NOT NULL default '',
  url_typ_text text NOT NULL,
  PRIMARY KEY  (url_typ_id),
  FULLTEXT KEY url_typ_name (url_typ_name),
  FULLTEXT KEY url_typ_text (url_typ_text)
) TYPE=MyISAM;
# --------------------------------------------------------

#
# Table structure for table `acme_user`
#

CREATE TABLE acme_user (
  user_id int(11) NOT NULL auto_increment,
  user_active enum('Y','N') NOT NULL default 'Y',
  user_name varchar(25) NOT NULL default '',
  user_passwd varchar(25) NOT NULL default '',
  user_groups varchar(200) NOT NULL default '',
  user_login enum('Y','N') NOT NULL default 'N',
  user_last_login datetime NOT NULL default '0000-00-00 00:00:00',
  PRIMARY KEY  (user_id)
) TYPE=MyISAM;

