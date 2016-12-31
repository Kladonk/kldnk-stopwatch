#pragma once

#include "stopwatch-type.h"
#include <obs-data.h>

#define SETTING_TYPE                            "type"
#define SETTING_TYPE_COUNTUP                    "type_countup"
#define SETTING_TYPE_COUNTDOWN                  "type_countdown"
#define SETTING_COUNTUP_ENDVALUE                "countup_endvalue"
#define SETTING_COUNTDOWN_INITIALVALUE          "countdown_initialvalue"


/**
 * Returs the stopwatch type (counting up or down).
 *
 * @param settings the settings
 * @return stopwatch type
 */
stopwatch_type settings_get_type(obs_data_t *settings);


/**
 * Returns the initial value, used e.q. for the counting down
 * stopwatch (aka timer).
 *
 * @param settings the settings
 * @return the initial value
 */
const char *settings_get_initial_value(obs_data_t *settings);


/**
 * Returns the initial value, used e.q. for the counting down
 * stopwatch (aka timer).
 *
 * @param settings the settings
 * @return the initial value as int
 */
int64_t settings_get_initial_value_as_int(obs_data_t *settings);


/**
 * Returns the end value, used e.q. for the counting up
 * stopwatch.
 *
 * @param settings the settings
 * @return the end value
 */
const char *settings_get_end_value(obs_data_t *settings);


/**
 * Returns the end value, used e.q. for the counting up
 * stopwatch.
 *
 * @param settings the settings
 * @return the end value as int
 */
int64_t settings_get_end_value_as_int(obs_data_t *settings);
