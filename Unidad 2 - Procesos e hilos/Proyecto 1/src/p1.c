/*
 * p1.c
 *
 *  Created on: Mar 22, 2021
 *      Author: juanpa
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char *argv[]){

	  FILE *pfile, *pfout;

	  pfile = fopen(argv[1], "r");
	  pfout = fopen(argv[2], "w");
	  char titulo[21];
	  int valor;
	  char entrada[26];
	  char array_titulos[2000][21];

	  memset(array_titulos, '\0', 42000*sizeof(char));  //Rellenamos todo el array con el caracter que inica final de cadena
	  	  	  	  	  	  	  	  	  	  	  	  	    //de esta forma sabemos si existe o no el valor
	  if(pfile == NULL){
		  perror("Archivo no abierto");
		  return 1;
	  }

	  while(fgets(entrada, 25, pfile) != NULL){
		  sscanf(entrada, "%20s %d", titulo, &valor);
		  if(valor < 0){
			  valor = abs(valor) + 1000;
		  }
		  strcpy(array_titulos[valor], titulo);
	  }

	  for(int i=999; i>=0; i--){
		  if(strcmp("\0",array_titulos[i]) != 0){
			  fprintf(pfout, "%s %d\n", array_titulos[i], i);
		  }
	  }
	  for(int i=1001; i<2000; i++){
		  if(strcmp("\0",array_titulos[i]) != 0){
			  fprintf(pfout, "%s -%d\n", array_titulos[i], i-1000);
		  }
	  }

	  fclose(pfile);
	  fclose(pfout);

	  return EXIT_SUCCESS;
}
