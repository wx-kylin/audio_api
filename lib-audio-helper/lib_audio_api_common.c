#include <stdio.h>
#include <glib.h>
#include <gio/gio.h>
#include <string.h>
#include <pthread.h>
#include "lib_audio_api.h"
#include "lib_audio_api_common.h"
#include "lib_audio_api_dbus_client.h"

GSList *g_module_list = NULL;
extern struct module_info *g_module_info;

int audio_api_module_cmd_sup(char *mod, int cmd)
{
    struct module_info tmp_module_info;
    GSList *find = NULL;
    struct module_info *find_info = NULL;
    GSList *find_cmd = NULL;
    struct module_cmd_info tmp_cmd_info;

    strcpy(tmp_module_info.module_name, mod);
    find = g_slist_find_custom(g_module_list, &tmp_module_info, audio_api_module_name_cmp);
    if (find != NULL) {
        find_info = (struct module_info *)find->data;
        tmp_cmd_info.cmd = cmd;
        find_cmd = g_slist_find_custom(find_info->list, &tmp_cmd_info, audio_api_cmd_cmp);
        if (find_cmd != NULL) {
            return 1;
        }
    }
    return 0;
}

struct module_info *audio_api_get_module(char *mod)
{
    struct module_info tmp_module_info;
    GSList *find = NULL;

    strcpy(tmp_module_info.module_name, mod);
    find = g_slist_find_custom(g_module_list, &tmp_module_info, audio_api_module_name_cmp);
    if (find != NULL) {
        return (struct module_info *)find->data;
    }
    return NULL;
}

int audio_api_cmd_execute(char *mod, int cmd)
{
    struct module_info *module_info = NULL;
    // 最多等待5ms
    int count = 5;

    module_info = audio_api_get_module(mod);
    if (module_info == NULL) {
        printf("module not support, mod is %s.\n", mod);
        return AUDIO_API_MODULE_NAME_NOT_SUPPORT;
    }
    module_info->cmd_exe = cmd;
    module_info->finished = 0;
    if(!audio_api_module_cmd_sup(mod, module_info->cmd_exe)) {
        printf("cmd not support, cmd is %d.\n", module_info->cmd_exe);
        return AUDIO_API_CMD_NOT_SUPPORT;
    }
    printf("audio_api_cmd_execute.\n");
    audio_api_exe_ukui_mod_cmd(mod);
    while (module_info->finished == 0 && count--) {
        sleep(1);
    }
    if (module_info->finished == 0) {
        printf("audio_api_cmd_exe timeout.\n");
        return AUDIO_API_CMD_EXE_TIMEOUT;
    } else {
        if (g_module_info->exe_result != 0) {
            return g_module_info->exe_result;
        }
    }
    return AUDIO_API_OK;
}

void audio_api_display_info(GSList  *list) {
    GSList *iterator = NULL;
    GSList *iterator_in = NULL;
    struct module_info *info;
    struct module_cmd_info *cmd_info;
    int i = 0;
    printf("\n------------------audio_api_show_info start-----------------\n");
    for (iterator = list; iterator; iterator = iterator->next) {
        info = (struct module_info *)iterator->data;
        printf( "id: %d, module_name: %s, need_time: %d.\n", i, info->module_name, info->need_time);
        printf("api: %s, dbus_service: %s.\n", info->api, info->dbus_service);
        printf("dbus_path: %s, dbus_interface: %s.\n", info->dbus_path, info->dbus_interface);
        i++;
        for (iterator_in = info->list; iterator_in; iterator_in = iterator_in->next) {
            cmd_info = (struct module_cmd_info *)iterator_in->data;
            printf("cmd %d: %s\n", cmd_info->cmd, cmd_info->cmd_des);
        }
        printf("\n");
    }
    printf("------------------audio_api_show_info end-----------------\n\n");
}

