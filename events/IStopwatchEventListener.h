#pragma once

#include "IStopwatchEvent.h"

class IStopwatchEventListener
{
public:
	virtual ~IStopwatchEventListener() {};
    virtual void handle(const IStopwatchEvent& event) = 0;
};
