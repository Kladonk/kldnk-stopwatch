#pragma once

class IStopwatchAction
{
public:
	virtual ~IStopwatchAction() {};
	virtual void execute() = 0;
};
