
"  --------------  My Vim --------------
"  VERSION 1.0


" Set Linux Debian Desktop
runtime! debian.vim

" Not complete with Vi Mode
set nocompatible

set regexpengine=1

" History
set history=9888

" @ Replace <leader> key map to <space>
let mapleader=" "


filetype off

call plug#begin('~/.vim/bundle/')

Plug 'vim-airline/vim-airline'
Plug 'vim-airline/vim-airline-themes'

Plug 'flazz/vim-colorschemes'
Plug 'liuchengxu/space-vim-dark'
Plug 'gorodinskiy/vim-coloresque'

Plug 'majutsushi/tagbar'

Plug 'scrooloose/nerdtree'
Plug 'Xuyuanp/nerdtree-git-plugin'

Plug 'ctrlpvim/ctrlp.vim'
Plug 'mileszs/ack.vim'
Plug 'junegunn/fzf', { 'dir': '~/.fzf', 'do': './install --all' }

Plug 'scrooloose/syntastic'
"Plug 'fatih/vim-go'
Plug 'kh3phr3n/python-syntax'
Plug 'pangloss/vim-javascript'
"Plug 'groenewege/vim-less'
"Plug 'lepture/vim-velocity'
"Plug 'cakebaker/scss-syntax.vim'
"Plug 'rstacruz/vim-ultisnips-css'
Plug 'hail2u/vim-css3-syntax'
"Plug 'leafgarland/typescript-vim'
"Plug 'jason0x43/vim-js-indent'
"Plug 'HerringtonDarkholme/yats.vim'
"Plug 'Quramy/tsuquyomi'
"Plug 'mustache/vim-mustache-handlebars'                                                                                                                                                                                               
"Plug 'mxw/vim-jsx'
Plug 'othree/xml.vim'
Plug 'othree/html5.vim'
"Plug 'othree/yajs.vim'
"Plug 'maksimr/vim-jsbeautify'
Plug 'othree/javascript-libraries-syntax.vim'
Plug 'ap/vim-css-color'
"Plug 'docunext/closetag.vim'
Plug 'elzr/vim-json'
"Plug 'bcicen/vim-jfmt' " brew install jq
"Plug 'plasticboy/vim-markdown'

Plug 'mattn/emmet-vim'
"Plug 'tpope/vim-git'
"Plug 'tpope/vim-fugitive'
"Plug 'airblade/vim-gitgutter'
"Plug 'chrisbra/vim-diff-enhanced'

Plug 'jiangmiao/auto-pairs'
"Plug 'rstacruz/sparkup', {'rtp': 'vim/'}
Plug 'Valloric/YouCompleteMe'

""时光机
"Plug 'sjl/gundo.vim'

"Plug 'terryma/vim-expand-region'
"Plug 'terryma/vim-multiple-cursors'

"Plug 'thinca/vim-quickrun'
Plug 'VundleVim/Vundle.vim'
Plug 'godlygeek/tabular'
Plug 'plasticboy/vim-markdown'

Plug 'bf4/vim-dark_eyes'
Plug 'nightsense/stellarized'

if !exists("g:gui_oni")
    Plug 'ap/vim-buftabline'
endif

call plug#end()
filetype on
filetype plugin on
filetype plugin indent on

set rtp+=~/.vim/bundle/vundle/
call vundle#rc()
" C (C插件)
Bundle 'c.vim'
" SQL 补全工具
Bundle 'SQLComplete.vim'

set rtp+=/usr/local/opt/fzf
set rtp+=~/.fzf

""Syntastic (静态语法检查)
let g:syntastic_check_on_open = 1
let g:syntastic_cpp_include_dirs = ['/usr/include/']
let g:syntastic_cpp_remove_include_errors = 1
let g:syntastic_cpp_check_header = 1
let g:syntastic_cpp_compiler = 'gcc'
let g:syntastic_cpp_compiler_options = '-std=gnu11 -stdlib=libstdc'
""c
let g:syntastic_c_compiler = 'gcc'
let g:syntastic_c_errorformat=1
let g:syntastic_c_compiler_options = '-std=gnu11'
let g:syntastic_c_config_file=1
let g:syntastic_c_include_dirs = ["includes", "headers", "/usr/include/"]

let g:syntastic_error_symbol = 'XX'
let g:syntastic_warning_symbol = '!!'
let g:syntastic_enable_balloons = 1


