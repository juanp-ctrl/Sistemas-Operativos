/*
 * max.c
 *
 *  Created on: Mar 15, 2021
 *      Author: juanpa
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	puts("!!!Maximo!!!");

	int tam = argc-1;
	int numeros[tam];
	for(int i=0; i<tam; i++){
		numeros[i] = (int)*argv[i+1] - 48;
	}
	int promedio, min, max, total = 0, temp = 0;
	for(int i=0; i<tam; i++){
		total += numeros[i];
	}
	for (int i = 0; i < tam-1; i++) {
		for (int j = i+1; j < tam; j++) {
		   if(numeros[i] > numeros[j]) {
			   temp = numeros[i];
			   numeros[i] = numeros[j];
			   numeros[j] = temp;
		   }
		}
	}
	max = numeros[tam-1];
	printf("Max %d\n", max);

	return EXIT_SUCCESS;
}
