#include <stdio.h>
#include <pthread.h>

void *taskOne() {
    int m, n;
    while (1) {
        printf("task 1\n");
        for (m = 0; m <= 1000; m++)
            for (n = 0; n <= 10000; n++);
        /* Defor-lussen dienen om een vertraging te realiseren, zodater een aantal keer een context switch naar taak 2 optreedt */}
}

void *taskTwo() {
    int m, n;
    while (1) {
        printf("task 2\n");
        for (m = 0; m <= 1000; m++)
            for (n = 0; n <= 10000; n++);
        /* Defor-lussen dienen om een vertraging te realiseren, zodater een aantal keer een context switch naar taak 2 optreedt */}
}

void *taskThree() {
    int m, n;
    while (1) {
        printf("task 3\n");
        for (m = 0; m <= 1000; m++)
            for (n = 0; n <= 10000; n++);
        /* Defor-lussen dienen om een vertraging te realiseren, zodater een aantal keer een context switch naar taak 2 optreedt */}
}

void *taskFour() {
    int m, n;
    while (1) {
        printf("task 4\n");
        for (m = 0; m <= 1000; m++)
            for (n = 0; n <= 10000; n++);
        /* Defor-lussen dienen om een vertraging te realiseren, zodater een aantal keer een context switch naar taak 2 optreedt */}
}

int main() {
    int arg = 0;
    pthread_t tid;
    pthread_attr_t tattr;
    pthread_attr_init(&tattr);  //tattr init met defaultwaarden
    pthread_attr_setschedpolicy(&tattr, SCHED_RR);//TODO sched policy aanpassen
    pthread_create(&tid, &tattr, taskOne, &arg);
    pthread_create(&tid, &tattr, taskTwo, &arg);
    pthread_create(&tid, &tattr, taskThree, &arg);
    pthread_create(&tid, &tattr, taskFour, &arg);
    pthread_join(tid, NULL);
    return 0;
}