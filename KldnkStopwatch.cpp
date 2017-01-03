#include <obs-module.h>
#include "Stopwatch.h"
#include "Timer.h"

#define T_(v)               obs_module_text(v)
#define T_NAME              T_("StopwatchSource")
#define T_TYPE              T_("Type")
#define T_TYPE_COUNTUP      T_("Type.Countup")
#define T_TYPE_COUNTDOWN    T_("Type.Countdown")
#define T_ENDVALUE          T_("EndValue")
#define T_INITIALVALUE      T_("InitialValue")
#define T_HK_ENABLE         T_("Hotkey.Enable")
#define T_HK_RESET          T_("Hotkey.Reset")


OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("kldnk-stopwatch", "en-US")

class StopwatchSource
{
private:
    obs_source_t *m_source;
    const IStopwatch& m_stopwatch;
    obs_hotkey_id m_hk_enable;
    obs_hotkey_id m_hk_reset;

public:
    StopwatchSource(const IStopwatch& stopwatch) : m_stopwatch(stopwatch) {};
    ~StopwatchSource() {};
};


static const char *stopwatch_source_get_name(void *type_data)
{
    return T_NAME;
}


static void *stopwatch_source_create(obs_data_t *settings, obs_source_t *source)
{
    const IStopwatch& stopwatch = Stopwatch(0);
    return (void*)new StopwatchSource(stopwatch);
}


static void stopwatch_source_destroy(void *data)
{
    delete reinterpret_cast<StopwatchSource*>(data);
}


static void stopwatch_source_update(void *data, obs_data_t *settings)
{
}


static uint32_t stopwatch_source_getwidth(void *data)
{
}


static uint32_t stopwatch_source_getheight(void *data)
{
}


static void stopwatch_source_render(void *data, gs_effect_t *effect)
{
}


static void stopwatch_source_tick(void *data, float seconds)
{
}


static void stopwatch_source_defaults(obs_data_t *settings)
{
}


static obs_properties_t *stopwatch_source_properties(void *data)
{
}


void enum_active_sources(void *data, obs_source_enum_proc_t enum_callback, void *param)
{
}


bool obs_module_load(void)
{
    struct obs_source_info si = {};
    si.id = "kldnk_stopwatch_source";
    si.type = OBS_SOURCE_TYPE_INPUT;
    si.output_flags = OBS_SOURCE_VIDEO;
    si.get_name = stopwatch_source_get_name;
    si.create = stopwatch_source_create;
    si.destroy = stopwatch_source_destroy;
    si.update = stopwatch_source_update;
    si.get_width = stopwatch_source_getwidth;
    si.get_height = stopwatch_source_getheight;
    si.video_render = stopwatch_source_render;
    si.video_tick = stopwatch_source_tick;
    si.get_defaults = stopwatch_source_defaults;
    si.get_properties = stopwatch_source_properties;
    si.enum_active_sources = enum_active_sources;

    obs_register_source(&si);
    return true;
}


void obs_module_unload(void)
{
}
