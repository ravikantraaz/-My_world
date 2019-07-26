#ifndef __HEADER_H__
#define __HEADER_H__
#include"../inc/header.h"
#endif
int BioCaptureFinger()
{
    unsigned char *buff = NULL;
    int status;
    status = PTGrab(handle, 
        (PT_BYTE)PT_GRAB_TYPE_508_508_8_SCAN508_508_8,
        4000,
        (PT_BOOL)PT_TRUE,
        (PT_DATA **)&GrabbedData,
        NULL,
        NULL);
    if(status == SUCCESS)
    {
        printf("PTGrab Success\n");
        buff = malloc(GrabbedData->Header.Length + 2);
        if (buff != NULL)
        {
            memcpy(buff, GrabbedData, GrabbedData->Header.Length + 2);
            status = ISO_CreateTemplate(256, 360, buff, myiso);
            if (status == SUCCESS)
            {
                printf("ISO_CreateTemplate Success\n");
                status = ISO_GetTemplateParameter(myiso,
                        PARAM_TEMPLATE_SIZE,
                        &mlen);
                if (status == SUCCESS)
                {
                    printf("ISO_GetTemplateParameter Success\n");
                }
                else
                    printf("ISO_GetTemplateParameter failed:%d\n",status);
            }
            else
                printf("ISO_CreateTemplate failed:%d\n",status);
        }
        else
        {
            printf("Memory allocation failed\n");
            return -1;
        }
    }
    else
    {
        printf("PTGrab Failed:%d",status);
    }
}
int Authenticate_iso(USER *head)
{
    printf("\e[31m\nAuthenticate To Delete...Press Enter\e[0m");
    getchar();
    getchar();
    int status,score;
    unsigned char *buff = NULL;
C:status = PTGrab(handle,
          (PT_BYTE)PT_GRAB_TYPE_508_508_8_SCAN508_508_8, 
          4000, (PT_BOOL)PT_TRUE,
          (PT_DATA **)&GrabbedData,
          NULL,
          NULL);
  if(status != SUCCESS)
  {
      printf("\nFinger capturing failed status=%d",status);
      goto C;
  }

  buff = malloc(GrabbedData->Header.Length + 2);
  if (buff == NULL)
  {
      printf("Malloc Failed\n");
      goto C;
  }
  memcpy(buff,GrabbedData,GrabbedData->Header.Length + 2);
  status = ISO_CreateTemplate(256,360,buff,myiso);
  if(status == 0)
  {
#ifdef DEBUG
      printf("ISO_CreateTemplate Success:%d\n",status);
#endif
      status = ISO_GetTemplateParameter(myiso,PARAM_TEMPLATE_SIZE,&mlen);
      if(status == 0)
      {
#ifdef DEBUG
          printf("ISO_GetTemplateParameter Success:%d\n",status);
#endif
      }
      else
      {
          printf("ISO_GetTemplateParameter failed:%d\n",status);
          return -1;
      }
  }

  else
  {
      printf("ISO_CreateTemplate failed:%d\n",status);
      return -1;
  }
  status = ISO_VerifyMatch(head->Buffer,myiso,180,&score);
  printf("matching score===%d,status=%d\n",score,status);
  if (status == 0 && score >= 13700)
  {
      printf("\e[32mVerified...OK\n\e[0m");
      return 0;
  }
  else
  {
      printf("\e[31mRefuted\n\e[0m");
      return 1;
  }
}

