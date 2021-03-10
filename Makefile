all:    hw1_ramzi.exe

hw1_ramzi.exe:  main.o initMatrix.o multiply.o
	gcc main.o initMatrix.o multiply.o -o hw1_ramzi.exe -lpthread

main.o: main.c
	gcc -c main.c -o main.o

initMatrix.o:   initMatrix.c
	gcc -c initMatrix.c -o initMatrix.o

multiply.o:   multiply.c
	gcc -c multiply.c -o multiply.o

clean:
	rm -fr hw1_ramzi *.o
