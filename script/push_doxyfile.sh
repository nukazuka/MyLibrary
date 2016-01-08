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



# doxygen
# cd document
# #rename "s/_canvas/canvas/" _canvas*
# #sed -i -e "s/_canvas/canvas/g" *.html
# echo -e "\n\n git add ." 
# git add -A
# git commit -m "$1"
# git push origin gh-pages

# cd ..
# git add -A 
# git commit -m "$1"
# git push origin master


# checkout to gh-pages in document directory
cd document
git checkout gh-pages

# go to parent directory and make doxygen files
cd ..
doxygen

# back to document directory
cd document

# rename files which begin with"_" 
for file in `ls _*`
do
    new_file=`echo $file | cut -c2-`
    mv ${file} ${new_file}
    sed -i -e "s/${file}/${new_file}/g" *.html
done

#rename -f "s/_canvas/canvas/" _canvas*
#sed -i -e "s/_canvas/canvas/g" *.html

git add -A
git commit -m "$1"
git push origin gh-pages
git checkout master

