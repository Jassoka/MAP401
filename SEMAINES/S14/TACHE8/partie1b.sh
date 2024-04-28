#!/bin/bash

cd "./IMAGES"
for file in courbe_hilbert_*.pbm; do
    time ../eps_segments $file 0 "../RESULTATS/${file%.pbm}_0.eps"
    echo ""
done