//Reader and Writer problem #include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include <stdlib.h>
#include<unistd.h>
#include<stdio.h>

sem_t mutex,wrt;
int data=0, rcnt=0;
void* reader(void * arg)
{
 sem_wait(&mutex);
 rcnt=rcnt+1;
 if(rcnt==1)
 sem_wait(&wrt);
 sem_post(&mutex);
 printf("data is read %d\n",data);
 sleep(1);
 sem_wait(&mutex);
 rcnt=rcnt-1;
 if(rcnt==0)
 sem_post(&wrt);
 sem_post(&mutex);
}
void* writer(void *qrg)
{
 sem_wait(&wrt);
 data++;
 printf("data is written %d\n",data);
 sleep(1);
 sem_post(&wrt);
}
int main()
{
 int i;
 pthread_t rtid[5],wrtid[5];
 sem_init(&mutex,0,1);
 sem_init(&wrt,0,1);
 for(i=0;i<2;i++)
 {
 pthread_create(&wrtid[i],NULL,(void*) writer,NULL);  pthread_create(&rtid[i],NULL, (void*) reader,NULL);  }
 for(i=0;i<2;i++)
 {
 pthread_join(wrtid[i],NULL);
 pthread_join(rtid[i],NULL);
 }
}
