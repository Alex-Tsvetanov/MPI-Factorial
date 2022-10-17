// MPI-Factorial.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <mpi.h>
#include "../lib/BigUInt.hpp"
#include "../utils/MpiCreateBigUInt.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

typedef BigUInt::BigUInt product_t;
typedef unsigned long long factor_t;

// Creates intervals of factorial multipliers
factor_t* create_intervals(factor_t N, int processes) {
    factor_t* intervals = new factor_t [processes];
    assert(intervals != nullptr);
    int i;
    const factor_t elements_per_process = N / processes;
    for (i = 0 ; i < processes ; i ++) {
        intervals[i] = i * elements_per_process + 1;
    }
    return intervals;
}

// Computes the multiplication of numbers in the interval
product_t compute_product(factor_t interval, int processes, factor_t N) {
    factor_t start (interval);
    factor_t end (interval + N / processes - 1);
    if (N - end < processes) end = N;
    product_t product (1);
    factor_t i;
    for (i = start; i <= end; i += 1) {
        product *= i;
    }
    return product;
}

// Computs the multiplication of numbers in array
product_t compute_custom_product(product_t* numbers, int number_of_elements) {
    product_t product (1);
    int i;
    for (i = 0; i < number_of_elements; i++) {
        product *= numbers[i];
    }
    return product;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: mpi_factorial N\n");
        return 1;
    }

    const factor_t n = atoi(argv[1]);

    MPI_Init(nullptr, nullptr);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Create datatype for BigUInt
    MPI_Datatype MPI_BigUInt;
    createType_BigUInt(MPI_BigUInt);

    // Create intrvals of mfactorial multipliers that are to be spread through the processes
    factor_t* intervals_to_prcess = nullptr;
    if (world_rank == 0) {
        intervals_to_prcess = create_intervals(n, world_size);
    }

    // For each process, create a buffer that will hold a subset of the entire
    // array
    factor_t sub_interval;

    // Scatter the random numbers from the root process to all processes in
    // the MPI world
    MPI_Scatter(intervals_to_prcess, 1, MPI_UNSIGNED_LONG_LONG, &sub_interval, 1, MPI_UNSIGNED_LONG_LONG, 0, MPI_COMM_WORLD);

    // Compute the product of your interval
    product_t sub_product = compute_product(sub_interval, world_size, n);

    // Gather all partial products down to the root process
    product_t* sub_products = nullptr;
    if (world_rank == 0) {
        sub_products = new product_t[world_size];
        assert(sub_products != nullptr);
    }
    MPI_Gather(&sub_product, 1, MPI_BigUInt, sub_products, 1, MPI_BigUInt, 0, MPI_COMM_WORLD);

    // Now that we have all of the partial products on the root, compute the
    // total product of all numbers.
    if (world_rank == 0) {
        product_t factorial = compute_custom_product(sub_products, world_size);
        printf("%s\n", factorial.to_string().c_str());
    }

    // Clean up
    if (world_rank == 0) {
        delete[] intervals_to_prcess;
        delete[] sub_products;
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
}