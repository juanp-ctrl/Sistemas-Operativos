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
#include <stdio.h>
#include <stdlib.h>

#define NTHREADS 100  //Van a ser 100 hilos
#define LOOPS 1000000	//el numero de loops

pthread_mutex_t sum_mutex;		//Declaramos el mutex
long sum = 0;

void  *doWork(void *pdata){
    long i;

    for(i= 0; i<LOOPS; i++){
        									//Entramos a la región crítica
        pthread_mutex_lock(&sum_mutex);		//Lockeamos el mutex dado

        sum = sum + 1;		//Hacemos el proceso que deseamos hacer y ahora

        									//Salimos de la región crítica
        pthread_mutex_unlock(&sum_mutex);	//Deslockeamos el mutex
    }
    pthread_exit(NULL);
}

int main(int argc, char * argv[]){

    pthread_t threads[NTHREADS];		//Creamos un array de hilos

    pthread_mutex_init(&sum_mutex,NULL);		//Iniciamos el mutex

    for(int i = 0; i<NTHREADS; i++){
        pthread_create(&threads[i],NULL,doWork,NULL);	//Creamos el hilo con el metodo que implementa MUTual EXclusion device
    }

    for(int i = 0;i<NTHREADS;i++){		//Esperamos los hilos
        pthread_join(threads[i],NULL);
    }

    pthread_mutex_destroy(&sum_mutex);		//Destruimos el mutex

    printf("Suma del hilo: %ld\n", sum);
    sum = 0;

    for(int i = 0; i<NTHREADS*LOOPS;i++){		//Ahora hacemos el mismo proceso de suma aquí
        sum = sum + 1;
    }

    printf("Checkeo de suma : %ld\n", sum);

    pthread_exit(NULL);
}
