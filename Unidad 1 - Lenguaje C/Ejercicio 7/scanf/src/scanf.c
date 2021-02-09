/*
 ============================================================================
 Name        : scanf.c
 Author      : Juan Pablo Jiménez
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int num;
    char key;
    printf("Prueba a scanf. Ingrese el numero 325 y presione ENTER:\n");
    scanf("%d",&num);
    printf("Ingrese cualquier tecla para terminar y presione ENTER:\n");
    scanf(" %c",&key);

    printf("%d\t%c",num,key);

    return 0;
}
