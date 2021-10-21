#define _GNU_SOURCE

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sched.h>
#include <time.h>

void *taskOne() {
    int m, n;
    while (1) {
        printf("task 1\n");
        for (m = 0; m <= 1000; m++)
            for (n = 0; n <=
                        10000; n++); /* Defor-lussen dienen om een vertraging te realiseren, zodater een aantal keer een context switch naar taak 2 optreedt */}
}

void *taskTwo() {
    int m, n;
    while (1) {
        printf("task 2\n");
        for (m = 0; m <= 1000; m++)
            for (n = 0; n <=
                        10000; n++); /* Defor-lussen dienen om een vertraging te realiseren, zodater een aantal keer een context switch naar taak 2 optreedt */}
}

void *taskThree() {
    int i, m, n;
    for (i = 0; i < 40; i++) {
        printf("task 3 \n");
        for (m = 0; m <= 1000; m++)
            for (n = 0; n <=
                        10000; n++);     /* De for-lussen dienen omeen vertraging te realiseren, zodat er een aantal keer een context switchnaar taak 4 optreedt */}
}

void *taskFour() {
    int i, m, n;
    for (i = 0; i < 40; i++) {
        printf("task 4\n");
        for (m = 0; m <= 1000; m++)
            for (n = 0; n <=
                        10000; n++);     /* De for-lussen dienen omeen vertraging te realiseren, zodat er een aantal keer een context switch naar taak 4 optreedt */}
}

int main(void) {
    int arg = 0;
    pthread_t tid;
    pthread_attr_t tattr1;
    struct sched_param param1;

    //run de taken op core nr 0
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);
    sched_setaffinity(0, sizeof(mask), &mask);

    //tattr init met default values
    pthread_attr_init(&tattr1);
    pthread_attr_setschedpolicy(&tattr1, SCHED_RR);
    pthread_attr_getschedparam(&tattr1, &param1);
    param1.sched_priority = 150;
    pthread_attr_setinheritsched(&tattr1, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedparam(&tattr1, &param1);
    pthread_create(&tid, &tattr1, taskOne, NULL);
    return 0;
}