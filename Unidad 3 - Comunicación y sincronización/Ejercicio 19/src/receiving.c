/*
 * receiving.c
 *
 *  Created on: Apr 23, 2021
 *      Author: juanpa
 */


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
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
   int toend;
   key_t key;

   if ((key = ftok("msgq.txt", 'B')) == -1) {
      perror("ftok");
      exit(1);
   }

   if ((msqid = msgget(key, PERMS)) == -1) {	//Nos conectamos a la misma cola ya que usamos el mismo archivo y mismos bits
      perror("msgget");
      exit(1);
   }

   printf("Cola de mensajes, lista para recivir mensajes\n");

   for(;;) { /* normally receiving never ends but just to make conclusion */
             /* this program ends wuth string of end */
      if (msgrcv(msqid, &buf, sizeof(buf.mtext), 0, 0) == -1) {
         perror("msgrcv");
         exit(1);
      }
      printf("Mensaje: \"%s\"\n", buf.mtext);
      toend = strcmp(buf.mtext,"end");
      if (toend == 0)
      break;
   }
   printf("Cola de mensajes termino de recivir.\n");
   system("rm msgq.txt");
   return 0;
}
