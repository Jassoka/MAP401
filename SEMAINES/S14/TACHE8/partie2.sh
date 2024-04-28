#!/bin/bash

cd "./IMAGES"
for file in Asterix3.pbm lettre-L-cursive.pbm ColombesDeLaPaix.pbm; do
    for i in 0 0.5 1 2 4 8 16; do
    echo " [ d = $i ] "
        ../eps_segments $file $i "../RESULTATS/${file%.pbm}_segm_$i.eps"
        ../eps_bezier2 $file $i "../RESULTATS/${file%.pbm}_bez2_$i.eps"
        ../eps_bezier3 $file $i "../RESULTATS/${file%.pbm}_bez3_$i.eps"
    echo ""
    done
done