int delete_by_scan(USER **start, USER *head)
{
    int flag, status, security;
    unsigned long userid;
    userid = identify_by_scan_iso(handle, head, flag = 2);
#ifdef DEBUG
    printf("userid==%lu\n",userid);
#endif
    if(userid != -1 && userid != -2 && userid != 0)
    {
        status = delete_by_userid(userid, &(*start), head, security);
#ifdef DEBUG
        printf("status = %d,userid = %lu\n",status,userid);
#endif
        if(status == 0)
            return userid;
        else if(status == 1)
            return -4;
        else
            return -1;
    }
    else if(userid == -1 || userid == 0)
        return -1;
    else if(userid == -2)
        return -2;
    else
        return -3;
}
int Free_User(USER *head)
{
    int status;
    status = Authenticate_iso(head);
    if(status == 0)
    {
        free(head);
        return 0;
    }
    else if(status == 1)
        return 1;
    else
        return -1;
}
int delete_by_userid(unsigned long userid, USER **start, USER *head,int security)
{
    USER *tmp = NULL, *pre = NULL;int status;
    if(head->UserId == userid && head->Next == NULL) //checking for single node match
    {
        free(head);
        head = NULL;
        *start = head;
        return 0;
    }
    else if(head->UserId == userid && head->Next != NULL) //checking for first node match
    {
        tmp = head->Next;
        free(head);
        head = NULL;
        *start = tmp;
        return 0;
    }
    else //checking for other and last node match
    {
        *start = head;
        pre = head;
        head = head->Next;
        while(head != NULL)
        {
            if(head->UserId == userid && head->Next != NULL) //match at other node but last
            {
                pre->Next = head->Next;
                free(head);
                return 0;
            }
            if(head->UserId == userid && head->Next == NULL) //match at last node
            {
                pre->Next = NULL;
                free(head);
                return 0;
            }
            pre = pre->Next;
            head = head->Next;
        }
    }
    return -1;
}

USER *enroll_user(unsigned long userid, char *username, USER *head)
{
    USER *tmp = NULL, *tail = NULL;
    tmp = head;
    if(tmp == NULL)
    {
        head = tmp = (USER*)malloc(sizeof(USER));
        tmp->UserId = userid;
        strcpy(tmp->UserName,username);
        memcpy(tmp->Buffer, (char *)myiso, mlen + 1);
        tmp->Next = NULL;
        return head;
    }
    else
    {
        while(tmp->Next != NULL)
        {
            tmp = tmp->Next;
        }
        tail = tmp->Next = (USER*)malloc(sizeof(USER));
        tmp->Next->UserId = userid;
        strcpy(tmp->Next->UserName,username);
        memcpy(tmp->Next->Buffer, (char *)myiso, mlen + 1);
        tmp->Next->Next = NULL;
        return tail;
    }
}

void printuser(USER *head)
{
    if(head == NULL)
    {
        printf("\e[31mNo Users Are Enrolled\n\e[0m");
        return;
    }
    printf("\t*****Enrolled Users*****\n");
    printf("\t\e[35mUSERNAME\tUSERID\n\e[0m");
    while(head != NULL)
    {
        printf("\t%s\t\t%lu\n",head->UserName,head->UserId);
        head = head->Next;
    }
    printf("\t************************\n");
}

int search_user(USER *head, unsigned long userid, char *username)
{
    while(head != NULL)
    {
        if(head->UserId == userid)
            return 1;
        if(username && strcmp(head->UserName,username) == 0)
            return 2;
        head = head->Next;
    }
    return 0;
}

unsigned long identify_by_scan_iso(PT_CONNECTION handle, USER *head, int flag)
{
    int status, score;
    unsigned char *buff = NULL;
    if(head == NULL)
    {
        printf("\e[31mNo Users Are Enrolled Exiting...\n\e[0m");
        return -1;
    }
    if(flag != 1)
    {
C:status = PTGrab(handle, (PT_BYTE)PT_GRAB_TYPE_508_508_8_SCAN508_508_8, 4000, (PT_BOOL)PT_TRUE, (PT_DATA **)&GrabbedData, NULL, NULL);
  if(status != SUCCESS)
  {
      printf("\nFinger capturing failed status=%d",status);
      goto C;
  }

  buff = malloc(GrabbedData->Header.Length + 2);
  if (buff == NULL)
  {
      printf("Malloc Failed\n");
      goto C;
  }
  memcpy(buff,GrabbedData,GrabbedData->Header.Length + 2);
  status = ISO_CreateTemplate(256,360,buff,myiso);
  if(status == 0)
  {
#ifdef DEBUG
      printf("ISO_CreateTemplate Success:%d\n",status);
#endif
      status = ISO_GetTemplateParameter(myiso,PARAM_TEMPLATE_SIZE,&mlen);
      if(status == 0)
      {
#ifdef DEBUG
          printf("ISO_GetTemplateParameter Success:%d\n",status);
#endif
      }
      else
      {
          printf("ISO_GetTemplateParameter failed:%d\n",status);
          return -1;
      }
  }

  else
  {
      printf("ISO_CreateTemplate failed:%d\n",status);
      return -1;
  }
    }
    while (head != NULL )
    {
        status = ISO_VerifyMatch(head->Buffer,myiso,180,&score);
        printf("matching score===%d,status=%d\n",score,status);
        if (status == 0 && score >= 13700)
        {
            if(flag == 0)
                printf("\e[32mIdentified with USERID %lu\n\e[0m",head->UserId);
            if(flag == 1)
                return 1;
            if(flag == 2)
                return head->UserId;
            break;
        }
        head = head->Next;
    }
    if(head == NULL)
    {
        if(flag == 0)
            printf("\e[31mNot Identified\n\e[0m");
    }
    return 0;
}

