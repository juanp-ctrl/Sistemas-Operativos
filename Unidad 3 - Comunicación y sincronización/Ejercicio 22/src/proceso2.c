/*
 * proceso2.c
 *
 *  Created on: Apr 24, 2021
 *      Author: juanpa
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

     int shm_fd = shm_open("memory_compartida", O_RDONLY, 0600);

     if (shm_fd < 0) {
         perror("shm memory error: ");
         exit(EXIT_FAILURE);
     }

     fprintf(stdout, "Shared memory es abierto con fd: %d\n", shm_fd);

     void* map = mmap(NULL, SH_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

     if (map == MAP_FAILED) {
         perror("Mapping failed: ");
         exit(EXIT_FAILURE);
     }

     char *ptr = (char *)map;
     fprintf(stdout, "El contenido del archivo de memoria compartida es: %s\n", ptr);


     if (munmap(ptr, SH_SIZE) < 0) {
         perror("Unmapping failed: ");
         exit(EXIT_FAILURE);
     }


     if (close(shm_fd) < 0) {
         perror("Closing shm failed: ");
         exit(EXIT_FAILURE);
     }

     if (shm_unlink("memory_compartida") < 0) {		//Eliminamos el descriptor del archivo de memoria compartida
         perror("Unlink failed: ");
         exit(EXIT_FAILURE);
     }

     exit(EXIT_SUCCESS);
 }
