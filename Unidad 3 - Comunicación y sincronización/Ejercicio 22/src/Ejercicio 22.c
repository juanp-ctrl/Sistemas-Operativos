/*
 ============================================================================
 Name        : Ejercicio.c
 Author      : Juan Pablo Jiménez Heredia
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <sys/mman.h>
 #include <sys/stat.h>        /* For mode constants */
 #include <fcntl.h>           /* For O_* constants */
 #include <string.h>
 #include <unistd.h>
 #include <sys/types.h>


 #define SH_SIZE 16

 int main(int argc, char * argv[]){

     int shm_fd = shm_open("memory_compartida", O_CREAT | O_RDWR, 0600);		//Creamos el shared-memory-object

     if (shm_fd < 0) {
         perror("shm memory error: ");
         exit(EXIT_FAILURE);
     }

     fprintf(stdout, "La memoria compartida es creada con el descriptor de archivo: %d\n", shm_fd);

     if (ftruncate(shm_fd, SH_SIZE * sizeof(char)) < 0) {		//Truncamos el archivo a 16 bytes
         perror("Truncation failed: ");
         exit(EXIT_FAILURE);
     }

     fprintf(stdout, "La region de memoria fue truncada.\n");

     void* map = mmap(NULL, SH_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);		//Creamos el mapa de memoria

     if (map == MAP_FAILED) {
         perror("Mapping failed: ");
         exit(EXIT_FAILURE);
     }

     char* ptr = (char*)map;
     ptr[0] = 'A';
     ptr[1] = 'B';
     ptr[2] = 'C';
     ptr[3] = '\n';
     ptr[4] = '\0';

     fprintf(stdout, "Los datos han sido escritos en la memoria compartida.\n");

     if (munmap(ptr, SH_SIZE) < 0) {		//Removemos los mapas de memoria de las paginas que contienen alguna direccion comenzando en esta
         perror("Unmapping failed: ");
         exit(EXIT_FAILURE);
     }


     if (close(shm_fd) < 0) {		//Cerramos el descriptor del archivo
         perror("Closing shm failed: ");
         exit(EXIT_FAILURE);
     }

     exit(EXIT_SUCCESS);
 }
