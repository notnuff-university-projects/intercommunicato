#ifndef T4_H
#define T4_H

#include "thread_base.h"

class T4 : public ThreadBase {
public:
    explicit T4(Data& data);

protected:
    void createInput() override;
    void sendAndReceiveInput() override;

protected:
    int computeLocalT() override;

protected:
    void calculateMAnLocal() override;

protected:
    // input
    TMatrix MR;

    // input from other threads
    TVector Cn4; TMatrix MD;
    TMatrix MXn4, MZn4;
};

#endif // T4_H