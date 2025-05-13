#include "t1.h"
#include <iostream>
#include <mpi.h>
#include <semaphore>

T1::T1(Data& data) : ThreadBase(data) {}

void T1::createInput() {
    std::cout << "T1: Введення C, MD" << std::endl;

    data.fillRandomVector(C);
    data.fillRandomMatrix(MD);
}

void T1::sendAndReceiveInput() {
    // Відправляємо Сn2
    MPI_Send(C.data() + data.quarterN * 1, data.quarterN, MPI_INT, 1, 1, MPI_COMM_WORLD);

    std::cout << "T1: sent: " << C[data.quarterN * 1] << std::endl;

    // Відправляємо Сn3
    // MPI_Send(C.data() + data.quarterN * 2, data.quarterN, MPI_INT, 2, 1, MPI_COMM_WORLD);
    //
    // // Відправляємо Сn4
    // MPI_Send(C.data() + data.quarterN * 3, data.quarterN, MPI_INT, 3, 1, MPI_COMM_WORLD);

    // Відправляємо MD (тут можна використати bcast)
    MPI_Send(MD.data(), MD.size(), MPI_INT, 1, 2, MPI_COMM_WORLD);
    // MPI_Send(MD.data(), MD.size(), MPI_INT, 2, 2, MPI_COMM_WORLD);
    // MPI_Send(MD.data(), MD.size(), MPI_INT, 3, 2, MPI_COMM_WORLD);


    // алокуємо пам'ять для буферів
    MXn1.resize(data.quarterNxN); MZn1.resize(data.quarterNxN);
    MR.resize(data.NxN);

    // отримуємо дані з інших потоків
    MPI_Recv(MXn1.data(), data.quarterNxN, MPI_INT, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(MZn1.data(), data.quarterNxN, MPI_INT, 1, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    // MPI_Recv(MR.data(), data.N, MPI_INT, 3, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    std::cout << "T1: received: " << MXn1[0] << std::endl;
}

void T1::syncInput() {

    MPI_Barrier(MPI_COMM_WORLD);
}
