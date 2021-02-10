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
#include <string.h>

int main(void)
{
    char name[10];
    printf("What's your name? ");
    if (fgets(name, 10, stdin))
    {
        name[strcspn(name, "\n")] = 0;
        printf("Hello %s!\n", name);
    }
	return EXIT_SUCCESS;
}
