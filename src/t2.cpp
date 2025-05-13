#include "t2.h"
#include <iostream>
#include <mpi.h>
#include <semaphore>

T2::T2(Data& data) : ThreadBase(data) {}

void T2::createInput() {
    std::cout << "T2: Введення MX, MZ" << std::endl;

    data.fillRandomMatrix(MX);
    data.fillRandomMatrix(MZ);
}

void T2::sendAndReceiveInput() {
    // алокуємо пам'ять для буферів
    Cn2.resize(data.quarterN); MD.resize(data.NxN);
    MR.resize(data.NxN);

    // отримуємо дані з інших потоків
    MPI_Recv(Cn2.data(), data.quarterNxN, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(MD.data(), data.NxN, MPI_INT, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    MPI_Send(MX.data() + data.quarterN * 0, data.quarterNxN, MPI_INT, 0, 1, MPI_COMM_WORLD);
    MPI_Send(MX.data() + data.quarterN * 2, data.quarterNxN, MPI_INT, 2, 1, MPI_COMM_WORLD);
    MPI_Send(MX.data() + data.quarterN * 3, data.quarterNxN, MPI_INT, 3, 1, MPI_COMM_WORLD);

    MPI_Send(MZ.data() + data.quarterN * 0, data.quarterNxN, MPI_INT, 0, 2, MPI_COMM_WORLD);
    MPI_Send(MZ.data() + data.quarterN * 2, data.quarterNxN, MPI_INT, 2, 2, MPI_COMM_WORLD);
    MPI_Send(MZ.data() + data.quarterN * 3, data.quarterNxN, MPI_INT, 3, 2, MPI_COMM_WORLD);

    MPI_Recv(MR.data(), data.N, MPI_INT, 3, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    std::cout << "T2: received MD: " << MD[0] << std::endl;
}

void T2::syncInput() {
    MPI_Barrier(MPI_COMM_WORLD);
}
