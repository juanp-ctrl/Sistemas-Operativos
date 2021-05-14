/*
 * cliente.c
 *
 *  Created on: May 13, 2021
 *      Author: juanpa
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
 #include <arpa/inet.h>

 #define PORT 8888
 #define BUF_SIZE 128

 struct client_t{
     int socket;
     int estado;
 };

 void * leer(void *arg){

     struct client_t *client = ((struct client_t *)arg);

     ssize_t nBytes;
     char buf[BUF_SIZE];

     while(1){			//Leemos del servidor

    	 nBytes = read(client->socket, buf, BUF_SIZE);

         if(nBytes == 0){
             printf("Se ha cerrado el servidor\n");
             break;
         }

         else if(nBytes == -1){
             perror("Error al leer con el hilo");
             break;
         }

         else{
             printf("%s\n",buf);
         }

     }

     printf("Hilo de lectura terminado\n");

     client->estado = 0;
     return NULL;
 }

 int main(int argc, char *argv[]){

     char buf[BUF_SIZE];
     char nombre[BUF_SIZE];
     int status;
     int server_sd;
     pthread_t hilo;
     struct client_t client;

     printf("Ingresa tu nombre:\n");
     scanf("%s",nombre);
     printf("Bienvenido %s\n",nombre);

     // 1. ignoramos la señal sigpipe
     signal(SIGPIPE, SIG_IGN);

     // 2. Creamos el socket para el server
     server_sd = socket(AF_INET, SOCK_STREAM, 0);

     if (server_sd == -1) {
         perror("Error al crear el socket\n");
         exit(EXIT_FAILURE);
     }

     printf("Socket creado\n");

     //3. Connect to the server 127.0.0.1:PORT

     struct sockaddr_in addr;
     memset(&addr, 0, sizeof(addr));

     addr.sin_family = AF_INET;
     addr.sin_addr.s_addr = inet_addr("127.0.0.1");
     addr.sin_port = htons(PORT);

     status = connect(server_sd, (struct sockaddr*)&addr, sizeof(addr));		//Nos conectamos al servidor con la direccion dada

     if(status == -1){
         perror("Error al conectar con el servidor\n");
         close(server_sd);
         exit(EXIT_FAILURE);
     }

     printf("Conectado al servidor\n");

     // 4. Creación del hilo para leer
     client.socket = server_sd;
     client.estado = 1;
     printf("Hilo creado para leer del servidor\n");

     status = pthread_create(&hilo, NULL, &leer, &client);

     if(status == -1){
         perror("Error al crear el hilo");
         close(server_sd);
         exit(EXIT_FAILURE);
     }

     status = write(client.socket, nombre, strlen(nombre)+1);

	  if(status == -1){
		  perror("Error al enviar el nombre");
	  }

     while(1){		//Escribimos los mensajes

         if(client.estado == 0){
             printf("El servidor cerro el socket\n");
             break;
         }

         if (fgets(buf, BUF_SIZE, stdin) == NULL){
             printf("Entrada nula\n");
         }
         if( 0 == strncmp(buf,"/q",strlen("/q")) ){
             printf("Sesion cerrada\n");
             break;
         }

         if( buf[ strlen(buf)-1 ] == '\n') buf[ strlen(buf) - 1 ] = 0;

         status = write(client.socket, buf, strlen(buf)+1);

         if(status == -1){
             perror("Error al escribir en el servidor");
             break;
         }
     }

     close(client.socket);

     exit(EXIT_SUCCESS);
 }
