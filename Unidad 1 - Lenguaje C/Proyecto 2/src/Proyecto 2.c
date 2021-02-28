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

	FILE *pfile;

	typedef struct estudiantes{
		int cedula;
		char nombre[20];
		int semestre;
	}estudiante;

	estudiante *puntr = NULL;

	char entrada[100], comand[40], nombredb[20], nombreest[20], ruta[20];
	int salida = 0, tamaño = 0, cedula, semestre, p;

int main(void) {
	puts("!!!Base de datos de Estudiantes V2.0!!!");

	do{
		printf("Ingresa un comando \n");
		fgets(entrada, 99, stdin);

		sscanf(entrada, "%s", comand);

		if(strncmp(comand, "mdb", 3) == 0){
			sscanf(entrada, "%s %s %d", comand, nombredb, &tamaño);
			mkdb(nombredb, tamaño);
		}

		else if(strncmp(comand, "ldb", 3) == 0){
			sscanf(entrada, "%s %s", comand, ruta);
			loaddb(ruta);
		}

		else if(strncmp(comand, "lsdbs", 5) == 0){
			readall();
		}

		else if(strncmp(comand, "gdb", 3) == 0){
			readsize();
		}

		else if(strncmp(comand, "sdb", 3) == 0){
			sscanf(entrada, "%s %s", comand, ruta);
			savedb(ruta);
		}

		else if(strncmp(comand, "radb", 4) == 0){
			readsize();
		}

		else if(strncmp(comand, "rsdb", 4) == 0){
			readsize();
		}

		else if(strncmp(comand, "svdb", 4) == 0){
			readsize();
		}

		else if(strncmp(comand, "mreg", 4) == 0){
			sscanf(entrada, "%s %d %s %d", comand, &cedula, nombreest, &semestre);
			mkreg(cedula, nombreest, semestre);
		}

		else if(strncmp(comand, "rr", 2) == 0){
			sscanf(entrada, "%s %d", comand, &cedula);
			readreg(cedula);
		}

		else if(strncmp(comand, "exit", 4) == 0){
			salir();
		}

		else{
			printf("Comando Incorrecto\n");
		}

	}while(salida == 0);

	return EXIT_SUCCESS;
}
