#include <stdio.h>

int main()
{
    printf("%d",getchar());
    
    char c;
    do{
        c = getchar(); //guardamos el primer caracter obtenido del flujo de caracteres terminados en nueva linea
        putchar(c); //imprime el caracter
        putchar('\n'); //Salta de linea
    }while(c!='X'); 
    
    return 0;
}