/*
 ============================================================================
 Name        : Ejercicio.c
 Author      : Juan Pablo Jiménez
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

uint8_t arraycommon(int32_t *arr1, int32_t arr1size, int32_t *arr2, int32_t arr2size, int32_t *arrRes, int32_t arrResSize);

int main(void) {
	puts("!!!Elementos comunes de dos arreglos de enteros!!!");

	int size1, size2, sizer, n;
	puts("Ingrese el tamaño del primer arreglo");
	scanf("%d",&size1);
	int array1[size1];
	for(int i=0; i<size1; i++){
		printf("Ingrese un numero ");
		scanf("%d",&n);
		array1[i] = n;
	}

	puts("Ingrese el tamaño del segundo arreglo");
		scanf("%d",&size2);
		int array2[size2];
		for(int i=0; i<size2; i++){
			printf("Ingrese un numero ");
			scanf("%d",&n);
			array2[i] = n;
		}

	if(size1 <= size2){
		sizer = size1;
	}
	else{
		sizer = size2;
	}

	int32_t arrayr[sizer];

	arraycommon(array1, size1, array2, size2, arrayr, sizer);

	return EXIT_SUCCESS;
}

uint8_t arraycommon(int32_t *arr1, int32_t arr1size, int32_t *arr2, int32_t arr2size, int32_t *arrRes, int32_t arrResSize){

	int32_t n, cont;

	n = strcspn((char*)arr2, (char*)arr1);

	return 1;

}
