/*
 * arma.c
 *
 *  Created on: Feb 25, 2021
 *      Author: juanpa
 */


#include <stdlib.h>
#include <stdio.h>

//Definimos la estructura y las funciones de la cabecera gun.h (en el proceso de enlazado se encarga de esto)

typedef int estado;

//La estructura
typedef struct armas{
	int balas;
} arma;

arma* mem_arma(){
	return (arma*)malloc(sizeof(arma));  //Retornamos en terminos de la estructura arma la direccion del bloque de memoria reservado
}

void new_arma(arma* dir, int balas_ini){
	dir->balas = 0; //Comenzamos con el arma descargada
	if(balas_ini > 0){
		dir->balas = balas_ini;
	}
}

void elm_arma(arma* dir){
	free(dir);
}

estado tiene_balas(arma* dir){
	return (dir->balas > 0);
}

void disparar(arma* dir){
	dir->balas --;
	puts("BUM!!!, Has disparado");
}

void recargar(arma* dir){
	if(dir->balas == 6){
		puts("El arma esta full");
	}
	else{
		dir->balas ++;
		puts("+1 En balas :)");
	}
}
