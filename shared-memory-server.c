#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
#include<unistd.h>
#include<signal.h> 
#include<pthread.h> 
#include"shm1.h"  
#include"shm2.h"
#include"semaphore.h" 
#include "p.c"
#include "v.c"
#include "initsem.c"

void* client1TOclient2();
void* client2TOclient1(); 


struct shared_use_st1* shared_client1; 
struct shared_use_st2* shared_client2;
key_t semkey1 = 1234; 
key_t semkey2 =5678; 

int main()
{

	pthread_t thread_1, thread_2; 
	void* thread_1_result; void* thread_2_result;
	void* shared_memory1 = (void*)0;
	void* shared_memory2 = (void*)0;
	int shmid1, shmid2;

	shmid1 = shmget((key_t)60099, sizeof(struct shared_use_st1), 0666 | IPC_CREAT); 
	shared_memory1 = shmat(shmid1, (void*)0, 0); 
	shared_client1 = (struct shared_use_st1*)shared_memory1;
	shared_client1->flag = 0; 
	shared_client1->written_by_server = 0; 
	shared_client1->start_flag=0;

	shmid2 = shmget((key_t)60098, sizeof(struct shared_use_st2), 0666 | IPC_CREAT); 
	shared_memory2 = shmat(shmid2, (void*)0, 0); 
	shared_client2 = (struct shared_use_st2*)shared_memory2;
	shared_client2->flag = 0; 
	shared_client2->written_by_server = 0;
	shared_client2->start_flag=0;

	pthread_create(&thread_1, NULL, client2TOclient1, NULL); 
	pthread_create(&thread_2, NULL, client1TOclient2, NULL); 

	pthread_join(thread_1, thread_1_result);
	pthread_join(thread_2, thread_2_result);

	if (shmdt(shared_memory1) < 0) {
		printf("error"); 
		return;
	}
	if (shmdt(shared_memory2) < 0) {
		printf("error");
		return;
	}
}

void* client1TOclient2()   
{
	int semid; 
	while (1) {
		if (shared_client1->written_by_1 == 1) {
			if ((semid = initsem(semkey1)) < 0)
				exit(1);

			p(semid); //before critical section 
			if (shared_client1->flag == 1) {
				strncpy(shared_client2->message, shared_client1->message, BUFFER_SIZE); 

				shared_client1->flag = 0;
				shared_client1->written_by_1 = 0;
				shared_client2->flag = 1;
				shared_client2->written_by_server = 1;
				sleep(1);
			}
			v(semid); //after critical section 
		}
	}
	pthread_exit("nice work!");
}

void* client2TOclient1()   
{
	char buffer[BUFFER_SIZE]; 
	int semid;
	 
	while(1){
     		if(shared_client2->start_flag == 1){
			shared_client1->start_flag=1;
      			break;
		}
	}
	while (1) {
		if (shared_client2->written_by_2 == 1) {
			if ((semid = initsem(semkey2)) < 0)
				exit(1);

			p(semid); //before critical section 
			if (shared_client2->flag == 1) {
				strncpy(shared_client1->message, shared_client2->message, BUFFER_SIZE); 
				shared_client2->flag = 0;
				shared_client2->written_by_2 = 0;
				shared_client1->flag = 1;
				shared_client1->written_by_server = 1;
				sleep(1);
			}
			v(semid); 
		}
	}
}

