#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

void* worker_code (void* arg);
void sigHandler(int sigNum);

const int INPUT_SIZE = 50;  // number of characters user can input
int fileCounter = 0;        // Used to keep track of the number of files accessed.

//extra credit stuff
pthread_mutex_t lock;
int totalFileTime = 0;        // keep track of total file access time

/*****************************************************
 * A Fileserver simulation. The initial thread prompts
 * the user for input, then spawns a worker thread
 * and sends the input (filename) to the worker to
 * so it can "find" it. 
 ****************************************************/
int main(){
    char input[INPUT_SIZE];
    
    pthread_t thread_id; 
    int status;

    //Mutex to time threads
    pthread_mutex_init(&lock, NULL);

    /* Override ^C signal */
    signal(SIGINT, sigHandler);

    while(1){
        
        /* Prompt user for filename string */
        printf("\n> ");
        fgets(input, INPUT_SIZE, stdin);

        
        /* Spawn child thread tell it filename string */
        if (( status = pthread_create (&thread_id, NULL, worker_code, &input)) != 0) {
                fprintf (stderr, "thread create error %d: %s\n", status, strerror(status));
                exit(1);
        }
    }

    //Destroy mutex once complete
    pthread_mutex_destroy(&lock);
    return 0;
}


/*****************************************************
 * Function passed to the child threads for them to run
 ****************************************************/
void* worker_code (void* arg){

    char input[INPUT_SIZE];
    strcpy(input, arg);                     // Copy the argument passed to the function to the input var
    srand(time(0));                         // Seed Rand with the time
    int sleepChance = rand() % 5 + 1;       // Random number between 1 and 5
    int percent = 0;
    int sleepTime = 0;


    fileCounter += 1;                       // Increment the number of files accessed.
 
     /* 80% probability, sleep 1 sec. 
     * The simulates the worker thread found the desired file in the cache and serves it up quickly */
    if( sleepChance < 5 ){
        percent = 80;
        sleepTime = 1;
        sleep(1);
    }

    /* 20% probability sleep 7-10 deconds (randomly).
     * This simulates the worker has not found the requested file in cache and must block while it reads from the disk */
    if( sleepChance == 5 ){
        sleepTime = (rand() % (10 - 7)) + 7;     // Generate random number between 7 and 10
        percent = 20;
        sleep(sleepTime);
    }
    
    pthread_mutex_lock(&lock);
    totalFileTime += sleepTime;
    pthread_mutex_unlock(&lock);

    printf("\r%d%% - Slept for %d second(s) - (Thread: %ld) File: %s\n> ",percent, sleepTime, pthread_self(), input);
    fflush(stdout);
    
    return arg;
}

/*****************************************************
 * Function used to override the ^C signal
 ****************************************************/
void sigHandler(int sigNum){
    float avgFileTime = (float) totalFileTime / (float) fileCounter;
    //printf("Average file access time: %f s\n", avgFileTime);
    printf("\r^C recieved.\nThe number of files accessed is %d.\nAverage file access time is %f s.\nShutting down now.\n", fileCounter, avgFileTime);
    exit(0);
}
