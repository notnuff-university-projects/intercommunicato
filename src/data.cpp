#include "data.h"

#include <algorithm>
#include <climits>
#include <iomanip>
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
            result[rowBegin + matColumn] = matResult;
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

void Data::printMatrix(const TMatrix &mat) {
    const int maxDisplay = 4;   // Number of rows/cols to show before/after '...'
    const int cellWidth = 6;    // Fixed width per cell (including alignment)
    const int rows = mat.size() / N;

    auto formatCell = [&](int value) -> std::string {
        std::ostringstream oss;
        oss << value;
        std::string str = oss.str();

        if ((int)str.size() > cellWidth) {
            return str.substr(0, cellWidth - 3) + "...";
        } else {
            std::ostringstream padded;
            padded << std::setw(cellWidth) << str;
            return padded.str();
        }
    };

    auto printRow = [&](int rowIndex) {
        for (int j = 0; j < N; ++j) {
            if (j < maxDisplay || j >= N - maxDisplay) {
                std::cout << formatCell(mat[rowIndex * N + j]) << " ";
            } else if (j == maxDisplay) {
                std::cout << std::setw(cellWidth) << "..." << " ";
            }
        }
        std::cout << "\n";
    };

    for (int i = 0; i < rows; ++i) {
        if (i < maxDisplay || i >= rows - maxDisplay) {
            printRow(i);
        } else if (i == maxDisplay) {
            for (int j = 0; j < N; ++j) {
                if (j < maxDisplay || j >= N - maxDisplay) {
                    std::cout << std::setw(cellWidth) << "..." << " ";
                } else if (j == maxDisplay) {
                    std::cout << std::setw(cellWidth) << "..." << " ";
                }
            }
            std::cout << "\n";
        }
    }
}

int Data::GetRandomNumber() {
    return dist(gen);
}
