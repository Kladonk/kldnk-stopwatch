#pragma once

#include "IStopwatchEvent.h"

class IStopwatchEventListener
{
public:
	virtual ~IStopwatchEventListener() {};
    virtual void handle(IStopwatchEvent *event) = 0;
};
