/*
 ============================================================================
 Name        : Ejercicio.c
 Author      : Juan Pablo Jimenez
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <unistd.h>

int main(void) {
	pid_t hijo1;
	pid_t hijo2;

	hijo1 = fork();     //Creamos el proceso hijo
	if(wait(NULL) == hijo1){   //Si estamos en el proceso hijo su id sera 0 entonces no aplica pero si estamos en el padre
							   //el id del hijo sera igual al id que retorna el wait si el proceso sale bien
							   //de esta manera terminamos con el hijo1 y continuamos con la ejecucion del proceso del padre
		hijo2 = fork();   //Creamos el otro proceso hijo
		wait(NULL);		  //Esperamos haste que el hijo2 termine de ejecutarse
	}

	int fact = 0;
	for(int k=1; k<=10; k++){
		fact = k;
		for(int i=k-1; i>=1; i--){
			fact = fact * i;
		}
		printf("Proceso %d Factorial de %d es %d\n", getpid(), k, fact);
	}

	return EXIT_SUCCESS;
}
