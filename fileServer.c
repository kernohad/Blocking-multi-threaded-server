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

int main(){
    char input[INPUT_SIZE];

    pthread_t thread1;  // Might need to dynamically make these if we cannot reuse it. TODO 
    int status;

    // Override ^C signal
    signal(SIGINT, sigHandler);

    // Loop through the following 2 steps until user enters in ^C signal, then gracefully shutdown: TODO
    while(1){
        // Prompt user for filename string
        printf("\n> ");
        fgets(input, INPUT_SIZE, stdin);
       
        // TODO: Remove this, just testing input
        printf("Filename: %s\n", input);

        
        // Spawn child thread tell it filename string
        if (( status = pthread_create (&thread1, NULL, worker_code, &input)) != 0) {
                fprintf (stderr, "thread create error %d: %s\n", status, strerror(status));
                exit(1);
        }
    }

    // TODO: Remove this, just to test passing filename to thread
    sleep(11);

    return 0;
}

void* worker_code (void* arg){
    // TODO: clean up print statements in sleep ifs

    char input[INPUT_SIZE];
    strcpy(input, arg);
    
    srand(time(0));
    int sleepChance = rand() % 5 + 1;       // Random number between 1 and 5
    
    fileCounter += 1;   // Increment the number of files accessed.

    // 80% probability, sleep 1 sec. 
    // The simulates the worker thread found the desired file in the cache and serves it up quickly 
    if( sleepChance < 5 ){
        printf("Sleep Num: %d\n", sleepChance);
        printf("Sleep for 1 second.\n");
        sleep(1);
    }

    // 20% probability sleep 7-10 deconds (randomly).
    // This simulates the worker has not found the requested file in cache and must block while it reads from the disk
    if( sleepChance == 5 ){
        printf("Sleep Num: %d\n", sleepChance);
        int sleepTime = (rand() % (10 - 7)) + 7;     // Generate random number between 7 and 10
        printf("Sleep for %d second.\n", sleepTime);
        sleep(sleepTime);
    }

    // TODO: Remove this, just to test passing filename to thread
    printf("Thread Filename: %s\n", input);


    return arg;
}

void sigHandler(int sigNum){
    printf(" recieved.\nThe number of files accessed is %d.\nShutting down now.\n", fileCounter);
    exit(0);
}
