#include "Stopwatch.h"
#include "Timer.h"
#include <obs-module.h>
#include <memory>

extern "C" {
    #include "time-util.h"
}


/**
 * Update the stopwatch every 15 milliseconds
 */
#define UPDATE_AFTER_SECONDS    0.015f

 /**
 * The ID of the text_ft2_source to instantiate the sub-source
 */
#define TEXT_SOURCE_ID      "text_ft2_source\0"

/*
 * Define texts
 */
#define T_(v)               obs_module_text(v)
#define T_NAME              T_("StopwatchSource")
#define T_TYPE              T_("Type")
#define T_TYPE_COUNTUP      T_("Type.Countup")
#define T_TYPE_COUNTDOWN    T_("Type.Countdown")
#define T_ENDVALUE          T_("EndValue")
#define T_INITIALVALUE      T_("InitialValue")
#define T_HK_ENABLE         T_("Hotkey.Enable")
#define T_HK_RESET          T_("Hotkey.Reset")

#define AS_STOPWATCH(v)     (reinterpret_cast<StopwatchSource*>(v))


OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("kldnk-stopwatch", "en-US")


// Need to be declared outside of this compilation unit because it needs
// to #include <obs-internla.h> which is currently incompatible with C++.
extern "C" {
    void update_ft2_text(obs_source_t *textSource, const char *text);
}


/**
 * Enum class that defines the avaliable types of stopwatches.
 */
enum class StopwatchType
{
    Stopwatch,
    Timer,
    Invalid
};


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


StopwatchSource::StopwatchSource(obs_source_t *source, obs_data_t *settings)
{
    m_update_time_elapsed = 0.0f;

    m_source = source;
    m_textSource = obs_source_create(TEXT_SOURCE_ID, TEXT_SOURCE_ID, settings, NULL);
    /*
    stopwatch->type = settings_get_type(settings);
    stopwatch->initial_value = settings_get_initial_value_as_int(settings);
    stopwatch->end_value = settings_get_end_value_as_int(settings);
    reset(stopwatch);

    obs_source_add_active_child(stopwatch->source, stopwatch->textSource);

    init_stopwatch_hotkeys(stopwatch);

    update_stopwatch_text(stopwatch);

    return stopwatch;
    */
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
    update_ft2_text(m_textSource, time_string);
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


/**
 * The plugin starting function. Called when the plugin is loaded.
 *
 * @return true
 */
bool obs_module_load(void)
{
    struct obs_source_info si = {};
    si.id = "kldnk_stopwatch_source";
    si.type = OBS_SOURCE_TYPE_INPUT;
    si.output_flags = OBS_SOURCE_VIDEO;
    si.get_name = [] (void *type_data)
    {
        return obs_module_text("StopwatchSource");
    };
    si.create = [] (obs_data_t *settings, obs_source_t *source)
    {
        return (void*)new StopwatchSource(source, settings);
    };
    si.destroy = [] (void *data)
    {
        delete AS_STOPWATCH(data);
    };
    si.update = [] (void *data, obs_data_t *settings)
    {
        AS_STOPWATCH(data)->update(settings);
    };
    si.get_width = [] (void *data)
    {
        return AS_STOPWATCH(data)->getWidth();
    };
    si.get_height = [] (void *data)
    {
        return AS_STOPWATCH(data)->getHeight();
    };
    si.video_render = [] (void *data, gs_effect_t *effect)
    {
        AS_STOPWATCH(data)->render();
    };
    si.video_tick = [] (void *data, float seconds)
    {
        AS_STOPWATCH(data)->tick(seconds);
    };
    si.get_defaults = [] (obs_data_t *settings)
    {
        // TODO
    };
    si.get_properties = [] (void *data)
    {
        return AS_STOPWATCH(data)->getProperties();
    };
    si.enum_active_sources = [] (void *data, obs_source_enum_proc_t enum_callback, void *param)
    {
        return AS_STOPWATCH(data)->enumActiveSources(enum_callback, param);
    };

    obs_register_source(&si);
    return true;
}


/**
 * The plugin end function. Called when the plugin is unloaded.
 */
void obs_module_unload(void)
{
    // TODO
}
