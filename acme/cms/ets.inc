<?php

/**
 * ETS - Easy Template System - 3.02a
 * Copyright (C) 2002  Franck Marcia <phpets@hotmail.com>
 * http://ets.sourceforge.net
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * @author  Franck Marcia <phpets@hotmail.com>
 * @version 3.02a
 */

/**
 * Size reducing behaviour
 */
define('_ETS_REDUCE_NULL',         0);
define('_ETS_REDUCE_OFF',          1);
define('_ETS_REDUCE_SPACES',       2);
define('_ETS_REDUCE_ALL',          4);

/**
 * Parsing modes
 */
define('_ETS_DATA',                1);
define('_ETS_NAME',                2);
define('_ETS_CLOSING_TAG',         4);
define('_ETS_VALUE',               8);
define('_ETS_COMMENT',            16);
define('_ETS_CDATA',              32);

/**
 * Parsing mode groups
 */
define('_ETS_GROUP0',  _ETS_COMMENT + _ETS_CDATA);

/**
 * Element types
 */
define('_ETS_NULL',              0x0);
define('_ETS_ROOT',              0x1);
define('_ETS_TEXT',              0x2);
define('_ETS_TAG',               0x4);
define('_ETS_ALT_TAG',           0x8);
define('_ETS_TEMPLATE',         0x10);
define('_ETS_SET',              0x20);
define('_ETS_SETVAL',           0x40);
define('_ETS_MIS',              0x80);
define('_ETS_MISVAL',          0x100);
define('_ETS_PHP',             0x200);
define('_ETS_CONST',           0x400);
define('_ETS_IF',              0x800);
define('_ETS_CODE',           0x1000);
define('_ETS_CHOOSE',         0x2000);
define('_ETS_WHENTEST',       0x4000);
define('_ETS_ELSE',           0x8000);
define('_ETS_CHOOSEVAR',     0x10000);
define('_ETS_WHENVAL',       0x20000);
define('_ETS_CALL',          0x40000);
define('_ETS_ARG',           0x80000);
define('_ETS_MIS_TEMPLATE', 0x100000);
define('_ETS_REDUCE',       0x200000);
define('_ETS_REPEAT',       0x400000);
define('_ETS_INCLUDE',      0x800000);
define('_ETS_INSERT',      0x1000000);

/**
 * Element type groups
 */

define('_ETS_CODEs',   _ETS_CODE    + _ETS_PHP);
define('_ETS_CHOOSEs', _ETS_CHOOSE  + _ETS_CHOOSEVAR);
define('_ETS_SETs',    _ETS_SET     + _ETS_SETVAL);
define('_ETS_MISs',    _ETS_MIS     + _ETS_MISVAL);
define('_ETS_GROUP1',  _ETS_CHOOSEs + _ETS_CODEs + _ETS_CALL + _ETS_ROOT);
define('_ETS_GROUP2',  _ETS_CHOOSEs + _ETS_CODEs + _ETS_CALL);
define('_ETS_GROUP3',  _ETS_CHOOSEs + _ETS_CALL  + _ETS_ROOT);

/**
 * Building directions
 */
define('_ETS_FORWARD',             1);
define('_ETS_BACKWARD',            2);

/**
 * Building types
 */
define('_ETS_MISSING',             1);
define('_ETS_SCALAR',              2);
define('_ETS_COMPLEX',             4);
define('_ETS_PARENT',              8);
define('_ETS_FROM_ROOT',          16);


/**
 * Template management class
 * This class is intended to be used by printt() and sprintt() only
 */
class _ets
{
	/**
	 * Data tree
	 */
	var $datatree;

	/**
	 * Mask tree
	 */
	var $masktree = array();

	/**
	 * Size reducing behavior
	 */
	var $reduce = _ETS_REDUCE_NULL;

	/**
	 * Current file name in parsing
	 */
	var $filename = NULL;


	/*****   E R R O R   *****/

    /**
     * Print out error message and exit
     */
	function error($type, $message, $line = 0, $elttype = _ETS_NULL)
	{
		switch ($type) {
			case 0:
				if ($elttype == _ETS_ROOT) {
					echo "<b>ETS error:</b> $message can't be defined outside a template on line $line of <b>{$this->filename}</b><br>";
				} else {
					echo '<b>ETS error:</b> ' . $this->eltlabel($elttype) . " can't contain $message on line $line of <b>{$this->filename}</b><br>";
				}
				exit;
			case 1:
				echo '<b>ETS error:</b> unexpected closing tag {/' . $message . "} on line $line of <b>{$this->filename}</b><br>";
				exit;
			case 2:
				echo "<b>ETS error:</b> $message on line $line of <b>{$this->filename}</b><br>";
				exit;
			case 3:
				echo "<b>ETS error:</b> end of " . $this->modelabel($elttype) . " starting on line $line not found in file <b>{$this->filename}</b><br>";
				exit;
			case 4:
				echo "<b>ETS error:</b> closing tag not found for " . $this->eltlabel($elttype) . " starting on line $line in file <b>{$this->filename}</b><br>";
				exit;
			case 5:
				if ($line == 0) {
					echo "<b>ETS error:</b> unable to read file $message given as argument<br>";
				} else {
					echo "<b>ETS error:</b> unable to read file $message of " . $this->eltlabel($elttype) . " on line $line of <b>{$this->filename}</b><br>";
				}
				exit;
		}
	}

	/**
	 * Define the label of a element type from an id
	 */
	function eltlabel($eltid)
	{
		switch($eltid) {
			case _ETS_ROOT:         return 'root element';
			case _ETS_TEXT:         return 'text element';
			case _ETS_TAG:          return 'simple tag element';
			case _ETS_ALT_TAG:      return 'alternate tag element';
			case _ETS_TEMPLATE:     return 'template element';
			case _ETS_SET:          return 'set element';
			case _ETS_SETVAL:       return 'set-value element';
			case _ETS_MIS:          return 'missing element';
			case _ETS_MISVAL:       return 'missing-value element';
			case _ETS_PHP:          return 'PHP element';
			case _ETS_CONST:        return 'constant element';
			case _ETS_IF:           return 'if element';
			case _ETS_CODE:         return 'PHP code or test';
			case _ETS_CHOOSE:       return 'choose element';
			case _ETS_WHENTEST:     return 'when-test element';
			case _ETS_ELSE:         return 'else element';
			case _ETS_CHOOSEVAR:    return 'choose-variable element';
			case _ETS_WHENVAL:      return 'when-value element';
			case _ETS_CALL:         return 'call element';
			case _ETS_ARG:          return 'argument element';
			case _ETS_MIS_TEMPLATE: return 'missing template element';
			case _ETS_REDUCE:       return 'reduce element';
			case _ETS_REPEAT:       return 'repeat element';
			case _ETS_INCLUDE:      return 'include element';
			case _ETS_INSERT:       return 'insert element';
		}
	}

	/**
	 * Define the label of a parsing mode from an id
	 */
	function modelabel($modeid)
	{
		switch($modeid) {
			case _ETS_COMMENT:      return 'comment';
			case _ETS_CDATA:        return 'cdata';
		}
	}


	/*****   P A R S I N G   *****/

