#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>
#define pi (acos(-1.0))
using namespace std;
const int MAX_PCB = 200;  //Max Process Number == 200
int Num_PCB;              //Actual Process Numbers
char sFileName[20];       //Input File Path & Name

typedef struct PCB_Node   //Structure of Process PCB
{
    int p_ID;             //Process Name
    int p_Arrival;        //Process Arrival Time
    int p_Burst;          //Process Burst Time (Nanoseconds)
    int p_Wait;           //Process Wait Time (Nanoseconds)
    int p_Turn;           //Process Turnaround Time (Nanoseconds)

    int p_Priority;       //Process Priority (0 ~ 2: 0 -> Highest, 2 -> Lowest)
    int p_Completed;      /*Process Completion Flag (0 -> Not Completed, 1 -> Completed)
                            Only Useful When Come To RR & Priority Algorithms*/
} PCB;

PCB PCBs[MAX_PCB];      //PCB Array

void InitPCB()          //Initialize PCB Parts
{
    for (int i = 0; i < MAX_PCB; i++)
    {
        PCBs[i].p_ID = i + 1;
        PCBs[i].p_Arrival = -1;
        PCBs[i].p_Burst = -1;
        PCBs[i].p_Wait = 0;
        PCBs[i].p_Turn = 0;

        PCBs[i].p_Priority = -1;
        PCBs[i].p_Completed = 0;
    }
    Num_PCB = 0;
}

int ReadPCBFile(char sFileName[20])  //Read Process File Into Array 'PCBs', Then Print
{
    FILE *fp;
    char cHead;  //Store One Character of The Input File

    if ((fp = fopen(sFileName, "r")) == NULL)
    {
        cout << "Error ! File : " << sFileName << "Can Not Be Found, Please Check Path & File Name Again !" << endl;
        return -1;
    }
    else
    {
        cHead = fgetc(fp);  //fgetc() --> Get One Character From Stream
        while (cHead == ' ' || cHead == 10 || cHead == 9)  //Filter For Space, TAB & Line Break
        {
            cHead = fgetc(fp);
        }
        if (cHead == EOF)  //Empty File
        {
            printf("Error ! File : %s is Empty ! Please Check File Content Again !\n", sFileName);
            return -1;
        }
        else               //Not Empty File
        {
            fseek(fp, -1, SEEK_CUR);  //fseek() --> Reposition Stream Position Indicator; SEEK_CUR -> Current Position of The File Pointer; Function --> Read The Whole Line
            while (!feof(fp))  //feof() --> Check End-of-file Indicator, Stop At Each Space
            {
                fscanf(fp, "%d %d %d %d", &PCBs[Num_PCB].p_ID, &PCBs[Num_PCB].p_Arrival, &PCBs[Num_PCB].p_Burst, &PCBs[Num_PCB ].p_Priority);
                Num_PCB++;  //Plus 1 When Each Line Have Been Read
            }

            //Read Info Output Part
            cout << endl << "Info Read From File : " << sFileName << endl;
            cout << "Number of Total Processes : " << Num_PCB << endl;
            cout << "Process ID\t  Arrival Time\t   Burst Time\t\t Priority" << endl;
            for (int i = 0; i < Num_PCB - 1; i++)
            {
                cout << "  P[" << PCBs[i].p_ID << "]\t\t\t   " << PCBs[i].p_Arrival
                     << "\t\t\t   " << PCBs[i].p_Burst << "\t\t\t\t" << PCBs[i].p_Priority << endl;
            }
            return 0;
        }
    }
}

void ResetPCB()         //Reset PCB To Wait For Another Algorithm & Print Info
{
    //Read Info Output Part
    cout << endl << "/*-----------------------------------------------------------------*/" << endl;
    cout << endl << "Info Read From File : " << sFileName << endl;
    cout << "Number of Total Processes : " << Num_PCB << endl;
    cout << "Process ID\t  Arrival Time\t   Burst Time\t\t Priority" << endl;
    for (int i = 0; i < Num_PCB - 1; i++)
    {
        PCBs[i].p_Completed = 0;
        PCBs[i].p_Wait = 0;
        cout << "  P[" << PCBs[i].p_ID << "]\t\t\t   " << PCBs[i].p_Arrival
             << "\t\t\t   " << PCBs[i].p_Burst << "\t\t\t\t" << PCBs[i].p_Priority << endl;
    }
}

void PCBArrivalSort()
{
    //Sorting Processes' Arrival Times in Ascending Order (Selection Sort)
    for (int i = 0; i < Num_PCB - 1; i++)
    {
        int pos = i;
        for (int j = i + 1; j < Num_PCB - 1; j++)
        {
            if (PCBs[j].p_Arrival < PCBs[pos].p_Arrival)
                pos = j;
        }
        //Swap PCB
        struct PCB_Node temp;
        temp = PCBs[i];
        PCBs[i] = PCBs[pos];
        PCBs[pos] = temp;
    }
}

/*---------------------------------------------------------------------------*/

