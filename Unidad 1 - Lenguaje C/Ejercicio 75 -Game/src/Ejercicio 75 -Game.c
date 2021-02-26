/*
 ============================================================================
 Name        : Ejercicio.c
 Author      : Juan Pablo Jiménez
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "gun.h"
#include "jugador.h"

int main(void) {
	puts("!!!Juego de disparos :) !!! \nIngresa el nombre de tu personaje:");

	char nombre[20];
	fgets(nombre, 19, stdin);
	struct jugador* pl1 = mem_jugador();
	struct gun* arma = mem_arma();
	new_arma(arma, 6);
	ini_jugador(pl1, nombre);

	int op = 0;
	do{
	printf("Hola %s", nombre);
	puts("Ingrese 1. Para coger un arma\n2. Para disparar\n3. Para ver si esta cargada el arma\n4. Para recargar\n5. Para dejar el arma\n9. Para salir");
	scanf("%d", &op);
	switch(op){

	case 1: recoger_arma(pl1, arma);
			puts("En tus manos un blaster espacial");
		break;
	case 2: disparar(arma);
		break;
	case 3: tiene_balas(arma);
		break;
	case 4: recargar(arma);
		break;
	case 5: tirar_arma(pl1);
		break;
	case 9: elm_jugador(pl1);
			free(pl1);
			elm_arma(arma);
		break;
	default: puts("Entrada no valida");
		break;

	}

	}while(op != 9);

	return EXIT_SUCCESS;
}
