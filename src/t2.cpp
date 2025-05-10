#include "t2.h"
#include <iostream>
#include <semaphore>

T2::T2(Data& data) : ThreadBase(data, data.H, 2 * data.H - 1) {}

void T2::input() {
    std::cout << "T2: Введення MX, MZ" << std::endl;

    // Ініціалізація MX
    MX.resize(data.N, std::vector<int>(data.N));
    for (int i = 0; i < data.N; ++i) {
        for (int j = 0; j < data.N; ++j) {
            MX[i][j] = data.GetRandomNumber();
        }
    }

    // Ініціалізація MZ
    MZ.resize(data.N, std::vector<int>(data.N));
    for (int i = 0; i < data.N; ++i) {
        for (int j = 0; j < data.N; ++j) {
            MZ[i][j] = data.GetRandomNumber();
        }
    }
}
