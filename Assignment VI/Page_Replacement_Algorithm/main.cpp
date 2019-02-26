#include <iostream>
#include <sstream>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <algorithm>
#define invalid -1
#define MAX_VM 32        //Max Capacity of Virtual Memory
#define MAX_INS 320      //Max Length of Instruction = 320
using namespace std;

int Ran_Add[MAX_INS];    //Random Instruction Flow
int page[MAX_INS];       //Corresponding Page Number
int offset[MAX_INS];     //Corresponding Page Offset Number
int counter_pf;          //Page Faults Counter (Take The First 3 Faults Into Account Too)

typedef struct           //Page Structure
{
    int ID_p;            //Page Number
    int ID_pf;           //Related Frame Number in Memory
    int t_LastAcc;       //Last Access Time
    bool bool_visited;
} stru_Page;
stru_Page Page_Arr[MAX_VM];  //Page Number == MAX_VM

struct stru_PageControl  //Memory Page Control Structure
{
    int ID_p;            //Page Number
    int ID_pf;           //Frame Number in Memory
    struct stru_PageControl *next;
};
typedef struct stru_PageControl PageCon;  //Byname of 'stru_PageControl'
PageCon PCon_Arr[MAX_VM];
PageCon *pf_Idle;        //Page Frame Idle Pointer -> Header

/*-----------------------------------------------------------------*/

void initialization(int n_pf)  //Initialization
{	//n_pf -> total_PageFrame
    int i = 0, counter_pf = 0;  //Set Initial Page Fault to 0
    //Initialize Page Structure
    for (i = 0; i < MAX_VM; i++)
    {
        Page_Arr[i].ID_p = i;
        Page_Arr[i].ID_pf = invalid;   //-1 --> Current Page Hasn't Been Allocated to Memory
        Page_Arr[i].bool_visited = false;
        Page_Arr[i].t_LastAcc = -1;
    }
    //Initialize Memory Page Control Structure
    for (i = 0; i < n_pf - 1; i++)
    {
        PCon_Arr[i].ID_pf = i;         //Initialize Frame Number
        PCon_Arr[i].next = &PCon_Arr[i + 1];  //Establish The 'next' Pointer Connection
    }
    PCon_Arr[n_pf - 1].next = NULL;    //Last Page Control Structure Pointer -> NULL
    PCon_Arr[n_pf - 1].ID_pf = n_pf - 1;  //Last Page Control Structure Frame ID -> 'n_pf - 1'
    pf_Idle = &PCon_Arr[0];            //Memory Idle Frame Pointer -> Page_Control_Array[0]
}

int Algorithm_FIFO(int n_pf)  //First-in, First-out Algorithm
{
    initialization(n_pf);
    int i = 0;
    bool swap = false;
    int occupied[MAX_VM] = {0};  //Reference Bit --> Capacity MAX_VM

    PageCon *pnext = pf_Idle;    //'pf_Idle' Initilized As 'PCon_Arr[0]'
    PageCon *head = pf_Idle;
    counter_pf = 0;

    for (i = 0; i < MAX_INS; i++)  //Excute The Instruction 0 ~ MAX_INS
    {	//page[i] --> Locate The Correponding Page Number of The Given Instruction
        if (Page_Arr[page[i]].ID_pf == invalid)  //Page Fault !
        {
            counter_pf++;  //Page Fault Recorded
            if (occupied[pnext->ID_pf] == 0)             //Have Idle Page Space --> Swap In
            {
                Page_Arr[page[i]].ID_pf = pnext->ID_pf;  //Refresh Corresponding Frame Number
                pnext->ID_p = page[i];                   //Refresh Corresponding Page Number In Memory
                occupied[pnext->ID_pf] = 1;              //Reset 'occupied[]' Info
                pnext = pnext->next;
                if (pnext == NULL)                       //No Following Page --> Point To 'PCon_Arr[0]'
                    pnext = head;
                if (swap == false)                       //The First Wave of Pages Swapping -> No Fault Accured
                    pf_Idle = pf_Idle->next;             //Idle Page Pointer Directly Points to The Following Space
            }
            if (pf_Idle == NULL)                         //No Idle Page Available
            {
                while (occupied[pnext->ID_pf] == 1)      //Is Occupied --> Give Second Chance
                {
                    occupied[pnext->ID_pf] = 0;          //Change State -> Second Chance
                    pnext = pnext->next;                 //Skip
                    if (pnext == NULL)                   //No Following Page --> Point To 'PCon_Arr[0]'
                        pnext = head;
                }
                //Swap Out Victim Page
                Page_Arr[pnext->ID_p].ID_pf = invalid;
                swap = true;
            }
        }
        else  //Page Hit !
            occupied[Page_Arr[page[i]].ID_pf] = 1;
    }
    printf("%6.3f\t", 1 - (float)counter_pf / MAX_INS);
    return 0;
}

