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

protected:
    virtual void createInput();

protected:
    virtual void sendInput();
    virtual void receiveOthersInput();

protected:
    virtual void syncInput();

};

#endif // THREAD_BASE_H 