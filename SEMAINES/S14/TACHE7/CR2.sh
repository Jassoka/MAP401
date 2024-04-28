#!/bin/bash

cd "./CR"
for file in *.pbm; do
    for i in 1 3 10 30; do
        echo "$file d=$i"
        ../eps_bezier2 $file $i "../CR2/${file%.pbm}_$i.eps"
    done
done