#include <obs-module.h>
#include <obs-internal.h>
#include "kldnk-stopwatch.h"

#define TEXT_STOPWATCH_SOURCE_NAME          obs_module_text("StopwatchSource")
#define TEXT_STOPWATCH_ENABLE_HOTKEY_NAME   obs_module_text("Hotkey.Enable.Name")
#define TEXT_STOPWATCH_ENABLE_HOTKEY_DESC   obs_module_text("Hotkey.Enable.Desc")
#define TEXT_STOPWATCH_RESET_HOTKEY_NAME    obs_module_text("Hotkey.Reset.Name")
#define TEXT_STOPWATCH_RESET_HOTKEY_DESC    obs_module_text("Hotkey.Reset.Desc")

#define TEXT_SOURCE_ID                      "text_ft2_source\0"

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("kldnk-stopwatch", "en-US")

static struct obs_source_info stopwatch_source_info = {
        .id             = "kldnk_stopwatch_source",
        .type           = OBS_SOURCE_TYPE_INPUT,
        .output_flags   = OBS_SOURCE_VIDEO,
        .get_name       = stopwatch_source_get_name,
        .create         = stopwatch_source_create,
        .destroy        = stopwatch_source_destroy,
        .update         = stopwatch_source_update,
        .get_width      = stopwatch_source_getwidth,
        .get_height     = stopwatch_source_getheight,
        .video_render   = stopwatch_source_render,
        .video_tick     = stopwatch_source_tick,
        .get_properties = stopwatch_source_properties,
        .enum_active_sources = enum_active_sources
};

static const char *stopwatch_source_get_name(void *type_data)
{
    UNUSED_PARAMETER(type_data);
    return TEXT_STOPWATCH_SOURCE_NAME;
}

static void *stopwatch_source_create(obs_data_t *settings, obs_source_t *source)
{
    struct stopwatch_source *stopwatch = bzalloc(sizeof(stopwatch_source_t));
    stopwatch->source = source;
    stopwatch->textSource = obs_source_create(TEXT_SOURCE_ID, TEXT_SOURCE_ID, settings, NULL);
    stopwatch->time_elapsed = 0;
    stopwatch->total_time_elapsed = 0;
    stopwatch->enabled = false;

    obs_source_add_active_child(stopwatch->source, stopwatch->textSource);

    update_stopwatch_text(stopwatch);

    init_stopwatch_hotkeys(stopwatch);

    return stopwatch;
}

static void init_stopwatch_hotkeys(stopwatch_source_t *stopwatch)
{
    obs_source_t *source = stopwatch->source;
    stopwatch->enable_hotkey_id = obs_hotkey_register_source(source,
            "kldnk-stopwatch.toggle", TEXT_STOPWATCH_ENABLE_HOTKEY_NAME,
            stopwatch_enable_hotkey_pressed, stopwatch);

    stopwatch->reset_hotkey_id = obs_hotkey_register_source(source,
            "kldnk-stopwatch.reset", TEXT_STOPWATCH_RESET_HOTKEY_NAME  ,
            stopwatch_reset_hotkey_pressed, stopwatch);
}

static void stopwatch_enable_hotkey_pressed(void *data, obs_hotkey_id id, obs_hotkey_t *hotkey, bool pressed)
{
    stopwatch_source_t *stopwatch = data;
    if (pressed && stopwatch)
    {
        stopwatch->enabled = !stopwatch->enabled;
    }

    UNUSED_PARAMETER(id);
    UNUSED_PARAMETER(hotkey);
}

static void stopwatch_reset_hotkey_pressed(void *data, obs_hotkey_id id, obs_hotkey_t *hotkey, bool pressed)
{
    stopwatch_source_t *stopwatch = data;
    if (pressed && stopwatch && !stopwatch->enabled)
    {
        stopwatch->total_time_elapsed = 0;
        stopwatch->time_elapsed = 0;

        update_stopwatch_text(stopwatch);
    }

    UNUSED_PARAMETER(id);
    UNUSED_PARAMETER(hotkey);
}

