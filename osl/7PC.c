//Producer and Consumer problem
#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include <stdlib.h>
#define maxitems 5
#define buffsz 5
pthread_mutex_t mutex;
sem_t empty, full;
int in =0, out=0;
int i;
int buffer[5];
void * producer(void *pno)
{
 int item;
 for(i=0;i<maxitems;i++)
 {
 item= rand();
 sem_wait(&empty);
 pthread_mutex_lock(&mutex);
 buffer[in]=item;
 printf("Producer %d placed item in buff%d at %d\n", ((int*)pno),buffer[in],in);  in=(in+1)%buffsz;
 pthread_mutex_unlock(&mutex);
 sem_post(&full);
 }
}
void * consumer(void *cno)
{
 for(i=0;i<maxitems;i++)
 {
 sem_wait(&full);
 pthread_mutex_lock(&mutex);
 int item=buffer[out];
 printf("Consumer %d consumed item from buff %d at %d\n", ((int*)cno),item,out);  out=(out+1)%buffsz;
 pthread_mutex_unlock(&mutex);
 sem_post(&empty);
 }

}
int main()
{

 pthread_t prod[5],cons[5];
 pthread_mutex_init(&mutex,NULL);
 sem_init(&empty,0,5);
 sem_init(&full,0,0);

 int a[5]={1,2,3,4,5};

 for(i=0;i<5;i++)
 {
 pthread_create(&prod[i],NULL,(void*) producer,&a[i]);
 }

 for(i=0;i<5;i++)
 {
 pthread_create(&cons[i],NULL,(void*) consumer,&a[i]);  }

 for(i=0;i<5;i++)
 {
 pthread_join(prod[i],NULL);
 }
 for(i=0;i<5;i++)
 {
 pthread_join(cons[i],NULL);
 }

}
