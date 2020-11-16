
1、修改makefile中LIBDIR为本地lib库存放位置；
2、增加glib、gio库的依赖，例子见audio_helper_cpp项目
3、将动态库拷贝到lib库：
sudo cp ./lib-audio-helper/libaudio.so /usr/lib/
4、引用lib_audio_api.h文件
5、根据需要，调用文件中提供的api
1）lib初始化接口，在调用其他接口之前需要先调用此接口
	audio_api_init（void）
2）将模块和命令信息打印到标准输出流：
	audio_api_show_cmds（void）
3）命令执行接口，mod为模块名，cmd为命令序号
	audio_api_cmd_execute(char *mod, int cmd)
	注意：调用命令时，需要单独起一个线程，不能和init接口通过同一个线程调用，否则会阻塞；
4) 将模块信息读入文件
	audio_api_read_module_info(void)
5） 获得版本号信息
	audio_api_get_verison_info（void）
5、编译、执行应用程序
