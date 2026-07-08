#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main() {
	long long int N = 100000000;
	long long int count = 0;

	#pragma omp parallel for reduction(+:count)
	for (long long int i = 0; i < N; i++) {
		unsigned int seed = time(NULL) ^ omp_get_thread_num() ^ i;

		double x = (double)rand_r(&seed) / RAND_MAX * 2 - 1;
		double y = (double)rand_r(&seed) / RAND_MAX * 2 - 1;

		if (x * x + y * y <= 1) {
			count++;
		}
	}

	double pi = 4.0 * count / N;

	printf("Pi = %f\n", pi);

	return 0;
}