    /**
     * Define size reducing behavior
     */
	function set_reduce($value)
	{
		switch(strtoupper($value)) {
			case 'OFF':
			case 'NOTHING':
				$this->reduce = _ETS_REDUCE_OFF;
				break;

			case 'SPACE':
			case 'SPACES':
				$this->reduce = _ETS_REDUCE_SPACES;
				break;

			case 'CRLF':
			case 'ON':
			case 'ALL':
				$this->reduce = _ETS_REDUCE_ALL;
				break;
		}
	}

    /**
     * Walk through a slash separated path of a node to build a tree
     */
	function node_path_walk($elements, $rank, $ptype, &$i, &$line, $cvalue, $ncontent, $content)
	{
		if (count($elements) == 1) {
			$elt[$ptype . ':' . $i . ':' . $elements[0] . ':' . $cvalue] = $this->parse($ptype, $i, $line, $ncontent, $content);
		} else {
			$element1 = array_shift($elements);
			$masktype = ($ptype == _ETS_MIS || $ptype == _ETS_MISVAL) ? _ETS_MIS_TEMPLATE : _ETS_TEMPLATE;
			$elt[$masktype . ':' . $i . '.' . $rank . ':' . $element1] = $this->node_path_walk($elements, $rank + 1, $ptype, $i, $line, $cvalue, $ncontent, $content);
		}
		return $elt;
	}

    /**
     * Store a new node in the template tree
     */
	function store_node(&$elts, $ptype, &$i, &$line, $cname, $cvalue, $ncontent, $content)
	{
		$isabsolute = FALSE;
		if ($cname{0} == '/' && $cname{1} == '/') {
			$isabsolute = TRUE;
			$cname = substr($cname, 2);
		}
		$elements = explode('/', $cname);
		if (count($elements) == 1 && !$isabsolute) {
			$elts[$ptype . ':' . $i . ':' . $cname . ':' . $cvalue] = $this->parse($ptype, $i, $line, $ncontent, $content);
		} else {
			if ($isabsolute) {
				$elts[_ETS_TEMPLATE . ':' . $i . '.1://'] = $this->node_path_walk($elements, 2, $ptype, $i, $line, $cvalue, $ncontent, $content);
			} else {
				$element1 = array_shift($elements);
				$masktype = ($ptype == _ETS_MIS || $ptype == _ETS_MISVAL) ? _ETS_MIS_TEMPLATE : _ETS_TEMPLATE;
				$elts[$masktype . ':' . $i . '.1:' . $element1] = $this->node_path_walk($elements, 2, $ptype, $i, $line, $cvalue, $ncontent, $content);
			}
		}
	}

    /**
     * Walk through a slash separated path of a leaf to build a tree
     */
	function leaf_path_walk($elements, $rank, $ptype, &$i, $cvalue)
	{
		if (count($elements) == 1) {
			$elt[$ptype . ':' . $i . ':' . $elements[0] . ':' . $cvalue] = '';
		} else {
			$element1 = array_shift($elements);
			$elt[_ETS_TEMPLATE . ':' . $i . '.' . $rank . ':' . $element1] = $this->leaf_path_walk($elements, $rank + 1, $ptype, $i, $cvalue);
		}
		return $elt;
	}

    /**
     * Store a new leaf in the template tree
     */
	function store_leaf(&$elts, $ptype, &$i, $cname, $cvalue = NULL)
	{
		$isabsolute = FALSE;
		if ($cname{0} == '/' && $cname{1} == '/') {
			$isabsolute = TRUE;
			$cname = substr($cname, 2);
		}

		$elements = explode('/', $cname);
		if (count($elements) == 1 && !$isabsolute) {
			$elts[$ptype . ':' . $i . ':' . $cname . ':' . $cvalue] = '';
		} else {
			if ($isabsolute) {
				$elts[_ETS_TEMPLATE . ':' . $i . '.1://'] = $this->leaf_path_walk($elements, 2, $ptype, $i, $cvalue);
			} else {
				$element1 = array_shift($elements);
				$elts[_ETS_TEMPLATE . ':' . $i . '.1:' . $element1] = $this->leaf_path_walk($elements, 2, $ptype, $i, $cvalue);
			}
		}
	}

    /**
     * Store a new text in the template tree
     */
	function store_text(&$elts, &$i, $ptype, $ntext, $ctext)
	{
		if ($ntext == 1) {
			if ($ptype == _ETS_CODE) { // don't store border spaces in code
				$ctext = trim($ctext);
				if ($ctext !== '') {
					$elts[_ETS_TEXT . ':' . $i] = $ctext;
				}
			} elseif ($ptype != _ETS_ROOT) {
				$elts[_ETS_TEXT . ':' . $i] = $ctext;
			}
		}
	}

	/**
	 * Define if the parameter is a non printable character
	 */
	function is_space($char)
	{
		$asc = ord($char);
		if ($asc == 32) {
			return TRUE;
		} elseif ($asc > 8 && $asc < 14) {
			return TRUE;
		}
		return FALSE;
	}

