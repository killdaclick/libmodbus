#include "modbus.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#ifdef COMPILE_TEST_MODE_NOLIB
int main( void )
{
    modbus_mapping_t mb_mapping;
    mb_mapping.nb_registers = 16;
    modbus_t* ctx = modbus_new_tcp("192.168.1.81", 1502);
    int s = -1;
    s = modbus_tcp_listen(ctx,1);
    modbus_tcp_accept(ctx,&s);


    for (;;) {
        uint8_t query[MODBUS_TCP_MAX_ADU_LENGTH];
        int rc;

        rc = modbus_receive(ctx, query);
        if (rc > 0) {
            /* rc is the query size */
            modbus_reply(ctx, query, rc, &mb_mapping);
        } else if (rc == -1) {
            /* Connection closed by the client or error */
            break;
        }
    }

    printf("Quit the loop: %s\n", modbus_strerror(errno));

    if (s != -1) {
        close(s);
    }
    //modbus_mapping_free(mb_mapping);
    modbus_close(ctx);
    modbus_free(ctx);

    return 0;










    //modbus_t* ctx = modbus_new_rtu("/dev/tty1", 115200, 'N', 8, 1);

    /*SHMctrl& shmCtrl = SHMctrl::Instance();

    int32_t err = shmCtrl.checkInit();
    if( err > 0 )
        return -1;

    uint16_t tabW[4];
    tabW[0] = 1111;
    tabW[1] = 1112;
    tabW[2] = 1113;
    tabW[3] = 1114;
    uint16_t tabR[4];
    tabR[0] = 0;
    tabR[1] = 0;
    tabR[2] = 0;
    tabR[3] = 0;

    shmCtrl.write( "MEAS", 0, 2, tabW );
    shmCtrl.read( "MEAS", 0, 2, tabR );*/

    bool stop = true;

}
#endif
