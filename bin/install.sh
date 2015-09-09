#!/bin/bash

BASE=MyLibrary-config
TEMP=MyLibrary-config.temp

DIR_BIN=~/bin

echo 
echo -e "==   install.sh started ==========================================="
echo -e " Install MyLibrary-config"
echo -e " This script return options for gcc\n" 

# make copy
cp ${BASE} ${TEMP}
chmod u+x ${TEMP}

# get path to MyLibrary/lib
DIR=`pwd -P | sed -e "s/\/bin//g"`
DIR_LIB=${DIR}/lib

echo " ${TEMP} was made"
echo -n -e " This script will return :"

# edit temp file
sed -i -e "s:DIR_MYLIBRARY=:DIR_MYLIBRARY=${DIR_LIB}:g" MyLibrary-config.temp

./${TEMP}

# mv temp file 
mv ${TEMP} ${DIR_BIN}/${BASE}

echo -e " ${TEMP} is moved to :${DIR_BIN}\n"
echo -e " Let's try \$ ${BASE}\n"

echo "==   install.sh ended ==========================================="
echo
