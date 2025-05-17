#ifndef T2_H
#define T2_H

#include "thread_base.h"

class T2 : public ThreadBase {
public:
    explicit T2(Data& data);
    ~T2() override;

protected:
    void createInput() override;
    void sendAndReceiveInput() override;

protected:
    int computeLocalT() override;

protected:
    virtual void computeMAn() override;
    void calculateMAnLocal() override;

protected:
    virtual void afterDone() override;

protected:
    // input
    TMatrix MX, MZ;
    TMatrix MXn2, MZn2;

    // input from other threads
    TVector Cn2; TMatrix MD;
    TMatrix MR;

    // output
    TMatrix MA;

    std::chrono::time_point<std::chrono::system_clock> startTime;
    std::chrono::time_point<std::chrono::system_clock> endTime;
};

#endif // T2_H