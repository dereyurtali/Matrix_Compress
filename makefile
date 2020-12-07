all: main.o compress.o
	gcc -g main.o compress.o -o matrix_multiplier

main.o: main.c
	gcc -g -c -Wall main.c 

compress.o: compress.c
	gcc -g -c -Wall compress.c 


clean:
	rm -f main.o compress.o matrix_multiplier
