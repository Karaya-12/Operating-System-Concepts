#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define pi (acos(-1.0))
#define MAX 10
#define p(x) sem_wait(&x)
#define v(x) sem_post(&x)
using namespace std;

int chairs;
sem_t customer, barber;  //Set Up Semaphore - 'customer' & 'barber'
pthread_mutex_t mutex;   //Set Up pthread mutex lock - 'mutex'

void initialize()
{
    chairs = MAX;
    //int sem_init(sem_t *sem, int pshared, unsigned int value);  Set Semaphore Initial Number
    sem_init(&barber, 0, 1);    //Initially 1 Barber
    sem_init(&customer, 0, 0);  //Initially 0 Customer
}

void* _barber(void* arg)
{
    while (true)
    {
        p(customer);                   //Request For One Coming 'cutomer' -> p(customer)
        pthread_mutex_lock(&mutex);    //Lock Up Critial Region
        chairs++;                      //Take One Chair (if available)
        pthread_mutex_unlock(&mutex);  //Unlock Critial Region
        sleep(5);                      //Working Time -> 500 useconds
        cout << "*-*-*-*-*-*\nOne Customer Got His Hair Done....\n*-*-*-*-*-*" << endl << endl;
        v(barber);                     //Release The Working 'barber'
    }
}

void* _customer(void* arg)
{
    int *p = (int*) arg;
    int x = *p;
    pthread_mutex_lock(&mutex);  //Lock Up The Critical Region
    if (chairs > 0)  //Still Have Chairs Available
    {
        chairs--;    //One 'customer' Take One Chair
        v(customer); //Release The 'customer'
        cout << "Customer No." << x << " Takes A Seat and Wait For The Barber...\n"
             << "Total: " << MAX - chairs << " Customers Are Waiting..." << endl << endl;
        pthread_mutex_unlock(&mutex);  //Unlock The Critical Region
        p(barber);   //Request For 'barber'
    }
    else  //No More Available Chairs --> Critical Region & 'barber' Not Affected !
    {
        pthread_mutex_unlock(&mutex);  //Unlock The Critical Region
        cout << "Customer No." << x << " Went Away !" << endl << endl;
    }
}


int main(int argc, char const *argv[])
{
    int i, cid[MAX * 100];
    initialize();
    pthread_t sl_bar;
    pthread_t pthreads[MAX * 100];
    pthread_create(&sl_bar, NULL, _barber, NULL);
    for (i = 0; i < MAX * 100; i ++)
    {
        sleep(1);
        cid[i] = i;
        pthread_create(&pthreads[i], NULL, _customer, &cid[i]);
    }
    pthread_join(sl_bar, NULL);
    for (i = 0; i < MAX * 100; i++)
        pthread_join(cid[i], NULL);
}
