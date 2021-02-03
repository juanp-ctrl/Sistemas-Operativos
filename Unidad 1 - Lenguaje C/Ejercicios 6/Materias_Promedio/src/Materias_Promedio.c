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

	char materias[3*numero][10];

	for(int i=0; i<3*numero; i++){

		int temp = i;

		char cadena[8];

		printf("%s\n", "Ingrese el nombre de la materia");
		scanf("%s", &cadena);
		strcpy(materias[i],cadena);

		printf("%s\n", "Ingrese la nota de la materia");
		scanf("%s", &cadena);
		strcpy(materias[++i],cadena);

		printf("%s\n", "Ingrese el numero de creditos de la materia");
		scanf("%s", &cadena);
		strcpy(materias[++i],cadena);

	}

	int tm = 0;
	printf("%s\t%s\t%s\t\n", "Materia","Nota","Creditos");
	for(int i=0; i<3*numero; i++){
		tm++;
		if(tm <= 3){
			printf("%s\t", materias[i]);
		}
		if(tm == 3){
			printf("\n");
			tm = 0;
		}
	}


	float promedio = 0, pro, totalcr, cr, totalnotas, tmr;
	for(int i=0; i<3*numero; i++){
		tmr++;
		if(tmr==2){
			totalnotas = *materias[i]-48;
		}
		if(tmr==3){
			totalcr += (*materias[i]-48);
			cr = *materias[i]-48;
			promedio = promedio + (totalnotas) * (cr);
			tmr = 0;
		}
	}
	pro = promedio / totalcr;

	printf("%s%2.2f\n","El promdio ponderado es ", pro);


	return EXIT_SUCCESS;
}
