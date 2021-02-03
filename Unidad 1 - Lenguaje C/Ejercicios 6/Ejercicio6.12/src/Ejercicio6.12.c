/*
 ============================================================================
 Name        : 12.c
 Author      : Juan Pablo Jiménez
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

char nombres[3][20] = {"juan", "pablo", "code"};

int main(void) {

	char i; //un char
	char *a; //puntero de tipo array
	char (*b)[20];  //array de punteros

	a = (char *)nombres;  //En arreglos bidimensionales viene siendo lo mismo en lugar de un char es un array de tipo char
	printf("El primer nombre es %s \n", a);

	b = (char (*)[20])nombres[0];  //Almacena la primera direccion de memoria de cada arreglo
	for(i=0; i<3; i++){
		printf("EL nombre[%d] es %s \n", i, (char *)(b+i));  //Imprimimos cada arreglo de caracteres, al decir que array de punteros + i estamos iterando en el arreglo
	}
	return EXIT_SUCCESS;
}
