#pragma once

#include "IStopwatchEvent.h"
#include "../IStopwatch.h"

class StopwatchEventBase : public IStopwatchEvent
{
private:
    IStopwatch& m_stopwatch;

protected:
    StopwatchEventBase(IStopwatch& stopwatch) : m_stopwatch(stopwatch) {};
    ~StopwatchEventBase() {};

    IStopwatch& getStopwatch() { return m_stopwatch; };
};
