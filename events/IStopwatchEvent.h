#pragma once

class IStopwatchEvent
{
public:
	virtual ~IStopwatchEvent() {};
    virtual const char *getName() = 0;
};
