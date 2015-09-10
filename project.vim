" Load this with command LoadProjectVimrc
"
" directory
" Folder in which script resides: (not safe for symlinks)
let s:base_path = expand('<sfile>:p:h')
let s:build_dir = s:base_path . "/build/make"
let s:bin_dir = s:base_path . "/bin"
let s:bin_name = "Bens-Game"

function! EditRootCMakeLists()
    let l:CMakePath = s:base_path . "/CMakeLists.txt"
    execute 'vsplit' l:CMakePath
endfunction
command! EditRootCMakeLists call EditRootCMakeLists()

function! EditCurrentCMakeLists()
    let l:CMakePath = getcwd() . "/CMakeLists.txt"
    execute 'vsplit' l:CMakePath
endfunction
command! EditCurrentCMakeLists call EditCurrentCMakeLists()

command! Make execute '!cd '. s:build_dir . " && make"

function! Run()
    write
    Make
    exec '!cd ' . s:bin_dir . ' && ./' . s:bin_name
endfunction
map <F5> :call Run()<CR>

