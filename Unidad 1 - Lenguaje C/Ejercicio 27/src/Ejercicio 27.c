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

 int main(int argc, char* argv[]) {

     #ifdef CONDITION
     printf("CODIGO IF\n");
     #else
     printf("CODIGO ELSE\n");
     #endif
     return 0;
 }
