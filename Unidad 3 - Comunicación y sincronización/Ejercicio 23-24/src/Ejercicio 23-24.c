 #include <stdio.h>
 #include <stdint.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <fcntl.h>
 #include <errno.h>
 #include <string.h>
 #include <sys/mman.h>
 #include <sys/wait.h>
 #include <semaphore.h>

 #define SH_SIZE 4

 int shared_fd = 0;

 int32_t* contador = NULL;
 sem_t* semaforo = NULL;

 void init_control_mechanism() {

     semaforo = sem_open("semaforo", O_CREAT, 0600, 1);		//Creamos el semaforo

     if (semaforo == SEM_FAILED) {	//Si falla
         perror("Opening the semaphore failed: ");
         exit(EXIT_FAILURE);
     }

 }

 void shutdown_control_mechanism() {

     if (sem_close(semaforo) < 0) {		//Cerramos el semaforo
         perror("Closing the semaphore failed: ");
         exit(EXIT_FAILURE);
     }

     if (sem_unlink("sem0") < 0) {		//Eliminamos el semaforo
         perror("Unlinking failed: ");
         exit(EXIT_FAILURE);
     }
 }

 void init_shared_resource() {

     shared_fd = shm_open("shm0", O_CREAT | O_RDWR, 0600);		//Creamos el archivo de memoria compartida

     if (shared_fd < 0) {
         perror("Failed to create shared memory: ");
         exit(EXIT_FAILURE);
     }

     fprintf(stdout, "La memoria compartida es creada con fd: %d\n", shared_fd);

 }

 void shutdown_shared_resource() {

     if (shm_unlink("shm0") < 0) {
         perror("Unlinking shared memory failed: ");
         exit(EXIT_FAILURE);
     }

 }

 void inc_counter() {

     usleep(1);

     sem_wait(semaforo);		//Bloqueamos con el semaforo
     int32_t temp = *contador;

     usleep(1);
     temp++;

     usleep(1);
     *contador = temp;

     sem_post(semaforo);		//Desbloqueamos con el semaforo
     usleep(1);

 }


 int main(int argc, char** argv) {

     init_shared_resource();
     init_control_mechanism();

     if (ftruncate(shared_fd, SH_SIZE * sizeof(char)) < 0) {
         perror("Truncation failed: ");
         exit(EXIT_FAILURE);
     }

     fprintf(stdout, "La region de memoria ha sido truncada.\n");

     void* map = mmap(0, SH_SIZE, PROT_WRITE, MAP_SHARED, shared_fd, 0);

     if (map == MAP_FAILED) {
         perror("Mapping failed: ");
         exit(EXIT_FAILURE);
     }

     contador = (int32_t*)map;
     *contador = 0;

     pid_t pid = fork();

     if (pid) { // The parent process

         inc_counter();
         fprintf(stdout, "Proceso padre, contador = %d.\n", *contador);
         int status = -1;
         wait(&status);

         fprintf(stdout, "El proceso hijo termina con status %d.\n", status);

     } else { // The child process

         inc_counter();
         fprintf(stdout, "Proceso hijo, contador = %d.\n", *contador);

     }


     if (munmap(contador, SH_SIZE) < 0) {
         perror("Unmapping failed: ");
         exit(EXIT_FAILURE);
     }

     if (close(shared_fd) < 0) {
         perror("Closing shared memory fd failed: ");
         exit(EXIT_FAILURE);
     }

     if (pid) {
         shutdown_shared_resource();
         shutdown_control_mechanism();
     }

     exit(EXIT_SUCCESS);
 }
