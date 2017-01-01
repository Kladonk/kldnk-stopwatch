#include "stopwatch-settings.h"
#include "time-util.h"


stopwatch_type settings_get_type(obs_data_t *settings)
{
    const char *type = obs_data_get_string(settings, SETTING_TYPE);
    if (strcmp(type, SETTING_TYPE_COUNTUP) == 0)
    {
        return STOPWATCH_TYPE_COUNTUP;
    }
    else if (strcmp(type, SETTING_TYPE_COUNTDOWN) == 0)
    {
        return STOPWATCH_TYPE_COUNTDOWN;
    }
    return STOPWATCH_TYPE_INVALID;
}


const char *settings_get_initial_value(obs_data_t *settings)
{
    return obs_data_get_string(settings, SETTING_COUNTDOWN_INITIALVALUE);
}


int64_t settings_get_initial_value_as_int(obs_data_t *settings)
{
    const char *time_string = settings_get_initial_value(settings);
    return time_string_to_millis(time_string);
}


const char *settings_get_end_value(obs_data_t *settings)
{
    return obs_data_get_string(settings, SETTING_COUNTUP_ENDVALUE);
}


int64_t settings_get_end_value_as_int(obs_data_t *settings)
{
    const char *time_string = settings_get_end_value(settings);
    return time_string_to_millis(time_string);
}
