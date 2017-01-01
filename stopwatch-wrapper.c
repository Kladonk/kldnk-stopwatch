#include "stopwatch-wrapper.h"
#include "stopwatch-settings.h"
#include "stopwatch-type.h"
#include "time-util.h"
#include <obs-module.h>
#include <obs-internal.h>


/**
 * The ID of the text_ft2_source to instantiate the sub-source
 */
#define TEXT_SOURCE_ID                          "text_ft2_source\0"

/**
 * Update the stopwatch every X milliseconds
 */
 #define UPDATE_AFTER_MILLIS                    15

/*
 * Define hotkeys
 */
#define HOTKEY_STOPWATCH_TOGGLE                 "kldnk_stopwatch_toggle"
#define HOTKEY_STOPWATCH_RESET                  "kldnk_stopwatch_reset"


/*
 * Define texts
 */
#define TEXT_STOPWATCH_SOURCE_NAME              obs_module_text("StopwatchSource")
#define TEXT_STOPWATCH_TYPE                     obs_module_text("Stopwatch.Type")
#define TEXT_STOPWATCH_TYPE_COUNTUP             obs_module_text("Stopwatch.Type.Countup")
#define TEXT_STOPWATCH_TYPE_COUNTDOWN           obs_module_text("Stopwatch.Type.Countdown")
#define TEXT_STOPWATCH_COUNTUP_ENDVALUE         obs_module_text("Stopwatch.Countup.EndValue")
#define TEXT_STOPWATCH_COUNTDOWN_INITIALVALUE   obs_module_text("Stopwatch.Countdown.InitialValue")
#define TEXT_STOPWATCH_ENABLE_HOTKEY_NAME       obs_module_text("Hotkey.Enable.Name")
#define TEXT_STOPWATCH_RESET_HOTKEY_NAME        obs_module_text("Hotkey.Reset.Name")


/**
 * The stopwatch source structure
 */
struct stopwatch_source {
	obs_source_t *source;
	obs_source_t *textSource;
	stopwatch_type type;
	int64_t time_elapsed;
	int64_t total_time_elapsed;
	int64_t initial_value;
	int64_t end_value;
	bool enabled;
	bool finished;
	obs_hotkey_id enable_hotkey_id;
	obs_hotkey_id reset_hotkey_id;
};


/*
 * Declare some helpers and callbacks
 */
static void update_stopwatch_text(stopwatch_source_t *stopwatch);
static void init_stopwatch_hotkeys(stopwatch_source_t *stopwatch);
static void stopwatch_enable_hotkey_pressed(void *data, obs_hotkey_id id, obs_hotkey_t *hotkey, bool pressed);
static void stopwatch_reset_hotkey_pressed(void *data, obs_hotkey_id id, obs_hotkey_t *hotkey, bool pressed);
static bool stopwatch_type_changed(obs_properties_t *props, obs_property_t *property, obs_data_t *settings);
static void set_property_visibility(obs_properties_t *props, const char *name, bool visible);


/*
 * Stopwatch control functions
 */
void start(stopwatch_source_t *stopwatch)
{
	stopwatch->enabled = true;
}


void stop(stopwatch_source_t *stopwatch)
{
	stopwatch->enabled = false;
}


bool check_if_finished(stopwatch_source_t *stopwatch)
{
	return ((stopwatch->type == STOPWATCH_TYPE_COUNTUP) &&
		(stopwatch->total_time_elapsed >= stopwatch->end_value)) ||
		((stopwatch->type == STOPWATCH_TYPE_COUNTDOWN) &&
		(stopwatch->initial_value - stopwatch->total_time_elapsed <= 0));
}


void update(stopwatch_source_t *stopwatch, float seconds)
{
	if (is_enabled(stopwatch) && !is_finished(stopwatch))
	{
		int64_t millis = seconds * 1000;
		stopwatch->total_time_elapsed += millis;

		if (check_if_finished(stopwatch))
		{
			stopwatch->finished = true;
			stopwatch->total_time_elapsed = stopwatch->type == STOPWATCH_TYPE_COUNTUP ? stopwatch->end_value : 0; // Cap to end value
		}
	}
}


bool is_enabled(stopwatch_source_t *stopwatch)
{
	return stopwatch->enabled;
}


bool is_finished(stopwatch_source_t *stopwatch)
{
	return stopwatch->finished;
}


void reset(stopwatch_source_t *stopwatch)
{
	stopwatch->enabled = false;
	stopwatch->finished = false;
	stopwatch->total_time_elapsed = 0;
}


/*
 * Plugin implementation
 */
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
	stopwatch->type = settings_get_type(settings);
	stopwatch->initial_value = settings_get_initial_value_as_int(settings);
	stopwatch->end_value = settings_get_end_value_as_int(settings);
	reset(stopwatch);

	obs_source_add_active_child(stopwatch->source, stopwatch->textSource);

	init_stopwatch_hotkeys(stopwatch);

	update_stopwatch_text(stopwatch);

	return stopwatch;
}


static void init_stopwatch_hotkeys(stopwatch_source_t *stopwatch)
{
	obs_source_t *source = stopwatch->source;
	stopwatch->enable_hotkey_id = obs_hotkey_register_source(source,
			HOTKEY_STOPWATCH_TOGGLE, TEXT_STOPWATCH_ENABLE_HOTKEY_NAME,
			stopwatch_enable_hotkey_pressed, stopwatch);

	stopwatch->reset_hotkey_id = obs_hotkey_register_source(source,
			HOTKEY_STOPWATCH_RESET, TEXT_STOPWATCH_RESET_HOTKEY_NAME,
			stopwatch_reset_hotkey_pressed, stopwatch);
}


