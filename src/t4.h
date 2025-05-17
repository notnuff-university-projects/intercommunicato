#ifndef T4_H
#define T4_H

#include "thread_base.h"

// Клас четвертого потоку (T4)
// Відповідає за:
// 1. Генерацію матриці MR
// 2. Розподіл MR між іншими потоками
// 3. Отримання частин C, MD, MX та MZ від інших потоків
// 4. Обчислення локальної частини MA
class T4 : public ThreadBase {
public:
    explicit T4(Data& data);

protected:
    // Створення вхідних даних
    void createInput() override;
    // Обмін даними з іншими потоками
    void sendAndReceiveInput() override;

protected:
    // Обчислення локального t
    int computeLocalT() override;

protected:
    // Обчислення локальної частини MA
    void calculateMAnLocal() override;

protected:
    // Вхідні дані
    TMatrix MR;               // Матриця MR

    // Дані, отримані від інших потоків
    TVector Cn4;              // Частина C від T1
    TMatrix MD;               // Матриця MD від T1
    TMatrix MXn4, MZn4;       // Частини матриць MX та MZ від T2
};

#endif // T4_H