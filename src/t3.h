#ifndef T3_H
#define T3_H

#include "thread_base.h"

class T3 : public ThreadBase {
public:
    explicit T3(Data& data);

protected:
    virtual void createInput();

protected:
    virtual void sendAndRecieveInput();
    virtual void receiveOthersInput();

protected:
    virtual void syncInput();

protected:
    // input from other threads
    TVector Cn3; TMatrix MD;
    TMatrix MX3, MZ3;
    TMatrix MR;
};

#endif // T3_H