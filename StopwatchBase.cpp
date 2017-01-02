#include "StopwatchBase.h"
#include "events/StopwatchStartEvent.h"
#include "events/StopwatchStopEvent.h"
#include "events/StopwatchResetEvent.h"

void StopwatchBase::start()
{
    setEnabled(true);
    fireEvent(StopwatchStartEvent(*this));
};


void StopwatchBase::stop()
{
    setEnabled(false);
    fireEvent(StopwatchStopEvent(*this));
};


void StopwatchBase::reset()
{
    init();
    fireEvent(StopwatchResetEvent(*this));
}
