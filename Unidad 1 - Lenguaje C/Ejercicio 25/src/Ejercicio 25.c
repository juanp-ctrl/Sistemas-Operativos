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
#define M 5
#define C 5
#define MAP(val,m,c) x*m+c

 int main(int argc, char* argv[]) {
	 int x = 2;
	 int y = MAP(x,M,C);
	 printf("y: %d", y);
	 return 0;
 }
