project: grep.o list.o
	cc grep.o list.o -o project
grep.o : grep.c list.h
	cc -c grep.c
list.o : list.c list.h
	cc -c list.c
