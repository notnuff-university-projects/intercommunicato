#ifndef THREAD_BASE_H
#define THREAD_BASE_H

#include "data.h"

// Базовий клас для всіх потоків обчислення
// Визначає загальну структуру та поведінку потоків
class ThreadBase {
protected:
    Data& data;  // Посилання на об'єкт даних

public:
    explicit ThreadBase(Data& data);
    virtual ~ThreadBase() = default;

public:
    // Основний метод виконання потоку
    virtual void run();

protected:
    // Етап введення даних
    void inputStage();
    virtual void createInput();           // Створення вхідних даних
    virtual void sendAndReceiveInput();   // Обмін даними між потоками
    virtual void syncInput();             // Синхронізація введення

protected:
    // Етап обчислення t (мінімального значення)
    void computeT();
    virtual int computeLocalT() = 0;      // Обчислення локального t
    void computeGlobalT(int localT);      // Обчислення глобального t
    void syncT();                         // Синхронізація t

protected:
    // Етап обчислення матриці MA
    virtual void computeMAn();

    virtual void calculateMAnLocal() = 0;  // Обчислення локальної частини MA
    // Допоміжний метод для обчислення частини MA
    void calculateAndStashMAnLocal(
        const TMatrix& MXnLocal,
        const TMatrix& MR,
        int t,
        const TMatrix& MZnLocal,
        const TMatrix& MD
        );

    void sendMAn(void *recBuffer);        // Відправка частини MA

protected:
    virtual void afterDone();             // Дії після завершення обчислень

protected:
    int t = std::numeric_limits<int>::max();  // Глобальне значення t
    std::string name;                         // Назва потоку

    TMatrix MAnLocal;                         // Локальна частина матриці MA
};

#endif // THREAD_BASE_H