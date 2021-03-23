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

struct parametros_hilo{  //Esta estructura sirve para pasar los parámetros al hilo
	char caracter;
	int contador;
};

void* imprimir_caracter (void* parametros){

	struct parametros_hilo* p = (struct parametros_hilo*) parametros;  //Casteamos los parametros a la estructura correcta
	for(int i=0; i< p->contador; i++){
		fputc(p->caracter, stderr);   //Imprimimos el caracter en la salida de error
	}
	return NULL;
}

int main(void) {

	pthread_t hilo1, hilo2;
	struct parametros_hilo hilo1_p;
	struct parametros_hilo hilo2_p;

	//Un hilo para imprimir 30.000 x
	hilo1_p.caracter = 'x';
	hilo1_p.contador = 30000;
	pthread_create(&hilo1, NULL, &imprimir_caracter, &hilo1_p);    //Se ejecuta la función (parametro 3) con los parametros pasados por la estructura, que luego en la
																   // función se castea el parametro generico a la estructura del hilo
	hilo2_p.caracter = 'o';
	hilo2_p.contador = 20000;
	pthread_create(&hilo2, NULL, &imprimir_caracter, &hilo2_p);

	pthread_join(hilo1, NULL);
	pthread_join(hilo2, NULL);

	return EXIT_SUCCESS;
}
