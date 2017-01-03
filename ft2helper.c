#include <obs-internal.h>

void update_ft2_text(obs_source_t *textSource, const char *text)
{
	obs_data_set_string(textSource->context.settings, "text", text);
	obs_source_update(textSource, textSource->context.settings);
}
