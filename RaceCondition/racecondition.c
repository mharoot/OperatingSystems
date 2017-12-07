#include <stdio.h>
#include <pthread.h>
#include <time.h>

int sum = 0;
//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct P1 {
    int offset;
    int loops;
    int id;
};


void* count_by_threads(void* arg) {

    struct P1 process =  * (struct P1 *) arg;
    int NUM_LOOPS = process.loops;
    int offset    = process.offset;
    int id        = process.id;

    for(int i = 0; i < NUM_LOOPS; i++) {
        // Start critical section - locking this means only one thread at a time can run this section of code until the unlock
//        pthread_mutex_lock(&mutex);
          printf("\nid: %d, sum: %d", id, sum);

        sum += offset;
          printf("\nid: %d, sum: %d", id, sum);

//        struct timespec tim, tim2;
//        tim.tv_sec = 0;
//        tim.tv_nsec = 10000000L;
//        nanosleep(&tim , &tim2);
        // End critical section
//        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

int main(void){

for(int i = 0; i < 10000000; i++)
{
   struct P1 p1_struct;
   p1_struct.offset = -1;
   p1_struct.loops = 5;
   p1_struct.id = 1;

   struct P1 p2_struct;
   p2_struct.offset = 1;
   p2_struct.loops = 4;
   p2_struct.id = 2;

   // Spawn Threads
   pthread_t id1;
   pthread_create(&id1, NULL, count_by_threads, &p1_struct);

   pthread_t id2;
   pthread_create(&id2, NULL, count_by_threads, &p2_struct);

   // Wait for threads to join
   pthread_join(id1,NULL);
   pthread_join(id2,NULL);

   printf("\n\n SUM = %d\n", sum);
        if (sum != -1 && sum != 0 && sum != 1 && sum != -2 && sum != 3 && sum != 4 && sum != -5)
                return 0;
   sum = 0;
}


}

