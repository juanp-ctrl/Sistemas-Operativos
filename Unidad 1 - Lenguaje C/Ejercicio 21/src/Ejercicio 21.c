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
	int array2[size2+1];

	for(int i=0; i<size2; i++){
		printf("Ingrese un numero ");
		scanf("%d",&n);
		array2[i] = n;
	}

	array2[size2] = -1;

	if(size1 <= size2){
		sizer = size1;
	}
	else{
		sizer = size2;
	}

	int32_t arrayr[sizer];

	for(int i=0; i<sizer; i++){
			arrayr[i] = -1;
		}

	printf("Se encontraron %d elementos iguales en los dos arreglos \n Arreglo : ", arraycommon(array1, size1, array2, size2, arrayr, sizer));

	int k = 0;
	while(arrayr[k] != -1){
		printf("%d|", arrayr[k]);
		k++;
	}

	return EXIT_SUCCESS;
}

uint8_t arraycommon(int32_t *arr1, int32_t arr1size, int32_t *arr2, int32_t arr2size, int32_t *arrRes, int32_t arrResSize){

	int num, j;
	int n = 0;
	for(int i=0; i<arr1size; i++){
		num = arr1[i];
		j = 0;

		while(arr2[j] != -1){

			if(arr2[j] == num){

				int k=0, l= 0;
				while(arrRes[k] != -1){
					if(arrRes[k] == arr2[j]){
						l++;
						break;
					}
					k++;
				}
				if(l==0){
					arrRes[n] = arr2[j];
					n++;
				}
				arr2[j] = -1;
				for(int i=j; i<arr2size-1; i++){
					arr2[i] = arr2[i+1];
				}
				break;
			}
			else{
				j++;
			}
		}
	}

	return n;

}
