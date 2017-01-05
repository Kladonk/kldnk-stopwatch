#pragma once

#include "StopwatchActionBase.h"

class SwitchSceneAction : public StopwatchActionBase
{
public:
    SwitchSceneAction(IStopwatch& stopwatch) : StopwatchActionBase(stopwatch) {};
    ~SwitchSceneAction() {};

    void execute() override;
};
