/*
 ============================================================================
 Name        : 8_Apuntadores.c
 Author      : Juan Pablo Jiménez
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

void f1(int, int *, int *);

int main(void) {
  int d1 = 3, d2 = 1, d3 = 4;
  printf("d1=%d, d2=%d, d3=%d\n",d1,d2,d3);

  f1(--d2,&d3,&d1);

  printf("d1=%d, d2=%d, d3=%d\n",d1,d2,d3);
  return (0);
}

void f1(int x,int *y, int *z) {
  *y = x + *z;
  *z = --(*y);
  x = *y - *z;
}

