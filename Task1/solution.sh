#!/bin/bash

if [ $# -eq 0 ]; then
    DIR=$(pwd) 
elif [ -d "$1" ]; then
    DIR="$1"
else
    echo "Error: $1 is not a directory"
    exit 1
fi
echo "running on dir: $DIR"

for file in $(find "$DIR" -type f -name "*.c"); do
    echo "$file"
    if [ -e "$file.orig" ]; then
        read -p "File $file.orig exists. Overwrite? [Y/n]" answer

        answer=${answer:-y}
        if [[ "$answer" =~ ^[Yy]$ ]]; then
            cp "$file" "$file.orig"
            echo "Overwritten $file.orig"
        else
            echo "Skipped $file.orig"
        fi
    else
        cp "$file" "$file.orig"
    fi
   
done