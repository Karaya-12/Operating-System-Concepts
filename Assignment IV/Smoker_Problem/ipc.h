#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <sys/types.h>
#define SIZE_BUFF 256
int pid[2];
/*key ->  key assignments of IPC's ID; shm -> shared memory; sem -> semaphore; msg -> message queue*/
//Functions That Build Up / Get the IPC
int get_ipc_id(char *proc_file, key_t key);                //Get IPC ID
char *set_shm(key_t shm_key, int shm_num, int shm_flag);   //Set Up Shared Memory
int set_msq(key_t msq_key, int msq_flag);                  //Set Up Message Queue
int set_sem(key_t sem_key, int sem_num, int sem_flag);     //Set Up Shared Memory
int down(int sem_id);                                      //Hold Off Current Process
int up(int sem_id);                                        //Wake Up Current Process
void common_setup();                                       //Basic Shared Memory, Semaphore, Signal Set Up

//Union for Semaphore Control
typedef union sem_union
{
	int val;
} Sem_Uns;

//Message Queue Structure
typedef struct msg_buff
{
	long msg_type;
	char msg_text[1];
} Msg_Buff;

//Variables in the Shared Buffer of Providers & Smokers
key_t buff_key;
int buff_num;
char *buff_ptr;

//Semaphore --> Providers
key_t prod_key;
key_t pmtx_key;
int prod_sem;
int pmtx_sem;

//Semaphore --> Smokers
key_t smok_key;
key_t smtx_key;
int smok_sem;
int smtx_sem;

//Semaphore --> Common
int sem_num;
int sem_flg;
int shm_flg;
