if v:lang =~ "utf8$" || v:lang =~ "UTF-8$"
    set fileencodings=ucs-bom,utf-8,lat1
endif

"random settings someone else had put there
set nocompatible " Use Vim defaults
set bs=indent,eol,start "allow backspacing over everything in insert mode
set ai "set auto indent on
set backup "keep a backup file
set viminfo='20,\"50 "read/write a .viminfo file, don't store more than 50 lines of registers
set history=150  "keep 50 lines of command line history
set ruler  "show the cursor position all the time
set hlsearch

"my settings
"make the F2 key toggle (and show) the paste mode 
"(needed to correct auto-indenting)
nnoremap <F2> :set invpaste paste?<cr>
set pastetoggle=<F2>
"set up the F3 key to toggle word wrap on and off
nnoremap <F3> :set wrap!<cr>
"set up the F4 key to toggle line numbers on and off
nnoremap <F4> :set number!<cr>
"set up the F5 key to toggle search wrap on and off
nnoremap <F5> :set wrapscan!<cr>:set wrapscan?<cr>

"GUI settings I like
set showmode   "show what mode VI is in
set showcmd    "show the cmds being typed
set cursorline "show the current line of the cursor
set number     "show line numbers
set smartindent
set smarttab
set tabstop=4
set shiftwidth=4
set expandtab  "need to find a way to turn this off for .py files
set nrformats=hex
syntax on

:let mapleader = " "  "make the spacebar the map leader

"map increment and decrement operators to something nice and pnemonic
:nnoremap <leader>i <C-a>
:nnoremap <leader>d <C-x>
"quick toggle of different increment/decrement modes
nnoremap <leader>0 :set nrformats=hex<CR>:set nrformats?<CR>
nnoremap <leader>8 :set nrformats=octal<CR>:set nrformats?<CR>
nnoremap <leader>a :set nrformats=alpha<CR>:set nrformats?<CR>

"set faster redo
nnoremap <leader>r <C-r>

"Fast editting and sourcing of vim rc file
:nnoremap <leader>ev :vsplit /etc/vimrc<cr>
:nnoremap <leader>zv :source /etc/vimrc<cr>

"force save
"Allow saving of files as sudo when vim was not run with sudo
cnoremap w!! w !sudo tee > /dev/null %

"Make ctrl arrow keys move between file splits
:nnoremap <C-Up> :wincmd k<cr>
:nnoremap <C-Down> :wincmd j<cr>
:nnoremap <C-Left> :wincmd h<cr>
:nnoremap <C-Right> :wincmd l<cr>
"Make z+vim keys move between splits
:nnoremap zk :wincmd k<cr>
:nnoremap zj :wincmd j<cr>
:nnoremap zh :wincmd h<cr>
:nnoremap zl :wincmd l<cr>

"quick word highlight
:nnoremap <leader>w viw
"quick line highlight
:nnoremap <leader>l 0v$

"clear search highlights
:nnoremap <leader>n :noh<cr>

"jump to next capital letter (not a perfect in-line only find tho...)
:nnoremap <leader>c /[A-Z]<cr>:noh<cr>

"disable arrow keys b/c fun (note I gave up and down a different mapping for mousewheel)
":nnoremap <Up> :echo "Vim cat: >^.^<  Use k meow~"<esc>
":nnoremap <Down> :echo "Vim cat: >^.^<  Use j meow~"<esc>
:nnoremap <Left> :echo "Vim cat: >^.^<  Use h meow~"<esc>
:nnoremap <Right> :echo "Vim cat: >^.^<  Use l meow~"<esc>

