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

if [ "$(uname)" = "Darwin" ]
then
    echo_option=""
    br=""
elif [ "$(uname)" = "Linux" ]
then
    echo_option="-e"
    br="\n"
fi

# message
echo ${echo_option} "Let's make ${FILE}!"
echo ${echo_option} "============================"

# make new MyLibrary.hh
if [ -e ${path} ]
then
    rm ${path}
fi

touch ${path}


###############################################################
## settings for this file ######################################
###############################################################

# include guard #############################################
echo ${echo_option} "#ifndef MYLIB_MYLIBRARY_HH" >> ${path}
echo ${echo_option} "#define MYLIB_MYLIBRARY_HH" >> ${path}

# include headers  #############################################
echo ${echo_option} "${br}//include headers" >> ${path}


###############################################################
## ifndef __CINT__ # for cpp ##################################
###############################################################
echo ${echo_option} "#ifndef __CINT__" >> ${path}
ls -1 ${path2}include/*.hh | xargs -I {} basename {} .hh | xargs -I {} echo ${echo_option} "#include \"{}.hh\"" >> ${path}
echo ${echo_option} "#endif // ndef __CINT__" >> ${path}

###############################################################
## ifdef __CINT__ # for CINT ##################################
###############################################################
#echo ${echo_option} "${br}//if __CINT__ is defined, include its source files" >> ${path}
echo ${echo_option} "${br}//if __CINT__ is defined, include header files with its full path" >> ${path}
echo ${echo_option} "#ifdef __CINT__" >> ${path}

#ls -1 ${path2}include/*.hh | xargs -I {} echo ${echo_option} "#include \"`pwd`/{}\"" >> ${path}
#echo "#include \"`pwd -P`/../include/ArgumentParser.hh\""  >> ${path}
#echo "#include \"`pwd -P`/../include/MultiHist.hh\""  >> ${path}
#echo "#include \"`pwd -P`/../include/Style.hh\""  >> ${path}
echo "#include \"`pwd -P`/include/ArgumentParser.hh\""  >> ${path}
echo "#include \"`pwd -P`/include/MultiHist.hh\""  >> ${path}
echo "#include \"`pwd -P`/include/Style.hh\""  >> ${path}

# include *.hh with its full path
## some file depend on other files eg DirectoryOperation depends StringOperation
## to avoid confliction, such files are included at last
#ls -1 ${path2}src/*.cc | grep -v DirectoryOperation | xargs -I {} echo ${echo_option} "#include \"`pwd`/{}\"" >> ${path}
ls -1 ${path2}include/*.hh | grep -v DirectoryOperation | xargs -I {} echo ${echo_option} "#include \"`pwd`/{}\"" >> ${path}
#ls -1 ${path2}src/*.cc | grep  DirectoryOperation | xargs -I {} echo ${echo_option} "#include \"`pwd`/{}\"" >> ${path}
ls -1 ${path2}include/*.hh | grep  DirectoryOperation | xargs -I {} echo ${echo_option} "#include \"`pwd`/{}\"" >> ${path}

## if .cc contains class, .hh should be included as well ######
# include *.hh
echo `grep ArgumentParser.cc ${path} | sed -e "s/src/include/g" | sed -e "s/.cc/.hh/g" ` >> ${path}
echo `grep MultiHist.cc ${path}      | sed -e "s/src/include/g" | sed -e "s/.cc/.hh/g" ` >> ${path}
echo `grep Style.cc ${path}         | sed -e "s/src/include/g" | sed -e "s/.cc/.hh/g" ` >> ${path}


echo ${echo_option} "#endif // __CINT__" >> ${path}

## end of ifdef __CINT__

###############################################################
# edit MyLibrary.hh  ###########################################
###############################################################
## remove #include "MyLibrary.hh" and "HeadersPhast.hh"

# # sed -e "/line4/s/enable/disable/" /home/test.conf
sed -i "/MyLibrary.hh/d" ${path} 
sed -i "/Phast/d" ${path} 

# last endif
echo ${echo_option} "#endif // MYLIB_MYLIBRARY_HH" >> ${path}

# echo used in Mac doesn't support -e option
# so echo ${echo_option} "~~~" -> -e "~~~"
# delete "-e " with following commands
# And -i of sed in Mac is bit different
# so these commands are executed again
if [ `uname` = Darwin ]
then
    sed -i "" "/MyLibrary.hh/d" ${path} 
    sed -i "" "/Phast/d" ${path} 
    sed -i "" "s/\-e //" ${path}

    # because it's template class
#    sed -i "" "s/src\/MultiHist.cc/include\/MultiHist.hh/" ${path}
    sed -i "" "s/src\/PaveOperation.cc/include\/PaveOperation.hh/" ${path}
#    sed -i "" "s/src\/Style.cc/include\/Style.hh/" ${path}
fi


cat ${path}

# message
echo ${echo_option} "============================"
echo ${echo_option} "${path} was created" 
