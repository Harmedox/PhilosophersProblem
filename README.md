# PhilosophersProblem

Requirements
1) Run indefinitely
    The program currently continues running until ctrl+c is pressed.
2) Take number of philosophers as a command line argumnet
    The program currently takes an argument of the number of philosophers, with an error message displayed (and exit) if not provided. However, I could not succesfully use this value as the shared mutex variable was declared with this number of philosophers. Getting the input from command line made the declaration variable out of scope.
3) Mutex_lock and condition variables
    The program currently utilizes mutex lock obtained when a philosopher picks up a fork, and released when she is done eating. However, I was not successful in implementing the condition variable to utilize the pthread_cond_wait when only one fork has been picked up.
    
