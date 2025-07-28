
#if defined(THREADSAFE_AND_REENTRANT)

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;

int increment_reentrant_threadsafe(int *counter) {
    pthread_mutex_lock(&my_mutex);  // Thread-safe: Protects access
    int temp = *counter;
    *counter = temp + 1;
    pthread_mutex_unlock(&my_mutex);
    return *counter; // Reentrant: No shared mutable state outside parameters
}

void *thread_function(void *arg) {
    int *counter = (int *)arg;
    for (int i = 0; i < 10000; i++) {
      increment_reentrant_threadsafe(counter);
    }
    return NULL;
}

int main() {
    int counter = 0;
    pthread_t threads[2];

    for (int i = 0; i < 2; i++) {
        pthread_create(&threads[i], NULL, thread_function, &counter);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Counter: %d\n", counter); // Should be 20000
    pthread_mutex_destroy(&my_mutex);
    return 0;
}

#elif defined(THREADSAFE_AND_NOTREENTRANT)

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;
static int my_static_variable = 0; // Shared and static

int increment_not_reentrant_threadsafe() {
    pthread_mutex_lock(&my_mutex);
    my_static_variable++; // Not reentrant: Modifies static variable
    int temp = my_static_variable;
    pthread_mutex_unlock(&my_mutex);
    return temp;
}

void *thread_function(void *arg) {
    for (int i = 0; i < 10000; i++) {
        increment_not_reentrant_threadsafe();
    }
    return NULL;
}

int main() {
    pthread_t threads[2];

    for (int i = 0; i < 2; i++) {
        pthread_create(&threads[i], NULL, thread_function, NULL);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Static Variable: %d\n", my_static_variable); // Should be 20000
    pthread_mutex_destroy(&my_mutex);
    return 0;
}

#elif defined(NOTTHREADSAFE_AND_REENTRANT)

#include <stdio.h>
#include <stdlib.h>

int global_counter = 0; // Shared mutable state

int increment_reentrant_not_threadsafe() {
    int temp = global_counter; // Not thread-safe
    global_counter = temp + 1;  // Not thread-safe
    return global_counter;    // Reentrant: No shared mutable state outside globals
}

void *thread_function(void *arg) {
    for (int i = 0; i < 10000; i++) {
        increment_reentrant_not_threadsafe();
    }
    return NULL;
}

int main() {
    pthread_t threads[2];

    for (int i = 0; i < 2; i++) {
        pthread_create(&threads[i], NULL, thread_function, NULL);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Global Counter: %d\n", global_counter); // Race condition
    return 0;
}

#elif defined(NOTTHREADSAFE_AND_NOTREENTRANT)

#include <stdio.h>
#include <stdlib.h>

static int my_static_variable = 0; // Shared and static

int increment_not_reentrant_not_threadsafe() {
  my_static_variable++; // Not reentrant
  return my_static_variable; // Not thread-safe
}

void *thread_function(void *arg) {
    for (int i = 0; i < 10000; i++) {
      increment_not_reentrant_not_threadsafe();
    }
    return NULL;
}

int main() {
    pthread_t threads[2];

    for (int i = 0; i < 2; i++) {
        pthread_create(&threads[i], NULL, thread_function, NULL);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Static Variable: %d\n", my_static_variable); // Race condition
    return 0;
}

#endif



