#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main()
{
	int rank, size;
	long long int N = 100000000; //Total number of darts
	long long local_N; //Number of darts per process
	long long int local_count = 0; //Number of darts in the circle per process
	long long int global_count = 0; //Total number of darts in the cirlce

	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	//Calculate number of darts per process
	local_N = N / size;

	//Generate random numbers
	srand(time(NULL) + rank);

	//Run montecarlo simulation
	for (long long int i = 0; i < local_N; i++)
	{
		double x = (double)rand() / RAND_MAX * 2 - 1;
		double y = (double)rand() / RAND_MAX * 2 - 1;

		if (x * x + y * y <= 1){
			local_count++;
		}}

	//Reduce the local count to global count
	MPI_Reduce(&local_count, &global_count, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

	//Compute and print the value of pi
	if (rank == 0)
	{
		double pi = 4.0 * global_count / N;
		printf("Pi = %f\n", pi);
	}

	MPI_Finalize();
	return 0;
}
