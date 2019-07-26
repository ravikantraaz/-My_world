#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<ctype.h>
int temp=0;
char names[50];
char namec[50];
char usr[50];
using namespace std;
class bank {
	char name[20],name1[20],mobile[11],mobile1[11];
	char email[30],email1[30],pass[15],pass1[15];
	public :
		void signup();
		void signin();
		void banking();
		void save(int);
		void casec(char *);
		int uinfo(char *,char *);
		int validate(char *);
		void atm();
		void atm_menu();
		void bank_menu();
		void balance();
		void ministat();
		void withdrawal();
		void deposit(char *,char *);
};
void bank :: atm_menu()
{
	cout<<"\e[32mb : balance\n\e[33mw : withdrawal\n\e[34md : deposit\n\e[35mm : ministatement\n\e[31mq : quit\n\e[36mEnter your option : \e[0m";
}
void bank :: bank_menu()
{
	cout<<"\e[32mS : Sign up"<<endl<<"\e[33ms : sign in"<<endl<<"\e[34ma : atm"<<endl<<"\e[31mq : quit"<<endl<<"\e[35mEnter your choice : \e[0m";
}
void bank :: withdrawal()
{
	
}
void bank :: deposit(char *na,char *pa)
{
	cout<<*na<<*pa;
	int resp,count=0,amount=0,amt=0;
	FILE *df;
	df=fopen(na,"r+");
	cout<<"Enter amount to deposit : ";
	cin>>amount;
	if(df==NULL)
	{
		cout<<"Error\n";
		return;
	}
	while((resp=fgetc(df))!=EOF)
	{
		if(resp==':')
			count++;
		else if(count==5)
		{
			printf("%d %c",resp,resp);
			fputs(amount,df);
		}
		else ;
	}
	//cout<<amt<<endl;
	cout<<endl;
	fclose(df);
}
void bank :: ministat()
{
	
}
void bank :: balance()
{
	
}
void bank :: casec(char *ptr)
{
	int l=0,m=0;
	while(ptr[l])
	{
		if(ptr[l]>='a' && ptr[l]<='z')
			namec[m++]=ptr[l]-32;
		else if(ptr[l]>='A' && ptr[l]<='Z')
			namec[m++]=ptr[l];
		else ;
		l++;
	}
}
void bank :: atm()
{
	char name3[30]={0},pass3[30]={0};
	int ret;
	cout<<"Enter your UID/username: ";
	cin>>name3;
	cout<<"Enter your password: ";
	cin>>pass3;
	if(ret=uinfo(name3,pass3)==1)
		;
	else 
	{
		cout<<"\e[31musername/password incorrect\e[0m\n";
		return ;
	}
	char opt;
	cout<<"\e[32mWelcome to atm\e[0m\n";
	while(1)
	{
		atm_menu();
		scanf(" %c",&opt);
		switch(opt)
		{
			case 'b' : balance();break;
			case 'w' : withdrawal();break;
			case 'd' : deposit(name3,pass3);break;
			case 'm' : ministat();break;
			case 'q' : return;
			default : cout<<"Wrong option"<<endl;
		}
	}
}
int bank :: validate(char *data)
{
	int ret=5;
	char cmd[50];
	sprintf(cmd,"grep -qw %s database",data);
	ret=system(cmd);
	if(ret==0)
		return -1;
	else
		return 1;
}
void bank :: signup()
{
	char res;
	int ret,amt=0;
	char kmd[50]={0};
	sprintf(kmd,"if [ -f database ];then return 0;else return 1;fi");
	ret=system(kmd);
	if(ret==0)
		cout<<"\e[32mdatabase file present\e[0m\n";
	else
	{
		cout<<"\e[33mdatabase file not present : creating a dummy one\e[0m\n";
		system("touch database");
	}
	
	cout<<"Fields marked with (\e[31m*\e[0m) are mandatory :"<<endl;
	N:cout<<"Enter your name\e[31m*\e[0m: ";
	cin>>name;
	cout<<"Confirm your name: ";
	cin>>name1;
	if(strcmp(name,name1)==0)
		cout<<"\e[32m Name matched \e[0m"<<endl;
	else
	{
		cout<<"\e[31m Name not matched: \e[0m"<<endl;
		goto N;
	}

	M:cout<<"Enter your Mobile No.\e[31m*\e[0m: ";
	cin>>mobile;
	cout<<"Confirm your Mobile No.: ";
	cin>>mobile1;

	res=validate(mobile);
	if(res==-1)
	{
		cout<<"\e[35mMobile number already registered\e[0m"<<endl;
		goto M;
	}
	res=5;

	if(strcmp(mobile,mobile1)==0)
		cout<<"\e[32m Mobile No. matched \e[0m"<<endl;
	else
	{
		cout<<"\e[31m Mobile No. not matched: \e[0m"<<endl;
		goto M;
	}

	E:cout<<"Enter your e-mail\e[31m*\e[0m: ";
	cin>>email;
	cout<<"Confirm your e-mail: ";
	cin>>email1;

	res=validate(email);
	if(res==-1)
	{
		cout<<"\e[35mEmail id already registered\e[0m"<<endl;
		goto E;
	}

	if(strcmp(email,email1)==0)
			cout<<"\e[32m Email matched \e[0m"<<endl;
	else
	{
		cout<<"\e[31m Email not matched: \e[0m"<<endl;
		goto E;
	}
	system("stty -echo");
	P:cout<<"Enter new password\e[31m*\e[0m: ";
	cin>>pass;
	cout<<"Confirm your password: ";
	cin>>pass1;
	system("stty echo");
	if(strcmp(pass,pass1)==0)
			cout<<"\e[32m Password matched \e[0m"<<endl;
	else
	{
		cout<<"\e[31m Password not matched: \e[0m"<<endl;
		goto P;
	}
	cout<<"Your details: "<<endl;
	cout<<"Name: "<<name<<endl<<"Mobile: "<<mobile<<endl<<"Email: "<<email<<endl<<"Pass: "<<pass<<endl;
	cout<<"\e[32mPress \"s\" for signup or \"c\" for cancel: \e[0m";
	scanf(" %c",&res);
	temp=1;
	if(res=='s')
		save(amt);
	else if(res=='c')
		cout<<"\e[31mSignup canceled\e[0m"<<endl;
	else
		cout<<"\e[31mSignup failed\e[0m"<<endl;
}
void bank :: signin()
{
	FILE *fd;
	char name2[30]={0},pass2[11]={0},uid_uid[50]={0},uid_email[50]={0},uid_mobile[50]={0},uid_pass[50]={0},uid_bal[50]={0};
	int ret=0,chh=0,ct=0,flag=0,flag1=0,flag2=0,flag3=0,flag4=0,c,cnt,i=0,j=0,k=0,n=0,o=0;
	cout<<"Enter your UID/username: ";
	cin>>name2;
	cout<<"Enter your password: ";
	cin>>pass2;
	ret=uinfo(name2,pass2);
	if(ret==1)
	{
		fd=fopen(name2,"r");
		if(fd!=NULL)
		{
			while((chh=fgetc(fd))!=EOF)
			{
				if(chh==':')
					ct++;
				else ;
				//////////////////////////
				if(ct==1)
				{
					if(flag1==1)
						uid_email[i++]=chh;
					else flag1=1;
				}
				else ;
				if(ct==2)
				{
					if(flag2==1)
						uid_mobile[j++]=chh;
					else flag2=1;
				}
				else ;
				if(ct==4)
				{
					if(flag3==1)
						uid_uid[k++]=chh;
					else flag3=1;
				}
				else ;
				if(ct==5)
				{
					if(flag4==1)
						uid_bal[o++]=chh;
					else flag4=1;
				}
				else ;
				//////////////////////////
				if(ct==3 && flag==1)
				{
					uid_pass[n++]=chh;
					//printf("*");
				}
				else
				{
					//printf("%c",chh);
					if(ct==3)
						flag=1;
					else ;
				}
			}
		}
	fclose(fd);
//////////////////////////Printing_Info/////////////////////////////
casec(names);
memset(uid_pass,'*',sizeof(strlen(uid_pass)));
strcat(usr,names);
strcat(usr,uid_uid);
cout<<"\n\n+------------------------------------------------------------------------------------------------------+\n";//120
printf("*%55s\e[1;33m%-47s\e[0m*\n","Welcome Mr/s. : ",namec);
printf("*%10s\e[1;33m%-20s\e[0m%5s\e[1;33m%-4s\e[0m%38s\e[1;33m%-24s\e[0m%c\n","Name : ",names,"UID : ",uid_uid,"Username : ",usr,'*');
printf("*%10s\e[1;33m%-17s\e[0m%9s\e[1;33m%-25s\e[0m%17s\e[1;33m%-10s\e[0m%15c\n","Mobile : ",uid_mobile,"E-mail : ",uid_email,"Pass : ",uid_pass,'*');
printf("*%10s\e[1;33m%-20s\e[0m%73c","bal : ",uid_bal,'*');
cout<<"\n+------------------------------------------------------------------------------------------------------+\n\n";//120
////////////////////////////////////////////////////////////////////
	}
	else if(ret==-1)
		cout<<"\e[31mUsername/password Invalid\e[0m";
	cout<<endl;
	memset(usr,'\0',sizeof(usr));
	memset(names,'\0',sizeof(names));
	memset(namec,'\0',sizeof(namec));
}
int bank :: uinfo(char *n,char *p)
{
	int ch=0,cnt=0,i=0;
	FILE *FP;
	FP=fopen(n,"r");
	if(FP==NULL)
		return -1;
	while((ch=fgetc(FP))!=EOF)
	{
		if(ch==':')
			cnt++;
		else if(cnt==0)
			names[i++]=ch;
		else if(cnt==3)
		{
			if(ch==*p++)
				;
			else
				break;
		}
		else ;		
	}
	if(((*p)!='\0') || (ch!=EOF))
	{
		fclose(FP);
		return -1;
	}
	fclose(FP);
return 1;
}
void bank :: banking()
{
	char choice;
	while(1)
	{
		bank_menu();
		scanf(" %c",&choice);
		switch(choice)
		{
			case 'S' : bank :: signup();break;
			case 's' : bank :: signin();break;
			case 'a' : bank :: atm();break;
			case 'q' : return;
			default  : cout<<"Wrong choice"<<endl;
		}
	}
}
void bank :: save(int amount)
{
	FILE *fp;
	FILE *fdb;
	static int uid=1000;int ret;
	if(temp==0)
	{
		cout<<"Nothing to save"<<endl; return;
	}
	
	fp=fopen(name,"w");

	fputs(name,fp);
	fputs(":",fp);

	fputs(email,fp);
	fputs(":",fp);

	fputs(mobile,fp);
	fputs(":",fp);

	fputs(pass,fp);
	fputs(":",fp);

	char pmd[50];
	while(1)
	{
		sprintf(pmd,"if [ -f %d ];then return 0;else return 1; fi",uid);
		ret=system(pmd);
		if(ret==0)
			//uid++;
			{srand(time(NULL));
			 uid=rand()%1000+1000;}
		else
			break;
	}
////////////Random//////////////
	srand(time(NULL));
	uid=rand()%1000+1000;
///////////////////////////////
	char rmd[50];
	sprintf(rmd,"%d",uid);
	fputs(rmd,fp);
	fputs(":",fp);
///////////amount/////////////
	char amd[50];
	sprintf(amd,"%d",amount);
	fputs(amd,fp);
	fclose(fp);	
//////////////////////
	char tmd[50];
	char name_uid[50];
	sprintf(name_uid,"%s%d",name,uid);
	sprintf(tmd,"mv %s %s%d",name,name,uid);
	system(tmd);
//////////////creating UID//////////////////////
	char lmd[50];
	sprintf(lmd,"ln -s %s %d ",name_uid,uid);
	if(ret=system(lmd)==0)
	{
		cout<<"\e[32mUID created with : \e[33m"<<uid<<"\e[33m --> \e[34m"<<name_uid<<" for \""<<name<<"\" :\e[0m"<<endl;
	}
	else
		cout<<"UID not created"<<endl;
/////////////////////////////////////////
	char smd[50];
	sprintf(smd,"%d",uid);

	fdb=fopen("database","a+");
	fputs(mobile,fdb);
	fputs(":",fdb);
	fputs(email,fdb);
	
	fputs(":",fdb);
	fputs(smd,fdb);

	fputs("\n",fdb);
	fclose(fdb);

	temp=0;
	cout<<"\e[32mSignup success...\e[0m\n";
}
int main()
{
	bank b;
	b.banking();
return 0;
}
