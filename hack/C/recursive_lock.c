
#if defined(NORMAL_MUTEX)

#include <pthread.h>
#include <stdio.h>

pthread_mutex_t my_mutex; // Normal mutex by default

void recursive_function() {
    pthread_mutex_lock(&my_mutex); // Potential problem here!

    // ... do something ...

    recursive_function(); // Recursive call

    pthread_mutex_unlock(&my_mutex);
}

int main() {
    pthread_mutex_init(&my_mutex, NULL);
    recursive_function(); // Likely deadlock or error
    pthread_mutex_destroy(&my_mutex);
    return 0;
}

#elif defined(RECURSIVE_MUTEX)

pthread_mutexattr_t attr;
pthread_mutexattr_init(&attr);
pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE); // Set to recursive
pthread_mutex_init(&my_mutex, &attr); // Initialize with the attribute
pthread_mutexattr_destroy(&attr); // Destroy the attribute when no longer needed.

#endif


