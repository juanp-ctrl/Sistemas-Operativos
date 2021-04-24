/*
 * desbloquea.c
 *
 *  Created on: Apr 24, 2021
 *      Author: juanpa
 */


#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void) {

	sem_t *sem;

	sem = sem_open("ejemplo_de_semaforo",0);

	printf("Desbloquear el semaforo en el proceso %d\n", getpid());

	sem_post(sem);

	printf("Desbloqueo hecho %d\n", getpid());

	sem_close(sem);

	sem_unlink("ejemplo_de_semaforo");

	return EXIT_SUCCESS;
}
