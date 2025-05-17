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
#include <mpi/mpi.h>

#include "data.h"
#include "t1.h"
#include "t2.h"
#include "t3.h"
#include "t4.h"

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(nullptr, nullptr);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    Data data;

    std::unique_ptr<ThreadBase> currentThread;

    if (world_size != 4) {
        std::cerr << "Wrong number of processes!\n";
        return EXIT_FAILURE;
    }

    switch (world_rank) {
        case 0:
            currentThread = std::make_unique<T1>(data);
            break;
        case 1:
            currentThread = std::make_unique<T2>(data);
            break;
        case 2:
            currentThread = std::make_unique<T3>(data);
            break;
        case 3:
            currentThread = std::make_unique<T4>(data);
            break;
        default:
            std::cerr << "Wrong rank: " << world_rank << "\n";
            return EXIT_FAILURE;

    }

    if (world_rank == 3) {
        bool t = true;
        while (t) sleep(5);
    }
    currentThread->run();

    MPI_Finalize();
    return 0;
}