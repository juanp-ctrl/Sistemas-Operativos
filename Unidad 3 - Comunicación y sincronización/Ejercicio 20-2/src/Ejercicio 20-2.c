/*
 ============================================================================
 Name        : Ejercicio.c
 Author      : Juan Pablo Jiménez Heredia
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

static long glob = 0;
pthread_mutex_t mutex;

static void* threadFunc(void *arg) {

    int loops = *((int *) arg);  //Convertimos lo pasado por el parametro en el entero loops
    long loc;

    for (int j = 0; j < loops; j++) {

    	pthread_mutex_lock(&mutex);

    	loc = glob;
        loc++;
        glob = loc;		//Incrementamos el valor de glob

        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);		//Cerramos el hilo
}

int main(int argc, char *argv[]){
    pthread_t t1, t2;		//Creamos dos hilos
    int loops, s;

    loops = (argc > 1) ? atol(argv[1]) : 10000000;		//El signo ? es usado asi -> (test) ? (when-true) : (when:false)
    													//En este caso si el argumento es mayor a 1 el string pasado se convierte a tipo long
    													//Con la funcion atol y si el argumento no es > 1, loops es igual a 10 millones
    pthread_mutex_init(&mutex,NULL);

    s = pthread_create(&t1, NULL, threadFunc, &loops);
    if (s != 0) perror("pthread create");
    s = pthread_create(&t2, NULL, threadFunc, &loops);
    if (s != 0) perror("pthread create");

    s = pthread_join(t1, NULL);
    if (s != 0) perror("pthread_join");

    s = pthread_join(t2, NULL);
    if (s != 0) perror("pthread_join");

    pthread_mutex_destroy(&mutex);

    printf("glob = %ld\n", glob);
    exit(EXIT_SUCCESS);
}
