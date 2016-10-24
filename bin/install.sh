#!/bin/bash

BASE=MyLibrary-config
TEMP=MyLibrary-config.temp

DIR_BIN=~/bin

# OS dependent valiable
if [ `uname` = "Darwin" ]
then
    suffix=".dylib"
elif [ `uname` = "Linux" ]
then
    suffix=".so"
fi

# if ${TEMP} file is exist, remove this
if [ -e "${TEMP}" ]
then
    rm ${TEMP}
fi

echo 
echo -e "==   install.sh started ==========================================="
echo -e " Install MyLibrary-config"
echo -e " This script return options for gcc\n" 

# use bash
echo "#!/bin/bash" >> ${TEMP}

# get path to MyLibrary/lib
DIR=`pwd -P | sed -e "s/\/bin//g"`
DIR_LIB=${DIR}/lib
DIR_INCLUDE=${DIR}/include
echo "DIR_INCLUDE=${DIR_INCLUDE}" >> ${TEMP}
echo "DIR_MYLIBRARY=${DIR_LIB}" >> ${TEMP}

# add library options
LIB_FILES=(`ls -1 ${DIR_LIB}`)
flag=1
for file in ${LIB_FILES[@]}
do

#    option=`echo $file | cut -c4- | xargs -I {} basename -s ${suffix} {} | xargs -I {} echo "-l"{}`
    option=`echo $file | cut -c4- | xargs -I {} basename {} ${suffix} | xargs -I {} echo "-l"{}`
    
    if [ "${flag}" -eq 1 ]
    then 
	echo "LIBS=\"${option} \"" >> ${TEMP}
	flag=0
    else
	echo "LIBS+=\"${option} \" " >> ${TEMP}
    fi
done


# incdir 
echo "if [ \"\${1}\" = \"--incdir\" ] " >> ${TEMP}
echo "then" >> ${TEMP}
echo "echo \${DIR_INCLUDE}" >> ${TEMP}

# libdir
echo "elif [ \"\${1}\" = \"--libdir\" ] " >> ${TEMP}
echo "then" >> ${TEMP}
echo "echo \${DIR_MYLIBRARY}" >> ${TEMP}

# libs
echo "elif [ \"\${1}\" = \"--libs\" ] " >> ${TEMP}
echo "then" >> ${TEMP}
echo "echo -L\${DIR_MYLIBRARY} \${LIBS}" >> ${TEMP}

# help
echo "elif [ \"\${1}\" = \"--help\" ] " >> ${TEMP}
echo "then" >> ${TEMP}
echo "echo -e \"\\n ==== MyLibrary-config HELP === \\n\"" >> ${TEMP}
echo "echo \ \ --incdir : show the path to the include directory" >> ${TEMP}
echo "echo \ \ --libdir : show the path to the library directory" >> ${TEMP}
echo "echo \ \ --libs \ \ : returns a -L/-l flags in above output" >> ${TEMP}
echo "echo -e \"  (nothing): show everything\\n\"" >> ${TEMP}

# all 
echo "else" >> ${TEMP}
echo "echo -I\${DIR_INCLUDE} -L\${DIR_MYLIBRARY} \${LIBS}" >> ${TEMP}

echo "fi" >> ${TEMP}

# mv temp file 
chmod u+x ${TEMP}
mv ${TEMP} ${DIR_BIN}/${BASE}

echo -e " ${TEMP} is moved to :${DIR_BIN}\n"
echo -e " Let's try \$ ${BASE}\n"

echo "==   install.sh ended ==========================================="
echo
