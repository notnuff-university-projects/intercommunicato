/**
* ПЗВПКС
* Лабораторна робота ЛР5
* Бібліотека MPI
* Програмування взаємодії потоків через повідомлення
* Моя функція: MA = MX * MR - min(C) * (MZ * MD)
* Ярошенко Олександр Сергійович
* Група ІМ-21
* Дата 06.05.2025
*/

#include <iostream>
#include <chrono>
#include "data.h"
#include "t1.h"
#include "t2.h"
#include "t3.h"
#include "t4.h"
#include "mpi/mpi.h"

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    // Print off a hello world message
    std::cout << "Hello world from processor " << processor_name
              << ", rank " << world_rank << " out of " << world_size << " processors\n";

    // Finalize the MPI environment
    MPI_Finalize();
    //
    // Data data;
    //
    // auto start = std::chrono::high_resolution_clock::now();
    //
    // T1 t1(data);
    // T2 t2(data);
    // T3 t3(data);
    // T4 t4(data);
    //
    // t1.start();
    // t2.start();
    // t3.start();
    // t4.start();
    //
    // t1.join();
    // t2.join();
    // t3.join();
    // t4.join();
    //
    // auto end = std::chrono::high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    //
    // std::cout << "Час виконання: " << duration.count() << " мс" << std::endl;
    //
    return 0;
}