#!/bin/bash

for file in *.pbm; do
    if [[ -f "$file" ]]; then
        ./test_contours "$file" "${file%.*}.contours.txt"
    fi
done