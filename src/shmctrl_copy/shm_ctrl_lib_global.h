#ifndef SHM_CTRL_LIB_GLOBAL_H
#define SHM_CTRL_LIB_GLOBAL_H

// komentujemy ponizsze jezeli korzystamy z pliku Qt *.pro
/*
#ifdef SHMCTRL_COMPILE_DLL
    #define SHMCTRL_COMPILE_TEST_MODE_NOLIB
    #undef SHMCTRL_COMPILE_APP
    #undef SHMCTRL_COMPILE_STATIC
#endif

#ifdef SHMCTRL_COMPILE_STATIC
    #define SHMCTRL_COMPILE_TEST_MODE_NOLIB
    #undef SHMCTRL_COMPILE_APP
    #undef SHMCTRL_COMPILE_DLL
#endif

#ifdef SHMCTRL_COMPILE_APP
    #undef SHMCTRL_COMPILE_TEST_MODE_NOLIB
    #undef SHMCTRL_COMPILE_DLL
    #undef SHMCTRL_COMPILE_STATIC
#endif
*/

//#include <inttypes.h>
//#include <string.h>

#define _GCC

#if defined(_MSC_VER)
    //  Microsoft
    #define EXPORT __declspec(dllexport)
    #define IMPORT __declspec(dllimport)
#elif defined(_GCC)
    //  GCC
    #define EXPORT __attribute__((visibility("default")))
    #define IMPORT
#else
    //  do nothing and hope for the best?
    #define EXPORT
    #define IMPORT
    #pragma warning Unknown dynamic link import/export semantics.
#endif

/*
#include <QtCore/qglobal.h>

#if defined(SHMCTRL_COMPILE_DLL)
#  define SHM_CTRL_LIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SHM_CTRL_LIBSHARED_EXPORT Q_DECL_IMPORT
#endif
*/

// tutaj wrzucamy funkcje ktore eksportujemy i uzywamy z biblioteki
#ifdef SHMCTRL_COMPILE_DLL
#ifdef __cplusplus
extern "C" {
#endif

int32_t checkInit(void);
int32_t read( std::string name, uint16_t offset, uint16_t size, uint16_t* buff, int32_t *error=NULL, uint32_t flag=0 );
int32_t write( std::string name, uint16_t offset, uint16_t size, uint16_t* buff, int32_t *error=NULL, uint32_t flag=0 );


#ifdef __cplusplus
}
#endif
#endif // SHM_USE_DLL

#endif // SHM_CTRL_LIB_GLOBAL_H
