#include <gio/gio.h>
#include <stdio.h>
#include <stdlib.h>
#include "lib_audio_ukui_api.h"

GDBusProxy *bproxy;
GMainLoop * g_main_loop;

void mycallback (GObject * gobj, GAsyncResult * res, gpointer user_data)
{
	g_printf ("\n Inside mycallback\n ");

	GError *error;
	GVariant *result;
	int str;

	error = NULL;
	result = g_dbus_proxy_call_finish (bproxy, res, &error);
	g_variant_get (result, "(i)", &str);
	g_print ("String from Server %d\n", str);
	g_main_loop_quit(g_main_loop);
	exit(0);
}

int main (int argc, char **argv)
{
	GDBusConnection *bcon;
	GMainLoop *loop;
	struct module_register *mod_reg;
	// GVariant *tmp;

	mod_reg = (struct module_register *)malloc(sizeof(struct module_register));
	strcpy(mod_reg->module_name, "temp");
	strcpy(mod_reg->api, "api2");
	strcpy(mod_reg->dbus_path, "/a/b/c/d");
	mod_reg->need_time = 1;

	printf("------1-------------\n");
	bcon = g_bus_get_sync (G_BUS_TYPE_SESSION, NULL, NULL);
	// bproxy = g_dbus_proxy_new_sync (bcon, G_DBUS_PROXY_FLAGS_NONE, NULL, "org.ukui.audio_api", "/org/ukui/audio_api", "org.ukui.audio_api", NULL, NULL);
	bproxy = g_dbus_proxy_new_sync (bcon, G_DBUS_PROXY_FLAGS_NONE, NULL, "org.ukui.module", "/org/ukui/module", "local.ukui_demo.MainWindow", NULL, NULL);
	printf("------2-------------\n");
	// g_dbus_proxy_call (bproxy, "module_register", g_variant_new("((sssi))", \
	// 	"ukui-control-centor", mod_reg->api, mod_reg->dbus_path, mod_reg->need_time), \
	// 	G_DBUS_CALL_FLAGS_NONE, -1, NULL, (GAsyncReadyCallback) mycallback, NULL);

	// g_dbus_proxy_call (bproxy, "cmd_register", g_variant_new("((sis))", \
		"ukui-control-centor", 4, "cmd4"), G_DBUS_CALL_FLAGS_NONE, -1, NULL, (GAsyncReadyCallback) mycallback, NULL);
	g_dbus_proxy_call(bproxy, "ukui_module_exe_cmd_api", g_variant_new("(i)", 1), \
         G_DBUS_CALL_FLAGS_NONE, -1, NULL, (GAsyncReadyCallback) mycallback, NULL);
	// g_dbus_proxy_call (bproxy, "cmd_execute_result", g_variant_new("((sis))", \
	// 	"temp", 0, "ok"), G_DBUS_CALL_FLAGS_NONE, -1, NULL, (GAsyncReadyCallback) mycallback, NULL);
	printf("------3-------------\n");
	g_main_loop = g_main_loop_new(NULL, FALSE);
	g_main_loop_run(g_main_loop);
	return 0;
}