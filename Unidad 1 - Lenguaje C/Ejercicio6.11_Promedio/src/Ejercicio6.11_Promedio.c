/*
 ============================================================================
 Name        : 11_Promedio.c
 Author      : Juan Pablo Jiménez
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int promedio(int *);

int main(void) {

	int arreglo[100];
	for(int i = 0; i<100; i++){
		arreglo[i] = i+1;
	}

	printf("El promedio de los valores del arreglo es: %d\n", promedio(arreglo));

	return EXIT_SUCCESS;
}

int promedio(int *array){
	int promedio, total = 0;
	for(int i = 0; i<100; i++){
		total += array[i];
	}
	promedio = total / 100;

	return promedio;
}

