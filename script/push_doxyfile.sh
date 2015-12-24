#!/bin/bash

if [ $(uname) = "Linux" ]
then
echo_op="-e"
elif [ $(uname) = "Darwin" ]
then
echo_op=""
fi

if [ `pwd | xargs -I {} basename {} ` != "MyLibrary" ]
then
    echo ${echo_op} "Now you are `pwd`"
    echo ${echo_op} "Please go to MyLibrary"
    exit
fi

if [ $# -ne 1 ]
then
    echo ${echo_op} "Usage $0 [comment for commitment]"
    echo ${echo_op} "[comment for commitment] must be provided."
    exit
fi



doxygen
cd document
#rename "s/_canvas/canvas/" _canvas*
#sed -i -e "s/_canvas/canvas/g" *.html
echo -e "\n\n git add ." 
git add .

echo -e "\n\n git commit $1 " 
git commit -m "$1"

echo -e "\n\n git push gh-pages"
git push origin gh-pages

cd ..
echo -e "\n\n git add -A" 
git add -A 
echo -e "\n\n git commit -m $1"
git commit -m "$1"
echo -e "\n\n git push origin master"
git push origin master

