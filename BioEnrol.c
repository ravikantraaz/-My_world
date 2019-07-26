#ifndef __HEADER_H__
#define __HEADER_H__
#include"header.h"
#endif
//#include"../inc/bmp.h"
#include"../inc/bmpHexArr_.h"
int prepare_bmp(unsigned char *bmpbuf,unsigned char *data,int lenprn)
{
    int count1,count2;
    for(count1=0,count2=0;count1<lenprn;count1++)
    {
        if(count2 >99999)
        {
            printf("PRINTER:********* %d\n",count2);
            return -1;
        }
        if(count1%48==0)
            count2=count2+(48*4);
        bmpbuf[count2+(47-(count1%48))]=~data[count1];
        bmpbuf[count2+48+(47-(count1%48))]=~data[count1];
        bmpbuf[count2+96+(47-(count1%48))]=~data[count1];
        bmpbuf[count2+48+96+(47-(count1%48))]=~data[count1];
    }
    /*char bmpbuff[100000]="";
    int ret;

    memset(bmpbuff,0,sizeof(bmpbuff));
    len = prepare_bmp(bmpbuff,block_bmp,sizeof(block_bmp));
    ret = prn_write_bmp(bmpbuff,len);
    printf("ret = %d\n",ret);
    memset(bmpbuff,0,sizeof(bmpbuff));*/
    return count2;
}
void BioThermalPrint()
{
    int len;
    int status;
    char buffer[100] = {0x00};
    sprintf(buffer, "\n    ************************\n\n\n\n");
    strcat(pbuffer, buffer);
    len = strlen(pbuffer);    
    status = prn_open();
    if(status  == 1 || status == 2)
    {
        status = prn_write_text(pbuffer , len, 1);
        if(status != -1)
        {
            printf("prn_write_text success\n");
            prn_close();
        }
        else
        {
            printf("prn_write_text failed\n");
        }
    }
    else
    {
        printf("prn_open failed\n");
    }
    memset(pbuffer, 0x00, 10000);
}
void BioPrint()
{
    int command;
    char buffer[100] = {0x00};
    user_t *tmp = NULL;

    while(1)
    {
        sprintf(buffer, "    *****Enrolled Users*****\n\n"
                "    Username          Userid\n\n");
        strcat(pbuffer, buffer);
        tmp = start;
        if (tmp == NULL)
        {
            printf("\e[31mNo users are enrolled\e[0m\n");
            sprintf(buffer, "    No users are enrolled\n\n");
            strcat(pbuffer, buffer);
            BioThermalPrint();
            break;
        }
        BIO_PRINT_MENU;
        printf("Enter your choice :  ");
        scanf("%d", &command);
        if (command == SOFTPRINT)
        {
            printf("\t*****Enrolled Users*****\n");
            printf("\t\e[35mUsername\tUserid\n\e[0m");
            while(tmp != NULL)
            {
                printf("\t%s\t\t%d\n", tmp->username, tmp->userid);
                tmp = tmp->next;
            }
            printf("\t************************\n");
        }
        else if(command == HARDPRINT)
        {
            while(tmp != NULL)
            {
                sprintf(buffer, "    %-10s        %-4d\n", 
                        tmp->username, tmp->userid);
                strcat(pbuffer, buffer);
                memset(buffer, 0x00, 100);
                tmp = tmp->next;
            }
            BioThermalPrint();
        }
        else if(command == 0)
        {
            break;
        }
        else
        {
            printf("Invalid selection Expected : 1 or 2\n");
        }
    }
    return;
}

int BioIdentify(unsigned char *CapturedData, int CapturedDataLength, 
        int Purpose)
{
    int status;
    int score;
    user_t *tmp = NULL;
    tmp = start;
    while(tmp != NULL)
    {
        status = ISO_VerifyMatch(tmp->buffer, CapturedData, 180, &score);
        if(status == 0 && score >= 13700)
        {
            if(Purpose == 1)
            {
                printf("\e[34mYou are already enrolled with userid %d\n"
                        "Please enrol with a different finger or person\e[0m\n",
                        tmp->userid);
            }
            else
            {
                printf("\e[34mMatched with userid %d \e[0m\n", tmp->userid);
            }
            return tmp->userid;
        }
        tmp = tmp->next;
    }
    return 0;
}

