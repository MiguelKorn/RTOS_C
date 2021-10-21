#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <mqueue.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define Q_NAME "/myqueue"
#define Q_SIZE 1024
#define MESSAGES 50

static void *taskOne(void *pars) {
    unsigned int prio;
    int bytes_read;
    char buffer[Q_SIZE];

    struct mq_attr attr = ((struct mq_attr) {0, 10, Q_SIZE, 0});
    mqd_t mq = mq_open(Q_NAME, O_CREAT | O_RDONLY | O_NONBLOCK, 0644, &attr);


    memset(buffer, 0x00, sizeof(buffer));
    mq_unlink(Q_NAME);
    int m = 0;
    while (m < MESSAGES) {

        bytes_read = mq_receive(mq, buffer, Q_SIZE, &prio);
        if (bytes_read >= 0) {
            printf("Receveid: %s\n", buffer);
            m++;
        } else {
            printf("Waiting... \n");
        }

        fflush(stdout);
        sleep(1);
    }

    printf("Read %i messages", m);
    mq_close(mq);
    mq_unlink(Q_NAME);

    return NULL;
}

static void *taskTwo(void *parc) {
    mqd_t mq = mq_open(Q_NAME, O_RDWR);

    char buffer[Q_SIZE];
    int count = 0;
    while (count < MESSAGES) {
        snprintf(buffer, sizeof(buffer), "%d", ++count);

        printf("Send: %i \n", count);
        mq_send(mq, buffer, Q_SIZE, 0);

        fflush(stdout);
        sleep(1);
    }

    mq_close(mq);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread2, NULL, &taskOne, NULL);
    pthread_create(&thread1, NULL, &taskTwo, NULL);

    pthread_join(thread2, NULL);
    pthread_join(thread1, NULL);
    return 0;
}