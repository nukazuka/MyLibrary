#!/bin/bash

# valiables
file=MyLibrary.hh
dist=include
path=${dist}/${file}

# argument operation for Makefile
if [ $# -eq 1 ]
then
    path=$1/${path}
    path2=$1/
fi

# message
echo -e "Let's make ${FILE}!"
echo -e "============================"

# make new MyLibrary.hh
if [ -e ${path} ]
then
    rm ${path}
fi

touch ${path}


# include guard #############################################
echo -e "#ifndef MYLIB_MYLIBRARY_HH" >> ${path}
echo -e "#define MYLIB_MYLIBRARY_HH" >> ${path}

# include headers  #############################################
echo -e "\n//include headers" >> ${path}

## ifndef __CINT__ # for cpp ###################################
echo -e "#ifndef __CINT__" >> ${path}

ls -1 ${path2}include/*.hh | xargs -I {} basename {} .hh | xargs -I {} echo -e "#include \"{}.hh\"" >> ${path}

echo -e "#endif // ndef __CINT__" >> ${path}

## ifdef __CINT__ # for CINT ###################################
echo -e "\n//if __CINT__ is defined, include its source files" >> ${path}
echo -e "#ifdef __CINT__" >> ${path}

#ls -1 ${path2}include/*.hh | xargs -I {} echo -e "#include \"`pwd`/{}\"" >> ${path}

ls -1 ${path2}src/*.cc | xargs -I {} echo -e "#include \"`pwd`/{}\"" >> ${path}

echo -e "#endif // __CINT__" >> ${path}

# edit MyLibrary.hh
## remove #include "MyLibrary.hh" and "HeadersPhast.hh"

# # sed -e "/line4/s/enable/disable/" /home/test.conf
sed -i "/MyLibrary.hh/d" ${path} 
sed -i "/Phast/d" ${path} 

# last endif
echo -e "#endif // MYLIB_MYLIBRARY_HH" >> ${path}

# echo used in Mac doesn't support -e option
# so echo -e "~~~" -> -e "~~~"
# delete "-e " with following commands
# And -i of sed in Mac is bit different
# so these commands are executed again
if [ `uname` = Darwin ]
then
    sed -i "" "/MyLibrary.hh/d" ${path} 
    sed -i "" "/Phast/d" ${path} 
    sed -i "" "s/\-e //" ${path}
fi


cat ${path}

# message
echo -e "============================"
echo -e "${path} was created" 
