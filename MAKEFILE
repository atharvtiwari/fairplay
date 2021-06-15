main: main.o cipher.o
	gcc main.o cipher.o -o main.exe

main.o: main.c
	gcc -Wall -c main.c -o main.o

cipher.o: cipher.c
	gcc -Wall -c cipher.c -o cipher.o