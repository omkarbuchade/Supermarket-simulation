#include "supermarket.h"
#include <stdio.h>
#include <math.h>

// descriptions of each methods can be found in supermarket.h file

Cashier::Cashier()
{
	num_customers = 0;
}

List <Customer*> Cashier:: getQueue()
{
    return *cashier;
}

Cashier::Cashier(int id_no)
{
	num_customers = 0;
    id=id_no;
}

int Cashier::get_num_customers()
{
	return num_customers;
}
int Cashier::getid()
{
	return id;
}

void Cashier::add_customer(Customer* obj)
{
	num_customers ++;	
	cashier->Append(obj);
}

Customer::Customer(int no, int Items, int sTime)
{
    id=no;
    items= Items;
	float time_sec = 10 + 90 + (5*Items);
	checkout_time = ceil(time_sec/60);
    starttime = sTime;
} 

int Customer::get_checkout_time()
{
	return checkout_time;
} 

int Customer::getStartTime()
{
	return starttime;
} 

int Customer::getItems()
{
	return items;
} 

int Customer::get_id()
{
	return id;
} 

int Customer::decrement_checkout_time() 
{
	checkout_time--;
    return checkout_time;
} 


int Cashier::simulateFront()
{
    int retVal=0;
    ListIterator<Customer *> *cust_iterator = new ListIterator<Customer *>(cashier) ;  
    if(!cust_iterator->IsDone())
    {
        Customer *currCustomer = cust_iterator->Item();
        int ckout_time = currCustomer ->decrement_checkout_time();
        //printf("curr processing time for customer %d is: %d \n",currCustomer->get_id(), currCustomer->get_checkout_time());
        if (ckout_time==0)
        {
        cashier->RemoveFront();
        int items = currCustomer->getItems();     
        float time_sec = 10 + 90 + (5*items);
        int checkout_time = ceil(time_sec/60);
        retVal = currCustomer->getStartTime() + checkout_time;
        num_customers --;
        //printf("Customer %d removed now num_customers for cashier %d is %d \n", currCustomer->get_id(),id, num_customers);
        }
    }
    return retVal;
}

void Cashier::summary()
{
    ListIterator<Customer *> *cust_iterator = new ListIterator<Customer *>(cashier) ;  
    //printf ("Cashier %d has following customers and serving time ", id);
    while(!cust_iterator->IsDone())
    {
        Customer *currCustomer = cust_iterator->Item();
        //printf (" %d : %d ", currCustomer->get_id(),currCustomer->get_checkout_time());
        cust_iterator->Next();
    }
    //printf("\n");
}

