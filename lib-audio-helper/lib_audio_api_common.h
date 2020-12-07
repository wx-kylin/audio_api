#ifndef LIB_AUDIO_API_COMMON_H
#define LIB_AUDIO_API_COMMON_H
#include <glib.h>
#include "lib_audio_api.h"
#include "lib_audio_ukui_api.h"

#define CFG_FILE_PATH "~/.config/audio_api_cfg"
int g_cfg_line_num;

struct module_cmd_info {
    int cmd;
    char cmd_des[128];
};

struct module_info {
    char module_name[AUDIO_API_MODULE_NAME_LEN];
    char module_start[32];
    char api[32];
    char dbus_service[32];
    char dbus_path[32];
    char dbus_interface[32];
    int dbus_connected;
    int cmd_exe;
    volatile int finished;
    int need_time;
    int exe_result;
    char res_des[128];
    GSList *list;
};

struct config_info {
    char id[8];
    char module_name[AUDIO_API_MODULE_NAME_LEN];
    char module_start[32];
    // void (*api)(int);
    // char dbus_path[128];
    // int need_time;
    int cmd;
    char cmd_des[128];
};

void audio_api_display_info(GSList  *list);
int audio_api_cmd_add(struct register_msg *msg);
int audio_api_cmd_execution(struct register_msg *msg);
int audio_api_module_info_init(void);
int audio_api_module_reg(struct module_register *mod_reg);
struct module_info *audio_api_get_module(char *mod);
int audio_api_get_module_info(char *file_path);

int audio_api_module_name_cmp(gconstpointer str1, gconstpointer str2);
int audio_api_cmd_cmp(gconstpointer str1, gconstpointer str2);
void audio_api_delete_module_info(void);
#endif