#pragma once

#include <string>

class IStopwatchEvent
{
public:
	virtual ~IStopwatchEvent() {};
    virtual std::string getName() = 0;
};
