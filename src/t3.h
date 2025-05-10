#ifndef T3_H
#define T3_H

#include "thread_base.h"

class T3 : public ThreadBase {
public:
    explicit T3(Data& data);

protected:
    virtual void execute() override;
};

#endif // T3_H 