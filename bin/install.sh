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
echo "DIR_MYLIBRARY=${DIR_LIB}" >> ${TEMP}

# add library options
LIB_FILES=(`ls -1 ${DIR_LIB}`)
flag=1
for file in ${LIB_FILES[@]}
do

    option=`echo $file | cut -c4- | xargs -I {} basename -s ${suffix} {} | xargs -I {} echo "-l"{}`
    
    if [ "${flag}" -eq 1 ]
    then 
	echo "LIBS=\"${option} \"" >> ${TEMP}
	flag=0
    else
	echo "LIBS+=\"${option} \" " >> ${TEMP}
    fi
done

echo "echo -L\${DIR_MYLIBRARY} \${LIBS}" >> ${TEMP}

# mv temp file 
chmod u+x ${TEMP}
mv ${TEMP} ${DIR_BIN}/${BASE}

echo -e " ${TEMP} is moved to :${DIR_BIN}\n"
echo -e " Let's try \$ ${BASE}\n"

echo "==   install.sh ended ==========================================="
echo
