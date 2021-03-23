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
#include <pthread.h>

void* print_x (void* nousado){  //Una función con un parametro de puntero generico
	while(1) fputc('x', stderr);  //Inserta una x en la salida de error stderr
	return NULL;
}

int main(void) {
	pthread_t idhilo;

	pthread_create(&idhilo, NULL, &print_x, NULL);  //Creamos un nuevo hilo que ejecuta la funcion print_x
	while(1) fputc('o', stderr);
	return EXIT_SUCCESS;
}
