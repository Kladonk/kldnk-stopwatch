#include "StopwatchSource.h"
#include "Stopwatch.h"
#include "Timer.h"
#include "time-util.h"
#include <memory>
#include <obs-module.h>
#include <obs-internal.h>


/**
 * Update the stopwatch every 15 milliseconds
 */
#define UPDATE_AFTER_SECONDS    0.015f

#define T_(v)               obs_module_text(v)
#define T_NAME              T_("StopwatchSource")
#define T_TYPE              T_("Type")
#define T_TYPE_COUNTUP      T_("Type.Countup")
#define T_TYPE_COUNTDOWN    T_("Type.Countdown")
#define T_ENDVALUE          T_("EndValue")
#define T_INITIALVALUE      T_("InitialValue")
#define T_HK_ENABLE         T_("Hotkey.Enable")
#define T_HK_RESET          T_("Hotkey.Reset")


StopwatchSource::StopwatchSource(obs_source_t *source_, obs_data_t *settings)
{
    m_update_time_elapsed = 0.0f;
}


StopwatchSource::~StopwatchSource()
{
    // Unregister hotkeys
    obs_hotkey_unregister(m_hk_enable);
    obs_hotkey_unregister(m_hk_reset);

    // Release textSource
    obs_source_remove(m_textSource);
    obs_source_release(m_textSource);
    m_textSource = NULL;

    // TODO Check if obs_source_release also frees the memory e.g. bfree(m_textSource)
}


StopwatchType StopwatchSource::getStopwatchType()
{
    IStopwatch *stopwatch = m_stopwatch.get();

    stopwatch = dynamic_cast<Stopwatch*>(stopwatch);
    if (stopwatch != nullptr)
    {
        return StopwatchType::Stopwatch;
    }

    stopwatch = dynamic_cast<Timer*>(stopwatch);
    if (stopwatch != nullptr)
    {
        return StopwatchType::Timer;
    }

    return StopwatchType::Invalid;
}


void StopwatchSource::updateText()
{
    const char *time_string = millis_to_string(m_stopwatch->getCurrentValue());
    obs_data_set_string(m_textSource->context.settings, "text", time_string);
    obs_source_update(m_textSource, m_textSource->context.settings);
}


void StopwatchSource::update(obs_data_t *settings)
{
    // TODO
}


uint32_t StopwatchSource::getWidth()
{
    return obs_source_get_width(m_textSource);
}


uint32_t StopwatchSource::getHeight()
{
    return obs_source_get_height(m_textSource);
}


void StopwatchSource::render()
{
    // TODO
}


void StopwatchSource::tick(float elapsedSeconds)
{
    m_stopwatch.get()->update(elapsedSeconds * 1000);

    m_update_time_elapsed += elapsedSeconds;

    if (m_update_time_elapsed >= UPDATE_AFTER_SECONDS)
    {
        m_update_time_elapsed = 0;
        updateText();
    }
}


obs_properties_t *StopwatchSource::getProperties()
{
    // TODO
    return NULL;
}


void StopwatchSource::enumActiveSources(obs_source_enum_proc_t enum_callback, void *param)
{
    enum_callback(m_source, m_textSource, param);
}
