# author: Muratcan Yurga

all: run

run: 
	gcc -I./libfdr/ sistem_proje.c -L./libfdr -lfdr -o sistem_proje 

#gcc -I./include/libfdr/ ./src/sistem_proje.c -L ./include/libfdr -o sistem_proje -lfdr
# Test: gcc -I. p1.c -L. -o p1 -lfdr

