
/*
https://www.tutorialspoint.com/semaphores-in-operating-system
https://docs.oracle.com/cd/E19683-01/806-6867/6jfpgdcnj/index.html#sync-19683
https://www.youtube.com/watch?v=cIkzOOcdh2Y
http://web.cecs.pdx.edu/~walpole/class/cs333/fall2009/slides/6.pdf monitor
*/
#include<stdio.h>
#include <pthread.h> 
#include <semaphore.h> 
void *createSem(void *value_s);

typedef struct {
int value, wakeups;
pthread_mutex_t  *mutex;
} Semaphore;

void perror_exit (char *s)
{
  perror (s);  exit (-1);
}



void  *createSem(void *value_s)

{printf("In Function createSem");
    Semaphore SemaphoreCreated;
int value= *(int *) value_s;
 printf("Value Of Semaphore%d ",value_s);

  Semaphore *sem = malloc(sizeof(Semaphore));
/*int sem_init(sem_t *sem, int pshared, unsigned int value);*/
  int n = sem_init(sem, 0, value);

    
    
}
int main()
{
int Nmessages;// count independent incoming messages in a system, 
int mmonitor_count;//and another thread mmonitor gets the count of threads at time intervals of size t1
int messagesID;
pthread_t threadCreator; 
int value =5 ;
    int *semaphore_Value;
    semaphore_Value=&value;
pthread_create(threadCreator, NULL, createSem, (void*)semaphore_Value);
printf("Thread Semaphore Creator");

    return 0;
}