int Algorithm_LRU(int n_pf)  //Least-Recently-Used Algorithm
{
    initialization(n_pf);
    int tar_PageNum = -1;    //tar_PageNum --> Target Page Number
    int min_tAcc = 10000;    //min_tAcc --> Time Stamp, Locate The Page Has NO Access for Long
    int CurrentTime = 0;
    counter_pf = 0;

    for (int i = 0; i < MAX_INS; i++)  //Excute The Instruction 0 ~ MAX_INS
    {
        if (Page_Arr[page[i]].ID_pf == invalid)  //Page Fault !
        {
            counter_pf++;  //Page Fault Recorded
            if (pf_Idle == NULL)  //No Idle Page Available
            {
                min_tAcc = 10000;
                //Find Minimum --> Page Hasn't Been Accessed for Long
                for (int j = 0; j < MAX_VM; j++)
                {	//Locate The Page Which Has The Smallest 't_LastAcc' In Memory Currently
                    if (min_tAcc > Page_Arr[j].t_LastAcc && Page_Arr[j].ID_pf != invalid)
                    {
                        min_tAcc = Page_Arr[j].t_LastAcc;  //Rewrite The Minimum Last Access Time Indicator
                        tar_PageNum = j;  //Record Current Target Page Number
                    }
                }

                //The Target Page Will Be Identified As 'Idle' --> Swap Out
                pf_Idle = &PCon_Arr[Page_Arr[tar_PageNum].ID_pf];
                Page_Arr[tar_PageNum].ID_pf = invalid;  //Target Page Identified As 'invalid' --> Swap Out
                Page_Arr[tar_PageNum].t_LastAcc = -1;   //Overwrite The 't_LastAcc' of Target Page
                pf_Idle->next = NULL;
            }
            //Have Idle Page Space --> Swap In
            Page_Arr[page[i]].ID_pf = pf_Idle->ID_pf;   //Swap The New Page In, Replace The Idle Page
            Page_Arr[page[i]].t_LastAcc = CurrentTime;  //Rewrite The 't_LastAcc' Value With Current Time
            pf_Idle = pf_Idle->next;
        }
        else  //Page Hit !
            Page_Arr[page[i]].t_LastAcc = CurrentTime;  //Refresh The Hit Page With Current Time
        CurrentTime++;
    }
    printf("%6.3f\t", 1 - (float)counter_pf / MAX_INS);
    return 0;
}

int Algorithm_OPT(int n_pf)  //Optimal Algorithm
{
    initialization(n_pf);
    int i = 0, j = 0;
    int tar_PageNum = -1;    //tar_PageNum --> Target Page Number
    int max_Dist = -1;       //Most Recent Access Distance
    int counter_dist = 1;    //Distance Stamp Counter
    int dist[MAX_VM] = {0};  //Distance Aray, Record Last Access Distance Info
    counter_pf = 0;

    for (i = 0; i < MAX_INS; i++)  //Excute The Instruction 0 ~ MAX_INS
    {
        if (Page_Arr[page[i]].ID_pf == invalid)  //Page Fault !
        {
            counter_pf++;  //Page Fault Recorded
            if (pf_Idle == NULL)  //No Idle Page Available
            {
                //Initialize Distance Info of Each Page
                for (j = 0; j < MAX_VM; j++)
                {
                    if (Page_Arr[j].ID_pf != invalid)  //Page Is In Memory
                        dist[j] = 10000;
                    else
                        dist[j] = 0;
                }

                //Compute The Distance Info of Every Instruction (Corresponding Page) After Current One
                counter_dist = 1;  //Initialize Counter to 1
                for (j = i + 1; j < MAX_INS; j++)
                {	//If -> Corresponding Page is In Memory && Is The First Time Be Accessed (Only First 'dist' Data Needed)
                    if (Page_Arr[page[j]].ID_pf != invalid && Page_Arr[page[j]].bool_visited == false)
                    {
                        dist[page[j]] = counter_dist;  //Rewrite Distance Info of The In Memory Page
                        Page_Arr[page[j]].bool_visited = true;
                    }
                    counter_dist++;
                }

                //Locate The Target Page With Longest Most Recent Access Distance
                max_Dist = -1;
                for (j = 0; j < MAX_VM; j++)
                {
                    Page_Arr[j].bool_visited = false;
                    if (max_Dist < dist[j])
                    {
                        max_Dist = dist[j];
                        tar_PageNum = j;
                    }
                }

                //The Target Page Will Be Identified As 'Idle' --> Swap Out
                pf_Idle = &PCon_Arr[Page_Arr[tar_PageNum].ID_pf];
                Page_Arr[tar_PageNum].ID_pf = invalid;  //Target Page Identified As 'invalid' --> Swap Out
                pf_Idle->next = NULL;
            }
            //Have Idle Page Space --> Swap In
            Page_Arr[page[i]].ID_pf = pf_Idle->ID_pf;  //Swap The New Page In, Replace The Idle Page
            pf_Idle = pf_Idle->next;
        }
    }
    printf("%6.3f", 1 - (float)counter_pf / MAX_INS);
    return 0;
}

