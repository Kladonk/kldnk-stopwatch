typedef struct stopwatch_source {
    obs_source_t *source;
    obs_source_t *textSource;
    long time_elapsed;
    long total_time_elapsed;
    bool enabled;
    obs_hotkey_id enable_hotkey_id;
    obs_hotkey_id reset_hotkey_id;
} stopwatch_source_t;

typedef struct time_info {
	uint32_t hours;
	uint32_t minutes;
	uint32_t seconds;
	uint32_t millis;
} time_info_t;

static const char *stopwatch_source_get_name(void *type_data);
static void *stopwatch_source_create(obs_data_t *settings, obs_source_t *source);
static void stopwatch_source_destroy(void *data);
static void stopwatch_source_update(void *data, obs_data_t *settings);
static uint32_t stopwatch_source_getwidth(void *data);
static uint32_t stopwatch_source_getheight(void *data);
static void stopwatch_source_render(void *data, gs_effect_t *effect);
static void stopwatch_source_tick(void *data, float seconds);
static obs_properties_t *stopwatch_source_properties(void *data);
void enum_active_sources(void *data, obs_source_enum_proc_t enum_callback, void *param);

static bool is_property_visible(obs_property_t *prop);
static void update_stopwatch_text(stopwatch_source_t *stopwatch);
static time_info_t *get_time_info(uint32_t millis);

static void init_stopwatch_hotkeys(stopwatch_source_t *source);
static void stopwatch_enable_hotkey_pressed(void *data, obs_hotkey_id id, obs_hotkey_t *hotkey, bool pressed);
static void stopwatch_reset_hotkey_pressed(void *data, obs_hotkey_id id, obs_hotkey_t *hotkey, bool pressed);