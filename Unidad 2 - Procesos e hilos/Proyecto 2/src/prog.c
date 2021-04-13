/*
 * prog.c
 *
 *  Created on: Mar 27, 2021
 *      Author: juanpa
 */


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>

typedef struct parametros_hilo{
	char *args[3];
} arg;

void* exhilo1 (void* parametros){

	struct parametros_hilo* p = (struct parametros_hilo*) parametros;

	FILE *pfile = fopen(p->args[1], "r");
	if(pfile == NULL){
		perror("Error en apertura de archivo");
	}

	FILE *pout = fopen(p->args[2], "w");
	if(pout == NULL){
		perror("Error en apertura de archivo");
	}

	char entrada[21];
	int cont = 0;

	while(fgets(entrada, 20, pfile) != NULL){   //Contamos la cantidad de lineas del archivo
		cont ++;
	}
	fclose(pfile);

	pfile = fopen(p->args[1], "r");

	char array_lineas[cont][21];

	int i = 0;
	while(fgets(array_lineas[i], 20, pfile) != NULL){
		i++;
	}

	for(int i=cont-1; i>=0; i--){
	  fprintf(pout, "%s", array_lineas[i]);
	}

	fclose(pfile);
	fclose(pout);

	return NULL;
}

void* exhilo2 (void* parametros){

	struct parametros_hilo* p = (struct parametros_hilo*) parametros;  //Casteamos los parametros a la estructura correcta

	FILE *pfile = fopen(p->args[1], "r");

	if(pfile == NULL){
		perror("Error en apertura de este archivo");
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

	pfile = fopen(p->args[1], "r");

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

	FILE *pout = fopen(p->args[2], "w");
	if(pout == NULL){
		perror("Error en apertura de archivo");
	}

	for(int i=0; i<cont; i++){
		fprintf(pout, "%s", entradas[i]);
	}

	fclose(pfile);
	fclose(pout);

	return NULL;
}

int main(int argc, char *argv[]){

	//Leer el archivo
	FILE *pfile = fopen(argv[1], "r");

	if(pfile == NULL){
		perror("Error en apertura de archivo");
		return 1;
	}

	typedef struct personas{
		char nombre[9];
		char profesion[9];
		int edad;
	} persona;

	char entrada[21];
	int cont = 0;

	while(fgets(entrada, 20, pfile) != NULL){   //Contamos la cantidad de lineas del archivo
		cont ++;
	}
	fclose(pfile);

	if(cont > 100){
		printf("El archivo excede las 100 lineas, por favor verifica el archivo");
		return 1;
	}

	persona *ptr = malloc(sizeof(persona)*cont);
	pfile = fopen(argv[1], "r");


	//Organizar en una estructura la información
	int i = 0;
	while(fgets(entrada, 20, pfile) != NULL){
		sscanf(entrada, "%9s %9s %d", (ptr+i)->nombre, (ptr+i)->profesion, &(ptr+i)->edad);
		i++;
	}

	//Imprimir el contenido de la estructura
	puts("\nContenido de la estructura");
	for(int i=0; i<cont; i++){
		printf("%s %s %d\n", (ptr+i)->nombre, (ptr+i)->profesion, (ptr+i)->edad);
	}
	free(ptr);

	pthread_t hilo1, hilo2;
	arg hilo1_p, hilo2_p;

	hilo1_p.args[0] = argv[0];
	hilo1_p.args[1] = argv[1];
	hilo1_p.args[2] = argv[2];

	hilo2_p.args[0] = argv[0];
	hilo2_p.args[1] = argv[1];
	hilo2_p.args[2] = argv[3];

	pthread_create(&hilo1, NULL, &exhilo1, &hilo1_p);
	pthread_create(&hilo2, NULL, &exhilo2, &hilo2_p);

	pthread_join(hilo1, NULL);
	pthread_join(hilo2, NULL);

	fclose(pfile);

	FILE *pin1, *pin2;
	pin1 = fopen(argv[2], "r");
	pin2 = fopen(argv[3], "r");

	printf("\nContenido de archivo lista de personas invertida %s\n", argv[2]);
	while(fgets(entrada, 20, pin1) != NULL){
		printf("%s", entrada);
	}

	printf("\nContenido de archivo por orden alfabetico de la ocupación %s\n", argv[3]);
	while(fgets(entrada, 20, pin2) != NULL){
		printf("%s", entrada);
	}
	puts("-");

	fclose(pin1);
	fclose(pin2);

	return EXIT_SUCCESS;
}
