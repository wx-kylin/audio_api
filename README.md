├── audio_api_log.txt --读取到的module info 文件
├── audio-helper --c版本的audio模块demo
│   ├── audio_helper_common.c
│   ├── audio_helper_common.h
│   ├── lib_audio_api.h
│   ├── main.c
│   ├── makefile
│   ├── readme
│   ├── student(1).txt
│   └── student.txt
├── audio-helper-cpp --c++版本的audio模块demo
│   ├── audio_helper_cpp
│   │   ├── audio_helper_common.cpp
│   │   ├── audio_helper_common.h
│   │   ├── audio_helper_cpp.pro
│   │   ├── audio_helper_cpp.pro.user
│   │   ├── lib_audio_api.h
│   │   ├── main.cpp
│   │   ├── mainwindow.cpp
│   │   ├── mainwindow.h
│   │   ├── mainwindow.ui
│   │   ├── mythread.cpp
│   │   ├── mythread.h
│   │   ├── org.ukui.audio_api.gschema.xml
│   │   ├── readme.txt
│   │   └── student.txt
│   └── build-audio_helper_cpp-unknown-Debug
│       ├── audio_helper_common.o
│       ├── audio_helper_cpp
│       ├── main.o
│       ├── mainwindow.o
│       ├── Makefile
│       ├── moc_mainwindow.cpp
│       ├── moc_mainwindow.o
│       ├── moc_predefs.h
│       ├── mythread.o
│       └── ui_mainwindow.h
├── dbus-test --dbus demo
│   ├── client
│   ├── client.c
│   ├── lib_audio_ukui_api.h
│   ├── readme.txt
│   └── server.c
├── lib-audio-helper --为audio提供的api源码库
│   ├── debug
│   │   └── makefile
│   ├── lib_audio_api.c --对audio模块的接口
│   ├── lib_audio_api_common.c  --核心操作
│   ├── lib_audio_api_common.h
│   ├── lib_audio_api_dbus.c  --dbus server相关操作
│   ├── lib_audio_api_dbus_client.c  --dbus clint相关操作
│   ├── lib_audio_api_dbus_client.h
│   ├── lib_audio_api_dbus.h
│   ├── lib_audio_api_gsetting.c --gsetting相关操作
│   ├── lib_audio_api_gsetting.h
│   ├── lib_audio_api.h
│   ├── lib_audio_ukui_api.h
│   ├── makefile
│   ├── org.ukui.audio_api.gschema.xml  --gsetting的配置文件
│   └── temp
│       └── makefile
├── README.md
├── test.c  --读文件的demo
└── ukui_demo --ukui模块的demo
    ├── main.cpp
    ├── mainwindow.cpp
    ├── mainwindow.h
    ├── readme.txt
    ├── ukui_demo.pro
    └── ukui_demo.pro.user

