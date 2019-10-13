#include "../lib/list.h"

//Customer class to define customer data stores and methods
class Customer
{
private:
	int checkout_time; //store serving time of customer in minutes
    int items; //store number of items customer has;
    int id; // unique identifier for each customer
    int starttime;//variable to keep a track of start time
public:
	Customer(int, int, int); // constructor sets the id and calculates the serving time of the customer
	int get_checkout_time();  // returns the serving time of customer
    int decrement_checkout_time(); // decrements serving time of a customer by 1 minute
    int get_id(); // get id id the customer
    int getStartTime(); // get customers arrival time at supermarket
    int getItems(); // return number of item customer has
    ~Customer();// destructor to deallocate the memory	

};

//cashier class to define cashier data stores and methods
class Cashier
{
private:
	List <Customer*> *cashier =new List<Customer*> (); //list to store customers in cashier list
	int num_customers; //Keep a track of customers in cashier queue
    int id; //unique identifier for cashier

public:
	Cashier(); //default constructor
    Cashier(int); //parameterized constructors that sets id for the cashier
	int get_num_customers(); //returns number of customers in cashier queue
	void add_customer(Customer*); // add customer to cashier queue
    List <Customer*> getQueue(); //returns the cashier queue
    int simulateFront(); //used to check availability in the cashier
    int getid(); //returns the id of cashier
    void summary(); //prints summary results of the cashier
	~Cashier();	// destructor to deallocate the memory	
};

