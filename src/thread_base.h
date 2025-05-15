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
    virtual void computeMAn();

    virtual void calculateMAnLocal() = 0;
    void calculateAndStashMAnLocal(
        const TMatrix& MXnLocal,
        const TMatrix& MR,
        int t,
        const TMatrix& MZnLocal,
        const TMatrix& MD
        );

    void sendMAn();

protected:
    int t = std::numeric_limits<int>::max();
    std::string name;

    TMatrix MAnLocal;
};

#endif // THREAD_BASE_H