function bbcode(f, ta, v)
 {
 if (document.selection) // for IE
   {
    var str = document.selection.createRange().text;
    document.forms[f].elements[ta].focus();
    var sel = document.selection.createRange();
    sel.text = "[" + v + "]" + str + "[/" + v + "]";
    return;
   }
  else if ((typeof document.forms[f].elements[ta].selectionStart) != 'undefined') // for Mozilla
   {
    var txtarea = document.forms[f].elements[ta];
    var selLength = txtarea.textLength;
    var selStart = txtarea.selectionStart;
    var selEnd = txtarea.selectionEnd;
    var oldScrollTop = txtarea.scrollTop;
    var s1 = (txtarea.value).substring(0,selStart);
    var s2 = (txtarea.value).substring(selStart, selEnd);
    var s3 = (txtarea.value).substring(selEnd, selLength);
    txtarea.value = s1 + '[' + v + ']' + s2 + '[/' + v + ']' + s3;
    txtarea.selectionStart = s1.length;
    txtarea.selectionEnd = s1.length + 5 + s2.length + v.length * 2;
    txtarea.scrollTop = oldScrollTop;
    txtarea.focus();
    return;
   }
  else input('[' + v + '][/' + v + '] ');
 }

function input(what)
 {
  if (document.forms[f].elements[ta].createTextRange)
   {
    document.forms[f].elements[ta].focus();
    document.selection.createRange().duplicate().text = what;
   }
  else if ((typeof document.forms[f].elements[ta].selectionStart) != 'undefined') // für Mozilla
   {
    var tarea = document.forms[f].elements[ta];
    var selEnd = tarea.selectionEnd;
    var txtLen = tarea.value.length;
    var txtbefore = tarea.value.substring(0,selEnd);
    var txtafter =  tarea.value.substring(selEnd, txtLen);
    var oldScrollTop = tarea.scrollTop;
    tarea.value = txtbefore + what + txtafter;
    tarea.selectionStart = txtbefore.length + what.length;
    tarea.selectionEnd = txtbefore.length + what.length;
    tarea.scrollTop = oldScrollTop;
    tarea.focus();
   }
  else
   {
    document.forms[f].elements[ta].value += what;
    document.forms[f].elements[ta].focus();
   }
 }

function insert_link(f, ta)
 {
 if (document.selection) // for IE
   {
    var str = document.selection.createRange().text;
    document.forms[f].elements[ta].focus();
    var sel = document.selection.createRange();
    sel.text = "[link=" + str + "]Link[/link]";
    return;
   }
  else if ((typeof document.forms[f].elements[ta].selectionStart) != 'undefined') // for Mozilla
   {
    var txtarea = document.forms[f].elements[ta];
    var selLength = txtarea.textLength;
    var selStart = txtarea.selectionStart;
    var selEnd = txtarea.selectionEnd;
    var oldScrollTop = txtarea.scrollTop;
    var s1 = (txtarea.value).substring(0,selStart);
    var s2 = (txtarea.value).substring(selStart, selEnd)
    var s3 = (txtarea.value).substring(selEnd, selLength);
    txtarea.value = s1 + '[link=' + s2 + ']Link[/link]' + s3;
    txtarea.selectionStart = s1.length;
    txtarea.selectionEnd = s1.length + 18 + s2.length;
    txtarea.scrollTop = oldScrollTop;
    txtarea.focus();
    return;
   }
  else input('[link=]Link[/link] ');
 }

function clear()
 {
  document.forms[f].elements[ta].value = "";
 }