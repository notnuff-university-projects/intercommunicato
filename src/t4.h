#ifndef T4_H
#define T4_H

#include "thread_base.h"

class T4 : public ThreadBase {
public:
    explicit T4(Data& data);

protected:
    virtual void input() override;

    TMatrix MR;
};

#endif // T4_H 