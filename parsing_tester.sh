#!/bin/bash

# for filename in ./invalid_maps/*.cub; do
#    ./cub3D $filename 2> piupiu.txt
# 	DIFF=$(diff --text piupiu.txt error.txt)
# 	if [ "$DIFF" != "" ]
# 	then
# 		echo -n "❌"
# 		echo $filename
# 		echo ""
# 	fi
# done
# rm -rf piupiu.txt

for filename in ./valid_maps/*.cub; do
    ./cub3D $filename > piupiu.txt
	mon_fichier=$(echo "$filename" | cut -d'_' -f3 | rev | cut -c 5- | rev)
	cat "./valid_maps/$mon_fichier" > output.txt
	DIFF=$(diff --text piupiu.txt output.txt)
	if [ "$DIFF" != "" ]
	then
		echo -n "❌"
		echo $filename
		echo ""
	fi
done
#rm -rf piupiu.txt
#rm -rf output.txt
