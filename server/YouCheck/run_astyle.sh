#!/bin/bash

[ -n "$1" ] || exit 1

folder_path=$1
cd $folder_path

files=$(find -type f -and -not -iname '*result.json')

for file in $files; do
	echo $file
	astyle $file 2>&1 >/dev/null
	out=$(diff --unchanged-line-format="#" --old-line-format="$file:%dn%c'\012'" --new-line-format="" $file ${file}.orig |& sed 's/#\+/#\n/g') 
	echo ${out#?}
	[ -f ${file}.orig ] && rm $file && mv ${file}.orig $file 2>/dev/null
done

cd -
