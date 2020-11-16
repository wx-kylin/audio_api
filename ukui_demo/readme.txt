1、项目中增加dbus库；
2、将模块信息注册给audio_api，包括三步：
1）注册模块信息：
	调用dbus的module_register函数
2）注册命令信息（多次）
	调用dbus的cmd_register函数
3）注册完成：
	调用dbus的mod_register_finish函数
4）各个函数的结构：
    "<method name='module_register'>"
		"<arg type='s' name='name' direction='in'/>"
		"<arg type='s' name='api' direction='in'/>"
		"<arg type='s' name='dbus_service' direction='in'/>"
		"<arg type='s' name='dbus_path' direction='in'/>"
		"<arg type='s' name='dbus_interface' direction='in'/>"
		"<arg type='i' name='need_time' direction='in'/>"
		"<arg name='result' type='i' direction='out'/>"
    "</method>"
    "<method name='cmd_register'>"
		"<arg type='s' name='name' direction='in'/>"
		"<arg type='i' name='cmd' direction='in'/>"
		"<arg type='s' name='cmd_des' direction='in'/>"
		"<arg name='result' type='i' direction='out'/>"
    "</method>"
	"<method name='cmd_execute_result'>"
		"<arg type='s' name='name' direction='in'/>"
		"<arg type='i' name='cmd' direction='in'/>"
		"<arg type='s' name='result' direction='in'/>"
		"<arg name='result' type='i' direction='out'/>"
    "</method>"
	"<method name='mod_register_finish'>"
		"<arg type='s' name='name' direction='in'/>"
		"<arg name='result' type='i' direction='out'/>"
    "</method>"
3、添加处理响应gsetting的connect
	gsetting路径：org.ukui.audio_api
	监听元素：init（bool值，0-1反复变化，监听到变化就说明audio-api已经初始化完成，需要注册）
4、实现命令调用函数，函数名通过模块信息注册，注册给audio_api