static void stopwatch_source_destroy(void *data)
{
    stopwatch_source_t *stopwatch = data;

    // Unregister hotkeys
    obs_hotkey_unregister(stopwatch->enable_hotkey_id);
    obs_hotkey_unregister(stopwatch->reset_hotkey_id);

    // Release textSource
    obs_source_remove(stopwatch->textSource);
    obs_source_release(stopwatch->textSource);
    stopwatch->textSource = NULL;

    bfree(stopwatch);
}

static void stopwatch_source_update(void *data, obs_data_t *settings)
{
    stopwatch_source_t *stopwatch = data;

    update_stopwatch_text(stopwatch);

    UNUSED_PARAMETER(settings);
}

static uint32_t stopwatch_source_getwidth(void *data)
{
    stopwatch_source_t *stopwatch = data;
    return obs_source_get_width(stopwatch->textSource);
}

static uint32_t stopwatch_source_getheight(void *data)
{
    stopwatch_source_t *stopwatch = data;
    return obs_source_get_height(stopwatch->textSource);
}

static void stopwatch_source_render(void *data, gs_effect_t *effect)
{
    stopwatch_source_t *stopwatch = data;
    obs_source_video_render(stopwatch->textSource);

    UNUSED_PARAMETER(effect);
}

static void stopwatch_source_tick(void *data, float seconds)
{
    stopwatch_source_t *stopwatch = data;

    if (stopwatch->enabled)
    {
        uint32_t millis = seconds * 1000;
        stopwatch->total_time_elapsed += millis;
        stopwatch->time_elapsed += millis;

        if (stopwatch->time_elapsed >= 1) // Update every 100 milliseconds
        {
            stopwatch->time_elapsed = 0;
            update_stopwatch_text(stopwatch);
        }
    }
}

static void update_stopwatch_text(stopwatch_source_t *stopwatch)
{
    time_info_t *ti = get_time_info(stopwatch->total_time_elapsed);

    char text[9]; // hh:mm:ss\0
    snprintf(text, sizeof(text), "%02d:%02d:%02d", ti->hours, ti->minutes, ti->seconds);
    bfree(ti);

    obs_data_set_string(stopwatch->textSource->context.settings, "text", text);
    obs_source_update(stopwatch->textSource, stopwatch->textSource->context.settings);
}

static obs_properties_t *stopwatch_source_properties(void *data)
{
	stopwatch_source_t *stopwatch = data;

	obs_properties_t *props = obs_source_properties(stopwatch->textSource);
    obs_property_t *prop = obs_properties_first(props);
    while (prop)
    {
        if (!is_property_visible(prop))
        {
            obs_property_set_visible(prop, false);
        }
        obs_property_next(&prop);
    }
	return props;
}

static bool is_property_visible(obs_property_t *prop)
{
    const char *name = obs_property_name(prop);
    return
        strcmp(name, "font") == 0 ||
        strcmp(name, "color1") == 0 ||
        strcmp(name, "color2") == 0 ||
        strcmp(name, "outline") == 0 ||
        strcmp(name, "drop_shadow") == 0 ||
        strcmp(name, "custom_width") == 0;
}

void enum_active_sources(void *data, obs_source_enum_proc_t enum_callback, void *param)
{
    struct stopwatch_source *context = data;
    enum_callback(context->source, context->textSource, param);
}

static time_info_t *get_time_info(uint32_t millis)
{
    time_info_t *time_info = bzalloc(sizeof(time_info_t));
    time_info->millis = millis % 1000;
    millis /= 1000;
    time_info->seconds = millis % 60;
    millis /= 60;
    time_info->minutes = millis % 60;
    millis /= 60;
    time_info->hours = millis % 60;
    millis /= 60;
    return time_info;
}

bool obs_module_load(void)
{
    obs_register_source(&stopwatch_source_info);
    return true;
}