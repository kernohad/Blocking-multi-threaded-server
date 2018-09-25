#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void* worker_code (void* arg);

const int INPUT_SIZE = 50;  // number of characters user can input

int main(){
    char input[INPUT_SIZE];

    pthread_t thread1;  // Might need to dynamically make these if we cannot reuse it. TODO 
    int status;

    // Loop through the following 2 steps until user enters in ^C signal, then gracefully shutdown: TODO
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

    // TODO: Remove this, just to test passing filename to thread
    sleep(2);

    return 0;
}

void* worker_code (void* arg){
    char input[INPUT_SIZE];
    strcpy(input, arg);
    // This function is for the worker thread code
    
    // Sleep for certain amount of time. 
    // 80% probability, sleep 1 sec. 
    // The simulates the worker thread found the desired file in the cache and serves it up quickly 
    // TODO

    // 20% probability sleep 7-10 deconds (randomly).
    // This simulates the worker has not found the requested file in cache and must block while it reads from the disk
    // TODO

    // TODO: Remove this, just to test passing filename to thread
    sleep(1);
    printf("Thread Filename: %s\n", input);


    return arg;
}