int audio_api_get_module_info(char *file_path)
{
    GSList *iterator = NULL;
    GSList *iterator_in = NULL;
    struct module_info *info;
    struct module_cmd_info *cmd_info;
    int i = 0;
    FILE *fp;

    if((fp=fopen(file_path,"w"))==NULL) {
        printf("Can not open file\n");
        return AUDIO_API_FAIL_OPEN_CONFIG_FILE;
    }

    fprintf(fp, "%s\n", "------------------audio_api_show_info start-----------------");
    for (iterator = g_module_list; iterator; iterator = iterator->next) {
        info = (struct module_info *)iterator->data;
        fprintf(fp, "id: %d, module_name: %s, need_time: %d\n", i, info->module_name, info->need_time);
        fprintf(fp, "api: %s, dbus_service: %s\n", info->api, info->dbus_service);
        fprintf(fp, "api: %s, dbus_path: %s\n", info->api, info->dbus_path);
        fprintf(fp, "api: %s, dbus_interface: %s\n", info->api, info->dbus_interface);
        i++;
        for (iterator_in = info->list; iterator_in; iterator_in = iterator_in->next) {
            cmd_info = (struct module_cmd_info *)iterator_in->data;
            fprintf(fp, "cmd %d: %s\n", cmd_info->cmd, cmd_info->cmd_des);
        }
    }
    fprintf(fp, "------------------audio_api_show_info end-----------------\n");
    fclose(fp);
    return AUDIO_API_OK;
}

int audio_api_module_name_cmp(gconstpointer str1, gconstpointer str2)
{
    struct module_info *info1, *info2;

    info1 = (struct module_info *)str1;
    info2 = (struct module_info *)str2;
    return strcmp(info1->module_name, info2->module_name);
}

int audio_api_cmd_cmp(gconstpointer str1, gconstpointer str2)
{
    struct module_cmd_info *info1, *info2;
    info1 = (struct module_cmd_info *)str1;
    info2 = (struct module_cmd_info *)str2;
    return !(info1->cmd == info2->cmd);
}

int audio_api_find_module_name(gconstpointer p1, gconstpointer p2) {
    struct module_info *info1, *info2;

    info1 = (struct module_info *)p1;
    info2 = (struct module_info *)p2;
    return strcmp(info1->module_name, info2->module_name);
}

int audio_api_update_cfg(struct cmd_register *cmd_reg, char *module_start)
{
    FILE *fp;
    char file_name[64] = CFG_FILE_PATH;

    strcat(file_name, ".txt");
    if((fp=fopen(file_name,"a"))==NULL) {
        printf("Can not open file\n");
        return AUDIO_API_FAIL_OPEN_CONFIG_FILE;
    }
    fprintf(fp, "%d,%s,%s,%d,%s\n", ++g_cfg_line_num, cmd_reg->module_name, \
                    module_start, cmd_reg->cmd, cmd_reg->cmd_des);
    fclose(fp);
    return AUDIO_API_OK;
}

int audio_api_cmd_reg(struct cmd_register *cmd_reg)
{
    struct module_info tmp_module_info;
    struct module_info *find_info;
    GSList *find = NULL;
    GSList *find_cmd = NULL;
    struct module_cmd_info tmp_cmd_info, *cmd_info;

    strcpy(tmp_module_info.module_name, cmd_reg->module_name);
    find = g_slist_find_custom(g_module_list, &tmp_module_info, audio_api_module_name_cmp);
    if (find != NULL) {
        find_info = (struct module_info *)find->data;
        tmp_cmd_info.cmd = cmd_reg->cmd;
        find_cmd = g_slist_find_custom(find_info->list, &tmp_cmd_info, audio_api_cmd_cmp);
        if (find_cmd == NULL) {
            cmd_info = (struct module_cmd_info *)malloc(sizeof(struct module_cmd_info));
            strcpy(cmd_info->cmd_des, cmd_reg->cmd_des);
            cmd_info->cmd = cmd_reg->cmd;
            find_info->list = g_slist_insert_sorted(find_info->list, cmd_info, audio_api_cmd_cmp);
            audio_api_update_cfg(cmd_reg, find_info->module_start);
        } else {
            printf("already have, no need to reg, cmd is %d.\n", cmd_reg->cmd);
            return AUDIO_API_CMD_EXIST;
        }
    } else {
        printf("module not support.\n");
        return AUDIO_API_MODULE_NAME_NOT_SUPPORT;
    }
    audio_api_display_info(g_module_list);
}

