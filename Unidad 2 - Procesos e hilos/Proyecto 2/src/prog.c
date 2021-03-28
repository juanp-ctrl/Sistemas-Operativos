/*
 * prog.c
 *
 *  Created on: Mar 27, 2021
 *      Author: juanpa
 */


#include <stdio.h>
#include <stdlib.h>

int main(){

	//Leer el archivo
	FILE *pfile = fopen("personas.txt", "r");

	if(pfile == NULL){
		perror("Error en apertura de archivo");
		return 1;
	}

	typedef struct personas{
		char nombre[9];
		char profesion[9];
		int edad;
	} persona;

	char entrada[21];
	int cont = 0;

	while(fgets(entrada, 20, pfile) != NULL){   //Contamos la cantidad de lineas del archivo
		cont ++;
	}
	fclose(pfile);

	if(cont > 100){
		printf("El archivo excede las 100 lineas, por favor verifica el archivo");
		return 1;
	}

	persona *ptr = malloc(sizeof(persona)*cont);
	pfile = fopen("personas.txt", "r");


	//Organizar en una estructura la información
	int i = 0;
	while(fgets(entrada, 20, pfile) != NULL){
		sscanf(entrada, "%9s %9s %d", (ptr+i)->nombre, (ptr+i)->profesion, &(ptr+i)->edad);
		i++;
	}

	//Imprimir el contenido de la estructura
	for(int i=0; i<cont; i++){
		printf("%s %s %d\n", (ptr+i)->nombre, (ptr+i)->profesion, (ptr+i)->edad);
	}
	free(ptr);

	return EXIT_SUCCESS;
}
