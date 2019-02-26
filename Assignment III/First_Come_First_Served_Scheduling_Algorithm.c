#include <stdio.h>
int main(int argc, char const *argv[])
{
    int n, i, t_TotalWait = 0, t_TotalTurn = 0;
    //t_TotalWait -> Average Waiting Time, t_TotalTurn -> Average Turnaround Time
    int ID[20] = {0}, t_Burst[20] = {0}, t_Wait[20] = {0}, t_Turn[20] = {0};
    /*t_Burst[20] -> Burst Time of 20 Processes
      t_Wait[20]  -> Wait  Time of 20 Processes*/
    float t_AveWait = 0, t_AveTurn = 0;

    printf("Enter Total Number of Processes Here(<= 20) : ");
    scanf("%d", &n);

    printf("\nEnter Process Burst Time Below\n");
    for (i = 0; i < n; i++)
    {
        printf("P[%d] : ", i + 1);
        scanf("%d", &t_Burst[i]);
        ID[i] = i + 1;
    }

    //Calculating Waiting Time of Each Processes
    for (i = 1; i < n; i++)  //Waiting Time of The First Process == 0
    {
        t_Wait[i] = 0;
        //Wait Time = Own Burst Time + Burst Times Before Current Process
        for (int j = 0; j < i; j++)
            t_Wait[i] += t_Burst[j];
        t_TotalWait += t_Wait[i];
    }

    printf("\nProcess ID\t  Burst Time\tWaiting Time\tTurnaround Time");

    //Calculating Total Waiting & Turnaround Time & Print Info of Each Process
    for (i = 0; i < n; i++)
    {
        t_Turn[i] = t_Burst[i] + t_Wait[i];  //Turnaround Time = Own Burst Time + Waiting Time
        t_TotalTurn += t_Turn[i];
        printf("\n  P[%d]\t\t\t   %d\t\t\t   %d\t\t\t\t%d", ID[i], t_Burst[i], t_Wait[i], t_Turn[i]);
    }

    //Calculating Average Waiting & Turnaround Time
    t_AveWait = (float)(t_TotalWait) / (float)(i);
    t_AveTurn = (float)(t_TotalTurn) / (float)(i);
    printf("\n\nAverage Waiting Time : %f", t_AveWait);
    printf("\nAverage Turnaround Time : %f", t_AveTurn);

    return 0;
}
