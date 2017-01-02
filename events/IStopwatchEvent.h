#pragma once

#include <string>

class IStopwatchEvent
{
public:
    virtual std::string getName() = 0;
};
