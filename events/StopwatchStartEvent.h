#pragma once

#include "StopwatchEventBase.h"

class StopwatchStartEvent : public StopwatchEventBase
{
public:
    StopwatchStartEvent(IStopwatch& stopwatch) : StopwatchEventBase(stopwatch) {};
    ~StopwatchStartEvent() {};

    const char *getName() override { return "StopwatchStartEvent";  };
};
