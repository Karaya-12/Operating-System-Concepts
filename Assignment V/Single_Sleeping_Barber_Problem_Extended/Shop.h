#ifndef _SHOP_ORG_H_
#define _SHOP_ORG_H_
#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
using namespace std;

#define DEFAULT_CHAIRS 3     //The Default Number of Chairs For Waiting = 3
#define DEFAULT_BARBERS 1    //The Default Number of Barbers = 1

class Shop
{
private:
    const int MAX;              //Max Number of Threads --> Max Number of 'customer' Waiting
    int cust_insvc;             //Current In Service 'customer' Thread ID_thread
    bool status_insvc;          //Status - 'customer' In Service
    bool status_leave;          //Status - 'customer' Able to Leave
    queue<int> que_wait;        //Queue of The Waiting Threads' IDs

    pthread_mutex_t mutex;
    pthread_cond_t cond_customers_waiting;
    pthread_cond_t cond_customer_served;
    pthread_cond_t cond_barber_leave;
    pthread_cond_t cond_barber_sleeping;

    void initialize();
    string int2string(int i);

    static const int barber = 0; //The ID of The 'barber' Thread
    void print(int type, string message);  //Print Out The Info of 'customer'/'barber' Neatly
public:
    //Initialize --> nBarbers & nChairs
    Shop(int nChairs): MAX((nChairs > 0) ? nChairs : DEFAULT_CHAIRS),
        cust_insvc(0), status_insvc(false), status_leave(false), nDropsOff(0)
    { initialize(); };
    //Default Initialize --> 1 Barber & 3 Chairs
    Shop(): MAX(DEFAULT_CHAIRS),
        cust_insvc(0), status_insvc(false), status_leave(false), nDropsOff(0)
    { initialize(); };

    int nDropsOff;           //Total Number of 'customer' Dropped Off

    int visitShop(int ID_thread);  //Return Ture Only When Customer Got A Service
    void leaveShop(int ID_thread);
    void helloCustomer();
    void byeCustomer();
};

#endif
