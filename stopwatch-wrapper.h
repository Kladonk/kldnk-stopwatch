#pragma once

#include <stdint.h>
#include <stdbool.h>


/**
 * Define stopwatch source structure.
 */
typedef struct stopwatch_source stopwatch_source_t;


/**
 * Starts the stopwatch.
 */
void start(stopwatch_source_t *stopwatch);


/**
 * Stops the stopwatch.
 */
void stop(stopwatch_source_t *stopwatch);


/**
 * Updates the stopwatch with the given millis_elapsed.
 */
void update(stopwatch_source_t *stopwatch, uint32_t millis_elapsed);


/**
 * Resets the stopwatch.
 */
void reset(stopwatch_source_t *stopwatch);


/**
 * Returns true if the stopwatch is enabled.
 */
bool is_enabled(stopwatch_source_t *stopwatch);


/**
 * Returns true if the stopwatch has finished.
 */
bool is_finished(stopwatch_source_t *stopwatch);
