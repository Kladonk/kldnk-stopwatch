#pragma once

#include "StopwatchEventBase.h"

class StopwatchFinishEvent : public StopwatchEventBase
{
public:
    StopwatchFinishEvent(IStopwatch& stopwatch) : StopwatchEventBase(stopwatch) {};
    ~StopwatchFinishEvent() {};

    const char *getName() override { return "StopwatchFinishEvent";  };
};
