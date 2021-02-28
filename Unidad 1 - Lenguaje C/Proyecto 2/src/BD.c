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
	int* registros;
} s_datab;

s_datab* datab(){
	return (s_datab*)malloc(sizeof(s_datab));
}

void new_db(s_datab* db, char* nombre, int regs){
	db->nombre = (char*)malloc((strlen(nombre) + 1) * sizeof(char));
	strcpy(db->nombre, nombre);
	db->N_registros = 0;
	db->tamaño = regs;
	db->registros = malloc(sizeof(struct s_estud)*regs);
}

void des_db(s_datab* db){
	free(db->nombre);
	free(db->registros);
}

void crear_registro(s_datab* db, struct s_estud* estud){
	db->registros[db->N_registros++] = &estud;
}