void FCFS_Algorithm()   //First-Come-First-Served Scheduling Algorithm
{
    int t_TotalWait = 0, t_TotalTurn = 0, t_Stamp = 0;
    float t_AveWait = 0, t_AveTurn = 0;

    cout << endl << "/*-----------------------------------------------------------------*/" << endl;
    cout << "First-Come-First-Served Scheduling Algorithm" << endl << endl;
    cout << "Process ID\t  Burst Time\t Waiting Time\t Turnaround Time";

    PCBArrivalSort();

    t_Stamp = PCBs[0].p_Arrival + PCBs[0].p_Burst;
    //Calculating Waiting Time of Each Processes
    for (int i = 1; i < Num_PCB - 1; i++)  //Waiting Time of The First Process == 0
    {
        if (t_Stamp >= PCBs[i].p_Arrival)
        {
            PCBs[i].p_Wait = t_Stamp - PCBs[i].p_Arrival;
            t_Stamp += PCBs[i].p_Burst;
        }
        else
        {
            PCBs[i].p_Wait = 0;
            t_Stamp = PCBs[i].p_Arrival + PCBs[i].p_Burst;
        }
        t_TotalWait += PCBs[i].p_Wait;
    }

    for (int i = 0; i < Num_PCB - 1; i++)
    {
        PCBs[i].p_Turn = PCBs[i].p_Burst + PCBs[i].p_Wait;  //Turnaround Time = Own Burst Time + Waiting Time
        printf("\n  P[%d]\t\t\t   %d\t\t\t   %d\t\t\t\t%d", PCBs[i].p_ID, PCBs[i].p_Burst, PCBs[i].p_Wait, PCBs[i].p_Turn);

        t_TotalTurn += PCBs[i].p_Turn;
    }

    cout << endl;
    cout << "Total Scheduling Times : " << Num_PCB - 1 << endl;
    cout << "Total Waiting Time : " << t_TotalWait << endl;
    cout << "Total Turnaround Time : " << t_TotalTurn << endl;

    t_AveWait = (float)(t_TotalWait) / (float)(Num_PCB - 1);
    t_AveTurn = (float)(t_TotalTurn) / (float)(Num_PCB - 1);
    cout << "Average Waiting Time : " << t_AveWait << endl;
    cout << "Average Turnaround Time : " << t_AveTurn << endl;
    cout << endl << "/*-----------------------------------------------------------------*/" << endl;
}

void SJF_Algorithm()    //Shortest-Job-First Algorithm
{
    int t_TotalWait = 0, t_TotalTurn = 0, t_Stamp = 0;
    float t_AveWait = 0, t_AveTurn = 0;
    int i = -1, j = -1, k = -1, pos = -1;

    cout << endl << "/*-----------------------------------------------------------------*/" << endl;
    cout << "Shortest-Job-First Scheduling Algorithm" << endl << endl;
    cout << "Process ID\t  Burst Time\t Waiting Time\t Turnaround Time";

    PCBArrivalSort();

    t_Stamp = PCBs[0].p_Arrival + PCBs[0].p_Burst;
    //Calculating Waiting Time of Each Processes
    for (i = 1; i < Num_PCB - 1; i++)  //Waiting Time of The First Process == 0
    {
        //Find Out The Latest Process Within Current Time Stamp
        for (j = i; j < Num_PCB - 1; j++)
        {
            if (PCBs[j].p_Arrival > t_Stamp)  //After Breaking Out The Loop,
                break;                        //PCBs[j-1] Will Be The Latest Process Meets The Requirment
        }
        //Pick Out The One With The Shortest Burst Time Among All Following Processes
        for (k = i, pos = k; k < j - 1; k++)  //Latest Process --> PCBs[j-1]
        {
            if (PCBs[k + 1].p_Burst < PCBs[k].p_Burst)
                pos = k + 1;
        }

        //Swap PCB --> Move The Suitable Process To The Top
        struct PCB_Node temp;
        temp = PCBs[pos];  //Store The Suitable One With 'temp'
        for (int t = pos; t > i; t--)
            /*Has To Be Reverse Order --> The Other Process Arrived Before It Shall Move Back One Slot*/
            PCBs[t] = PCBs[t - 1];
        PCBs[i] = temp;

        if (t_Stamp >= PCBs[i].p_Arrival)
        {
            PCBs[i].p_Wait = t_Stamp - PCBs[i].p_Arrival;
            t_Stamp += PCBs[i].p_Burst;
        }
        else
        {
            PCBs[i].p_Wait = 0;
            t_Stamp = PCBs[i].p_Arrival + PCBs[i].p_Burst;
        }
        t_TotalWait += PCBs[i].p_Wait;
    }

    //Calculating Total Waiting & Turnaround Time & Print Info of Each Process
    for (int i = 0; i < Num_PCB - 1; i++)
    {
        PCBs[i].p_Turn = PCBs[i].p_Burst + PCBs[i].p_Wait;  //Calculating Turnaround Time
        t_TotalTurn += PCBs[i].p_Turn;
        printf("\n  P[%d]\t\t\t   %d\t\t\t   %d\t\t\t\t%d", PCBs[i].p_ID, PCBs[i].p_Burst, PCBs[i].p_Wait, PCBs[i].p_Turn);
    }

    cout << endl;
    cout << "Total Scheduling Times : " << Num_PCB - 1 << endl;
    cout << "Total Waiting Time : " << t_TotalWait << endl;
    cout << "Total Turnaround Time : " << t_TotalTurn << endl;

    t_AveWait = (float)(t_TotalWait) / (float)(Num_PCB - 1);
    t_AveTurn = (float)(t_TotalTurn) / (float)(Num_PCB - 1);
    cout << "Average Waiting Time : " << t_AveWait << endl;
    cout << "Average Turnaround Time : " << t_AveTurn << endl;
    cout << endl << "/*-----------------------------------------------------------------*/" << endl;
}

