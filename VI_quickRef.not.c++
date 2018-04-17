//***************************************************************************************
//******* BLOCK 1 - The Basics **********************************************************
//***************************************************************************************
Insert Mode:
i  Jump into INSERT mode at a point just before the cursor
I  Jump into INSERT mode at the START of the line
a  Jump into insert mode at a point just AFTER the cursor
A  Jump into insert mode AFTER the last char in the line
o  Create a new line after the current one and jump into insert
O  Create a new line before the current one and jump into insert
esc  leave insert mode  (or any mode for that matter)


Be not in insert mode unless you are creating original text.


Basic Movement:  single character left/right up/down
Left      Down        Up       Right 
  h        j           k          l
  <        v           ^          >


Fast Movement:  
e (for end?) ~= w (word)   jump to the next word (most puncutation and all white space is a delimiter)
E (for END?) ~= W (WORD)   jump to the next WORD (only white space is a delimeter)
b  (back) by word
B  (back by WORD)
0  (THE beginning)
^ (non-whitespace beginnning)
$ (THE end)
f (inline character find)     
F (inline character find backwards)     
; repeats last inline find
, repeats last inline find in reverse
% (find corresponding paranthetical (good for coding!))
1G  go to line 1 (start of document)
G  go to last line (end of document)
#G go to line #
ctrl+u  page UP
ctrl+d  page DOWN
/  do a regex search
n  repeat previous full document search
N  repeat previous full document search in reverse


//***************************************************************************************
//******* BLOCK 2 - Editting Essentials *************************************************
//***************************************************************************************

Really good commonly used stuff:
/  do a regex search (n repeats search forwards N repeats search backwards)
x   delete a single character (it will go into your yank buffer)
.  repeat last performed action
u  undo
ctrl+r redo
dd  delete entire line
D = d$   delete the rest of the line starting from cursor
yy = Y  yank entire line
y$  yank the rest of the line starting from cursor
p   put most recently yanked (or deleted) text AFTER cursor
P   put most recently yanked (or deleted) text BEFORE cursor
J   join lines
c   change (delete an amount of text specified by the fed in move
            operation and drop into insert mode) ***see Examples below

c is especially useful in conjunction with . because the . will repeat both the text removal and text insertion

//***************************************************************************************
//******* BLOCK 3 - Lets Get Repeatable *************************************************
//***************************************************************************************

Rare but potentially extremely cool stuff
v Jump into visual mode to highlight stuff
~ Toggle the capitalization of the current character
  visual mode:
    ~ toggle case of selection  
    U force selection to UPPER  
    u force selection to lower
