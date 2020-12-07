1、增加glib、gio库的依赖，具体见audio_helper_cpp项目
2、拷贝配置文件和so库到本地项目中，增加配置文件和so库的安装操作，具体见audio_helper_cpp项目
3、引用lib_audio_api.h文件
4、根据需要，调用文件中提供的api
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
6）lib uninit操作;在程序关闭之前需要调用audio_api_uninit(void)函数，否则会有内存泄露（考虑放到析构函数中？）
	语音模块在退出之前需要调用uninit操作，否则会有内存泄漏；
5、拷贝xml文件到本地项目中，安装gsettings配置文件，具体见audio_helper_cpp项目
6、编译、执行应用程序
