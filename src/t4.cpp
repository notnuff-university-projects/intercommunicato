#include "t4.h"
#include <iostream>
#include <mpi.h>
#include <semaphore>

T4::T4(Data& data) : ThreadBase(data) {}

void T4::createInput() {
    data.fillRandomMatrix(MR);
}

void T4::sendAndReceiveInput() {
    // алокуємо пам'ять для буферів
    Cn4.resize(data.quarterN); MD.resize(data.NxN);
    MXn4.resize(data.quarterNxN), MZn4.resize(data.quarterNxN);

    // отримуємо дані з інших потоків
    MPI_Recv(Cn4.data(), data.quarterNxN, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(MD.data(), data.NxN, MPI_INT, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    MPI_Recv(MXn4.data(), data.quarterNxN, MPI_INT, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(MZn4.data(), data.quarterNxN, MPI_INT, 1, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    MPI_Send(MR.data(), data.NxN, MPI_INT, 0, 1, MPI_COMM_WORLD);
    MPI_Send(MR.data(), data.NxN, MPI_INT, 1, 1, MPI_COMM_WORLD);
    MPI_Send(MR.data(), data.NxN, MPI_INT, 2, 1, MPI_COMM_WORLD);


    std::cout << "T4: send MR: " << MR[0] << std::endl;
    std::cout << "T4: received MD: " << MD[0] << std::endl;
}

void T4::syncInput() {
    MPI_Barrier(MPI_COMM_WORLD);
}
