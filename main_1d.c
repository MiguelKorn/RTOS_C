#include <stdio.h>
#include <pthread.h>
#include <time.h>

void *taskOne() {
    int p = 0;
    while (1) {
        p++;
        printf("THREAD 1, %d \n", p);
        struct timespec deadline;
        clock_gettime(CLOCK_MONOTONIC, &deadline);

        // set interval
        deadline.tv_nsec += 500000000;
        deadline.tv_sec += 0;

        if(deadline.tv_nsec >= 1000000000) {
            deadline.tv_nsec -= 1000000000;
            deadline.tv_sec++;
        };
        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &deadline, NULL);
    }
}

void *taskTwo() {
    int p = 0;
    while (1) {
        p++;
        printf("THREAD 2, %d \n", p);
        struct timespec deadline;
        clock_gettime(CLOCK_MONOTONIC, &deadline);

        // set interval
        deadline.tv_nsec += 300000000;
        deadline.tv_sec += 1;

        if(deadline.tv_nsec >= 1000000000) {
            deadline.tv_nsec -= 1000000000;
            deadline.tv_sec++;
        };
        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &deadline, NULL);
    }
}


int main() {
    int arg = 0;
    pthread_t tid;
    pthread_attr_t tattr;

    pthread_attr_init(&tattr);  //tattr init met defaultwaarden
    pthread_attr_setschedpolicy(&tattr, SCHED_RR);//TODO sched policy aanpassen

    pthread_create(&tid, &tattr, taskOne, &arg);
    pthread_create(&tid, &tattr, taskTwo, &arg);
    pthread_join(tid, NULL);
    return 0;
}