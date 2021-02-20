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
#include <errno.h>

int main(void) {
	puts("!!!Base de datos de Estudiantes!!!");

	FILE *pfile;

	typedef struct estudiantes{
		int cedula;
		char nombre[20];
		int semestre;
	}estudiante;

	estudiante *puntr = NULL;

	char entrada[100], comand[40], nombredb[20], nombreest[20], ruta[20];
	int salida = 0, tamaño, cedula, semestre, p;

	do{
		printf("Ingresa un comando \n");
		fgets(entrada, 99, stdin);

		sscanf(entrada, "%s", comand);

		if(strncmp(comand, "mkdb", 4) == 0){
			sscanf(entrada, "%s %s %d", comand, nombredb, &tamaño);
			puntr = malloc(sizeof(estudiante)* tamaño);
			p = 0;
			printf("Base de datos creada exitosamente\n");
		}

		else if(strncmp(comand, "mkreg", 5) == 0){
			sscanf(entrada, "%s %d %s %d", comand, &cedula, nombreest, &semestre);
			if(puntr == NULL){
				printf("No se ha creado o cargado una base de datos\n");
			}
			else{
				estudiante est;
				est.cedula = cedula;
				strcpy(est.nombre, nombreest);
				est.semestre = semestre;
				puntr[p++] = est;
			}
		}

		else if(strncmp(comand, "readall", 7) == 0){
			if(puntr == NULL){
				printf("No se ha creado o cargado una base de datos\n");
			}
			else{
				for(int i=0; i<p; i++){
					printf("%d\t%s\t%d\n", (puntr+i)->cedula, (puntr+i)->nombre, (puntr+i)->semestre);
				}
			}
		}
		else if(strncmp(comand, "loaddb", 7) == 0){
			sscanf(entrada, "%s %s", comand, ruta);
			strcat(ruta, ".txt");
			pfile = fopen(ruta, "r");

			if(pfile == NULL){
				puts("Error en la apertura del archivo");
				perror("Error en la apertura del archivo");
			}
			else{
				fgets(entrada, 99, pfile);
				sscanf(entrada, "%s %d %d", nombredb, &tamaño, &p);
				puntr = malloc(sizeof(estudiante)* tamaño);
				int i = 0;
				while(fgets(entrada, 99, pfile) != NULL){
					sscanf(entrada, "%d %19s %d", &(puntr+i)->cedula, (puntr+i)->nombre, &(puntr+i)->semestre);
					i++;
				}
			}
			fclose(pfile);
		}

		else if(strncmp(comand, "savedb", 6) == 0){
			sscanf(entrada, "%s %s", comand, ruta);
			strcat(ruta, ".txt");
			pfile = fopen(ruta, "w");

			if(pfile == NULL){
				puts("Error en la apertura del archivo");
				perror("Error en la apertura del archivo");
			}
			else{
				if(puntr == NULL){
					printf("No se ha creado o cargado una base de datos\n");
				}
				else{
					fprintf(pfile, "%s %d %d\n", nombredb, tamaño, p);;
					for(int i=0; i<p; i++){
						fprintf(pfile, "%d\t%s\t%d\n", (puntr+i)->cedula, (puntr+i)->nombre, (puntr+i)->semestre);
					}
				}
			}
			fclose(pfile);
		}
		else if(strncmp(comand, "exit", 4) == 0){
			salida = 1;
		}
		else{
			printf("Comando Incorrecto\n");
		}

	}while(salida == 0);

	return EXIT_SUCCESS;
}
