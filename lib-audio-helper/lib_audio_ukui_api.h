#ifndef LIB_AUDIO_UKUI_API_H
#define LIB_AUDIO_UKUI_API_H

#define AUDIO_API_MODULE_NAME_LEN 32

struct module_register {
    char module_name[AUDIO_API_MODULE_NAME_LEN];
    char api[32];
    char dbus_service[32];
    char dbus_path[32];
    char dbus_interface[32];
    int need_time;
};

struct cmd_register {
    char module_name[AUDIO_API_MODULE_NAME_LEN];
    int cmd;
    char cmd_des[128];
};

struct module_cmd_execute_result {
    char module_name[AUDIO_API_MODULE_NAME_LEN];
    int result;
    char err_des[128];
};
int audio_api_module_register(struct module_register *mod_reg);

#endif