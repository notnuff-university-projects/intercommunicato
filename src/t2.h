#ifndef T2_H
#define T2_H

#include "thread_base.h"

class T2 : public ThreadBase {
public:
    explicit T2(Data& data);

protected:
    virtual void input() override;

    TMatrix MX, MZ;
    TMatrix MA;
};

#endif // T2_H 