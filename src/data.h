#ifndef DATA_H
#define DATA_H

#include <pthread.h>
#include <vector>
#include <random>
#include <ctime>
#include <semaphore>

using TVector = std::vector<int>;
using TMatrix = std::vector<int>;

class Data {
public:
    Data();
    ~Data();

public:
    void fillRandomVector(TVector &vec);
    void fillRandomMatrix(TMatrix &mat);

public:
    // Допоміжні методи

    static TVector addVectors(const TVector& v1, const TVector& v2);
    static int minElement(TVector::iterator begin, TVector::iterator end);

    // оскільки
    TMatrix multiplyMatrixPartByMatrix(const TMatrix &matPart, const TMatrix &mat);
    static void subtractMatrixPartByMatrixPart(TMatrix &target, const TMatrix &subtractor);

    template<typename T>
    static void multiplyByScalar(T& container, int value) {
        for(auto it = container.begin(); it != container.end(); ++it) {
            *it *= value;
        }
    }

public:
    int GetRandomNumber();

public:
    const int N = 1000;  // Розмірність векторів та матриць
    const int P = 4;     // Кількість потоків
    const int quarterN = N / P;
    const int quarterNxN = N * N / P;
    const int NxN = N * N;

protected:
    // Генератор випадкових чисел
    std::mt19937 gen;
    std::uniform_int_distribution<int> dist;

};

#endif // DATA_H 