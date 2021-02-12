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

 char nombres[3][20] = {"fulano","mengano","perano"};

 int main (void){

     char *a;  //Puntero de variables tipo char
     char (*b)[20];  //Puntero de arrays tipo char max 20
     char *c;
     char (*d)[3][20]; //punt array de 3 arrays de max 20

     a = &nombres[0][0];  //Direccion del primer caracter del primer array
     printf("el nombre es %s \n", a);
     b = nombres;  //Guardamos el primer caracter de cada array
     c = &nombres[0][0];  //Lo mismo que a
     d = &nombres;  //Guardamos el primer caracter de cada array en el primer array del puntero

     for(int i = 0; i < 3; i++ ){
         printf("char (*)[] el nombre[%d] es %s \n", i , (char * ) (b+i));
         printf("char *: el nombre[%d] es %s \n", i , (char * ) ( c + (i*2) ));  //Imprime el array desde el caracter + i*2
         printf("char (*)[][]: el nombre[%d] es %s \n", i , (char * ) (d+i));
     }
     return 0;
 }
