#ifndef __HEADER_H__
#define __HEADER_H__
#include"header.h"
#endif
void Admin()
{



}
int BioReadDB()
{
    FILE *fp;
    int status;
    user_t *tmp;
    head = NULL;

    fp = fopen (DBFILE, "rb");
    if (fp == NULL)
    {
        printf("\e[31mError opening database file : %s\e[0m\n", DBFILE);
        return -1;
    }

    tmp = (user_t *)calloc(10, sizeof(user_t));

    while(status = fread(tmp, sizeof(user_t), 1, fp))
    {
        printf("fread =%d\n", status);
        if(tmp->userid)
        {
            head = (user_t *)enrol_user(tmp->userid, tmp->username, 
                    tmp->buffer, tmp->bufferlength);
        }
    }
    status = feof(fp);
    if(status > 0)
    {
        printf("\e[32mDatabase read successfully ! DB : %s \e[0m\n", DBFILE);
        fclose(fp);
        return 0;
    }
    else
    {
        printf("\e[31mDatabase read failed !\e[0m\n");
        fclose(fp);
        return -2;
    }
}
int BioWriteDB(user_t *tmp, int mode)
{
    FILE *fp;
    int status;
    if(tmp == NULL || tmp == 0)
    {
        if(mode == 2)
        {
            fp = fopen(DBFILE, "wb");
            printf("\e[32mContents to database written successfully !\e[0m\n");
            fclose(fp);
            BioReadDB();
            return 0;
        }
        else
        {
            printf("\e[34mNothing to write to Database\e[0m\n");
            return -1;
        }
    }
    if(mode == 2)
        fp = fopen(DBFILE, "wb");
    else
        fp = fopen(DBFILE, "ab");

    if(fp == NULL)
    {
        printf("File open error\n");
        return -2;
    }
    user_t *tmpdb;
    tmpdb = tmp;
    while(tmpdb != NULL)
    {
        status = fwrite(tmpdb, sizeof(user_t), 1, fp);
        tmpdb = tmpdb->next;
    }
    if(status > 0)
    {
        printf("\e[32mContents to database written successfully !\e[0m\n");
        fclose(fp);
        BioReadDB();
        return 0;
    }
    else
    {
        printf("\e[31mError writing database !\e[0m\n");
        fclose(fp);
        return -3;
    }
}