/*-----------------------------------------------------------------*/

int main(int argc, char const *argv[])
{
    srand(10 * getpid());  //occupied Current Process ID As Argument
    //"rand()/(RAND_MAX + 1.0)" -> [0,1)  -->  ran_add -> Integer [0,319]
    int ran_add = (int)((float)(MAX_INS - 1) * (rand() / (RAND_MAX + 1.0)));

    cout << endl << "/*----Generating Random Instruction Flow----*/" << endl;
    int i = 0;
    Ran_Add[i] = ran_add;  //Initialize The First Instruction Address
    for (i = 1; i < MAX_INS; i++)  //Generate Instruction Flow 1 ~ 319
    {
        float ran_num = rand() / (RAND_MAX + 1.0);
        if (Ran_Add[i - 1] == MAX_INS - 1)       //Last Address Has Reached The Ceiling -> 319
            Ran_Add[i] = (int)((float)Ran_Add[i - 1] * (rand() / (RAND_MAX + 1.0)));
        else if (Ran_Add[i - 1] == 0)            //Last Address Has Reached The Floor -> 0
            Ran_Add[i] = (int)((float)(MAX_INS - 1) * (rand() / (RAND_MAX + 1.0)));
        else if (ran_num <= 0.5)                 //50% --> The Following Address
            Ran_Add[i] = Ran_Add[i - 1] + 1;
        else if (ran_num <= 0.75)                //25% --> Address Before Last One
            Ran_Add[i] = (int)((float)Ran_Add[i - 1] * (rand() / (RAND_MAX + 1.0)));
        else                                     //25% --> Address Behind Last One
            Ran_Add[i] = Ran_Add[i - 1] + (int)((float)((MAX_INS - 1) - Ran_Add[i - 1]) * (rand() / (RAND_MAX + 1.0)));
    }
    for (i = 0; i < MAX_INS; i++)  //Transfer Instruction Flow Into Page Sequence
    {
        page[i] = Ran_Add[i] / 10;
        offset[i] = Ran_Add[i] % 10;
    }

    for (i = 0; i < MAX_INS; i += 4)  //Display The Generated Addresses
    {
        cout << "\t" << Ran_Add[i] << "\t\t" << Ran_Add[i + 1] << "\t\t"
             << Ran_Add[i + 2] << "\t\t" << Ran_Add[i + 3] << endl;
    }

    cout << endl << endl << "/*--Hit Radio of 3 Algorithms On Different Physical Memory Frames--*/" << endl;
    cout << "\tPage\t  FIFO\t  LRU\t  OPT" << endl;
    int total_PageFrame = 0;
    for (total_PageFrame = 4; total_PageFrame <= 32; total_PageFrame++)
    {
        cout << "\t " << total_PageFrame << "\t\t";
        Algorithm_FIFO(total_PageFrame);
        Algorithm_LRU(total_PageFrame);
        Algorithm_OPT(total_PageFrame);
        cout << endl;
    }
    return 0;
}