""code
let g:html_indent_inctags = "html,body,head,tbody"
let g:html_indent_script1 = "inc"
let g:html_indent_style1 = "inc"
let g:user_emmet_settings = {
            \ 'php'     : {
            \ 'extends' : 'html',
            \ 'filters' : 'c',
            \ },
            \ 'xml'     : {
            \ 'extends' : 'html',
            \ },
            \ 'haml'    : {
            \ 'extends' : 'html',
            \ },
            \ 'phtml'    : {
            \ 'extends' : 'html',
            \ }
            \}

let g:gitgutter_sign_column_always = 0
let g:gitgutter_max_signs = 99999
let g:pydiction_location = '~/.vim/codeComplete/py-complete-dict'
let g:pydiction_menu_height = 20
autocmd FileType python set omnifunc=pythoncomplete#Complete
let python_self_cls_highlight = 1
let g:lastplace_open_folds = 0

let g:better_whitespace_filetypes_blacklist = ['FAR', 'far_vim', 'diff', 'gitcommit', 'unite', 'qf', 'help', '.ignore', 'node_modules']

let g:lt_location_list_toggle_map = '<leader>w'
let g:lt_quickfix_list_toggle_map = '<leader>q'
let g:mustache_abbreviations = 1
let g:jsx_ext_required = 0
let g:tsuquyomi_disable_quickfix = 1
let g:prettier#autoformat = 0
let g:prettier#exec_cmd_async = 1


""auto
let g:AutoPairsLoaded = 1
if !exists('g:AutoPairs')
    let g:AutoPairs = {'(':')', '[':']', '{':'}', "'":"'", '"':'"', '`':'`'}
endif

""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
set completeopt=longest,menu
let g:ycm_confirm_extra_conf=0
let g:ycm_complete_in_comments = 1
let g:ycm_complete_in_strings = 1
let g:ycm_collect_identifiers_from_tags_files=1
let g:ycm_collect_identifiers_from_comments_and_strings = 1
let g:ycm_seed_identifiers_with_syntax=1
let g:ycm_collect_identifiers_from_tags_files = 1
let g:ycm_min_num_of_chars_for_completion=2
let g:ycm_path_to_python_interpreter='/usr/bin/python'
if !empty(glob("~/.vim/bundle/YouCompleteMe/third_party/ycmd/cpp/ycm/.ycm_extra_conf.py"))
    let g:ycm_global_ycm_extra_conf = "~/.vim/bundle/YouCompleteMe/third_party/ycmd/cpp/ycm/.ycm_extra_conf.py"
endif
let g:ycm_key_invoke_completion = '<C-Space>'
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""


"nerdtree git 
let NERDTreeWinPos='left'
let NERDChristmasTree = 1
let NERDTreeMouseMode = 2
let NERDTreeWinSize=25

let g:NERDTreeUseSimpleIndicator = 1
let g:NERDTreeDirArrows=0


""查找ctrlp
let g:ctrlp_map = '<c-p>'
let g:ctrlp_cmd = 'CtrlP'
let g:ctrlp_working_path_mode = 'ra'

let g:ctrlp_max_height = 15
let g:ctrlp_match_window_reversed = 0
let g:ctrlp_by_filename = 1
let g:ctrlp_line_prefix = '♪ '

let g:ackhighlight = 1
let g:ack_qhandler = "botright copen 15"
let g:ack_autoclose = 1
let g:ack_use_cword_for_empty_search = 1

if executable('ag')
    let g:ackprg = 'ag --vimgrep'
endif
set grepprg=ag\ --nogroup\ --nocolor
let g:ctrlp_user_command = 'ag %s -l --nocolor --hidden -g ""'
let g:ctrlp_use_caching = 0

""tagbar
"nmap <Leader>tb :TagbarToggle<CR>

let g:tagbar_ctags_bin='/usr/bin/ctags'
let g:tagbar_width=30
let g:tagbar_jsctags_bin = '/usr/local/bin/jsctags'
let g:tagbar_iconchars = ['+', '-']

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" CTags (function 跳转工具)
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

"let Tlist_Sort_Type = "name"    " 按照名称排序  
let Tlist_Use_Right_Window = 1  " 在右侧显示窗口  
let Tlist_Compart_Format = 1    " 压缩方式  
let Tlist_Exist_OnlyWindow = 1  " 如果只有一个buffer，kill窗口也kill掉buffer  
let Tlist_Ctags_Cmd='/usr/local/bin/ctags'

