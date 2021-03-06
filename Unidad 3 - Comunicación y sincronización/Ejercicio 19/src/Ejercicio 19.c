/*
 ============================================================================
 Name        : Ejercicio.c
 Author      : Juan Pablo Jiménez Heredia
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

//msgsnd

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define PERMS 0644

struct my_msgbuf {		//El buffer del mensaje
   long mtype;
   char mtext[128];
};

int main(void) {

   struct my_msgbuf buf;	//Declaramos la estructura
   int msqid;
   int len;

   key_t key;
   system("touch msgq.txt");	//Creamos el archivo para usar en la cola de mensajes

   if ((key = ftok("msgq.txt", 'B')) == -1) {   //Creamos la llave en base al archivo de texto con el codigo ascii de la letra B
      perror("ftok");
      exit(1);
   }

   if ((msqid = msgget(key, PERMS | IPC_CREAT)) == -1) {  //Creamos la cola de mensajes con la llave creada, permisos 0644
      perror("msgget");
      exit(1);
   }

   printf("Cola de mensajes, Lista para enviar.\n");
   printf("Ingresa texto, ctrl + D para cerrar\n");
   buf.mtype = 1;

   while(fgets(buf.mtext, sizeof buf.mtext, stdin) != NULL) {  //Lo que esta en la entrada lo guardamos en el arreglo de la estructura

	  len = strlen(buf.mtext);

	  //Quitamos el new line si es que existe
      if (buf.mtext[len-1] == '\n') buf.mtext[len-1] = '\0';

      if (msgsnd(msqid, &buf, len+1, 0) == -1){		//Enviamos el mensaje a la cola
    	  perror("Error al enviar el mensaje");
      }
   }

   strcpy(buf.mtext, "end");	//Colocamos end como mensaje
   len = strlen(buf.mtext);

   if (msgsnd(msqid, &buf, len+1, 0) == -1){		//Enviamos el mensaje de end al otro proceso
	   perror("Error al enviar el mensaje");
	}

   if (msgctl(msqid, IPC_RMID, NULL) == -1) {		//Eliminamos la cola de mensajes
      perror("msgctl");
      exit(1);
   }

   printf("Cola de mensajes termino de enviar\n");

   return 0;
}
