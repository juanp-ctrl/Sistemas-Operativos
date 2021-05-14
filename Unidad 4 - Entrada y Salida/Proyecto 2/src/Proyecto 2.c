/*
 ============================================================================
 Name        : Proyecto.c
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

#define PORT 8888
#define BUF_SIZE 128

int maxC = 10, cont = 0;
struct client_t* client;

struct client_t{
    int socket;
    char nombre [BUF_SIZE];
    int estado;
    int conectado;
    int numClientes;
};

void *comandos(void *arg){
   char comando [32], cliente [32], buf[BUF_SIZE];
   int status, control, encontro = 0;

   while(strcmp(comando,"exit") != 0){

       printf("\nComandos:\n/cl para ver los clientes\n/del para desconectar un cliente\n");

       scanf("%s",comando);
       if (strcmp(comando,"/del") == 0){

           scanf("%s",cliente);
           for(int i=0; i<=maxC; i++){

               if(strcmp((client+i)->nombre,cliente) == 0 && (client+i)->conectado == 1){

                   (client+i)->conectado = 0;
                   (client+i)->estado = 0;
                   cont--;
                   control=i;
                   encontro=1;
                   break;
               }
           }

           if(encontro==1){

               for(int i=0; i<=maxC; i++){

            	   if((client+i)->conectado == 1 && (client+i)->numClientes != control ){

                       strcpy(buf, (client+control)->nombre);
                       strcat(buf, " ha abandonado el chat\n");
                       status = write((client+i)->socket,buf, strlen(buf)+1);
                       if(status == -1){
                           perror("Error al escribir en los clientes");
                           break;
                       }
                   }
                   if((client+i)->numClientes == control){

                	   strcpy(buf, "Te has desconectado\n");
                       status = write((client+control)->socket, buf, strlen(buf)+1);
                       if(status == -1){
						  perror("Error al escribir en el cliente ha desconectar");
						  break;
                       }
                       close((client+control)->socket);
                   }
               }
           }

           else{
               printf("Usuario no encontrado\n");
           }

           encontro=0;

       }

       else if (strcmp(comando,"/cl") == 0){

           if(cont == 0){
               printf("No hay clientes conectados\n");
           }

           else{
               printf("\nClientes en linea\n");

               for(int i=0; i<maxC; i++){
                   if((client+i)->conectado != 0){
                       printf("~%s\n",(client+i)->nombre);
                   }
               }
           }
           printf("En linea: %d\n", cont);

       }

       else if(strcmp(comando,"exit") == 0){
           printf("\n");
           break;
       }

       else{
           printf("Comando no valido\n");
       }

    }

   exit(EXIT_SUCCESS);
}

void * leer(void *arg){

   struct client_t *clienteC = ((struct client_t *)arg);
   ssize_t nBytes;
   char buf[BUF_SIZE], name[BUF_SIZE], msg[BUF_SIZE];
   int status;

   strcpy(name, (client+(cont-1))->nombre);
   strcat(name, " se ha unido al chat");

   for(int i=0; i<=maxC; i++){		//Le informamos a los clientes de la nueva conexion

       if ((client+i)->conectado == 1){

           status = write((client+i)->socket, name, strlen(name)+1);

           if(status == -1){
               perror("Error al escribir en los clientes");
               break;
           }
       }
   }

   while(1){		//Leemos los mensajes del cliente

       nBytes = read(clienteC->socket, buf, BUF_SIZE);

       if(nBytes == 0){
           printf("El cliente cerro la conexión\n");
           break;
       }
       else if(nBytes == -1){
    	   perror("Error al leer del cliente");
           return 0;
       }
       else {
           if (clienteC->conectado == 1){

        	   strcpy(msg, clienteC->nombre);
        	   strcat(msg, ": ");
        	   strcat(msg, buf);

               for(int i=0; i<=maxC; i++){		//Escribimos el mensaje en todos los clientes
                   if ((client+i)->conectado == 1){
                       status = write((client+i)->socket, msg, strlen(msg)+1);
                   }
               }

               if(status == -1){
                   perror("Error al escribir en los clientes");
                   break;
               }
           }
           else{
               printf("Cliente desconectado\n");

           }
       }
   }

   clienteC->estado = 0;
   close(clienteC->socket);

   return NULL;
   }

int main(int argc, char *argv[]){

    char buf[BUF_SIZE], nombre[BUF_SIZE];
    int numBytes;
    int status;
    int enable = 1;
    int server_sd;
    int client_sd;
    pthread_t hiloComandos;
    pthread_t rxThreadId [maxC];


    client = malloc(sizeof(struct client_t)*maxC);

    // 1. Ignore SIGPIPE
    signal(SIGPIPE, SIG_IGN);

    // 2. Create socket
    server_sd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sd == -1) {
        perror("Error al crear el socket\n");
        exit(EXIT_FAILURE);
    }

    // 3. Desactivamos el checkeo de direcciones del bind
    status = setsockopt(server_sd, SOL_SOCKET, SO_REUSEADDR,(int *) &enable, sizeof(enable));
    if (status == -1){
        perror("Error al usar setsockopt");
        exit(EXIT_FAILURE);
    }

    //4. BIND the socket to an address
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    status = bind(server_sd, (struct sockaddr*)&addr, sizeof(addr));

    if (status == -1) {
        perror("Error al hacer el bind");
        close(server_sd);
        exit(EXIT_FAILURE);
    }
    printf("Socket binded\n");

     // 5. Set backlog
    status = listen(server_sd, 10);

    if (status == -1) {
        perror("Error al poner en escucha al servidor");
        close(server_sd);
        exit(EXIT_FAILURE);
    }

    for(int i=0; i<=maxC; i++){		//Seteamos la conexion de todos los clientes en cero
        (client+i)->conectado = 0;
    }

    printf("Servidor escuchando\n");

    status = pthread_create(&hiloComandos, NULL, &comandos, NULL);	//Creamos el hilos para recibir comandos

    if(status == -1){
        perror("Error al crear el hilo de comandos");
        close(server_sd);
        exit(EXIT_FAILURE);
    }

    while(1){

        printf("Esperando por clientes\n");

        client_sd = accept(server_sd, NULL, NULL);

        if(client_sd == -1){
            perror("Error al aceptar la conexion del cliente");
            close(server_sd);
            exit(EXIT_FAILURE);
        }

        numBytes = read(client_sd, nombre, sizeof(nombre));

        if(numBytes == 0){
            printf("Nombre vacio\n");
            break;
        }

        else if(numBytes == -1){
            perror("Error al leer el nombre");
            break;
        }

         // 7. Creamos el hilo para las conexiones del cliente
        (client+cont)->socket = client_sd;
        (client+cont)->estado = 1;
        (client+cont)->conectado = 1;
        (client+cont)->numClientes = cont;
        strcpy((client+cont)->nombre,nombre);

        if(cont < 10){
            status = pthread_create(&rxThreadId[cont], NULL, &leer, (client+cont));
            cont++;
        }
        else{
            printf("Limite de conexiones es 10");
            close(client_sd);
        }

        if(status == -1){
            perror("Error al crear el hilo de lectura");
            close(server_sd);
            exit(EXIT_FAILURE);
        }

        if(client->estado == 0){
			printf("El cliente cerro la conexión\n");
			break;
		}

    }

    free(client);

    exit(EXIT_SUCCESS);
}
