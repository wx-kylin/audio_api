#include <gio/gio.h>
#include <stdlib.h>
#include <stdio.h>
#include "lib_audio_api_common.h"

GDBusProxy *bproxy = NULL;
struct module_info *g_module_info = NULL;

int *pull_thread(void *arg)
{
    pthread_t newThid;
    newThid = pthread_self();
    // printf("this is a new thread,thread ID = %lu\n",newThid);
    system(g_module_info->module_start);
    exit(0);
}

void audio_api_pull_module(void)
{
    int iRet = 0;
    pthread_t thid;
    // printf("my thread,ID is %lu\n",pthread_self());
    iRet = pthread_create(&thid,NULL,(void *)pull_thread,NULL);
    if(iRet != 0)
    {
        printf("audio_api_pull_module thread creation failed\n");
        return;
    }
    // system(g_module_info->module_start);
}
void audio_api_cmd_exe_callback (GObject * gobj, GAsyncResult * res, gpointer user_data)
{
	g_printf ("\n audio_api_cmd_exe_callback\n ");

	GError *error;
	GVariant *result;
	int str;

	error = NULL;
	result = g_dbus_proxy_call_finish (bproxy, res, &error);
    g_object_unref(bproxy);
	g_variant_get (result, "(i)", &str);
	g_print ("audio_api_cmd_exe_callback result from Server %d\n", str);
    if (str == 0) {
        g_module_info->finished = 1;
    } else {
        printf("audio_api_cmd_exe_callback module not started yet, will start module first.\n");
        // 拉起应用
        audio_api_pull_module();
    }
}

void audio_api_exe_ukui_mod_cmd(char *mod)
{
    GDBusConnection *bcon = NULL;
    struct module_info *module_info = NULL;
    GError *error;
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

    bcon = g_bus_get_sync(G_BUS_TYPE_SESSION, NULL, NULL);
    bproxy = NULL;
    error = NULL;
    bproxy = g_dbus_proxy_new_for_bus_sync(G_BUS_TYPE_SESSION, G_DBUS_PROXY_FLAGS_NONE, NULL, module_info->dbus_service, \
        module_info->dbus_path, module_info->dbus_interface, NULL, &error);
    if (bproxy == NULL) {
        printf("audio_api_exe_ukui_mod_cmd will start module %s.\n", module_info->module_start);
        audio_api_pull_module();
        return ;
    }
    // printf("service: %s, path: %s, interface: %s.\n", module_info->dbus_service, \
    //     module_info->dbus_path, module_info->dbus_interface);
    // printf("api: %s, cmd: %d.\n", module_info->api, module_info->cmd_exe);

	g_dbus_proxy_call(bproxy, module_info->api, g_variant_new("(i)", module_info->cmd_exe), \
        G_DBUS_CALL_FLAGS_NONE, -1, NULL, (GAsyncReadyCallback) audio_api_cmd_exe_callback, NULL);
}