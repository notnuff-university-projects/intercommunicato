#ifndef T2_H
#define T2_H

#include "thread_base.h"

class T2 : public ThreadBase {
public:
    explicit T2(Data& data);

protected:
    void createInput() override;
    void sendAndReceiveInput() override;

protected:
    int computeLocalT() override;

protected:
    void calculateMAnLocal() override;

protected:
    // input
    TMatrix MX, MZ;
    TMatrix MXn2, MZn2;

    // input from other threads
    TVector Cn2; TMatrix MD;
    TMatrix MR;
};

#endif // T2_H