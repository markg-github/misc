
#include <iostream>
// #include <pthread.h>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <stop_token>

using namespace std;

#define NUM_THREADS 1

#define BUFFER_SIZE 20
#define LOOP_COUNT 150


// pthread_mutex_t the_mutex;
// pthread_cond_t the_cond;

// struct {
//     int _buf[BUFFER_SIZE];
//     int _empty_slots;
//     int _head;
//     int _tail;
// } the_buffer;

struct Buffer {
    queue<int> _buf;
    int _empty_slots;
    mutex _mutex;
    condition_variable _cond;
};

#if defined(DONT_USE_JTHREAD)

void* producer(void*)
{
    unsigned duration = LOOP_COUNT;
    for (unsigned i = 0; i < duration; i++) {
        pthread_mutex_lock(&the_mutex);
        while (the_buffer._empty_slots == 0) {
            pthread_cond_wait(&the_cond, &the_mutex);
        }
        the_buffer._buf[the_buffer._tail] = the_buffer._tail;
        the_buffer._tail = (the_buffer._tail + 1) % BUFFER_SIZE;
        the_buffer._empty_slots--;
        pthread_cond_signal(&the_cond);
        pthread_mutex_unlock(&the_mutex);

    }

    return NULL;

}

#endif


void producer_jthread(Buffer& buffer, std::stop_token stop_token) {
    for (int i = 0; i < LOOP_COUNT && !stop_token.stop_requested(); ++i) {
        {
            unique_lock<mutex> lock(buffer._mutex);
            buffer._cond.wait(lock, [&buffer, &stop_token] { return buffer._empty_slots > 0 || stop_token.stop_requested(); });
            if(stop_token.stop_requested()) return;
            buffer._buf.push(i);
            cout << "pushed " << i << endl;
            buffer._empty_slots--;
        }
        buffer._cond.notify_one();
    }
}

#if defined(DONT_USE_JTHREAD)

void* consumer(void*)
{
    unsigned duration = LOOP_COUNT;
    for (unsigned i = 0; i < duration; i++) {
        pthread_mutex_lock(&the_mutex);
        while (the_buffer._empty_slots == BUFFER_SIZE) {
            pthread_cond_wait(&the_cond, &the_mutex);
        }
        cout << "consumed " << the_buffer._buf[the_buffer._head] << std::endl << std::flush;
        the_buffer._head = (the_buffer._head + 1) % BUFFER_SIZE;
        the_buffer._empty_slots++;
        pthread_cond_signal(&the_cond);
        pthread_mutex_unlock(&the_mutex);
        
    }

    return NULL;
}

#endif


void consumer_jthread(Buffer& buffer, std::stop_token stop_token) {
    for (int i = 0; i < LOOP_COUNT && !stop_token.stop_requested(); ++i) {
        {
            unique_lock<mutex> lock(buffer._mutex);
            buffer._cond.wait(lock, [&buffer, &stop_token] { return !buffer._buf.empty() || stop_token.stop_requested(); });
            if(stop_token.stop_requested()) return;
            cout << "consumed " << buffer._buf.front() << endl << flush;
            buffer._buf.pop();
            buffer._empty_slots++;
        }
        buffer._cond.notify_one();
    }
}


#if defined(DONT_USE_JTHREAD)

int main2()
{
    pthread_t cthread_id[1];
    pthread_t pthread_id[1];

    the_buffer._empty_slots = BUFFER_SIZE;
    the_buffer._head = the_buffer._tail = 0;

    pthread_mutex_init(&the_mutex, NULL);
    pthread_cond_init(&the_cond, NULL);


    pthread_create(&cthread_id[0], NULL, consumer, NULL);
    pthread_create(&pthread_id[0], NULL, producer, NULL);

    pthread_join(cthread_id[0], NULL);
    pthread_join(pthread_id[0], NULL);

    pthread_mutex_destroy(&the_mutex);
    pthread_cond_destroy(&the_cond);

    return 0;


}

#endif


int main() {
    Buffer buffer;
    buffer._empty_slots = BUFFER_SIZE;

    std::jthread consumer_thread([&buffer](std::stop_token st) { consumer_jthread(buffer, st); });
    std::jthread producer_thread([&buffer](std::stop_token st) { producer_jthread(buffer, st); });

    // jthreads join automatically when they go out of scope.
    return 0;
}
