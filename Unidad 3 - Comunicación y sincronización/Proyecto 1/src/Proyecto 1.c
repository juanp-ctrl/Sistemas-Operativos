/*
 ============================================================================
 Name        : Proyecto.c
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

int main(void) {

	puts("!!!Bienvenido a mensajes de padre a hijo!!!");

	int pipe1[2];		//Creamos los identificadores del pipe
	int pipe2[2];

	char buf[16];		//El buffer para los mensajes
	int nleido;

	//Creamos los pipes
	if(pipe(pipe1) == -1){
		perror("Errorr al crear el pipe 1");
		exit(EXIT_FAILURE);
	}

	if(pipe(pipe2) == -1){
		perror("Errorr al crear el pipe 2");
		exit(EXIT_FAILURE);
	}

	switch(fork()){

	case -1: //Si falla
		perror("Error al hacer el fork");
		exit(EXIT_FAILURE);

	case 0:  //El hijo

		//Cerramos la escritura del pipe 2
		if(close(pipe2[1]) == -1){
			perror("Error al cerrar el pipe 2 [1]");
			exit(EXIT_FAILURE);
		}

		//Cerramos la lectura del pipe 1
		if(close(pipe1[0]) == -1){
			perror("Error al cerrar el pipe 1 [0]");
			exit(EXIT_FAILURE);
		}

		//Leemos
		for(;;){
			while((nleido = read(pipe2[0], buf, 16)) > 0){

				char temp[16];

				strcpy(temp, buf);

				for(int i=0; i<strlen(temp); i++){
					if((int)temp[i] >= 97 && (int)temp[i] <= 122){
						temp[i] = temp[i] - 32;
					}
				}

				strcpy(buf, temp);

				//Enviamos mensaje al padre
				if(write(pipe1[1], buf, strlen(buf)) != strlen(buf)){
					perror("Error de escritura al padre");
					exit(EXIT_FAILURE);
				}

				if((int)buf[0] == 46)
		            break;
			}
			if((int)buf[0] == 46){
	            write(1, "Proceso hijo terminado\n", 24);
				break;
			}

		}

		close(pipe2[0]);
		close(pipe1[1]);
		exit(EXIT_SUCCESS);

	default:  //El padre

		//Cerramos la escritura del pipe 1
		if(close(pipe1[1]) == -1){
			perror("Error al cerrar el pipe 1 [1]");
			exit(EXIT_FAILURE);
		}

		//Cerramos la lectura del pipe 2
		if(close(pipe2[0]) == -1){
			perror("Error al cerrar el pipe 2 [0]");
			exit(EXIT_FAILURE);
		}

		char mensaje[16];
		char temp[16];

		printf("Escribe el mensaje para que el hijo lo vuelva a mayusculas:\n");

		while(fgets(mensaje, 16, stdin) != NULL){		//Leemos de la entrada

			int size = strlen(mensaje);

			for(int i=0; i<strlen(temp); i++){
				temp[i] = ' ';
			};

			//Enviamos mensaje a hijo
			if(write(pipe2[1], mensaje, strlen(mensaje)) != strlen(mensaje)){
				perror("Error de escritura al hijo");
				exit(EXIT_FAILURE);
			}

			while((nleido = read(pipe1[0], buf, 16)) > 0){		//Imprimimos en pantalla el mensaje en mayusculas
				for(int i=0; i<=size-1; i++){
					temp[i] = buf[i];
				}
				temp[size] = '\0';

				if((int)buf[0] == 46)
					break;

				write(1, temp, size);
				break;
			}

			if((int)buf[0] == 46)
				break;

			write(1, "Ingresa otro texto:\n", 21);
			for(int i=0; i<strlen(mensaje); i++){
				mensaje[i] = ' ';
			}

		}

		close(pipe1[0]);
		close(pipe2[1]);

		wait(NULL);

		exit(EXIT_SUCCESS);
	}
}
