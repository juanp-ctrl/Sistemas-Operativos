#include <stdio.h>

int main(void){
    
    char c;
    do{
        
        int op1, op2, op, resultado;

        printf("%s\n","Ingresa el primer operando");
        scanf("%d",&op1);

        printf("%s\n","Ingresa el segundo operando");
        scanf("%d",&op2);

        printf("%s\n","Ingresa la operación a realizar \n1.Suma \n2.Resta \n3.Dividir \n4.Multiplicar");

        scanf("%d",&op);
        switch (op)
        {
        case 1:
            resultado = op1 + op2;
            printf("%s%d\n","El resultado es ",resultado);
            break;
        
        case 2:
            resultado = op1 - op2;
            printf("%s%d\n","El resultado es ",resultado);
            break;

        case 3:
            resultado = op1 / op2;
            printf("%s%d\n","El resultado es ",resultado);
            break;

        case 4:
            resultado = op1 * op2;
            printf("%s%d\n","El resultado es ",resultado);
            break;
        
        default: printf("%s\n","Entrada no valida");
            break;
        }
        
        printf("%s\n","Ingresa q para terminar, otra tecla para continuar");
        scanf(" %c", &c);   //segun lo que lei el espacio antes del formato %c es para que se salte el caracter que hay en el buffer y capture el nuevo caracter

    }while (c!='q');
    

    return (0);
}