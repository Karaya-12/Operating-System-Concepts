#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int value = 0;
void *runner(void *param);                                           //The Thread

int main(int argc, char const *argv[])
{
    int pid;
    pthread_t tid;
    pthread_attr_t attr;
    pid = fork();
    if (pid == 0)                                                    //Child Process
    {
        pthread_attr_init(&attr);
        pthread_create(&tid, &attr, runner, NULL);
        pthread_join(tid, NULL);
        printf("CHILD : value = %d", value);                         //Line C
    }
    else if (pid > 0)                                                //Parent Process
    {
        wait(NULL);
        printf("PARENT : value = %d", value);                        //Line P
    }
}

void *runner(void *param)
{
    value = 5;
    pthread_exit(0);
}
