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

#include "StopwatchType.h"
#include "TimeUtil.h"
#include <obs-data.h>
#include <string>


#define S_TYPE              "type"
#define S_TYPE_STOPWATCH    "type_stopwatch"
#define S_TYPE_TIMER        "type_timer"
#define S_ENDVALUE          "endvalue"
#define S_INITIALVALUE      "initialvalue"


/**
 * Returs the stopwatch type (counting up or down).
 *
 * @param settings the settings
 * @return stopwatch type
 */
StopwatchType settings_get_type(obs_data_t *settings)
{
    const char *type = obs_data_get_string(settings, S_TYPE);
    if (strcmp(type, S_TYPE_TIMER) == 0)
    {
        return StopwatchType::Timer;
    }
    return StopwatchType::Stopwatch;
}


/**
 * Returns the initial value, used e.q. for the counting down
 * stopwatch (aka timer).
 *
 * @param settings the settings
 * @return the initial value
 */
const char *settings_get_initial_value(obs_data_t *settings)
{
    return obs_data_get_string(settings, S_INITIALVALUE);
}


/**
 * Returns the initial value, used e.q. for the counting down
 * stopwatch (aka timer).
 *
 * @param settings the settings
 * @return the initial value as int
 */
int64_t settings_get_initial_value_as_int(obs_data_t *settings)
{
    const char *timeString = settings_get_initial_value(settings);
    return time_string_to_millis(std::string(timeString));
}


/**
 * Returns the end value, used e.q. for the counting up
 * stopwatch.
 *
 * @param settings the settings
 * @return the end value
 */
const char *settings_get_end_value(obs_data_t *settings)
{
    return obs_data_get_string(settings, S_ENDVALUE);
}


/**
 * Returns the end value, used e.q. for the counting up
 * stopwatch.
 *
 * @param settings the settings
 * @return the end value as int
 */
int64_t settings_get_end_value_as_int(obs_data_t *settings)
{
    const char *timeString = settings_get_end_value(settings);
    return time_string_to_millis(std::string(timeString));
}
