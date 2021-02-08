/*
 ============================================================================
 Name        : heap.c
 Author      : Juan Pablo Jiménez
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	puts("!!!Hello World!!!");

	int *punt;
	punt = malloc(sizeof(int)*10);

	for(int i=0; i<10; i++){
		punt[i] = i;
	}
	for(int i=0; i<10; i++){
		printf("%d\n",punt[i]);
	}

	return EXIT_SUCCESS;
}
