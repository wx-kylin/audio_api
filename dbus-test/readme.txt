gcc server.c -I/usr/include/glib-2.0/ -I/usr/lib/x86_64-linux-gnu/glib-2.0/include/ -L/usr/lib/x86_64-linux-gnu/ -lglib-2.0 -lgio-2.0

gcc client.c -I/usr/include/glib-2.0/ -I/usr/lib/x86_64-linux-gnu/glib-2.0/include/ -L/usr/lib/x86_64-linux-gnu/ -lglib-2.0 -lgio-2.0 -o client
