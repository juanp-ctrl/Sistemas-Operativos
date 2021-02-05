/*
 ============================================================================
 Name        : Archivos.c
 Author      : Juan Pablo Jiménez
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

const char archivo[] = "src/input.txt";

int main(void) {
	puts("!!!Hello World!!!");
	int cont = 0;
	FILE *infile;  //FILE palabra reservada, creamos un puntero de tipo FILE

	int caracter;
	infile = fopen(archivo, "r");   //Abre el archivo y con r lo lee

	if(infile == NULL){
		printf("No puede abrir el archivo %s\n", archivo);
		exit(8);  //reporta que algo salio mal
	}
	while(1){   //el 0 es el false y cualquier otro numero es el true, aqui creamos un loop infinito para leer todo el archivo
		caracter = getc(infile);
		if(caracter == EOF){   //EOF es el end of file
			break;
		}
		printf("Caracter %c \n", caracter);
		++cont;
	}
	printf("Numero de caracteres del archivo %s es %d \n", archivo, cont);
	fclose(infile); //Cerramos archivo

	return EXIT_SUCCESS;
}
