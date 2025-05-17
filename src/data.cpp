#include "data.h"

#include <algorithm>
#include <climits>
#include <iomanip>
#include <iostream>
#include <semaphore>

// Конструктор: ініціалізує генератор випадкових чисел
Data::Data() {
    // Ініціалізація генератора випадкових чисел
    gen.seed(std::time(nullptr));
    dist = std::uniform_int_distribution<int>(5, 9); // Діапазон випадкових чисел: від 5 до 9
}

// Деструктор
Data::~Data() {}

// Заповнює вектор випадковими числами
void Data::fillRandomVector(TVector &vec) {
    vec.resize(N);  // Встановлення розміру вектора
    for (int i = 0; i < N; ++i) {
        vec[i] = GetRandomNumber();  // Заповнення випадковими числами
    }
}

// Заповнює матрицю випадковими числами
void Data::fillRandomMatrix(TMatrix &mat) {
    mat.resize(NxN);  // Встановлення розміру матриці (NxN)
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            // Індексування для одновимірного масиву
            mat[i * N + j] = GetRandomNumber();  // Заповнення випадковими числами
        }
    }
}

// Повертає мінімальний елемент у векторі (на заданому діапазоні)
int Data::minElement(const TVector::iterator begin, const TVector::iterator end) {
    const auto min = std::ranges::min_element(begin, end);
    return *min;
}

// Множить частину матриці (matPart) на повну матрицю (mat)
TMatrix Data::multiplyMatrixPartByMatrix(const TMatrix &matPart, const TMatrix &mat) {
    const auto matPartSize = matPart.size();
    if (matPartSize % N != 0) throw std::invalid_argument("Розмір частини матриці повинен бути кратним N");

    TMatrix result;
    result.resize(matPart.size());

    auto rowsNum = matPart.size() / N;
    for (int matPartRow = 0; matPartRow < rowsNum; ++matPartRow) {
        auto rowBegin = N * matPartRow;
        for (auto matColumn = 0; matColumn < N; ++matColumn) {
            int matResult = 0;
            for (auto i = 0; i < N; ++i) {
                // Обрахунок добутку рядка на стовпець
                const auto matPartIdx = rowBegin + i;
                const auto matIdx = matColumn + i * N;
                matResult += matPart[matPartIdx] * mat[matIdx];
            }
            result[rowBegin + matColumn] = matResult;
        }
    }

    return result;
}

// Віднімає одну частину матриці від іншої (елементно)
void Data::subtractMatrixPartByMatrixPart(TMatrix &target, const TMatrix &subtractor) {
    if (target.size() != subtractor.size()) 
        throw std::invalid_argument("Цільова матриця та від'ємник повинні мати однаковий розмір");
    
    for (int i = 0; i < target.size(); ++i) {
        target[i] -= subtractor[i];
    }
}

// Виводить матрицю у консоль (з обрізанням для великих розмірів)
void Data::printMatrix(const TMatrix &mat) {
    const int maxDisplay = 4;   // Кількість рядків/стовпців для відображення
    const int cellWidth = 6;    // Фіксована ширина комірки
    const int rows = mat.size() / N;

    // Форматує значення для виводу
    auto formatCell = [&](int value) -> std::string {
        std::ostringstream oss;
        oss << value;
        std::string str = oss.str();

        if ((int)str.size() > cellWidth) {
            return str.substr(0, cellWidth - 3) + "...";  // Обрізання довгих чисел
        } else {
            std::ostringstream padded;
            padded << std::setw(cellWidth) << str;  // Додавання відступів
            return padded.str();
        }
    };

    // Виводить один рядок матриці
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

    // Виведення матриці з обрізанням
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

// Повертає випадкове число у заданому діапазоні
int Data::GetRandomNumber() {
    return dist(gen);
}
