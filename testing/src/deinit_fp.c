#ifndef __HEADER_H__
#define __HEADER_H__
#include"../inc/header.h"
#endif
int deinit_FM(PT_CONNECTION handle)
{
	int status;

	/*status = dpfpdd_exit();
	if(status == 0)
	{
#ifdef DEBUG
		printf("dpfpdd_exit De-Initialized successfully\n");
#endif
	}
	else
	{
		printf("dpfpdd_exit Not De-Initialized successfully\n");
	}

    */
	status = IEngine_Terminate();
	if (status == 0)
	{
#ifdef DEBUG
                printf("IEngine_Init library De-Initialized successfully\n");
#endif
	}
        else
        {
                printf("IEngine_Init library Not De-Initialized successfully\n");
                return -1;
        }

	/*status = PTFree(pinfo);
	if (status == 0)
	{
#ifdef DEBUG
		printf("PTFree library De-Initialized successfully\n");
#endif
	}
	else
	{
		printf("PTFree library Not De-Initialized successfully\n");
		return -1;
	}*/

	status = PTClose(handle);
	if (status == 0)
	{
#ifdef DEBUG
		printf("PTClose success\n");
#endif
	}
	else
	{
		printf("PTClose failed\n");
		return -1;
	}

	status = PTTerminate();
	if (status == 0)
	{
#ifdef DEBUG
		printf("PTAPI library De-Initialized successfully\n");
#endif
	}
	else
	{
		printf("PTAPI library Not De-Initialized successfully\n");
		return -1;
	}
return 0;
}
