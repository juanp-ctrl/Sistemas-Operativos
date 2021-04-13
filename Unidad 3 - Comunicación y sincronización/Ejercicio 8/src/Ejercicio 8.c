/*
 ============================================================================
 Name        : Ejercicio.c
 Author      : Juan Pablo Jiménez Heredia
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

 #include <sys/wait.h>
 #include <unistd.h>
 #include <stdlib.h>
 #include <stdio.h>
 #include <string.h>

 #define BUF_SIZE 10  //El tamaño del bufer es 10

 int main(int argc, char *argv[])
 {
     int pfd[2];		//Los identificadores del pipe
     char buf[BUF_SIZE];	//Una arreglo de caracteres de tamaño 10
     ssize_t numRead;		//Un numero entero que soporta el -1 llamado numRead, almacenamos cuanto leemos

     if (argc != 2 || strcmp(argv[1], "--help") == 0){  //Si el programa esta siendo mal usado le ayudamos al usuario
         printf("usage error: %s string\n", argv[0]);
         exit(EXIT_FAILURE);
     }


     if (pipe(pfd) == -1){			//Creamos el pipe con sus identificadores (el arreglo) si devuelve -1 hubo un error
         perror("pipe");
         exit(EXIT_FAILURE);
     }

     switch (fork())			//Hacemos un fork de este proceso
     {
     case -1:
         perror("fork");		//Si devuelve -1 hubo un error
         exit(EXIT_FAILURE);
     case 0:					//Si es 0 es por que estamos en la imagen del proceso del hijo
         if (close(pfd[1]) == -1)				//Cerramos el identificador de escritura del pipe (por que ya no vamos a escribir),
        	 	 	 	 	 	 	 	 	 	//vamos a leer y si -1 hubo un error
         {
             perror("close - child");
             exit(EXIT_FAILURE);
         }
         for (;;)				//Entramos en un ciclo infinito en donde vamos a leer del pipe e imprimir esto en el standart output
         {
             numRead = read(pfd[0], buf, BUF_SIZE);			//Vamos leyendo del pipe de a 10 caracteres a la vez (definimos BUF_SIZE = 10)
             												//lo leido hasta el momento lo almacenamos en la cadena de caracteres buf
             	 	 	 	 	 	 	 	 	 	 	 	//el número de bytes leido lo almacenamos en numRead,
             	 	 	 	 	 	 	 	 	 	 	 	//al llegar a 0 es por que no queda mas datos por leer

             if (numRead == -1)			//Si numRead es -1 es por error
             {
                 perror("read");
                 exit(EXIT_FAILURE);
             }

             if (numRead == 0)			//Si numRead es 0 es por que llego al final de los datos del pipe
                 break;
             if (write(STDOUT_FILENO, buf, numRead) != numRead)			//Vamos a escribir en el standard output lo que esta en el arreglo
            	 	 	 	 	 	 	 	 	 	 	 	 	 	 	//buf, le especificamos cuanto vamos a escribir, si esto retorna algo
            	 	 	 	 	 	 	 	 	 	 	 	 	 	 	//diferente al numero de caracteres del buf hubo un error
             {
                 perror("child - partial/failed write");
                 exit(EXIT_FAILURE);
             }
         }
         write(STDOUT_FILENO, "\n", 1);						//Le agregamos al standard output un salto de linea
         if (close(pfd[0]) == -1)							//Cerramos el identificador de lectura del pipe ya que no vamos a leer mas
         {
             perror("close");
             exit(EXIT_FAILURE);
         }

         exit(EXIT_SUCCESS);

     default:			//Al ser otro numero que no sea 0 o 1 es el proceso del padre
         if (close(pfd[0]) == -1)				//Cerramos el identificador de lectura del pipe ya que no lo usamos, solo escribimos
         {
             perror("close - parent");
             exit(EXIT_FAILURE);
         }

         if (write(pfd[1], argv[1], strlen(argv[1])) != strlen(argv[1]))		//Escribimos en el identificador de escritura del pipe
        	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	//el string pasado como argumento
         {
             perror("parent - partial/failed write");
             exit(EXIT_FAILURE);
         }
         if (close(pfd[1]) == -1)			//Cerramos el identificador de escritura del pipe para que no se quede esperando escritura
         {
             perror("close");
             exit(EXIT_FAILURE);
         }
         wait(NULL);						//Esperamos a que el hijo termine su ejecucion
         exit(EXIT_SUCCESS);
     }
 }
