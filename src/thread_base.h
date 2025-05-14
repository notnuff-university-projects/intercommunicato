#ifndef THREAD_BASE_H
#define THREAD_BASE_H

#include "data.h"

class ThreadBase {
protected:
    Data& data;

public:
    explicit ThreadBase(Data& data);
    virtual ~ThreadBase() = default;

public:
    virtual void run();

protected:
    void inputStage();
    virtual void createInput();
    virtual void sendAndReceiveInput();
    virtual void syncInput();

protected:
    void computeT();
    virtual int computeLocalT() = 0;
    void computeGlobalT(int localT);
    void syncT();

protected:
    int t = std::numeric_limits<int>::max();
    std::string name;
};

#endif // THREAD_BASE_H