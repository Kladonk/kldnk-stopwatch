#pragma once

#include "StopwatchEventBase.h"

class StopwatchStartEvent : public StopwatchEventBase
{
public:
    StopwatchStartEvent(IStopwatch& stopwatch) : StopwatchEventBase(stopwatch) {};
    ~StopwatchStartEvent() {};

    std::string getName() override { return "StopwatchStartEvent";  };
};
