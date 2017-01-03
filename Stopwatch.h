#include "StopwatchBase.h"

class Stopwatch : public StopwatchBase
{
private:
    uint64_t m_maxMillis;

public:
    Stopwatch(uint64_t maxMillis) : StopwatchBase(), m_maxMillis(maxMillis) {};
    ~Stopwatch() {};

    uint64_t getMaxMillis() { return m_maxMillis; };

    bool checkIfFinished() override { return getElapsedMillis() >= getMaxMillis(); };
};