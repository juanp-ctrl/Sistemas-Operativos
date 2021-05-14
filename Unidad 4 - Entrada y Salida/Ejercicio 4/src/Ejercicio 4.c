/*
 ============================================================================
 Name        : Ejercicio.c
 Author      : Juan Pablo Jiménez H
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

 #include <stdio.h>
 #include <string.h>
 #include <errno.h>
 #include <unistd.h>
 #include <stdlib.h>
 #include <pthread.h>
 #include <sys/socket.h>
 #include <netinet/in.h>
 #include <signal.h>

 #define PUERTO 6666
 #define BUF_SIZE 128

 struct client_t{			//Estructura del cliente en donde guardamos el socket y el estado
     int socket;
     int rxState;
 };

 void* leer(void *arg){

     struct client_t *client = ((struct client_t *)arg);
     ssize_t nBytes;
     char buf[BUF_SIZE];

     while(1){		//Leemos del cliente

         nBytes = read(client->socket, buf, BUF_SIZE);		//Leemos del archivo descriptor del socket y lo guardamos en buf

         if(nBytes == 0){
             printf("El cliente ha cerrado la conexión\n");
             break;
         }

         else if(nBytes == -1){
             perror("Error al leer del socket del cliente");
             break;
         }
         else{
             printf("Cliente: %s\n", buf);			//Imprimimos el mensaje del cliente
         }
     }

     printf("Hilo de lectura terminado\n");

     client->rxState = 0;
     return NULL;
 }


 int main(int argc, char *argv[]){

     char buf[BUF_SIZE];
     int status;
     int enable = 1;
     int server_fd;
     int client_fd;
     pthread_t hilo;
     struct client_t client;

     // 1. Ignoramos los posibles errores de SIGPIPE asignandole SIG_IGN que indica que esta señal la ignoraremos
     signal(SIGPIPE, SIG_IGN);

     // 2. Creamos el socket del servidor usando IPv4
     server_fd = socket(AF_INET, SOCK_STREAM, 0);

     if (server_fd == -1) {
         perror("Error al crear el socket del servidor\n");
         exit(EXIT_FAILURE);
     }
     printf("Socket creado\n");

     // 3. Usamos setsockopt para controlar el comportamiento del socket del servidor
     // Especificamos que sera a nivel de socket con SOL_SOCKET
     // Y con la opcion SO_REUSEADDR alteramos el uso normal del bind() indicamos que permita reusar el mismo puerto con diferentes IPs
     // Y el servidor se puede reiniciar sin tener que cerrar la conexion con todos los clientes
     status = setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (int *) &enable, sizeof(enable));	//Retorna 0 en success y -1 en error

     if (status == -1){
         perror("Error al alterar el bind en el socket del servidor");
     }

     //4. Le asignamos cualquier direccion al socket del servidor
     struct sockaddr_in direccion;

     memset(&direccion, 0, sizeof(direccion));		//Llenamos la estructura con ceros

     direccion.sin_family = AF_INET;
     direccion.sin_addr.s_addr = INADDR_ANY;
     direccion.sin_port = htons(PUERTO);

     status = bind(server_fd, (struct sockaddr*)&direccion, sizeof(direccion));

     if (status == -1) {
         perror("Error en funcion bind");
         close(server_fd);
         exit(EXIT_FAILURE);
     }

     printf("Bind hecho correctamente\n");


     // 5.Indicamos que este socket sera pasivo, aceptara peticiones de conexión, el tamaño de la lista es 50

     status = listen(server_fd, 50);

     if (status == -1) {
         perror("Error al colocar el socket en listen");
         close(server_fd);
         exit(EXIT_FAILURE);
     }

     printf("Servidor escuchando\n");

     while(1){		// Ciclo infinito para aceptar peticiones

         printf("Esperando por un cliente\n");

         client_fd = accept(server_fd, NULL, NULL);			//Retorna el archivo descriptor del socket del cliente en el backlog

         if(client_fd == -1){
             perror("Error al aceptar la petición del cliente");
             close(server_fd);
             exit(EXIT_FAILURE);
         }

         printf("Cliente conectado");

         // 7. Llenamos la estructura cliente con el fd, el estado y creamos el hilo para recibir mensajes de este cliente
         client.socket = client_fd;
         client.rxState = 1;

         printf("Hilo para leer\n");

         status = pthread_create(&hilo, NULL, &leer, &client);

         if(status == -1){
             perror("Error al leer usando el hilo");
             close(server_fd);
             exit(EXIT_FAILURE);
         }

         while(1){			//Enviamos mensaje al cliente

             if(client.rxState == 0){
                 printf("Cliente cerro el socket\n");
                 break;
             }

             if (fgets(buf, BUF_SIZE, stdin) == NULL){
                 printf("La entrada es nula\n");
             }

             if(buf[strlen(buf)-1] == '\n'){
            	 buf[strlen(buf) - 1] = 0;
             }

             status = write(client.socket, buf, strlen(buf)+1);		//Escribimos en el archivo decriptor del socket

             if(status == -1){
                 perror("Error al escribir en el cliente");
                 break;
             }

         }

         close(client.socket);

     }

     exit(EXIT_SUCCESS);
 }
