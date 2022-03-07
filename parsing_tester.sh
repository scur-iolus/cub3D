#!/bin/bash

for filename in ./invalid_maps/*.cub; do
   ./cub3D $filename 2> piupiu.txt
	DIFF=$(diff --text piupiu.txt error.txt)
	if [ "$DIFF" != "" ]
	then
		echo -n "❌"
		echo $filename
		echo ""
	fi
done
rm -rf piupiu.txt

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

rm -rf piupiu.txt
rm -rf output.txt

: '
	// 																		FIXME
	printf("EA %s\n", data.ea);
	printf("NO %s\n", data.no);
	printf("SO %s\n", data.so);
	printf("WE %s\n", data.we);
	printf("C %d,%d,%d\n", data.c.r, data.c.g, data.c.b);
	printf("F %d,%d,%d\n", data.f.r, data.f.g, data.f.b);
	char	*tmp;
	tmp = data.map.content;
	tmp[data.map.pos] = data.map.compass;
	while (*tmp)
	{
		printf("%.*s\n", data.map.width, tmp);
		tmp += data.map.width;
	}
	free_data(&data);
	// 																		FIXME
'
