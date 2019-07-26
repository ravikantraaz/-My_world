#ifndef __HEADER_H__
#define __HEADER_H__
#include"../inc/header.h"
#endif
#define SECURITY 0
int main()
{
    int status, timeout = -1, flag, security;
    unsigned long userid;
    char username[20];
    char choice[1];
    USER *start = NULL;

    iodev_op(1);
    status = optcap_op(1);
    if(status == -1)
    {
        iodev_op(0);
        return -1;
    }

    handle = init_FM(handle);
    if(handle == 1)
    {
        MENU;
        while(1)
        {
C:printf("\e[36mEnter Choice : \e[0m");
  scanf(" %s",choice);
  if(strlen(choice)> sizeof(char))
  {
      printf("\e[33mInvalid Choice\n\e[0m");
      goto C;
  }
  switch(choice[0])
  {
      case '1' : printf("\e[35mEnter UserId : \e[0m");
                 scanf("%lu",&userid);
                 printf("\e[35mEnter UserName : \e[0m");
                 scanf("%s",username);
                 //printf("&start=%p,start=%p\n",&start,start);
                 status = enroll_by_scan(handle, userid, username, timeout, &start, start);
                 if(status == 1 || status == -1 || start == NULL)
                     printf("\e[31mEnrollment failed for UserId %lu\n\e[0m",userid);
                 else
                     printf("\e[32mEnrollment success for UserId %lu\n\e[0m",userid);
                 break;
                 //case '2' : identify_by_scan_bir(handle, start, flag = 0);break;
      case '2' : identify_by_scan_iso(handle, start, flag = 0);break;
      case '3' : MENU;break;
      case '4' : printuser(start);break;
      case '5' : if(start == NULL)
                 {
                     printf("\e[31mNo Users To Delete...\n\e[0m");
                     break;
                 }
                 else
                 {
                     printf("\e[35mEnter USERID : \e[0m");
                     scanf("%lu",&userid);
                     status = delete_by_userid(userid, &start, start, SECURITY);
                     if(status == 0)
                         printf("\e[32mUSERID %lu Is Deleted Successfully\n\e[0m",userid);
                     else
                         printf("\e[31mUSERID %lu Not Found\n\e[0m",userid);
                 }
                 break;
      case '6' : if(start == NULL)
                 {
                     printf("\e[31mNo Users To Delete...\n\e[0m");
                     break;
                 }
                 else
                 {
                     status = delete_by_scan(&start, start);
                     if(status>0)
                         printf("\e[32mUSERID %lu Is Deleted Successfully\n\e[0m",status);
                     else if(status == -2 || status == -1)
                         printf("\e[31mNo Users Found\n\e[0m");
                     else if(status == -4)
                         printf("\e[31mDeletion Rejected\n\e[0m");
                     else
                         printf("\e[31mUnknown ERROR\n\e[0m");
                 }
                 break;
      case '0' : free(start);
                 deinit_FM(handle);
                 goto clean;
      default  : printf("\e[33mInvalid Choice\n\e[0m");
  }
        }
    }
    else
    {
        printf("\e[31minit_FM failed\n\e[0m");
        goto clean;
    }
clean:
    optcap_op(0);
    iodev_op(0);
    return 0;
}
