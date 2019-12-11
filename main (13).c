#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#define NTHREADS 5
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

pthread_t pth_consumer;
pthread_t pth_sender;
pthread_t pth_receiver;
sem_t sender_semaphore,n,e;
int out_dequeu,in_Enqueu;
int mCount_message;
int shiftingQ;
int buffer;
int *queueMessages;


void *send_message(void*a)
{
    while(1)
    {
        sem_wait(&sender_semaphore);
        printf("\nMessage is written As Counter %d \n",mCount_message);
        mCount_message++;
        sem_post(&sender_semaphore);
        sleep(2);

    }

}

//Monitor Problem is the producer
void *receive_message(void* a)
{
    while(1)
    {
        sem_wait(&e);
        sem_wait(&sender_semaphore);
        buffer= mCount_message;
        printf("\nRecived Message-> %d \n", mCount_message);
        printf("\nBUFFER Has Recieved-> %d\n",buffer);
        if(in_Enqueu == NTHREADS -1 && out_dequeu!=0)
            in_Enqueu=-1;
        in_Enqueu=in_Enqueu+1;
        queueMessages[in_Enqueu]=buffer;
        if(out_dequeu==mCount_message-1)
        {
            printf("***BUFFER IS FULL***");
        }
        if ( in_Enqueu > out_dequeu)
    {
        printf("BUFFER Underflow NOT ALLOWED MESSAGES \n");
    }
        mCount_message=0;

        sem_post(&sender_semaphore);
        sem_post(&n);
        sleep(2);

    }
}



void *consumer_message(void* a)//read buffer

{
    while(1)
    {
        sem_wait(&n);
        sem_wait(&sender_semaphore);
        printf("\n %d IS CONSUMNED FROM THE BUFFER",queueMessages[shiftingQ]);
        
        if(out_dequeu ==NTHREADS)

        {
            out_dequeu=0;
        }
        if(out_dequeu-1==in_Enqueu)
        {
            out_dequeu=-1;
            in_Enqueu=-1;
        }
      shiftingQ=out_dequeu++;

        sem_post(&sender_semaphore);
        sem_post(&e);
    }
}

int main()
{  shiftingQ=0;

    out_dequeu=-1;
    in_Enqueu=-1;
    sem_init(&sender_semaphore, 0, 1);
    sem_init(&n, 0, 1);
    sem_init(&e, 0, 1);
    queueMessages=(int*)malloc(NTHREADS*sizeof(int));
    for(int processM=0; processM<NTHREADS; processM++)
    {
        pthread_create(&pth_sender,NULL,send_message,NULL);
        pthread_create(&pth_receiver,NULL,receive_message,NULL);
        pthread_create(&pth_consumer,NULL,consumer_message,NULL);
    }
    pthread_join(pth_sender, NULL);
    pthread_join(pth_receiver, NULL);
    pthread_join(pth_consumer, NULL);
    sem_destroy(&sender_semaphore);

    return 0;
}
