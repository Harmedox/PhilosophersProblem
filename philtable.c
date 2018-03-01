/* philtable.c    */

   #include  <sys/types.h>
   #include  <pthread.h>

   #define PHILNUM 5

   typedef enum {thinking, hungry, eating} philstat;

   typedef struct tablestruct {
     pthread_t t[PHILNUM];
     int self[PHILNUM];
     pthread_mutex_t mutex;
     pthread_cond_t condition[PHILNUM];
     philstat status[PHILNUM];
     } table;

   table * tab;

   void printstate(void){
     /* Prints out state of philosophers as, say, TEHHE, meaning */
     /* that philosopher 0 is thinking, philosophers 1 and 4 are eating, and*/
     /* philosophers 2 and 3 are hungry.*/
     static char stat[] = "THE";
     int i;
     for (i=0; istatus)[i]]);}
     printf("\n");
   }

   int test (int i) {
     if (
         ((tab->status)[i] == hungry) &&
         ((tab->status)[(i+1)% PHILNUM] != eating) &&
         ((tab->status)[(i-1+PHILNUM)% PHILNUM] != eating)) {
       (tab->status)[i] = eating;
       pthread_cond_signal(&((tab->condition)[i]));
       return 1;
     }
     return 0;
   }

   void pickup(int k) {
     pthread_mutex_lock(&(tab->mutex));
     (tab->status)[k] = hungry;
     printstate();
     if (!test(k)) {
       pthread_cond_wait(&((tab->condition)[k]), &(tab->mutex));}
     printstate();
     pthread_mutex_unlock(&(tab->mutex));
   }

   void putdown(int k) {
     pthread_mutex_lock(&(tab->mutex));
     (tab->status)[k] = thinking;
     printstate();
     test((k+1)%PHILNUM);
     test((k-1+PHILNUM)%PHILNUM);
     pthread_mutex_unlock(&(tab->mutex));
   }

   table * tableinit(void *(* philosopher)(void *)) {
     int i;
  
     tab = (table *) malloc (sizeof(table));
     if(pthread_mutex_init(&(tab->mutex), pthread_mutexattr_default) != 0) {
       perror("pthread_mutex_init");
       exit(1);}
     for (i=0; iself)[i] = i;
       (tab->status)[i] = thinking;
       if(pthread_cond_init(&((tab->condition)[i]), pthread_condattr_default) 
          != 0) {
         perror("pthread_cond_init");
         exit(1);}
     }
     for (i=0; it)[i]),pthread_attr_default,
	   	       philosopher, &((tab->self)[i]))!= 0) {
         perror("pthread_create");
         exit(1);}
     }
     return tab;
   }
