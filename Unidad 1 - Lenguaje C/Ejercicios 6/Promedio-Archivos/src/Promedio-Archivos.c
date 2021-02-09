/*
 ============================================================================
 Name        : Promedio-Archivos.c
 Author      : Juan Pablo Jiménez
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {

	char linea[20];
	char ca;
	int cont = 0, p = 0, n = 0;

	FILE *puntero;
	puntero = fopen("input.txt","r");

	while(feof(puntero) == 0){

		ca = fgetc(puntero);

		if(ca == '\n'){
			cont++;
		}
	}
	fclose(puntero);
	puntero = fopen("input.txt","r");

	typedef struct materias{
		char nombre[20];
		float nota;
		int creditos;
	}materia;

	cont = (cont-1)/3;
	materia *puntr;
	puntr = malloc(sizeof(materia)*cont);

	fgets(linea,20,puntero);

	materia sub;
	materia *punt;
	punt = &sub;

	while(1){

		ca = fgetc(puntero);

		if(ca == ':'){
			n++;

			if(n == 1){
				fscanf(puntero, "%s\n", sub.nombre);
			}
			if(n == 2){
				fscanf(puntero, "%f\n", &sub.nota);
			}
			if(n == 3){
				fscanf(puntero, "%i\n", &sub.creditos);
				puntr[p++] = *punt;
				n = 0;
			}

		}
		if(ca == EOF){
			break;
		}
	}
	fclose(puntero);

	FILE *archivo = fopen("notas.txt","w");

	fprintf(archivo, "%s\n", "Archivo de salida:");
	fprintf(archivo, "%s\t%s\t%s\n","Materia","Nota","Creditos");

	int gana = 0, pierde = 0;

	for(int i=0; i<cont; i++){
		materia sub;
		materia *punt;
		sub = puntr[i];  //Cargamos la estructura materia con el contenido del heap
		punt = &sub;  //Usamos el punteroç
		if((punt)->nota > 3){
			gana ++;
		}
		else{
			pierde ++;
		}
		fprintf(archivo, "%s\t%2.2f\t%d\n",(punt)->nombre,(punt)->nota,(punt)->creditos);
	}

	float promedio = 0, pro, totalcr = 0, cr, totalnotas;

	for(int i=0; i<cont; i++){
		materia sub;
		materia *punt;
		sub = puntr[i];
		punt = &sub;
		totalnotas = (punt)->nota;
		totalcr += (float)(punt)->creditos;
		cr = (punt)->creditos;
		promedio = promedio + (totalnotas) * (cr);
	}
	pro = promedio / totalcr;
	fprintf(archivo, "%s%d\n", "Total de materias: ", cont);
	fprintf(archivo, "%s%d\n", "Materias ganadas: ", gana);
	fprintf(archivo, "%s%d\n", "Materias perdidas: ", pierde);
	fprintf(archivo, "%s%2.2f\n","El promdio ponderado es ", pro);

	fclose(archivo);
	free(puntr);

	return EXIT_SUCCESS;
}
