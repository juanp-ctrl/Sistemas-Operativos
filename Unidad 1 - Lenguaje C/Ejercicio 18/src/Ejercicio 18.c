/*
 ============================================================================
 Name        : Ejercicio.c
 Author      : Juan Pablo Jiménez
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void contenido(int [], int);

int main(void) {
	puts("!!!Bienvenido\nIngresar el tamaño del arreglo!!!");
	int tam, n, p;
	scanf("%d",&tam);
	int array[++tam];

	for(int i=0; i<tam-1; i++){
		printf("Ingrese un número: ");
		scanf("%d",&n);
		array[i] = n;
	}

	contenido(array,tam-1);

	puts("\nIngrese la posición en donde desea insertar el nuevo numero: ");
	scanf("%d",&p);
	p--;
	puts("Ingrese el numero: ");
	scanf("%d",&n);

	for(int i=tam-1; i>=p; i--){
		array[i+1] = array[i];
	}

	array[p] = n;

	contenido(array,tam);

	return EXIT_SUCCESS;
}

void contenido(int arr[], int num){
	for(int i=0; i<num; i++){
		printf("%d%c",arr[i],'|');
	}
}
