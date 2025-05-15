#include "thread_base.h"

#include <mpi.h>

ThreadBase::ThreadBase(Data &data) : data(data) {}

void ThreadBase::run() {
    inputStage();
    computeT();
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

    std::cout << name << ":\n"
    << "localT: " << localT << std::endl
    << "globalT: " << t << std::endl;
}

void ThreadBase::computeGlobalT(int localT) {
    MPI_Allreduce(&localT, &t, 1, MPI_INT, MPI_MIN, MPI_COMM_WORLD);
}

void ThreadBase::syncT() {
    MPI_Barrier(MPI_COMM_WORLD);
}

void ThreadBase::computeMAn() {
    calculateMAnLocal();
    sendMAn();
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

void ThreadBase::sendMAn() {

}
