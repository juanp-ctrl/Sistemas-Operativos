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
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]) {

	int p1[2];			//Identificadores del pipe
	int p2[2];
	char buf[100];			//Donde guardamos (el buffer) para los mensajes
	int nleido;

	if(argc !=3 || strcmp(argv[1], "-h") == 0){
		printf("Ejecucion de programa %s \n-h para información\nprimer argumento -> el mensaje del padre\nsegundo argumento -> el mensaje del hijo\n", argv[0]);
	}

	//Creamos el pipe
	if(pipe(p1) == -1){
		perror("Error del pipe 1");
		exit(EXIT_FAILURE);
	}
	if(pipe(p2) == -1){
		perror("Error del pipe 2");
		exit(EXIT_FAILURE);
	}

	switch(fork()){

	case -1:
		perror("Error del fork");
		exit(EXIT_FAILURE);
	//El hijo
	case 0:

		if(close(p1[0]) == -1){
			perror("Error de cierre");
			exit(EXIT_FAILURE);
		}
		close(p2[1]);

		//Leemos
		while((nleido = read(p2[0], buf, 100)) > 0){
			write(1, buf, nleido);
		}
		close(p2[0]);

		//Escribimos
		sprintf(buf, "El hijo %d dice\n", getpid());
		write(p1[1], buf, strlen(buf));
		if(write(p1[1], argv[2], strlen(argv[2])) != strlen(argv[2])){
			perror("Error al escribir en el pipe");
			exit(EXIT_FAILURE);
		}
		close(p1[1]);

		write(1, "\n", 1);
		exit(EXIT_SUCCESS);
		break;

	default:
		close(p1[1]);
		close(p2[0]);
		//Escribimos
		sprintf(buf, "El padre %d dice\n", getpid());
		write(p2[1], buf, strlen(buf));
		if(write(p2[1], argv[1], strlen(argv[1])) != strlen(argv[1])){
			perror("Error de escritura en el padre");
			exit(EXIT_FAILURE);
		}
		close(p2[1]);
		//Leemos
		while((nleido = read(p1[0], buf, 100)) > 0){
			write(1, buf, nleido);
		}
		close(p1[0]);
		write(1, "\n", 1);
		wait(NULL);

		exit(EXIT_SUCCESS);
	}
}
