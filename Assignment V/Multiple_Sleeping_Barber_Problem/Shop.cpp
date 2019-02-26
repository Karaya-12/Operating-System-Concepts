#include "Shop.h"

Shop::Shop(int nBarbers, int nChairs)
{
	this->nBarbers = nBarbers;
	this->nChairs = nChairs;
	initialize();
}

Shop::Shop()
{
	this->nBarbers = DEFAULT_BARBERS;
	this->nChairs = DEFAULT_CHAIRS;
	initialize();
}

Shop::~Shop()
{
	delete [] cond_barber_paid;
	delete [] cond_customer_served;
	delete [] cond_barber_sleeping;

	delete [] barberArray;
	delete [] in_service;
	delete [] money_paid;
	delete [] service_chair;

	barberArray = NULL;
	in_service = NULL;
	money_paid = NULL;
	service_chair = NULL;
}

/*-----------------------------------------------------------------*/

void Shop::initialize()
{
	this->AllBarAVL = false;
	this->nDropsOff = 0;

	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_init(&mutex_custWait, NULL);
	pthread_mutex_init(&mutex_custVisitShop, NULL);
	pthread_mutex_init(&mutex_custLeaveShop, NULL);
	pthread_mutex_init(&mutex_barbHelloCust, NULL);
	pthread_mutex_init(&mutex_barbByeCust, NULL);

	this->cond_barber_paid     = new pthread_cond_t[nBarbers];
	this->cond_customer_served = new pthread_cond_t[nBarbers];
	this->cond_barber_sleeping = new pthread_cond_t[nBarbers];

	pthread_cond_init(&cond_customers_waiting, NULL);
	for (int i = 0; i < nBarbers; i++)
	{
		pthread_cond_init(&cond_barber_paid[i], NULL);
		pthread_cond_init(&cond_customer_served[i], NULL);
		pthread_cond_init(&cond_barber_sleeping[i], NULL);
	}

	/*bool Array Initialization*/
	this->barberArray = new int[nBarbers];
	this->service_chair = new int[nBarbers];
	for (int i = 0; i < nBarbers; i++)
		service_chair[i] = -1;

	this->in_service = new bool[nBarbers];
	for (int i = 0; i < nBarbers; i++)
		in_service[i] = false;

	this->money_paid = new bool[nBarbers];
	for (int i = 0; i < nBarbers; i++)
		money_paid[i] = false;
}

string Shop::int2string(int i)   //Convert Integer To String
{
	stringstream out;
	out << i;
	return out.str();
}

void Shop::print(int person, string message, bool isBarber)  //Formatted Output
{
	if (isBarber)
		cerr << "Barber  [" << person << "]: " << message << endl;
	else
		cerr << "Customer[" << person << "]: " << message << endl;
}

/*-----------------------------------------------------------------*/
/*Step C-00 -> Turn Away                         Step B-00 -> Sleeping
 *Step C-11 -> Take A Waiting Chair              Step B-11 -> Be Woken Up
 *Step C-12 -> Exit Current Waiting Chair
 *Step C-21 -> Move To Service Chair
 *Step C-22 -> Wake Up Bounded Barber
 *Step C-23 -> In Service                        Step B-21 -> In Service
 *Step C-31 -> Service Completed                 Step B-31 -> Service Completed
 *Step C-32 -> Pay The Barber                    Step B-32 -> Payment Confirmed
 *Step C-41 -> Leave The Shop                    Step B-41 -> Reset The Service Chair & Call for Next Customer*/

int Shop::visitShop(int ID_customer)  //Called By A 'customer' Thread
{
	pthread_mutex_lock(&mutex);  //Lock Up The Critical Region

	bool isBarber = false;
	bool ChairAVL = false;       //Find If Any Chair is Available
	for (int i = 0; i < nBarbers; i++)
	{
		if (service_chair[i] == -1)  //service_chair[] --> Initially Set To -1
		{
			ChairAVL = true;
			break;
		}
	}

	bool senario_1, senario_2;   //2 Senarios That Customers Will Turn Away
	senario_1 = (que_wait.size() == nChairs && nChairs != 0);  //Waiting Queue is Full
	senario_2 = (nChairs == 0 && ChairAVL == false);           //Neither Service Chair Nor Waiting Chair is Available
	if (senario_1 || senario_2)
	{
		print(ID_customer, "Step C-00 - Has Left The Shop --> No Available Waiting Chairs !", isBarber);
		++nDropsOff;
		pthread_mutex_unlock(&mutex);  //Unlock The Critical Region
		return (-1);
	}

	/*Waiting Chairs / Service Chairs Are Available --> Push Current Customer Into The Waiting Queue*/
	if (!que_wait.empty() || ChairAVL == false)
	{
		que_wait.push(ID_customer);
		print(ID_customer, "Step C-11 - Has Took A Seat.\n# Currently Waiting Chairs Available = "
		      + int2string(nChairs - que_wait.size()), isBarber);
		pthread_cond_wait(&cond_customers_waiting, &mutex);

		que_wait.pop();
		print(ID_customer, "Step C-12 - Exits A Waiting Chair.\n# Currently Waiting Chairs Available = "
		      + int2string(nChairs - que_wait.size()), isBarber);
	}

	int AVLChairNum = -1;        //The Number of The First Available Service Chair
	for (int i = 0; i < nBarbers; i++)
	{
		if (service_chair[i] == -1)
		{	//Record The First Available Service Chair
			AVLChairNum = i;
			break;
		}
	}
	print(ID_customer, "Step C-21 - Moves to Service Chair[" + int2string(AVLChairNum) + "]", isBarber);

	service_chair[AVLChairNum] = ID_customer;  //Refresh The In Service ID With Current Customer ID
	in_service[AVLChairNum] = true;  //Refresh The Status - In Service

	print(ID_customer, "Step C-22 - Wake Up Barber[" + int2string(AVLChairNum) + "]", isBarber);
	print(ID_customer, "Step C-23 - In Service...", isBarber);
	pthread_cond_signal(&cond_barber_sleeping[AVLChairNum]);  //Wake Up The Barber (In Case Sleeping)
	pthread_mutex_unlock(&mutex);  //Unlock The Critical Region

	return (AVLChairNum);
}

