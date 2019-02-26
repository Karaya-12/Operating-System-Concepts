#include <iostream>
#include <sys/time.h>
#include "Shop.h"
using namespace std;

//Default Arguments
static int NBARBERS    = 1;
static int NCHAIRS     = 1;
static int NCUSTOMERS  = 10;
static int SERVICETIME = 1000;

class ThreadParam
{
public:
    ThreadParam(Shop *shop, int id, int serviceTime):
        shop(shop), id(id), serviceTime(serviceTime) { };
    ThreadParam():
        shop(NULL), id(-1), serviceTime(1) { };

    Shop *shop;
    int id;                      //Thread ID
    int serviceTime;             //Barber Service Time for Each Customer
};

void* barber(void *arg)          //Barber Main Function
{
    ThreadParam &param = ((ThreadParam *)arg)[0];

    Shop &shop = *(param.shop);
    int  ID_barber = param.id;
    int  serviceTime = param.serviceTime;

    while (true)                 //Infinite Loop -> Call for 2 Main Functions of Barber Thread
    {
        shop.helloCustomer(ID_barber);
        usleep(serviceTime);
        shop.byeCustomer(ID_barber);
    }
}

void* customer(void *arg)        //Customer Main Function
{
    ThreadParam &param = ((ThreadParam *)arg)[0];

    Shop &shop = *(param.shop);
    int  ID_customer = param.id;
    int  serviceTime = param.serviceTime;

    /*Locate The Serving Barber of Current Customer*/
    int bound_barber = -1;
    bound_barber = shop.visitShop(ID_customer);
    if (bound_barber != -1)
        shop.leaveShop(ID_customer, bound_barber);
}

/*-----------------------------------------------------------------*/

int main(int argc, char *argv[])
{
    int nBarbers = -1, nChairs = -1, nCustomers = -1, serviceTime = -1;

    //Arguments Validation
    if (!(argc == 1 || argc == 5))
    {
        cerr << "Error: Invalid Number of Arguments" << endl;
        cerr << "Usage: $ ./sleepingBarbers <nBarbers> <nChairs> <nCustomers> <serviceTime>" << endl;
        cerr << "    OR $ ./sleepingBarbers (All Number Must Be Positive, Non-zero Integers)" << endl;
        return -1;
    }
    else if (argc == 5)          //Full Arguments -> User Fully Personalization
    { nBarbers = atoi(argv[1]); nChairs = atoi(argv[2]); nCustomers = atoi(argv[3]); serviceTime = atoi(argv[4]); }
    else if (argc == 1)          //No Arguments -> Run With Default Arguments
    { nBarbers = NBARBERS; nChairs = NCHAIRS; nCustomers = NCUSTOMERS; serviceTime = SERVICETIME; }

    cout << "Barber Shop Preset Parameters:" << endl;
    cout << "Barbers      : " << nBarbers   << endl;
    cout << "Chairs       : " << nChairs   << endl;
    cout << "Customers    : " << nCustomers << endl;
    cout << "Service Time : " << serviceTime  << endl;
    cout << endl;

    pthread_t barber_threads[nBarbers];
    pthread_t customer_threads[nCustomers];
    Shop shop(nBarbers, nChairs);

    ThreadParam* tempParam_Bar[nBarbers];
    for (int i = 0; i < nBarbers; i++)
    {
        tempParam_Bar[i] = new ThreadParam(&shop, i, serviceTime);
        pthread_create(&barber_threads[i], NULL, barber, (void*)tempParam_Bar[i]);
    }

    ThreadParam* tempParam_Cust[nCustomers];
    for (int i = 0; i < nCustomers; i++)
    {
        usleep(rand() % 1000);   //With Random interval
        tempParam_Cust[i] = new ThreadParam(&shop, i + 1, 0);
        pthread_create(&customer_threads[i], NULL, customer, (void*)tempParam_Cust[i]);
    }

    for (int i = 0; i < nCustomers; i++)   //Wait Until All Customers Have Been Served
    {
        pthread_join(customer_threads[i], NULL);
        delete tempParam_Cust[i];
    }
    for (int i = 0; i < nBarbers; i++)     //Terminate All Barbers
    {
        pthread_cancel(barber_threads[i]);
        delete tempParam_Bar[i];
    }

    cout << "\n\n# Total Number of Customers Who Didn't Receive A Service = " << shop.nDropsOff << endl;

    return 0;
}
