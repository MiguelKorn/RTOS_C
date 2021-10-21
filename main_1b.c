#include <stdio.h>
#include <pthread.h>

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

int main() {
    int arg = 0;
    pthread_t tid;
    pthread_t tid2;
    pthread_attr_t tattr;
    pthread_attr_init(&tattr);  //tattr init met defaultwaarden
    pthread_attr_setschedpolicy(&tattr, SCHED_RR);//TODO sched policy aanpassen
    pthread_create(&tid, &tattr, taskThree, &arg);
    pthread_create(&tid, &tattr, taskFour, &arg);
    pthread_join(tid, NULL);
    pthread_create(&tid2, &tattr, taskOne, &arg);
    pthread_create(&tid2, &tattr, taskTwo, &arg);
    pthread_join(tid2, NULL);
    return 0;
}