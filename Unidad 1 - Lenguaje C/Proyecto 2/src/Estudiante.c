/*
 * Estudiante.c
 *
 *  Created on: Feb 27, 2021
 *      Author: juanpa
 */

#include <stdlib.h>
#include <stdio.h>

typedef struct estudiantes{
	char* nombre;
	int cedula;
	int semestre;
} s_estud;

s_estud* estud(){
	return (s_estud*)malloc(sizeof(s_estud));
}

void new_estud(s_estud* estud, char* nombre, int cedula, int semestre){
	estud->nombre = (char*)malloc((strlen(nombre)+1)*sizeof(char));
	strcpy(estud->nombre, nombre);
	estud->cedula = cedula;
	estud->semestre = semestre;
}

void  des_estud(s_estud* estud){
	free(estud->nombre);
}
