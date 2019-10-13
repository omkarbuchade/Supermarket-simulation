# Supermarket-simulation
Supermarket cashier simulation using Nachos to determine the number of cashiers required based on the average number of customers at different times.

Following are the constraints upon which the simulation is based:
1. Each cashier line is a queue object.
2. A casher takes an average of 5 seconds to scan a single item for a customer.
3. The average startup time for a check out (greeting a new customer, moving the conveyer belt to reach items, …) is 10 seconds.
4. The average close time for a check out (getting the total, handling coupons, getting payments, …) is 1.5 minute.
5. Customers, checking out have a random number of items, average range between 5 to 40 items.
6. Peak hours are between 4 to 6 pm and random number of customers arriving for a check out is between 5 and 10 every minute.
7. During regular hours customers between 0 and 5 arrive every minute.
8. There are maximum 10 checkout lines and minimum 2 lines. Depends on waiting customers checkout lines can open/close.
9. Each casher cannot have more than 5 customers in line.
10. There is a single waiting queue of arriving customers for a casher when all open lines are full. If there are more than 10 customers in this queue, open a new line.
11. If there is no customer in the waiting queue and the last customer of a checkout line is served, the line will be closed.
12. Run the supermarket simulation from 2 pm to 7 pm.


To simulate the Nachos OS in Linux environment execute the following commands on the terminal:
1. navigate to the directory: /code/build.linux
2. make depend
3. make
4. ./nachos -K
