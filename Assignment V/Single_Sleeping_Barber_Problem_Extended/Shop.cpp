#include "Shop.h"

void Shop::initialize()
{
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond_customers_waiting, NULL);
	pthread_cond_init(&cond_customer_served, NULL);
	pthread_cond_init(&cond_barber_leave, NULL);
	pthread_cond_init(&cond_barber_sleeping, NULL);
}

string Shop::int2string(int i)  //Convert Integer To String
{
	stringstream out;
	out << i;
	return out.str();
}

void Shop::print(int type, string message)  //Print Out The 'cutomer'/'barber' Info Neatly
{
	cout << ((type != barber) ? "Customer[" : "Barber  [") << type << "]: " << message << endl;
}

/*-----------------------------------------------------------------*/

int Shop::visitShop(int ID_thread)  //Called By A 'customer' Thread
{
	pthread_mutex_lock(&mutex);  //Lock Up The Critical Region

	if (que_wait.size() == MAX)  //Waiting Queue is Full --> Customers Turn Away
	{
		print(ID_thread, "Has Left The Shop --> No Available Waiting Chairs !");
		++nDropsOff;
		pthread_mutex_unlock(&mutex);  //Unlock The Critical Region
		return -1;
	}

	if (cust_insvc != 0 || !que_wait.empty())  //Current 'customer' Has To Wait --> Push Into The Waiting Queue
	{	//Still Got 'customer's Waiting --> All 'barber's Are Working
		que_wait.push(ID_thread);       //Following 'customer' Takes A Seat

		print(ID_thread, "Has Took A Seat.\n# Currently Waiting Chairs Available = "
		      + int2string(MAX - que_wait.size()));

		pthread_cond_wait(&cond_customers_waiting, &mutex);
		//pthread_cond_wait() --> Unlock -> Wait For The Suitable Condition -> Lock Again
		que_wait.pop();
	}

	print(ID_thread, "Now In Service.\n# Currently Waiting Chairs Available = "
	      + int2string(MAX - que_wait.size()));
	cust_insvc = ID_thread;      //Refresh The In Service ID With Current Thread ID
	status_insvc = true;         //Refresh The Status - In Service

	pthread_cond_signal(&cond_barber_sleeping);  //Wake Up The Barber (In Case Sleeping)
	pthread_mutex_unlock(&mutex);  //Unlock The Critical Region
	return 1;
}

void Shop::leaveShop(int ID_thread)  //Called By A 'customer' Thread
{
	pthread_mutex_lock(&mutex);  //Lock Up The Critical Region

	print(ID_thread, "is Waiting For Haircut to Be Done...");
	while (status_insvc == true)                           //While Being Served
		pthread_cond_wait(&cond_customer_served, &mutex);  //Hold On To Waiting

	status_leave = true;
	pthread_cond_signal(&cond_barber_leave);

	print(ID_thread, "Goodbye Barber");
	pthread_mutex_unlock(&mutex);  //Unlock The Critical Region
}

/*-----------------------------------------------------------------*/

void Shop::helloCustomer()  //Called By A 'barber' Thread
{
	pthread_mutex_lock(&mutex);  //Lock Up The Critical Region

	if (que_wait.empty() && cust_insvc == 0)  //Not In Service & No Customer --> Fall Asleep
	{
		print(barber, "Doen't Have Customer --> Falls Asleep...");
		pthread_cond_wait(&cond_barber_sleeping, &mutex);
	}

	if (cust_insvc == 0)         //Check The Customer In Service
		pthread_cond_wait(&cond_barber_sleeping, &mutex);

	print(barber, "Starts a Hair-cut Service for Customer[" + int2string(cust_insvc) + "]");
	pthread_mutex_unlock(&mutex);  //Unlock The Critical Region
}

void Shop::byeCustomer()  //Called By A 'barber' Thread
{
	pthread_mutex_lock(&mutex);  //Lock Up The Critical Region

	status_insvc = false;        //Refresh The Status --> false
	print(barber, "Done With a Hair-cut Service for Customer[" + int2string(cust_insvc) + "]");

	status_leave = false;
	pthread_cond_signal(&cond_customer_served);  //Sign The 'customer' Thread --> All Set

	while (status_leave == false)
		pthread_cond_wait(&cond_barber_leave, &mutex);

	cust_insvc = 0;              //Refresh The In Service Customer --> None
	print(barber, "Calls In Another Customer...");
	pthread_cond_signal(&cond_customers_waiting);  //Sign The 'customer' Thread For Next One

	pthread_mutex_unlock(&mutex);  //Unlock The Critical Region
}
