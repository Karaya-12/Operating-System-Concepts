/*编制一段程序，实现进程的管道通信。使用系统调用pipe()建立一条管道线。两个子进程p1和p2分别向通道个写一句话：
Child_1 Process is Sending Message !
Child_2 Process is Sending Message !
而父进程则从管道中读出来自两个进程的信息，显示在屏幕上。*/
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
int pid1, pid2;
int main(int argc, char const *argv[])
{
    int fd[2];
    char outpipe[100], inpipe[100];
    pipe(fd);                                         //Pipe Created
    while ((pid1 = fork( )) == -1);
    if (pid1 == 0)
    {
        lockf(fd[1], 1, 0);
        sprintf(outpipe, "Child_1 Process is Sending Message !");
        //Put The String Into The 'outpipe'
        write(fd[1], outpipe, 50);                    //Write 50 Bytes Into The Pipe
        sleep(5);                                     //Self Block For 5 Seconds
        lockf(fd[1], 0, 0);
        exit(0);
    }
    else
    {
        while ((pid2 = fork( )) == -1);
        if (pid2 == 0)
        {
            lockf(fd[1], 1, 0);                         //Mutex
            sprintf(outpipe, "Child_2 Process is Sending Message !");
            write(fd[1], outpipe, 50);
            sleep(5);
            lockf(fd[1], 0, 0);
            exit(0);
        }
        else
        {
            wait(0);                                   //Synchronization
            read(fd[0], inpipe, 50);                   //Read 50 Bytes Into The Pipe
            printf("%s\n", inpipe);
            wait(0);
            read(fd[0], inpipe, 50);
            printf("%s\n", inpipe);
            exit(0);
        }
    }
}

/*            Results
延迟5秒后显示:
Child_1 Process is Sending Message !
再延迟5秒:
Child_2 Process is Sending Message !    */
