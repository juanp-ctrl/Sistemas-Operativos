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
#include <errno.h>

int main(int argc, char *argv[]) {

	int id = 0;

	char *numeros[argc];
	for(int i=0; i<argc; i++){
		numeros[i] = argv[i];
	}
	numeros[argc] = NULL;

	for (int hijo = 0; hijo < 3; ++hijo) {

	    int pid = fork();

	    if(pid < 0){
	        exit(EXIT_FAILURE);
	    }
	    else if (pid > 0){
	    	id++;

	    }
	    else{
	        if(id == 0){
	        	if(execv("./promedio", numeros) == -1){
	        		perror("Error de ejecución");
	        		return(1);
	        	}
	    	}
	    	else if(id == 1){
	        	if(execv("./min", numeros) == -1){
	        		perror("Error de ejecución");
	        		return(1);
	        	}
	    	}
	    	else if(id == 2){
	        	if(execv("./max", numeros) == -1){
	        		perror("Error de ejecución");
	        		return(1);
	        	}
	    	}

	        exit(EXIT_SUCCESS);
	    }
	}

	for (int hijo = 0; hijo < 3; ++hijo) {
	    int status;
	    pid_t pid = wait(&status);
	}
	puts("Proceso finalizado");

	return EXIT_SUCCESS;
}
