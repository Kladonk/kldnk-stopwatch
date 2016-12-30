#include "time-util.h"
#include "util/bmem.h"

time_info_t *millis_to_time(uint32_t millis)
{
    time_info_t *time_info = bzalloc(sizeof(time_info_t));
    time_info->millis = millis % 1000;
    millis /= 1000;
    time_info->seconds = millis % 60;
    millis /= 60;
    time_info->minutes = millis % 60;
    millis /= 60;
    time_info->hours = millis % 60;
    millis /= 60;
    return time_info;
}