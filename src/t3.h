#ifndef T3_H
#define T3_H

#include "thread_base.h"

class T3 : public ThreadBase {
public:
    explicit T3(Data& data);

protected:
    void sendAndReceiveInput() override;

protected:
    int computeLocalT() override;

protected:
    void calculateMAnLocal() override;

protected:
    // input from other threads
    TVector Cn3; TMatrix MD;
    TMatrix MXn3, MZn3;
    TMatrix MR;
};

#endif // T3_H