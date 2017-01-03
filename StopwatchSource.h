#pragma once

#include "StopwatchType.h"
#include "IStopwatch.h"
#include <obs-module.h>
#include <memory>


/**
 * The source class that brings together the stopwatch functionality with the
 * visual parts of the source plugin (i.e. displaying the current value).
 */
class StopwatchSource
{
private:
    obs_source_t *m_source;
    obs_source_t *m_textSource;
    std::shared_ptr<IStopwatch> m_stopwatch;
    obs_hotkey_id m_hk_enable;
    obs_hotkey_id m_hk_reset;
    float m_update_time_elapsed;

    void updateText();
    StopwatchType getStopwatchType();

public:
    StopwatchSource(obs_source_t *source_, obs_data_t *settings);
    ~StopwatchSource();
    void update(obs_data_t *settings);
    uint32_t getWidth();
    uint32_t getHeight();
    void render();
    void tick(float elapsedSeconds);
    obs_properties_t *getProperties();
    void enumActiveSources(obs_source_enum_proc_t enum_callback, void *param);
};
