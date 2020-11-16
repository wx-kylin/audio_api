#include <gio/gio.h>
#include <stdio.h>
#include "lib_audio_api.h"

#define AUDIO_API_SCHEMA                               "org.ukui.audio_api"

int audio_api_gsetting_init(void)
{
    gboolean init;
    GSettings *settings = g_settings_new(AUDIO_API_SCHEMA);

    init = g_settings_get_boolean(settings, "init");
    g_settings_set_boolean (settings, "init", !init);
    init = g_settings_get_boolean(settings, "init");
    return AUDIO_API_OK;
}