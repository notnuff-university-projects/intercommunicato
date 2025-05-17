#include "t3.h"
#include <iostream>
#include <mpi.h>
#include <semaphore>

T3::T3(Data& data) : ThreadBase(data) {
    name = "T3";
}

void T3::sendAndReceiveInput() {
    // алокуємо пам'ять для буферів
    Cn3.resize(data.quarterN); MD.resize(data.NxN);
    MXn3.resize(data.quarterNxN); MZn3.resize(data.quarterNxN);
    MR.resize(data.NxN);

    // отримуємо дані з інших потоків
    MPI_Recv(Cn3.data(), data.quarterNxN, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(MD.data(), data.NxN, MPI_INT, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    MPI_Recv(MXn3.data(), data.quarterNxN, MPI_INT, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(MZn3.data(), data.quarterNxN, MPI_INT, 1, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(MR.data(), data.NxN, MPI_INT, 3, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}

int T3::computeLocalT() {
    return Data::minElement(Cn3.begin(), Cn3.end());
}

void T3::calculateMAnLocal() {
    calculateAndStashMAnLocal(MXn3, MR, t, MZn3, MD);
}