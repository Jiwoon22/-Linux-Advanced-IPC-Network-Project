#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<pthread.h>
#include"shm2.h"
#include"semaphore.h"
#include"p.c"
#include"v.c"
#include"initsem.c"

void* recvMsgFromServer();
void* sendMsgToServer();

struct shared_use_st2* shared_stuff2;
key_t semkey2=5678;

char quiz[3][50] = { "Love is Timing","LOVE","Clown" };
int idx = 0, tidx = 0;
char song[2][100] = { "play 10cm.wav","play Leesang.wav" };
int win_flag=1;

int main(){
  pthread_t a_thread,b_thread;
  void* thread_result_a;
  void* thread_result_b;
  void* sm=(void*)0;

  int shmid;

  shmid=shmget((key_t)60098,sizeof(struct shared_use_st2),0666 | IPC_CREAT);
  sm=shmat(shmid,(void*)0,0);
  shared_stuff2=(struct shared_use_st2*)sm;

  pthread_create(&a_thread,NULL,recvMsgFromServer,NULL);
  pthread_create(&b_thread,NULL,sendMsgToServer,NULL);

  //music
  pthread_join(a_thread,thread_result_a);
  pthread_join(b_thread,thread_result_b);
}
void* recvMsgFromServer(){
  int semid;
shared_stuff2->start_flag = 1;
	system("play Busker.wav");
   while(1){
    if(shared_stuff2->written_by_server==1){
     if(shared_stuff2->flag==1){
      if((semid=initsem(semkey2))<0)
        exit(1);
  
     p(semid);
 
      printf("Client1 by Server: %s\n", shared_stuff2->message);
      shared_stuff2->flag=0;
      shared_stuff2->written_by_server=0;
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
    while(shared_stuff2->flag==0)
    {
	while(win_flag)
        {
        	fgets(buffer,sizeof(buffer),stdin);
        	buffer[strlen(buffer)-1]='\0';
		if (strcmp(buffer, quiz[idx]) == 0) 
		{
			printf("Excellant!!\n");
			sleep(3);
			strcpy(buffer, "Client 2 Wins");
			break;
					}
		else
		{
			printf("try again\n");
		}
	}
	if (win_flag == 0)
	{
		printf("You Loose\n");
	}
	else
	{
		strncpy(shared_stuff2->message, buffer, BUFFER_SIZE); //write to shared memory through strncpy()  <<secure co
	}
        if((semid=initsem(semkey2))<0)
        exit(1);
        printf("test string:%s\n", shared_stuff2->message);
        p(semid);
        shared_stuff2->flag=1;
        shared_stuff2->written_by_2=1;
   
	printf("Starting next song in 3 seconds\n");
	sleep(3);
	if (tidx <= 3)
	{
		system(song[tidx]);
		idx++;
		tidx++;
		shared_stuff2->flag=0;
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

