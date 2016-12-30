#pragma once

#include <stdint.h>

typedef struct time_info {
	uint32_t hours;
	uint32_t minutes;
	uint32_t seconds;
	uint32_t millis;
} time_info_t;

time_info_t *millis_to_time(uint32_t millis);
