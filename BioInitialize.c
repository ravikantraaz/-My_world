#ifndef __HEADER_H__
#define __HEADER_H__
#include"header.h"
#endif

int bio_init()
{

    int status;
    strcpy(dsn, "usb,vid=0x147e,pid=0x2016");

    remove("RAWImage.raw");
    remove("BIRTemplate.bir");
    remove("ISOTemplate.iso");

    status = PTInitialize(NULL);
    if (0 != status)
    {
        printf("PTAPI Library Not Initialized:%d\n", status);
        exit(EXIT_FAILURE);
        //return -1;
    }
    else
        //printf("PTAPI Library Initialized\n");
    status = PTOpen(dsn, &handle);
    if (0 != status)
    {
        printf("PTOpen Failed:%d\n", status);
        PTTerminate();
        exit(EXIT_FAILURE);
        //return -1;
    }
    else
        //printf("PTOpen Success:%ld\n", handle);
    /*status = PTInfo(handle,&pinfo);
    if (0 != status)
    {
        printf("PTInfo Not Initialized:%d\n", status);
        PTClose(handle);
        PTTerminate();
        exit(EXIT_FAILURE);
        //return -1;
    }
    else
        //printf("PTInfo Initialized\n");*/
    status = IEngine_Init();
    if (0 != status)
    {
        printf("IEngine_Init Failed:%d\n", status);
        PTFree(pinfo);
        PTClose(handle);
        PTTerminate();
        exit(EXIT_FAILURE);
        //return -1;
    }
    else
        //printf("IEngine_Init Success\n");
    /*status = dpfpdd_init();
    if (0 != status)
    {
        printf("dpfpdd_init Failed:%d\n", status);
        IEngine_Terminate();
        PTFree(pinfo);
        PTClose(handle);
        PTTerminate();
        exit(EXIT_FAILURE);
        //return -1;
    }
    else
        //printf("dpfpdd_init Success\n");*/
#if DEBUG
    printf("bio_init Success\n");
#endif
    return 0;
}
