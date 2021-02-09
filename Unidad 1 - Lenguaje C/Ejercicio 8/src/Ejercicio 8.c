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

int main(void)
{
    int a = 10;
    printf("enter a number: ");   //Scanf no lee lo que no puede parsear
    scanf("%d", &a);
    printf("You entered %d.\n", a);
	return EXIT_SUCCESS;
}
