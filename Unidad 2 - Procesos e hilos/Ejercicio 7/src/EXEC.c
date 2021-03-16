/*
 * EXEC.c
 *
 *  Created on: Mar 14, 2021
 *      Author: juanpa
 */

 #include<stdio.h>
 #include<unistd.h>

 int main()
 {
     printf("Proceso %d\n", getpid());

     printf("I am EXEC.c called by execv() ");
     printf("\n");
     return 0;
 }
