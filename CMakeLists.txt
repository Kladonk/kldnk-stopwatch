project(kldnk-stopwatch)

set(kldnk-stopwatch_SOURCES
    events/IStopwatchEventListener.h
    events/LoggingEventListener.h
    events/IStopwatchEvent.h
    events/StopwatchEventBase.h
    events/StopwatchStartEvent.h
    events/StopwatchStopEvent.h
    events/StopwatchResetEvent.h
    events/StopwatchFinishEvent.h

    actions/IStopwatchAction.h
    actions/StopwatchActionBase.h
    actions/SwitchSceneAction.h
    actions/SwitchSceneAction.cpp

    IStopwatch.h
    StopwatchBase.h
    StopwatchBase.cpp
    Stopwatch.h
    Timer.h

    StopwatchType.h
    StopwatchSettings.h
    TimeUtil.h
    TimeUtil.cpp
    ft2helper.c

    KldnkStopwatch.cpp
    )

add_library(kldnk-stopwatch MODULE
    ${kldnk-stopwatch_SOURCES})

target_link_libraries(kldnk-stopwatch
    libobs)

install_obs_plugin_with_data(kldnk-stopwatch data)
