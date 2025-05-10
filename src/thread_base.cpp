#include "thread_base.h"

ThreadBase::ThreadBase(Data& data, int from, int to)
    : data(data), from(from), to(to) {

}