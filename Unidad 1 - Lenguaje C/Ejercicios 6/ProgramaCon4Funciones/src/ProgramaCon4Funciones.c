/*
 ============================================================================
 Name        : ProgramaCon4Funciones.c
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
	puts("!!!Sumatoria de dos numeros!!!\n");
	printf("Ingrese el nombre del archivo a editar \n");
	FILE *puntero;
	char archivo[20], nombre[20];
	int n1, n2, total;

	scanf("%s",archivo);

	puntero = fopen(archivo, "r+");

	if(puntero == NULL){
		printf("Error al abrir el archivo");
	}
	else{
		if(fgets(nombre, 20, puntero) == NULL){
			printf("El archivo esta vacio");
		}
		else{
			fscanf(puntero,"%d\n%d",&n1,&n2);
			total = n1 + n2;
			fprintf(puntero,"\n%s%d","El total es: ",total);
			fputs("\nArchivo editado", puntero);
			printf("Bienvenido %s \nEl numero 1 es %d y el numero 2 es %d", nombre, n1, n2);
		}
	}
	fclose(puntero);

	return EXIT_SUCCESS;
}
