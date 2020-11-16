#include <gio/gio.h>
// #include <glib.h>
#include <stdlib.h>
#include <stdio.h>
#include "lib_audio_ukui_api.h"

static GDBusNodeInfo *introspection_data = NULL;

/* Introspection data for the service we are exporting */
static const gchar introspection_xml[] =
	"<node>"
        "<interface name='org.ukui.audio_api'>"
            "<method name='module_register'>"
                "<arg type='(sssi)' name='reg_info' direction='in'/>"
				"<arg name='result' type='s' direction='out'/>"
            "</method>"
            "<method name='cmd_register'>"
                "<arg type='(sis)' name='cmd_info' direction='in'/>"
				"<arg name='result' type='s' direction='out'/>"
            "</method>"
			"<method name='cmd_execute_result'>"
                "<arg type='(sis)' name='execute_result' direction='in'/>"
				"<arg name='result' type='s' direction='out'/>"
            "</method>"
        "</interface>"
    "</node>";

int module_register_process(GVariant * parameters)
{
	// struct module_register *reg_info;
	char *name, *api, *dbus;
	int need_t;

	g_variant_get (parameters, "((sssi))", &name, &api, &dbus, &need_t);
	printf("module_register info, name = %s, api = %s, dbus = %s, need_t = %d.\n", \
		name, start, api, dbus, need_t);
	return 0;
}

int cmd_register_process(GVariant * parameters)
{
	char *name, *cmd_des;
	int cmd;

	g_variant_get (parameters, "((sis))", &name, &cmd, &cmd_des);
	printf("cmd_register info, name = %s, cmd = %d, cmd_des = %s.\n", name, cmd, cmd_des);
	return 0;
}

int cmd_exe_result(GVariant * parameters)
{
	char *name, *err_des;
	int result;

	g_variant_get (parameters, "((sis))", &name, &result, &err_des);
	printf("cmd_register info, name = %s, result = %d, err_des = %s.\n", name, result, err_des);
	return 0;
}

static void
handle_method_call (GDBusConnection * connection,
	const gchar * sender, const gchar * object_path, const gchar * interface_name, const gchar * method_name, GVariant * parameters, GDBusMethodInvocation * invocation, gpointer user_data)
{
	g_printf ("Inside Handle Method Call \n");
	int ret;

	if (g_strcmp0 (method_name, "module_register") == 0) {
		ret = module_register_process(parameters);
	} else if (g_strcmp0 (method_name, "cmd_register") == 0) {
        ret = cmd_register_process(parameters);
    } else if (g_strcmp0 (method_name, "cmd_execute_result") == 0) {
        ret = cmd_exe_result(parameters);
    } else {
		ret = -1;
        printf("do not support this method.\n");
    }
	if (ret == 0) {
		g_dbus_method_invocation_return_value (invocation, g_variant_new ("(s)", "ok"));
	} else {
		g_dbus_method_invocation_return_value (invocation, g_variant_new ("(s)", "error"));
	}
}

static const GDBusInterfaceVTable interface_vtable = {
	handle_method_call,
	NULL,
	NULL
};

static void on_bus_acquired (GDBusConnection * connection, const gchar * name, gpointer user_data)
{
	g_print("\n Inside on_bus_acquired \n");

	guint registration_id;

	registration_id = g_dbus_connection_register_object (connection, "/org/ukui/audio_api", introspection_data->interfaces[0], &interface_vtable, NULL,	/* user_data */
		NULL,					/* user_data_free_func */
		NULL);					/* GError** */
	g_assert(registration_id > 0);

}

static void on_name_acquired (GDBusConnection * connection, const gchar * name, gpointer user_data)
{
    g_print("\n Inside on_name_acquired \n");
}

static void on_name_lost (GDBusConnection * connection, const gchar * name, gpointer user_data)
{
    g_print("\n Inside on_name_lost \n");
	exit (1);
}

int main (int argc, char **argv)
{
	guint owner_id;
	GMainLoop *loop;
	// g_type_init();
	introspection_data = g_dbus_node_info_new_for_xml (introspection_xml, NULL);
	g_assert(introspection_data != NULL);

	owner_id = g_bus_own_name (G_BUS_TYPE_SESSION, "org.ukui.audio_api", G_BUS_NAME_OWNER_FLAGS_NONE, on_bus_acquired, on_name_acquired, on_name_lost, NULL, NULL);

	g_print ("\n Owner id is %d.\n", owner_id);
	loop = g_main_loop_new (NULL, FALSE);
	g_main_loop_run (loop);

	g_bus_unown_name (owner_id);

	g_dbus_node_info_unref (introspection_data);

}