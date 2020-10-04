#!/bin/bash

workingpath=/home2/bing/nuage_generator/generateAngle/smearplot/pics/
cp mergepictures_latex_template.tex $workingpath
cd $workingpath
echo now im inside $workingpath
for f in *.png
do
    list="${list}${f},"
done

length=${#list}
list=${list:0:length-1}
echo "this is what i'm going to put into tex file" $list
echo
echo start to generate latex file by template

suffix=`date '+%d%b%Y'`
sed  "s/filenamelist/$list/" mergepictures_latex_template.tex > mergepictures_latex_${suffix}.tex

echo generate pdf ....

pdflatex mergepictures_latex_${suffix}.tex
rm *.aux *.log *.out
echo move to /net/www/bing/graphs/

# rm /net/www/bing/graphs/*

dirname=`date '+%d%b%Y_%H:%M'`

mkdir /net/www/bing/graphs/old/${dirname}
echo creating new dir: /net/www/bing/graphs/old/${dirname}

mv  /net/www/bing/graphs/*.* /net/www/bing/graphs/old/${dirname}/

cp *.png /net/www/bing/graphs/

cp mergepictures_latex_${suffix}.pdf /net/www/bing/graphs/

echo done
