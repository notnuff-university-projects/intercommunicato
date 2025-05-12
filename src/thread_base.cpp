#include "thread_base.h"

#include <mpi.h>

ThreadBase::ThreadBase(Data &data) : data(data) {}

void ThreadBase::run() {
    inputStage();
}

void ThreadBase::inputStage() {
    createInput();
    sendInput();
    receiveOthersInput();
    syncInput();
}

void ThreadBase::createInput() {}

void ThreadBase::sendInput() {}

void ThreadBase::receiveOthersInput() {}

void ThreadBase::syncInput() {
    MPI_Barrier(MPI_COMM_WORLD);
}
