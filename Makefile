all:    hw1_ramzi_2nd_part.exe

hw1_ramzi_2nd_part.exe:  main.o initMatrix.o
	gcc main.o initMatrix.o -o hw1_ramzi_2nd_part.exe -lpthread

main.o: main.c
	gcc -c main.c -o main.o

initMatrix.o:   initMatrix.c
	gcc -c initMatrix.c -o initMatrix.o

clean:
	rm -fr hw1_ramzi_2nd_part *.o
