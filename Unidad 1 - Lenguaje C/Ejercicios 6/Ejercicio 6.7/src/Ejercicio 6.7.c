/*
 ============================================================================
 Name        : 7.c
 Author      : Juan Pablo Jiménez
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

struct estudiante{
	char nombre[40];
	int idestu;
	int añomatri;
	float nota;
};

int main(void) {

	char tecla;

	puts("!!!Hello Estudiante!!!");

	struct estudiante estu = {"Jose", 4, 2009, 4.5};
	struct estudiante *ptrestu;
	ptrestu = &estu;
	printf("Nombre estudiante: %s\nId: %d\nAño: %d\nNota: %f\n", ptrestu -> nombre, ptrestu->idestu, ptrestu->añomatri, ptrestu->nota);

	printf("Ingrese r si desea cambiar el contenido del estudiante, x si no\n");
	scanf("%c",&tecla);

	while(tecla == 'r'){

			printf("1.Para cambiar el nombre \n2.Para cambiar el id\n3.Para cambiar el año\n4.Para cambiar la nota\n");
			int n;
			scanf("%d",&n);
			switch (n){
			case 1:printf("Ingrese el nuevo nombre");
				scanf("%s",estu.nombre);
				break;
			case 2:printf("Ingrese el nuevo id");
					scanf("%d",&estu.idestu);
					break;
			case 3:printf("Ingrese el nuevo año");
					scanf("%d",&estu.añomatri);
					break;
			case 4:printf("Ingrese la nueva nota");
					scanf("%f",&estu.nota);
					break;
			default: printf("Opcion invalida");
					break;
			}

			printf("Nombre estudiante: %s\nId: %d\nAño: %d\nNota: %f\n", ptrestu -> nombre, ptrestu->idestu, ptrestu->añomatri, ptrestu->nota);

			scanf(" %c", &tecla);

	}

	printf("Hasta luego");

	return EXIT_SUCCESS;
}
