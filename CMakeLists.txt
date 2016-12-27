project(kldnk-stopwatch)

set(kldnk-stopwatch_SOURCES
	kldnk-stopwatch.h
	kldnk-stopwatch.c
	)

add_library(kldnk-stopwatch MODULE
	${kldnk-stopwatch_SOURCES})

target_link_libraries(kldnk-stopwatch
	libobs)

install_obs_plugin_with_data(kldnk-stopwatch data)
