#include "t2.h"
#include <iostream>
#include <mpi.h>
#include <semaphore>

T2::T2(Data& data) : ThreadBase(data) {
    startTime = std::chrono::high_resolution_clock::now();

    name = "T2";
}

T2::~T2() {

}

void T2::createInput() {
    data.fillRandomMatrix(MX);
    data.fillRandomMatrix(MZ);

    auto MXn2begin = MX.data() + data.quarterN * 1;
    MXn2 = TMatrix(MXn2begin, MXn2begin + data.quarterNxN);

    auto MZn2begin = MZ.data() + data.quarterN * 1;
    MZn2 = TMatrix(MZn2begin, MZn2begin + data.quarterNxN);
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

    MPI_Recv(MR.data(), data.NxN, MPI_INT, 3, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}

int T2::computeLocalT() {
    return Data::minElement(Cn2.begin(), Cn2.end());
}

void T2::computeMAn() {
    calculateMAnLocal();

    MA.resize(data.NxN + 1);
    sendMAn(MA.data());

    data.printMatrix(MA);
}

void T2::calculateMAnLocal() {
    calculateAndStashMAnLocal(MXn2, MR, t, MZn2, MD);
}

void T2::afterDone() {
    endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    std::cout << "Час виконання: " << duration.count() << " мс" << std::endl;
}