int enroll_by_scan(PT_CONNECTION handle, unsigned long userid, char *username, int timeout, USER **start, USER *head)
{
    int status;
    if(userid == 0)
    {
        printf("\e[31mUserId \"0\" is Reserved\n\e[0m");
        return 1;
    }

    if(head != NULL)
    {
        status = search_user(head, userid, username);
        if(status == 1)
        {
            printf("\e[31mThis UserId is already taken\n\e[0m");
            return 1;
        }

        if(status == 2)
        {
            printf("\e[31mThis UserName is already taken\n\e[0m");
            return 1;
        }
    }
    status = PTGetSessionCfgEx(handle, 5, &cfgLen, (PT_SESSION_CFG**) &pCfg);//Session initialization
    if (status != SUCCESS)
    {
        printf("PTGetSessionCfgEx Failed\n");
        return -1;
    }
    else
    {
#ifdef DEBUG
        printf("Session initialized successfully\n");
#endif
    }

    pCfg->TemplateType = PT_TEMPLATE_TYPE_ALPHA;//To change Template Type

    status = PTSetSessionCfgEx(handle, 5, cfgLen, (PT_SESSION_CFG *)pCfg);//To start the session
    if(status != SUCCESS)
    {
        printf("Session not started successfully\n");
        return;
    }
    else
    {
#ifdef DEBUG
        printf("Session started successfully\n");
#endif
    }
    /*****************************************************************************************************************/
    int flag;
    unsigned char *buff;
    USER *tail = NULL;
    status = PTGrab(handle, (PT_BYTE)PT_GRAB_TYPE_508_508_8_SCAN508_508_8, timeout, (PT_BOOL)PT_TRUE, (PT_DATA **)&GrabbedData, NULL, NULL);
    if(status != SUCCESS)
    {
        printf("\nFinger capturing failed status=%d",status);
        return -1;
    }

    buff = malloc(GrabbedData->Header.Length + 2);
    memcpy(buff,GrabbedData,GrabbedData->Header.Length + 2);
    status = ISO_CreateTemplate(256,360,buff,myiso);
    if(status == 0)
    {
#ifdef DEBUG
        printf("ISO_CreateTemplate Success:%d\n",status);
#endif
        status = ISO_GetTemplateParameter(myiso,PARAM_TEMPLATE_SIZE,&mlen);
        if(status == 0)
        {
#ifdef DEBUG
            printf("ISO_GetTemplateParameter Success:%d\n",status);
#endif
        }
        else
        {
            printf("ISO_GetTemplateParameter failed:%d\n",status);
            return -1;
        }
    }

    else
    {
        printf("ISO_CreateTemplate failed:%d\n",status);
        return -1;
    }

    if (head == NULL)
    {
        head = enroll_user(userid, username, head);
    }
    else
    {
        status = identify_by_scan_iso(handle, head, flag = 1);
        if(status == 1)
        {
            printf("\e[31mThis person is already enrolled\n\e[0m");
            return 1;
        }
        tail = enroll_user(userid, username, head);
    }
    /*******************************************************************************************************************/
    *start = head;
    return 0;
}
