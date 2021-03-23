/*
 * Creacion_Input.c
 *
 *  Created on: Mar 22, 2021
 *      Author: juanpa
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

	FILE *ptr;

	ptr = fopen("input.txt", "w");

	char titulo[] = {"Texto  "};

	srand((int)time(NULL));

	for(int i=0; i<100; i++){
		titulo[5] = (rand() % 26+65);
		titulo[6] = (rand() % (57-48)+1+48);
		fprintf(ptr, "%s %d\n", titulo, (-1000 + rand() % (1000 -(-1000) +1)));
	}

	return EXIT_SUCCESS;
}
