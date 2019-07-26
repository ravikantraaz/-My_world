#ifndef __HEADER_H__
#define __HEADER_H__
#include"../inc/header.h"
#endif

int init_FM(PT_CONNECTION handle)
{
	strcpy(dsn,"usb,vid=0x147e,pid=0x2016");
#ifdef DEBUG
	printf("dsn=%s\n",dsn);
#endif
	int status;

	status = PTInitialize(NULL);
	if (status == 0)
	{
#ifdef DEBUG
		printf("PTAPI library Initialized successfully\n");
#endif
	}
	else
	{
		printf("PTAPI library Not Initialized successfully\n");
		return -1;
	}

	status = PTOpen(dsn, &handle);
	if (status == 0)
	{
#ifdef DEBUG
		printf("PTOpen success\n");
#endif
	}
	else
	{
		printf("PTOpen failed\n");
		PTTerminate();
		return -1;
	}

	status = PTInfo(handle,&pinfo);
	if (status == 0)
	{
#ifdef DEBUG
		printf("PTInfo library Initialized successfully\n");
#endif
	}
	else
	{
		printf("PTInfo library Not Initialized successfully\n");
		PTClose(handle);
		PTTerminate();
		return -1;
	}

	status = IEngine_Init();
	if (status == 0)
	{
#ifdef DEBUG
                printf("IEngine_Init library Initialized successfully\n");
#endif
	}
        else
        {
                printf("IEngine_Init library Not Initialized successfully:%d\n",status);
                return -1;
        }
/*	status = dpfpdd_init();
        if(status == 0)
	{
#ifdef DEBUG
                printf("dpfpdd_init success\n");
#endif
	}
        else
	{
                printf("dpfpdd_init failed\n");
		IEngine_Terminate();
		PTClose(handle);
		PTTerminate();
	}*/
		
	return handle;
}
