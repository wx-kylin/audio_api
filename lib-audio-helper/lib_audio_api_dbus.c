#include <gio/gio.h>
#include <stdlib.h>
#include <stdio.h>
#include "lib_audio_ukui_api.h"
#include "lib_audio_api_common.h"
#include "lib_audio_api_gsetting.h"
#include "lib_audio_api_dbus_client.h"

static GDBusNodeInfo *introspection_data = NULL;
extern struct module_info *g_module_info;

/* Introspection data for the service we are exporting */
static const gchar introspection_xml[] =
	"<node>"
        "<interface name='org.ukui.audio_api'>"
            "<method name='module_register'>"
                // "<arg type='(sssi)' name='reg_info' direction='in'/>"
				"<arg type='s' name='name' direction='in'/>"
				"<arg type='s' name='api' direction='in'/>"
				"<arg type='s' name='dbus_service' direction='in'/>"
				"<arg type='s' name='dbus_path' direction='in'/>"
				"<arg type='s' name='dbus_interface' direction='in'/>"
				"<arg type='i' name='need_time' direction='in'/>"
				"<arg name='result' type='i' direction='out'/>"
            "</method>"
            "<method name='cmd_register'>"
                // "<arg type='(sis)' name='cmd_info' direction='in'/>"
				"<arg type='s' name='name' direction='in'/>"
				"<arg type='i' name='cmd' direction='in'/>"
				"<arg type='s' name='cmd_des' direction='in'/>"
				"<arg name='result' type='i' direction='out'/>"
            "</method>"
			"<method name='cmd_execute_result'>"
                // "<arg type='(sis)' name='execute_result' direction='in'/>"
				"<arg type='s' name='name' direction='in'/>"
				"<arg type='i' name='cmd' direction='in'/>"
				"<arg type='s' name='result' direction='in'/>"
				"<arg name='result' type='i' direction='out'/>"
            "</method>"
			"<method name='mod_register_finish'>"
				"<arg type='s' name='name' direction='in'/>"
				"<arg name='result' type='i' direction='out'/>"
            "</method>"
        "</interface>"
    "</node>";

int module_register_finish_process(GVariant * parameters)
{
	// struct module_register *reg_info;
	char *name;
	struct module_info *module_info = NULL;

	// g_variant_get (parameters, "((sssssi))", &name, &api, &dbus, &need_t);
	g_variant_get (parameters, "(s)", &name);
	printf("module_register_finished, mod_name is %s.\n", name);

	audio_api_exe_ukui_mod_cmd(name);
	return 0;
}

int module_register_process(GVariant * parameters)
{
	// struct module_register *reg_info;
	char *name, *start, *api, *dbus_s, *dbus_p, *dbus_i;
	int need_t;
    struct module_register mod_reg;

	// g_variant_get (parameters, "((sssssi))", &name, &api, &dbus, &need_t);
	g_variant_get (parameters, "(sssssi)", &name, &api, &dbus_s, &dbus_p, &dbus_i, &need_t);
	printf("module_register info, name = %s, api = %s, dbus = %s, need_t = %d.\n", \
		name, api, dbus_s, need_t);
    strcpy(mod_reg.module_name, name);
    strcpy(mod_reg.api, api);
	strcpy(mod_reg.dbus_service, dbus_s);
	strcpy(mod_reg.dbus_path, dbus_p);
    strcpy(mod_reg.dbus_interface, dbus_i);
    mod_reg.need_time = need_t;
    audio_api_module_reg(&mod_reg);
	return 0;
}

int cmd_register_process(GVariant * parameters)
{
	char *name, *cmd_des;
	int cmd;
    struct cmd_register cmd_reg;

	// g_variant_get (parameters, "((sis))", &name, &cmd, &cmd_des);
	g_variant_get (parameters, "(sis)", &name, &cmd, &cmd_des);
	printf("cmd_register info, name = %s, cmd = %d, cmd_des = %s.\n", name, cmd, cmd_des);
    strcpy(cmd_reg.module_name, name);
    strcpy(cmd_reg.cmd_des, cmd_des);
    cmd_reg.cmd = cmd;
    audio_api_cmd_reg(&cmd_reg);
	return 0;
}

int cmd_exe_result(GVariant * parameters)
{
	char *name, *err_des;
	int result;

	// g_variant_get (parameters, "((sis))", &name, &result, &err_des);
	g_variant_get (parameters, "(sis)", &name, &result, &err_des);
	printf("cmd_exe_result, name = %s, result = %d, err_des = %s.\n", name, result, err_des);

	g_module_info->finished = 1;
	return 0;
}

static void handle_method_call (GDBusConnection * connection,
	const gchar * sender, const gchar * object_path, const gchar * interface_name,
    const gchar * method_name, GVariant * parameters, GDBusMethodInvocation * invocation, gpointer user_data)
{
	g_printf ("Inside Handle Method Call \n");
	int ret;

	if (g_strcmp0 (method_name, "module_register") == 0) {
		ret = module_register_process(parameters);
	} else if (g_strcmp0 (method_name, "cmd_register") == 0) {
        ret = cmd_register_process(parameters);
    } else if (g_strcmp0 (method_name, "cmd_execute_result") == 0) {
        ret = cmd_exe_result(parameters);
    } else if (g_strcmp0 (method_name, "mod_register_finish") == 0) {
        ret = module_register_finish_process(parameters);
    } else {
		ret = -1;
        printf("do not support this method.\n");
    }
	if (ret == 0) {
		g_dbus_method_invocation_return_value (invocation, g_variant_new ("(i)", 0));
	} else {
		g_dbus_method_invocation_return_value (invocation, g_variant_new ("(i)", 1));
	}
}

static const GDBusInterfaceVTable interface_vtable = {
	handle_method_call,
	NULL,
	NULL
};

static void on_bus_acquired (GDBusConnection * connection, const gchar * name, gpointer user_data)
{
	g_print("\nInside on_bus_acquired \n");

	guint registration_id;

	registration_id = g_dbus_connection_register_object (connection, "/org/ukui/audio_api", \
        introspection_data->interfaces[0], &interface_vtable, NULL,	/* user_data */
		NULL,					/* user_data_free_func */
		NULL);					/* GError** */
	g_assert(registration_id > 0);

}

static void on_name_acquired (GDBusConnection * connection, const gchar * name, gpointer user_data)
{
    g_print("\nInside on_name_acquired \n");
	audio_api_gsetting_init();
}

static void on_name_lost (GDBusConnection * connection, const gchar * name, gpointer user_data)
{
    g_print("\nInside on_name_lost \n");
	exit (1);
}

void audio_api_dbus_init(void)
{
	guint owner_id;
	introspection_data = g_dbus_node_info_new_for_xml (introspection_xml, NULL);
	g_assert(introspection_data != NULL);
	owner_id = g_bus_own_name (G_BUS_TYPE_SESSION, "org.ukui.audio_api", \
        G_BUS_NAME_OWNER_FLAGS_NONE, on_bus_acquired, on_name_acquired, on_name_lost, NULL, NULL);
	g_print ("\nDBus Owner id is %d.\n", owner_id);
}
