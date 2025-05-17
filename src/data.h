// data.h
// Клас Data: містить методи для генерації, обробки та виводу векторів і матриць
// Використовується для роботи з даними в паралельних обчисленнях

#ifndef DATA_H
#define DATA_H

#include <pthread.h>
#include <vector>
#include <random>
#include <ctime>
#include <semaphore>

// Типи даних для роботи з векторами та матрицями
// TVector - вектор цілих чисел
// TMatrix - матриця, представлена як одновимірний масив розміром NxN
using TVector = std::vector<int>;
using TMatrix = std::vector<int>;

// Клас для роботи з даними (векторами та матрицями)
class Data {
public:
    Data(); // Конструктор: ініціалізує генератор випадкових чисел
    ~Data();

public:
    // Методи для генерації випадкових даних
    void fillRandomVector(TVector &vec);    // Заповнює вектор випадковими числами
    void fillRandomMatrix(TMatrix &mat);    // Заповнює матрицю випадковими числами

public:
    // Допоміжні методи для обробки даних
    // Знаходить мінімальний елемент у вказаному діапазоні вектора
    static int minElement(TVector::iterator begin, TVector::iterator end);

    // Операції з матрицями
    TMatrix multiplyMatrixPartByMatrix(const TMatrix &matPart, const TMatrix &mat);  // Множить частину матриці на іншу матрицю
    static void subtractMatrixPartByMatrixPart(TMatrix &target, const TMatrix &subtractor);  // Віднімає одну частину матриці від іншої

    // Шаблонний метод для множення контейнера на скаляр
    template<typename T>
    static void multiplyByScalar(T& container, int value) {
        for(auto it = container.begin(); it != container.end(); ++it) {
            *it *= value;
        }
    }

public:
    // Метод для виводу матриці у консоль (з обрізанням для великих розмірів)
    void printMatrix(const TMatrix &mat);

public:
    // Метод для отримання випадкового числа у заданому діапазоні
    int GetRandomNumber();

public:
    // Константи для розмірності даних
    const int N = 1000;          // Розмірність векторів та матриць
    const int P = 4;             // Кількість потоків/процесів
    const int quarterN = N / P;  // Чверть розміру N (для розподілу даних між потоками)
    const int quarterNxN = N * N / P;  // Чверть розміру матриці (N*N/P)
    const int NxN = N * N;       // Повний розмір матриці

protected:
    // Генератор випадкових чисел
    std::mt19937 gen;
    std::uniform_int_distribution<int> dist;
};

#endif // DATA_H 