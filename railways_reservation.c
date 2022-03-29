#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
//***********************************GLOBAL VARIABLES***************************************************
typedef struct passenger_details{
	char name[100];
	int age;
	char gender;
	struct date{
		int dd;
		int mm;
		int yy;
		} d;
}details;
int pnr;
char gs[30];
int num_of_seats;
int train_num;

//************************************FUNCTION_PROTOTYPES************************************************
int login_system();
void view_trains(void);
void reservation(void);
float charge(int,int);
void train_details(int);
void print_ticket(details,int,int,float);
void pnr_back_to_file(int);
void cancellation(int);


	
//*****************************************MAIN********************************************	

int main()
{
system("cls");
printf("***********************************\n");
printf("WELCOME TO TRAIN TICKET RESERVATION\n");
printf("***********************************\n");

int s;
s=login_system();
int home_page;
int attempt=1;
while(s==1 && attempt<3){
	system("cls");
	printf("***********************************\n");
	printf("WELCOME TO TRAIN TICKET RESERVATION\n");
	printf("***********************************\n");
	attempt++;
	s=login_system();
}
printf("\n \n ***error due to multiple attempts*** \n ***try logging in after few time ***\n\n");
if(s==0){

FILE *fp1;
fp1=fopen("pnr.txt","r");
fgets(gs,30,fp1);
pnr=atoi(gs);	

start:
system("cls");
printf("1 -> Book a Ticket\n\n");
printf("2 -> View Available Trains\n\n");
printf("3 -> Cancel Ticket\n\n");
printf("4 -> Exit\n\n");

printf("Enter a number:");
scanf("%d",&home_page);
switch(home_page)
{
	case 1:
	system("cls");
	printf("\n\n\t\t WELCOME TO TICKET RESERVATION \t\t\n\n");
	printf("\n\t\t PLEASE ENTER YOUR DETAILS BELOW\n\n");
	reservation();
	break;
	
	case 2:
	system("cls");
	FILE *t;
	char str;
	printf("\nReading an existing file:");
	printf("\nInput file to be opened:\n");
	t = fopen("view_trains.txt","r");
	if(t==NULL)
		{
			printf("\nFile does not exist");
			exit(0);
		}
	str = fgetc(t);
	while(str!=EOF)
	{
		printf("%c",str);
		str = fgetc(t);
	}
	fclose(t);
	printf("\n********Press any key to go back Menu***********");
	getch();
	break;

	case 3:
	system("cls");
	int cancel_pnr_id;
	printf("\nEnter your pnr number\n");
	scanf("%d",&cancel_pnr_id);
	cancellation(cancel_pnr_id);
	printf("\n\n*******TICKET CANCELLATION SUCCESSFULL********\n********THANK YOU\n*******");
	printf("****\n\npress any key to go back to main menu\n\n****");
	getch();
	break;

	case 4:
	pnr_back_to_file(pnr);
	return 0;

	default:
	printf("\nInvalid Choice");
}
goto start;
return 0;
}
}
//********************************************************************************
void reservation(void)
{
	char confirm;
	int i=0;
	int j=0;
	int k=0;	
	int max1;
	float charges;
	details pd;
	char ch;
	FILE *fp;
	fp=fopen("reserved_seats.txt","a");
	fflush(stdin);
	printf("enter your name : ");
	scanf("%[^\n]s",&pd.name);
	fflush(stdin);
	printf("\n \n enter the gender (M/F) :>");
	scanf("%c",&pd.gender);
	printf("\n \n enter your age :>");
	scanf("%d",&pd.age);
	printf("\n \nenter the date in the form of dd/mm/yyyy : ");
	start:
	scanf("%d %d %d",&pd.d.dd,&pd.d.mm,&pd.d.yy);
	if(pd.d.mm==1 || pd.d.mm==3 || pd.d.mm==5 || pd.d.mm==7 || pd.d.mm==8 || pd.d.mm==10 || pd.d.mm==12)
max1=31;

else if(pd.d.mm==4 || pd.d.mm==6 || pd.d.mm==9 || pd.d.mm==11)
max1=30;

else if(pd.d.yy%4==0 && pd.d.yy%100!=0 || pd.d.yy%400==0)
max1=29;

else
{
max1=28;
}
if(pd.d.mm>=1 && pd.d.mm<=12 && pd.d.dd>=1 && pd.d.dd<=max1)
{
printf("valid date\n");
}
else
{

printf("invalid date\n");
printf("\n \n Try entering the date in the form of dd/mm/yyyy : ");
while(j<3){
		j++;
		goto start;
		}

printf("\n\n**************ERROR DUE TO INVALID DATE *************\n\n");
printf("\n\n		TRY BOOKING THE TICKET AGAIN		\n\n");
		printf("\n********Press any key to go back Menu***********");
		
}


if(pd.d.mm>=1 && pd.d.mm<=12 && pd.d.dd>=1 && pd.d.dd<=max1)
{
	printf("\n \nenter the num of seats to be reserved :>");
	scanf("%d",&num_of_seats);
	printf("\n\n ** press any key to view availabe train details**\n\n");
	getch();
	system("cls");
	FILE *t;
	char str;
	//printf("\nReading an existing file:");
	//printf("\nInput file to be opened:\n");
	t = fopen("view_trains.txt","r");
	if(t==NULL)
		{
			printf("\nFile does not exist");
			exit(0);
		}
	str = fgetc(t);
	while(str!=EOF)
	{
		printf("%c",str);
		str = fgetc(t);
	}
	fclose(t);
	printf("\n\n enter the train num : ");
	start1:
	scanf("%d",&train_num);

	if(train_num >= 100 && train_num <= 114)
	{
		charges=charge(train_num,num_of_seats);
		pnr=pnr+1;
		print_ticket(pd,train_num,num_of_seats,charges);
	}
	else
	{
		printf("\n\n Invalid train number !!! try entering again ");
		printf("\n\n enter the train num : ");
		while(i<3){
		i++;
		goto start1;
		}
		printf("\n\nERROR DUE TO TOO MANY ATTEMPTS !!! TRY AFTER SOMETIMES\n\n");
		printf("\n********Press any key to go back Menu***********");
		getch();
		
	}
if(train_num >= 100 && train_num <= 114)
{
start2:
printf("\n\n CONFIRM TICKETS (Y/N) :> ");
fflush(stdin);
scanf("%c",&confirm);
if((confirm=='y')||(confirm == 'Y'))

{

	fprintf(fp,"%d\t %d-%d-%d\t %d\t %s\t %d\t %.2f\n",pnr,pd.d.dd,pd.d.mm,pd.d.yy,train_num,pd.name,num_of_seats,charges);
	printf("------**********--------");
	printf("\n RESERVATION DONE SUCCESSFULLY \n");
	printf("------**********--------");
	printf("\n********Press any key to go back Menu***********");
}
else if((confirm == 'n') || (confirm == 'N'))
{
	printf("\n reservatin not done!!! \n press any key to go back to main menu\n");
}
else
{	
	printf("\n Invalid choice!!! try entering again ------->\n");
	while(k<3)
	{
		k++;
		goto start2;
	}
	printf("\nsorry reservation not completed\n");
	printf("\n********Press any key to go back Menu***********");
}
	
}
}
fclose(fp);
getch();
}

	
//*******************************CHARGES***************************************************
float charge(int train_num,int num_of_seats)
{
	if(train_num == 100)
	{
		return (1200.0*num_of_seats);
	}
	if(train_num == 101)
	{
		return (1800.0*num_of_seats);
	}
	if(train_num == 102)
	{
		return (1650.0*num_of_seats);
	}
	if(train_num == 103)
	{
		return (900.0*num_of_seats);
	}
	if(train_num == 104)
	{
		return (2200.0*num_of_seats);
	}
	if(train_num == 105)
	{
		return (1440.0*num_of_seats);
	}
	if(train_num == 106)
	{
		return (1105.0*num_of_seats);
	}
	if(train_num == 107)
	{
		return (1575.0*num_of_seats);
	}
	if(train_num == 108)
	{
		return (1350.0*num_of_seats);
	}
	if(train_num == 109)
	{
		return (2870.0*num_of_seats);
	}
	if(train_num == 110)
	{
		return (1490.0*num_of_seats);
	}
	if(train_num == 111)
	{
		return (2000.0*num_of_seats);
	}
	if(train_num == 112)
	{
		return (1950.0*num_of_seats);
	}
	if(train_num == 113)
	{
		return (1300.0*num_of_seats);
	}
	if(train_num == 114)
	{
		return (2990.0*num_of_seats);
	}
}

