/*
 * bloquea.c
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

	printf("Se bloquea el semaforo en el proceso %d\n", getpid());

	if(sem_wait(sem) == -1){
		perror("Error de bloqueo");
	}

	printf("Bloqueo terminado %d\n", getpid());

	sem_close(sem);

	return EXIT_SUCCESS;
}
