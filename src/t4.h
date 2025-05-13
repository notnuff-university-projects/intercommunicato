#ifndef T4_H
#define T4_H

#include "thread_base.h"

class T4 : public ThreadBase {
public:
    explicit T4(Data& data);

protected:
    virtual void createInput();

protected:
    virtual void sendAndRecieveInput();
    virtual void receiveOthersInput();

protected:
    virtual void syncInput();

protected:
    // input
    TMatrix MR;

    // input from other threads
    TVector Cn4; TMatrix MD;
    TMatrix MXn4, MZn4;
};

#endif // T4_H