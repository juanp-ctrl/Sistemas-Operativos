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

void mkdb(char[], int);
void loaddb(char[]);
void savedb(char[]);
void readall();
void readsize();
void mkreg(int, char[], int);
void readreg(int);
void salir();

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
	puts("!!!Base de datos de Estudiantes!!!");

	do{
		printf("Ingresa un comando \n");
		fgets(entrada, 99, stdin);

		sscanf(entrada, "%s", comand);

		if(strncmp(comand, "mkdb", 4) == 0){
			sscanf(entrada, "%s %s %d", comand, nombredb, &tamaño);
			mkdb(nombredb, tamaño);
		}

		else if(strncmp(comand, "mkreg", 5) == 0){
			sscanf(entrada, "%s %d %s %d", comand, &cedula, nombreest, &semestre);
			mkreg(cedula, nombreest, semestre);
		}

		else if(strncmp(comand, "readall", 7) == 0){
			readall();
		}

		else if(strncmp(comand, "readreg", 7) == 0){
			sscanf(entrada, "%s %d", comand, &cedula);
			readreg(cedula);
		}

		else if(strncmp(comand, "readsize", 8) == 0){
			readsize();
		}

		else if(strncmp(comand, "loaddb", 7) == 0){
			sscanf(entrada, "%s %s", comand, ruta);
			loaddb(ruta);
		}

		else if(strncmp(comand, "savedb", 6) == 0){
			sscanf(entrada, "%s %s", comand, ruta);
			savedb(ruta);
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

void mkdb(char nombre[], int tamaño){
	if((nombre == NULL) | (tamaño == 0)){
		puts("comando mkdb ingresado incorrectamente");
	}
	else{
	puntr = malloc(sizeof(estudiante)* tamaño);
	p = 0;
	printf("Base de datos creada exitosamente\n");
	}
}

void loaddb(char nombre[]){
		char rutal[20];
		strcpy(rutal,nombre);
		strcat(rutal, ".txt");
		pfile = fopen(rutal, "r");

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

void savedb(char nombre[]){
	char rutal[20];
	strcpy(rutal,nombre);
	strcat(rutal, ".txt");
	pfile = fopen(rutal, "w");

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

void readall(){
	if(puntr == NULL){
		printf("No se ha creado o cargado una base de datos\n");
	}
	else{
		for(int i=0; i<p; i++){
			printf("%d\t%s\t%d\n", (puntr+i)->cedula, (puntr+i)->nombre, (puntr+i)->semestre);
		}
	}
}

void mkreg(int cedula, char nombre[], int semestre){
	if(puntr == NULL){
		printf("No se ha creado o cargado una base de datos\n");
	}
	else{
		if(p < tamaño){
			estudiante est;
			est.cedula = cedula;
			strcpy(est.nombre, nombreest);
			est.semestre = semestre;
			puntr[p++] = est;
		}
		else{
			puts("Se ha completado el numero de registros permitidos");
		}
	}
}

void salir(){
	puts("Desea guardar la base de datos antes de salir ?");
	if(puntr == NULL){
		printf("No  ha creado o cargado una base de datos, hasta luego\n");
	}
	else{
		printf("1.Para salir sin guardar \n2.Para guardar y salir\n");
		int op = 0;
		scanf(" %d", &op);
		if(op == 2){
			savedb(nombredb);
		}
		puts("Hasta luego");
	}
	salida = 1;
	free(puntr);
}

void readreg(int cedula){
	if(puntr == NULL){
		printf("No se ha creado o cargado una base de datos\n");
	}
	else{
		int j = 0;
		for(int i=0; i<p; i++){
			if((puntr+i)->cedula == cedula){
				j=1;
				printf("%d\t%s\t%d\n", (puntr+i)->cedula, (puntr+i)->nombre, (puntr+i)->semestre);
			}
		}
		if(j==0){
			puts("Registro no encontrado");
		}
	}
}

void readsize(){
	if(puntr == NULL){
		printf("No se ha creado o cargado una base de datos\n");
	}
	else{
		printf("En la base de datos hay: %d\n", p);
	}
}
