#include <stdio.h>
int main(int argc, char const *argv[])
{
    int n, i, j, t_TotalWait = 0, t_TotalTurn = 0;
    int ID[20] = {0}, t_Burst[20] = {0}, t_Wait[20] = {0}, t_Turn[20] = {0};
    float t_AveWait = 0, t_AveTurn = 0;

    printf("Enter Total Number of Processes Here(<= 20) : ");
    scanf("%d", &n);

    printf("\nEnter Process Burst Time Below\n");
    for (i = 0; i < n; i++)
    {
        printf("P[%d]:", i + 1);
        scanf("%d", &t_Burst[i]);
        ID[i] = i + 1;
    }

    //Sorting Burst Time in Ascending Order (Selection Sort)
    for (i = 0; i < n; i++)
    {
        int pos = i, temp = 0;
        for (j = i + 1; j < n; j++)
        {
            if (t_Burst[j] < t_Burst[pos])
                pos = j;
        }
        //Swap Process Burst Time
        temp = t_Burst[i];
        t_Burst[i] = t_Burst[pos];
        t_Burst[pos] = temp;
        //Swap Process ID
        temp = ID[i];
        ID[i] = ID[pos];
        ID[pos] = temp;
    }

    //Calculating Waiting Time
    for (i = 1; i < n; i++)  //Waiting Time of The First Process == 0
    {
        t_Wait[i] = 0;
        //Wait Time = Own Burst Time + Burst Times Before Current Process
        for (j = 0; j < i; j++)
            t_Wait[i] += t_Burst[j];
        t_TotalWait += t_Wait[i];
    }

    printf("\nProcess ID\t  Burst Time\tWaiting Time\tTurnaround Time");

    //Calculating Total Waiting & Turnaround Time & Print Info of Each Process
    for (i = 0; i < n; i++)
    {
        t_Turn[i] = t_Burst[i] + t_Wait[i];  //Calculating Turnaround Time
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
