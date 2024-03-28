#!/bin/bash

for file in ./test_distance/* ; do
    if [[ -f "$file" ]]; then
        ./test_distance "$file"
    fi
done