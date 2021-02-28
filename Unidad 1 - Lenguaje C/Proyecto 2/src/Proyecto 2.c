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
#include "BD.h"
#include "Estudiante.h"

void mdb(struct s_datab* db, char* nombre, int tamaño);
void lsdbs();
void salir(struct s_datab* db);

	FILE *pfile;

	struct s_datab* pt_a;
	int itera = 0;
	struct s_datab *array_punteros[20];

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

			struct s_datab* ptrdb = datab();
			pt_a = ptrdb;
			mdb(ptrdb, nombredb, tamaño);
		}

		/*else if(strncmp(comand, "ldb", 3) == 0){
			sscanf(entrada, "%s %s", comand, ruta);
			loaddb(ruta);
		}*/

		else if(strncmp(comand, "lsdbs", 5) == 0){
			//funcion
		}

		/*else if(strncmp(comand, "gdb", 3) == 0){
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
		}*/

		else if(strncmp(comand, "exit", 4) == 0){
			salir(pt_a);
		}

		else{
			printf("Comando Incorrecto\n");
		}

	}while(salida == 0);

	return EXIT_SUCCESS;
}

void mdb(struct s_datab* db, char* nombre, int tamaño){
	new_db(db, nombredb, tamaño);
	array_punteros[itera++] = db;
}

void salir(struct s_datab* db){
	puts("Desea guardar la base de datos antes de salir ?");
	if(db == NULL){
		printf("No ha creado o cargado una base de datos, hasta luego\n");
	}
	else{
		printf("La base de datos Activa es %s\n1.Para salir sin guardar \n2.Para guardar y salir\n",  get_nom(db));
		int op = 0;
		scanf(" %d", &op);
		if(op == 2){
			puts("Base de datos guardada");
		}
		puts("Hasta luego");
	}
	salida = 1;
}
