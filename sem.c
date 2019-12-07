
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#define NTHREADS 25


pthread_t pth_sender;
pthread_t pth_receiver;
pthread_mutex_t sem_lock_buffer; 

int count_message; 
int num_attempts=0;


void *send_message(void* a)
{
    pthread_mutex_lock(&sem_lock_buffer); // before entering critical section and sending the message and changing the buffer sem-writer
    printf("message from thread \n");
    printf("sender write .. \n");
    pthread_mutex_unlock(&sem_lock_buffer);
}


void *receive_message(void* a)
{
    pthread_mutex_lock(&sem_lock_buffer);
    printf("message from thread \n");
    printf("thread ID  %ld", pthread_self());
    pthread_mutex_unlock(&sem_lock_buffer);
}



int main()
{
    while(1 && num_attempts!=NTHREADS){
        pthread_create(&pth_sender,NULL,send_message,NULL);
        pthread_create(&pth_receiver,NULL,receive_message,NULL);
        num_attempts+=1;

    }

    pthread_join(pth_sender, NULL);
    pthread_join(pth_receiver, NULL);

    pthread_mutex_destroy(&sem_lock_buffer);

    return 0;
}
