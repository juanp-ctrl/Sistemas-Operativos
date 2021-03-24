/*
 * p2.c
 *
 *  Created on: Mar 22, 2021
 *      Author: juanpa
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){

	FILE *pfile, *pfout;
	char array_lineas[100][26];

	printf("%s", argv[1]);

	 pfile = fopen(argv[0], "r");
	 pfout = fopen(argv[1], "w");

	  if(pfile == NULL){
		  perror("Archivo 1 no abierto");
		  return 1;
	  }

	  if(pfout == NULL){
		  perror("Archivo 2 no abierto");
		  return 1;
	  }

	  int i = 0;
	  while(fgets(array_lineas[i], 25, pfile) != NULL){
		  i++;
	  }

	  for(int i=99; i>=0; i--){
		  fprintf(pfout, "%s", array_lineas[i]);
	  }

	  fclose(pfile);
	  fclose(pfout);

	return EXIT_SUCCESS;
}
