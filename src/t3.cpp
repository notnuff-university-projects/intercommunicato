#include "t3.h"

#include <iostream>
#include <semaphore>

T3::T3(Data& data) : ThreadBase(data, 2 * data.H, 3 * data.H - 1) {}

void T3::execute() {
    // В execute ми вже завершили чекати на інші потоки, тому можемо просто вивести A
    ThreadBase::execute();

}
