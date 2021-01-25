/*
 * hw1-multiply-random-square-matrix (sequential & parallel using pthread)
 *
 *  Created on: 25 janv. 2021
 *      Author: relabed
 */
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include <time.h>

#include "initMatrix.h"
#include "displayMatrix.h"
#include "mult.h"

int main()
{

	char mode;
	printf("Entrez le mode d'exécution du programme (p pour prallèle et s pour séquentiel):\n");
			    scanf("%c",&mode); /* on récupère le mode d'exécution que l'utilisateur tape */
	if (mode == 's') {

	int n;  	// MATRIX DIMENSION
		int i;

		printf("Entrez la dimension de la matrice (un nombre entier):\n");
		    scanf("%d",&n); /* on récupère la dimension de la matrice que l'utilisateur tape */

		printf("Valeur de la 1ère Matrice (%d dimension) =\n", n);
		int **A = (int **)malloc(n * sizeof(int *)); /* on alloue de l'espace pour une matrice */
		for (i = 0; i < n; i++)
			A[i] = (int *)malloc(n * sizeof(int));

		generateRandomMatrix(A, n, 10); /* on affecte des valeurs aléatoires à la matrice A*/
		printMatrix(A, n); /* on affiche les valeurs de la matrice via la fonction printMatrix qui se trouve dans displayMatrix.c */

		printf("Valeur de la 2ème Matrice (%d dimension) =\n", n);
		int **B = (int **)malloc(n * sizeof(int *)); /* on alloue de l'espace pour une matrice */
		for (i = 0; i < n; i++)
			B[i] = (int *)malloc(n * sizeof(int));

		generateRandomMatrix(B, n, 10); /* on affecte des valeurs aléatoires à la matrice B */
		printMatrix(B, n); /* on affiche les valeurs de la matrice via la fonction printMatrix qui se trouve dans displayMatrix.c */


	float temps;
	clock_t t1, t2;

		int j,k;
		int **C = (int **)malloc(n * sizeof(int *)); /* on alloue de l'espace pour une matrice */
			for (i = 0; i < n; i++)
				C[i] = (int *)malloc(n * sizeof(int));

		printf("Multiplication de la matrice = \n");
		t1 = clock(); /* ici on commence à chronometrer le temps */
		for(i = 0; i < n; i++)
		{
			for(j = 0; j < n; j++)
			{
				C[i][j]=0;
				for(k = 0; k < n; k++)
				{
					C[i][j] +=  A[i][k] * B[k][j]; /* ici ce fait la multiplication et on enregistre les résultats dans la matrice C*/
				}
			}
		}

		//Afficher le résultat
		printMatrix(C, n);

		t2 = clock(); /* ici on arrête de chronometrer le temps */
		temps = (float)(t2-t1)/CLOCKS_PER_SEC;

		    printf("temps d'execution en secondes = %f\n", temps);

	}

	else if (mode == 'p')
	{





	float temps;
	clock_t t1, t2;

	int MAX;
	printf("Entrez la dimension de la matrice (un nombre entier):\n");
    scanf("%d",&MAX); /* on récupère la dimension de la matrice que l'utilisateur tape */

	int i,j,k;

	printf("Valeur de la 1ère Matrice (%d dimension) =\n", MAX);
		int **A = (int **)malloc(MAX * sizeof(int *)); /* on alloue de l'espace pour une matrice */
		for (i = 0; i < MAX; i++)
			A[i] = (int *)malloc(MAX * sizeof(int));

		generateRandomMatrix(A, MAX, 10); /* on affecte des valeurs aléatoires à la matrice A*/
		printMatrix(A, MAX); /* on affiche les valeurs de la matrice via la fonction printMatrix qui se trouve dans displayMatrix.c */

		printf("Valeur de la 2ème Matrice (%d dimension) =\n", MAX);
		int **B = (int **)malloc(MAX * sizeof(int *)); /* on alloue de l'espace pour une matrice */
		for (i = 0; i < MAX; i++)
			B[i] = (int *)malloc(MAX * sizeof(int));

		generateRandomMatrix(B, MAX, 10); /* on affecte des valeurs aléatoires à la matrice B */
		printMatrix(B, MAX); /* on affiche les valeurs de la matrice via la fonction printMatrix qui se trouve dans displayMatrix.c */


	int max = MAX*MAX;


	// déclaration d'un tableau de threads de taille MAX * MAX
	pthread_t *threads;
	threads = (pthread_t*)malloc(max*sizeof(pthread_t));

	printf("Nombre de Thread utilisé = %d\n", max);
	t1 = clock(); /* ici on commence à chronometrer le temps */
	int count = 0;
	int* data = NULL;
	for (i = 0; i < MAX; i++)
		for (j = 0; j < MAX; j++)
			{

			// stockage des éléments de ligne et de colonne dans les données
			data = (int *)malloc(max*sizeof(int));
			data[0] = MAX;

			for (k = 0; k < MAX; k++)
				data[k+1] = A[i][k];

			for (k = 0; k < MAX; k++)
				data[k+MAX+1] = B[k][j];

			// création de threads
				pthread_create(&threads[count++], NULL,	mult, (void*)(data));

					}

	printf("Multiplication de la matrice = \n");

	for (i = 0; i < max; i++)
	{
	void *k;

	// joindre tous les threads et collecter la valeur de retour
	pthread_join(threads[i], &k);


		int *p = (int *)k;
	printf("%d ",*p);
	if ((i + 1) % MAX == 0)
		printf("\n");
	}
	t2 = clock(); /* ici on arrête de chronometrer le temps */
		temps = (float)(t2-t1)/CLOCKS_PER_SEC;

		    printf("temps d'execution en secondes = %f\n", temps);

	}
	else {
		printf("erreur de saisie, veuillez relancer le programme");
	}
return 0;
}
