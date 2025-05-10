#include "t1.h"
#include <iostream>
#include <semaphore>

T1::T1(Data& data) : ThreadBase(data, 0, data.H - 1) {}

void T1::input() {
    std::cout << "T1: Введення C, MD" << std::endl;

    // Ініціалізація C
    C.resize(data.N);
    for (int i = 0; i < data.N; ++i) {
        C[i] = data.GetRandomNumber();
    }
    
    // Ініціалізація MC
    MD.resize(data.N, std::vector<int>(data.N));
    for (int i = 0; i < data.N; ++i) {
        for (int j = 0; j < data.N; ++j) {
            MD[i][j] = data.GetRandomNumber();
        }
    }
}