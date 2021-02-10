/*
 ============================================================================
 Name        : Materias_Promedio_V2.c
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

	int numero;

	printf("%s\n", "Ingrese el numero de materias");
	scanf("%d", &numero);

	typedef struct materias{  //Creamos la estructura de materia con un nombre, nota y creditos
		char nombre[20];
		float nota;
		int creditos;
	}materia;

	materia *puntr;  //Esto es para almacenar elementos de tipo materia en la memoria
	puntr = malloc(sizeof(materia)*numero); //Reservamos un espacio en memoria del tamaño de estructuras * el numero de materias (Array de structuras en el heap)

	for(int i=0; i<numero; i++){  //Llenamos las estructuras

		printf("%s\n", "Ingrese el nombre de la materia");
		scanf("%19s", (puntr+i)->nombre);        //puntr+i = puntr[i] para acceder al elemento de la memoria
		printf("%s\n", "Ingrese la nota de la materia");
		scanf("%f", &(puntr+i)->nota);
		printf("%s\n", "Ingrese el numero de creditos de la materia");
		scanf("%d", &(puntr+i)->creditos);

	}

	printf("%s %s\t%s\t\n","Materia","Nota","Creditos");

	for(int i=0; i<numero; i++){
		printf("%s\t%2.2f\t%d \n",(puntr+i)->nombre,(puntr+i)->nota,(puntr+i)->creditos);
	}

	float promedio = 0, pro, totalcr = 0, cr, totalnotas;

 	for(int i=0; i<numero; i++){
		totalnotas = (puntr+i)->nota;
		totalcr += (float)(puntr+i)->creditos;
		cr = (puntr+i)->creditos;
		promedio = promedio + (totalnotas) * (cr);
	}
 	pro = promedio / totalcr;
 	printf("%s%2.2f\n","El promdio ponderado es ", pro);
 	free(puntr);

	return EXIT_SUCCESS;
}
