#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define Q_SIZE 8
#define MESSAGES 50

static int fd[2];

static void *taskOne(void *pars) {
    char buffer[Q_SIZE];
    memset(buffer, 0x00, sizeof(buffer));
    int i = 0;
    while (i < MESSAGES) {
        int res = read(fd[0], buffer, Q_SIZE);

        if (res > 0) {
            printf("Receved: %s \n", buffer);
            i++;
        }

        sleep(1);
    }

    return NULL;
}

static void *taskTwo(void *parc) {
    int res;
    int i = 0;
    char buffer[Q_SIZE];

    while (i < MESSAGES) {
        snprintf(buffer, sizeof(buffer), "%d", ++i);
        res = write(fd[1], buffer, Q_SIZE);
        printf("Send: %i \n", i);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    pipe(fd);

    pthread_create(&thread2, NULL, &taskOne, NULL);
    pthread_create(&thread1, NULL, &taskTwo, NULL);

    pthread_join(thread2, NULL);
    pthread_join(thread1, NULL);
    return 0;
}