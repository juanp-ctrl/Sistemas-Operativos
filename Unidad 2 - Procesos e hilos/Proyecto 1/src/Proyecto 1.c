/*
 ============================================================================
 Name        : Proyecto.c
 Author      : Juan Pablo Jimenez
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {

	int id = 0;

	char *argsp1[4];
	argsp1[0] = argv[0];
	argsp1[1] = argv[1];
	argsp1[2] = argv[2];
	argsp1[3] = NULL;

	char *argsp2[4];
	argsp2[0] = argv[0];
	argsp2[1] = argv[1];
	argsp2[2] = argv[3];
	argsp2[3] = NULL;

	for (int hijo = 0; hijo < 2; ++hijo) {

	    int pid = fork();

	    if(pid < 0){
	        exit(EXIT_FAILURE);
	    }
	    else if (pid > 0){
	    	id++;
	    }
	    else{
	        if(id == 0){
	        	if(execv("./p1", argsp1) == -1){
	        		perror("Error de ejecución");
	        		return(1);
	        	}
	    	}
	    	else if(id == 1){
	        	if(execv("./p2", argsp2) == -1){
	        		perror("Error de ejecución");
	        		return(1);
	        	}
	    	}

	        exit(EXIT_SUCCESS);
	    }

	}

	for (int hijo = 0; hijo < 2; ++hijo) {
	    int status;
	    pid_t pid = wait(&status);
	}


	FILE *pfout1, *pfout2;

	pfout1 = fopen(argv[2], "r");
	if(pfout1 == NULL){
		  perror("Error en Archivo 1 no abierto");
		  return 1;
	}

	pfout2 = fopen(argv[3], "r");
	if(pfout2 == NULL){
		  perror("Error en Archivo 2 no abierto");
		  return 1;
	}

	puts("Archivo generado por p1\n");
	char linea[30];
	while(fgets(linea, 29, pfout1) != NULL){
		printf("%s\n",linea);
	}

	puts("Archivo generado por p2\n");
	while(fgets(linea, 29, pfout2) != NULL){
		printf("%s\n",linea);
	}

	return EXIT_SUCCESS;
}
