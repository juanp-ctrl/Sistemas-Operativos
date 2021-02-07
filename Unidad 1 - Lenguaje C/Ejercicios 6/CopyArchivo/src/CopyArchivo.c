/*
 ============================================================================
 Name        : CopyArchivo.c
 Author      : Juan Pablo Jiménez
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	puts("!!!Bienvenido!!!");
	char archivo1[20], archivo2[20];
	printf("Ingrese el nombre del primer archivo\n");
	scanf("%s",archivo1);
	printf("Ingrese el nombre del primer archivo\n");
	scanf("%s",archivo2);

	FILE *puntero1, *puntero2;

	puntero1 = fopen(archivo1, "r");

	char caracter;
	caracter = getc(puntero1);

	if(caracter == -1){
		printf("El archivo original esta vacio, fin del programa");
	}
	else{
		puntero2 = fopen(archivo2, "w");
		while(1){
			fputc(caracter, puntero2);
			caracter = fgetc(puntero1);
			if(caracter == EOF){
				fclose(puntero2);
				break;
			}
		}
	}
	fclose(puntero1);

	return EXIT_SUCCESS;
}