    /**
     * Recursively parse template
     */
	function parse($ptype, &$i, &$line, $ncontent, $content)
	{
		$elts = array();
		$mode = _ETS_DATA;
		$ntext = $nname = $nvalue = $nspace = 0;
		$ctext = $cname = $cvalue = '';
		$nameinvalue = 0;
		$nametype = NULL;
		$nspecial = 0;
		$saveline = $line;

		for ( ; $i < $ncontent; ++$i) {

			// current character and following
			$c0 = $content{$i};
			$c1 = $content{$i + 1};
			$a0 = ord($c0);

			// line count
			if ($a0 == 10 || ($a0 == 13 && ord($c1) != 10)) {
				++$line;
			}

			// data acquisition
			if ($mode == _ETS_DATA) {

				// tag?
				if ($c0 == '{') {

					$c2 = $content{$i + 2};
					$c3 = $content{$i + 3};
					$c4 = $content{$i + 4};
					$c5 = $content{$i + 5};
					$c6 = $content{$i + 6};
					$c7 = $content{$i + 7};

					// {* (comment)
					if ($c1 == '*') {
						if ($ptype & _ETS_CODEs) {
							$this->error(0, 'comment', $line, $ptype);
						}
						$this->store_text($elts, $i, $ptype, $ntext, $ctext);
						$mode = _ETS_COMMENT;
						$ntext = $nname = $nvalue = $nspace = 0;
						$ctext = $cname = $cvalue = '';
						$nameinvalue = 0;
						$nametype = NULL;
						++$i;
						++$nspecial;
						$saveline = $line;

					// {# (cdata)
					} elseif ($c1 == '#') {
						if ($ptype & _ETS_GROUP1) {
							$this->error(0, 'cdata', $line, $ptype);
						}
						$this->store_text($elts, $i, $ptype, $ntext, $ctext);
						$mode = _ETS_CDATA;
						$ntext = $nname = $nvalue = $nspace = 0;
						$ctext = $cname = $cvalue = '';
						$nameinvalue = 0;
						$nametype = NULL;
						++$i;
						++$nspecial;
						$saveline = $line;

					// {mask:
					} elseif ($c1 == 'm' && $c2 == 'a' && $c3 == 's' && $c4 == 'k' && $c5 == ':') {
						if ($ptype & _ETS_GROUP2) {
							$this->error(0, 'template element', $line, $ptype);
						}
						$this->store_text($elts, $i, $ptype, $ntext, $ctext);
						$mode = _ETS_NAME;
						$ntext = $nname = $nvalue = $nspace = 0;
						$ctext = $cname = $cvalue = '';
						$nameinvalue = 0;
						$nametype = _ETS_TEMPLATE;
						$i += 5;

					// {call:
					} elseif ($c1 == 'c' && $c2 == 'a' && $c3 == 'l' && $c4 == 'l' && $c5 == ':') {
						if ($ptype & _ETS_GROUP1) {
							$this->error(0, 'call element', $line, $ptype);
						}
						$this->store_text($elts, $i, $ptype, $ntext, $ctext);
						$mode = _ETS_NAME;
						$ntext = $nname = $nvalue = $nspace = 0;
						$ctext = $cname = $cvalue = '';
						$nameinvalue = 0;
						$nametype = _ETS_CALL;
						$i += 5;

					// {const:
					} elseif ($c1 == 'c' && $c2 == 'o' && $c3 == 'n' && $c4 == 's' && $c5 == 't' && $c6 == ':') {
						if ($ptype & _ETS_GROUP1) {
							$this->error(0, 'constant element', $line, $ptype);
						}
						$this->store_text($elts, $i, $ptype, $ntext, $ctext);
						$mode = _ETS_NAME;
						$ntext = $nname = $nvalue = $nspace = 0;
						$ctext = $cname = $cvalue = '';
						$nameinvalue = 0;
						$nametype = _ETS_CONST;
						$i += 6;

					// {set:
					} elseif ($c1 == 's' && $c2 == 'e' && $c3 == 't' && $c4 == ':') {
						if ($ptype & _ETS_GROUP1) {
							$this->error(0, 'set element', $line, $ptype);
						}
						$this->store_text($elts, $i, $ptype, $ntext, $ctext);
						$mode = _ETS_NAME;
						$ntext = $nname = $nvalue = $nspace = 0;
						$ctext = $cname = $cvalue = '';
						$nameinvalue = 0;
						$nametype = _ETS_SET;
						$i += 4;

					// {mis:
					} elseif ($c1 == 'm' && $c2 == 'i' && $c3 == 's' && $c4 == ':') {
						if ($ptype & _ETS_GROUP1) {
							$this->error(0, 'missing element', $line, $ptype);
						}
						$this->store_text($elts, $i, $ptype, $ntext, $ctext);
						$mode = _ETS_NAME;
						$ntext = $nname = $nvalue = $nspace = 0;
						$ctext = $cname = $cvalue = '';
						$nameinvalue = 0;
						$nametype = _ETS_MIS;
						$i += 4;

					// {choose:
					} elseif ($c1 == 'c' && $c2 == 'h' && $c3 == 'o' && $c4 == 'o' && $c5 == 's' && $c6 == 'e' && $c7 == ':') {
						if ($ptype & _ETS_GROUP1) {
							$this->error(0, 'choose element', $line, $ptype);
						}
						$this->store_text($elts, $i, $ptype, $ntext, $ctext);
						$mode = _ETS_NAME;
						$ntext = $nname = $nvalue = $nspace = 0;
						$ctext = $cname = $cvalue = '';
						$nameinvalue = 0;
						$nametype = _ETS_CHOOSEVAR;
						$i += 7;

					// {arg:
					} elseif ($c1 == 'a' && $c2 == 'r' && $c3 == 'g' && $c4 == ':') {
						if ($ptype == _ETS_CALL) {
							$mode = _ETS_NAME;
							$ntext = $nname = $nvalue = $nspace = 0;
							$ctext = $cname = $cvalue = '';
							$nameinvalue = 0;
							$nametype = _ETS_ARG;
							$i += 4;
						} else {
							$this->error(0, 'argument element', $line, $ptype);
						}

					// {reduce:
					} elseif ($c1 == 'r' && $c2 == 'e' && $c3 == 'd' && $c4 == 'u' && $c5 == 'c' && $c6 == 'e' && $c7 == ':') {
						if ($ptype == _ETS_ROOT) {
							if ($this->reduce == _ETS_REDUCE_NULL) {
								$mode = _ETS_NAME;
								$ntext = $nname = $nvalue = $nspace = 0;
								$ctext = $cname = $cvalue = '';
								$nameinvalue = 0;
								$nametype = _ETS_REDUCE;
								$i += 7;
							} else {
								$this->error(2, 'reuse of reduce element', $line, $ptype);
							}
						} else {
							$this->error(0, 'reduce element', $line, $ptype);
						}

					// {include:
					} elseif ($c1 == 'i' && $c2 == 'n' && $c3 == 'c' && $c4 == 'l' && $c5 == 'u' && $c6 == 'd' && $c7 == 'e' & $content{$i + 8} == ':') {
						if ($ptype & _ETS_GROUP2) {
							$this->error(0, 'include element', $line, $ptype);
						}
						$this->store_text($elts, $i, $ptype, $ntext, $ctext);
						$mode = _ETS_VALUE;
						$ntext = $nname = $nvalue = $nspace = 0;
						$ctext = $cname = $cvalue = '';
						$nameinvalue = 0;
						$nametype = _ETS_INCLUDE;
						switch ($content{$i + 9}) {
							case '\'':	$quotetype = 1; $i += 9; break;
							case '"':	$quotetype = 2; $i += 9; break;
							default:	$quotetype = 0; $i += 8; break;
						}

					// {insert:
					} elseif ($c1 == 'i' && $c2 == 'n' && $c3 == 's' && $c4 == 'e' && $c5 == 'r' && $c6 == 't' && $c7 == ':') {
						if ($ptype & _ETS_GROUP1) {
							$this->error(0, 'insert element', $line, $ptype);
						}
						$this->store_text($elts, $i, $ptype, $ntext, $ctext);
						$mode = _ETS_VALUE;
						$ntext = $nname = $nvalue = $nspace = 0;
						$ctext = $cname = $cvalue = '';
						$nameinvalue = 0;
						$nametype = _ETS_INSERT;
						switch ($content{$i + 8}) {
							case '\'':	$quotetype = 1; $i += 8; break;
							case '"':	$quotetype = 2; $i += 8; break;
							default:	$quotetype = 0; $i += 7; break;
						}

					// {when:
					} elseif ($c1 == 'w' && $c2 == 'h' && $c3 == 'e' && $c4 == 'n' && $c5 == ':') {

						// of of whentest
						if ($ptype == _ETS_CHOOSE) {
							$mode = _ETS_DATA;
							$ntext = $nname = $nvalue = $nspace = 0;
							$ctext = $cname = $cvalue = '';
							$nameinvalue = 0;
							$nametype = NULL;
							$i += 6;
							$index = _ETS_WHENTEST . ':' . $i;
							$elts['when'][$index]['test'] = $this->parse(_ETS_CODE,     $i, $line, $ncontent, $content);
							$elts['when'][$index]['true'] = $this->parse(_ETS_WHENTEST, $i, $line, $ncontent, $content);
						}

						// of whenval
						elseif ($ptype == _ETS_CHOOSEVAR) {
							$mode = _ETS_VALUE;
							$ntext = $nname = $nvalue = $nspace = 0;
							$ctext = $cname = $cvalue = '';
							$nameinvalue = 0;
							$nametype = _ETS_WHENVAL;
							switch ($c6) {
								case '\'':	$quotetype = 1; $i += 6; break;
								case '"':	$quotetype = 2; $i += 6; break;
								default:	$quotetype = 0; $i += 5; break;
							}

						} else {
							$this->error(0, 'when element', $line, $ptype);
						}

					// {if:
					} elseif ($c1 == 'i' && $c2 == 'f' && $c3 == ':') {
						if ($ptype & _ETS_GROUP1) {
							$this->error(0, 'if element', $line, $ptype);
						}
						$this->store_text($elts, $i, $ptype, $ntext, $ctext);
						$mode = _ETS_DATA;
						$ntext = $nname = $nvalue = $nspace = 0;
						$ctext = $cname = $cvalue = '';
						$nameinvalue = 0;
						$nametype = NULL;
						$i += 4;
						$index = _ETS_IF . ':' . $i;
						$elts[$index]['test'] = $this->parse(_ETS_CODE, $i, $line, $ncontent, $content);
						$elts[$index]['true'] = $this->parse(_ETS_IF, $i, $line, $ncontent, $content);

					// {repeat:
					} elseif ($c1 == 'r' && $c2 == 'e' && $c3 == 'p' && $c4 == 'e' && $c5 == 'a' && $c6 == 't' && $c7 == ':') {
						if ($ptype & _ETS_GROUP1) {
							$this->error(0, 'repeat element', $line, $ptype);
						}
						$this->store_text($elts, $i, $ptype, $ntext, $ctext);
						$mode = _ETS_DATA;
						$ntext = $nname = $nvalue = $nspace = 0;
						$ctext = $cname = $cvalue = '';
						$nameinvalue = 0;
						$nametype = NULL;
						$i += 8;
						$index = _ETS_REPEAT . ':' . $i;
						$elts[$index]['value'] = $this->parse(_ETS_CODE, $i, $line, $ncontent, $content);
						$elts[$index]['repeat'] = $this->parse(_ETS_REPEAT, $i, $line, $ncontent, $content);

					// simple tag with absolute path
					} elseif ($c1 == '/' && $c2 == '/') {
						if ($ptype & _ETS_GROUP3) {
							$this->error(0, 'simple tag element with absolute path', $line, $ptype);
						}
						$this->store_text($elts, $i, $ptype, $ntext, $ctext);
						$mode = _ETS_NAME;
						$ntext = $nname = $nvalue = $nspace = 0;
						$ctext = $cvalue = '';
						$cname = '//';
						$nameinvalue = 0;
						$nametype = _ETS_TAG;
						$i += 2;

					// other simple tag
					} elseif ($c1 != '/' && !$this->is_space($c1)) {

						// {else
						if ($c1 == 'e' && $c2 == 'l' && $c3 == 's' && $c4 == 'e' && ($this->is_space($c5) || $c5 == '}' )) {
							if ($ptype & _ETS_CHOOSEs) {
								$mode = _ETS_NAME;
								$ntext = $nvalue = $nspace = 0;
								$nname = 1;
								$ctext = $cvalue = '';
								$cname = 'else';
								$nameinvalue = 0;
								$nametype = _ETS_TAG;
								$i += 4;
							} else {
								$this->error(0, 'else element', $line, $ptype);
							}

						} elseif ($ptype & _ETS_GROUP3) {
							$this->error(0, 'simple tag element', $line, $ptype);

						// other
						} else {
							$this->store_text($elts, $i, $ptype, $ntext, $ctext);
							$mode = _ETS_NAME;
							$ntext = $nname = $nvalue = $nspace = 0;
							$ctext = $cname = $cvalue = '';
							$nameinvalue = 0;
							$nametype = _ETS_TAG;
						}

					// {/mask
					} elseif ($c1 == '/' && $c2 == 'm' && $c3 == 'a' && $c4 == 's' && $c5 == 'k') {
						if ($ptype == _ETS_TEMPLATE) {
							$this->store_text($elts, $i, $ptype, $ntext, $ctext);
							$mode = _ETS_CLOSING_TAG;
							$ntext = $nname = $nvalue = $nspace = 0;
							$ctext = $cname = $cvalue = '';
							$nameinvalue = 0;
							$nametype = NULL;
							$i += 5;
						} else {
							$this->error(1, 'mask', $line, $ptype);
						}

					// {/set
					} elseif ($c1 == '/' && $c2 == 's' && $c3 == 'e' && $c4 == 't') {
						if ($ptype & _ETS_SETs) {
							$this->store_text($elts, $i, $ptype, $ntext, $ctext);
							$mode = _ETS_CLOSING_TAG;
							$ntext = $nname = $nvalue = $nspace = 0;
							$ctext = $cname = $cvalue = '';
							$nameinvalue = 0;
							$nametype = NULL;
							$i += 4;
						} else {
							$this->error(1, 'set', $line, $ptype);
						}

					// {/mis
					} elseif ($c1 == '/' && $c2 == 'm' && $c3 == 'i' && $c4 == 's') {
						if ($ptype & _ETS_MISs) {
							$this->store_text($elts, $i, $ptype, $ntext, $ctext);
							$mode = _ETS_CLOSING_TAG;
							$ntext = $nname = $nvalue = $nspace = 0;
							$ctext = $cname = $cvalue = '';
							$nameinvalue = 0;
							$nametype = NULL;
							$i += 4;
						} else {
							$this->error(1, 'mis', $line, $ptype);
						}

					// {/php
					} elseif ($c1 == '/' && $c2 == 'p' && $c3 == 'h' && $c4 == 'p') {
						if ($ptype == _ETS_PHP) {
							$this->store_text($elts, $i, $ptype, $ntext, $ctext);
							$mode = _ETS_CLOSING_TAG;
							$ntext = $nname = $nvalue = $nspace = 0;
							$ctext = $cname = $cvalue = '';
							$nameinvalue = 0;
							$nametype = NULL;
							$i += 4;
						} else {
							$this->error(1, 'PHP', $line, $ptype);
						}

					// {/if
					} elseif ($c1 == '/' && $c2 == 'i' && $c3 == 'f') {
						if ($ptype == _ETS_IF) {
							$this->store_text($elts, $i, $ptype, $ntext, $ctext);
							$mode = _ETS_CLOSING_TAG;
							$ntext = $nname = $nvalue = $nspace = 0;
							$ctext = $cname = $cvalue = '';
							$nameinvalue = 0;
							$nametype = NULL;
							$i += 3;
						} else {
							$this->error(1, 'if', $line, $ptype);
						}

					// {/choose
					} elseif ($c1 == '/' && $c2 == 'c' && $c3 == 'h' && $c4 == 'o' && $c5 == 'o' && $c6 == 's' && $c7 == 'e') {
						if ($ptype & _ETS_CHOOSEs) {
							$mode = _ETS_CLOSING_TAG;
							$ntext = $nname = $nvalue = $nspace = 0;
							$ctext = $cname = $cvalue = '';
							$nameinvalue = 0;
							$nametype = NULL;
							$i += 7;
						} else {
							$this->error(1, 'choose', $line, $ptype);
						}

					// {/call
					} elseif ($c1 == '/' && $c2 == 'c' && $c3 == 'a' && $c4 == 'l' && $c5 == 'l') {
						if ($ptype == _ETS_CALL) {
							$mode = _ETS_CLOSING_TAG;
							$ntext = $nname = $nvalue = $nspace = 0;
							$ctext = $cname = $cvalue = '';
							$nameinvalue = 0;
							$nametype = NULL;
							$i += 5;
						} else {
							$this->error(1, 'call', $line, $ptype);
						}

					// {/arg
					} elseif ($c1 == '/' && $c2 == 'a' && $c3 == 'r' && $c4 == 'g') {
						if ($ptype == _ETS_ARG) {
							$this->store_text($elts, $i, $ptype, $ntext, $ctext);
							$mode = _ETS_CLOSING_TAG;
							$ntext = $nname = $nvalue = $nspace = 0;
							$ctext = $cname = $cvalue = '';
							$nameinvalue = 0;
							$nametype = NULL;
							$i += 4;
						} else {
							$this->error(1, 'arg', $line, $ptype);
						}

					// {/when
					} elseif ($c1 == '/' && $c2 == 'w' && $c3 == 'h' && $c4 == 'e' && $c5 == 'n') {

						// of when val
						if ($ptype == _ETS_WHENVAL) {
							$this->store_text($elts, $i, $ptype, $ntext, $ctext);
							$mode = _ETS_CLOSING_TAG;
							$ntext = $nname = $nvalue = $nspace = 0;
							$ctext = $cname = $cvalue = '';
							$nameinvalue = 0;
							$nametype = NULL;
							$i += 5;

						// of when test
						} elseif ($ptype == _ETS_WHENTEST) {
							$this->store_text($elts, $i, $ptype, $ntext, $ctext);
							$mode = _ETS_CLOSING_TAG;
							$ntext = $nname = $nvalue = $nspace = 0;
							$ctext = $cname = $cvalue = '';
							$nameinvalue = 0;
							$nametype = NULL;
							$i += 5;

						} else {
							$this->error(1, 'when', $line, $ptype);
						}

					// {/else
					} elseif ($c1 == '/' && $c2 == 'e' && $c3 == 'l' && $c4 == 's' && $c5 == 'e') {
						if ($ptype == _ETS_ELSE) {
							$this->store_text($elts, $i, $ptype, $ntext, $ctext);
							$mode = _ETS_CLOSING_TAG;
							$ntext = $nname = $nvalue = $nspace = 0;
							$ctext = $cname = $cvalue = '';
							$nameinvalue = 0;
							$nametype = NULL;
							$i += 5;
						} else {
							$this->error(1, 'else', $line, $ptype);
						}

					// {/repeat
					} elseif ($c1 == '/' && $c2 == 'r' && $c3 == 'e' && $c4 == 'p' && $c5 == 'e' && $c6 == 'a' && $c7 == 't') {
						if ($ptype == _ETS_REPEAT) {
							$this->store_text($elts, $i, $ptype, $ntext, $ctext);
							$mode = _ETS_CLOSING_TAG;
							$ntext = $nname = $nvalue = $nspace = 0;
							$ctext = $cname = $cvalue = '';
							$nameinvalue = 0;
							$nametype = NULL;
							$i += 7;
						} else {
							$this->error(1, 'repeat', $line, $ptype);
						}

					// {/ (simplified closing tag)
					} elseif ($c1 == '/' && ($c2 == '}' || $this->is_space($c2))) {
						if ($ptype != _ETS_ROOT) {
							$this->store_text($elts, $i, $ptype, $ntext, $ctext);
							$mode = _ETS_CLOSING_TAG;
							$ntext = $nname = $nvalue = $nspace = 0;
							$ctext = $cname = $cvalue = '';
							$nameinvalue = 0;
							$nametype = NULL;
							++$i;
						} else {
							$this->error(1, '', $line, $ptype);
						}

					// text
					} elseif ($ptype != _ETS_CHOOSE && $ptype != _ETS_CHOOSEVAR && $ptype != _ETS_CALL && $ptype != _ETS_ROOT) {
						$ctext .= $c0;
						$ntext = 1;
					}

				// end of test of if or whentest element
				} elseif ($c0 == '}' && $ptype == _ETS_CODE) {
					$this->store_text($elts, $i, $ptype, $ntext, $ctext);
					++$i;
					return $elts;

				// no text in choosevar element
				} elseif ($ptype == _ETS_CHOOSE && !$this->is_space($c0)) {
					$this->error(2, "unexpected character '$c0' in choose element", $line);

				// no text in choose element
				} elseif ($ptype == _ETS_CHOOSEVAR && !$this->is_space($c0)) {
					$this->error(2, "unexpected character '$c0' in choose-variable element", $line);

				// no text in call element
				} elseif ($ptype == _ETS_CALL && !$this->is_space($c0)) {
					$this->error(2, "unexpected character '$c0' in call element", $line);

				// text
				} elseif ($ptype != _ETS_ROOT) {
					$ctext .= $c0;
					$ntext = 1;
				}

			// name acquisition
			} elseif ($mode == _ETS_NAME) {

				// end of name acquisition
				if ($c0 == '}' && $nname == 1) {

					// reduce
					if ($nametype == _ETS_REDUCE) {
						$this->set_reduce($cname);

					// template
					} elseif ($nametype == _ETS_TEMPLATE) {
						++$i;
						if ($ptype != _ETS_ROOT) {
							$this->store_node($elts, _ETS_TEMPLATE, $i, $line, $cname, NULL, $ncontent, $content);
						} elseif (isset($elts[$cname])) {
							$this->error(2, "template $cname already defined", $line);
						} else {
							$elts[$cname] = $this->parse(_ETS_TEMPLATE, $i, $line, $ncontent, $content);
						}

					// call
					} elseif ($nametype == _ETS_CALL) {
						++$i;
						$this->store_node($elts, _ETS_CALL, $i, $line, $cname, NULL, $ncontent, $content);

					// const
					} elseif ($nametype == _ETS_CONST) {
						$this->store_leaf($elts, _ETS_CONST, $i, $cname);

					// set
					} elseif ($nametype == _ETS_SET) {
						++$i;
						$this->store_node($elts, _ETS_SET, $i, $line, $cname, NULL, $ncontent, $content);

					// mis
					} elseif ($nametype == _ETS_MIS) {
						++$i;
						$this->store_node($elts, _ETS_MIS, $i, $line, $cname, NULL, $ncontent, $content);

					// tag?
					} elseif ($nametype == _ETS_TAG) {

						// php
						if ($cname == 'php') {
							++$i;
							$elts[_ETS_PHP . ':' . $i] = $this->parse(_ETS_PHP, $i, $line, $ncontent, $content);

						// choose
						} elseif ($cname == 'choose') {
							++$i;
							$elts[_ETS_CHOOSE . ':' . $i] = $this->parse(_ETS_CHOOSE, $i, $line, $ncontent, $content);

						// else
						} elseif (($ptype == _ETS_CHOOSE || $ptype == _ETS_CHOOSEVAR) && $cname == 'else') {
							if (isset($elts['else'])) {
								$this->error(2, "else statement already exists in " . $this->eltlabel($ptype), $line);
							} else {
								++$i;
								$elts['else'] = $this->parse(_ETS_ELSE, $i, $line, $ncontent, $content);
							}

						// alternate tag
						} elseif ($nameinvalue == 1) {
							$this->store_leaf($elts, _ETS_ALT_TAG, $i, $cname, $cvalue);
							$nameinvalue = 0;

						// tag!
						} else {
							$this->store_leaf($elts, _ETS_TAG, $i, $cname);
						}

					// choose var
					} elseif ($nametype == _ETS_CHOOSEVAR) {
						++$i;
						$this->store_node($elts, _ETS_CHOOSEVAR, $i, $line, $cname, NULL, $ncontent, $content);

					// arg
					} elseif ($nametype == _ETS_ARG) {
						++$i;
						$this->store_node($elts, _ETS_ARG, $i, $line, $cname, NULL, $ncontent, $content);
					}

					$mode = _ETS_DATA;

				// space in name acquisition
				} elseif ($this->is_space($c0)) {
					if (($nameinvalue == 0 && $nname == 1) || ($nameinvalue == 1 && $nvalue == 1)) {
						$nspace = 1;
					} else {
						$this->error(2, "unexpected space before name", $line);
					}

				// start of value acquisition
				} elseif ($c0 == ':' && $nname == 1 && ($nametype == _ETS_SET || $nametype == _ETS_MIS)) {
					$cvalue = '';
					$nvalue = 0;
					$nspace = 0;
					$mode = _ETS_VALUE;
					switch ($c1) {
						case '\'':	$quotetype = 1; ++$i; break;
						case '"':	$quotetype = 2; ++$i; break;
						default:	$quotetype = 0;       break;
					}

				// start of second name acquisition
				} elseif ($c0 == ':' && $nametype == _ETS_TAG && $nname == 1 && $nvalue == 0) {
					$cvalue = '';
					$nvalue = 0;
					$nameinvalue = 1;
					$nspace = 0;

				// data after trailing spaces
				} elseif ($nspace == 1) {
					$this->error(2, "unexpected character '$c0' after spaces in name", $line);

				// name acquisition
				} elseif (($nname == 0 && preg_match('/[a-zA-Z_\.\x7f-\xff]/', $c0)) || ($nname == 1 && preg_match('/[\[\]\'\/a-zA-Z0-9_\.\x7f-\xff]/', $c0))) {
					if ($nameinvalue == 1) {
						$cvalue .= $c0;
						$nvalue = 1;
					} else {
						$cname .= $c0;
						$nname = 1;
					}

				// absolute path at the beginning of name acquisition
				} elseif ($c0 == '/' && $c1 == '/' && $nname == 0) {
					$cname = '//';
					++$i;

				// error in name acquisition
				} else {
					$this->error(2, "unexpected character '$c0' in name", $line);
				}

			// end of closing tag
			} elseif ($mode == _ETS_CLOSING_TAG) {
				if ($c0 == '}') {
					$this->store_text($elts, $i, $ptype, $ntext, $ctext);
					return $elts;
				} elseif (!$this->is_space($c0)) {
					$this->error(2, "unexpected character '$c0' in closing tag", $line);
				}

			// value acquisition
			} elseif ($mode == _ETS_VALUE) {

				// end of value acquisition
				if ($c0 == '}' && $nvalue == 1 && ($quotetype == 0 || $nspace == 1 || $nspace == 2)) {

					if ($nametype == _ETS_SET) {
						++$i;
						$this->store_node($elts, _ETS_SETVAL, $i, $line, $cname, $cvalue, $ncontent, $content);

					} elseif ($nametype == _ETS_MIS) {
						++$i;
						$this->store_node($elts, _ETS_MISVAL, $i, $line, $cname, $cvalue, $ncontent, $content);

					} elseif ($nametype == _ETS_WHENVAL) {
						++$i;
						$elts['when'][_ETS_WHENVAL . ':' . $i . '::' . $cvalue] = $this->parse(_ETS_WHENVAL, $i, $line, $ncontent, $content);

					} elseif ($nametype == _ETS_INCLUDE) {
						++$i;
						if ($ptype == _ETS_ROOT) {
							$filename = $this->filename;
							$masktree = $this->parse_file($cvalue);
							$this->filename = $filename;
							if (!isset($masktree)) {
								$this->error(5, $cvalue, $line, _ETS_INCLUDE);
							}
							$this->masktree = array_merge($this->masktree, $masktree);
						} else {
							if (!file_exists($cvalue)) {
								$this->error(5, $cvalue, $line, _ETS_INCLUDE);
							}
							$this->store_leaf($elts, _ETS_INCLUDE, $i, '', $cvalue);
						}
					} elseif ($nametype == _ETS_INSERT) {
						if (!file_exists($cvalue)) {
							$this->error(5, $cvalue, $line, _ETS_INSERT);
						}
						$this->store_leaf($elts, _ETS_INSERT, $i, '', $cvalue);
					}

					$mode = _ETS_DATA;

				// no more character after space for single quoted string
				} elseif ($c0 == '\'' && $quotetype == 1 && $nspace == 0) {
					$nspace = 2;

				// no more character after space for double quoted string
				} elseif ($c0 == '"' && $quotetype == 2 && $nspace == 0) {
					$nspace = 2;

				// space in value acquisition
				} elseif ($this->is_space($c0)) {
					if ($nvalue == 0 && $quotetype == 0) { // no value without quote
						$this->error(2, "unexpected space at the beginning of a value", $line);
					} else { // value found or with quotes
						if ($quotetype == 0) { // no quote
							$nspace = 1;
						} else { // with quotes
							if ($nspace == 2) { // after quotes
								$nspace = 1;
							} else {			// in quotes
								$cvalue .= $c0;
								$nvalue = 1;
							}
						}
					}

				// escape } with \} in value acquisition without quote
				} elseif ($c0 == '\\' && $c1 == '}' && $nspace == 0) {
					$cvalue .= '}';
					$nvalue = 1;
					++$i;

				// espace ' with \' in value acquisition for single quoted string
				} elseif ($c0 == '\\' && $c1 == '\'' && $quotetype == 1 && $nspace == 0) {
					$cvalue .= '\'';
					$nvalue = 1;
					++$i;

				// espace " with \" in value acquisition for single quoted string
				} elseif ($c0 == '\\' && $c1 == '"' && $quotetype == 2 && $nspace == 0) {
					$cvalue .= '"';
					$nvalue = 1;
					++$i;

				// value acquisition
				} elseif ($nspace == 0) {
					$cvalue .= $c0;
					$nvalue = 1;

				// error in value acquisition
				} else {
					$this->error(2, "unexpected character '$c0' in value", $line);
				}

			// comment
			} elseif ($mode == _ETS_COMMENT) {

				// nested
				if ($c0 == '{' && $c1 == '*') {
					++$i;
					++$nspecial;

				// end
				} elseif ($c0 == '*' && $c1 == '}') {
					++$i;
					--$nspecial;

					// last end
					if ($nspecial == 0) {
						$mode = _ETS_DATA;
					}
				}

			// cdata
			} elseif ($mode == _ETS_CDATA) {

				// nested
				if ($c0 == '{' && $c1 == '#') {
					++$i;
					++$nspecial;

				// end
				} elseif ($c0 == '#' && $c1 == '}') {
					++$i;
					--$nspecial;

					// last end
					if ($nspecial == 0) {
						$mode = _ETS_DATA;
					}

				// text acquisition
				} else {
					$ctext .= $c0;
					$ntext = 1;
				}
			}

		}

		// errors
		if ($mode & _ETS_GROUP0) {
			$this->error(3, '', $saveline, $mode);
		}

		if ($ptype != _ETS_ROOT) {
			$this->error(4, '', $saveline, $ptype);
		}

		return $elts;
	}

