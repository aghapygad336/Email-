
/*
https://www.tutorialspoint.com/semaphores-in-operating-system
https://docs.oracle.com/cd/E19683-01/806-6867/6jfpgdcnj/index.html#sync-19683
https://www.youtube.com/watch?v=cIkzOOcdh2Y
*/
#include<stdio.h>
#include <pthread.h> 
Semaphore *createSem(void *value)
{
  Semaphore *sem = check_malloc(sizeof(Semaphore));
  int n = sem_init(sem, 0, value);
  if (n != 0) perror_exit("sem_init failed");
  return sem;
}
int main()
{
int Nmessages;// count independent incoming messages in a system, 
int mmonitor_count;//and another thread mmonitor gets the count of threads at time intervals of size t1
pthread_t threadCreator; 
printf("Thread Semaphore Creator");
pthread_create(&threadCreator, NULL, createSem, (void*)semaphore_Value); 

    return 0;
}
