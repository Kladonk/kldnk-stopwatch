#include "StopwatchEventBase.h"

class StopwatchResetEvent : public StopwatchEventBase
{
public:
    StopwatchResetEvent(IStopwatch& stopwatch) : StopwatchEventBase(stopwatch) {};
    ~StopwatchResetEvent() {};

    std::string getName() override { return "StopwatchResetEvent"; };
};
