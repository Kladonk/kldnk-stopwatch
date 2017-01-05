#pragma once

#include "IStopwatchAction.h"
#include "../IStopwatch.h"

class StopwatchActionBase : public IStopwatchAction
{
private:
    IStopwatch& m_stopwatch;

protected:
    StopwatchActionBase(IStopwatch& stopwatch) : m_stopwatch(stopwatch) {};
    ~StopwatchActionBase() {};

    IStopwatch& getStopwatch() { return m_stopwatch; };
};
