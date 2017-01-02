#include "StopwatchEventBase.h"

class StopwatchStopEvent : public StopwatchEventBase
{
public:
    StopwatchStopEvent(IStopwatch& stopwatch) : StopwatchEventBase(stopwatch) {};
    ~StopwatchStopEvent() {};

    std::string getName() override { return "StopwatchStopEvent"; };
};
