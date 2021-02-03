#include <stdio.h>
#include <stdlib.h>

int main(void){

    char nombres[3][20] = {"fulano", "megano", "perano"};

    char i;
    char *a;
    char (*b)[20];  //arreglo de puntero

    //nombres es la direccion del primen elemento

    a = (char *) nombres; //a almacena direcciones de char y nombres al ser int * lo casteamos


    return (0);

}