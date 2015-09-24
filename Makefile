#
# Makefile
# prashant, 2015-09-23 09:24
#

CC= gcc
TARGET= album
CFLAGS= -g -w -ggdb -O0 -Wunreachable-code
build : conversions.c fileoperations.c album.c
	$(CC) -o $(TARGET) $(TARGET).c $(CFLAGS)
clean: 
	rm $(TARGET)
	rm index.html
	rm thumb*
	rm medium*

