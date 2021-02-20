/*
 ============================================================================
 Name        : Proyecto.c
 Author      : Juan Pablo Jiménez
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	puts("!!!Base de datos de Estudiantes!!!");

	char entrada[100], comand[40];
	int salida = 0;

	do{
		printf("Ingresa el comando \n");
		fgets(entrada, 99, stdin);

		sscanf(entrada, "%s", comand);

		if(strncmp(comand, "mkdb", 4) == 0){
			printf("Base de datos creada\n");
		}
		else if(strncmp(comand, "exit", 4) == 0){
			salida = 1;
		}
		else{
			printf("Comando Incorrecto");
		}

	}while(salida == 0);

	return EXIT_SUCCESS;
}
