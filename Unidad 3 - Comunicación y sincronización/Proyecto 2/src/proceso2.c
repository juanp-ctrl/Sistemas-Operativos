/*
 * proceso2.c
 *
 *  Created on: Apr 26, 2021
 *      Author: juanpa
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>

#define PERMS 0644

struct bufstr {
   long mtype;
   char mtext[128];
};

void *enviar(void *msqid){

    struct bufstr buf;
    int len;

    printf("Bienvenido al chat usuario TWO.\n\n");

    buf.mtype = 1;

    while(fgets(buf.mtext, sizeof(buf.mtext), stdin) != NULL) {

        len = strlen(buf.mtext);

        if (buf.mtext[len-1] == '\n') buf.mtext[len-1] = '\0';

        if (msgsnd(msqid, &buf, len+1, 0) == -1){
        	perror("Error al enviar el mensaje");
        }

        if(strcmp(buf.mtext, "end") == 0){
        	printf("Cerrando.\n");
        	break;
        }

    }

    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }

    pthread_exit(NULL);

}

void *leer(void *msqid){

    struct bufstr buf;
    int len;

    for(;;) {

        if (msgrcv(msqid, &buf, sizeof(buf.mtext), 0, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }

        printf("User ONE: \"%s\"\n", buf.mtext);

        if (strcmp(buf.mtext, "end") == 0){
        	printf("El usuario ONE ya no enviara mas mensajes\n");
			break;
        }
    }

    pthread_exit(NULL);
}

int main(void) {

    int msqid1;
    int msqid2;
    key_t key1;
    key_t key2;
    pthread_t hilo1;
    pthread_t hilo2;

    if ((key2 = ftok("msgq2.txt", 'A')) == -1) {
        perror("ftok");
        exit(1);
    }

    if ((msqid2 = msgget(key2, PERMS | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(1);
    }

    if ((key1 = ftok("msgq1.txt", 'B')) == -1) {
        perror("ftok");
        exit(1);
    }

    if ((msqid1 = msgget(key1, PERMS)) == -1) {
        perror("msgget");
        exit(1);
    }

    pthread_create(&hilo1, NULL, &enviar, msqid2);
    pthread_create(&hilo2, NULL, &leer, msqid1);

    pthread_join(hilo1,NULL);
    pthread_join(hilo2, NULL);

   return 0;
}
