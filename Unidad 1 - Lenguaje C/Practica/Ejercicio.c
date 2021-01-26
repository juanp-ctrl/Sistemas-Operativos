#include <stdio.h>  //Incluimos el prototipo de las funciones de input y output
#include <stdlib.h>

void functionPointer(int *, int); //Definimos el prototipo de la funcion, necesita 

int main(void){

    int variable = 20;
    printf("variable = %d\n", variable);

    //Con el asterisco almacenamos direcciones y con & obtenemos la direccion de la variable
    //El puntero puede cambiar la direccion de la variable
    int *pvariable = &variable;

    *pvariable = 30;

    printf("Variable = %d\n", variable);

    return EXIT_SUCCESS;
}

void functionPointer(int *pvar, int value){

    *pvar = (*pvar) + value;
}

/*
El puntero es donde guardamos la direccion de la memoria
podemos usar el puntero para interactuar con la variable
*/