void Shop::leaveShop(int ID_customer, int ID_barber)  //Called By A 'customer' Thread
{
	bool isBarber = false;
	pthread_mutex_lock(&mutex);  //Lock Up The Critical Region

	if (in_service[ID_barber] == true)  //In Service --> Wait for The Service To Be Completed
	{
		pthread_cond_wait(&cond_customer_served[ID_barber], &mutex);
		print(ID_customer, "Step C-31 - Service Completed", isBarber);
	}
	money_paid[ID_barber] = true;

	print(ID_customer, "Step C-32 - Pay The Barber", isBarber);
	print(ID_customer, "Step C-41 - Leave The Shop", isBarber);

	pthread_cond_signal(&cond_barber_paid[ID_barber]);
	pthread_mutex_unlock(&mutex);  //Unlock The Critical Region
}

/*-----------------------------------------------------------------*/

void Shop::helloCustomer(int ID_barber)  //Called By A 'barber' Thread
{
	pthread_mutex_lock(&mutex);  //Lock Up The Critical Region

	bool isBarber = true;
	bool NoCustomer = true;      //Currently No Customer In The Shop
	if (ID_barber == nBarbers - 1)  //All Barbers Are Available
		AllBarAVL = true;
	if (!que_wait.empty())       //Still Got Customer(s) Waiting
		NoCustomer = false;
	else                         //Further Check If All Service Chair Are Empty --> No Customer
	{
		for (int i = 0; i < nBarbers; i++)
		{
			if (service_chair[i] != -1)
			{
				NoCustomer = false;
				break;
			}
		}
	}

	if (NoCustomer && AllBarAVL)
	{	//Hibernate All Barber Threads
		for (int i = 0; i < nBarbers; i++)
			print(i, "Step B-00 - Doen't Have Customer --> Falls Asleep...", isBarber);

		pthread_cond_wait(&cond_barber_sleeping[ID_barber], &mutex);
		print(ID_barber, "Step B-11 - Has Been Woken Up !", isBarber);
	}
	else if (service_chair[ID_barber] == -1)
		pthread_cond_wait(&cond_barber_sleeping[ID_barber], &mutex);

	print(ID_barber, "Step B-21 - Starting A Hair-cut Service for Bounded Customer["
	      + int2string(service_chair[ID_barber]) + "]", isBarber);
	pthread_mutex_unlock(&mutex);  //Unlock The Critical Region
}

void Shop::byeCustomer(int ID_barber)  //Called By A 'barber' Thread
{
	pthread_mutex_lock(&mutex);  //Lock Up The Critical Region

	bool isBarber = true;
	print(ID_barber, "Step B-31 - Completed Service for Bounded Customer["
	      + int2string(service_chair[ID_barber]) + "]", isBarber);

	in_service[ID_barber] = false;
	money_paid[ID_barber] = false;

	pthread_cond_signal(&cond_customer_served[ID_barber]);

	if (money_paid[ID_barber] == false)
	{	//Hibernate Until Signal Received leaveShop()
		pthread_cond_wait(&cond_barber_paid[ID_barber], &mutex);
		print(ID_barber, "Step B-32 - Payment Confirmed", isBarber);
	}

	service_chair[ID_barber] = -1;  //Service Chair Reset To -1
	print(ID_barber, "Step B-41 - Resets Service Chair, Calls for Next Customer", isBarber);

	pthread_cond_signal(&cond_customers_waiting);
	pthread_mutex_unlock(&mutex);  //Unlock The Critical Region
}
