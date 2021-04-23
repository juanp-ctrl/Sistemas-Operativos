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
struct my_msgbuf {
   long mtype;
   char mtext[128];
};

int main(void) {
   struct my_msgbuf buf;
   int msqid;
   int len;
   key_t key;
   system("touch msgq.txt");

   if ((key = ftok("msgq.txt", 'B')) == -1) {   //Creamos la llave en base al archivo de texto
      perror("ftok");
      exit(1);
   }

   if ((msqid = msgget(key, PERMS | IPC_CREAT)) == -1) {  //Creamos la cola de mensajes con la llave creada, permisos 0644
      perror("msgget");
      exit(1);
   }
   printf("Cola de mensajes, Lista para enviar.\n");
   printf("Ingresa texto, ctrl + D para cerrar\n");
   buf.mtype = 1; /* we don't really care in this case */

   while(fgets(buf.mtext, sizeof buf.mtext, stdin) != NULL) {  //Lo que esta en la entrada lo guardamos en el arreglo de la estructura

	  len = strlen(buf.mtext);

	  /* remove newline at end, if it exists */
      if (buf.mtext[len-1] == '\n') buf.mtext[len-1] = '\0';

      if (msgsnd(msqid, &buf, len+1, 0) == -1)		//Enviamos el mensaje a la cola
      perror("msgsnd");

   }

   strcpy(buf.mtext, "end");
   len = strlen(buf.mtext);

   if (msgsnd(msqid, &buf, len+1, 0) == -1) /* +1 for '\0' */
   perror("msgsnd");

   if (msgctl(msqid, IPC_RMID, NULL) == -1) {
      perror("msgctl");
      exit(1);
   }
   printf("Cola de mensajes termino de enviar\n");
   return 0;
}
