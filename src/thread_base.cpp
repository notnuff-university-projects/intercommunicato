#include "thread_base.h"

#include <mpi.h>

ThreadBase::ThreadBase(Data &data) : data(data) {}

void ThreadBase::run() {
    inputStage();
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
