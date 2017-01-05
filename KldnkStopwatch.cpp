#include "Stopwatch.h"
#include "Timer.h"
#include "StopwatchSettings.h"
#include "TimeUtil.h"
#include "events/LoggingEventListener.h"
//#include "actions/SwitchSceneAction.h"
#include <obs-module.h>
#include <memory>


/**
 * Update the stopwatch every 15 milliseconds
 */
#define UPDATE_AFTER_SECONDS        0.015f

 /**
 * The ID of the text_ft2_source to instantiate the sub-source
 */
#define TEXT_STOPWATCH_SOURCE_ID    "text_ft2_source\0"

 /*
 * Define hotkeys
 */
#define HOTKEY_STOPWATCH_TOGGLE     "kldnk_stopwatch_toggle"
#define HOTKEY_STOPWATCH_RESET      "kldnk_stopwatch_reset"

/*
 * Define texts
 */
#define T_(v)                       obs_module_text(v)
#define T_NAME                      T_("StopwatchSource")
#define T_TYPE                      T_("Type")
#define T_TYPE_STOPWATCH            T_("Type.Stopwatch")
#define T_TYPE_TIMER                T_("Type.Timer")
#define T_ENDVALUE                  T_("EndValue")
#define T_INITIALVALUE              T_("InitialValue")
#define T_HK_ENABLE                 T_("Hotkey.Enable")
#define T_HK_RESET                  T_("Hotkey.Reset")

#define STOPWATCH_SOURCE_(v)        (reinterpret_cast<StopwatchSource*>(v))


OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("kldnk-stopwatch", "en-US")


// Need to be declared outside of this compilation unit because it needs
// to #include <obs-internal.h> which is currently incompatible with C++.
extern "C" {
    void update_ft2_text(obs_source_t *textSource, const char *text);
}


/**
 * Forward declarations of callback functions.
 */
void stopwatch_enable_hotkey_pressed(void *data, obs_hotkey_id id, obs_hotkey_t *hotkey, bool pressed);
void stopwatch_reset_hotkey_pressed(void *data, obs_hotkey_id id, obs_hotkey_t *hotkey, bool pressed);
bool stopwatch_type_changed(obs_properties_t *props, obs_property_t *property, obs_data_t *settings);


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
    obs_hotkey_id m_hkEnable;
    obs_hotkey_id m_hkReset;
    float m_updateTimeElapsed;

    void initStopwatch(obs_data_t *settings);
    void initHotkeys();
    void updateText();
    StopwatchType getStopwatchType();
    IStopwatch *getStopwatch() { return m_stopwatch.get(); };

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

    void toggle();
    void reset();
};


StopwatchSource::StopwatchSource(obs_source_t *source, obs_data_t *settings)
{
    m_updateTimeElapsed = 0.0f;

    m_source = source;

    m_textSource = obs_source_create(TEXT_STOPWATCH_SOURCE_ID, TEXT_STOPWATCH_SOURCE_ID, settings, NULL);
    obs_source_add_active_child(m_source, m_textSource);

    initStopwatch(settings);
    initHotkeys();

    //getStopwatch()->addAction(new SwitchSceneAction(*getStopwatch()));
    getStopwatch()->addEventListener(new LoggingEventListener());

    updateText();
}


void StopwatchSource::initStopwatch(obs_data_t *settings)
{
    StopwatchType type = settings_get_type(settings);
    if (type == StopwatchType::Timer)
    {
        uint64_t initialValue = settings_get_initial_value_as_int(settings);
        m_stopwatch = std::make_shared<Timer>(initialValue); 
    }
    else
    {
        uint64_t maxValue = settings_get_end_value_as_int(settings);
        m_stopwatch = std::make_shared<Stopwatch>(maxValue); 
    }
}


void StopwatchSource::initHotkeys()
{
    m_hkEnable = obs_hotkey_register_source(m_source,
            HOTKEY_STOPWATCH_TOGGLE, T_HK_ENABLE,
            stopwatch_enable_hotkey_pressed, this);

    m_hkReset = obs_hotkey_register_source(m_source,
            HOTKEY_STOPWATCH_RESET, T_HK_RESET,
            stopwatch_reset_hotkey_pressed, this);
}


/**
 * Callback fuunction to enable/disable the stopwatch.
 */
void stopwatch_enable_hotkey_pressed(void *data, obs_hotkey_id id, obs_hotkey_t *hotkey, bool pressed)
{
    StopwatchSource *stopwatch = STOPWATCH_SOURCE_(data);
    if (pressed && stopwatch)
    {
        stopwatch->toggle();
    }

    UNUSED_PARAMETER(id);
    UNUSED_PARAMETER(hotkey);
}


/**
 * Callback function to reset the stopwatch.
 */
void stopwatch_reset_hotkey_pressed(void *data, obs_hotkey_id id, obs_hotkey_t *hotkey, bool pressed)
{
    StopwatchSource *stopwatch = STOPWATCH_SOURCE_(data);
    if (pressed && stopwatch)
    {
        stopwatch->reset();
    }

    UNUSED_PARAMETER(id);
    UNUSED_PARAMETER(hotkey);
}


StopwatchSource::~StopwatchSource()
{
    // Unregister hotkeys
    obs_hotkey_unregister(m_hkEnable);
    obs_hotkey_unregister(m_hkReset);

    // Release textSource
    obs_source_remove(m_textSource);
    obs_source_release(m_textSource);
    m_textSource = NULL;
}


