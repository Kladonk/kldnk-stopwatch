#include "StopwatchEventBase.h"

class StopwatchStopEvent : public StopwatchEventBase
{
public:
    StopwatchStopEvent(IStopwatch& stopwatch) : StopwatchEventBase(stopwatch) {};
    ~StopwatchStopEvent() {};

    const char *getName() override { return "StopwatchStopEvent"; };
};
