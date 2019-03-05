# CS4440 Introduction to Operating Systems    

## Project 2: Exercises in Concurrency and Synchronization

### Objectives: 
* Solve inter-process communication problems during concurrent execution of processes. 
* Use Posix Pthread library for concurrency. 

### Problem Statement:  
1. Bounded-buffer Producer/Consumer problem: Implement a solution to the boundedbuffer producer/consumer problem. Implement the solution using synchronization primitives (pthread_mutex_t for mutual exclusion and sem_t for minding the buffer size) provided by the POSIX threads. Your implementation will consist of a control program that (i) initializes the buffer and the synchronization variables and (ii) creates and terminates the threads for the producer and the consumer.  The producer generates printable characters and places them into the buffer and the consumer pulls the characters out of the buffer one at a time and prints them out.  Let the control program  simulate  all  possible  conditions:  buffer  empty  (consumer  waiting),  buffer  full  (producer waiting),  buffer  not  empty  (both  producer  and  consumer  working).    Assume  that  production  and consumption per character take the same amount of time.  
2. Mother Hubbard (children, mother, father) There are 12 children.  Each child needs to be woken up, fed breakfast, sent to school, given dinner, given a bath, read a book, and tucked in bed.  The mother applies each task in order, to each child in order, before being able to move on to the next task.  Then after all the children have all the tasks done to them, the mother can take a nap break.  After a child takes their bath, the father can read the child a book and tuck the child in bed.  When all children are in bed, then the father can go to sleep.  When the father goes to sleep, he wakes up the mother and the cycle repeats.  (Note that the Mother can give a child a bath while the father read anotherchild a book, but a child who has not had a bath yet, cannot get read a book.) The following occurrences must be printed out at the right times: 
    * When either the Mother or Father wakes up or goes to sleep. 
        * i.e. “Father is going to sleep and waking upMother to take care of the children.” 
    * When a child is fed breakfast, sent to school, given dinner, given a bath by the Mother 
        * i.e. “Child #3 is being fed breakfast.” 
    * When a child is read a book and tucked in bed by the Father 
        * i.e. “Child #11 is being read a book.” 
    * When the beginning/end of a cycle/day occurs and what # cycle/day it is. 
        * i.e. “This is day #3 of a day in the life of Mother Hubbard.” 
3. Airline Passengers There are P passengers, B baggage handlers, S security screeners, and F flight attendants.  Each passenger must give their baggage to a baggage handler, then go have their “security” screened by a security screener, and finally be seated by a flight attendant.  When all P passengers have this done, the plane takes off.  All P passengers arrive at the same time to the terminal and must wait on a line to be processed, but are processed in no particular order (yes, seems unfair but that’s the way it is at this airline, so stuff it! :P We know you had a choice, so thank you for choosing us!) The following occurrences must be printed out at the right times: 
    * When a passenger is waiting to be processed. 
        * i.e. “Passenger #61 arrived at the terminal.”
        * i.e. “Passenger #12 is waiting at baggage processing for a handler.” 
        * i.e. “Passenger #33 is waiting to be screened by a screener.”
        * i.e. “Passenger #23 is waiting to board the plane by an attendant.”
        * i.e. “Passenger #5 has been seated and relaxes.” 