//******************************PRINT_TICKET******************************************
void print_ticket(details pd,int train_num,int num_of_seats,float charges)
{
printf("\n----------------------------\n");
printf("\n \t\t TICKET \t\t \n");
printf("\n----------------------------\n");
printf("\n\n \tDATE:%d/%d/%d",pd.d.dd,pd.d.mm,pd.d.yy);
printf("\n\n NAME:%s \t\t AGE : %d\t\t GENDER : %c",pd.name,pd.age,pd.gender);
printf("\n\n TRAIN_NUM :%d",train_num);
printf("\n\n PNR:%d",pnr);
train_details(train_num);
printf("\n\n NUM_OF_SEATS : %d \t\t CHARGES:%f",num_of_seats,charges);
}



//*****************************TRAIN_DETAILS***************************************
void train_details(int train_num)
{
	if(train_num == 100)
	{
		printf("\n Name : \t\t Delhi express");
		printf("\n Destination : \t\t Howrah to New Delhi");
		printf("\n Depature time: \t\t 17:05");
	}
	if(train_num == 101)
	{
		printf("\n Name : \t\t Delhi express");
		printf("\n Destination : \t\t Mumbai central to New Delhi");
		printf("\n Depature time: \t\t 17:30");
	}
	if(train_num == 102)
	{
		printf("\n Name : \t\t Delhi express");
		printf("\n Destination : \t\t Ahmedabad to New Delhi");
		printf("\n Depature time: \t\t 18:20");
	}
	if(train_num == 103)
	{
		printf("\n Name : \t\t Hyderabad express");
		printf("\n Destination : \t\t Bengaluru to Hyderabad");
		printf("\n Depature time: \t\t 10:20");
	}
	if(train_num == 104)
	{
		printf("\n Name : \t\t Delhi express");
		printf("\n Destination : \t\t Bengaluru to New Delhi");
		printf("\n Depature time: \t\t 20:30");
	}
	if(train_num == 105)
	{
		printf("\n Name : \t\t Delhi express");
		printf("\n Destination : \t\t New Delhi to Dibrugarh");
		printf("\n Depature time: \t\t 16:45");
	}
	if(train_num == 106)
	{
		printf("\n Name : \t\t Delhi express");
		printf("\n Destination : \t\tNew Delhi  to Bilaspur");
		printf("\n Depature time: \t\t 16:00");
	}
	if(train_num == 107)
	{
		printf("\n Name : \t\t Delhi express");
		printf("\n Destination : \t\t Bubaneshwar to New Delhi");
		printf("\n Depature time: \t\t 10:00");
	}
	if(train_num == 108)
	{
		printf("\n Name : \t\t Delhi express");
		printf("\n Destination : \t\t New Delhi to Jammu Tawi");
		printf("\n Depature time: \t\t 21:10");
	}
	if(train_num == 109)
	{
		printf("\n Name : \t\t Chennai express");
		printf("\n Destination : \t\t New Delhi  to chennai");
		printf("\n Depature time: \t\t 16:00");
	}
	if(train_num == 110)
	{
		printf("\n Name : \t\t Ranchi express");
		printf("\n Destination : \t\t New Delhi to Ranchi");
		printf("\n Depature time: \t\t 15:30");
	}
	if(train_num == 111)
	{
		printf("\n Name : \t\t Madgaon express");
		printf("\n Destination : \t\t New Delhi to madgaon");
		printf("\n Depature time: \t\t 11:25");
	}
	if(train_num == 112)
	{
		printf("\n Name : \t\t Delhi express");
		printf("\n Destination : \t\t  New Delhi to Secundeabad");
		printf("\n Depature time: \t\t 16:00");
	}
	if(train_num == 113)
	{
		printf("\n Name : \t\t Bengaluru express");
		printf("\n Destination : \t\t Chennai to Bengaluru");
		printf("\n Depature time: \t\t 06:35");
	}
	if(train_num == 114)
	{
		printf("\n Name : \t\t Delhi express");
		printf("\n Destination : \t\t Agartala to New Delhi");
		printf("\n Depature time: \t\t 19:00");
	}

}


