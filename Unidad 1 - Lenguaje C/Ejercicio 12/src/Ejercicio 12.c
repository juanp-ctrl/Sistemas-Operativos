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
    char name[40];
    printf("What's your name? ");
    scanf("%39s", name);
    printf("Hello %s!\n", name);
	return EXIT_SUCCESS;
}
