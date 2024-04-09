#!/bin/bash

cd "./tache6_test"
for file in *.pbm ; do
    if [[ -f "$file" && ! $(grep -q "carre*" "$file") ]]; then
        ../eps_segments $file $1 ../eps_files/${file%.pbm}_$1.eps
    fi
done