int audio_api_module_reg(struct module_register *mod_reg)
{
    struct module_info tmp_module_info;
    struct module_info *find_info;
    GSList *find = NULL;

    strcpy(tmp_module_info.module_name, mod_reg->module_name);
    find = g_slist_find_custom(g_module_list, &tmp_module_info, audio_api_module_name_cmp);
    if (find != NULL) {
        find_info = (struct module_info *)find->data;
        strcpy(find_info->api, mod_reg->api);
        strcpy(find_info->dbus_service, mod_reg->dbus_service);
        strcpy(find_info->dbus_path, mod_reg->dbus_path);
        strcpy(find_info->dbus_interface, mod_reg->dbus_interface);
        find_info->need_time = mod_reg->need_time;
    } else {
        printf("module not support.\n");
        return AUDIO_API_MODULE_NAME_NOT_SUPPORT;
    }
    return AUDIO_API_OK;
}

static void audio_api_add_cfg_info(struct config_info *cfg_info)
{
    struct module_info tmp_module_info, *module_info;
    struct module_cmd_info tmp_cmd_info, *cmd_info;
    GSList *find = NULL;
    struct module_info *find_info;
    GSList *find_cmd = NULL;
    int ret = AUDIO_API_OK;

    g_cfg_line_num++;
    strcpy(tmp_module_info.module_name, cfg_info->module_name);
    find = g_slist_find_custom(g_module_list, &tmp_module_info, audio_api_module_name_cmp);
    if (find == NULL) {
        module_info = (struct module_info *)malloc(sizeof(struct module_info));
        strcpy(module_info->module_name, cfg_info->module_name);
        strcpy(module_info->module_start, cfg_info->module_start);
        strcpy(module_info->api, "\0");
        strcpy(module_info->dbus_path, "\0");
        strcpy(module_info->dbus_service, "\0");
        strcpy(module_info->dbus_interface, "\0");
        module_info->dbus_connected = 0;
        module_info->finished = 1;
        module_info->need_time = 0;
        module_info->list = NULL;
        module_info->exe_result = -1;
        strcpy(module_info->res_des, "\0");
        g_module_list = g_slist_insert_sorted(g_module_list, module_info, audio_api_module_name_cmp);

        cmd_info = (struct module_cmd_info *)malloc(sizeof(struct module_cmd_info));
        strcpy(cmd_info->cmd_des, cfg_info->cmd_des);
        cmd_info->cmd = cfg_info->cmd;
        module_info->list = g_slist_insert_sorted(module_info->list, cmd_info, audio_api_cmd_cmp);
    } else {
        tmp_cmd_info.cmd = cfg_info->cmd;
        find_info = (struct module_info *)find->data;
        find_cmd = g_slist_find_custom(find_info->list, &tmp_cmd_info, audio_api_cmd_cmp);
        if (find_cmd == NULL) {
            cmd_info = (struct module_cmd_info *)malloc(sizeof(struct module_cmd_info));
            cmd_info->cmd = cfg_info->cmd;
            strcpy(cmd_info->cmd_des, cfg_info->cmd_des);
            find_info->list = g_slist_insert_sorted(find_info->list, cmd_info, audio_api_cmd_cmp);
        }
    }
}

int audio_api_module_info_init(void) {
    int i, j;
    struct module_info *module_info;
    char *cmd;
    char line[1024];

    struct config_info cfg_info;
    FILE *fp;
    char file_name[64] = CFG_FILE_PATH;
    strcat(file_name, ".txt");
    printf("file name is %s.\n", file_name);
    if((fp=fopen(file_name,"r"))==NULL) {
        printf("Can not open file\n");
        return AUDIO_API_FAIL_OPEN_CONFIG_FILE;
    }

	fscanf(fp,"%[^\n]", line);
	while(!feof(fp)) {
		fscanf(fp,"%[^,],%[^,],%[^,],%d,%[^\n] ", cfg_info.id, cfg_info.module_name, \
            cfg_info.module_start, &cfg_info.cmd, cfg_info.cmd_des);
		audio_api_add_cfg_info(&cfg_info);
	}
    fclose(fp);
    audio_api_display_info(g_module_list);
    return AUDIO_API_OK;
}