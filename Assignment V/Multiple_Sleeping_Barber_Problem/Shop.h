#ifndef _SHOP_H_
#define _SHOP_H_
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
    int nBarbers, nChairs;
    bool isBarber;           //Barber Thread Identifier
    bool AllBarAVL;          //All Barbers Are Available

    int* barberArray = NULL;
    int* service_chair = NULL;
    bool* in_service = NULL;
    bool* money_paid = NULL;

    queue<int> que_wait;         //Queue of The ID of Waiting Customers

    pthread_mutex_t mutex;
    pthread_mutex_t mutex_custWait;
    pthread_mutex_t mutex_custVisitShop;
    pthread_mutex_t mutex_custLeaveShop;
    pthread_mutex_t mutex_barbHelloCust;
    pthread_mutex_t mutex_barbByeCust;

    pthread_cond_t  cond_customers_waiting;
    pthread_cond_t* cond_barber_paid     = NULL;
    pthread_cond_t* cond_customer_served = NULL;
    pthread_cond_t* cond_barber_sleeping = NULL;

    void initialize();
    string int2string(int i);
    void print(int person, string message, bool isBarber);  //Print Out The Info of 'customer'/'barber' Neatly
public:
    int nDropsOff;  //Total Number of 'customer' Dropped Off

    Shop(int nBarbers, int nChairs);  //Initialize --> nBarbers & nChairs
    Shop();  //Default Initialize --> 1 Barber & 1 Chair
    ~Shop();

    int visitShop(int ID_customer);  //Return Current In Service Chair Number
    void leaveShop(int ID_customer, int ID_barber);
    void helloCustomer(int ID_barber);
    void byeCustomer(int ID_barber);
};

#endif