""let Tlist_File_Fold_Auto_Close = 0  " 不要关闭其他文件的tags  
""let Tlist_Enable_Fold_Column = 0    " 不要显示折叠树  
let Tlist_Show_One_File=1            "不同时显示多个文件的tag，只显示当前文件的
"airline
let g:airline#extensions#tabline#enabled = 1
"let g:airline#extensions#tabline#formatter = 'default'
if !exists('g:airline_symbols')
	let g:airline_symbols = {}
endif



""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" VIM Keyboard Commands
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
"新建一个标签页
map <F2> <Esc>:tabnew<CR>
map <F3> :NERDTreeToggle<CR>
imap <F3> <ESC> :NERDTreeToggle<CR>
map <C-F3> \be
nnoremap <F4> ggVG:Tab2Space<CR>
:autocmd BufRead,BufNewFile *.dot map <F5> :w<CR>:!dot -Tjpg -o %<.jpg % && eog %<.jpg  <CR><CR> && exec "redr!"
"代码格式优化化
map <F6> :call FormartSrc()<CR><CR>
""tagbar
nmap <F8> :TagbarToggle<CR>

nmap tl :Tlist<cr> 
:nmap <silent> <F9> <ESC>:Tlist<RETURN>
nnoremap <F10> :%s////g<CR>
" shift tab pages
map <F12> gg=G


"定义FormartSrc()
func FormartSrc()
    exec "w"
    if &filetype == 'c'
        exec "!astyle --style=ansi -a --suffix=none %"
    elseif &filetype == 'cpp' || &filetype == 'hpp'
        exec "r !astyle --style=ansi --one-line=keep-statements -a --suffix=none %> /dev/null 2>&1"
    elseif &filetype == 'perl'
        exec "!astyle --style=gnu --suffix=none %"
    elseif &filetype == 'py'||&filetype == 'python'
        exec "r !autopep8 -i --aggressive %"
    elseif &filetype == 'java'
        exec "!astyle --style=java --suffix=none %"
    elseif &filetype == 'jsp'
        exec "!astyle --style=gnu --suffix=none %"
    elseif &filetype == 'xml'
        exec "!astyle --style=gnu --suffix=none %"
    else
        exec "normal gg=G"
        return
    endif
    exec "e! %"
endfunc
"结束定义FormartSrc
"

" -------------- Tooling Function Binding ------------------
" Lookup HighLight Syntax Define
function! <SID>SynStack()
    echo map(synstack(line('.'),col('.')),'synIDattr(v:val, "name")')
endfunc

" Return indent (all whitespace at start of a line), converted from
" tabs to spaces if what = 1, or from spaces to tabs otherwise.
" When converting to tabs, result has no redundant spaces.
function! Indenting(indent, what, cols)
    let spccol = repeat(' ', a:cols)
    let result = substitute(a:indent, spccol, '\t', 'g')
    let result = substitute(result, ' \+\ze\t', '', 'g')
    if a:what == 1
        let result = substitute(result, '\t', spccol, 'g')
    endif
    return result
endfunction

" Convert whitespace used for indenting (before first non-whitespace).
" what = 0 (convert spaces to tabs), or 1 (convert tabs to spaces).
" cols = string with number of columns per tab, or empty to use 'tabstop'.
" The cursor position is restored, but the cursor will be in a different
" column when the number of characters in the indent of the line is changed.
function! IndentConvert(line1, line2, what, cols)
    let savepos = getpos('.')
    let cols = empty(a:cols) ? &tabstop : a:cols
    execute a:line1 . ',' . a:line2 . 's/^\s\+/\=Indenting(submatch(0), a:what, cols)/e'
    call histdel('search', -1)
    call setpos('.', savepos)
endfunction

" Space2Tab
" Tab2Space
" RetabIndent
command! -nargs=? -range=% Space2Tab call IndentConvert(<line1>,<line2>,0,<q-args>)
command! -nargs=? -range=% Tab2Space call IndentConvert(<line1>,<line2>,1,<q-args>)
command! -nargs=? -range=% RetabIndent call IndentConvert(<line1>,<line2>,&et,<q-args>)

