#include "thread_base.h"

#include <mpi.h>

// Конструктор базового класу
ThreadBase::ThreadBase(Data &data) : data(data) {}

// Основний метод виконання потоку
void ThreadBase::run() {
    inputStage();     // Етап введення даних
    computeT();       // Етап обчислення t
    computeMAn();     // Етап обчислення MA
}

// Етап введення даних
void ThreadBase::inputStage() {
    createInput();            // Створення вхідних даних
    sendAndReceiveInput();    // Обмін даними між потоками
    syncInput();              // Синхронізація введення
}

// За замовчуванням - порожня реалізація
void ThreadBase::createInput() {}

// За замовчуванням - порожня реалізація
void ThreadBase::sendAndReceiveInput() {}

// Синхронізація введення через MPI бар'єр
void ThreadBase::syncInput() {
    MPI_Barrier(MPI_COMM_WORLD);
}

// Етап обчислення t (мінімального значення)
void ThreadBase::computeT() {
    auto localT = computeLocalT();    // Обчислення локального t
    computeGlobalT(localT);           // Обчислення глобального t
    syncT();                          // Синхронізація t

    std::cout << name << ":\n";
}

// Обчислення глобального t через MPI_Allreduce
void ThreadBase::computeGlobalT(int localT) {
    MPI_Allreduce(&localT, &t, 1, MPI_INT, MPI_MIN, MPI_COMM_WORLD);
}

// Синхронізація t через MPI бар'єр
void ThreadBase::syncT() {
    MPI_Barrier(MPI_COMM_WORLD);
}

// Етап обчислення матриці MA
void ThreadBase::computeMAn() {
    calculateMAnLocal();    // Обчислення локальної частини MA
    sendMAn(nullptr);       // Відправка частини MA
}

// Обчислення частини MA
void ThreadBase::calculateAndStashMAnLocal(
    const TMatrix &MXnLocal,
    const TMatrix &MR,
    int t,
    const TMatrix &MZnLocal,
    const TMatrix &MD)
{
    // Обчислення лівої частини: MX * MR
    auto leftPart = data.multiplyMatrixPartByMatrix(MXnLocal, MR);
    
    // Обчислення правої частини: MZ * MD
    auto rightPart = data.multiplyMatrixPartByMatrix(MZnLocal, MD);

    // Множення правої частини на t
    Data::multiplyByScalar(rightPart, t);
    
    // Віднімання правої частини від лівої
    Data::subtractMatrixPartByMatrixPart(leftPart, rightPart);
    
    // Збереження результату
    MAnLocal = std::move(leftPart);
}

// Відправка частини MA через MPI_Gather
void ThreadBase::sendMAn(void *recBuffer) {
    MPI_Gather(MAnLocal.data(), data.quarterNxN, MPI_INT,
                recBuffer, data.quarterNxN, MPI_INT,
                1, MPI_COMM_WORLD);
}

// За замовчуванням - порожня реалізація
void ThreadBase::afterDone() {}
