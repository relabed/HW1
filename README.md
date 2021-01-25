# HW1
HW1 MASTER 2 IIPE
This is the first homework for APP (Architecture and Parallel Programing) Module In the Master 2 IIPE (Informatique Industrielle, Parallèle et Embarquée)
Teacher Pr Lakhdar LOUKIL

Student Ramzi El Abed & Houari Belarbi

Multiply two square matrix using langage C with Eclipse IDE 202-12 in sequential mode & parallel mode (with pthread)


This is what we do in this homework :

- a Makefile has been defined.
- User has to input the dimension of the matrix
- Sequential version of mmm
- Parallel version of mmm
- We verify that parallel version is correct by comparing the result matrix with
one generated using the sequential algorithm.
- we have timed the execution time and we display the result in seconds
- A README is written.
- We have commenting the programs

Execution of the program :
- after downloading HW1-main.zip from github
- Decompressed in Linux (Ubuntu if possible)
- Open a terminal from the folder HW1-main
- run make command
- execute with ./hw1_ramzi.exe
- you will be ask to choose between sequential and parallel mode by typing (s or p), if you tape another character or number the program stop, you will have to execute it another time
- for sequential mode, you will have to input the dimension and you will have the execution time
- for parallel mode, you will have to input the dimension and the number of threads, you will get the execution time of sequential and parallel calculating, also you wil get the acceleration of the calculating and the comparison between result of sequential and parallel calculating