static void stopwatch_enable_hotkey_pressed(void *data, obs_hotkey_id id, obs_hotkey_t *hotkey, bool pressed)
{
	stopwatch_source_t *stopwatch = data;
	if (pressed && stopwatch)
	{
		if (is_enabled(stopwatch))
		{
			stop(stopwatch);
		}
		else
		{
			start(stopwatch);
		}
	}

	UNUSED_PARAMETER(id);
	UNUSED_PARAMETER(hotkey);
}


static void stopwatch_reset_hotkey_pressed(void *data, obs_hotkey_id id, obs_hotkey_t *hotkey, bool pressed)
{
	stopwatch_source_t *stopwatch = data;
	if (pressed && stopwatch && (!is_enabled(stopwatch) || is_finished(stopwatch)))
	{
		reset(stopwatch);
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

	// Check if stopwatch type has changed
	stopwatch_type new_stopwatch_type = settings_get_type(settings);
	if (stopwatch->type != new_stopwatch_type)
	{
		stopwatch->type = new_stopwatch_type;
		reset(stopwatch);
	}

	// Check if end value has changed
	int64_t new_end_value = settings_get_end_value_as_int(settings);
	if (stopwatch->end_value != new_end_value)
	{
		stopwatch->end_value = new_end_value;
	}

	// Check if initial value has changed
	int64_t new_initial_value = settings_get_initial_value_as_int(settings);
	if (stopwatch->initial_value != new_initial_value)
	{
		stopwatch->initial_value = new_initial_value;
	}

	update_stopwatch_text(stopwatch);
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

	stopwatch->time_elapsed += seconds * 1000;

	if (is_enabled(stopwatch) || is_finished(stopwatch))
	{
		update(stopwatch, seconds);

		if (stopwatch->time_elapsed >= UPDATE_AFTER_MILLIS)
		{
			stopwatch->time_elapsed = 0;
			update_stopwatch_text(stopwatch);
		}
	}
}


static void update_stopwatch_text(stopwatch_source_t *stopwatch)
{
	int64_t time = 0;
	if (stopwatch->type == STOPWATCH_TYPE_COUNTUP)
	{
		time = stopwatch->total_time_elapsed;
	}
	else if (stopwatch->type == STOPWATCH_TYPE_COUNTDOWN)
	{
		time = stopwatch->initial_value - stopwatch->total_time_elapsed;
	}

	const char *time_string = millis_to_string(time);
	obs_data_set_string(stopwatch->textSource->context.settings, "text", time_string);
	obs_source_update(stopwatch->textSource, stopwatch->textSource->context.settings);
}


static void stopwatch_source_defaults(obs_data_t *settings)
{
	obs_data_set_default_bool(settings, "unload", false);
	obs_data_set_default_string(settings, SETTING_TYPE, SETTING_TYPE_COUNTUP);
}


static obs_properties_t *stopwatch_source_properties(void *data)
{
	stopwatch_source_t *stopwatch = data;

	// Add text source properties and set visibility 
	obs_properties_t *props = obs_source_properties(stopwatch->textSource);
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
	prop = obs_properties_add_list(props, SETTING_TYPE, TEXT_STOPWATCH_TYPE, OBS_COMBO_TYPE_LIST, OBS_COMBO_FORMAT_STRING);
	obs_property_list_add_string(prop, TEXT_STOPWATCH_TYPE_COUNTUP, SETTING_TYPE_COUNTUP);
	obs_property_list_add_string(prop, TEXT_STOPWATCH_TYPE_COUNTDOWN, SETTING_TYPE_COUNTDOWN);
	obs_property_set_modified_callback(prop, stopwatch_type_changed);

	prop = obs_properties_add_text(props, SETTING_COUNTUP_ENDVALUE, TEXT_STOPWATCH_COUNTUP_ENDVALUE, OBS_TEXT_DEFAULT);
	obs_property_set_visible(prop, true);

	prop = obs_properties_add_text(props, SETTING_COUNTDOWN_INITIALVALUE, TEXT_STOPWATCH_COUNTDOWN_INITIALVALUE, OBS_TEXT_DEFAULT);
	obs_property_set_visible(prop, false);

	return props;
}


static bool stopwatch_type_changed(obs_properties_t *props, obs_property_t *property, obs_data_t *settings)
{
	stopwatch_type type = settings_get_type(settings);
	set_property_visibility(props, SETTING_COUNTUP_ENDVALUE, type == STOPWATCH_TYPE_COUNTUP);
	set_property_visibility(props, SETTING_COUNTDOWN_INITIALVALUE, type == STOPWATCH_TYPE_COUNTDOWN);

	UNUSED_PARAMETER(property);
	return true;
}


static void set_property_visibility(obs_properties_t *props, const char *name, bool visible)
{
	obs_property_t *prop = obs_properties_get(props, name);
	obs_property_set_visible(prop, visible);
}


void enum_active_sources(void *data, obs_source_enum_proc_t enum_callback, void *param)
{
	struct stopwatch_source *context = data;
	enum_callback(context->source, context->textSource, param);
}


struct obs_source_info stopwatch_source_info = {
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
		.get_defaults   = stopwatch_source_defaults,
		.get_properties = stopwatch_source_properties,
		.enum_active_sources = enum_active_sources
};