    /**
     * Read a file and return its content
     */
	function read_file()
	{
		$content = NULL;
		$this->filename = trim($this->filename);
		if ($handle = @fopen($this->filename, 'rb')) {
			$size = @filesize($this->filename);
			$content = @fread($handle, $size);
			fclose($handle);
		}
		return $content;
	}

    /**
     * Parse a file and return its template tree
     */
    function parse_file($filename)
    {
		$this->filename = $filename;
		$content = $this->read_file();
		return isset($content) ? $this->parse(_ETS_ROOT, $i = 0, $line = 1, strlen($content), $content) : NULL;
	}

    /**
     * Read files then parse their content to build a template tree
     */
	function parse_files($filenames)
	{
		// Construct an array of file names
		if (!is_array($filenames)) {
			$filenames = explode(',', $filenames);
		}

		// Parse each file
		foreach ($filenames as $filename) {
			$masktree = $this->parse_file($filename);
			if (!isset($masktree)) {
				$this->error(5, $this->filename);
			}
			$this->masktree = array_merge($this->masktree, $masktree);
		}
	}


	/*****   M A T C H I N G   *****/

    /**
     * Retrieve the value of a string representation of a variable
     */
	function get_value($parent, $varname)
	{
		if (isset($parent->$varname)) {
			return $parent->$varname;
		} else {
			$elements = explode('[', $varname);
			if (count($elements) == 1) {
				return NULL;
			} else {
				$vartest = $parent;
				foreach($elements as $elementid => $element) {
					if ($elementid == 0) {
						$vartest = $parent->$element;
						if (!isset($vartest)) {
							return NULL;
						}
					} else {
						$index = substr($element, 0, -1);
						if ($index == '_first') {
							$index = 0;
						} elseif ($index == '_last') {
							$index = count($vartest) - 1;
						}
						if (!isset($vartest[$index])) {
							return NULL;
						} else {
							$vartest = $vartest[$index];
						}
					}
				}
			}
			return $vartest;
		}
	}

