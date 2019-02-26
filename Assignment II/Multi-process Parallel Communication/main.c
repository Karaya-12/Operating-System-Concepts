#include <sys/types.h>
#include <unistd.h>                                                  //For execlp()
#include <stdio.h>                                                   //For pipe()
#include <stdlib.h>
#include <signal.h>
/*pipe() Function Reference
int pipe(int pipe_id[2]);
pipe[0] -> read; pipe[1] -> write*/
int function_x(int x)
{
    if (x == 1)
        return 1;
    else
        return function_x(x - 1) * x;                                //f(x) = f(x-1) * x
}

int function_y(int y)
{
    if (y == 1 || y == 2)
        return 1;
    else
        return function_y(y - 1) + function_y(y - 2);                //f(y) = f(y-1) + f(y-2)
}


int main(int argc, char* argv[])
{
    printf("Main Function --> f(x,y) = f(x) + f(y) (Both Specific)\n");

    int x, y;
    printf("Input Parameter 'x' -> ");
    scanf("%d", &x);
    printf("Input Parameter 'y' -> ");
    scanf("%d", &y);

    int pid_1, pid_2;
    int pipe_1[2], pipe_2[2], pipe_3[2], pipe_4[2];
    if (pipe(pipe_1) < 0)
        printf("pipe_1 Went Wrong !");
    if (pipe(pipe_2) < 0)
        printf("pipe_2 Went Wrong !");
    if (pipe(pipe_3) < 0)
        printf("pipe_3 Went Wrong !");
    if (pipe(pipe_4) < 0)
        printf("pipe_4 Went Wrong !");

    if ((pid_1 = fork()) < 0)
    {
        fprintf(stderr, "Fork Failed ! Pipe Build Up Failed !\n");
        exit(-1);
    }
    else if (pid_1 == 0)                                             //pid_1 > 0 --> Currently Running The Child Process
    {
        //First Process Deals With f(x)
        int fx_1;
        close(pipe_1[1]);
        close(pipe_2[0]);
        read(pipe_1[0], &fx_1, sizeof(int));                         //read() pipe_1[0] Into fx_1

        int fx_z = function_x(fx_1);
        write(pipe_2[1], &fx_z, sizeof(int));                        //wirte() fx_z Into pipe[2]_1
        close(pipe_1[0]);
        close(pipe_2[1]);
        exit(0);
    }
    else                                                             //pid_1 > 0 --> Currently Running The Father Process
    {
        if ((pid_2 = fork()) < 0)
        {
            fprintf(stderr, "Second Fork Failed ! Process Build Up Failed !\n");
            exit(-1);
        }
        else if (pid_2 == 0)                                         //pid_2 == 0 --> Currently Running The Child Process
        {
            //Second Process Deals With f(y)
            int fy_1;
            close(pipe_3[1]);
            close(pipe_4[0]);
            read(pipe_3[0], &fy_1, sizeof(int));

            int fy_z = function_y(fy_1);
            write(pipe_4[1], &fy_z, sizeof(int));
            close(pipe_3[0]);
            close(pipe_4[1]);
            exit(0);
        }
        close(pipe_1[0]);
        close(pipe_2[1]);
        close(pipe_3[0]);
        close(pipe_4[1]);

        int result;
        write(pipe_1[1], &x, sizeof(int));
        write(pipe_3[1], &y, sizeof(int));
        read(pipe_2[0], &x, sizeof(int));
        read(pipe_4[0], &y, sizeof(int));

        result = x + y;
        printf("Final Result : %d\n", result);

        close(pipe_1[1]);
        close(pipe_2[0]);
        close(pipe_3[1]);
        close(pipe_4[0]);
    }
    return 0;
}
