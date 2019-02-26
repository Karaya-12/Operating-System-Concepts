#include <sys/types.h>
#include <wait.h>
#include <unistd.h>                                                  //For execlp()
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
typedef void(*sighandler_t)(int);
void displayls()
{
    printf("Process Continue To Execute...\n\n");
    execlp("/bin/ls", "ls", NULL);                                   //int execlp(const char * file,const char * arg,……);
    printf("Finished Given Commands --> 'ls'");
}


int main(int argc, char* argv[])
{
    pid_t pid_0;                                                     //pid_0 -> ID of Child Process
    int status;                                                      //status -> Returned Value of Child Process
    pid_0 = fork();                                                  //Build Up Child Process
    if (pid_0 < 0)                                                   //Failed Building Up Child Process
    {
        fprintf(stderr, "Fork Failed ! Child Process Build Up Failed !\n");
        exit(-1);
    }
    else if (pid_0 == 0)                                             //pid_0 == 0 --> Currently Running The First Child Process
    {
        printf("\n/*------------------------------*/\n");
        printf("Current Process Type : Child Process\nProcess ID: %d.\nFather Process ID: %d.\nGiven Commands to --> 'ls'.\n", getpid(), getppid());
        printf("/*------------------------------*/\n\n");
        signal(SIGINT, (sighandler_t)displayls);                     //Register a Signal, e.g. signal(int signum, sighandler_t handler);
        printf("Process Pause, Wait For The Signal...\n");
        pause();                                                     //Wait For Signal & Invoke displayls()
    }
    else if (pid_0 > 0)                                              //pid_0 > 0 --> Currently Running The Father Process
    {
        printf("Current Process Type : Father Process\nProcess ID: %d.\nGiven Commands to --> 'fork() Again'.\n", getppid());
        //fork() One More Time In Father Process, New Child Process To Perform 'ps' Command
        pid_t pid_1;
        pid_1 = fork();
        if (pid_1 < 0)                                               //Failed Building Up Child Process
        {
            fprintf(stderr, "Second Fork Failed ! Child Process Build Up Failed !\n");
            exit(-1);
        }
        else if (pid_1 == 0)                                         //pid_1 == 0 --> Currently Running The Second Child Process
        {
            printf("\n/*------------------------------*/\n");
            printf("The ID of The Process to be Triggered is %d\n", pid_0);  //pid_0 To Trigger
            printf("Current Process Type : Child Process\nProcess ID: %d.\nFather Process ID: %d.\nGiven Commands to --> 'ps'.\n", getpid(), getppid());
            printf("/*------------------------------*/\n\n");
            execlp("/bin/ps", "ps", NULL);
        }
        else//Wait For The Child Process To Complete, Then Send Signal To pid_0 To Execute Command 'ls'
        {
            wait(NULL);
            printf("\n\n/*------------------------------*/\n");
            printf("Finished Given Commands --> 'ps'\n");
            kill(pid_0, SIGINT);                                     //Send Keyboard Kill Signal To First Child Process (pid_0)
            printf("Signal Sent\n");
            printf("/*------------------------------*/\n\n");
        }
        //Wait For All Child Processes Have Completed, Then Exit wait(NULL)
        printf("\n/*------------------------------*/\n");
        printf("All Child Processes Have Completed !\n");
        printf("Exiting Program...\n");
        exit(0);
    }
}
