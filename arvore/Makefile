main:	main.o arvore.o
	gcc main.o arvore.o -o 1

main.o:	main.c
	gcc -c main.c

arvore.o: arvore.c arvore.h
	gcc -c arvore.c 

clean:
	rm *.o

