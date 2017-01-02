#pragma once

#include "IStopwatchEvent.h"

class IStopwatchEventListener
{
public:
    virtual void handle(const IStopwatchEvent& event) = 0;
};