//********************************LOGIN_FORM*************************************
int login_system()
{
int i;
int comparision=0;
char user_name[25];//to get the username
char user[][25]={"sailaja","rachana","sarveksha"};
char password[25];//to get the password
char pass[][25]={"pass1","pass2","pass3"};
char ch;

printf("\n Enter the user name : ");
scanf("%s",user_name);

printf("\n Enter the password : ");
i=0;
while(1)
{
	ch=getch();
	if(ch=='\r')
	{
	break;
	}
	else if(ch=='\b')
	{       if(i!=0) // to avoid the ENTER instructions getting deleted 
		{
			printf("\b");  // backspace to move cursor one pos back
			printf("%c",32);/*making the char invisible which was entered when backspace is pressed ,32 ascii val of char space*/
			printf("\b"); // backspace to move cursor one pos back
			i--;
			password[i]='\0';
		}
		else
		{
		continue;
		}

	}
	else
	{
	putchar('*');// char - '*' will be printed instead of the entered character 
	password[i]=ch;
	i++;
	}
}
password[i]='\0';


for(i=0;i<=2;i++)
{
	if((strcmp(user_name,user[i]))==0 && (strcmp(password,pass[i]))==0)
	{
		comparision=1;
		break;
	}
}
if(comparision) 
{
printf("\n \n *****Login successful!******");
printf("\n ------press any key to continue------");
getch();
return 0;
}
else 
{
printf("\n \n XXX  Incorrect username or password   XXX\n\n");
printf("\n*****press any key to go back and try logging in again***** ");
getch();
return 1;
}
printf("\n \n -----> Enter to continue <-----");
getch();
}

//******************************************************************************************


void pnr_back_to_file(int pnr)
{
	FILE*fp4=fopen("pnr.txt","w");
	itoa(pnr,gs,10);
	fputs(gs,fp4);
}
//******************************************CANCELLATION***************************************************
void cancellation(int cancel_pnr_id)
{
	FILE*fp5=fopen("reserved_seats.txt","r");
	FILE*fp6=fopen("temp.txt","w");
	char s1[500];
	char str[30];
	char s2[500];
	while(fgets(s1,500,fp5)!=NULL)
	{
		strcpy(s2,s1);
		char *val=strtok(s2,"\t");
		
		if(cancel_pnr_id != atoi(val))
		{
			
			fprintf(fp6,"%s",s1);
		}
                val=strtok(NULL,"\t");

	}
	fclose(fp5);
	fclose(fp6);
	remove("reserved_seats.txt");
	rename("temp.txt","reserved_seats.txt");

}



