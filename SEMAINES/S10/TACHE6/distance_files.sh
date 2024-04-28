#!/bin/bash

for file in ./fich_test/* ; do
    if [[ -f "$file" ]]; then
        ./test_distance "$file"
    fi
done