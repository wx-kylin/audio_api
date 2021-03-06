#include <stdio.h>
#include <stdlib.h>

#include "lib_audio_api.h"
#include "lib_audio_api_common.h"
#include "lib_audio_api_dbus.h"

extern GSList *g_module_list;
char g_cfg_file[128] = "\0";

void audio_api_get_verison_info(void)
{
    printf("lib_audio_api version is 1.0.\n");
}

void audio_api_show_cmds(void)
{
    audio_api_display_info(g_module_list);
}

int audio_api_read_module_info(char *file_path)
{
    return audio_api_get_module_info(file_path);
}

int audio_api_init(char *cfg_file)
{
    int ret = 0;
    g_cfg_line_num = 0;
    strcpy(g_cfg_file, cfg_file);
    ret = audio_api_module_info_init();
    if (ret) {
        return ret;
    }
    // 写gsettings放到dbus获得name之后，防止dbus还没有注册成功，ukui module就调用接口来注册，发生错误
    audio_api_dbus_init();
    return AUDIO_API_OK;
}

void audio_api_uninit(void)
{
    audio_api_delete_module_info();
}