function! VisualSelection(direction, extra_filter) range
    let l:saved_reg = @"
    execute "normal! vgvy"

    let l:pattern = escape(@", '\\/.*$^~[]')
    let l:pattern = substitute(l:pattern, "\n$", "", "")

    if a:direction == 'b'
        execute "normal ?" . l:pattern . "^M"
    elseif a:direction == 'ag'
        execute 'Ag '.l:pattern
    elseif a:direction == 'replace'
        execut  "%s" . '/'. l:pattern . '/'
    elseif a:direction == 'f'
        execute "normal /" . l:pattern . "^M"
    endif

    let @/ = l:pattern
    let @" = l:saved_reg
endfunction
" -------------- Tooling Function Ending ------------------

" Split faster
nnoremap <leader>\ :vs<CR>
nnoremap <leader>- :sp<CR>

" Fast to copy files path
nnoremap <leader>p "+gp
vnoremap <leader>p "+p
vnoremap <leader>y "+y
vnoremap <leader>d "+d
nnoremap <leader>cd :cd %:p:h<CR>
nnoremap <leader>cp :let @+=expand("%:p")<CR>:echo "Copied current file
            \ path '".expand("%:p")."' to clipboard"<CR>

" Vundle keyfire
nnoremap <leader>vi :PlugInstall<CR>
nnoremap <leader>vu :PlugUpdate<CR>

" Tabluer Format
vnoremap <leader>t :Tabularize/
vnoremap <leader>t= :Tabularize/=<CR>
vnoremap <leader>t, :Tabularize/,<CR>
vnoremap <leader>t. :Tabularize/.<CR>
vnoremap <leader>t: :Tabularize/:<CR>
vnoremap <leader>t; :Tabularize/;<CR>
vnoremap <leader>t\ :Tabularize/\|<CR>



" Incsearch
" nnoremap / /\v
" vnoremap / /\v
" Ag bind \ (backward slash) to grep shortcut
"map / <Plug>(incsearch-forward)
map ? <Plug>(incsearch-backward)
map g/ <Plug>(incsearch-stay)
map \ :Ag<SPACE>

nmap <C-f> :FZF<CR>
nmap <leader>f :norm yiw<CR>:Ack "<C-R>""
"let mapleader = ","
function! LookUpwards()
    let column_num = virtcol('.')
    let target_pattern = '\%' . column_num . 'v.'
    let target_line_num = search(target_pattern . '*\S', 'bnW')


    if !target_line_num
        return ""
    else
        return matchstr(getline(target_line_num), target_pattern)
    endif
endfunction
imap <silent> <C-Y> <C-R><C-R>=LookUpwards()<CR>


au FileType php setlocal dict+=~/.vim/dict/php_funclist.dict
au FileType css setlocal dict+=~/.vim/dict/css.dict
au FileType c setlocal dict+=~/.vim/dict/c.dict
au FileType cpp setlocal dict+=~/.vim/dict/cpp.dict
au FileType scale setlocal dict+=~/.vim/dict/scale.dict
au FileType javascript setlocal dict+=~/.vim/dict/javascript.dict
au FileType html setlocal dict+=~/.vim/dict/javascript.dict
au FileType html setlocal dict+=~/.vim/dict/css.dict
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" markdown  轻量级标记语言
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
au BufRead,BufNewFile *.{md,mdown,mkd,mkdn,markdown,mdwn}   set filetype=mkd
au BufRead,BufNewFile *.{go}   set filetype=go
au BufRead,BufNewFile *.{js}   set filetype=javascript
au BufRead,BufNewFile *.{py}   set filetype=python
au BufNewFile,BufRead *.vue set ft=html
au BufNewFile,BufRead *.ax,*.handlebar,*.mustache,*.tpl set ft=mustache
au BufNewFile,BufRead *.vm,*.stm set ft=velocity
"自动解析markdown为HTML  
"nmap md :!~/.vim/markdown.pl % > %.html <CR><CR>
"nmap fi :!firefox %.html & <CR><CR>
"nmap \ \cc
"vmap \ \cc
"


" Ignore file config
set wildignore=*.o,*.obj,*~ "stuff to ignore when tab completing
set wildignore+=*/tmp/*,*.so,*.swp,*.zip     " MacOSX/Linux
set wildignore+=*DS_Store*
set wildignore+=vendor/rails/**
set wildignore+=vendor/cache/**
set wildignore+=*.gem
set wildignore+=log/**
set wildignore+=tmp/**
set wildignore+=*.png,*.jpg,*.gif,*.webp,*.psd,*.exe,*.sketch
set wildignore+=*.so,*.swp,*.zip,*/.Trash/**,*.pdf,*.dmg,*/Library/**,*/.rbenv/**
set wildignore+=*/.nx/**,*.app,*.git,.git,.svn

let g:ctrlp_custom_ignore = '\v[\/]\.(git|hg|svn)$'
let g:ctrlp_custom_ignore = '\v\.(exe|so|dll)$'
let g:ctrlp_extensions = ['funky']

let g:lastplace_ignore = "gitcommit,gitrebase,svn,hgcommit,FAR,far_vim"
let g:lastplace_ignore_buftype = "quickfix,nofile,help,FAR,far_vim"

let NERDTreeIgnore=['\.pyc']
let g:NERDTreeShowIgnoredStatus = 1
let g:NERDTreeRespectWildIgnore=1


""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" VIM File Format & layout
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" 自动缩进为4个空格
set sw=4
" Tab 宽度为4  
set ts=4 
" 设置光标超过88列时候折行
"set tw=88 
" 不折行
set nowrap 
" 在行和段开始处使用制表符, 按下删除键直接删除4个空格
set smarttab
" 智能缩进
set smartindent
" 不在单词中间折行
set lbr 
" 自动格式化
set formatoptions=tcrqn
" 继承前一行的缩进方式，特别适用于多行注释
set autoindent
" 使用C样式的缩进
set cindent
" 制表符为4
set tabstop=4
" 统一缩进为4
set softtabstop=4
set shiftwidth=4

" 带有如下符号的单词不要被换行分割
set iskeyword+=_,$,@,%,#,-

set linespace=0

""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" VIM File Setting 
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" 编辑时将所有Tab替换成空格
set et
" 设定默认解码
set fenc=utf-8
set fencs=utf-8,usc-bom,euc-jp,gb18030,gbk,gb2312,cp936
" 在处理未保存或只读文件的时候，弹出确认
set confirm
" 侦测文件类型
filetype on
" 载入文件类型插件
filetype plugin on
" 为特定文件类型载入相关缩进文件
filetype indent on
" 使回格键（backspace）正常处理indent, eol, start等
set backspace=2
" 防止特殊符号无法正常显示
set ambiwidth=double 
" 禁止生成临时文件
set nobackup
" 不要生成swap文件，当buffer被丢弃的时候隐藏它
setlocal noswapfile
set nowritebackup
set bufhidden=hide
set dictionary+=/usr/share/dict/words
" 打开C/C++风格自动缩进，可以通过:set paste关闭，:set nopaste重新开启
set cin 

""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" VIM Search & Matching
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" 搜索时高亮显示被找到的文本
set hls
"搜索忽略大小写
set ignorecase
" 匹配括号高亮的时间（单位是十分之一秒）
set matchtime=2
"高亮被搜索的句子 nohlsearch为不高亮
set hlsearch
" 在搜索时，输入的词句的逐字符高亮
set incsearch
" 高亮显示匹配的括号
set showmatch

""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" VIM UI Config 
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" 光标移动到buffer的顶部和底部时保持3行距离
set scrolloff=3
" 不要闪烁
set noerrorbells
set novisualbell
set t_vb=
" set Undo file
set undofile
set undodir=~/.vim/undo/
set viminfo+=!
" 显示括号配对情况
set sm 
" 在被分割的窗口间显示空白，便于阅读
set fillchars=vert:\ ,stl:\ ,stlnc:\
" 打开上色功能, 语法高亮
syntax on 
"高亮光标所在行
set cul 
"set cuc
" 不要图形按钮  
set go=   
" 用浅色高亮当前行
autocmd InsertEnter * se cul 
" 输入的命令显示出来，看的清楚些    
set showcmd          
" 允许折叠      
"set foldenable  
" 手动折叠       
set foldmethod=manual   
" 显示中文帮助
if version >= 603
    set helplang=cn
    set encoding=utf-8
endif
" 使用空格代替制表符
set expandtab
"将tab替换为空格
nmap tt :%s/\t/    /g<CR>
" 显示行号
set number
"set copyindent
"set preserveindent
"语言设置
set langmenu=zh_CN.UTF-8
set helplang=cn
"字体设置
set guifont=Bitstream\ Vera\ Sans\ Mono\ 10
"背景颜色设置
set t_Co=256

""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" VIM Status Line &  Command Line
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" 打开vim状态栏标尺
set ru
" 启动显示状态行(1),总是显示状态行(2)
set laststatus=2
" 命令行（在状态行下）的高度，默认为1，这里是2
set cmdheight=1
"状态行显示的内容
set statusline=%F%m%r%h%w\ [FORMAT=%{&ff}]\ [TYPE=%Y]\ [POS=%l,%v][%p%%]\ %{strftime(\"%d/%m/%y\ -\ %H:%M\")}
" 高亮字符，让其不受100列限制
highlight OverLength ctermbg=red ctermfg=white guibg=red guifg=white
:match OverLength '\%80v.*'
" 状态行颜色
highlight StatusLine guifg=SlateBlue guibg=Yellow
highlight StatusLineNC guifg=Gray guibg=White
" 命令模式Tab自动补全
set wildmenu 
" 在状态行上显示光标所在位置的行号和列号
set ruler
set rulerformat=%20(%2*%<%f%=\ %m%r\ %3l\ %c\ %p%%%)

""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" VIM Other Config 
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" 打开断行模式对亚洲语言支持
set fo+=mB
" 启动的时候不显示那个援助乌干达儿童的提示  
set shortmess=atI  

""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" VIM Action Item 
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" 可以在buffer的任何地方使用鼠标（类似office中在工作区双击鼠标定位）
set mouse=v
"set selection=exclusive
"set selectmode=mouse,key
" 输入:set list命令是应该显示些啥？
set listchars=tab:\|\ ,trail:.,extends:>,precedes:<,eol:$
"set list listchars=tab:→\ ,extends:>,precedes:<
" 当右键单击窗口的时候，弹出快捷菜单
set mousemodel=popup 
" 删除键可以继续往前删除数据 
set backspace=indent,eol,start 
" 通过使用: commands命令，告诉我们文件的哪一行被改变过
set report=0

""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" VIM Normal Config 
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" 不兼容vi
set nocp
" 与windows共享剪贴板
set clipboard+=unnamed  
" 保存全局变量
set viminfo+=!
" 去掉输入错误的提示声音
set noeb
" 设置当文件被改动时自动载入
set autoread
"代码补全 
set completeopt=preview,menu 
"自动保存
set autowrite
" 突出显示当前行
set cursorline              
" 设置魔术
set magic   
" 隐藏工具栏
set guioptions-=T 
" 隐藏菜单栏          
set guioptions-=m 
if has("autocmd")
    autocmd BufReadPost *
                \ if line("'\"") > 0 && line("'\"") <= line("$") |
                \   exe "normal g`\"" |
                \ endif
endif

" Vim 所工作的终端 (或者 Windows 的 Console 窗口) 的字符编码方式
" Encoding setting
set termencoding=utf-8
" 当前字符编码
set encoding=utf8 
" 设置编码自动识别
set fileencodings=utf8,ucs-bom,gbk,cp936,gb2312,gb18030,latin1 
set fileencoding=utf-8
language messages en_US.utf-8

"新建文件后，自动定位到文件末尾
autocmd BufNewFile * normal G

"autocmd BufEnter * cd %:p:h



let g:NERDTreeIndicatorMapCustom = {
    \ "Modified"  : "✹",
    \ "Staged"    : "✚",
    \ "Untracked" : "✭",
    \ "Renamed"   : "➜",
    \ "Unmerged"  : "═",
    \ "Deleted"   : "✖",
    \ "Dirty"     : "✗",
    \ "Clean"     : "✔︎",
    \ 'Ignored'   : '☒',
    \ "Unknown"   : "?"
    \ }

""""""""""""""""""""""主题
"colorscheme space-vim-dark
colorscheme dark_eyes
"hi Comment cterm=italic

let g:airline_theme= "bubblegum"

let g:airline_left_sep = '▶'
let g:airline_right_sep = '◀'
let g:airline_symbols.crypt = '������'
let g:airline_symbols.linenr = '☰'
let g:airline_symbols.linenr = '¶'
let g:airline_symbols.maxlinenr = '㏑'
let g:airline_symbols.branch = '⎇'
let g:airline_symbols.paste = 'Þ'
let g:airline_symbols.spell = 'Ꞩ'
let g:airline_symbols.notexists = '∄'
let g:airline_symbols.whitespace = 'Ξ'
