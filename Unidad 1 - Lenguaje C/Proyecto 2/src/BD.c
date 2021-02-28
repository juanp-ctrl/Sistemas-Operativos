/*
 * BD.c
 *
 *  Created on: Feb 27, 2021
 *      Author: juanpa
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Estudiante.h"

typedef struct databases{
	char* nombre;
	int N_registros;
	int tamaño;
	struct s_estud** registros;
} s_datab;

s_datab* datab(){
	return (s_datab*)malloc(sizeof(s_datab));
}

void new_db(s_datab* db, char* nombre, int regs){
	db->nombre = (char*)malloc((strlen(nombre) + 1) * sizeof(char));
	strcpy(db->nombre, nombre);
	db->N_registros = 0;
	db->tamaño = regs;
	db->registros = malloc(sizeof(struct s_estud*)*regs);
}

void des_db(s_datab* db){
	free(db->nombre);
	free(db->registros);
}

void crear_reg(s_datab* db, char* nombre, int cedula, int semestre){
	 struct s_estud* estudiante = estud();
	 db->registros[db->N_registros++] = estudiante;
	 new_estud(estudiante, nombre, cedula, semestre);
}

char* get_nom(s_datab* db){
	return db->nombre;
}

int get_tam(s_datab* db){
	return db->tamaño;
}

int get_regs(s_datab* db){
	return db->N_registros;
}

void leer_regs(s_datab* db){
	for(int i=0; i<db->N_registros; i++){
		printf("Cedula: %d Nombre: %s Semestre: %d\n", get_sced((struct s_estud*)db->registros[i]), get_snom((struct s_estud*)db->registros[i]), get_ssem((struct s_estud*)db->registros[i]));
	}
}


