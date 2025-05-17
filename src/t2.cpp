#include "t2.h"
#include <iostream>
#include <mpi.h>
#include <semaphore>

// Конструктор другого потоку
T2::T2(Data& data) : ThreadBase(data) {
    startTime = std::chrono::high_resolution_clock::now();
    name = "T2";
}

// Деструктор
T2::~T2() {}

// Створення вхідних даних
void T2::createInput() {
    // Генерація матриць MX та MZ випадковими числами
    data.fillRandomMatrix(MX);
    data.fillRandomMatrix(MZ);

    // Виділення частин матриць для T2
    auto MXn2begin = MX.data() + data.quarterN * 1;
    MXn2 = TMatrix(MXn2begin, MXn2begin + data.quarterNxN);

    auto MZn2begin = MZ.data() + data.quarterN * 1;
    MZn2 = TMatrix(MZn2begin, MZn2begin + data.quarterNxN);
}

// Обмін даними з іншими потоками
void T2::sendAndReceiveInput() {
    // Алокація пам'яті для отримання даних
    Cn2.resize(data.quarterN);  // Частина C від T1
    MD.resize(data.NxN);        // Матриця MD від T1
    MR.resize(data.NxN);        // Матриця MR від T4

    // Отримання даних від інших потоків
    MPI_Recv(Cn2.data(), data.quarterNxN, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);  // C2 <- T1
    MPI_Recv(MD.data(), data.NxN, MPI_INT, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);          // MD <- T1

    // Відправка частин MX іншим потокам
    MPI_Send(MX.data() + data.quarterN * 0, data.quarterNxN, MPI_INT, 0, 1, MPI_COMM_WORLD);  // MX1 -> T1
    MPI_Send(MX.data() + data.quarterN * 2, data.quarterNxN, MPI_INT, 2, 1, MPI_COMM_WORLD);  // MX3 -> T3
    MPI_Send(MX.data() + data.quarterN * 3, data.quarterNxN, MPI_INT, 3, 1, MPI_COMM_WORLD);  // MX4 -> T4

    // Відправка частин MZ іншим потокам
    MPI_Send(MZ.data() + data.quarterN * 0, data.quarterNxN, MPI_INT, 0, 2, MPI_COMM_WORLD);  // MZ1 -> T1
    MPI_Send(MZ.data() + data.quarterN * 2, data.quarterNxN, MPI_INT, 2, 2, MPI_COMM_WORLD);  // MZ3 -> T3
    MPI_Send(MZ.data() + data.quarterN * 3, data.quarterNxN, MPI_INT, 3, 2, MPI_COMM_WORLD);  // MZ4 -> T4

    // Отримання MR від T4
    MPI_Recv(MR.data(), data.NxN, MPI_INT, 3, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);          // MR <- T4
}

// Обчислення локального t (мінімального значення в другій частині C)
int T2::computeLocalT() {
    return Data::minElement(Cn2.begin(), Cn2.end());
}

// Обчислення та вивід матриці MA
void T2::computeMAn() {
    calculateMAnLocal();  // Обчислення локальної частини MA

    MA.resize(data.NxN + 1);  // Алокація пам'яті для фінальної матриці
    sendMAn(MA.data());       // Збір частин MA від усіх потоків

    data.printMatrix(MA);     // Вивід фінальної матриці
}

// Обчислення локальної частини MA
void T2::calculateMAnLocal() {
    calculateAndStashMAnLocal(MXn2, MR, t, MZn2, MD);
}

// Дії після завершення обчислень
void T2::afterDone() {
    endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    std::cout << "Час виконання: " << duration.count() << " мс" << std::endl;
}