void RR_Algorithm()     //Round-Robin Scheduling Algorithm
{
    int index = 0, t_TotalWait = 0, t_TotalTurn = 0, t_Stamp = 0;
    int quantum = 10;     //Quantum Length (Nanoseconds), Default: 10 Nanoseconds

    cout << endl << "Set Quantum Time Here : ";
    cin >> quantum;

    cout << endl << "/*-----------------------------------------------------------------*/" << endl;
    cout << "Round-Robin Scheduling Algorithm, With Quantum = " << quantum << " Nanoseconds" << endl;

    queue<PCB_Node> queue;  //Define A Queue For The Processes
    struct PCB_Node temp;

    PCBArrivalSort();  //Sort All Processes By Arrival Time

    while (!queue.empty() || index < Num_PCB - 1)
    {
        if (!queue.empty())  //Queue is NOT Empty
        {
            temp = queue.front();
            queue.pop();
            t_TotalWait += t_Stamp - temp.p_Arrival;
            //Update Current Time Stamp: Adding The Smaller One Between Burst Time & Quantum Time
            t_Stamp += min(temp.p_Burst, quantum);

            for (; index < Num_PCB - 1 && PCBs[index].p_Arrival < t_Stamp; index++)
                //Push All The Processes Which Arrival Time < Current Time Stamp Into The Queue
                queue.push(PCBs[index]);

            if (temp.p_Burst > quantum)  //Process Can't Be Completed In 1 Round
            {
                temp.p_Burst = temp.p_Burst - quantum;
                queue.push(temp);  //Push New 'temp' Struct Into The End of The Queue
            }
        }
        else  //Empty Queue --> Initialize Queue
        {
            queue.push(PCBs[index]);  //PCBs[index] == PCBs[0]
            t_Stamp = PCBs[index].p_Arrival;
            index++;
        }
    }

    cout << "Total Waiting Time : " << t_TotalWait << endl;
    t_TotalTurn += t_TotalWait;
    for (int t = 0; t < Num_PCB - 1; t++)
        t_TotalTurn += PCBs[t].p_Burst;
    cout << "Total Turnaround Time : " << t_TotalTurn << endl;

    float t_AveWait = (float)(t_TotalWait) / (float)(Num_PCB - 1);
    float t_AveTurn = (float)(t_TotalTurn) / (float)(Num_PCB - 1);
    cout << "Average Waiting Time : " << t_AveWait << endl;
    cout << "Average Turnaround Time : " << t_AveTurn << endl;
    cout << endl << "/*-----------------------------------------------------------------*/" << endl;
}


/*---------------------------------------------------------------------------*/


int main(int argc, char const *argv[])
{
    int iSelect;              //Algorithm Selection: 1 ~ 4
    char flag_choice;        //Input To Have Another Algorithm Running

    InitPCB();                //Initialize PCB Parts

    cout << "Input The Path And File Name Below (/home/karaya_12/Desktop/filename.txt)" << endl;
    cin >> sFileName;

    if (ReadPCBFile(sFileName) == 0)   //If Function 'ReadPCBFile' Works Well
    {
        do
        {
            cout << endl;
            cout << "1 --> FCFS_Algorithm, 2 --> Shortest-Job-First Algorithm" << endl
                 << "3 --> Round-Robin Scheduling Algorithm" << endl;
            cout << "Make Your Choice Here : ";
            cin >> iSelect;

            switch (iSelect)
            {
            case 1:
                ResetPCB();
                FCFS_Algorithm();
                break;
            case 2:
                ResetPCB();
                SJF_Algorithm();
                break;
            case 3:
                ResetPCB();
                RR_Algorithm();
                break;
            default:
                cout << "Not Illegal Input ! Please Choose Again !" << endl;
                return -1;
            }

            cout << endl << "Input 'Y' or 'y' For Another Algorithm, Anything Else To Quit : ";
            cin >> flag_choice;
        } while (flag_choice == 'Y' || flag_choice == 'y');
    }
    cout << "Process Scheduling Algorithm Simulator Completed !" << endl << "Exit..." << endl;
    return 0;
}
