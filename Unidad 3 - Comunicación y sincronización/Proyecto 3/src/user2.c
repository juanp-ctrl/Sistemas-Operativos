/*
 * user2.c
 *
 *  Created on: Apr 27, 2021
 *      Author: juanpa
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* mode constants */
#include <fcntl.h>           /* O_* constants */
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <semaphore.h>
#include <pthread.h>

#define SH_SIZE 16

int descriptor;
int descriptor2;

sem_t *semaforoesc = NULL;
sem_t *semaforolee = NULL;
sem_t *semaforoesc2 = NULL;
sem_t *semaforolee2 = NULL;


void *leer(void *data){

	void* mapa = mmap(NULL, SH_SIZE, PROT_WRITE, MAP_SHARED, descriptor, 0);

	if(mapa == MAP_FAILED){
		perror("Error al crear el mapa");
		exit(EXIT_FAILURE);
	}

	char *ptrtexto = (char *)mapa;	//Le asiganamos la direccion que nos da el mapa

	while(ptrtexto[0] != 'Q'){

		if(sem_wait(semaforolee) == 0){		//Esperamos a que el usuario ingrese texto

			printf("User 1: %s\n", ptrtexto);

			sem_post(semaforoesc);		//Le damos paso a que pueda volver a escribir

		}
		else{
			printf("Error al esperar con el semaforo");
			break;
		}

	}

	pthread_exit(NULL);
}

void *enviar(void *data){

	void* mapa2 = mmap(NULL, SH_SIZE, PROT_WRITE, MAP_SHARED, descriptor2, 0);

	if(mapa2 == MAP_FAILED){
		perror("Error al crear el mapa");
		exit(EXIT_FAILURE);
	}

	char texto[32];

	char *ptrtexto = (char *)mapa2;	//Le asiganamos la direccion que nos da el mapa

	while(texto[0] != 'Q'){

		if(sem_wait(semaforoesc2) == 0){

			fgets(texto, 32, stdin);

			strcpy(ptrtexto, texto);

			sem_post(semaforolee2);
		}
		else{
			printf("Error al esperar con el semaforo");
			break;
		}

	}

	if(munmap(ptrtexto, SH_SIZE) < 0){
		perror("Error al eliminar el mapa");
		exit(EXIT_FAILURE);
	}

	pthread_exit(NULL);
}

int main(void) {

	pthread_t hilo1;
	pthread_t hilo2;

	descriptor = shm_open("memoria_comp", O_RDWR, 0600);

	if(descriptor < 0){
		perror("Error al crear el archivo de memoria compartida.");
		exit(EXIT_FAILURE);
	}

	if(ftruncate(descriptor, SH_SIZE * sizeof(char)) < 0){
		perror("Error al truncar el shared-memory-object");
		exit(EXIT_FAILURE);
	}

	descriptor2 = shm_open("memoria_comp2", O_RDWR, 0600);

	if(descriptor2 < 0){
		perror("Error al crear el archivo de memoria compartida 2.");
		exit(EXIT_FAILURE);
	}

	if(ftruncate(descriptor2, SH_SIZE * sizeof(char)) < 0){
		perror("Error al truncar el shared-memory-object");
		exit(EXIT_FAILURE);
	}

	//Abrir el semaforo

	semaforoesc = sem_open("semaforo_esc", 0);

	if(semaforoesc == SEM_FAILED){
		perror("Error al crear el semafor");
		exit(EXIT_FAILURE);
	}
	semaforoesc2 = sem_open("semaforo_esc2", 0);

	if(semaforoesc2 == SEM_FAILED){
		perror("Error al crear el semafor");
		exit(EXIT_FAILURE);
	}

	//Abrir el semaforo de lectura

	semaforolee = sem_open("semaforo_lee", 0);

	if(semaforolee == SEM_FAILED){
		perror("Error al crear el semafor");
		exit(EXIT_FAILURE);
	}
	semaforolee2 = sem_open("semaforo_lee2", 0);

	if(semaforolee2 == SEM_FAILED){
		perror("Error al crear el semafor");
		exit(EXIT_FAILURE);
	}

	puts("Bienvenido al chat:");

	pthread_create(&hilo1, NULL, &leer, NULL);
	pthread_create(&hilo2, NULL, &enviar, NULL);

	pthread_join(hilo1, NULL);
	pthread_join(hilo2, NULL);

	if(close(descriptor) < 0){
		perror("Error al cerrar el archivo de memoria compartida");
		exit(EXIT_FAILURE);
	}

	if(sem_close(semaforoesc) < 0){
		perror("Error al cerrar el semaforo 1");
		exit(EXIT_FAILURE);
	}

	if(sem_close(semaforolee) < 0){
		perror("Error al cerrar el semaforo 2");
		exit(EXIT_FAILURE);
	}

	if(sem_close(semaforoesc2) < 0){
		perror("Error al cerrar el semaforo 1.2");
		exit(EXIT_FAILURE);
	}

	if(sem_close(semaforolee2) < 0){
		perror("Error al cerrar el semaforo 2.2");
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}
