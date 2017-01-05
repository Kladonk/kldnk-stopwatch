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

#include <stdint.h>
#include <string>

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
* @return the timeString struct representing the time string
*/
time_info_t time_string_to_time(std::string timeString);


/**
* Converts millis to a time_info structure.
*
* @param millis the milliseconds
* @return the time_info struct
*/
time_info_t millis_to_time(int64_t millis);


/**
 * Parses a time string an returns the representing millis.
 *
 * @param timeString the time string (format: hh:mm:ss)
 * @return the milliseconds representing the time string
 */
int64_t time_string_to_millis(std::string timeString);


/**
* Converts the time_info structure to millis.
*
* @param ti the time_info struct
* @return the milliseconds
*/
int64_t time_to_millis(time_info_t ti);


/**
* Returns the string representation of the millis.
*
* @param millis the milliseconds
* @return the string representing the milliseconds (format: hh:mm:ss);
*/
std::string millis_to_string(int64_t millis);


/**
 * Returns the string representation of the time_info structure.
 *
 * @param ti the time_info struct
 * @return the string representing the time_info struct (format: hh:mm:ss)
 */
std::string time_to_string(time_info_t ti);
