My solution is based on the code found at https://mariusbancila.ro/blog/2017/01/16/dining-philosophers-in-cpp11/, which is the default code in the assignment.

The actual solution came from https://en.wikipedia.org/wiki/Dining_philosophers_problem#Arbitrator_solution, which we talked about in class.

The basic idea is to create a "waiter" that restricts access to the forks. To get a fork at all, the philosopher must ask the waiter for permission to use them.
The waiter only lets one philosopher eat at a time, which meets the **each philosopher eats one after another sequentially** requirement.
The waiter acts as a guard around the critical section, which is the shared resource of "forks". Instead of allowing philosophers to pick up one fork without picking up the other,
the waiter ensures that both forks must be picked up.

Having a waiter completely eliminates the possibility of deadlock: if only one philosopher can eat at a time, then it is impossible for
two philosophers to try to access the same fork at the same time.

This solutions reduces the concurrency of the code, since it is now possible for up to 4 philosophers to be waiting to eat at once after they
finish thinking, but it seems to be the only way to meet the requirements for the project...
