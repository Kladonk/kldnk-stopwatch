#include "StopwatchBase.h"

class Timer : public StopwatchBase
{
private:
    uint64_t m_initialValue;
    
public:
    Timer(uint64_t initialValue) : StopwatchBase(), m_initialValue(initialValue) {};
    ~Timer() {};

    uint64_t getInitialValue() { return m_initialValue; };
    uint64_t getCurrentValue() override { return getInitialValue() - getElapsedMillis(); };
    bool checkIfFinished() override { return getInitialValue() - getElapsedMillis() <= 0; };
    void finish() { StopwatchBase::finish(); setElapsedMillis(0); };
};
