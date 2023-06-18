#include <iostream>
#include <cmath>
#include <iomanip>
#include <mpi.h>

using namespace std;

//Formula Bailey Borwien Plouffe
long double calculateBBP(int rank, int size, int numTerms) {
    long double sum = 0.0;
    int startTerm = rank * numTerms / size;
    int endTerm = (rank + 1) * numTerms / size;

    for (int k = startTerm; k < endTerm; ++k) {
        long double numerator = 1.0 / pow(16.0, k);
        long double denominator1 = (8.0 * k) + 1.0;
        long double denominator2 = (8.0 * k) + 4.0;
        long double denominator3 = (8.0 * k) + 5.0;
        long double denominator4 = (8.0 * k) + 6.0;
        sum += numerator * (4.0 / denominator1 - 2.0 / denominator2 - 1.0 / denominator3 - 1.0 / denominator4);
    }

    return sum;
}

int main(int argc, char** argv) {
    

    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int numTerms=0;
    
    if (rank == 0) {
        cout << "Introduzca el nro de Interacciones para mas Precision mayor a 10000 terminos" << endl;
        cin >> numTerms;
    }
    
    
    long double partialSum = calculateBBP(rank, size, numTerms);

    long double totalSum;
    MPI_Reduce(&partialSum, &totalSum, 1, MPI_LONG_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        long double pi = totalSum;
        cout << setprecision(20);
        cout << "El valor aproximado de pi es: " << pi << endl;
    }

    MPI_Finalize();

    return 0;
}
