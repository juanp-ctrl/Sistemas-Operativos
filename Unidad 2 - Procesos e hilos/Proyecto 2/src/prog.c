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
	puts("Contenido de la estructura");
	for(int i=0; i<cont; i++){
		printf("%s %s %d\n", (ptr+i)->nombre, (ptr+i)->profesion, (ptr+i)->edad);
	}
	free(ptr);

	typedef struct parametros_hilo{
		int id;
	} arg;

	void* ejecutar_hilo (void* parametros){

		struct parametros_hilo* p = (struct parametros_hilo*) parametros;  //Casteamos los parametros a la estructura correcta

		char hilo[] = {"./hilo "};
		hilo[6] = (char) p->id + '0';

		char *args[4];
		args[0] = argv[0];
		args[1] = argv[1];
		if(p->id == 1){
			args[2] = argv[2];
		}
		else if(p->id == 2){
			args[2] = argv[3];
		}
		args[3] = NULL;

		execv(hilo, args);

		return NULL;
	}

	pthread_t hilo1, hilo2;
	arg hilo1_p, hilo2_p;

	hilo1_p.id = 1;
	pthread_create(&hilo1, NULL, &ejecutar_hilo, &hilo1_p);

	hilo2_p.id = 2;
	pthread_create(&hilo2, NULL, &ejecutar_hilo, &hilo2_p);

	pthread_join(hilo1, NULL);
	pthread_join(hilo2, NULL);

	fclose(pfile);

	return EXIT_SUCCESS;
}