	/**
	 * Add system variables to an object
	 */
	function add_system_var(&$datatree, $index, $last, $key)
	{
		$datatree->_key = $key;
		$datatree->_index = $index;
		$datatree->_rank = $index + 1;
		$datatree->_odd = $datatree->_not_even = (1 == $datatree->_rank % 2);
		$datatree->_even = $datatree->_not_odd = (0 == $datatree->_rank % 2);
		$datatree->_first = (0 == $index);
		$datatree->_middle = !$datatree->_first && !$last;
		$datatree->_last = $last;
		$datatree->_not_first = !$datatree->_first;
		$datatree->_not_last = !$last;
		$datatree->_not_middle = !$datatree->_middle;
	}

    /**
     * Excerpt info defined in the index of each node of the template tree
     */
	function parse_info($info)
	{
		$elements = explode(':', $info);
		$count = count($elements);
		if ($count > 4) {
			for ($i = 4; $i < $count; ++$i) {
				$elements[3] .= ':' . $elements[$i];
			}
		} else {
			$elements = array_pad($elements, 4, '');
		}
		return array($elements[0], $elements[2], $elements[3]);
	}

    /**
     * Recursively match the template tree with the data tree
     */
	function build_mask($datatree, $masktree, $direction = _ETS_FORWARD, $index = -1, $last = FALSE, $key = '', $incode = FALSE)
	{
		$built = array();

		// array
		if (isset($datatree) && is_array($datatree) && count($datatree) > 0) {
			$lindex = 0;
			$count = count($datatree) - 1; // remove parent element
			foreach($datatree as $dk => $dv) {
				if (!is_scalar($dv) && $dk !== '_parent') {
					if (is_object($dv)) {
						$dv->_parent = &$datatree['_parent'];
					} elseif (is_array($dv)) {
						$dv['_parent'] = &$datatree['_parent'];
					}
					$built[] = $this->build_mask($dv, $masktree, _ETS_FORWARD, $lindex, ($count == $lindex + 1), $dk);
				}
				++$lindex;
			}
			return implode('', $built);
		}

		// define system variables
		if (is_object($datatree) && $index > -1 && !isset($datatree->_key)) {
			$this->add_system_var($datatree, $index, $last, $key);
		}

		// loop through each child template
		foreach($masktree as $maskinfo => $child) {

			// retrieve info from index
			list($masktype, $maskname, $maskvalue) = $this->parse_info($maskinfo);

			switch ($masktype) {

				// content data element
				case _ETS_TEXT:
					$built[] = $child;
					break;

				// php element
				case _ETS_PHP:
					$return = NULL;
					@eval('$return=' . $this->build_mask($datatree, $child, _ETS_FORWARD, -1, FALSE, '', TRUE) . ';');
					if (isset($return)) {
						$built[] = $return;
					}
					break;

				// const element
				case _ETS_CONST:
					if (isset($this->masktree[$maskname])) {
						$built[] = $this->build_mask($datatree, $this->masktree[$maskname]);
					}
					break;

				// call element
				case _ETS_CALL:
					if (isset($this->masktree[$maskname])) {
						$argdatatree = $datatree;
						foreach ($child as $arginfo => $argchild) {
							list($argtype, $argname, $argvalue) = $this->parse_info($arginfo);
							$argdatatree->$argname = $this->build_mask($datatree, $argchild);
						}
						$built[] = $this->build_mask($argdatatree, $this->masktree[$maskname]);
					}
					break;

				// include element
				case _ETS_INCLUDE:
					$this->masktree = array_merge($this->masktree, $this->parse_file($maskvalue));
					break;

				// insert element
				case _ETS_INSERT:
					$this->filename = $maskvalue;
					$built[] = $this->read_file();
					break;

				// other types of element
				default:
					// retrieve value
					$currentdata = $this->get_value($datatree, $maskname);

					// define data type
					if ($maskname == '//') {
						$datatype = _ETS_FROM_ROOT;
						$root = $this->datatree;
						if ($direction == _ETS_FORWARD) {
							if (is_array($root)) {
								$root['_parent'] = &$datatree;

							} elseif (is_object($root)) {
								$root->_parent = &$datatree;
							}
						}

					} elseif ($maskname == '..') {
						$datatype = _ETS_PARENT;

					} elseif (isset($currentdata)) {
						if (is_scalar($currentdata)) {
							if ($currentdata === FALSE && !$incode) {
								$datatype = _ETS_MISSING;

							} elseif ($currentdata === '' && !$incode) {
								$datatype = _ETS_MISSING;

							} else {
								$datatype = _ETS_SCALAR;
							}

						} elseif (is_object($currentdata) && count(get_object_vars($currentdata)) > 0) {
							$datatype = _ETS_COMPLEX;
							if ($direction == _ETS_FORWARD) {
								$currentdata->_parent = &$datatree;
							}

						} elseif (is_array($currentdata) && count($currentdata) > 0) {
							$datatype = _ETS_COMPLEX;
							if ($direction == _ETS_FORWARD) {
								$currentdata['_parent'] = &$datatree;
							}

						} else {
							$datatype = _ETS_MISSING;
						}

					} else {
						$datatype = _ETS_MISSING;
					}

					switch ($masktype) {

						// simple tag element
						case _ETS_TAG:
							if ($datatype == _ETS_SCALAR && isset($this->masktree[$maskname])) {
								$built[] = $this->build_mask($datatree, $this->masktree[$maskname]);
							} elseif ($datatype == _ETS_SCALAR) {
								if ($incode) {
									if ($currentdata === TRUE) {
										$built[] = 'TRUE';
									} elseif ($currentdata === FALSE) {
										$built[] = 'FALSE';
									} elseif (is_string($currentdata)) {
										$built[] = '"' . addcslashes($currentdata, "\0..\31\"") . '"';
									} else {
										$built[] = $currentdata;
									}

								} else {
									$built[] = $currentdata;
								}
							} elseif ($datatype == _ETS_COMPLEX && isset($this->masktree[$maskname])) {
								$built[] = $this->build_mask($currentdata, $this->masktree[$maskname]);
							} elseif ($datatype == _ETS_MISSING && $incode) {
								$built[] = 'NULL';
							}
							break;

						// alternate tag element
						case _ETS_ALT_TAG:
							if ($datatype == _ETS_SCALAR && isset($this->masktree[$maskvalue])) {
								$built[] = $this->build_mask($datatree, $this->masktree[$maskname]);

							} elseif ($datatype == _ETS_COMPLEX && isset($this->masktree[$maskvalue])) {
								$built[] = $this->build_mask($currentdata, $this->masktree[$maskvalue]);

							} elseif ($datatype == _ETS_SCALAR) {
								$built[] = $currentdata;
							}
							break;

						// template element
						case _ETS_TEMPLATE:
							if ($datatype == _ETS_SCALAR) {
								$built[] = $this->build_mask($datatree, $child);

							} elseif ($datatype == _ETS_COMPLEX) {
								$built[] = $this->build_mask($currentdata, $child, _ETS_FORWARD, $index, $last, $key, $incode);

							} elseif ($datatype == _ETS_PARENT) {
								if (is_array($datatree)) {
									$built[] = $this->build_mask($datatree['_parent'], $child, _ETS_BACKWARD, $index, $last, $key, $incode);
								} elseif (is_object($datatree)) {
									$built[] = $this->build_mask($datatree->_parent, $child, _ETS_BACKWARD, $index, $last, $key, $incode);
								}

							} elseif ($datatype == _ETS_FROM_ROOT) {
								$built[] = $this->build_mask($root, $child, _ETS_FORWARD, $index, $last, $key, $incode);
							}
							break;

						// if element
						case _ETS_IF:
							$test = $this->build_mask($datatree, $child['test'], _ETS_FORWARD, -1, FALSE, '', TRUE);
							$return = NULL;
							@eval('$return=' . $test . ';');
							if ($return === TRUE) {
								$built[] = $this->build_mask($datatree, $child['true']);
							}
							break;

						// repeat element
						case _ETS_REPEAT:
							$test = $this->build_mask($datatree, $child['value'], _ETS_FORWARD, -1, FALSE, '', TRUE);
							$return = NULL;
							@eval('$return=(int)(' . $test . ');');
							for ($i = 0; $i < $return; ++$i) {
								$built[] = $this->build_mask($datatree, $child['repeat']);
							}
							break;

						// choose element
						case _ETS_CHOOSE:
							$notfound = TRUE;
							if (isset($child['when'])) {
								foreach($child['when'] as $grandchild)  {
									$test = $this->build_mask($datatree, $grandchild['test'], _ETS_FORWARD, -1, FALSE, '', TRUE);
									$return = NULL;
									@eval('$return=' . $test . ';');
									if ($return === TRUE) {
										$notfound = FALSE;
										$built[] = $this->build_mask($datatree, $grandchild['true']);
										break;
									}
								}
							}
							if ($notfound && isset($child['else'])) {
								$built[] = $this->build_mask($datatree, $child['else']);
							}
							break;

						// choose variable element
						case _ETS_CHOOSEVAR:
							if ($datatype == _ETS_SCALAR) {
								$notfound = TRUE;
								if (isset($child['when'])) {
									foreach($child['when'] as $gcmaskinfo => $grandchild)  {
										list($gcmasktype, $gcmaskname, $gcmaskvalue) = $this->parse_info($gcmaskinfo);
										if ($currentdata == $gcmaskvalue) {
											$built[] = $this->build_mask($datatree, $grandchild);
											$notfound = FALSE;
										}
									}
								}
								if ($notfound && isset($child['else'])) {
									$built[] = $this->build_mask($datatree, $child['else']);
								}
							}
							break;

						// set element
						case _ETS_SET:
							if ($datatype != _ETS_MISSING) {
								$built[] = $this->build_mask($datatree, $child);
							}
							break;

						// mis element
						case _ETS_MIS:
							if ($datatype == _ETS_MISSING) {
								$built[] = $this->build_mask($datatree, $child);
							}
							break;

						// set val element
						case _ETS_SETVAL:
							if ($datatype == _ETS_SCALAR) {
								if ($currentdata == $maskvalue) {
									$built[] = $this->build_mask($datatree, $child);
								}
							}
							break;

						// mis val element
						case _ETS_MISVAL:
							if ($datatype == _ETS_MISSING || ($datatype == _ETS_SCALAR && $currentdata != $maskvalue)) {
								$built[] = $this->build_mask($datatree, $child);
							}
							break;

						// mis mask element
						case _ETS_MIS_TEMPLATE:
							if ($datatype == _ETS_MISSING || $datatype == _ETS_COMPLEX) {
								$built[] = $this->build_mask($currentdata, $child);
							} elseif ($datatype == _ETS_PARENT) {
								if (is_array($datatree)) {
									$built[] = $this->build_mask($datatree['_parent'], $child, _ETS_BACKWARD);
								} elseif (is_object($datatree)) {
									$built[] = $this->build_mask($datatree->_parent, $child, _ETS_BACKWARD);
								}
							}
							break;
					}
					break;
			}
		}

		// done
		return implode('', $built);
	}


