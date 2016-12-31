#include "time-util.h"
#include "util/bmem.h"
#include <stdio.h>

time_info_t *time_string_to_time(const char *time_string)
{
	//const char *delimiters = ":";
	//char *running = bstrdup(time_string);

	// TODO

	//bfree(running);
	
	time_info_t *ti = bzalloc(sizeof(time_info_t));
	ti->hours = 0;
	ti->minutes = 0;
	ti->seconds = 0;
	ti->millis = 0;

	return ti;
}


time_info_t *millis_to_time(uint32_t millis)
{
	time_info_t *ti = bzalloc(sizeof(time_info_t));
	ti->millis = millis % 1000;
	millis /= 1000;
	ti->seconds = millis % 60;
	millis /= 60;
	ti->minutes = millis % 60;
	millis /= 60;
	ti->hours = millis % 60;
	return ti;
}


uint32_t time_string_to_millis(const char *time_string)
{
	time_info_t *ti = time_string_to_time(time_string);
	uint32_t millis = time_to_millis(ti);
	bfree(ti);
	return millis;
}


uint32_t time_to_millis(time_info_t *ti)
{
	return ti->hours * 3600000 +
		ti->minutes * 60000 +
		ti->seconds * 1000 +
		ti->millis;
}


const char *millis_to_string(uint32_t millis)
{
	time_info_t *ti = millis_to_time(millis);
	const char *text = time_to_string(ti);
	bfree(ti);
	return text;
}


const char *time_to_string(time_info_t *ti)
{
	char text[9];
	snprintf(text, sizeof(text), "%02d:%02d:%02d", ti->hours, ti->minutes, ti->seconds);
	return bstrdup(text);
}