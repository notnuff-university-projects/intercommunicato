#ifndef T3_H
#define T3_H

#include "thread_base.h"

// Клас третього потоку (T3)
// Відповідає за:
// 1. Отримання частин C, MD, MX, MZ та MR від інших потоків
// 2. Обчислення локальної частини MA
class T3 : public ThreadBase {
public:
    explicit T3(Data& data);

protected:
    // Обмін даними з іншими потоками
    void sendAndReceiveInput() override;

protected:
    // Обчислення локального t
    int computeLocalT() override;

protected:
    // Обчислення локальної частини MA
    void calculateMAnLocal() override;

protected:
    // Дані, отримані від інших потоків
    TVector Cn3;              // Частина C від T1
    TMatrix MD;               // Матриця MD від T1
    TMatrix MXn3, MZn3;       // Частини матриць MX та MZ від T2
    TMatrix MR;               // Матриця MR від T4
};

#endif // T3_H