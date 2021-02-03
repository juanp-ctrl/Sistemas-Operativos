/*
 ============================================================================
 Name        : Estructuras.c
 Author      : Juan Pablo Jiménez
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	puts("!!!Canción!!!");

	struct cdMusica {
		char titulo[30];
		char artista[30];
		char genero[20];
		int numcanciones;
		int lanzamiento;
		int precio;
	};

	struct cdMusica cd = {"Brindo con el alma", "Diomedes Diaz", "Vallenato", 11, 1986, 19900};

	printf("Titulo: %s\nArtista: %s\nGenero: %s\nCaciones: %d\nLanzamiento: %d\nPrecio: %d\n", cd.titulo, cd.artista, cd.genero, cd.numcanciones, cd.lanzamiento, cd.precio);


	return EXIT_SUCCESS;
}