StopwatchType StopwatchSource::getStopwatchType()
{
    IStopwatch *stopwatch = m_stopwatch.get();

    stopwatch = dynamic_cast<Timer*>(stopwatch);
    if (stopwatch != nullptr)
    {
        return StopwatchType::Timer;
    }
    return StopwatchType::Stopwatch;
}


void StopwatchSource::updateText()
{
    std::string timeString = millis_to_string(m_stopwatch->getCurrentValue());
    update_ft2_text(m_textSource, timeString.c_str());
}


void StopwatchSource::update(obs_data_t *settings)
{
    initStopwatch(settings);
    updateText();
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
    obs_source_video_render(m_textSource);
}


void StopwatchSource::tick(float elapsedSeconds)
{
    getStopwatch()->update(elapsedSeconds * 1000);

    m_updateTimeElapsed += elapsedSeconds;

    if (m_updateTimeElapsed >= UPDATE_AFTER_SECONDS)
    {
        m_updateTimeElapsed = 0;
        updateText();
    }
}


obs_properties_t *StopwatchSource::getProperties()
{
    // Add text source properties and set visibility 
    obs_properties_t *props = obs_source_properties(m_textSource);
    obs_property_t *prop = obs_properties_first(props);
    while (prop)
    {
        const char *name = obs_property_name(prop);
        bool visible = strcmp(name, "font") == 0 ||
                       strcmp(name, "color1") == 0 ||
                       strcmp(name, "color2") == 0 ||
                       strcmp(name, "outline") == 0 ||
                       strcmp(name, "drop_shadow") == 0;

        obs_property_set_visible(prop, visible);

        obs_property_next(&prop);
    }

    // Add the stopwatch specific properties
    prop = obs_properties_add_list(props, S_TYPE, T_TYPE, OBS_COMBO_TYPE_LIST, OBS_COMBO_FORMAT_STRING);
    obs_property_list_add_string(prop, T_TYPE_STOPWATCH, S_TYPE_STOPWATCH);
    obs_property_list_add_string(prop, T_TYPE_TIMER, S_TYPE_TIMER);
    obs_property_set_modified_callback(prop, stopwatch_type_changed);

    prop = obs_properties_add_text(props, S_ENDVALUE, T_ENDVALUE, OBS_TEXT_DEFAULT);
    obs_property_set_visible(prop, true);

    prop = obs_properties_add_text(props, S_INITIALVALUE, T_INITIALVALUE, OBS_TEXT_DEFAULT);
    obs_property_set_visible(prop, false);

    return props;
}


void set_property_visibility(obs_properties_t *props, const char *name, bool visible)
{
    obs_property_t *prop = obs_properties_get(props, name);
    obs_property_set_visible(prop, visible);
}


bool stopwatch_type_changed(obs_properties_t *props, obs_property_t *property, obs_data_t *settings)
{
    StopwatchType type = settings_get_type(settings);
    set_property_visibility(props, S_ENDVALUE, type == StopwatchType::Stopwatch);
    set_property_visibility(props, S_INITIALVALUE, type == StopwatchType::Timer);

    UNUSED_PARAMETER(property);
    return true;
}


void StopwatchSource::enumActiveSources(obs_source_enum_proc_t enum_callback, void *param)
{
    enum_callback(m_source, m_textSource, param);
}


void StopwatchSource::toggle()
{
    IStopwatch *s = getStopwatch();
    if (s->isEnabled())
    {
        s->stop();
    }
    else if (!s->isFinished())
    {
        s->start();
    }
}


void StopwatchSource::reset()
{
    IStopwatch *s = getStopwatch();
    if (!s->isEnabled() || s->isFinished())
    {
        s->reset();
    }
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
        UNUSED_PARAMETER(type_data);
        return obs_module_text("StopwatchSource");
    };
    si.create = [] (obs_data_t *settings, obs_source_t *source)
    {
        return (void*)new StopwatchSource(source, settings);
    };
    si.destroy = [] (void *data)
    {
        delete STOPWATCH_SOURCE_(data);
    };
    si.update = [] (void *data, obs_data_t *settings)
    {
        STOPWATCH_SOURCE_(data)->update(settings);
    };
    si.get_width = [] (void *data)
    {
        return STOPWATCH_SOURCE_(data)->getWidth();
    };
    si.get_height = [] (void *data)
    {
        return STOPWATCH_SOURCE_(data)->getHeight();
    };
    si.video_render = [] (void *data, gs_effect_t *effect)
    {
        UNUSED_PARAMETER(effect);
        STOPWATCH_SOURCE_(data)->render();
    };
    si.video_tick = [] (void *data, float seconds)
    {
        STOPWATCH_SOURCE_(data)->tick(seconds);
    };
    si.get_defaults = [] (obs_data_t *settings)
    {
        obs_data_set_default_bool(settings, "unload", false);
        obs_data_set_default_string(settings, S_TYPE, S_TYPE_STOPWATCH);
    };
    si.get_properties = [] (void *data)
    {
        return STOPWATCH_SOURCE_(data)->getProperties();
    };
    si.enum_active_sources = [] (void *data, obs_source_enum_proc_t enum_callback, void *param)
    {
        return STOPWATCH_SOURCE_(data)->enumActiveSources(enum_callback, param);
    };

    obs_register_source(&si);
    return true;
}


/**
 * The plugin end function. Called when the plugin is unloaded.
 */
void obs_module_unload(void)
{
    // Nothing to do so far
}
