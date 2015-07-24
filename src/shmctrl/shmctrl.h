#ifndef SHMCTRL_H
#define SHMCTRL_H

#include "shm_ctrl_lib_global.h"
#include "sys_shm_config.h"

#include <iostream>
#include <fstream>
#include <map>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <inttypes.h>

// SHM
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
// \SHM

// semaphores
#include <semaphore.h>
// \semaphores

#define SHMCTRL_INIT_REGSHMLISTATTACH_ERROR   1
#define SHMCTRL_INIT_REGSHMWRONGNAME_ERROR  2
#define SHMCTRL_INIT_REGSHMRESATTACH_ERROR  4
#define SHMCTRL_READWRITE_REGSHMWRONGNAME_ERROR 8
#define SHMCTRL_READWRITE_OFFSETOUTOFRANGE_ERROR 16
#define SHMCTRL_READWRITE_SIZEOUTOFRANGE_ERROR 32
#define SHMCTRL_READWRITE_UNKNOWN_ERROR 64
#define SHMCTRL_INIT_REGSHMSEMAPHORE_ADDRNOTFOUND_ERROR 128

using namespace std;

class EXPORT SHMctrl
{

    public:
        static SHMctrl& Instance(); // Singleton
        int32_t checkInit( void );
        int32_t read( string name, uint16_t offset, uint16_t size, uint16_t* buff, int32_t *error=NULL, uint32_t flag=0 );
        int32_t write( string name, uint16_t offset, uint16_t size, uint16_t* buff, int32_t *error=NULL, uint32_t flag=0 );

        struct SHMresourceItemStruct
        {
            SHMresourceItemStruct() : name(""), addr(0), sizeW(0), sectorSize(0), listPos(0), semCnt(0), semOffset(0) {} // zerujemy domyslnie wartosci

            std::string name;
            uint16_t* addr;
            uint16_t sizeW;
            uint8_t sectorSize;
            uint8_t listPos;
            uint8_t semCnt;
            uint16_t semOffset;
        };
        typedef pair<string, SHMresourceItemStruct> SHMresourcesMapPair;
        typedef map<string, SHMresourceItemStruct> SHMresourcesMap;

    private:
        SHMctrl();   // Singleton
        SHMctrl( const SHMctrl& ) {};           // przeladowujemy operator kopiowania aby byl niedostepny
        void operator=( const SHMctrl& ) {};   // przeladowujemy operator kopiowania aby byl niedostepny
        ~SHMctrl() {};

        string getSHMdescriptorFile( const string &shmName );
        int32_t attachSHMregion( const string &name, uint32_t flags );
        int32_t getSHMresources( const string shmName );

        //inline uint16_t SHMctrl::getSemaphoreSector( const string &name )
        //{
        //}


        int32_t initError_;
        SHMresourcesMap shmResourcesMap_;
        sem_t* semAddr_;

};

// Class factory "C" functions - do ladowania biblioteki dynamicznej

#ifdef SHMCTRL_COMPILE_DLL
typedef SHMctrl& create_t;
typedef void destroy_t(SHMctrl*);
#endif

#endif // SHMCTRL_H
