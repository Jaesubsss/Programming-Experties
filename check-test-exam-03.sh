function file_check () {
    # Check if an argument was provided
    if [ -z "$1" ]; then
        msg-errord "Error: No filename provided and/or extension provided!"
        return 1
    fi
    if [ -f "$1" ]; then
        filename=$(basename -- "$1")
        extension="${filename##*.}"
        extension=$(echo "$extension" | awk '{print tolower($0)}') ;#'
        extension=".$extension"
        givenext=$(echo "$2" | awk '{print tolower($0)}') ;#'
        if [ -z "$2" ]; then
            # no extension given, file exists
            return 0
        elif [ "$extension" == "$givenext" ]; then
            return 0
        else
            msg-error "Error: $1 has not the required extension $2 ('$extension' != '$givenext')"
            return 1
        fi
    else 
       msg-error "File '$1' does not exists!"
    fi
    msg-error "Error: that should not be reached!"
    return 1
}
  
function mexec {
    ## last argument
    msg=${!#}
    ## remove it from compilation
    local args=("$@")
    set -- "${args[@]:0:$((${#args[@]}-1))}"
    echo -e "\033[32m$@ ($msg)\033[0m"
    $@
}

function msg-error {
    echo -e "\033[31m$1\033[0m"
}    
    
function msg-warn  {
    echo -e "\033[33m$1\033[0m"
}
function msg-yellow  {
    echo -e "\033[33m$1\033[0m"
}
function tasks {
    if [ -z $4 ]; then
        msg-warn "Usage: bash $0 cpp-file uniprot1.dat uniprot2.dat uniprot.dat.gz ?other-cpp-file?"
        return 0
    else
       if ! [ -f uniprot.txt ]; then touch uniprot.txt ; fi
       if ! file_check $2 .dat ; then msg-error "second file must have dat extension"; return 0; fi
       if ! file_check $3 .dat ; then msg-error "third file must have dat extension"; return 0; fi       
       if ! file_check $4 .gz ; then msg-error "fourth file must have dat.gz extension"; return 0; fi              
       if [ -f dummy.dat ]; then msg-error "Error: file 'dummy.da't should not exists!"; return 0; fi
       if [ -f task ]; then rm task ; fi
       msg-yellow compile       
       ## fourth argument might be additional files to compile such as pex.cpp
       mexec  g++ -std=c++17 $5 $1 -o task "compilation"
       if ! [ -f "task" ] ; then 
           msg-error "Compilation does not worked!"
           return 1
       fi
       ### task 1
       msg-yellow task1
       mexec ./task "check usage"
       mexec ./task --help "check help"
       mexec ./task --go-search GO:0005576 dummy.dat "no existing file"
       mexec ./task --go-search GO:0005576 uniprot.txt "wrong file extension"
       mexec ./task --go-test GO:0005576 $2 "wrong option"       
       mexec ./task --go-search GO:000ABC $2 "wrong GO-id"
       ### task 2
       msg-yellow task2
       if file_check $4 .gz; then 
            mexec ./task --go-search GO:0005576 $4  "compressed file error" 
       else
            msg-error "Error: Fourth argument '$4' must be a file with extension .gz or .GZ!"
            return 0
       fi
       mexec ./task --go-search GO:0005576 $2  "all fine, check AP3A hits" | head -n 10
       
       ### task 3
       msg-yellow task3
       mexec grep --color class $1 "check for class - task 3"
       msg-yellow "search two files"
       mexec ./task --go-search GO:0005576 $2 $3 "all fine, check AP3A, Y729 hits" | head -n 10       
       msg-yellow "go-count one files"       
       mexec ./task --go-count GO:0005576 $2 "go count check one file" | tail -n 10       
       msg-yellow "go-count two files"       
       mexec ./task --go-count GO:0005576 $2 $3 "go count check two files" | tail -n 10       
    fi
    
}

tasks $@ 
