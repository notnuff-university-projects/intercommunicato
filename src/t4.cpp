#include "t4.h"
#include <iostream>
#include <mpi.h>
#include <semaphore>

// Конструктор четвертого потоку
T4::T4(Data& data) : ThreadBase(data) {
    name = "T4";
}

// Створення вхідних даних
void T4::createInput() {
    // Генерація матриці MR випадковими числами
    data.fillRandomMatrix(MR);
}

// Обмін даними з іншими потоками
void T4::sendAndReceiveInput() {
    // Алокація пам'яті для отримання даних
    Cn4.resize(data.quarterN);        // Частина C від T1
    MD.resize(data.NxN);              // Матриця MD від T1
    MXn4.resize(data.quarterNxN);     // Частина MX від T2
    MZn4.resize(data.quarterNxN);     // Частина MZ від T2

    // Отримання даних від інших потоків
    MPI_Recv(Cn4.data(), data.quarterNxN, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);  // C4 <- T1
    MPI_Recv(MD.data(), data.NxN, MPI_INT, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);          // MD <- T1

    MPI_Recv(MXn4.data(), data.quarterNxN, MPI_INT, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);  // MX4 <- T2
    MPI_Recv(MZn4.data(), data.quarterNxN, MPI_INT, 1, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);  // MZ4 <- T2

    // Відправка MR всім іншим потокам
    MPI_Send(MR.data(), data.NxN, MPI_INT, 0, 1, MPI_COMM_WORLD);  // MR -> T1
    MPI_Send(MR.data(), data.NxN, MPI_INT, 1, 1, MPI_COMM_WORLD);  // MR -> T2
    MPI_Send(MR.data(), data.NxN, MPI_INT, 2, 1, MPI_COMM_WORLD);  // MR -> T3
}

// Обчислення локального t (мінімального значення в четвертій частині C)
int T4::computeLocalT() {
    return Data::minElement(Cn4.begin(), Cn4.end());
}

// Обчислення локальної частини MA
void T4::calculateMAnLocal() {
    calculateAndStashMAnLocal(MXn4, MR, t, MZn4, MD);
}