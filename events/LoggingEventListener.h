/******************************************************************************
    Kladonk Stopwatch Plugin
    Copyright(C) 2016-2017 Jan Held <development@kladonk.de>

    This program is free software : you can redistribute it and / or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

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
