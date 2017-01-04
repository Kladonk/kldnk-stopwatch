#include "StopwatchEventBase.h"

class StopwatchResetEvent : public StopwatchEventBase
{
public:
    StopwatchResetEvent(IStopwatch& stopwatch) : StopwatchEventBase(stopwatch) {};
    ~StopwatchResetEvent() {};

    const char *getName() override { return "StopwatchResetEvent"; };
};
