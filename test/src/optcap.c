#ifndef __HEADER_H__
#define __HEADER_H__
#include"../inc/header.h"
#endif
int optcap_op(int op)
{

	int status;

	switch(op)
	{

	case 1:
		status = gl11_optcap_pwron();
        	if(status == -1)
        	{
                	printf("scanner not powered on successfully\n");
                	return -1;
        	}
        	else
		{
#ifdef DEBUG
                	printf("scanner powered on successfully\n");
#endif
		}
		break;
	case 0:
        	status = gl11_optcap_pwroff();
		if(status == -1)
        	{
                	printf("scanner not powered off successfully\n");
                	return -1;
        	}
        	else
		{
#ifdef DEBUG
                	printf("scanner powered off successfully\n");
#endif
		}
		break;
	default:
		{
			printf("Unknown operation\n");
			return -1;
		}
	}
	return 0;
}

