#include <stdio.h>
#include <unistd.h>

//Cadena para guardar caracteres, como el String 
char nombre[50];

/*
Comentario
de varias lineas
*/
int main(){
    int pid = getpid();
    printf("Hola Mundo");
    printf("Ingrese su nombre aqui: ");
    scanf("%s", nombre);   //%s para formato  de cadena de caracteres
    printf("Hola %s, su id de procesos es %d", nombre, pid);  //%d es para formato de numero entero
    return 0;
}
