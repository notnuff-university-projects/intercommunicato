#include "t4.h"
#include <iostream>
#include <semaphore>

T4::T4(Data& data) : ThreadBase(data, 3 * data.H, data.N - 1) {}

void T4::input() {
    std::cout << "T4: Введення MR" << std::endl;

    // Ініціалізація MZ
    MR.resize(data.N, std::vector<int>(data.N));
    for (int i = 0; i < data.N; ++i) {
        for (int j = 0; j < data.N; ++j) {
            MR[i][j] = data.GetRandomNumber();
        }
    }
}
