/*
 ============================================================================
 Name        : 6.c
 Author      : Juan Pablo Jiménez
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	puts("!!!Area del triangulo!!!");

	typedef struct puntot{
		int p1;
		int p2;
	}punto;

	punto punto1;
	punto punto2;

	printf("Ingrese la primera coordenada del primer punto");
	scanf("%d",&punto1.p1);
	printf("Ingrese la segunda coordenada del primer punto");
	scanf("%d",&punto1.p2);

	printf("Ingrese la primera coordenada del segundo punto");
	scanf("%d",&punto2.p1);
	printf("Ingrese la segunda coordenada del segundo punto");
	scanf("%d",&punto2.p2);

	int area = abs(punto1.p1-punto2.p1)*abs(punto1.p2-punto2.p2);

	printf("El area es %d\n", area);

	return EXIT_SUCCESS;
}
