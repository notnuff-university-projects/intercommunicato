#ifndef T1_H
#define T1_H

#include "thread_base.h"

class T1 : public ThreadBase {
public:
    explicit T1(Data& data);

protected:
    void createInput() override;

protected:
    void sendAndReceiveInput() override;
    virtual void syncInput() override;

protected:
    // input
    TVector C;
    TMatrix MD;

    // input from other threads
    TMatrix MXn1, MZn1;
    TMatrix MR;
};

#endif // T1_H 