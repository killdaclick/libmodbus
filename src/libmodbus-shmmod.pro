TEMPLATE = lib
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += staticlib
CONFIG += c++11

# wybor trybu kompilacji (jeden mozliwy)
#CONFIG += COMPILE_DLL
#CONFIG += COMPILE_STATIC
CONFIG += COMPILE_APP

COMPILE_DLL {
TEMPLATE = lib
DEFINES += COMPILE_DLL

DEFINES -= COMPILE_TEST_MODE_NOLIB
DEFINES -= COMPILE_STATIC
DEFINES -= COMPILE_APP
}

COMPILE_STATIC {
TEMPLATE = lib
CONFIG += staticlib
DEFINES += COMPILE_STATIC

DEFINES -= COMPILE_TEST_MODE_NOLIB
DEFINES -= COMPILE_DLL
DEFINES -= COMPILE_APP
}

COMPILE_APP {
TEMPLATE = app
DEFINES += COMPILE_APP
DEFINES += COMPILE_TEST_MODE_NOLIB

DEFINES -= COMPILE_DLL
DEFINES -= COMPILE_STATIC
}

INCLUDEPATH += ../

LIBS += -L"../lib/shmctrl/i386"
LIBS += -lpthread   # potrzebne do <semaphores.h>
LIBS += -lshmctrl

SOURCES += \
    modbus.cpp \
    modbus-tcp.cpp \
    modbus-rtu.cpp \
    modbus-data.cpp \
    main.cpp

HEADERS += \
    modbus-version.h.in \
    modbus-rtu.h \
    modbus-tcp-private.h \
    modbus-tcp.h \
    modbus-version.h \
    modbus.h \
    modbus-rtu-private.h \
    modbus-private.h \
    shmctrl/sys_shm_config.h \
    shmctrl/shmctrl.h \
    shmctrl/shm_ctrl_lib_global.h

