/*
 ============================================================================
 Name        : Ejercicio.c
 Author      : Juan Pablo Jimenez
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	pid_t pid_hijo;

	printf("El pid de este programa es: %d\n", (int)getpid());
	pid_hijo = fork(); //duplicamos este proceso

	switch(pid_hijo){
	case -1:
		puts("Error");
		return -1;
	case 0:
		puts("Proceso hijo");
		printf("Soy el hijo, PID es %d\n", (int)getpid());
		break;
	default:
		printf("Proceso padre: proceso hijo con PID %d creado \n", (int)pid_hijo);
	}

	printf("Soy el proceso %d, bye\n", (int)getpid()); //esto se ejecuta en ambos procesos
	exit(EXIT_SUCCESS); //llamado al sistema exit

}
