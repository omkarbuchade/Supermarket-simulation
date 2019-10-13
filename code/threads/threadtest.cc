
//include necessary files
#include "kernel.h"
#include "main.h"
#include "thread.h"
#include "supermarket.h"
#include "../lib/list.h"
#include <cstdlib>
#include <math.h>

// Function to divide two numbers since Nachos does not perform floating point division efficiently.
float divide (int x,int y)
{
 int c1=0;
 int c2=0;
 if(x>y)
    {
    while (x-y > 0)
    {
        x=x-y;
        c1++;
    }
    x=x*100;
    while(x-y >= 0)
    {
        
        c2++;
        x=x-y;
    }
    return (c1+ 0.01*c2);
 }
 else if (x==y)
    return 1;
else
{
    x=x*100;
    while(x-y >= 0)
    {
        
        c2++;
        x=x-y;
    }
    return (0.01*c2);
}
}

// Supermarket method that simulates our supermarket
void
SuperMarket()
{
    int num_customers=0; //keep a track of total customers
    List <Customer*> *waitingQueue =new List<Customer*>(); //waiting queue to enqueue customers

	Cashier *Cashier1 =new Cashier(1);  //cashier 1 
	Cashier *Cashier2 =new Cashier(2);  // cashier 2

	List <Cashier*> *CashierList =new List<Cashier*>();
    CashierList->Append(Cashier1);
    CashierList->Append(Cashier2);

    //Defining iterators for cashier list and waiting queue
    ListIterator<Cashier *> *iterator = new ListIterator<Cashier *>(CashierList) ;  
    ListIterator<Cashier *> *iterator1 = new ListIterator<Cashier *>(CashierList) ;  
    ListIterator<Customer *> *WQiterator = new ListIterator<Customer *>(waitingQueue) ;  

// Declaring variables for keeping a track of simulation 
int time_min =1, cashierNo=2, hourlycustomers=0, hourlylines=0, hour=1, maxOpenLines=0;
int totalServingTime=0, minServingTime=999, maxServingTime= 0, avgCustWQ=0, minCustWQ=999;
int maxCustWQ=0, avgTimeCashier=0, EntireServiceTime, EntireServiceTimeMin=999;
int EntireServiceTimeMax=0, waitingTime=0, minwaitingTime=999, maxwaitingTime=0;
int EntirewaitingTime=0, EntireminwaitingTime=999,EntiremaxwaitingTime=0, sTime;

while (time_min < 300) // 300 minutes since 2-7 PM is 300 minutes 
	{
        int flag=0;
        *iterator =  ListIterator<Cashier *>(CashierList);  
        *iterator1 = ListIterator<Cashier *>(CashierList); 
		int customers ;
		if (time_min <120 || time_min > 240)
			customers = rand() % 6 ;
		else
			customers = rand() % 6 + 5;   //peak hours

        //customers = 3;        // uncomment line for running test case
        //check if there any vacancy in cashier queue
        while(!iterator1->IsDone())
        {
            Cashier *currCashier = iterator1->Item();
            sTime = currCashier->simulateFront();
            if(sTime !=0)
            {
                waitingTime = waitingTime + time_min - sTime;

                if(minwaitingTime > time_min - sTime)
                    minwaitingTime = time_min - sTime;

                if(maxwaitingTime < time_min - sTime)
                    maxwaitingTime = time_min - sTime;
            }
            iterator1->Next();
        }
        if(CashierList->NumInList()==10)
        {
            *iterator =  ListIterator<Cashier *>(CashierList);  
            
            while(!iterator->IsDone())
            {
            Cashier *currCashier = iterator->Item();
                if(currCashier->get_num_customers() > 2)
                {
                    iterator->Next();
                    continue;
                }
                else
                    flag=1;
                break;
            }
        }
        else
            flag=1;
            
        if(flag==0)
            avgTimeCashier++;
        

		while (customers!=0)
		{
            num_customers++;
			int item = rand() % 36 + 5 ;
            //item = 6; //uncomment line to run the test case
            Customer *cust = new Customer(num_customers, item, time_min);	
            	
            waitingQueue->Append(cust);
            totalServingTime=totalServingTime+cust->get_checkout_time();
            if(minServingTime >  cust->get_checkout_time())
            {
                minServingTime = cust->get_checkout_time();
            }
            if(maxServingTime <  cust->get_checkout_time())
            {
                maxServingTime = cust->get_checkout_time();
            }

            customers --;
		}
        *iterator =  ListIterator<Cashier *>(CashierList);  
        while(!iterator->IsDone())
                {
                    Cashier *currCashier = iterator->Item();
                    while (!waitingQueue->IsEmpty() && currCashier->get_num_customers() < 5)
                    {
                        Customer * cust = waitingQueue->RemoveFront();
                        currCashier->add_customer(cust);
                    }
                    iterator->Next();
                }
 
        //add new cashier if customers in waiting queue is more than 10
        if(waitingQueue-> NumInList()>10)
        {
            if(cashierNo<10)  // Limit maximum cashiers to 10
            {
                cashierNo++;
                Cashier *Cashiernew =new Cashier(cashierNo);
                CashierList->Append(Cashiernew);

                while(!waitingQueue->IsEmpty() && Cashiernew->get_num_customers()<5)
                {
                    Customer * cust = waitingQueue->RemoveFront();
                    Cashiernew->add_customer(cust);
                }
            }
        }
        avgCustWQ = avgCustWQ + waitingQueue->NumInList(); 
        if(minCustWQ > waitingQueue->NumInList())
        {
            minCustWQ = waitingQueue->NumInList();
        }

        if(maxCustWQ < waitingQueue->NumInList())
        {
            maxCustWQ = waitingQueue->NumInList();
        }

        if(!waitingQueue->IsEmpty())
        {
            *iterator =  ListIterator<Cashier *>(CashierList);  
            iterator->Next();
            iterator->Next();
            while(!iterator->IsDone())
                {
                    Cashier *currCashier = iterator->Item();
                    if (currCashier->get_num_customers()==0)
                    {
                        CashierList->Remove(currCashier);   
                        cashierNo--;
                    }
                iterator->Next();  
                }
        }

    *iterator =  ListIterator<Cashier *>(CashierList);  
    while(!iterator->IsDone())
    {
        Cashier *currCashier = iterator->Item();
        currCashier->summary();
        iterator->Next();
    }

	time_min ++;	
    hourlylines=hourlylines+ cashierNo;
    if(maxOpenLines<cashierNo)
    {
        maxOpenLines= cashierNo;    
    }

    //print requirements
    if(time_min%60==0)
    {
        hour++;
        int cust=num_customers-hourlycustomers;
        printf("\n \n");
        printf("===================  Hourly summary for %d:00 to %d:59 PM   ================================ \n",hour,hour);
        printf(" Average no of customers arriving for checkout per minute: %.2f \n ",divide(cust,60));
        printf("Average waiting time per customer: %.2f \n ",divide(waitingTime,cust));
        printf("Shortest waiting time: %d \n ",minwaitingTime);
        printf("Longest waiting time: %d \n ",maxwaitingTime);
        printf("Average serving time per customer: %.2f \n ",divide(totalServingTime,cust));
        printf("Shortest serving time: %d \n ",minServingTime);
        printf("Longest serving time: %d \n ",maxServingTime);
        printf("Average no of open lines: %.2f \n ",divide(hourlylines,60));
        printf("Maximum no of open lines: %d \n ",maxOpenLines);
        printf("Average time each cashier will have more than 3 customers standing in line per minute: %.2f \n ",divide(avgTimeCashier,60));
        printf("Average number of customers in waiting queue: %.2f \n ",divide(avgCustWQ,60));
        printf("Smallest number of customers in waiting queue: %d \n ",minCustWQ);
        printf("Largest number of customers in waiting queue: %d \n ",maxCustWQ);
        printf("------------------------------------------------------------------------------- \n");

        EntireServiceTime=EntireServiceTime+ totalServingTime;
        if(EntireServiceTimeMin >minServingTime )
            EntireServiceTimeMin =minServingTime;

        if(EntireServiceTimeMax  < maxServingTime )
            EntireServiceTimeMax =maxServingTime;


        EntirewaitingTime =EntirewaitingTime+ waitingTime;
        if(EntireminwaitingTime >minwaitingTime )
            EntireminwaitingTime =minwaitingTime;

        if(EntiremaxwaitingTime  < maxwaitingTime )
            EntiremaxwaitingTime =maxwaitingTime;

        hourlylines=0;
        totalServingTime=0;
        maxOpenLines=0;
        hourlycustomers= num_customers;
        minServingTime=999;
        maxServingTime=0;
        avgCustWQ=0;
        minCustWQ =999;
        maxCustWQ=0;
        avgTimeCashier=0;
        waitingTime=0;
        minwaitingTime=999;
        maxwaitingTime=0;

    }
	}
        printf(" ------------------------------------------------------------------------------- \n \n");
        printf("\n\n\n");
        printf("============================  Entire simulation summary  ======================== \n ");
        printf("Average waiting time: %.2f \n ", divide(EntirewaitingTime,num_customers) );
        printf("Shortest waiting time: %d \n ", EntireminwaitingTime);
        printf("Longest waiting time: %d \n ", EntiremaxwaitingTime);
        printf("Average serving time: %.2f \n ", divide(EntireServiceTime,num_customers) );
        printf("Shortest serving time: %d \n ", EntireServiceTimeMin);
        printf("Longest serving time: %d \n ", EntireServiceTimeMax );
        printf("Maximum number of customers in waiting queue: %d \n ", waitingQueue->NumInList() );
        printf("------------------------------------------------------------------------------- \n");
        printf(" -------------------------------  End of summary  ------------------------------ \n");
        printf(" ------------------------------------------------------------------------------- \n \n");

}

void ThreadTest()
{
    Thread *t = new Thread("forked thread");
    t->Fork((VoidFunctionPtr) SuperMarket, NULL);
    //SuperMarket();
}
