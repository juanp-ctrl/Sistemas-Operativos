/*
 ============================================================================
 Name        : Materias_Promedio.c
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

	materia *puntr;
	puntr = malloc(sizeof(materia)*numero); //Reservamos un espacio en memoria del tamaño de estructuras * el numero de materias

	for(int i=0; i<numero; i++){  //Llenamos las estructuras

		materia subject;
		materia *punt;
		punt = &subject;

		printf("%s\n", "Ingrese el nombre de la materia");
		scanf("%s", subject.nombre);
		printf("%s\n", "Ingrese la nota de la materia");
		scanf("%f", &subject.nota);
		printf("%s\n", "Ingrese el numero de creditos de la materia");
		scanf("%d", &subject.creditos);

		puntr[i] = *punt;   //Guardamos en el heap el contenido del puntero (la estructura)
	}

	printf("%s %s\t%s\t\n","Materia","Nota","Creditos");

	for(int i=0; i<numero; i++){
		materia sub;
		materia *puntero;
		sub = puntr[i];  //Cargamos la estructura materia con el contenido del heap
		puntero = &sub;  //Usamos el puntero
		printf("%s\t%2.2f\t%d \n",(puntero)->nombre,(puntero)->nota,(puntero)->creditos);
	}

	float promedio = 0, pro, totalcr = 0, cr, totalnotas;

 	for(int i=0; i<numero; i++){
		materia sub;
		materia *puntero;
		sub = puntr[i];
		puntero = &sub;
		totalnotas = (puntero)->nota;
		totalcr += (float)(puntero)->creditos;
		cr = (puntero)->creditos;
		promedio = promedio + (totalnotas) * (cr);
	}
 	pro = promedio / totalcr;
 	printf("%s%2.2f\n","El promdio ponderado es ", pro);

	return EXIT_SUCCESS;
}
