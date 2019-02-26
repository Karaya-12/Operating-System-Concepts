#include <iostream>      //Cout
#include <sys/time.h>    //Gettimeofday
#include "Shop.h"
using namespace std;

//Function Prototype
void *barber(void *);    //The Prototype of The Barber Thread Function
void *customer(void *);  //The Prototype of The Customer Thread Function

int main(int argc, char *argv[])
{
    //Validate The Arguments & Pop Out Usage Hint (if not correctly running)
    if (argc != 5)
    {
        cerr << "Illegal Input ! Please Follow The Usage Hint Below : " << endl
             << "Input Arguments - 'SleepingBarber' 'nBaerbers' 'nChairs' 'nCustomers' 'ServiceTime'" << endl;
        return -1;
    }

    int nChairs = atoi(argv[2]);       //Chairs Available For Customers to Wait On
    int nCustomers = atoi(argv[3]);    //Customers Who Need A Haircut Service
    int serviceTime = atoi(argv[4]);   //Each Barber's Service Time (u seconds)

    pthread_t barber_thread;
    pthread_t customer_threads[nCustomers];
    Shop shop(nChairs);                //Instantiate A Barbershop

    void *barber_param[2] = { (void *)&shop, (void *)&serviceTime };
    pthread_create(&barber_thread, NULL, barber, barber_param);
    for (int i = 0; i < nCustomers; i++)
    {
        usleep(rand() % 1000);
        int id = i + 1;
        void *customer_param[2] = { (void *)&shop, (void *)&id };
        pthread_create(&customer_threads[i], NULL, customer, customer_param);
    }

    for (int i = 0; i < nCustomers; i++)
        pthread_join(customer_threads[i], NULL);

    pthread_cancel(barber_thread);
    cout << "# Total Number of Customers Who Didn't Receive A Service = " << shop.nDropsOff << endl;

    return 0;
}

//The Barber Thread Function
void *barber(void *arg)
{
    void **args = (void **)arg;
    Shop &shop = *(Shop *)args[0];
    int serviceTime = *(int *)args[1];

    //Keep Working Until Being Terminated By main()
    while (true)
    {
        shop.helloCustomer();    //Pick Up A New Customer
        usleep(serviceTime);     //Spend A Service Time
        shop.byeCustomer();      //Release The Customer
    }
}

//The Customer Thread Function
void *customer(void *arg)
{
    void **args = (void **)arg;
    Shop &shop = *(Shop *)args[0];
    int id = *(int *)args[1];

    if (shop.visitShop(id) == true)
        shop.leaveShop(id);
}
