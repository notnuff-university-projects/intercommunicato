#include "t1.h"
#include <iostream>
#include <mpi.h>
#include <semaphore>

T1::T1(Data& data) : ThreadBase(data) {
    name = "T1";
}

void T1::createInput() {
    data.fillRandomVector(C);
    data.fillRandomMatrix(MD);
}

void T1::sendAndReceiveInput() {
    // Відправляємо Сn2
    MPI_Send(C.data() + data.quarterN * 1, data.quarterN, MPI_INT, 1, 1, MPI_COMM_WORLD);

    // Відправляємо Сn3
    MPI_Send(C.data() + data.quarterN * 2, data.quarterN, MPI_INT, 2, 1, MPI_COMM_WORLD);

    // // Відправляємо Сn4
    MPI_Send(C.data() + data.quarterN * 3, data.quarterN, MPI_INT, 3, 1, MPI_COMM_WORLD);

    // Відправляємо MD (тут можна використати bcast)
    MPI_Send(MD.data(), MD.size(), MPI_INT, 1, 2, MPI_COMM_WORLD);
    MPI_Send(MD.data(), MD.size(), MPI_INT, 2, 2, MPI_COMM_WORLD);
    MPI_Send(MD.data(), MD.size(), MPI_INT, 3, 2, MPI_COMM_WORLD);


    // алокуємо пам'ять для буферів
    MXn1.resize(data.quarterNxN); MZn1.resize(data.quarterNxN);
    MR.resize(data.NxN);

    // отримуємо дані з інших потоків
    MPI_Recv(MXn1.data(), data.quarterNxN, MPI_INT, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(MZn1.data(), data.quarterNxN, MPI_INT, 1, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(MR.data(), data.NxN, MPI_INT, 3, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    std::cout << "T1: send MD: " << MD[0] << std::endl;
    std::cout << "T1: received MR: " << MR[0] << std::endl;

}

int T1::computeLocalT() {
    return Data::minElement(C.begin(), C.begin() + data.quarterN);
}

void T1::calculateMAnLocal() {
    calculateAndStashMAnLocal(MXn1, MR, t, MZn1, MD);
}

