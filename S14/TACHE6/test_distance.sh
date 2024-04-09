#!/bin/bash

cd distance_fichiers/
for file in ./* ; do
    if [[ -f "$file" ]]; then
	echo "$file"
        ../test_distance "$file"
    fi
done
