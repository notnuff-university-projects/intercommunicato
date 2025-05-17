#ifndef T2_H
#define T2_H

#include "thread_base.h"

// Клас другого потоку (T2)
// Відповідає за:
// 1. Генерацію матриць MX та MZ
// 2. Розподіл частин MX та MZ між іншими потоками
// 3. Отримання частин C, MD та MR від інших потоків
// 4. Збір та вивід фінальної матриці MA
class T2 : public ThreadBase {
public:
    explicit T2(Data& data);
    ~T2() override;

protected:
    // Створення вхідних даних
    void createInput() override;
    // Обмін даними з іншими потоками
    void sendAndReceiveInput() override;

protected:
    // Обчислення локального t
    int computeLocalT() override;

protected:
    // Обчислення та вивід матриці MA
    virtual void computeMAn() override;
    // Обчислення локальної частини MA
    void calculateMAnLocal() override;

protected:
    // Дії після завершення обчислень
    virtual void afterDone() override;

protected:
    // Вхідні дані
    TMatrix MX, MZ;           // Матриці MX та MZ
    TMatrix MXn2, MZn2;       // Частини матриць MX та MZ для T2

    // Дані, отримані від інших потоків
    TVector Cn2;              // Частина C від T1
    TMatrix MD;               // Матриця MD від T1
    TMatrix MR;               // Матриця MR від T4

    // Вихідні дані
    TMatrix MA;               // Фінальна матриця MA

    // Змінні для вимірювання часу
    std::chrono::time_point<std::chrono::system_clock> startTime;
    std::chrono::time_point<std::chrono::system_clock> endTime;
};

#endif // T2_H