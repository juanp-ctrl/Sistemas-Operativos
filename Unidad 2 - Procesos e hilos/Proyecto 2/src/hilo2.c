/*
 * hilo2.c
 *
 *  Created on: Mar 28, 2021
 *      Author: juanpa
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]){
	//Leer el archivo
	FILE *pfile = fopen(argv[1], "r");

	if(pfile == NULL){
		perror("Error en apertura de este archivo");
		return 1;
	}

	char entrada[21];
	int cont = 0;

	while(fgets(entrada, 20, pfile) != NULL){   //Contamos la cantidad de lineas del archivo
		cont ++;
	}
	fclose(pfile);

	//Ordenar de forma alfabetica los strings

	char entradas[cont][21];
	char temp[21];

	pfile = fopen(argv[1], "r");

	int k = 0;
	while(fgets((char*)entradas[k], 20, pfile) != NULL){
		k ++;
	}

	for(int i=0; i<cont; i++){
		int j=0;
		while(entradas[i][j] != ' '){
			j++;
		}
		j++;

		//Metodo LowerCase
		//Sumar 32 a la letra para convertirla en minuscula solo si el caracter esta entre 65 a 90
		while(entradas[i][j] != ' '){
			if((int)entradas[i][j] >= 65 && (int)entradas[i][j] <= 90){
				entradas[i][j] = entradas[i][j] + 32;
			}
			j++;
		}
	}

	for(int i=0; i<cont; i++){
		int j=0;
		while(entradas[i][j] != ' '){
			j++;
		}
		j++;

		for(int a=i+1; a<cont; a++){
			int l=0;
			while(entradas[a][l] != ' '){
				l++;
			}
			l++;
			if(strcmp(entradas[i]+j, entradas[a]+l) > 0){ //Comparamos una cadena con todas las cadenas si esta es mayor a la otra intercambiamos posiciones
				strcpy(temp, entradas[i]);
				strcpy(entradas[i], entradas[a]);
				strcpy(entradas[a], temp);

				j=0;
				while(entradas[i][j] != ' '){
					j++;
				}
				j++;
			}
		}

	}

	FILE *pout = fopen(argv[2], "w");
	if(pout == NULL){
		perror("Error en apertura de archivo");
		return 1;
	}

	for(int i=0; i<cont; i++){
		fprintf(pout, "%s", entradas[i]);
	}

	fclose(pfile);
	fclose(pout);
	puts("Hilo2 termino");

	return EXIT_SUCCESS;
}
