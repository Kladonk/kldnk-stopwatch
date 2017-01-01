#include "time-util.h"
#include "util/bmem.h"
#include <util/dstr.h>
#include <stdlib.h>
#include <stdio.h>


time_info_t *time_string_to_time(const char *time_string)
{
	time_info_t *ti = bzalloc(sizeof(time_info_t));
	ti->hours = 0;
	ti->minutes = 0;
	ti->seconds = 0;
	ti->millis = 0;

	if (time_string)
	{
		char **tokens = strlist_split(time_string, ':', false);
		if (tokens && tokens[0] && tokens[1] && tokens[2])
		{
			ti->hours = atoi(tokens[0]);
			ti->minutes = atoi(tokens[1]);
			ti->seconds = atoi(tokens[2]);
		}
		strlist_free(tokens);
	}

	return ti;
}


time_info_t *millis_to_time(int64_t millis)
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


int64_t time_string_to_millis(const char *time_string)
{
	time_info_t *ti = time_string_to_time(time_string);
	int64_t millis = time_to_millis(ti);
	bfree(ti);
	return millis;
}


int64_t time_to_millis(time_info_t *ti)
{
	return ti->hours * 3600000 +
		ti->minutes * 60000 +
		ti->seconds * 1000 +
		ti->millis;
}


const char *millis_to_string(int64_t millis)
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