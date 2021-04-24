/*
 ============================================================================
 Name        : Ejercicio.c
 Author      : Juan Pablo Jiménez Heredia
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(void) {

	sem_t *semaforo;
	mode_t modo = 0666;
	int flags = O_CREAT;
	unsigned int valor = 0;

	semaforo = sem_open("ejemplo_de_semaforo", flags, modo, valor);

	sem_close(semaforo);

	return EXIT_SUCCESS;
}
