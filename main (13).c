#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#define NTHREADS 2

pthread_t pth_consumer;
pthread_t pth_sender;
pthread_t pth_receiver;
pthread_mutex_t sem_lock_buffer;//Problem (1)
pthread_mutex_t s,n,e;//Problem (2)
int front,rear;
int count_message; 
int num_attempts=0;
int buffer;
int *queueMessages;


void *send_message(void*a)
{    while(1)
    {
    pthread_mutex_lock(&s);
    printf("Wake Up thread %d \n",count_message);//threadid-> nomattemmp
    count_message++;
    pthread_mutex_unlock(&s);
      sleep(2);

    }
  
}


void *receive_message(void* a)//producer
{while(1){
    pthread_mutex_lock(&e);
    pthread_mutex_lock(&s);
        buffer= count_message;
    printf("\ncounter -> %d ", count_message);
    printf("\nBUFFER -> %d",buffer);
    if(rear == NTHREADS -1 && front!=0)
                 rear=-1;
            rear=rear+1;
            queueMessages[rear]=buffer;
            if(front==-1)
            front=0;
	printf("\n%d IS PRODUCED IN THE BUFFER",buffer);
    printf("\nsem wait  .. \n");
            count_message=0;    

    pthread_mutex_unlock(&s);
    pthread_mutex_unlock(&n);
          sleep(2);

 }
}



void *consumer_message(void* a)//read buffer

{     while(1){
      
        pthread_mutex_lock(&n);
        pthread_mutex_lock(&s);
printf("\n%d IS CONSUMNED FROM THE BUFFER",queueMessages[front++]);
         if(front ==NTHREADS)
        {
            front=0;
        }
        if(front-1==rear)
        {
            front=-1;
            rear=-1;
        }
       pthread_mutex_unlock(&s);
       pthread_mutex_unlock(&e);
    }
}

int main()
{
front=-1;
rear=-1;
queueMessages=(int*)malloc(NTHREADS*sizeof(int));

    while(num_attempts!=NTHREADS){
    pthread_create(&pth_sender,NULL,send_message,NULL);//attemp
    pthread_create(&pth_receiver,NULL,receive_message,NULL);//producer p2
    pthread_create(&pth_consumer,NULL,consumer_message,NULL);//thread consumer 
        num_attempts+=1;
    }
    
    pthread_join(pth_sender, NULL);
    pthread_join(pth_receiver, NULL);   
    pthread_join(pth_consumer, NULL);    

    pthread_mutex_destroy(&s);

    return 0;
}
