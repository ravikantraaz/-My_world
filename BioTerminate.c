#ifndef __HEADER_H__
#define __HEADER_H__
#include"header.h"
#endif
void bio_uninit()
{
    //dpfpdd_exit();
    IEngine_Terminate();
    //PTFree(pinfo);
    PTClose(handle);
    PTTerminate();
#if DEBUG
    printf("bio_uninit Success\n");
#endif
}
