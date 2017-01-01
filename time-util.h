#pragma once

#include <stdint.h>

/**
 * Time structure for storing hours, minutes, seconds and millis.
 */
typedef struct time_info {
    uint32_t hours;
    uint32_t minutes;
    uint32_t seconds;
    uint32_t millis;
} time_info_t;


/**
* Parses a time string an returns the representing time_info struct.
*
* @param time_string the time string (format: hh:mm:ss)
* @return the time_info struct representing the time string
*/
time_info_t *time_string_to_time(const char *time_string);


/**
* Converts millis to a time_info structure.
*
* @param millis the milliseconds
* @return the time_info struct
*/
time_info_t *millis_to_time(int64_t millis);


/**
 * Parses a time string an returns the representing millis.
 *
 * @param time_string the time string (format: hh:mm:ss)
 * @return the milliseconds representing the time string
 */
int64_t time_string_to_millis(const char *time_string);


/**
* Converts the time_info structure to millis.
*
* @param ti the time_info struct
* @return the milliseconds
*/
int64_t time_to_millis(time_info_t *ti);


/**
* Returns the string representation of the millis.
*
* @param millis the milliseconds
* @return the string representing the milliseconds (format: hh:mm:ss);
*/
const char *millis_to_string(int64_t millis);


/**
 * Returns the string representation of the time_info structure.
 *
 * @param ti the time_info struct
 * @return the string representing the time_info struct (format: hh:mm:ss)
 */
const char *time_to_string(time_info_t *ti);
