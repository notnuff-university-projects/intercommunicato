#include "data.h"

#include <algorithm>
#include <climits>
#include <iostream>
#include <semaphore>

Data::Data() {
    // Ініціалізація генератора випадкових чисел
    gen.seed(std::time(nullptr));
    dist = std::uniform_int_distribution<int>(5, 9);
}

Data::~Data() {}

void Data::fillRandomVector(TVector &vec) {
    vec.resize(N);
    for (int i = 0; i < N; ++i) {
        vec[i] = GetRandomNumber();
    }
}

void Data::fillRandomMatrix(TMatrix &mat) {
    mat.resize(NxN);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            mat[i + i * j] = GetRandomNumber();
        }
    }
}

int Data::minElement(const TVector::iterator begin, const TVector::iterator end) {
    const auto min = std::ranges::min_element(begin, end);
    std::cout << "MIN: " << *min << " " << *begin << " " << *end << std::endl;
    return *min;
}

TMatrix Data::multiplyMatrixPartByMatrix(const TMatrix &matPart, const TMatrix &mat) {
    const auto matPartSize = matPart.size();
    if (matPartSize % N != 0) throw std::invalid_argument("Matrix part size must be a multiple of N");


    TMatrix result;
    result.resize(matPart.size());

    auto rowsNum = matPart.size() / N;
    for (int matPartRow = 0; matPartRow < rowsNum; ++matPartRow) {
        auto rowBegin = N * matPartRow;
        for (auto matColumn = 0; matColumn < N; ++matColumn) {
            int matResult = 0;
            for (auto i = 0; i < N; ++i) {
                const auto matPartIdx = rowBegin + i;
                const auto matIdx = matColumn + i * N;
                matResult += matPart[matPartIdx] * mat[matIdx];
            }
            result[matColumn * N + matPartRow] = matResult;
        }
    }

    return result;
}

void Data::subtractMatrixPartByMatrixPart(TMatrix &target, const TMatrix &subtractor) {
    if (target.size() != subtractor.size()) throw std::invalid_argument("The target and subtractor must be the same size.");
    for (int i = 0; i < target.size(); ++i) {
        target[i] -= subtractor[i];
    }
}

int Data::GetRandomNumber() {
    return dist(gen);
}
