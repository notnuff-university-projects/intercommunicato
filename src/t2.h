#ifndef T2_H
#define T2_H

#include "thread_base.h"

class T2 : public ThreadBase {
public:
    explicit T2(Data& data);

protected:
    void createInput() override;

protected:
    void sendAndReceiveInput() override;

protected:
    void syncInput() override;

protected:
    // input
    TMatrix MX, MZ;

    // input from other threads
    TVector Cn2; TMatrix MD;
    TMatrix MR;
};

#endif // T2_H