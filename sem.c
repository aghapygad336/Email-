#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#define NTHREADS 2

pthread_t mCounter;
pthread_t pth_sender;
pthread_t pth_receiver;
pthread_mutex_t sem_lock_buffer; 
int count_message; 
int num_attempts=0;
int buffer;

void *send_message(void*a)
{    while(1)
    {
    pthread_mutex_lock(&sem_lock_buffer); // before entering critical section and sending the message and changing the buffer sem-writer
    printf("Wake Up thread %d \n",count_message);//threadid-> nomattemmp
    count_message++;
    pthread_mutex_unlock(&sem_lock_buffer);
      sleep(2);

    }
  
}


void *receive_message(void* a)
{while(1){
    pthread_mutex_lock(&sem_lock_buffer);
        buffer= count_message;

    printf("\ncounter -> %d ", count_message);
    printf("BUFFER -> %d",buffer);
    printf("\nsem wait  .. \n");
            count_message=0;    

    pthread_mutex_unlock(&sem_lock_buffer);
          sleep(2);

 }
}



int main()
{
    
    while(num_attempts!=NTHREADS){
    /* ->*/   pthread_create(&pth_sender,NULL,send_message,NULL);//attemp
        pthread_create(&pth_receiver,NULL,receive_message,NULL);
        num_attempts+=1;
    }
    pthread_join(pth_sender, NULL);
    pthread_join(pth_receiver, NULL);    
    pthread_mutex_destroy(&sem_lock_buffer);

    return 0;
}
