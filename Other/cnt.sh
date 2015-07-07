#!/usr/bin/env bash
DIR=$1
if [ -d $DIR ]; then
	if [ $# = 1 ]
    	then
			echo "Файлы *.c"
			find $DIR -name "*.c" -exec wc -l '{}' \;
			echo "Файлы *.h"
			find $DIR -name "*.h" -exec wc -l '{}' \;
			
			find $DIR -name "*.c" -exec wc -l '{}' \; | awk '{z=s = s+$1 }; END { print "Количество строк в файлах *.c - "  s }'
			find $DIR -name "*.h" -exec wc -l '{}' \; | awk '{y=s = s+$1 }; END { print "Количество строк в файлах *.h - "  s }'

		else echo "Syntaxis error: usage ./filename.sh [dirname]"
	fi
else echo "Dir not found"
fi