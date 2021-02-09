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
    int a;
    printf("enter a number: ");
    int n = scanf("%d", &a);
    printf("%d",n);
    while (scanf("%d", &a) != 1)  //la conversion no se realiza si es algo que no sea numeros y en este caso devuelve 0
    {
        // input was not a number, ask again:
        printf("enter a number: ");
    }
    printf("You entered %d.\n", a);
	return EXIT_SUCCESS;
}
