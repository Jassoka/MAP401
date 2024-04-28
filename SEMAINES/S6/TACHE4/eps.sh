#!/bin/bash

for file in *.pbm; do
    if [[ -f "$file" ]]; then
        ./contour_eps "$file"
    fi
done