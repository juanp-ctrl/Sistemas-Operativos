/*
 ============================================================================
 Name        : Ejercicio.c
 Author      : Juan Pablo Jimenez
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	puts("!!!Lista de numeros!!!");

	int numeros[argc-1];
	for(int i=1; i<argc; i++){
		numeros[i-1] = (int)*argv[i] - 48;
	}
	int promedio, min, max, total = 0, temp = 0;
	for(int i=0; i<argc-2; i++){
		total += numeros[i];
	}
	for (int i = 0; i < argc-2; i++) {
		for (int j = i+1; j < argc-2; j++) {
		   if(numeros[i] > numeros[j]) {
			   temp = numeros[i];
			   numeros[i] = numeros[j];
			   numeros[j] = temp;
		   }
		}
	}
	promedio = total / argc;
	min = numeros[0];
	max = numeros[argc-2];
	printf("Promedio %d, Min %d, Max %d\n", promedio, min, max);

	return EXIT_SUCCESS;
}
