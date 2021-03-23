/*
 * p2.c
 *
 *  Created on: Mar 22, 2021
 *      Author: juanpa
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

	FILE *pfile, *pfout;
	char array_lineas[100][26];

	 pfile = fopen("input.txt", "r");
	 pfout = fopen("outputP2.txt", "w");

	  if(pfile == NULL){
		  perror("Archivo no abierto");
		  return 1;
	  }

	  if(pfout == NULL){
		  perror("Archivo no abierto");
		  return 1;
	  }

	  int i = 0;
	  while(fgets(array_lineas[i], 25, pfile) != NULL){
		  i++;
	  }

	  for(int i=99; i>=0; i--){
		  printf("%s", array_lineas[i]);
	  }

	return EXIT_SUCCESS;
}
