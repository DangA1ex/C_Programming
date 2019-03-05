#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define CHILDREN 13

pthread_mutex_t mother = PTHREAD_MUTEX_INITIALIZER;
sem_t father;

int day = 1;

void *mother_tasks(void *arg);
void *father_tasks(void *arg);

int main(int argc, char **argv) {
    // initialize semaphore and threads
    sem_init(&father, 1, 0);
    pthread_t m, f;

    // check if argument is valid
    if (atoi(argv[1]) > 0) {
        int days = atoi(argv[1]);
        for (int i = 0; i < days; i++) {
            pthread_create(&m, NULL, mother_tasks, NULL);
            pthread_create(&f, NULL, father_tasks, NULL);
            pthread_join(m, NULL);
            pthread_join(f, NULL);
            day++;
        }
    } else {
        printf("Invalid argument.\n");
    }
}

void *mother_tasks(void *arg) {
    printf("This is day #%d of a day in the life of Mother Hubbard.\n", day);

    for (int i = 1; i < CHILDREN; i++) {
        printf("Child #%d is being woken up\n", i);
        usleep(100);
        printf("Child #%d is being fed breakfast\n", i);
        usleep(100);
        printf("Child #%d is being sent to school\n", i);
        usleep(100);
        printf("Child #%d is being given dinner\n", i);
        usleep(100);
        printf("Child #%d is being given a bath\n", i);
        usleep(100);
        sem_post(&father);
    }

    printf("Mother is taking a nap.\n");

    pthread_mutex_lock(&mother);
}

void *father_tasks(void *arg){
    for (int i = 1; i < CHILDREN; i++) {
        sem_wait(&father);

        printf("Child #%d is being read a book.\n", i);
        usleep(100);
        printf("Child #%d is being tucked in bed\n", i);
        usleep(100);
    }

    printf("Father is going to sleep and waking up Mother to take care of the children.\n");

    pthread_mutex_unlock(&mother);
}