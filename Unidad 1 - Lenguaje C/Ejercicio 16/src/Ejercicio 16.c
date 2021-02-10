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

int main(void) {
	int *p;
	int (*ptr)[5];
	int arr[5];

	p = arr;
	ptr = &arr;
	printf("p = %p, ptr = %p\n", p, ptr);
	p++;
	ptr++;
	printf("p = %p, ptr = %p\n", p, ptr);
	return 0;
}
