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
    const char *time_string = settings_get_initial_value(settings);
    return time_string_to_millis(time_string);
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
    const char *time_string = settings_get_end_value(settings);
    return time_string_to_millis(time_string);
}
