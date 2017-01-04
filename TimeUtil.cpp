#include "TimeUtil.h"
#include <stdint.h>
#include <util/dstr.h>


time_info_t time_string_to_time(std::string timeString)
{
    time_info_t ti;
    ti.hours = 0;
    ti.minutes = 0;
    ti.seconds = 0;
    ti.millis = 0;

    char **tokens = strlist_split(timeString.c_str(), ':', false);
    if (tokens && tokens[0] && tokens[1] && tokens[2])
    {
        ti.hours = atoi(tokens[0]);
        ti.minutes = atoi(tokens[1]);
        ti.seconds = atoi(tokens[2]);
    }
    strlist_free(tokens);

    return ti;
}


time_info_t millis_to_time(int64_t millis)
{
    time_info_t ti;
    ti.millis = millis % 1000;
    millis /= 1000;
    ti.seconds = millis % 60;
    millis /= 60;
    ti.minutes = millis % 60;
    millis /= 60;
    ti.hours = millis % 60;
    return ti;
}


int64_t time_string_to_millis(std::string timeString)
{
    time_info_t ti = time_string_to_time(timeString);
    int64_t millis = time_to_millis(ti);
    return millis;
}


int64_t time_to_millis(time_info_t ti)
{
    return ti.hours * 3600000 +
        ti.minutes * 60000 +
        ti.seconds * 1000 +
        ti.millis;
}


std::string millis_to_string(int64_t millis)
{
    time_info_t ti = millis_to_time(millis);
    std::string text = time_to_string(ti);
    return text;
}


std::string time_to_string(time_info_t ti)
{
    char text[9];
    snprintf(text, sizeof(text), "%02d:%02d:%02d", ti.hours, ti.minutes, ti.seconds);
    return std::string(text);
}
