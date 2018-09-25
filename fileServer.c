#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void* worker (void* arg);

int main(){
    // Loop through the following 2 steps until user enters in ^C signal, then gracefully shutdown: TODO
    // Prompt user for filename string
    // TODO
    
    // Spawn child thread tell it filename string
    // TODO

}

void* worker (void* arg){
    // This function is for the worker thread code
    
    // Sleep for certain amount of time. 
    // 80% probability, sleep 1 sec. 
    // The simulates the worker thread found the desired file in the cache and serves it up quickly 
    // TODO

    // 20% probability sleep 7-10 deconds (randomly).
    // This simulates the worker has not found the requested file in cache and must block while it reads from the disk
    // TODO

}
