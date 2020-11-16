#ifndef LIB_AUDIO_API_H
#define LIB_AUDIO_API_H

#define AUDIO_API_OK 0
#define AUDIO_API_INPUT_PARAM_ERROR -1
#define AUDIO_API_MODULE_NAME_NOT_SUPPORT -2
#define AUDIO_API_MODULE_NAME_LEN 32
#define AUDIO_API_CMD_LEN 128

void audio_api_get_verison_info(void);
int audio_api_cmd_register(struct register_msg *msg);
int audio_api_exec_cmd(struct register_msg *msg);
void audio_api_show_cmds(void);
int audio_api_init(void);

#endif