#include <iostream>
#include <cstdlib>
#include <cmath>
#include <omp.h> 

double slowFunction(double x) {
    double result = 0.0;
    for (int i = 0; i < 1000; ++i) {
        result += sin(x + i * 0.001);
    }
    return result;
}

double integrate(double a, double b, int numDivisions) {
    double h = (b - a) / numDivisions;
    double integral = 0.0;

    integral += 0.5 * (slowFunction(a) + slowFunction(b));

    #pragma omp parallel for reduction(+:integral) num_threads(8)
    for (int i = 1; i < numDivisions; ++i) {
        integral += slowFunction(a + i * h);
    }

    integral *= h;

    return integral;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <number_of_divisions>" << std::endl;
        return 1;
    }

    int numDivisions = std::atoi(argv[1]);

    if (numDivisions <= 0) {
        std::cerr << "Number of divisions and threads must be positive integers." << std::endl;
        return 1;
    }

    double a = 0.0;
    double b = 1.0;

    double result = integrate(a, b, numDivisions);
    std::cout << "Integral: " << result << std::endl;

    return 0;
}