/*
 ============================================================================
 Name        : Ejercicio.c
 Author      : Juan Pablo Jimenez
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

 #include<stdio.h>
 #include<stdlib.h>
 #include<unistd.h>

 int main()
 {
	 	 printf("Proceso %d\n", getpid());
         char *args[]={"./EXEC",NULL};  //Un arreglo de punteros de tipo char que termina con un NULL
         execv(args[0],args);  //Le pasamos el archivo a ejecutar y la lista de punteros de tipo char

         //Esto no se ejecuta ya que se remplaza con otro proceso
         printf("Ending-----");

     return 0;
 }