"fast quoting/bracketing of current word
:nnoremap <leader>" viw<esc>bea"<esc>hbi"<esc>lel
:nnoremap <leader>' viw<esc>bea'<esc>hbi'<esc>lel
:nnoremap <leader>( viw<esc>bea)<esc>hbi(<esc>lel
:nnoremap <leader>[ viw<esc>bea]<esc>hbi[<esc>lel
:nnoremap <leader>< viw<esc>bea><esc>hbi<<esc>lel
:nnoremap <leader>{ viw<esc>bea}<esc>hbi{<esc>lel

"fast quoting/bracketing of visual selection
:vnoremap <leader>" <esc>BEa"<esc>`<i"<esc>`>2l
:vnoremap <leader>' <esc>BEa'<esc>`<i'<esc>`>2l
:vnoremap <leader>( <esc>BEa)<esc>`<i(<esc>`>2l
:vnoremap <leader>[ <esc>BEa]<esc>`<i[<esc>`>2l
:vnoremap <leader>< <esc>BEa><esc>`<i<<esc>`>2l
:vnoremap <leader>{ <esc>BEa}<esc>`<i{<esc>`>2l

" when in visual mode, use // to paste highlighted text into
" a 'literal' search (Very no magic mode)
:vnoremap // y/\V<C-R>"<CR>

"quickly jumping between xml tags (this is built in!)
"1. v+a+t   :    this will highlight the tag pair
"2. o       :    while highlighted this jumps between tag endpoints

"quickly run a macro on a visually selected block
:vnoremap @ :normal @

"make a new line w/o going into insert mode
:nnoremap <leader>o o<esc>
:nnoremap <leader>O O<esc>


"remap arrow keys (assists mouse scroll wheel)
:nnoremap <Up> <C-y>
:nnoremap <Down> <C-e>

"
"File navigation
"Toggle between last opened file
:nnoremap <leader><TAB> <C-^>
"Create a go FORWARDS or BACKWARDS or to ORIGINAL file
:nnoremap <leader>F :bnext<cr>
:nnoremap <leader>b :bprev<cr>
:nnoremap <leader>1 :b 1<cr>
"remember to jump to a selected file, just use built in gf cmd


"------------------------------------------------------------------------------
"Fun with highlights
"clear currently up special highlight (:match based) effects
:nnoremap <leader>m :match<cr>:echo " "<cr>

"define a blue highlight function and command pair
function! ColorItBlueHighlight(pttrn)
	echo a:pttrn
	execute 'match DiffDelete /' . a:pttrn . '/'
endfunction

:command! -nargs=1 Cbh call ColorItBlueHighlight(<f-args>)
"------------------------------------------------------------------------------



"------------------------------------------------------------------------------
"Regex In-line Find
"Execute a funciton that will act just like an in-line character find,
"except it will use a regex instead of a character and you will need to 
"fiddle with the current wrapscan setting to make it not go to next line
function! FindRegexInLine(pttrn)
  let @/ = '\%' . line(".") . 'l' . a:pttrn
  execute 'normal! n'
endfunction

:command! -nargs=1 Fin call FindRegexInLine(<f-args>)
:command! -nargs=1 FIn call FindRegexInLine(<f-args>)

:nnoremap <leader>f :Fin
"------------------------------------------------------------------------------


"------------------------------------------------------------------------------
"Searching for lines NOT containing something 
"(need a function / command pair again)
function! SearchInvert(search)
	let @/ = '^\(\(.*' . a:search . '.\)\@!.\)*$'
	execute 'normal! n'
	"NOTE :noh will slightly wreck the highlighting here
endfunction

:command! -nargs=1 Not call SearchInvert(<f-args>)
"------------------------------------------------------------------------------


"------------------------------------------------------------------------------
"function and mapping pair for sending current file to a different box (linux)
function! SendToBox()
	let boxName = input('Enter BoxName:')
	execute '!scp -r ' . @% . ' ' . boxName . ':/tmp'
endfunction
:noremap <leader>xxx :call SendToBox()<cr>
"------------------------------------------------------------------------------


set diffexpr=MyDiff()
function! MyDiff()
  let opt = '-a --binary '
  if &diffopt =~ 'icase' | let opt = opt . '-i ' | endif
  if &diffopt =~ 'iwhite' | let opt = opt . '-b ' | endif
  let arg1 = v:fname_in
  if arg1 =~ ' ' | let arg1 = '"' . arg1 . '"' | endif
  let arg2 = v:fname_new
  if arg2 =~ ' ' | let arg2 = '"' . arg2 . '"' | endif
  let arg3 = v:fname_out
  if arg3 =~ ' ' | let arg3 = '"' . arg3 . '"' | endif
  let eq = ''
  if $VIMRUNTIME =~ ' '
    if &sh =~ '\<cmd'
      let cmd = '""' . $VIMRUNTIME . '\diff"'
      let eq = '"'
    else
      let cmd = substitute($VIMRUNTIME, ' ', '" ', '') . '\diff"'
    endif
  else
    let cmd = $VIMRUNTIME . '\diff'
  endif
  silent execute '!' . cmd . ' ' . opt . arg1 . ' ' . arg2 . ' > ' . arg3 . eq
endfunction

