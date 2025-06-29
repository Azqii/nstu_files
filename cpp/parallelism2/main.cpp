#include <iostream>
#include <cmath>
#include <chrono>
#include <mpi.h>

bool is_perfect_power(long long num) {
    if (num <= 1) {
        return false;
    }
    for (int exp = 2; exp <= log2(num) + 1; ++exp) {
        long long base = round(pow(num, 1.0 / exp));
        if (pow(base, exp) == num) {
            return true;
        }
    }
    return false;
}

std::pair<long long, long long> sequential_search(long long N) {
    long long x = N + 1;
    while (true) {
        for (long long y = N + 1; y < x; ++y) {
            long long diff = x - y;
            long long sum = x + y;
            if (is_perfect_power(diff) && is_perfect_power(sum)) {
                return {x, y};
            }
        }
        ++x;
    }
}

std::pair<long long, long long> parallel_search(long long N, int rank, int size) {
    long long x = N + 1 + rank;
    while (true) {
        for (long long y = N + 1; y < x; ++y) {
            long long diff = x - y;
            long long sum = x + y;
            if (is_perfect_power(diff) && is_perfect_power(sum)) {
                return {x, y};
            }
        }
        x += size;
    }
}

void min_pair(void* in, void* inout, int* len, MPI_Datatype* dptr) {
    long long* left = (long long*)in;
    long long* right = (long long*)inout;
    if (left[0] < right[0] || (left[0] == right[0] && left[1] < right[1])) {
        right[0] = left[0];
        right[1] = left[1];
    }
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    long long N;
    std::pair<long long, long long> result_seq;

    if (rank == 0) {
        std::cout << "Enter N: ";
        std::cin >> N;

        auto start_seq = std::chrono::high_resolution_clock::now();
        result_seq = sequential_search(N);
        auto end_seq = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration_seq = end_seq - start_seq;
        std::cout << "Sequential result: x = " << result_seq.first << ", y = " << result_seq.second << std::endl;
        std::cout << "Time spent (sequential): " << duration_seq.count() << " sec" << std::endl;
    }

    MPI_Bcast(&N, 1, MPI_LONG_LONG_INT, 0, MPI_COMM_WORLD);

    auto start_par = std::chrono::high_resolution_clock::now();

    std::pair<long long, long long> local_result = parallel_search(N, rank, size);

    auto end_par = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_par = end_par - start_par;

    long long local[2] = {local_result.first, local_result.second};
    long long global[2];

    // Пользовательская операция для сравнения пар
    MPI_Op min_op;
    MPI_Op_create(min_pair, 1, &min_op);

    MPI_Reduce(local, global, 2, MPI_LONG_LONG_INT, min_op, 0, MPI_COMM_WORLD);

    MPI_Op_free(&min_op);

    double max_duration_par;
    MPI_Reduce(&duration_par, &max_duration_par, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);


    if (rank == 0) {
        std::cout << "Parallel result: x = " << global[0] << ", y = " << global[1] << std::endl;
        std::cout << "Time spent (parallel): " << max_duration_par << " sec" << std::endl;
    }

    MPI_Finalize();
    return 0;
}
