#ifndef __HEADER_H__
#define __HEADER_H__
#include"../inc/header.h"
#endif
int iodev_op(int op)
{
    int status;

    switch(op)
    {

        case 1:
            status = gl11_iodev_open();
            if(status == -1)
            {
                printf("Iodev not opened successfully\n");
                return -1;
            }
            else
#ifdef DEBUG
                printf("Iodev opened successfully\n");
#endif
            break;
        case 0:
            status = gl11_iodev_close();
            if(status == -1)
            {
                printf("Iodev not closed successfully\n");
                return -1;
            }
            else
#ifdef DEBUG
                printf("Iodev closed successfully\n");
#endif
            break;
        default:
            {
                printf("Unknown operation\n");
                return -1;
            }
    }
    return 0;
}
