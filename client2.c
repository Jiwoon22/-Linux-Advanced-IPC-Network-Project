#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<pthread.h>
#include"shm1.h"
#include"semaphore.h"
#include"p.c"
#include"v.c"
#include"initsem.c"
int win_flag=1;
void* recvMsgFromServer();
void* sendMsgToServer();
void playMusic();
struct shared_use_st1* shared_stuff1;
key_t semkey1=1234;

char quiz[3][50] = { "Love is Timing","LOVE","Clown" };
int idx = 0, tidx = 0;
char song[2][100] = { "play 10cm.wav","play Leesang.wav" };

int main(){
  pthread_t a_thread,b_thread;
  void* thread_result_a;
  void* thread_result_b;
  void* sm=(void*)0;

  int shmid;

  shmid=shmget((key_t)60099,sizeof(struct shared_use_st1),0666 | IPC_CREAT);
  sm=shmat(shmid,(void*)0,0);
  shared_stuff1=(struct shared_use_st1*)sm;

  pthread_create(&a_thread,NULL,recvMsgFromServer,NULL);
  pthread_create(&b_thread,NULL,sendMsgToServer,NULL);

//  playMusic();

  pthread_join(a_thread,thread_result_a);
  pthread_join(b_thread,thread_result_b);
}

void* recvMsgFromServer(){
  int semid; 
while (1)
{
	if (shared_stuff1->start_flag == 1)
	{
		system("play Busker.wav");
			break;
	}
}
 while(1){
    if(shared_stuff1->written_by_server==1){
      if((semid=initsem(semkey1))<0)
        exit(1);
  
   p(semid);
    if(shared_stuff1->flag==1){
      printf("Client2 by Server: %s\n", shared_stuff1->message);
      win_flag=0;
      shared_stuff1->flag=0;
      shared_stuff1->written_by_server=0;
      sleep(1);
    }
    v(semid);

  }
}
pthread_exit("Finish!\n");
}

void* sendMsgToServer(){
  char buffer[BUFFER_SIZE];
  int semid;
  
  while(1){
    while(shared_stuff1->flag==0){
	while(win_flag)
	{
     		if (strcmp(buffer, quiz[idx]) == 0) 
     		{
			printf("Excellant!!\n");
			
			strcpy(buffer, "Client 1 Wins");
			break;
		}
	}
	if (win_flag == 0)
	{
		printf("You Loose\n");
	}
	else
	{
		strncpy(shared_stuff1->message, buffer, BUFFER_SIZE); //write to shared memory through strncpy()  <<secure co
	}    
 	if((semid=initsem(semkey1))<0)
 	      exit(1);
     
        p(semid);
        printf("Starting next song in 3 seconds\n");
	sleep(3);
	if (tidx <= 3)
	{
		system(song[tidx]);
		idx++;
		tidx++;
		win_flag=1;
	}
	else
	{
		printf("Program exit");
		exit(1);
	}
        v(semid);		
		}
	}
}



