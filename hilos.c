#include <pthread.h>
#include <stdio.h>

int saldo = 0;
#define NUM_HILOS 100
#define REPETICIONES 100
pthread_mutex_t mutex;

void * sumaSaldo(void *arg) {
    for (int i = 0; i < REPETICIONES; i++) {
        pthread_mutex_lock(&mutex);
        saldo += 100;
        pthread_mutex_unlock(&mutex);
        printf("Valor actual de saldo en el hilo: %d\n", saldo);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t hilos[NUM_HILOS];
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < NUM_HILOS; i++) {
        pthread_create(&hilos[i], NULL, sumaSaldo, NULL);
    }

    for (int i = 0; i < NUM_HILOS; i++) {
        pthread_join(hilos[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    printf("Saldo final: %d\n", saldo);

    pthread_exit(NULL);
}