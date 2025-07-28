#include <pthread.h>
#include <unistd.h>

#include <iostream>

using namespace std;

#define NUM_THREADS 2

#define BUFFER_SIZE 6
#define LOOP_COUNT 15

typedef struct
{
    int buf[BUFFER_SIZE];
    int w_index;
    int r_index;
    int filled_slots;

    void dec_filled_slots() {
        filled_slots--;
        if (filled_slots < 0) {
            cout << filled_slots << std::endl << std::flush;
        }
    }
    void inc_filled_slots() {
        filled_slots++;
        if (filled_slots > BUFFER_SIZE) {
            cout << filled_slots << std::endl << std::flush;
        }
    }
} CIR_BUF;

typedef void* (*THREAD_FUNCTION)(void*);

CIR_BUF CirBuf = {0};

pthread_mutex_t sync_mutex;

static void pthread_create_wrapper(pthread_t* a_thread, THREAD_FUNCTION tfn, const char* label)
{
    cout << label << std::endl << std::flush;
    pthread_create(a_thread, NULL, tfn, NULL);

}

#define __USE_SEMAPHORE__
// #define __USE_CONDVAR__

#if defined(__USE_CONDVAR__)

#include <condition_variable>

pthread_cond_t condition;

void *consumer(void* arg)
{
    unsigned cnt = 0;
    while (cnt++ < LOOP_COUNT)
    {
        pthread_mutex_lock(&sync_mutex);
        while (CirBuf.filled_slots == 0)
        {
            // / Buffer is empty, nothing to consume /
            // / Wait for Producer to produce itmes, whichever lock you have acquired release it,
            // * so that producer can acquire lock and do it work
            // * Release the lock conditionally so that producer can notify you once item is available
            // */
            /*Below instruction release the lock and thread goes to sleep until it get notification from producer */
            pthread_cond_wait(&condition, &sync_mutex);
            /*If you are hear, means you got notification from producer, and lock is automatically acquired back to you */
        }

        cout << "consumed " << CirBuf.buf[CirBuf.r_index] << std::endl
             << std::flush;
        CirBuf.r_index = (CirBuf.r_index + 1) % BUFFER_SIZE;
        // CirBuf.filled_slots--;
        CirBuf.dec_filled_slots();

        pthread_mutex_unlock(&sync_mutex); /* It does not matter, you can release lock after sending below wake up signal as well */
        pthread_cond_signal(&condition);
    }
    return NULL;
}

void *producer(void* arg)
{
    unsigned cnt = 0;
    while (cnt++ < LOOP_COUNT)
    {
        pthread_mutex_lock(&sync_mutex);
        while (CirBuf.filled_slots == BUFFER_SIZE)
        {
            // / Buffer is Full, nothing to produce /
            // / Wait for Consumer to consume itmes, whichever lock you have acquired release it,
            // * so that Consumer can acquire lock and do it work
            // * Release the lock conditionally so that Consumer can notify you once item is consumed
            // */
            /*Below instruction release the lock and thread goes to sleep until it get notification from consumer */
            pthread_cond_wait(&condition, &sync_mutex);
            /*If you are here, means you got notification from consumer, and lock is automatically acquired back to you */
        }
        CirBuf.buf[CirBuf.w_index] = CirBuf.w_index;
        cout << "produced " << CirBuf.buf[CirBuf.w_index] << std::endl
             << std::flush;
        CirBuf.w_index = (CirBuf.w_index + 1) % BUFFER_SIZE;
        // CirBuf.filled_slots++;
        CirBuf.inc_filled_slots();

        pthread_mutex_unlock(&sync_mutex); /* It does not matter, you can release lock after sending below wake up signal as well */
        pthread_cond_signal(&condition);
    }
    return NULL;
}

int condvar_main()
{
    cout << __FUNCTION__ << std::endl << std::flush;

    pthread_t thread_id[NUM_THREADS];
    // int thread_arg[NUM_THREADS];

    if (pthread_mutex_init(&sync_mutex, NULL))
    {
        cout << "Mutex not init" << endl;
    }
    if (pthread_cond_init(&condition, NULL))
    {
        cout << "Cond not init" << endl;
    }

    pthread_create_wrapper(&thread_id[0], producer, "creating producer thread");
    pthread_create_wrapper(&thread_id[1], consumer, "creating consumer thread");

    pthread_join(thread_id[0], NULL);
    pthread_join(thread_id[1], NULL);

    pthread_mutex_destroy(&sync_mutex);
    pthread_cond_destroy(&condition);
    return 0;
}

