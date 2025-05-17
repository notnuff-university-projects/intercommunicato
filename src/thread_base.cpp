#include "thread_base.h"

#include <mpi.h>

ThreadBase::ThreadBase(Data &data) : data(data) {}

void ThreadBase::run() {
    inputStage();
    computeT();
    computeMAn();

}

void ThreadBase::inputStage() {
    createInput();

    sendAndReceiveInput();
    syncInput();
}

void ThreadBase::createInput() {}

void ThreadBase::sendAndReceiveInput() {}

void ThreadBase::syncInput() {
    MPI_Barrier(MPI_COMM_WORLD);
}

void ThreadBase::computeT() {
    auto localT = computeLocalT();

    computeGlobalT(localT);
    syncT();

    std::cout << name << ":\n";
}

void ThreadBase::computeGlobalT(int localT) {
    MPI_Allreduce(&localT, &t, 1, MPI_INT, MPI_MIN, MPI_COMM_WORLD);
}

void ThreadBase::syncT() {
    MPI_Barrier(MPI_COMM_WORLD);
}

void ThreadBase::computeMAn() {
    calculateMAnLocal();
    sendMAn(nullptr);
}

void ThreadBase::calculateAndStashMAnLocal(
    const TMatrix &MXnLocal,
    const TMatrix &MR,
    int t,
    const TMatrix &MZnLocal,
    const TMatrix &MD)
{
    auto leftPart = data.multiplyMatrixPartByMatrix(MXnLocal, MR);
    auto rightPart = data.multiplyMatrixPartByMatrix(MZnLocal, MD);

    Data::multiplyByScalar(rightPart, t);
    Data::subtractMatrixPartByMatrixPart(leftPart, rightPart);
    MAnLocal = std::move(leftPart);
}

void ThreadBase::sendMAn(void *recBuffer) {
    MPI_Gather(MAnLocal.data(), data.quarterNxN, MPI_INT,
                recBuffer, data.quarterNxN, MPI_INT,
                1, MPI_COMM_WORLD);
}

void ThreadBase::afterDone() {}
