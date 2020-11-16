#include <gio/gio.h>
#include <stdio.h>
#include <string.h>
#include "lib_audio_api.h"
#include "audio_helper_common.h"

int main(int argc, char *argv[]) {
    // struct register_msg msg;
    GMainLoop *loop;

    audio_helper_version();
    audio_api_get_verison_info();
    (void)audio_api_init();

    loop = g_main_loop_new (NULL, FALSE);
	g_main_loop_run(loop);

    // // add ukui-control-centor cmd
    // strcpy(msg.module_name, "ukui-control-center");
    // strcpy(msg.cmd, "new_cmd");
    // audio_api_cmd_register(&msg);
    // audio_api_show_cmds();

    // // add other cmd
    // strcpy(msg.module_name, "ukui-control");
    // strcpy(msg.cmd, "new_cmd");
    // audio_api_cmd_register(&msg);
    // audio_api_show_cmds();

    // //exec cmd
    // strcpy(msg.module_name, "ukui-control-center");
    // strcpy(msg.cmd, "ukui-control-center -u");
    // audio_api_exec_cmd(&msg);

    return 0;
}