#elif defined(__USE_SEMAPHORE__)

// #include <iostream>

// // Using Semaphore

// #include <pthread.h>
// #include <unistd.h>
#include <semaphore.h>

// using namespace std;

// #define NUM_THREADS 2

// #define BUFFER_SIZE 10

// typedef struct
// {
//     int buf[BUFFER_SIZE];
//     int w_index;
//     int r_index;
//     int filled_slots;
// } CIR_BUF;

// CIR_BUF CirBuf = {0};

// pthread_mutex_t sync_mutex;
sem_t sem_empty_slots;
sem_t sem_filled_slots;

/*


When Producer Consumer problem is implemented using Mutex and condition variable,
we first acquire the sync_mutex and then wait conditionally (if Buffer is full/empty),
Conditional wait will unlock the sync_mutex so that consumer can acquire sync_mutex, which will eventually signal the waiting thread
so that waiting thread can run. When waiting thread starts running, it automatically acquire the lock on sync_mutex
So here we first acquire the sync_mutex and then wait
But same is not applicable when Produce consumer problem is solved using Semaphore
Here if we first acquire sync_mutex and then if slots are completely empty/filled, then thread will wait
inside sem_wait continuously, (In contrast to conditional wait using mutex), sem_wait does not release sync_mutex
In this case second thread can not run because sync_mutex is already locked by first thread.
To avoid this deadlock, we first wait within sem_wait and if count is non zero then lock the sync mutex,
to make sure second thread can not modify shared data at the same moment.
*/
void *consumer(void *arg)
{
    unsigned cnt = 0;
    while (cnt++ < LOOP_COUNT)
    {
        sem_wait(&sem_filled_slots);
        pthread_mutex_lock(&sync_mutex);

        cout << "consumed " << CirBuf.buf[CirBuf.r_index] << std::endl
             << std::flush;
        CirBuf.r_index = (CirBuf.r_index + 1) % BUFFER_SIZE;
        // CirBuf.filled_slots--;
        CirBuf.dec_filled_slots();

        pthread_mutex_unlock(&sync_mutex); /* It does not matter, you can release lock after sending below wake up signal as well */
        sem_post(&sem_empty_slots);
    }
    return NULL;
}

void *producer(void *arg)
{
    unsigned cnt = 0;
    while (cnt++ < LOOP_COUNT)
    {
        sem_wait(&sem_empty_slots);
        pthread_mutex_lock(&sync_mutex);

        CirBuf.buf[CirBuf.w_index] = CirBuf.w_index;
        cout << "produced " << CirBuf.buf[CirBuf.w_index] << std::endl
             << std::flush;
        CirBuf.w_index = (CirBuf.w_index + 1) % BUFFER_SIZE;
        // CirBuf.filled_slots++;
        CirBuf.inc_filled_slots();

        pthread_mutex_unlock(&sync_mutex);
        sem_post(&sem_filled_slots);
    }
    return NULL;
}

int sem_main()
{
    cout << __FUNCTION__ << std::endl << std::flush;

    pthread_t thread_id[NUM_THREADS];
    // int thread_arg[NUM_THREADS];

    if (pthread_mutex_init(&sync_mutex, NULL))
    {
        cout << "Mutex not init" << endl;
    }
    if (sem_init(&sem_empty_slots, 0, BUFFER_SIZE))
    {
        cout << "Init Sem empty slots failed" << endl;
    }

    if (sem_init(&sem_filled_slots, 0, 0))
    {
        cout << "Init Sem filled slots failed" << endl;
    }

    pthread_create_wrapper(&thread_id[0], producer, "creating producer thread");
    pthread_create_wrapper(&thread_id[1], consumer, "creating consumer thread");

    pthread_join(thread_id[0], NULL);
    pthread_join(thread_id[1], NULL);

    pthread_mutex_destroy(&sync_mutex);
    sem_destroy(&sem_empty_slots);
    sem_destroy(&sem_filled_slots);
    return 0;
}

#else

