#include <stdio.h>
#include <stdlib.h>

void printArr(int *parr, int tamañoArr);

int main(void){

    int arr[] = {1,2,3,4,5,6,7,8,9,10};

    int tamañoA = sizeof(arr)/sizeof(int);

    printArr(arr, tamañoA);

    /*for(int i = 0; i < sizeof(arr)/sizeof(int); i++){    //para conocer el tamaño del arreglo es el tamaño en bytes dividido los bytes de un entero
                                                        //entonces seria por ejemplo 40 / 4 ya que un entero es 4 bytes

        printf("arr[%d]: %d\n", i, arr[i]);    //otra forma de imprimir
    }

    return (0);*/
}

void printArr(int *parr, int tamañoArr){

    for(int i=0; i<tamañoArr; i++){
        printf("arr[%d]: %d\n", i, parr[i]);
    }
}

//En c el nombre del arreglo es la direccion del primer elemento del arreglo