project(kldnk-stopwatch)

set(kldnk-stopwatch_SOURCES
    events/IStopwatchEventListener.h
    events/IStopwatchEvent.h
    events/StopwatchEventBase.h
    events/StopwatchStartEvent.h
    events/StopwatchStopEvent.h
    events/StopwatchResetEvent.h

    actions/IStopwatchAction.h
    actions/StopwatchActionBase.h
    actions/SwitchSceneAction.h
    actions/SwitchSceneAction.cpp

    IStopwatch.h
    StopwatchBase.h
    StopwatchBase.cpp
    Stopwatch.h
    Timer.h
    
    time-util.h
    time-util.c
    stopwatch-type.h
    stopwatch-settings.h
    stopwatch-settings.c
    stopwatch-wrapper.h
    stopwatch-wrapper.c
    kldnk-stopwatch.c
    )

add_library(kldnk-stopwatch MODULE
    ${kldnk-stopwatch_SOURCES})

target_link_libraries(kldnk-stopwatch
    libobs)

install_obs_plugin_with_data(kldnk-stopwatch data)
