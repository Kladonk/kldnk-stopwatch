#pragma once

#include "IStopwatchEventListener.h"
#include <obs-module.h>

#define log(loglevel, format, ...) (blog(loglevel, "[kldnk_stopwatch_source] " format, ##__VA_ARGS__))
#define info(format, ...) (log(LOG_INFO, format, ##__VA_ARGS__))
#define warn(format, ...) (log(LOG_WARNING, format, ##__VA_ARGS__))
#define error(format, ...) log(LOG_ERROR, format, ##__VA_ARGS__))

class LoggingEventListener : public IStopwatchEventListener
{
public:
    void handle(IStopwatchEvent *event) override { info("%s", event->getName()); };
};
