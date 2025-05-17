#include "t1.h"
#include <iostream>
#include <mpi.h>
#include <semaphore>

// Конструктор першого потоку
T1::T1(Data& data) : ThreadBase(data) {
    name = "T1";
}

// Створення вхідних даних
void T1::createInput() {
    // Генерація вектору C та матриці MD випадковими числами
    data.fillRandomVector(C);
    data.fillRandomMatrix(MD);
}

// Обмін даними з іншими потоками
void T1::sendAndReceiveInput() {
    // Відправка частин вектору C іншим потокам
    MPI_Send(C.data() + data.quarterN * 1, data.quarterN, MPI_INT, 1, 1, MPI_COMM_WORLD);  // C2 -> T2
    MPI_Send(C.data() + data.quarterN * 2, data.quarterN, MPI_INT, 2, 1, MPI_COMM_WORLD);  // C3 -> T3
    MPI_Send(C.data() + data.quarterN * 3, data.quarterN, MPI_INT, 3, 1, MPI_COMM_WORLD);  // C4 -> T4

    // Відправка матриці MD всім іншим потокам
    MPI_Send(MD.data(), MD.size(), MPI_INT, 1, 2, MPI_COMM_WORLD);  // MD -> T2
    MPI_Send(MD.data(), MD.size(), MPI_INT, 2, 2, MPI_COMM_WORLD);  // MD -> T3
    MPI_Send(MD.data(), MD.size(), MPI_INT, 3, 2, MPI_COMM_WORLD);  // MD -> T4

    // Алокація пам'яті для отримання даних
    MXn1.resize(data.quarterNxN);  // Частина MX від T2
    MZn1.resize(data.quarterNxN);  // Частина MZ від T2
    MR.resize(data.NxN);           // Матриця MR від T4

    // Отримання даних від інших потоків
    MPI_Recv(MXn1.data(), data.quarterNxN, MPI_INT, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);  // MX1 <- T2
    MPI_Recv(MZn1.data(), data.quarterNxN, MPI_INT, 1, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);  // MZ1 <- T2
    MPI_Recv(MR.data(), data.NxN, MPI_INT, 3, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);           // MR <- T4
}

// Обчислення локального t (мінімального значення в першій частині C)
int T1::computeLocalT() {
    return Data::minElement(C.begin(), C.begin() + data.quarterN);
}

// Обчислення локальної частини MA
void T1::calculateMAnLocal() {
    calculateAndStashMAnLocal(MXn1, MR, t, MZn1, MD);
}

