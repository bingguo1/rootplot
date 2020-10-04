#!/bin/bash

workingpath=/home2/bing/nuage_generator/analysis/nomadtgt_duneflux/fhc_numubar/pic/
cp create_latexbody.sh $workingpath
cp template_head_mergePNGSs.tex $workingpath
cd $workingpath
echo now im inside $workingpath
chmod +x create_latexbody.sh
cp template_head_mergePNGSs.tex full_template.tex
./create_latexbody.sh >> full_template.tex

echo "full template generated"
echo 

while true; do
    read -p "Do you wish to generate pdf (Y) or make furthur change(N) ?" yn
    case $yn in
        [Yy]* ) echo "then I will generate pdf now"; break;;
        [Nn]* ) echo "exitting...."; exit;;
        * ) echo "Please answer yes or no.";;
    esac
done


echo 
echo generate pdf ....

pdflatex full_template.tex
pdflatex full_template.tex

echo move to /net/www/bing/graphs/

# rm /net/www/bing/graphs/*

dirname=`date '+%d%b%Y_%H:%M'`

mkdir /net/www/bing/graphs/old/${dirname}
echo creating new dir: /net/www/bing/graphs/old/${dirname}

mv  /net/www/bing/graphs/*.* /net/www/bing/graphs/old/${dirname}/

cp *.png /net/www/bing/graphs/

cp full_template.pdf /net/www/bing/graphs/

rm -f full_template.aux full_template.log full_template.out full_template.lof

echo done

exit

