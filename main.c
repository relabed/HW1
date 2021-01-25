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
#include <stdint.h>
#include <sys/time.h>

#include "initMatrix.h"

struct thread_args{
	    int start;
	    int end;
	};

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int main()
{

	char mode;
	printf("Entrez le mode d'exécution du programme (p pour parallèle et s pour séquentiel):\n");
			    scanf("%c",&mode); /* on récupère le mode d'exécution que l'utilisateur tape */

	if (mode == 's') { // si s exécution séquentiel seulement

		printf("Sequential execution\n");

	int n;  	// MATRIX DIMENSION
	int i;

		printf("Entrez la dimension de la matrice (un nombre entier):\n");
		    scanf("%d",&n); /* on récupère la dimension de la matrice que l'utilisateur tape */


		int **A = (int **)malloc(n * sizeof(int *)); /* on alloue de l'espace pour une matrice */
		for (i = 0; i < n; i++)
			A[i] = (int *)malloc(n * sizeof(int));

		generateRandomMatrix(A, n, 10); /* on affecte des valeurs aléatoires à la matrice A*/


		int **B = (int **)malloc(n * sizeof(int *)); /* on alloue de l'espace pour une matrice */
		for (i = 0; i < n; i++)
			B[i] = (int *)malloc(n * sizeof(int));

		generateRandomMatrix(B, n, 10); /* on affecte des valeurs aléatoires à la matrice B */


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


		t2 = clock(); /* ici on arrête de chronometrer le temps */
		temps = (float)(t2-t1)/CLOCKS_PER_SEC;

		    printf("temps d'execution en secondes = %f\n", temps);

	}

	else if (mode == 'p')  	{  // si p mode séquentiel et parallèle avec comparaison du temps d'exécution et du résultat
		float temps_p,temps_s;
			clock_t t1, t2, t3,t4;


		printf("Sequential & Parallal execution\n");

		int DIM;
			printf("Entrez la dimension de la matrice (un nombre entier):\n");
		    scanf("%d",&DIM); // on récupère la dimension de la matrice que l'utilisateur choisi

		int NUM_THREADS;
			printf("Entrez le nombre de threads:\n");
		    scanf("%d",&NUM_THREADS); // on récupère le nombre de thread que l'utilisateur veut utiliser

		 int i;

		 int **A = (int **)malloc(DIM * sizeof(int *)); // on alloue de l'espace pour une matrice
		 for (i = 0; i < DIM; i++)
		 A[i] = (int *)malloc(DIM * sizeof(int));

		 generateRandomMatrix(A, DIM, 10); // on affecte des valeurs aléatoires à la matrice A

		 int **B = (int **)malloc(DIM * sizeof(int *)); // on alloue de l'espace pour une matrice
		 for (i = 0; i < DIM; i++)
		 B[i] = (int *)malloc(DIM * sizeof(int));

		 generateRandomMatrix(B, DIM, 10); // on affecte des valeurs aléatoires à la matrice B

		 int **C = (int **)malloc(DIM * sizeof(int *)); // on alloue de l'espace pour la matrice de la multiplication séquentielle
		 for (i = 0; i < DIM; i++)
		 C[i] = (int *)malloc(DIM * sizeof(int));

		 int **D = (int **)malloc(DIM * sizeof(int *)); // on alloue de l'espace pour la matrice de la multiplication parallèle
		 for (i = 0; i < DIM; i++)
		 D[i] = (int *)malloc(DIM * sizeof(int));

		 int j,k;

		 t3 = clock(); /* ici on commence à chronometrer le temps du séquentiel */
		 for(i = 0; i < DIM; i++)
		    		{
		    			for(j = 0; j < DIM; j++)
		    			{
		    				C[i][j]=0;
		    				for(k = 0; k < DIM; k++)
		    				{
		    					C[i][j] +=  A[i][k] * B[k][j]; /* ici ce fait la multiplication et on enregistre les résultats dans la matrice C*/
		    				}
		    			}
		    		}


		    		t4 = clock(); /* ici on arrête de chronometrer le temps du séquentiel */
		    		temps_s = (float)(t4-t3)/CLOCKS_PER_SEC;

		    		    printf("temps d'execution en mode séquentiel en secondes = %f\n", temps_s);


		       void *multiply(void *arg) {
		    		struct thread_args * range = (struct thread_args *) arg;
		    			for(int i = 0; i < DIM; i++) {
		    				 for(int j = 0; j < DIM; j++) {
		    				    long thread_private_tmp = 0;
		    				    	for(int k = range->start; k < range->end; k++) {
		    				          thread_private_tmp += A[i][k] * B[k][j];
		    				    					   }
		    				                        pthread_mutex_lock(&lock);
		    				    					 D[i][j] += thread_private_tmp;
		    				    					 pthread_mutex_unlock(&lock);
		    				    					    	    	    }
		    				    					    	    	}
		    				    					    	 }

		pthread_t child_threads[NUM_THREADS];
			    struct thread_args work_ranges[NUM_THREADS];
			    int current_start, range;
			    current_start = 0;
			    range = DIM / NUM_THREADS;
			    for(int i = 0; i < NUM_THREADS; i++) {
			        work_ranges[i].start = current_start;
			        work_ranges[i].end = current_start + range;
			        current_start += range;
			    }
			    work_ranges[NUM_THREADS-1].end = DIM;
			    t1 = clock(); // ici on commence à chronometrer le temps du parallèle
			    for(int i = 0; i < NUM_THREADS; i++) {
			        pthread_create(&child_threads[i], NULL, multiply, &work_ranges[i]);
			    }
			    t2 = clock(); // ici on arrête de chronometrer le temps du parallèle
			    for(int i = 0; i < NUM_THREADS; i++) {
			        pthread_join(child_threads[i], NULL);
			    }

temps_p = (float)(t2-t1)/CLOCKS_PER_SEC;
printf("temps d'execution en mode parallèle en secondes = %f\n", temps_p);
printf("Accélération de Calcul = %f\n", temps_s/temps_p);

int **E = (int **)malloc(DIM * sizeof(int *)); // on alloue de l'espace pour la matrice de vérification des résultats parallèls et sequentiels
for (i = 0; i < DIM; i++)
E[i] = (int *)malloc(DIM * sizeof(int));

for (i = 0; i < DIM; ++i) {
		for (j = 0; j < DIM; ++j) {
			E[i][j]=D[i][j]-C[i][j];
					}
	}

if (E[DIM-1][DIM-1] == 0){
	printf("les Matrices résultantes de la multiplication en mode séquentiel et parallèle sont identiques");
}
else {
	printf("il y a eu une erreur de calcul dans le mode parallèle");
}
	}
	else {
		printf("erreur de saisie, veuillez relancer le programme");
	}
return 0;
}
