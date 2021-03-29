/*
 * hilo1.c
 *
 *  Created on: Mar 28, 2021
 *      Author: juanpa
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	//Leer el archivo
	FILE *pfile = fopen(argv[1], "r");
	if(pfile == NULL){
		perror("Error en apertura de archivo");
		return 1;
	}

	FILE *pout = fopen(argv[2], "w");
	if(pout == NULL){
		perror("Error en apertura de archivo");
		return 1;
	}

	char entrada[21];
	int cont = 0;

	while(fgets(entrada, 20, pfile) != NULL){   //Contamos la cantidad de lineas del archivo
		cont ++;
	}
	fclose(pfile);

	pfile = fopen(argv[1], "r");

	char array_lineas[cont][21];

	int i = 0;
	while(fgets(array_lineas[i], 20, pfile) != NULL){
		i++;
	}

	for(int i=cont-1; i>=0; i--){
	  fprintf(pout, "%s", array_lineas[i]);
	}

	fclose(pfile);
	fclose(pout);

	return EXIT_SUCCESS;
}
