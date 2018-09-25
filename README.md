# Blocking-multi-threaded-server
GVSU CIS-452 Lab 4

Recall the class discussion of a multi-threaded fileserver, in which a Dispatch thread receives a file access request from a client, dispatches a Worker thread to satisfy the request, and resumes accepting new requests from other clients.  The worker threads proceed to service their assigned request (potentially blocking while waiting for the disk).  This mini-programming assignment simulates the thread execution manifested by a multi-threaded fileserver process.

Develop a multi-threaded program with the following specifications:

The Dispatch thread should:
* input a string from the user (simulating the name of a file to access)
* spawn a child thread and communicate to it the filename requested/entered by the user
* _immediately_ repeat the input/spawn sequence (i.e. accept a new file request)

Each Worker thread should:
* obtain the simulated filename from the dispatcher
* sleep for a certain amount of time, simulating the time spent performing a file access:
  * with 80% probability, sleep for 1 second.  This simulates the scenario that the Worker thread has found the desired file in the disk cache and serves it up quickly.
  * with 20% probability, sleep for 7-10 seconds (randomly).  This simulates the scenario that the worker thread has not found the requested file in the disk cache and must block while it is read in from the hard drive.
* wake up, print a diagnostic message that includes the name of the file accessed, terminate

It's ok if the resulting display looks somewhat "messy"; that shows true concurrency is occurring.

Your program should continue to execute until terminated by the user (^C).  At that point, your program should print out basic statistics:
* total number of file requests received/serviced

When terminated, your program should cleanup as appropriate and shutdown gracefully.

In addition to being correct, your program should be efficient and should execute in parallel.

__Remember:__ threads share data by definition -- as a rule, all multi-threaded programs should be carefully scrutinized for potential race conditions or "data clobbering".

Note: the threads in this assignment mostly sleep (simulating blocking I/O).  However, you may at some point write a more computationally intense program and want to "watch" your threads executing.  The eos environment provides a graphical tool called _"mate-system-monitor"_.  Make sure the "Resources" tab is selected.  The top graph displays CPU activity on all CPU cores (recall that Linux sees Intel hyperthreading as two cores, so a quad-core system reports 8 CPUs).  If your threads are sufficiently busy and correctly concurrent, you should see them occupying and executing on multiple cores.
