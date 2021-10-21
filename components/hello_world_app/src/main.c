/*
 * Copyright (C) 2019-2021, HENSOLDT Cyber GmbH
 */

#include <camkes.h>
#include <sel4/sel4.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/types.h>

#include <camkes/msgqueue.h>
#include <camkes/msgqueue_template.h>

#include "message.h"

typedef struct msg
{
    int handle;
    int status;
} msg_t;

volatile int counter = 0;

int
thread1(void)
{
    printf("Hello there thread 1\n");
    return 1;
}

int
thread2(void)
{
    printf("Hello there thread 2\n");
    return 2;
}

int
thread3(void)
{
    printf("Hello there thread 3\n");
    return 3;
}

int
thread4(void)
{
    printf("Hello there thread 4\n");
    return 4;
}

int
thread5(void)
{
    printf("Hello there thread 5\n");
    return 5;
}

int
thread6(void)
{
    printf("Hello there thread 6\n");
    return 6;
}

typedef int (*thread_func_ptr_t)(void);

// Parameters passed to the thread that will be started
volatile thread_func_ptr_t thread_to_run          = NULL;
volatile bool              thread_to_run_detached = false;

// Return value from the thread being joined
volatile int               thread_return_value    = 0;

// Used to execute the function passed as an argument on one thread from the
// thread pool in either joinable or detached fashion.
void
thread_start(thread_func_ptr_t func, bool detached)
{

    // Get a mutex to guarantee only one instance of this function is active at
    // a given time.
    if (thread_start_lock())
    {
        printf("Mutex error\n");
        return;
    }

    // Check on the semaphore if there is a free thread in the thread pool.
    // In place of busy waiting we can return an out of resources / try again
    // error and let the user deal with it.
    // If there is a free thread we reserve it here.
    while (threads_available_trywait())
    {
        printf("Waiting for a free thread in the pool\n");
        seL4_Yield();
    }

    // Prepare the arguments to be passed to the thread we start.
    thread_to_run          = func;
    thread_to_run_detached = detached;

    // Wake up a random thread from the pool.
    thread_start_e_emit();
    // Wait for confirmation it started executing.
    thread_started_c_wait();

    // Unlock the mutex, allowing the next start call to be executed.
    if (thread_start_unlock())
    {
        printf("Mutex error\n");
        return;
    }
}

// Wait for a joinable thread to finish and get its return code.
int
thread_join()
{
    // Wait for a thread to finish.
    if(threads_join_wait())
    {
        printf("Semaphore error\n");
        return -1;
    }
    // Get its return value.
    int return_value = thread_return_value;
    // Release the mutex signaling we read the return value.
    if (thread_join_unlock())
    {
        printf("Mutex error\n");
        return -1;
    }
    return return_value;
}

// This skeleton is running in each thread, implementing the framework needed
// for the various thread constructs.
int
thread_runner(int badge)
{
    while (1)
    {
        // Local variables to save the parameters passed by the create call.
        thread_func_ptr_t local_thread_to_run = NULL;
        bool              local_detached      = false;
        // Return value.
        int               return_value        = 0;

        // Post to semaphore, increasing the count of free threads in the pool
        // by one.
        if(threads_available_post())
        {
            printf("Semaphore error\n");
            return -1;
        }

        // Wait for a start request from thread_start.
        thread_start_c_wait();

        // Copy parameters passed from create to local variables, allowing
        // the global variables to be used in the next create call.
        local_thread_to_run    = thread_to_run;
        local_detached         = thread_to_run_detached;
        thread_to_run          = NULL;

        // signal to thread_create that the requested thread started.
        thread_started_e_emit();

        // Check if we got an actual function pointer to execute.
        if (local_thread_to_run)
        {
            // Execute the passed function.
            return_value = local_thread_to_run();
        }

        // Check if its a JOINABLE thread which has to return a value.
        if (!local_detached)
        {
            // Lock the return value variable, to prevent other threads from
            // overwriting it.
            if (thread_join_lock())
            {
                printf("Mutex error\n");
                return -1;
            }
            // Write the return value.
            thread_return_value = return_value;
            // Signal the thread_join there is a return value to be read.
            if(threads_join_post())
            {
                printf("Semaphore error\n");
                return -1;
            }
        }
    }

    return 0;
}

#define JOINABLE false
#define DETACHED true

int
run(void)
{
    thread_start(thread1, JOINABLE);
    thread_start(thread2, JOINABLE);
    thread_start(thread3, JOINABLE);
    thread_start(thread6, DETACHED);
    thread_start(thread6, DETACHED);
    thread_start(thread6, DETACHED);
    printf("Thread finished with result %d\n", thread_join());
    thread_start(thread4, JOINABLE);
    printf("Thread finished with result %d\n", thread_join());
    printf("Thread finished with result %d\n", thread_join());
    thread_start(thread5, JOINABLE);
    printf("Thread finished with result %d\n", thread_join());
    printf("Thread finished with result %d\n", thread_join());
    thread_start(thread6, JOINABLE);
    thread_start(thread3, JOINABLE);
    printf("Thread finished with result %d\n", thread_join());
    printf("Thread finished with result %d\n", thread_join());
    thread_start(thread4, JOINABLE);
    thread_start(thread5, JOINABLE);
    printf("Thread finished with result %d\n", thread_join());
    printf("Thread finished with result %d\n", thread_join());

    seL4_DebugDumpScheduler();

    camkes_msgqueue_receiver_t recv = {0};

    printf("recv init %d\n", camkes_msgqueue_receiver_init(1, &recv));

    camkes_msgqueue_wait(&recv);

    Msg a, b;

    printf("Status get %d\n", camkes_msgqueue_get(&recv, &a, sizeof(a)));

    printf("Status %d %d\n", a.handle, a.status);

    printf("Status get %d\n", camkes_msgqueue_get(&recv, &b, sizeof(b)));

    printf("Status %d %d\n", b.handle, b.status);

    printf("hello world!\n");

    return 0;
}
