/* philmain.c    */

   #include  "philtable.h"

   void * philosopher(int * a); 

   int main(void) {
     void * tab = tableinit(philosopher);
     sleep(60);  // Wait a while then exit
     printf("WE ARE DONE\n");}

   void * philosopher(int * who) {
     /* For simplicity, all philosophers eat for the same amount */
     /* of time and think for a time that is simply related */
     /* to their position at the table. The parameter who identifies*/
     /* the philosopher: 0, 1, 2, .. */
     while (1){
       sleep((*who)+1);
       pickup((*who));
       sleep(1);
       putdown((*who));}}
