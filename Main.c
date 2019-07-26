#ifndef __HEADER_H__
#define __HEADER_H__
#include"header.h"
#endif

int main()
{
    unsigned char *CapturedData = NULL;
    int CapturedDataLength;
    int capture_timeout_ms = 4000;
    int status;
    int mode = 1;
    FILE *fp;
    char DatabaseFileName[] = "person.dat";
    sprintf(DBFILE, "%s", DatabaseFileName);

    bct_t CaptureFormat;

    device_open();
    scanner_open();
    bio_init();
    BioReadDB();

    while(1) 
    {
        BIO_MENU;
        ENTER_CHOICE;
        switch(choice[0])
        {
            case '1':
                while(1) 
                {
                    BIO_SUB_MENU;
                    ENTER_CHOICE;
                    switch(choice[0])
                    {
                        case '1':
                            CaptureFormat = BCF_RAW;
                            status = BioCaptureFinger(&CapturedData,
                                    &CapturedDataLength,
                                    capture_timeout_ms,
                                    CaptureFormat);
                            if ( 0 != status )
                            {
                                printf("BioCaptureFinger Failed:%d\n", status);
                            }
                            break;
                        case '2':
                            CaptureFormat = BCF_BIR;
                            status = BioCaptureFinger(&CapturedData,
                                    &CapturedDataLength,
                                    capture_timeout_ms,
                                    CaptureFormat);
                            if ( 0 != status )
                            {
                                printf("BioCaptureFinger Failed:%d\n", status);
                            }
                            break;
                        case '3':
                            CaptureFormat = BCF_ISO;
                            status = BioCaptureFinger(&CapturedData,
                                    &CapturedDataLength,
                                    capture_timeout_ms,
                                    CaptureFormat);
                            if ( 0 != status )
                            {
                                printf("BioCaptureFinger Failed:%d\n", status);
                            }
                            break;
                        case '0':
                            status = TRUE;
                            break;
                        default:
                            {
                                printf("Invalid choice\n");
                            }
                    }

                    if ( status == TRUE )
                    {
                        status = FALSE;
                        break;
                    }
                }
                break;
            case '2':
                Admin();
            case '+':
                CaptureFormat = BCF_ISO;
                status = BioEnrolByScan(CaptureFormat, capture_timeout_ms);
                if ( 0 != status )
                {
                    printf("BioCaptureFinger Failed:%d\n", status);
                }
                break;
            case '*':
                BioPrint();
                break;
            case '.':
                status = BioReadDB();
                printf("BioReadDB = %d\n", status);
                break;
            case '-':
                status = BioDelUserDB();
                printf("BioDelUserDB = %d\n", status);
                break;
            case '0':
                status = TRUE;
                break;
            default:
                {
                    printf("Invalid choice\n");
                }
        }
        if ( status == TRUE )
        {
            status = FALSE;
            break;
        }
    }

    free(start);
    bio_uninit();
    scanner_close();
    device_close();

    return 0;
}
