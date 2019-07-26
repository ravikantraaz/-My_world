#ifndef __HEADER_H__
#define __HEADER_H__
#include"header.h"
#endif

int device_open(void)
{
    int status;
    status = gl11_iodev_open();
    if (-1 == status)
    {
        printf("Device Opening Failed\n");
        exit(EXIT_FAILURE);
        //return -1;
    }
    else
    {
#if DEBUG
        printf("Device Opened\n");
#endif
        return 0;
    }
}

int scanner_open(void)
{
    int status;
    status = gl11_optcap_pwron();
    if (-1 == status)
    {
        printf("Scanner Opening Failed\n");
        exit(EXIT_FAILURE);
        //return -1;
    }
    else
    {
#if DEBUG
        printf("Scanner Opened\n");
#endif
        sleep(1);
        return 0;
    }
}
