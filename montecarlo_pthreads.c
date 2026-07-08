#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_THREADS 4 // Number of threads

long long int N = 100000000; // Total darts
long long int global_count = 0;

// Mutex to preotect shared variable
pthread_mutex_t lock;

void* montecarlo(void* arg) {
	long long int local_count = 0;
	long long int local_N = N / NUM_THREADS;

	// Unique seed per thread
	unsigned int seed = time(NULL) ^ (long)arg;

	for (long long int i = 0; i < local_N; i++) {
		double x = (double)rand_r(&seed) / RAND_MAX * 2 - 1;
		double y = (double)rand_r(&seed) / RAND_MAX * 2 - 1;

		if (x * x + y * y <= 1) {
			local_count++;
		}
	}
	
	// Add to global count with mutex
	pthread_mutex_lock(&lock);
	global_count += local_count;
	pthread_mutex_unlock(&lock);

	return NULL;
}

int main() {
	pthread_t threads[NUM_THREADS];

	pthread_mutex_init(&lock, NULL);

	// Create threads
	for (long t = 0; t < NUM_THREADS; t++) {
		pthread_create(&threads[t], NULL, montecarlo, (void*)t);
	}

	// Join threads
	for (int t = 0; t < NUM_THREADS; t++) {
		pthread_join(threads[t], NULL);
	}

	// Compute pi
	double pi = 4.0 * global_count / N;
	printf("Pi = %f\n", pi);

	pthread_mutex_destroy(&lock);
	return 0;
}
