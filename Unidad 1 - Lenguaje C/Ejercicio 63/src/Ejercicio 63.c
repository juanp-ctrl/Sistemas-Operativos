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
     char *ptr = malloc(20*sizeof(char));
     free(ptr);
     return 0;
 }
