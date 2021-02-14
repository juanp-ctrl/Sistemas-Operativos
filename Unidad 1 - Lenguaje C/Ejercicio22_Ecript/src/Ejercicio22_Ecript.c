/*
 ============================================================================
 Name        : Ejercicio22_Ecript.c
 Author      : Juan Pablo Jiménez
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

int encript(int letra);

int main(int argc, char *argv[]){  //Se pueden usar otros nombres para los parametros, lo importante es que concuerde con int main(int, char*[])

	FILE *fp, *fout;
	char entrada[50], input[15], salida[25], function[5];
	int tamaño;
	//printf("Ingresa Archivo_a_Encriptar Archivo_de_salida Función\n");
	//fgets(entrada, 49, stdin);

	strcpy(input, argv[1]);  //strcpy sobreescribe la cadena
	strcat(salida, "./../");
	strcat(salida, argv[2]);
	strcpy(function, argv[3]);

	//sscanf(entrada, "%s %s %s", input, salida, function);  //Leemos de una cadena y guardamos en tres cadenas

	fp = fopen(input, "r");
	fout = fopen(salida, "w");

	if(fp == NULL){
		printf("Error %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	while (fgets(entrada, 50, fp) != NULL){
		tamaño = strlen(entrada);

		if(strncmp("xor", function, 5) == 0){

			for(int i=0; i<tamaño; i++){
				entrada[i] = encript(entrada[i]);
			}
			fputs(entrada, fout);

		}
	}
	fclose(fp);
	fclose(fout);

	return EXIT_SUCCESS;
}

int encript(int letra){
	return letra ^ 0xFF;
}