// #include <iostream>

// #include <pthread.h>
// #include <unistd.h>
// #include <semaphore.h>

// using namespace std;

// #define NUM_THREADS 2

// #define BUFFER_SIZE 10

// typedef struct
// {
//     int buf[BUFFER_SIZE];
//     int w_index;
//     int r_index;
//     int filled_slots;
// } CIR_BUF;

// CIR_BUF CirBuf = {0};

// pthread_mutex_t sync_mutex;
// sem_t sem_empty_slots;
// sem_t sem_filled_slots;

/*


When Producer Consumer problem is implemented using Mutex and condition variable,
we first acquire the sync_mutex and then wait conditionally (if Buffer is full/empty),
Conditional wait will unlock the sync_mutex so that consumer can acquire sync_mutex, which will eventually signal the waiting thread
so that waiting thread can run. When waiting thread starts running, it automatically acquire the lock on sync_mutex
So here we first acquire the sync_mutex and then wait
But same is not applicable when Produce consumer problem is solved using Semaphore
Here if we first acquire sync_mutex and then if slots are completely empty/filled, then thread will wait
inside sem_wait continuously, (In contrast to conditional wait using mutex), sem_wait does not release sync_mutex
In this case second thread can not run because sync_mutex is already locked by first thread.
To avoid this deadlock, we first wait within sem_wait and if count is non zero then lock the sync mutex,
to make sure second thread can not modify shared data at the same moment.
*/
void *consumer(void *arg)
{
    unsigned cnt = 0;
    while (cnt++ < LOOP_COUNT)
    {
        // sem_wait(&sem_filled_slots);
        pthread_mutex_lock(&sync_mutex);

        cout << "consumed " << CirBuf.buf[CirBuf.r_index] << std::endl
             << std::flush;
        CirBuf.r_index = (CirBuf.r_index + 1) % BUFFER_SIZE;
        // CirBuf.filled_slots--;
        CirBuf.dec_filled_slots();

        pthread_mutex_unlock(&sync_mutex); /* It does not matter, you can release lock after sending below wake up signal as well */
        // sem_post(&sem_empty_slots);
    }
    return NULL;
}

void *producer(void *arg)
{
    unsigned cnt = 0;
    while (cnt++ < LOOP_COUNT)
    {
        // sem_wait(&sem_empty_slots);
        pthread_mutex_lock(&sync_mutex);

        CirBuf.buf[CirBuf.w_index] = CirBuf.w_index;
        cout << "produced " << CirBuf.buf[CirBuf.w_index] << std::endl
             << std::flush;
        CirBuf.w_index = (CirBuf.w_index + 1) % BUFFER_SIZE;
        // CirBuf.filled_slots++;
        CirBuf.inc_filled_slots();

        pthread_mutex_unlock(&sync_mutex);
        // sem_post(&sem_filled_slots);
    }
    return NULL;
}

int simplistic_main()
{
    cout << __FUNCTION__ << std::endl << std::flush;

    pthread_t thread_id[NUM_THREADS];
    // int thread_arg[NUM_THREADS];

    if (pthread_mutex_init(&sync_mutex, NULL))
    {
        cout << "Mutex not init" << endl;
    }
    // if (sem_init(&sem_empty_slots, 0, BUFFER_SIZE))
    // {
    //     cout << "Init Sem empty slots failed" << endl;
    // }

    // if (sem_init(&sem_filled_slots, 0, 0))
    // {
    //     cout << "Init Sem filled slots failed" << endl;
    // }

    // return 0;


    pthread_create_wrapper(&thread_id[0], producer, "creating producer thread");
    pthread_create_wrapper(&thread_id[1], consumer, "creating consumer thread");

    pthread_join(thread_id[0], NULL);
    pthread_join(thread_id[1], NULL);

    pthread_mutex_destroy(&sync_mutex);
    // sem_destroy(&sem_empty_slots);
    // sem_destroy(&sem_filled_slots);
    return 0;
}


#endif

int main(int argc, char** argv)
{
    cout << argv[0] << std::endl << std::flush;

    #if defined(__USE_CONDVAR__)

    condvar_main();

    #elif defined(__USE_SEMAPHORE__)

    sem_main();

    #else

    simplistic_main();

    #endif

    return 0;
}


