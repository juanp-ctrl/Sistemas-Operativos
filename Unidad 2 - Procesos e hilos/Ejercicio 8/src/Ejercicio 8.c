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
#include <wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

	pid_t hijo1;
	pid_t hijo2;
	pid_t hijo3;

	char *numeros[argc];
	for(int i=0; i<argc; i++){
		numeros[i] = argv[i];
	}
	numeros[argc] = NULL;

	hijo1 = fork();
	if(wait(NULL) == hijo1){
		hijo2 = fork();
		if(wait(NULL) == hijo2){
			hijo3 = fork();
			if(wait(NULL) == hijo3){
				puts("Proceso finalizado");
			}
		}
	}

	if(hijo1 == 0){
		execv("./promedio", numeros);
	}
	else if(hijo2 == 0){
		execv("./min", numeros);
	}
	else if(hijo3 == 0){
		execv("./max", numeros);
	}

	return EXIT_SUCCESS;
}
