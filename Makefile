all:	hw1_ramzi

hw1_ramzi:	main.o initMatrix.o displayMatrix.o mult.o
	gcc -lpthread main.o initMatrix.o displayMatrix.o mult.o -o hw1_ramzi

main.o:	main.c
	gcc -c main.c -o main.o

initMatrix.o:	initMatrix.c
	gcc -c initMatrix.c -o initMatrix.o

displayMatrix.o:	displayMatrix.c
	gcc -c displayMatrix.c -o displayMatrix.o	
	
mult.o:	mult.c
	gcc -c -lpthread mult.c -o mult.o

clean:
	rm -fr hw1_ramzi *.o