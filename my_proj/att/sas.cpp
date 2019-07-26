#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
using namespace std;
class office {
	public : 
		void off_menu();
		int off_in();
		int off_out();
		int off_show();
		int off_check(char *);
	};
int office :: off_check(char *data)
{
	int ret=5;
	char cmd[50];
        sprintf(cmd,"grep -qw %s bd",data);
        ret=system(cmd);
        if(ret==0)
                return 1;
        else
                return -1;
}	
int office :: off_in()
{
	char strin[10];
	FILE *fi;
	fi=fopen("db","a");
	if(fi==NULL)
	{
		cout<<"Error";
		return -1;
	}
	cout<<"Enter in time : ";
	cin>>strin;
	fputs(__DATE__"\t\t",fi);
	fputs(strin,fi);
	fputs("\n",fi);
	fclose(fi);
	FILE *fc;
}
int office :: off_out()
{
	char strout[10];
	FILE *fo;
	fo=fopen("db","a");
	if(fo==NULL)
	{
		cout<<"Error";
		return -1;
	}
	cout<<"Enter out time : ";
	cin>>strout;
	fputs(__DATE__"\t\t",fo);
	fputs(strout,fo);
	fputs("\n",fo);
	fclose(fo);
}
void office :: off_menu()
{
	char choice;
	cout<<"'i' : office_in\n'o' : office_out\n's' : office_show\n";
	cout<<"Enter your choice : ";
	cin>>choice;
	switch(choice)
	{
		case 'i' : if(office :: off_check())
				cout<<"Already Checked IN\n"
			   else
				office :: off_in();
			   break;
		case 'o' : if(off_check())
                                cout<<"Already Checked OUT\n"
                           else
                                office :: off_out();
                           break;
		case 's' : office :: off_show();break;
		default : cout<<"Invalid selection\n";
	}
		
}
int office :: off_show()
{
	int ch;
	FILE *fs;
	fs=fopen("db","r");
        if(fs==NULL)
        {
                cout<<"Error";
                return -1;
        }
	cout<<"\e[32mDate\t\t\tIN\t\t\tOUT\e[0m\n";
	while((ch=fgetc(fs))!=EOF)
	printf("%c",ch);
	cout<<endl;
}
int main()
{
	office off1;
	off1.off_menu();
}
