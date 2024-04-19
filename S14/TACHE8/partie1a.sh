#!/bin/bash

cd "./IMAGES"
for file in zebres*.pbm; do
    time ../eps_segments $file 0 "../RESULTATS/${file%.pbm}_0.eps"
    echo ""
done