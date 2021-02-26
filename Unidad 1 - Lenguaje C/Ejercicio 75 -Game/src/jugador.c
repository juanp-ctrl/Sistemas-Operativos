/*
 * jugador.c
 *
 *  Created on: Feb 25, 2021
 *      Author: juanpa
 */


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "gun.h"

typedef struct jugadores{
	char* nombre;
	struct gun* arma;
} jugador;

jugador* mem_jugador(){
	return (jugador*)malloc(sizeof(jugador));
}

void ini_jugador(jugador* player, char* nombre){
	player->nombre = (char*)malloc((strlen(nombre)+1) * sizeof(char));  //Al tener un arreglo dentro de la estructura reservamos un espacio en el heap para usar despues el nombre
	strcpy(player->nombre, nombre);
	player->arma = NULL;
}

void elm_jugador(jugador* player){
	free(player->nombre);	//Liberamos el espacio reservado en la estructura
}

void recoger_arma(jugador* player, struct gun* arma){
	player->arma = arma; //Relación de agregacion
}

void jugador_dispara(jugador* player){
	if(player->arma != NULL){  //Si arma no esta vacio disparamos
		disparar(player->arma);
	}
	else{
		puts("No has recogido un arma");
	}
}

void tirar_arma(jugador* player){
	player->arma = NULL;  //No es necesario liberar la memoria del arma por que es una relacion de agregación
}
