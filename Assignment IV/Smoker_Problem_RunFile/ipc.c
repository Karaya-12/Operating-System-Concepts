#include "ipc.h"

int get_ipc_id(char *proc_file, key_t key)
{
    FILE *pf;
    char line[SIZE_BUFF], column[SIZE_BUFF];

    if ((pf = fopen(proc_file, "r")) == NULL)  //File Cannot be Open
    {
        perror("/proc/sysvipc/ File Cannot be Open...");
        exit(-1);
    }

    fgets(line, SIZE_BUFF, pf);  //char *fgets(char *str, int val, FILE *stream)
    /*Reads characters from stream and stores them as a string until (val-1) characters have been read.*/
    while (!feof(pf))  //Check End-of-file Indicator --> Loop When Not Finished
    {
        int i = 0, j = 0;

        /*Read File, and Copy to Lines & Colums*/
        fgets(line, SIZE_BUFF, pf);
        while (line[i] == ' ')
            i++;
        while (line[i] != ' ')
            column[j++] = line[i++];
        column[j] = '\0';  //End Column With '\0'

        if (atoi(column) != key)  //atoi() --> Convet String to Integerl; Stop When 'key' Has Been Found
            continue;

        fclose(pf);
        /*Rewrite column[]*/
        j = 0;
        while (line[i] == ' ')
            i++;
        while (line[i] != ' ')
            column[j++] = line[i++];
        column[j] = '\0';

        i = atoi(column);
        return i;
    }
    fclose(pf);
    return -1;
}

/* Linux 'sembuf' Structure
struct sembuf
{
    unsigned short int sem_num;  //Index of Semaphores, Starts With 0
    short int sem_op;            //Three Kinds of Operation on Semaphores: >0, 0, <0
    short int sem_flg;           //Two Flags of Operation: IPC_NOWAIT, SEM_UNDO
}; */

/*Hold Off Current Process*/
int down(int sem_id)
{
    struct sembuf buf;
    buf.sem_num = 0;
    buf.sem_op = -1;  //sem_op < 0 --> Hold Off Current Process
    buf.sem_flg = SEM_UNDO;  //Automatically Undo All Operations When Process Ends

    /*int semop(int sem_id, struct sembuf *sops, size_t nsops)
     *nsops --> Amounts of Signals to Be Operated On
     *Invoke semop() Successfully --> Return 1; Unsuccessfully --> Return -1 */
    if ((semop(sem_id, &buf, 1)) < 0)
    {
        perror("Down Error !");
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}

/*Wake Up Current Process*/
int up(int sem_id)
{
    struct sembuf buf;
    buf.sem_num = 0;
    buf.sem_op = 1;  //sem_op > 0 --> Wake Up Current Process
    buf.sem_flg = SEM_UNDO;
    if ((semop(sem_id, &buf, 1)) < 0)
    {
        perror("Up Error !");
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}

/*Set Up One Semephore Within n * Signal, And Return Identifiers 'sem_id'*/
int set_sem(key_t sem_key, int sem_num, int sem_flg)
{
    int sem_id;
    Sem_Uns sem_arg;

    //Get or Set Up Semaphore
    if ((sem_id = get_ipc_id("/proc/sysvipc/sem", sem_key)) < 0)
    {
        //int semget(key_t key, int nsems, int semflg); --> Build Up A New Semaphore, Return ID to sem_id
        if ((sem_id = semget(sem_key, 1, sem_flg)) < 0)
        {
            perror("Error ! Semaphore Cannot Be Created !\n");
            exit(EXIT_FAILURE);
        }
        sem_arg.val = sem_num;  //Initialize The Semaphore

        //int semctl(int semid, int semnum, int cmd, union semun arg); Failure --> Return -1
        if (semctl(sem_id, 0, SETVAL, sem_arg) < 0)
        {
            perror("Error ! Semaphore Set Failure !\n");
            exit(EXIT_FAILURE);
        }
    }
    return sem_id;
}

/*Set Up One n bytes Shared Memory, And Return Pointer 'shm_buf' Pointed To The First Address*/
char * set_shm(key_t shm_key, int shm_num, int shm_flg)
{
    int i, shm_id;
    char * shm_buf;  //Pointer Pointed To The First Address

    //Get or Set Up Shared Memory
    if ((shm_id = get_ipc_id("/proc/sysvipc/shm", shm_key)) < 0)
    {
        //int shmget(key_t key, size_t size, int shmflg);
        //Get or Set Up New Shared Memory (Length = shm_num bytes), Return Identifier to shm_id
        if ((shm_id = shmget(shm_key, shm_num, shm_flg)) < 0)
        {
            perror("Error ! Shared Memory Cannot Be Set Up !\n");
            exit(EXIT_FAILURE);
        }

        //void *shmat(int shmid, const void *shmaddr, int shmflg);
        //Map The Memory Marked by 'shm_id' to Pointer 'shm_buf'
        if ((shm_buf = (char *)shmat(shm_id, 0, 0)) < (char *)0)
        {
            perror("Error ! Cannot Get Shared Memory !\n");
            exit(EXIT_FAILURE);
        }

        //Initialize 'shm_buf' --> 0
        for (i = 0; i < shm_num; i++)
            shm_buf[i] = 0;
    }
    //Map The Memory Marked by 'shm_id' to Pointer 'shm_buf'
    if ((shm_buf = (char *)shmat(shm_id, 0, 0)) < (char *)0)
    {
        perror("Error ! Cannot Get Shared Memory !\n");
        exit(EXIT_FAILURE);
    }
    return shm_buf;
}

/*Set Up One Message Queue, And Return Message Queue ID - 'msq_id'*/
int set_msq(key_t msq_key, int msq_flg)
{
    int msq_id;

    //Get or Set Up Message Queue
    if ((msq_id = get_ipc_id("/proc/sysvipc/msg", msq_key)) < 0)
    {
        //int msgget(key_t key, int msgflag); --> Build Up A New Semaphore, Return ID to msq_id
        if ((msq_id = msgget(msq_key, msq_flg)) < 0)
        {
            perror("Error ! Message Queue Cannot Be Set Up !\n");
            exit(EXIT_FAILURE);
        }
    }
    return msq_id;
}