	/*****   I N T E R F A C E   *****/

    /**
     * Build the result
     */
	function build_all($entry)
	{
		if (!isset($this->masktree[$entry])) {
			return NULL;
		}

		if (is_array($this->datatree)) {
			$this->datatree['_parent'] = NULL;
		} elseif (is_object($this->datatree)) {
			$this->datatree->_parent = NULL;
		}

		$built = $this->build_mask($this->datatree, $this->masktree[$entry]);

		switch ($this->reduce) {
			case _ETS_REDUCE_NULL:
			case _ETS_REDUCE_OFF:
				return $built;
			case _ETS_REDUCE_SPACES:
				return preg_replace('/(\r\n|\r|\n)+/sm', "\n", preg_replace('/[ \t]*?(\r\n|\r|\n)+[\t ]*/sm', "\n", $built));
			case _ETS_REDUCE_ALL:
				return preg_replace('/[ \t]*?(\r\n|\r|\n)+[\t ]*/sm', '', $built);
		}
	}

    /**
     * Contructor : store the data tree then build the template tree
     */
	function _ets($datatree, $filenames)
	{
		$this->datatree = $datatree;
		$this->parse_files($filenames);
	}
}

/**
 * Return a build template
 */
function sprintt($datatree, $filenames, $entry = 'main')
{
	$ets = new _ets($datatree, $filenames);
	return $ets->build_all($entry);
}

/**
 * Print out a built template
 */
function printt($datatree, $filenames, $entry = 'main')
{
	$ets = new _ets($datatree, $filenames);
	echo $ets->build_all($entry);
}

?>
