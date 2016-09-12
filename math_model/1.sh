#!/bin/bash
for((i=0;i<500;i=i+1))
do
	g++ map.cpp -o map
	./map>map.txt
	./road<map.txt>>out.txt
	echo "\n" >>out.txt
	echo $i
done

