#
# Makefile
# prashant, 2015-09-23 09:24
#

build : conversions.c fileoperations.c album.c
	gcc -o album -g album.c -Wall -Wextra -ggdb -O0 -Wunreachable-code
clean: 
	rm album
	rm index.html
	rm thumb*
	rm medium*

