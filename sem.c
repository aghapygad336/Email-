/*https://www.sourceware.org/pthreads-win32/manual/pthread_mutex_init.html*/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define NTHREADS 10
void *thread_function(void *);
void *save_Buffer_thread(void *);

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int  counter = 0;

void main()
{
    pthread_t *thread_id;

thread_id = malloc(sizeof(pthread_t)*NTHREADS);
   int i, j;

   for(i=0; i < NTHREADS; i++)
   {
      pthread_create( &thread_id[i], NULL, thread_function, NULL );
   }

   for(j=0; j < NTHREADS; j++)
   {
      pthread_join( thread_id[j], NULL);
   }






int value =counter ;
    int *p_buffer;
    p_buffer=&value;
   //Push to buffer
       pthread_t reader_Buffer_thread;

         pthread_create(&reader_Buffer_thread, NULL,save_Buffer_thread, p_buffer);
      pthread_join(reader_Buffer_thread, NULL);
}
void *save_Buffer_thread(void *param_buffer)
{
      int buffer = *(int *) param_buffer;
      printf("Buffer - > :%d",buffer);
}


void *thread_function(void *dummyPtr)
{
   printf("Thread number %ld\n", pthread_self());
   pthread_mutex_lock( &mutex1 );
   counter++;

   pthread_mutex_unlock( &mutex1 );
}
