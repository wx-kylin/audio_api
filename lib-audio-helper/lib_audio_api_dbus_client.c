#include <gio/gio.h>
#include <stdlib.h>
#include <stdio.h>
#include "lib_audio_api_common.h"

GDBusProxy *bproxy = NULL;
struct module_info *g_module_info = NULL;

void audio_api_cmd_exe_callback (GObject * gobj, GAsyncResult * res, gpointer user_data)
{
	g_printf ("\n audio_api_cmd_exe_callback\n ");

	GError *error;
	GVariant *result;
	int str;

	error = NULL;
	result = g_dbus_proxy_call_finish (bproxy, res, &error);
	g_variant_get (result, "(i)", &str);
	g_print ("result from Server %d\n", str);
    if (str == 0) {
        g_module_info->finished = 1;
    } else {
        printf("module not started yet, will start module first.\n");
        // to do 拉起应用
    }

}

void audio_api_exe_ukui_mod_cmd(char *mod)
{
    GDBusConnection *bcon = NULL;
    struct module_info *module_info = NULL;

    // printf("mod is %s, cmd is %d.\n", mod, cmd);
    module_info = audio_api_get_module(mod);
    if(module_info == NULL) {
        printf("module not support, mod is %s.\n", mod);
        return;
    }
    g_module_info = module_info;
    if (module_info->finished == 1) {
        return;
    }
    printf("audio_api_exe_ukui_mod_cmd before dbus.\n");
    if (module_info->dbus_connected == 0) {
        bcon = g_bus_get_sync(G_BUS_TYPE_SESSION, NULL, NULL);
        bproxy = g_dbus_proxy_new_sync (bcon, G_DBUS_PROXY_FLAGS_NONE, NULL, module_info->dbus_service, \
            module_info->dbus_path, module_info->dbus_interface, NULL, NULL);
        printf("service: %s, path: %s, interface: %s.\n", module_info->dbus_service, \
            module_info->dbus_path, module_info->dbus_interface);
        printf("api: %s, cmd: %d.\n", module_info->api, module_info->cmd_exe);
        module_info->dbus_connected = 1;
    }
	g_dbus_proxy_call(bproxy, module_info->api, g_variant_new("(i)", module_info->cmd_exe), \
        G_DBUS_CALL_FLAGS_NONE, -1, NULL, (GAsyncReadyCallback) audio_api_cmd_exe_callback, NULL);
}