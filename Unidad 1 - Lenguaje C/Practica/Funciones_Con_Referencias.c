/*
 ============================================================================
 Name        : Ejercicio6.c
 Author      : Juan Pablo Jiménez
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

void cambiar(int *d1, int *d2);  //Declaracion (prototipo) de la funcion

int x, y;

int main(void) {

	x=1;
	y=2;

	printf("X es igual a: %d\n", x);
	printf("%s%d\n","Y es igual a: ", y);

	cambiar(&x,&y);   //Invocacion de la funcion

	printf("X es igual a: %d\n", x);
	printf("%s%d\n","Y es igual a: ", y);

	return EXIT_SUCCESS;
}

void cambiar(int *d1, int *d2){    //Definicion de la funcion

	int temp;
	temp = *d1;
	*d1 = *d2;
	*d2 = temp;
}
