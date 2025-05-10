#ifndef THREAD_BASE_H
#define THREAD_BASE_H

#include "data.h"
#include "tthread.h"

class ThreadBase : public TThread {
protected:
    Data& data;
    int from;
    int to;

public:
    ThreadBase(Data& data, int from, int to);
    virtual ~ThreadBase() = default;

public:
    virtual void run_thread() override;

protected:
};

#endif // THREAD_BASE_H 