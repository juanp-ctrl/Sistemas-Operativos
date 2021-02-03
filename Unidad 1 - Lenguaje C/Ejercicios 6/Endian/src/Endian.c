/*
 ============================================================================
 Name        : Endian.c
 Author      : Juan Pablo Jiménez
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>

#define LITTLE_ENDIAN 0
#define BIG_ENDIAN 1

int machineEndianness() {
int i = 1;
char *p = (char *) &i;
if (p[0] == 1) // Lowest address contains the least significant byte
return LITTLE_ENDIAN;
else
return BIG_ENDIAN;
}
int main() {
if(machineEndianness())
printf("Big endian\n");
else
printf("Little endian\n");
return 0;
}
