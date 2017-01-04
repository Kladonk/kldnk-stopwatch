#pragma once

#include "IStopwatchEventListener"
#include <obs-module.h>

#define log(loglevel, format, ...) (blog(loglevel, "[kldnk_stopwatch_source] " format, ##__VA_ARGS__))
#define info(format, ...) (log(LOG_INFO, format, ##__VA_ARGS__))
#define warn(format, ...) (log(LOG_WARNING, format, ##__VA_ARGS__))
#define error(format, ...) log(LOG_ERROR, format, ##__VA_ARGS__))

class LoggingEventListener
{
public:
	LoggingEventListener() {};
	~LoggingEventListener() override {};
    void handle(const IStopwatchEvent& event) overide
    {
    	
    };
};
