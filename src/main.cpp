/**
* ПЗВПКС - Паралельні та розподілені обчислювальні системи
* Лабораторна робота ЛР5
* Бібліотека MPI
* Програмування взаємодії потоків через повідомлення
* 
* Завдання: Обчислення формули MA = MX * MR - min(C) * (MZ * MD)
* 
* Автор: Ярошенко Олександр Сергійович
* Група: ІМ-21
* Дата: 06.05.2025
*/

#include <iostream>
#include <chrono>
#include <mpi/mpi.h>

#include "data.h"
#include "t1.h"
#include "t2.h"
#include "t3.h"
#include "t4.h"

int main(int argc, char** argv) {
    // Ініціалізація MPI середовища
    MPI_Init(nullptr, nullptr);

    // Отримання загальної кількості процесів
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Отримання рангу поточного процесу
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Створення об'єкта для роботи з даними
    Data data;

    // Вказівник на поточний потік
    std::unique_ptr<ThreadBase> currentThread;

    // Перевірка кількості процесів
    if (world_size != 4) {
        std::cerr << "Помилка: необхідно 4 процеси!\n";
        return EXIT_FAILURE;
    }

    // Створення відповідного потоку залежно від рангу
    switch (world_rank) {
        case 0:
            currentThread = std::make_unique<T1>(data);  // Перший потік
            break;
        case 1:
            currentThread = std::make_unique<T2>(data);  // Другий потік
            break;
        case 2:
            currentThread = std::make_unique<T3>(data);  // Третій потік
            break;
        case 3:
            currentThread = std::make_unique<T4>(data);  // Четвертий потік
            break;
        default:
            std::cerr << "Помилка: некоректний ранг: " << world_rank << "\n";
            return EXIT_FAILURE;
    }

    // Спеціальна обробка для четвертого потоку
    if (world_rank == 3) {
        bool t = true;
        while (t) sleep(5);
    }

    // Запуск обчислень
    currentThread->run();

    // Завершення MPI
    MPI_Finalize();
    return 0;
}