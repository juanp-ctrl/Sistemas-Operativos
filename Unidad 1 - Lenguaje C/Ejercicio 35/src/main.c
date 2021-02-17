/*
 * main.c
 *
 *  Created on: Feb 16, 2021
 *      Author: juanpa
 */


 #include "file1.h"
 #include <stdio.h>

 int main(int argc, char* argv[]) {
     int a = suma(4, 5);
     int b = multiplicacion(9, a);
     printf("el valor de b es %d", b);
     return 0;
 }
