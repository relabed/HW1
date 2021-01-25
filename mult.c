/*
 * multiply-matrix.c
 *
 *  Created on: 25 janv. 2021
 *      Author: relabed
 */

#include <stdlib.h>
#include<pthread.h>

#include "mult.h"

// Chaque thread calcule un seul élément dans la matrice résultante
void *mult(void* arg)
{
	int *data = (int *)arg;
	int k = 0, i = 0;

	int x = data[0];
	for (i = 1; i <= x; i++)
		k += data[i]*data[i+x];

	int *p = (int*)malloc(sizeof(int));
		*p = k;

// Utilisé pour terminer un thread et la valeur de retour est passée en tant que pointeur
	pthread_exit(p);
}
