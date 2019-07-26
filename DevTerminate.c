#ifndef __HEADER_H__
#define __HEADER_H__
#include"header.h"
#endif

int device_close(void)
{
    int status;
    status = gl11_iodev_close();
    if (-1 == status)
    {
        printf("Device Closing Failed\n");
        return -1;
    }
    else
    {
#if DEBUG
        printf("Device Closed\n");
#endif
        return 0;
    }
}

int scanner_close(void)
{
    int status;
    status = gl11_optcap_pwroff();
    if (-1 == status)
    {
        printf("Scanner Closing Failed\n");
        return -1;
    }
    else
    {
#if DEBUG
        printf("Scanner Closed\n");
#endif
        return 0;
    }
}
