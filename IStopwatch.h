#pragma once

#include "events/IStopwatchEventListener.h"
#include "actions/IStopwatchAction.h"
#include <cstdint>

class IStopwatch
{
public:
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void reset() = 0;
    virtual void update(uint32_t elapsedMillis) = 0;
    virtual uint64_t getCurrentValue() = 0;

    virtual bool isEnabled() = 0;
    virtual bool isFinished() = 0;
    virtual uint64_t getElapsedMillis() = 0;

    virtual void addEventListener(IStopwatchEventListener *eventListener) = 0;
    virtual void addAction(IStopwatchAction *action) = 0;
};