r replace a single character
R jump into REPLACE mode to overtype
ctrl+a  increment (many windows VIM installs use default windows shortcuts so this may not be mapped at all)
ctrl+x  decrement
movement operator i/a ("[<{     i.e.    i( = inside ()   a[ = around []          " //this quote included purely for color display purposes

q<lowecase-letter>  enter recording mode and record all keystrokes into a register named <lowercase_letter> (q again to exit recording mode)
  example:  qjnddq   will record ndd into a register named j 
  (playing this macro results in repeating the last search and then deleting the line at the newly jumped to search term)

q<uppercase-letter> enter recording mode and APPEND all keystrokes into a register named (lowercase version of)<uppercase-letter> (q again to exit recording mode)
  example:  qKj$q    will record j$ into a register named k
  (the k register will now do what it used to do and then move down a line and move to the end of the line)

@<letter>   playback the contents of the register named <letter>   (i.e. execute macro named <letter>)
  example:  @j   or @k    will execute all of the actions corresponding to the recorded keystrokes in register j or k
<count>@<letter>    execute macro <letter> <count> number of times
  exampled:  50@j  will perform the keystrokes recorded into j 50 times  
  (NOTE macro playback will stop on an error, e.g. if your macro includes j for 'go down 1 line' as one of the recorded keystrokes, 
        but you are currently on the last line of the file, then playback will stop when j fails to move down 1 line)

"<letter>  the next yank or delete command will store into a register
           named <letter>  the next put command will put the contents
           of register                                                          " //this quote included purely for color display purposes
example:  "ayy    will yank the current line into register a                    " //this quote included purely for color display purposes
example:  "ap    will put the contents of a into the file following normal put rules " //this quote included purely for color display purposes

m<letter> mark the document with a marker name <letter>
'<letter> go to marker named <letter>
'`  (a single quote followed by a back-tick)  jump to previous file location


//***************************************************************************************
//******* BLOCK 4 - Who is your regex and what does he do? ******************************
//***************************************************************************************

/  do a regex search (n repeats search forwards N repeats search backwards)
default VI regex search:
case sensitive - (you can always put \C to force Case sensitive or \c to force cASe insensitivity)
:set ignorecase  or :set noignorecase to turn on or off the ignore case option permanently 
     (put in vimrc file to make it really permanent)

Every component of a regex serves 1 of 3 purposes:
1.  Anchor (represents a line location and forces the matched pattern to be attached to that location)
2.  Character - the desired character to be matched
3.  Numerical Counter (Repetition) - the number of times the preceding character can be matched

Anchors
^            Beginning of line
$            End of line

Character Classes
a            a
B            B
3            3
.            Any character
\.           .
[a-z]        Any lowercase letter
[A-Za-z]     Any letter
[Aa]         A or a
[BbAa]       A, a, B, or b
[abcdABCD]   The first 4 letters of the alphabet regardless of case
[5-9]        Any of the numbers 5 through 9
[^x]         Anything except for a lowercase x

Numerical Counters (note the use of escape characters here is usage style for the default VIM regex mode)
                   (more typical regex patterns would not require escaping for ?, +, {}, or ()   )
\?           0 or 1 times
\+           1 or more times
*            0 or more times
\{n,m}       Any number betweeen n and m times

example VIM regex searches:
/cat           look for any instance of cat   will not matche on Cat or CAT, but will match on (the cat part of) location or acat
/[Cc]at        matches any instance of Cat or cat
/^[Cc]at       matches instances of Cat or cat that appear at the BEGINNING of a line
/\ccat         matches any instance of any case of cat:  cat, CAT, cAt, CaT, etc
/cat$          matches instances of cat that occur at the end of a line; the previous line would have no matches but this one would match because cat
/\c^cat$       matches any case of cat, but only if it is the only thing in the line (it is anchored to the beginning AND end)
/[Cc]a\+t*     matches any instance of Cat or cat, but also matches Ca, ca, Caa, caaa, caaattttt, caaaaaaaaat, Caatttttttttttt, etc
/c.t           matches cat, cut, cot, but also matches cet, cit, cbt, cct, czt, c+t, c!, c t, c9t, etc
/c.\{0,2}t     matches ct, cat, cut, cot, coat, ciet, c*!t, cult, c+=t, c^t, etc

the same examples broken out into their types:
/cat           contains three very specific character (char) classes:   [c]  [a]   [t]
/[Cc]at        contains three  very specific char classes:   [Cc]  [a]   [t]
/^[Cc]at       contains 1 anchor and the previous 3 char classes:   ^   [Cc]   [a]   [t]
/\ccat         contains the case insensitivity switch and 3 char classes:   \c   [c]  [a]  [t]
/cat$          contains 3 char classes and 1 anchor:  [c]  [a]  [t]  $
/\c^cat$       contains the case insensitivity switch, 2 anchors and 3 char classes:   \c  ^  [c]  [a]  [t]  $
/[Cc]a\+t*     contains 3 char classes and 2 numerical counters:  [Cc]  [a]  +  [t]  *
    (the + modifies how many occurrences of [a] there can be and the * modifies [t])
	 (note most regex libraries don't force you to escape the +, that is a VIM specialty)
/c.t           contains 3 char classes and 1 numerical counter:  [c]  [-A-Za-z0-9~!@#$%^&*()_+-=....]   [t]
/c.\{0,2}t     contains 3 char classes and 1 numerical counter:  [c]  .  {0,2}  [t]
    (the {0,2} modifies the dot, so anywhere from 0 to 2 occurrences of any character at all)

//***************************************************************************************
//******* BLOCK 5 - The Elusive VIMRC file ... ******************************************
//***************************************************************************************
1.  Pick a leader. 
let mapleader = " "
(note the above is what I use, spacebar, the default is \ I believe)
2.  Add lines to quickly edit and source your vimrc (warn about over sourcing)
:nnoremap <leader>ev :vsplit $MYVIMRC<cr>
:nnoremap <leader>zv :source $MYVIMRC<cr>
3.  Add lines to quickly edit your vim reference file
:nnoremap <leader>qv :vsplit $THIS_FILE<cr>
4.  map command:  ALWAYS use noremap instead of map... recursion has no place here
5.  options that preface the noremap command:  (nothing)-nvo   i -insert  v-visual o-operator n-normal
6.  Comments inside vimrc file are lines that start with "

