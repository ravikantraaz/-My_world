#ifndef __HEADER_H__
#define __HEADER_H__
#include"header.h"
#endif

int BioCaptureFinger( unsigned char **CapturedData, int  *CapturedDataLength, 
                            int capture_timeout_ms, int CaptureFormat )
{
    PT_BIR *CapturedTemplate = NULL;
    PT_DATA *GrabbedData = NULL;
    unsigned char ISOTemplate[1566];
    int status;
    int ISOTemplateLength;
    unsigned char *tmpdata = NULL;
    int tmplength = 0;
    
    if ( CaptureFormat == 0 || CaptureFormat == 2 )
    {
        status = PTGrab( handle,
                PT_GRAB_TYPE_508_508_8_SCAN508_508_8,
                capture_timeout_ms,
                PT_TRUE,
                &GrabbedData,
                NULL,
                NULL );
        if ( 0 != status )
        {
            printf("PTGrab Failed:%d\n", status);
            return status;
        }

        tmplength = GrabbedData->Length + 2;
        tmpdata = malloc(tmplength);

        if( NULL != tmpdata )
        {
            if ( CaptureFormat == 2 )
            {
                memcpy(tmpdata, GrabbedData->Data, tmplength);
                PTFree(GrabbedData);
                status = ISO_CreateTemplate(256, 360, tmpdata, ISOTemplate);
                if (0 != status)
                {
                    printf("ISO_CreateTemplate Failed:%d\n",status);
                    return status;
                }
                else
                {
                    status = ISO_GetTemplateParameter(ISOTemplate, PARAM_TEMPLATE_SIZE, 
                            &ISOTemplateLength);
                    if (0 != status)
                    {
                        printf("ISO_GetTemplateParameter Failed:%d\n",status);
                        return status;
                    }
                    else
                    {
                        sprintf(FILENAME, "%d.iso", g_userid);
                        *CapturedDataLength = ISOTemplateLength;
                        *CapturedData = malloc(ISOTemplateLength + 2);
                        ISO_SaveTemplate(FILENAME, ISOTemplate);
                        status = ISO_LoadTemplate(FILENAME, *CapturedData);
                        remove(FILENAME);
                        return status;
                    }
                }
            }
            else
            {
                memcpy(*CapturedData, GrabbedData->Data, *CapturedDataLength);
                PTFree(GrabbedData);
                return 0;
            }
        }
        else
        {
            printf("Memory Allocation Failed\n");
            PTFree(GrabbedData);
            return -1;
        }

    }
    else if (CaptureFormat == 1)
    {
        status = PTCapture(handle,
                PT_PURPOSE_VERIFY,
                &CapturedTemplate,
                capture_timeout_ms,
                NULL,
                NULL,
                NULL);

        if (0 != status)
        {
            printf("PTCapture Failed:%d\n",status);
            return status;
        }
        else
        {
            *CapturedDataLength = CapturedTemplate->Header.Length + 2;
            *CapturedData = malloc(*CapturedDataLength);
            if(NULL != *CapturedData)
            {
                memcpy(*CapturedData, CapturedTemplate->Data, *CapturedDataLength);
                PTFree(CapturedTemplate);
                return 0;
            }
            else
            {
                printf("Memory Allocation Failed\n");
                PTFree(CapturedTemplate);
                return -1;
            }
        }
    }
    else
    {
        printf("Invalid Capture Format\n0 - Raw,1 - BIR,2 - ISO\n");
        return -1;
    }
    return 0;
}
