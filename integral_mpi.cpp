#include <iostream>
#include <cstdlib>
#include <cmath>
#include <mpi.h>

double slowFunction(double x) {
    double result = 0.0;
    for (int i = 0; i < 1000; ++i) {
        result += sin(x + i * 0.001);
    }
    return result;
}

double integrate(double a, double b, int numDivisions, int rank, int size) {
    double h = (b - a) / numDivisions;
    double local_integral = 0.0;

    int local_start = rank * (numDivisions / size) + 1;
    int local_end = (rank + 1) * (numDivisions / size);

    if (rank == 0) {
        local_integral += 0.5 * slowFunction(a);
    }
    if (rank == size - 1) {
        local_integral += 0.5 * slowFunction(b);
    }

    if(rank == size -1 && numDivisions % size != 0){
        local_end = numDivisions;
    }

    for (int i = local_start; i < local_end; ++i) {
        local_integral += slowFunction(a + i * h);
    }

    local_integral *= h;
    return local_integral;
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if (argc != 2) {
        if (world_rank == 0) {
            std::cerr << "Usage: " << argv[0] << " <number_of_divisions>" << std::endl;
        }
        MPI_Finalize();
        return 1;
    }

    int numDivisions = std::atoi(argv[1]);

    if (numDivisions <= 0) {
        if (world_rank == 0) {
            std::cerr << "Number of divisions must be a positive integer." << std::endl;
        }
        MPI_Finalize();
        return 1;
    }

    double a = 0.0;
    double b = 1.0;

    double local_result = integrate(a, b, numDivisions, world_rank, world_size);

    double global_result;
    MPI_Reduce(&local_result, &global_result, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        std::cout << "Integral: " << global_result << std::endl;
    }

    MPI_Finalize();
    return 0;
}