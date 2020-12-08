#ifndef LIB_AUDIO_API_H
#define LIB_AUDIO_API_H

#define AUDIO_API_OK 0
#define AUDIO_API_INPUT_PARAM_ERROR -1
#define AUDIO_API_MODULE_NAME_NOT_SUPPORT -2
#define AUDIO_API_FAIL_OPEN_CONFIG_FILE -3
#define AUDIO_API_CMD_EXIST -4
#define AUDIO_API_DBUS_METHOD_NOT_SUPPORT -5
#define AUDIO_API_CMD_NOT_SUPPORT -6
#define AUDIO_API_CMD_EXE_TIMEOUT -7
#define AUDIO_API_MODULE_NAME_LEN 32
#define AUDIO_API_CMD_LEN 128

void audio_api_get_verison_info(void);
int audio_api_read_module_info(char *file_path);
int audio_api_cmd_execute(char *mod, int cmd);
void audio_api_show_cmds(void);
int audio_api_init(char *cfg_file);
void audio_api_uninit(void);

#endif