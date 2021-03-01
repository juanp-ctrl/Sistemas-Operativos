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
void ldb(char* nombre);
void lsdbs();
void gdb();
void sdb(char* nombre);
void svdb();
void radb();
void rsdb();
void mreg(char* nombre, int cedula, int semestre);
void rr(int cedula);
void salir();

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

		else if(strncmp(comand, "ldb", 3) == 0){
			sscanf(entrada, "%s %s", comand, ruta);
			ldb(ruta);
		}

		else if(strncmp(comand, "lsdbs", 5) == 0){
			lsdbs();
		}

		else if(strncmp(comand, "gdb", 3) == 0){
			gdb();
		}

		else if(strncmp(comand, "sdb", 3) == 0){
			sscanf(entrada, "%s %s", comand, ruta);
			sdb(ruta);
		}

		else if(strncmp(comand, "radb", 4) == 0){
			radb();
		}

		else if(strncmp(comand, "rsdb", 4) == 0){
			rsdb();
		}

		else if(strncmp(comand, "svdb", 4) == 0){
			svdb();
		}

		else if(strncmp(comand, "mreg", 4) == 0){
			sscanf(entrada, "%s %d %s %d", comand, &cedula, nombreest, &semestre);
			mreg(nombreest, cedula, semestre);
		}

		else if(strncmp(comand, "rr", 2) == 0){
			sscanf(entrada, "%s %d", comand, &cedula);
			rr(cedula);
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

void mdb(struct s_datab* db, char* nombre, int tamaño){
	new_db(db, nombredb, tamaño);
	array_punteros[itera++] = db;
}

void ldb(char* nombre){
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
		sscanf(entrada, "%s %d", nombredb, &tamaño);
		struct s_datab* ptrdb = datab();
		pt_a = ptrdb;
		mdb(ptrdb, nombredb, tamaño);

		while(fgets(entrada, 99, pfile) != NULL){
			sscanf(entrada, "%d %19s %d", &cedula, nombreest, &semestre);
			crear_reg(pt_a, nombreest, cedula, semestre);
		}
		puts("La base de datos se ha cargado");
	}
	fclose(pfile);
}

void lsdbs(){
	for(int i=0; i<itera; i++){
		printf("BD %d Nombre: %s Tamaño: %d Registros: %d\n", i+1, get_nom(array_punteros[i]), get_tam(array_punteros[i]), get_regs(array_punteros[i]));
	}
}

void gdb(){
	printf("La base de datos activa es: %s Tamaño: %d Registros: %d\n", get_nom(pt_a), get_tam(pt_a), get_regs(pt_a));
}

void sdb(char* nombre){
	int opc = 0;
	for(int i=0; i<itera; i++){
		if(strcmp(get_nom(array_punteros[i]),nombre) == 0){
			pt_a = array_punteros[i];
			opc = 1;
		}
	}
	if(opc == 0){
		puts("No se ha encontrado la base de datos dada");
	}
}

void svdb(){
	char rutal[20];
	strcpy(rutal,get_nom(pt_a));
	strcat(rutal, ".txt");
	pfile = fopen(rutal, "w");

	if(pfile == NULL){
		puts("Error en la apertura del archivo");
		perror("Error en la apertura del archivo");
	}
	else{
		if(pt_a == NULL){
			printf("No se ha creado o cargado una base de datos\n");
		}
		else{
			fprintf(pfile, "%s %d %d\n", get_nom(pt_a), get_tam(pt_a), get_regs(pt_a));;
			for(int i=0; i<get_regs(pt_a); i++){
				fprintf(pfile, "%d\t%s\t%d\n", get_sced((struct s_estud*)get_registro(pt_a,i)), get_snom((struct s_estud*)get_registro(pt_a,i)), get_ssem((struct s_estud*)get_registro(pt_a,i)));
			}
		}
	}
	fclose(pfile);
}

void radb(){
	leer_regs(pt_a);
}

void rsdb(){
	printf("La cantidad de registros en la base de datos es: %d", get_regs(pt_a));
}

void mreg(char* nombre, int cedula, int semestre){
	crear_reg(pt_a, nombre, cedula, semestre);
}

void rr(int cedula){
	for(int i=0; i<get_regs(pt_a); i++){
		if(cedula == get_sced((struct s_estud*)get_registro(pt_a,i))){
			printf("Cedula: %d Nombre: %s Semestre: %d\n", get_sced((struct s_estud*)get_registro(pt_a,i)), get_snom((struct s_estud*)get_registro(pt_a,i)), get_ssem((struct s_estud*)get_registro(pt_a,i)));
		}
	}
}

void salir(){
	puts("Desea guardar la base de datos antes de salir ?");
	if(pt_a == NULL){
		printf("No ha creado o cargado una base de datos, hasta luego\n");
	}
	else{
		printf("La base de datos activa es %s\n1.Para salir sin guardar \n2.Para guardar y salir\n",  get_nom(pt_a));
		int op = 0;
		scanf(" %d", &op);
		if(op == 2){
			svdb();
			puts("Base de datos guardada");
		}
		puts("Hasta luego");
	}
	for(int i=0; i<itera; i++){
		for(int j=0; j<get_regs(array_punteros[i]); j++){
				des_estud((struct s_estud*)get_registro(array_punteros[i],j));
			}
		des_db(array_punteros[i]);
	}
	salida = 1;
}
