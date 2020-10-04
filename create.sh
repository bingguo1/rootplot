#!/bin/bash

namearray=(hPx0 hPy0 hPz0 hPx hPy hPz hthetaXtest hthetaYtest hthetaX0 hthetaY0 hthetaXY0 hthetaX1 hthetaY1 hthetaXY1 hthetaX2 hthetaY2 hthetaXY2)

i=0
n=${#namearray[@]}
while [ $i -lt $n ]
do
    echo  " TH1F *${namearray[$i]}=(TH1F*)file->Get(\"${namearray[$i]}\");"
#    echo " ${namearray[$i]}->Smooth();"
    let i=$i+1
done
