#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#define MAX_SIZE 5

pthread_mutex_t bufLock;
sem_t pro, con;

int count;

void producer(char *buffer)
{
    while (1)
    {
        sem_wait(&con);
        while (count < MAX_SIZE)
        {
            pthread_mutex_lock(&bufLock);
            buffer[count] = 'a';
            count++;
            printf("Produced an item. %d \n", count);
            pthread_mutex_unlock(&bufLock);
        }
        sem_post(&pro);

    }
}

void consumer(char *buffer)
{
    while (1)
    {
        sem_wait(&pro);
        while (count > 0)
        {
            pthread_mutex_lock(&bufLock);
            printf("Consumed an item. %c \n", buffer[count-1]);
            buffer[count - 1] == NULL;
            count--;
            pthread_mutex_unlock(&bufLock);
        }
        sem_post(&con);
    }
}

int main()
{
    char buffer[MAX_SIZE];
    int choice;
    pthread_t p;

    sem_init(&pro, 0, 0);
    sem_init(&con, 0, 5);
    
    pthread_mutex_init(&bufLock, NULL);

    printf("Enter 1 for empty buffer, 2 for full buffer, and 3 for partially full buffer:");
    scanf("%d", &choice);

    switch(choice){
        case 1:
            count = 0;
   
            pthread_create(&p, NULL,(void *) producer, &buffer);
            consumer(&buffer);
            break;
        case 2:
            count = 5;
            for(int i = 0; i < count; i++){
                buffer[i] = 'a';
            }
            pthread_create(&p, NULL,(void *) producer, &buffer);
            consumer(&buffer);
            break;
        case 3:
            count = 3;
            for(int i = 0; i < count; i++){
                buffer[i] = 'a';
            }
            pthread_create(&p, NULL,(void *) producer, &buffer);
            consumer(&buffer);
            break;
        default:
            count = 0;
            pthread_create(&p, NULL,(void *) producer, &buffer);
            consumer(&buffer);
    }
    
    return 0;
}