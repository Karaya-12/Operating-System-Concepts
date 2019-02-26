#include "ipc.h"

/*Basic Shared Memory, Semaphore, Synchronizing / Mutex Signal Set Up*/
void common_setup()
{
    //Variables of Shared Buffer
    buff_key = 101;  //Random Given Key Assignment of The Shared Buffer
    buff_num = 2;    //Random Given Length of The Shared Buffer
    shm_flg = IPC_CREAT | 0644;  //Share The R&W Authority of the Shared Memory; 0644 --> Authority Code

    //Get Shared Memory in the Shared Buffer Area
    //'buff_ptr' Points to the First Address of the Shared Buffer
    buff_ptr = (char *)set_shm(buff_key, buff_num, shm_flg);

    //Variables of Semaphore
    prod_key = 201;  //Key Assignment of Provider's Synchronizing Signal
    pmtx_key = 202;  //Key Assignment of Provider's Mutex Signal
    smok_key = 301;  //Key Assignment of Smoker's   Synchronizing Signal
    smtx_key = 302;  //Key Assignment of Smoker's   Mutex Signal
    sem_flg = IPC_CREAT | 0644;  //Share The R&W Authority of the Semaphore; 0644 --> Authority Code

    //Synchronizing Semaphore of The Providers
    sem_num = 1;
    //Get The Synchronizing Semaphore of The Providers
    prod_sem = set_sem(prod_key, sem_num, sem_flg);

    //Synchronizing Semaphore of Smokers --> Initially No Cigarette -> sem_num = 0
    sem_num = 0;
    //Get The Synchronizing Semaphore of The Smokers
    smok_sem = set_sem(smok_key, sem_num, sem_flg);
}
