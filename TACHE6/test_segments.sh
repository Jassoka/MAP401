#!/bin/bash

cd "./TACHE6_TEST"
if [ $# -ge 1 ]; then
    for file in *.pbm ; do
        ../eps_segments $file $1 ../TACHE6_RES/${file%.pbm}_$1.eps $2
    done
else
    echo "Syntaxe: $0 <distance_seuil> (s)"
fi