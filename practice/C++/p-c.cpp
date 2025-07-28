
#include <iostream>
#include <pthread.h>

using namespace std;

#define NUM_THREADS 1

#define BUFFER_SIZE 20
#define LOOP_COUNT 150


pthread_mutex_t the_mutex;
pthread_cond_t the_cond;

struct {
    int _buf[BUFFER_SIZE];
    int _empty_slots;
    int _head;
    int _tail;
} the_buffer;

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

int main()
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