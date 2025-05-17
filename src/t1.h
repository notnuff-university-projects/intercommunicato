#ifndef T1_H
#define T1_H

#include "thread_base.h"

// Клас першого потоку (T1)
// Відповідає за:
// 1. Генерацію вектору C та матриці MD
// 2. Розподіл частин C між іншими потоками
// 3. Розподіл MD між іншими потоками
// 4. Отримання частин MX, MZ та MR від інших потоків
class T1 : public ThreadBase {
public:
    explicit T1(Data& data);

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
    TVector C;    // Вектор C
    TMatrix MD;   // Матриця MD

    // Дані, отримані від інших потоків
    TMatrix MXn1, MZn1;  // Частини матриць MX та MZ
    TMatrix MR;          // Матриця MR
};

#endif // T1_H 