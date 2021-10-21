#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MSGS 5

pthread_mutex_t mutex;

static void *taskOne(void *pars) {
    for (;;) {
        pthread_mutex_lock(&mutex);
        for (int i = 0; i < MSGS; i++) {
            printf("sectie 1\n");
            sleep(1);
        }
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}

static void *taskTwo(void *parc) {
    for (;;) {
        pthread_mutex_lock(&mutex);
        for (int i = 0; i < MSGS; i++) {
            printf("sectie 2\n");
            sleep(1);
        }
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}

int main() {
    pthread_t thread1, thread2;
    pthread_attr_t tattr;

    pthread_attr_init(&tattr);
    pthread_attr_setschedpolicy(&tattr, SCHED_RR);

    pthread_create(&thread1, &tattr, &taskOne, NULL);
    pthread_create(&thread2, &tattr, &taskTwo, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    return 0;
}