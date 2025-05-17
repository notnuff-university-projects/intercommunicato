#include "t3.h"
#include <iostream>
#include <mpi.h>
#include <semaphore>

// Конструктор третього потоку
T3::T3(Data& data) : ThreadBase(data) {
    name = "T3";
}

// Обмін даними з іншими потоками
void T3::sendAndReceiveInput() {
    // Алокація пам'яті для отримання даних
    Cn3.resize(data.quarterN);        // Частина C від T1
    MD.resize(data.NxN);              // Матриця MD від T1
    MXn3.resize(data.quarterNxN);     // Частина MX від T2
    MZn3.resize(data.quarterNxN);     // Частина MZ від T2
    MR.resize(data.NxN);              // Матриця MR від T4

    // Отримання даних від інших потоків
    MPI_Recv(Cn3.data(), data.quarterNxN, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);  // C3 <- T1
    MPI_Recv(MD.data(), data.NxN, MPI_INT, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);          // MD <- T1

    MPI_Recv(MXn3.data(), data.quarterNxN, MPI_INT, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);  // MX3 <- T2
    MPI_Recv(MZn3.data(), data.quarterNxN, MPI_INT, 1, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);  // MZ3 <- T2
    MPI_Recv(MR.data(), data.NxN, MPI_INT, 3, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);           // MR <- T4
}

// Обчислення локального t (мінімального значення в третій частині C)
int T3::computeLocalT() {
    return Data::minElement(Cn3.begin(), Cn3.end());
}

// Обчислення локальної частини MA
void T3::calculateMAnLocal() {
    calculateAndStashMAnLocal(MXn3, MR, t, MZn3, MD);
}