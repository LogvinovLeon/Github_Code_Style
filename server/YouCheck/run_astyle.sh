#!/bin/bash

[ -n "$1" ] || exit 1

folder_path=$1
cd $folder_path

files=$(find -type f -and -not -iname '*result.json' -and -not -iname '*formatting.json')

for file in $files; do
	echo $file >&2
	astyle $file 2>&1 >/dev/null
	diff $file ${file}.orig >&2
	([ -f ${file}.orig ] && rm $file && mv ${file}.orig $file) 2>&1 >/dev/null
done

cd -