int search_user(int userid, char *username)
{
    user_t *tmp = NULL;
    tmp = start;
    while(tmp != NULL)
    {
        if(tmp->userid != 0 && tmp->userid == userid)
            return 1;
        if(username != NULL && strcmp(tmp->username, username) == 0)
            return 2;
        tmp = tmp->next;
    }
    return 0;
}
int BioDeleteByScan()
{
    int userid;
    int status;
    int Purpose = 0;
    unsigned char *CapturedData = NULL;
    int CapturedDataLength;
    int capture_timeout_ms = 4000;
    int CaptureFormat = BCF_ISO;

    status = BioCaptureFinger(&CapturedData,
            &CapturedDataLength,
            capture_timeout_ms,
            CaptureFormat);
    if ( 0 != status )
    {
        printf("BioCaptureFinger Failed:%d\n", status);
        return status;
    }

    userid = BioIdentify(CapturedData, CapturedDataLength, Purpose);
    if(userid != 0)
    {
        status = BioDeleteByUserid(userid);
        return status;
    }
    else
    {
        printf("\e[31mMatching Failed\e[0m\n");
        return -1;
    }
}
int BioDeleteByUserid(int uid)
{
    int userid;
    user_t *tmp = NULL, *prev = NULL, *current = NULL;
    if(uid)
    {
        userid = uid;
    }
    else
    {
        printf("Enter userid : ");
        scanf("%d", &userid); 
    }
    current = start;
    if(start == NULL || start == 0)
    {
        printf("\e[31mNo database found\e[0m\n");
        return -1;
    }
    if(current->userid == userid && current->next == NULL)
    {
        free(current);
        current = NULL;
        start = current;
        return 1;
    }
    else if(current->userid == userid && current->next != NULL)
    {
        tmp = current->next;
        free(current);
        current = tmp;
        start = current;
        return 2;
    }
    else
    {
        prev = current;
        current = current->next;
        while(current != NULL)
        {
            if(current->userid == userid && current->next != NULL)
            {
                tmp = current->next;
                free(current);
                prev->next = tmp;
                return 3;
            }
            else if(current->userid == userid && current->next == NULL)
            {
                free(current);
                prev->next = NULL;
                return 4;
            }
            else
            {
                prev = prev->next;
                current = current->next;
            }
        }
    }
    return -2;
}
int BioDelUserDB()
{
    int status;
    int mode = 2;
    int uid = 0;
    if(start == NULL || start == 0)
    {
        printf("\e[34mNo database found\e[0m\n");
        return -1;
    }
    while(1)
    {
        BIO_REMOVE_MENU;
        ENTER_CHOICE;
        switch(choice[0])
        {
            case '1':   status = BioDeleteByUserid(uid);
                        printf("BioDeleteByUserid = %d\n", status);
                        if(status > 0)
                            BioWriteDB(start, mode);
                        break;
            case '2':   status = BioDeleteByScan();
                        printf("BioDeleteByScan = %d\n", status);
                        if(status > 0)
                            BioWriteDB(start, mode);
                        break;
            case '0':   return -1;
                        break;
            default:    printf("Invalid method\n");
        }
    }
    return 0;
}
user_t *enrol_user(int userid, char *username, 
        unsigned char *CapturedData, int CapturedDataLength)
{
    user_t *newuser = NULL;
    newuser = head;
    if(newuser == NULL || newuser == 0)
    {
        start = newuser = (user_t *)malloc(sizeof(user_t));
        newuser->userid = userid;
        strcpy(newuser->username, username);
        memcpy(newuser->buffer, CapturedData, CapturedDataLength);
        newuser->bufferlength = CapturedDataLength;//added
        newuser->next = NULL;
        return newuser;
    }
    else
    {
        newuser->next = (user_t *)malloc(sizeof(user_t));
        newuser->next->userid = userid;
        strcpy(newuser->next->username, username);
        memcpy(newuser->next->buffer, CapturedData, CapturedDataLength);
        newuser->next->bufferlength = CapturedDataLength;//added
        newuser->next->next = NULL;
        return newuser->next;
    }
}

int BioEnrolByScan(int CaptureFormat, int capture_timeout_ms)
{
    int userid;
    char username[20];
    unsigned char *CapturedData = NULL;
    int CapturedDataLength;
    int status;
    int Purpose = 1;

    do
    {
        printf("Enter userid: ");
        scanf("%d", &userid);
        if(userid == 0)
            return -1;
        status = search_user(userid, NULL);
        if (0 != status)
            printf("\e[33mUserid \"%d\" is already taken\n"
                    "Choose a different one\e[0m\n", userid);
    } while(status != 0);

    g_userid = userid;

    do
    {
        printf("Enter username: ");
        scanf("%s", username);
        if(strcmp(username, "0") == 0)
            return -1;
        status = search_user(0, username);
        if (0 != status)
            printf("\e[33mUsername \"%s\" is already taken\n"
                    "Choose a different one\e[0m\n", username);
    } while(status != 0);
    do
    {
        status = BioCaptureFinger(&CapturedData,
                &CapturedDataLength,
                capture_timeout_ms,
                CaptureFormat);
        if ( 0 != status )
        {
            printf("BioCaptureFinger Failed:%d\n", status);
            return status;
        }

        status = BioIdentify(CapturedData, CapturedDataLength, Purpose);
        if(status != 0)
        {
            printf("\e[32mPress enter to continue: \e[0m");
            if(0 == flag1++)
                status = getchar();
            status = getchar();
            if(status == 48)
                return -1;
        }

    } while(status != 0);

    head = enrol_user(userid, username, CapturedData, CapturedDataLength);
    if (head == NULL || head == 0)
    {
        printf("\e[31mEnrollment Failed\e[0m\n");
        return -1;
    }
    else
    {
        BioWriteDB(head);
        return 0;
    }
}
