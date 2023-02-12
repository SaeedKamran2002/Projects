#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#include<time.h>
#include<windows.h>
//*******************************************FUNCTION LIST*************************************************
void customer();
void login();
void manager();
void completeOrder();
void checkOrder();
void buyerDetails();
void supplierDetails();
void chemicalList();
void bankwork();
void addBank();
void addDebit();
void addCredit();
void checkDebit();
void checkCredit();
void bankStatement();
//****************************************** GOTOXY FUNCTION & Time & Date & text color & Comapny Name*************************************************
COORD coord = {0, 0};
void gotoxy(int x, int y)
{
 	COORD coord;
 	coord.X = x;
 	coord.Y = y;
 	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void textcolor(int x){
	HANDLE hconsole;
	hconsole=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hconsole, x );	
}

int t(void){
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
	gotoxy(90,2);
	textcolor(245);
	printf("Date : %s",__DATE__);
	gotoxy(90,3);
	printf("Time : %s",__TIME__);
	textcolor(240);
	return 0;
}

void compName()
{
	printf("\t\t\t\t\t\t*****************************\n");
	printf("\t\t\t\t\t\t    Pak Chemicals Pvt Ltd\t\t\n");
	printf("\t\t\t\t\t\t*****************************\n");
	
	printf("\n");
}

void company()
{	
	printf("\t\t\t\t\t\t*****************************\n");
	printf("\t\t\t\t\t\t    Pak Chemicals Pvt Ltd\t\t\n");
	printf("\t\t\t\t\t\t*****************************\n");
	
	printf("\n");
}

//******************************************STRUCTURE*******************************************************
struct CUSTOMER
	{
		char order[50],name[50];
		float quantity, rate, rate2 , profit;
		char quality;
		char sup[30];
	}cust;
	
struct CHEMICAL{
	char chemical[30];
	char sup[30];
	char supMob[30];
}supl;

struct bank{
	char bankName[30];
	char accountNo[30];
};

struct debit{
	int day , month , year;
	char name[30];
	char nameofbank[30];
	char amountType[10];
	float amount;
};

struct credit{
	int day , month , year;
	char name[30];
	char nameofbank[30];
	char amountType[10];
	float amount;
};
//******************************************Global Variables*******************************************************
char yesNo;
//*********************************************Main Function*******************************************************
int main()
{
	system("COLOR 7C");
	textcolor(112);
	login();
}
//*******************************************LOGIN************************************************
void login()
{
	textcolor(112);
	int task, attemp=3 , p=0;
	char user[20]={"admin"};
	char pas[20]={"admin"};
	char pasword[20],username[20]; 
	
	company();
	
		
	printf("\t\t 1. Customer\n");
	printf("\t\t 2. Manager\n");
	printf("\t\t 3. Exit\n");
	
	printf("\n\n\t\tTo Perform The Given Task Enter The Number :  ");
	scanf("%d",&task);
	
	system("cls");
	
	if(task==1)
	{
		customer();
	}
	
	else if(task==2)
	{
    	int a=0,i=0;
    	char uname[10],c=' '; 
    	char pword[10],code[10];
    	char user[10]="admin";
    	char pass[10]="admin";
    	do
		{
			company();
    		printf(" \n\n \t\t\t\t                    USERNAME = ");
			scanf("%s", &uname); 
			printf(" \n\n \t\t\t\t                    PASSWORD = ");
			while(i<10)
			{
	    		pword[i]=getch();
	    		c=pword[i];
	    		if(c==13)
				{
					 break;
				}
	    		else
				{
					printf("*");
	    			i++;
	    		}
			}
			pword[i]='\0';
			i=0;
			
			if(strcmp(uname,"admin")==0 && strcmp(pword,"admin")==0)
			{
				printf("  \n\n\n \t\t         WELCOME TO PAK CHEMICAL MANAGEMENT SYSTEM !!!! YOUR LOGIN IS SUCCESSFUL");
				textcolor(242);
				printf("\n\n\n\t\t\t                       Press any key to continue...");
				getch();//holds the screen
				manager();
			}
			else
			{
				textcolor(252);
				printf("\n\n\n\t\t\t        SORRY !!!!  LOGIN IS UNSUCESSFUL!");
				a++;
			
				getch();//holds the screen
			
			}
			system("cls");
		}
		while(a<=2);
		if (a>2)
		{
			printf("\n\t\t\tSorry you have entered the wrong username and password for four times!!!");
			getch();//holds the screen
		}
		system("cls");
	}
	else
	{
		sleep(3);
		exit(1);
	}
}
//*******************************************COUSTOMER FUNCTION*************************************
void customer()
{
	
	system("cls");
    char ch;
    int i=1;
	int orderNumber=i;//order number
	A:

    //*********************************A************************************

	company();//titile screen
	FILE*fptr;
	fptr = fopen("Customer.txt","a");
	
	printf("\t\tEnter your Name:");
	scanf("%s",&cust.name);//name
	
	printf("\n\t\tOrder number : %d\n\n",orderNumber);//order number
	
	printf("\t\tEnter Item Name :");
	scanf("%s",&cust.order);//chemical name
	
	printf("\t\tEnter Quantity :");
	scanf("%f",&cust.quantity);//quantity
	
	printf("\t\tEnter Quality [A/B/C] : ");
	scanf(" %c",&cust.quality);//quality
	
	orderNumber++;
	
	fprintf(fptr,"%s\n %s\n %f\n %c\n %f\n %f\n %s\n\n",cust.name,cust.order,cust.quantity,cust.quality,cust.rate=0,cust.rate2=0,cust.sup);
	printf("\n\n\n\n\t\t\t***********Order Confirmed Sucessfully*****************");
	fclose(fptr);
	
	B://********************************B***************************************
	
	printf("\n\n\t\tFor More Entries Enter Y for Yes And N For No : ");
	scanf(" %c",&ch);
	
	if(ch=='n'||ch=='N')
	{
		system("cls");
        login();
	}
	else if(ch=='y'||ch=='Y')
	{
		system("cls");
		goto A;
	}
	else
	{
		printf("choose valid option.....");
		goto B;
	}			
}
//******************************************MANAGER**************************************************
void manager()
{
	int task;
	system("cls");
	company();
	textcolor(240);
	
	t();
	
	printf("\t\t\t\t\t\t\t\t\t     ---------------\n");
	printf("\t\t\t\t\t\t        Main Menu\t\t\n");
	printf("\t\t\t\t\t\t     ---------------\n");
	
	printf("\n");
	printf("\n");
	
	printf("\t\t 1. Complete the order\n");
	printf("\t\t 2. Check order\n");
	printf("\t\t 3. Buyer details\n");
	printf("\t\t 4. Supplier details\n");
	printf("\t\t 5. Chemical list\n");
	printf("\t\t 6. Bank\n");
	printf("\t\t 7. Exit");
	
	printf("\n\n\t\tTo Perform The Given Task Enter The Number :  ");
	scanf("%d",&task);
	
	if(task==1)
	{
		completeOrder();
	}
	else if(task==2)
	{
		checkOrder();
	}
	else if(task==3)
	{
		buyerDetails();
	}
	else if(task==4)
	{
		supplierDetails();
	}
	else if(task==5)
	{
		chemicalList();
	}
	else if(task==6)
	{
		bankWork();
	}
	else
	{
		system("cls");
		main();
	}
}
//********************************************COMPLETE ORDER*****************************************
void completeOrder()
{	
	FILE* fptr,*temp,*supp,*order,*buyer;
	fptr=fopen("Customer.txt","r");
	temp=fopen("temp.txt","w");
	supp=fopen("supplier.txt","a+");
	order=fopen("order.txt","a");
	buyer=fopen("buyer.txt","a");
	
	if(fptr==NULL)
	{
		printf("ERROR");
	}
	int orderNum=1;
	
	system("cls");
	company();

    while(fscanf(fptr, "%s\n %s\n %f\n %c\n %f\n %f\n", cust.name, cust.order, &cust.quantity, &cust.quality, &cust.rate, &cust.rate2 ,cust.sup) != EOF)
    {
    	printf("\t\t Order Number : %d\n\n",orderNum++);
    	printf("\t\t Name:%s\n",cust.name);
        printf("\t\t Item Name:%s\n",cust.order);
		printf("\t\t Quantity:%.2f\n",cust.quantity);
		printf("\t\t Quality:%c\n",cust.quality);
		
		printf("\t\t Enter Buying Price:");
		scanf("%f",&cust.rate);  
		   	
		printf("\t\t Enter Selling Price:");
		scanf("%f",&cust.rate2);
		
		printf("\t\t Enter suplier Name:");
		scanf("%s",&cust.sup);
		
		system("cls");
		company();
		
//        fprintf(temp, "%s\n %s\n %f\n %c\n %f\n %f\n %s\n\n", cust.name, cust.order, cust.quantity, cust.quality, cust.rate, cust.rate2, cust.sup);
		fprintf(supp, "%s\n %s\n %f\n %c\n %f\n\n",cust.sup,cust.order,cust.quantity,cust.quality,cust.rate);  
		fprintf(order,"%s\n %s\n %f\n %c\n %f\n %f\n %s\n\n", cust.name, cust.order, cust.quantity, cust.quality, cust.rate, cust.rate2, cust.sup); 
		fprintf(buyer,"%s\n %s\n %f\n %c\n %f\n\n", cust.name,cust.order,cust.quantity,cust.quality,cust.rate2); 
		printf("\n\n\n"); 
	}
    fclose(fptr);
//    fclose(temp);
    fclose(supp);
    fclose(order);
    fclose(buyer);
    remove("Customer.txt");
//	rename("temp.txt", "Customer.txt");
    getche();
    manager();  
}
//*******************************************CHECK ORDER DETAIL*******************************************************
void checkOrder()
{
	int r=9;	
	char sname[20];
	int task;
	
	system("cls");
	company();
	
	FILE*order;
	order=fopen("order.txt","r");
	
		system("cls");
		company();
		
		gotoxy(54,3);
	    printf("----------");
	    
	    gotoxy(54,4);
	    printf("ORDER LIST");
	    
	    gotoxy(54,5);
	    printf("----------");
	    
		gotoxy(1,7);
		printf("Buyer Name");
		
		gotoxy(20,7);
		printf("Supplier Name");
		
		gotoxy(40,7);
		printf("Order");
		
		gotoxy(55,7);
		printf("Quantity");
		
		gotoxy(67,7);
		printf("Quality");
		
		gotoxy(79,7);
		printf("Buying ");
		
		gotoxy(91,7);
		printf("Selling ");
		
		gotoxy(103,7);
		printf("Profit");
		
		printf("\n========================================================================================================================");
		
		while(fscanf(order,"%s\n %s\n %f\n %c\n %f\n %f\n %s\n\n", cust.name,cust.order,&cust.quantity ,&cust.quality,&cust.rate,&cust.rate2,cust.sup)!=EOF)
		{
		 
		 gotoxy(1,r);
		 printf("%s",cust.name);
		 gotoxy(20,r);
		 printf("%s",cust.sup);
		 gotoxy(40,r);
		 printf("%s",cust.order);
		 gotoxy(55,r);
		 printf("%.2f",cust.quantity);
		 gotoxy(67,r);
		 printf("%c",cust.quality);
		 gotoxy(79,r);
		 printf("%.2f",cust.rate);
		 gotoxy(91,r);
		 printf("%.2f",cust.rate2);
		 gotoxy(103,r);
		 printf("%.2f",(cust.rate2-cust.rate)*cust.quantity);
		 
		 r++;
		}
		fclose(order);
		getche();
		manager();
}
		
//****************************************** CHECK BUYER DETAIL********************************************************
void buyerDetails()
{
	int task;
	int i=1,r=9;
	char bname[20];
	
	system("cls");
	company();
	
	
	FILE*buyer;
	buyer=fopen("buyer.txt","r");
	
	if(buyer==NULL)
	{
		printf("Error");
		exit(0);
	}
	
	printf("\n\t\t 1. Display Full List");
     printf("\n\t\t 2. Search by name");
     printf("\n\t\t 3. Exit");
     
     printf("\n\n\t\tTo Perform The Given Task Enter The Number :  ");
	 scanf("%d",&task);
     fflush(stdin);
     
     if(task==1)
     {
     	system("cls");
		company();
     	
     	gotoxy(54,3);
	    printf("-------------");
        gotoxy(54,4);
        printf("BUYER DETAILS");
	    gotoxy(54,5);
        printf("-------------");
     	
    
     	 gotoxy(30,7);
		 printf("Name");
		 
		 gotoxy(45,7);
		 printf("Item Name");
		 
		 gotoxy(60,7);
		 printf("Quantity");
		 
		 gotoxy(75,7);
		 printf("Quality");
	
		 gotoxy(90,7);
		 printf("Selling Price");
		 
		 gotoxy(30,8);
		 printf("=========================================================================");
		 
        while(fscanf(buyer,"%s\n %s\n %f\n %c\n %f\n",&cust.name,&cust.order,&cust.quantity,&cust.quality,&cust.rate2)!=EOF)
        {
        	gotoxy(30,r);
			printf("%s",cust.name);
			     
			gotoxy(45,r);
			printf("%s",cust.order);
				
			gotoxy(60,r);
			printf("%.2f",cust.quantity);
				 
			gotoxy(75,r);
			printf("%c",cust.quality);
				 
			gotoxy(90,r);
			printf("%.2f",cust.rate2);
				 
			r++;
		}
		
		getche();
		buyerDetails();
	 }
     
     if(task==2)
     {
     	system("cls");
    	company();
    	
    	printf("\n\t\t Enter the name You Want To Search : ");
     	scanf("%s",bname);
     	
    system("cls");
		company();
     	
     	gotoxy(54,3);
	    printf("-------------");
        gotoxy(54,4);
        printf("BUYER DETAILS");
	    gotoxy(54,5);
        printf("-------------");
     	
    
     	 gotoxy(30,7);
		 printf("Name");
		 
		 gotoxy(45,7);
		 printf("Item Name");
		 
		 gotoxy(60,7);
		 printf("Quantity");
		 
		 gotoxy(75,7);
		 printf("Quality");
	
		 gotoxy(90,7);
		 printf("Selling Price");
		 
		 gotoxy(30,8);
		 printf("=========================================================================");
		 
        while(fscanf(buyer,"%s\n %s\n %f\n %c\n %f\n",&cust.name,&cust.order,&cust.quantity,&cust.quality,&cust.rate2)!=EOF)
		{
			
			if(strcmp(cust.name,bname)==0)
			{
				gotoxy(30,r);
				printf("%s",cust.name);
				     
				gotoxy(45,r);
				printf("%s",cust.order);
					
				gotoxy(60,r);
				printf("%.2f",cust.quantity);
					 
				gotoxy(75,r);
				printf("%c",cust.quality);
					 
				gotoxy(90,r);
				printf("%.2f",cust.rate2);
					 
				r++;
		    }
		}
		
		getche();
		buyerDetails(); 
	}
	
	else
	{
		manager();
	}
	
	fclose(buyer);
}
//***************************************** CHECK SUPPLIER DETAIL *****************************************************
void supplierDetails()
{
	int task, i=1, r=9;
	char sname[30];
	
	system("cls");
	company();
	
	FILE*supp;	
	supp=fopen("supplier.txt","r");
	
	if(supp==NULL)
	{
		printf("Error");
		exit(0);
	}

     printf("\n\t\t 1. Display Full List");
	 printf("\n\t\t 2. Search By Name");
     printf("\n\t\t 3. Exit");
     
     printf("\n\n\t\tTo Perform The Given Task Enter The Number :  ");
	 scanf("%d",&task);
     fflush(stdin);
     
    if(task==1)
    {
    	system("cls");
    	company();
    	
     	gotoxy(54,3);
	 	printf("----------------");
     	gotoxy(54,4);
     	printf("SUPPLIER DETAILS");
	 	gotoxy(54,5);
     	printf("----------------");
     	
     	 gotoxy(30,7);
		 printf("Name");
		 
		 gotoxy(45,7);
		 printf("Item Name");
		 
		 gotoxy(60,7);
		 printf("Quantity");
		 
		 gotoxy(75,7);
		 printf("Quality");
		 
		 gotoxy(90,7);
		 printf("Buying Price");
		 
		 gotoxy(30,8);
		 printf("=========================================================================");
		 
	    
	    while(fscanf(supp,"%s\n%s\n%f\n%c\n%f\n",cust.sup,cust.order,&cust.quantity,&cust.quality,&cust.rate)!=EOF)
		{
			gotoxy(30,r);
		    printf("%s",cust.sup);
		    
		    gotoxy(45,r);
			printf("%s",cust.order);
	
		    gotoxy(60,r);
			printf("%.2f",cust.quantity);
			 
			gotoxy(75,r);
			printf("%c",cust.quality);
			 
			 gotoxy(90,r);
			 printf("%.2f",cust.rate);
		    
			 r++;
		}
		getche();
		supplierDetails(); 
    }
    
    else if(task==2)
    {
    	system("cls");
    	company();
     	
    	printf("\n\t\t Enter the name : ");
     	scanf("%s",sname);
     	
     	system("cls");
    	company();
     	
     	
     	gotoxy(54,3);
	 	printf("----------------");
     	gotoxy(54,4);
     	printf("SUPPLIER DETAILS");
	 	gotoxy(54,5);
     	printf("----------------");
     	
     	 gotoxy(30,7);
		 printf("Name");
		 
		 gotoxy(45,7);
		 printf("Item Name");
		 
		 gotoxy(60,7);
		 printf("Quantity");
		 
		 gotoxy(75,7);
		 printf("Quality");
		 
		 gotoxy(90,7);
		 printf("Buying Price");
		 
		 gotoxy(30,8);
		 printf("=========================================================================");
		   
		while(fscanf(supp,"%s\n %s\n %f\n %c\n %f\n",&cust.sup,&cust.order,&cust.quantity,&cust.quality,&cust.rate)!=EOF)
		{
			if(strcmp(cust.sup,sname)==0)
			{
			 	gotoxy(30,r);
			    printf("%s",cust.sup);
			    
			    gotoxy(45,r);
				printf("%s",cust.order);
		
			    gotoxy(60,r);
				printf("%.2f",cust.quantity);
				 
				gotoxy(75,r);
				printf("%c",cust.quality);
				 
				 gotoxy(90,r);
				 printf("%.2f",cust.rate);
			    
				 r++;
		    }
		} 
		getche();
		supplierDetails(); 
	}
	else
	{
		manager();
	}
}
//***************************************** CHEMICAL LIST #############################################################
void chemicalList()
{
	int task;
	char ch;
	FILE* chemical;
	
	system("cls");
	company();
	

 	 printf("\n\t\t 1. Add chemical");
	 printf("\n\t\t 2. Search chemical by name");
	 printf("\n\t\t 3. Display full chemical list");
	 printf("\n\t\t 4. Exit");
	 
	 printf("\n\n\t\tTo Perform The Given Task Enter The Number :  ");
	 scanf("%d",&task);
	 
	 if(task==1)
	 {
	 	do
	 	{
	 		system("cls");
	 	 	company();
	 	 
			 chemical=fopen("chemicalList.txt","a");
			 
		 	 printf("\n\t\t Enter Chemical Name:");
		 	 scanf("%s",supl.chemical);
		 	 
		 	 printf("\t\t Enter Supplier Name:");
		 	 scanf("%s",supl.sup);
		 	 
		 	 printf("\t\t Enter Supplier Contact Number:");
		 	 scanf("%s",supl.supMob);
		 	 
		 	 fprintf(chemical,"%s\n %s\n %s\n\n",supl.chemical,supl.sup,supl.supMob);
		 	 
		 	 printf("\n\n\n\t\t\t***********Chemical Added Sucessfully*****************");

		     printf("\n\n\t\tFor More Entries Enter Y for Yes And N For No : ");
		     scanf(" %c",&yesNo);
		     
		     system("cls");
			 company();
		     
		 }while(yesNo=='Y' || yesNo=='y');     
		
		fclose(chemical);
		getche();
		chemicalList();
	 }
	 
	 else if(task==2)
	 {
	 	 system("cls");
	 	 company();
	 	 
	 	 char cname[30];
	 	 int r=9,i=1;
	 	 
	 	 FILE* chemical;
		 chemical=fopen("chemicalList.txt","r");
		 
		 printf("\n\t\t Enter name to search:");
		 scanf("%s",cname);
		 
		 system("cls");
	 	 company();
		 	
		 gotoxy(54,3);
		 printf("----------------");
	     gotoxy(54,4);
	     printf("CHEMICAL DETAILS");
		 gotoxy(54,5);
	     printf("----------------");
		 
		 gotoxy(25,7);
     	 printf("S:NO");
     	 gotoxy(45,7);
		 printf("Chemical Name");
		 gotoxy(65,7);
 		 printf("Supplier Name");
		 gotoxy(85,7);
		 printf("Mobile Number");
		 
		 gotoxy(25,8);
		 printf("=========================================================================");
		 
		 while(fscanf(chemical,"%s\n %s\n %s\n\n",&supl.chemical,&supl.sup,&supl.supMob)!=EOF)
		 {
		 	if(strcmp(supl.chemical,cname)==0)
			 {
		 		 gotoxy(25,r);
				 printf("%d",i);
				 gotoxy(45,r);
		    	 printf("%s",supl.chemical);
		     	 gotoxy(65,r);
				 printf("%s",supl.sup);
		     	 gotoxy(85,r);
			   	 printf("%s",supl.supMob);
			   	 
			   	 i++;
			   	 r++;
			 }
		 }
		 fclose(chemical);
		 getche();
		 chemicalList();
	 	
	 }
	 else if(task==3)
	 {
	 	system("cls");
	 	company();
	 	
	 	FILE* chemical;
		 chemical=fopen("chemicalList.txt","r");
	 	 
	 	 int r=9,i=1;
	 	 
	 	gotoxy(54,3);
		 printf("----------------");
	     gotoxy(54,4);
	     printf("CHEMICAL DETAILS");
		 gotoxy(54,5);
	     printf("----------------");
		 
		 gotoxy(25,7);
     	 printf("S:NO");
     	 gotoxy(45,7);
		 printf("Chemical Name");
		 gotoxy(65,7);
 		 printf("Supplier Name");
		 gotoxy(85,7);
		 printf("Mobile Number");
		 
		 gotoxy(25,8);
		 printf("=========================================================================");
		 
		 while(fscanf(chemical,"%s\n %s\n %s\n\n",&supl.chemical,&supl.sup,&supl.supMob)!=EOF)
		 {
		  	gotoxy(25,r);
			printf("%d",i);
			gotoxy(45,r);
		    printf("%s",supl.chemical);
		    gotoxy(65,r);
			printf("%s",supl.sup);
		    gotoxy(85,r);
			printf("%s",supl.supMob);
			
			i++;
			r++;
		 }
		 fclose(chemical);
		 getche();
		 chemicalList();	  
    }
    else if(task==4)
    {
    	manager();
	}
}
//******************************************Bank*******************************************************
void bankWork()
{
	system("cls");
	compName();
	int mainMenuNum;

	printf("\t\t\t\t\t\t    ---------------\n");
	printf("\t\t\t\t\t\t        Main Menu\t\t\n");
	printf("\t\t\t\t\t\t     ---------------\n");
	
	printf("\n");
	printf("\n");
	
	printf("\t\t 1. Add Bank\n");
	printf("\t\t 2. Add Debit\n");
	printf("\t\t 3. Add Credit\n");
	printf("\t\t 4. Check Debit\n");
	printf("\t\t 5. Check Credit\n");
	printf("\t\t 6. Bank Statement\n");
	printf("\t\t 7. Exit\n");
	
	printf("\n\n\t\tTo Perform The Given Task Enter The Number :  ");
	scanf("%d",&mainMenuNum);
	
	system("cls");
	if(mainMenuNum==1)
	{
		addBank();
	}
	else if(mainMenuNum==2)
	{
		addDebit();
	}
	else if(mainMenuNum==3)
	{
		addCredit();
	}
	else if(mainMenuNum==4)
	{
		checkDebit();
	}
	else if(mainMenuNum==5)
	{
		checkCredit();
	}
	else if(mainMenuNum==6)
	{
		bankStatement();
	}
	else
	{
		manager();
	}
}
//******************************************Add Bank*******************************************************
void addBank()
{
	int addBankMenuNum, i=16  ;
	struct bank b1;
	FILE *bank_accountNo;
	compName();
		
	
	printf("\t\t 1. Add Bank\n");
	printf("\t\t 2. View Banks\n");
	printf("\t\t 3. Exit\n");
	
	printf("\n\n\t\tTo Perform The Given Task Enter The Number :  ");
	scanf("%d",&addBankMenuNum);
	
	system("cls");
	
	if(addBankMenuNum==1)
	{
		compName();
		bank_accountNo=fopen("bank names and Account No.txt","a");
		
		if (bank_accountNo == NULL) 
		{
        	printf("Error!");
        	exit(1);
       	}
		
		do{
			system("cls");
			compName();
		
			printf("\t\t Name Of Bank:");
			getchar();
			scanf("%s",b1.bankName);
			
			printf("\n\t\t Account No :");
			scanf("%s",b1.accountNo);
			
			
			printf("\n\n\t\tFor More Entries Enter Y for Yes And N For No :");
			getchar();
			scanf("%c",&yesNo);
			
			fprintf(bank_accountNo,"%s %s\n",b1.bankName,b1.accountNo);
			
		}while(yesNo=='Y' || yesNo=='y' );
		
		fclose(bank_accountNo);
		
		system("cls");
		
			
		addBank();
		
	}
	else if(addBankMenuNum==2)
	{
		int i=10;
		compName();
		bank_accountNo = fopen("bank names and Account No.txt","r");
		if(bank_accountNo==NULL)
		{
	    	printf("file can't open!!!!");
	    	exit(1);
		}
		
		printf("\t\t\t\t\t\t ---------------------------\n");
		printf("\t\t\t\t\t\t   Bank Names And Account #\t\t\n");
		printf("\t\t\t\t\t\t ---------------------------\n");

	
		gotoxy(45,8);
		printf("Bank Name  \t   Account#");
		
		gotoxy(40,9);
		printf("============================================");
		
		printf("\n");
		
		fscanf(bank_accountNo,"%s %s",b1.bankName,b1.accountNo);
		
		
		while(!feof(bank_accountNo))
		{
			gotoxy(47,i);
			printf("%s",b1.bankName);
			
			gotoxy(68,i); 
			printf("%s",b1.accountNo);
			i=i+1;
			
			fscanf(bank_accountNo,"%s %s",b1.bankName,b1.accountNo);
		}
		
		fclose(bank_accountNo);
		
		getche();
		
		system("cls");
			
		addBank();
	
	}
	else
	{
		bankWork();
	}
	
}
//******************************************Add Debit*******************************************************
void addDebit()
{
	FILE *ptrdebit;
	struct debit debit1;
	compName();
	
	ptrdebit=fopen("debit account.txt","a");
	
	if (ptrdebit == NULL) 
	{
        printf("Error!");
       	exit(1);
    }
	do{
		printf("\t\t Enter Date[DD/MM/YYYY]:  ");
		scanf("%d %d %d",&debit1.day,&debit1.month,&debit1.year);
		
		printf("\t\t Enter Name:");
		getchar();
		scanf("%s",&debit1.name);
		
		printf("\t\t Enter Bank Name:");
		getchar();
		scanf("%s",&debit1.nameofbank);
		
		printf("\t\t Enter Amount Type:");
		getchar();
		scanf("%s",&debit1.amountType);
		
		printf("\t\t Enter Debit Amount:");
		scanf("%f",&debit1.amount);
		
		fprintf(ptrdebit,"%d %d %d\n %s\n %s\n %s\n %f\n\n",debit1.day,debit1.month,debit1.year,debit1.name,debit1.nameofbank,debit1.amountType,debit1.amount);
		
		printf("\n\n\t\tFor More Entries Enter Y for Yes And N For No :");
		getchar();
		scanf("%c",&yesNo);

		
		system("cls");
		compName();
		
	}while(yesNo=='Y' || yesNo=='y');
	
	fclose(ptrdebit);
	
	system("cls");
	
	bankWork();	
}
//******************************************Add Credit*******************************************************
void addCredit()
{
	FILE *ptrcredit;
	struct credit credit1;
	compName();
	
	ptrcredit=fopen("credit account.txt","a");
	
	if (ptrcredit == NULL) 
	{
        printf("Error!");
       	exit(1);
    }
    
    do{
		printf("\t\t Enter Date[DD/MM/YYYY]:");
		scanf("%d %d %d",&credit1.day,&credit1.month,&credit1.year);
		
		
		printf("\t\t Enter Name:");
		getchar();
		scanf("%s",&credit1.name);
		
		
		printf("\t\t Enter Bank Name:");
		getchar();
		scanf("%s",&credit1.nameofbank);
		
		printf("\t\t Enter Amount Type:");
		getchar();
		scanf("%s",&credit1.amountType);
		
		printf("\t\t Enter Credit Amount:");
		scanf("%f",&credit1.amount);
		
		fprintf(ptrcredit,"%d %d %d\n %s\n %s\n %s\n %f\n\n",credit1.day,credit1.month,credit1.year,credit1.name,credit1.nameofbank,credit1.amountType,credit1.amount);
		
		printf("\n\n\t\tFor More Entries Enter Y for Yes And N For No :");
		getchar();
		scanf("%c",&yesNo);
		
		system("cls");
		compName();
		
	
	}while(yesNo=='Y' || yesNo=='y');
	
	fclose(ptrcredit);
	
	system("cls");
	
	bankWork();	
}
//******************************************Check Debit*******************************************************
void checkDebit()
{
	char name[30] ;
	int i=10 ;
	struct debit debit1;
	FILE *ptr_checkDebit;
	int mainMenuNum;
	
	compName();
	
	ptr_checkDebit = fopen("debit account.txt","r");
	
	if(ptr_checkDebit==NULL)
	{
	    printf("file can't open!!!!");
	    exit(1);
	}
	
	printf("\t\t 1. Display Full List\n");
	printf("\t\t 2. Search By Name\n");
	printf("\t\t 3. Exit\n");
	
	printf("\n\n\t\tTo Perform The Given Task Enter The Number :  ");
	scanf("%d",&mainMenuNum);
	
	if(mainMenuNum==1)
	{
		system("cls");
		compName(); 
		
		printf("\t\t\t\t\t\t    -------------\n");
		printf("\t\t\t\t\t\t      Debit List\t\t\n");
		printf("\t\t\t\t\t\t    -------------\n");
	
		gotoxy(30,8);
		printf("Date \t Name \t      Bank Name \t Type \t        Amount");
		
		gotoxy(60,8);
		printf("\n                        ===========================================================================");

		while(fscanf(ptr_checkDebit,"%d %d %d\n %s\n %s\n %s\n %f\n\n",&debit1.day,&debit1.month,&debit1.year,debit1.name,debit1.nameofbank,debit1.amountType,&debit1.amount)!=EOF)
		{
			gotoxy(25,i);
			printf("%d/%d/%d",debit1.day,debit1.month,debit1.year);
				
			gotoxy(41,i);
			printf("%s",debit1.name);
				
			gotoxy(54,i);
			printf("%s",debit1.nameofbank);
				
			gotoxy(72,i);
			printf(" %s",debit1.amountType);
				
			gotoxy(88,i);
			printf("%.2f",debit1.amount);
			i=i+1;
			
		}
		
		getche();
		system("cls");
		checkDebit();
	}
		
	else if(mainMenuNum==2)
	{
		system("cls");
		compName(); 
			
		printf("\t\t Enter The Name To Be Searched:  ");
		scanf("%s",&name);
		fflush(stdin);
		
		system("cls"); 
		
		compName();
		
	
		printf("\t\t\t\t\t\t    -------------\n");
		printf("\t\t\t\t\t\t      Debit List\t\t\n");
		printf("\t\t\t\t\t\t    -------------\n");
		
		gotoxy(30,8);
		printf("Date \t Name \t      Bank Name \t Type \t        Amount");
		
		gotoxy(60,8);
		printf("\n                        ===========================================================================");
	
		while(fscanf(ptr_checkDebit,"%d %d %d\n %s\n %s\n %s\n %f\n\n",&debit1.day,&debit1.month,&debit1.year,debit1.name,debit1.nameofbank,debit1.amountType,&debit1.amount)!=EOF)
		{
			if(strcmp(debit1.name,name)==0)
			{
				gotoxy(25,i);
				printf("%d/%d/%d",debit1.day,debit1.month,debit1.year);
					
				gotoxy(41,i);
				printf("%s",debit1.name);
					
				gotoxy(54,i);
				printf("%s",debit1.nameofbank);
					
				gotoxy(72,i);
				printf(" %s",debit1.amountType);
					
				gotoxy(88,i);
				printf("%.2f",debit1.amount);
				i=i+1;
			}
		}
		
		getche();
		system("cls");
		checkDebit();
	}
	else
	{
		system("cls");
		bankWork();
	}
		
    fclose(ptr_checkDebit);
}
//*****************************************Check Credit*******************************************************
void checkCredit()
{
	char name[30] ;
	int i=10, mainMenuNum;
	struct credit credit1;
	FILE *ptr_checkCredit;
	
	compName();
	
	ptr_checkCredit = fopen("credit account.txt","r");
	
	if(ptr_checkCredit==NULL)
	{
	    printf("file can't open!!!!");
	}
	
	printf("\t\t 1. Display Full List\n");
	printf("\t\t 2. Search By Name\n");
	printf("\t\t 3. Exit\n");
	
	printf("\n\n\t\tTo Perform The Given Task Enter The Number :  ");
	scanf("%d",&mainMenuNum);
	
	if(mainMenuNum==1)
	{
		system("cls");
		compName(); 
		
		printf("\t\t\t\t\t\t     -------------\n");
		printf("\t\t\t\t\t\t      Credit List\t\t\n");
		printf("\t\t\t\t\t\t     -------------\n");
		
		gotoxy(30,8);
		printf("Date \t Name \t      Bank Name \t Type \t        Amount");
		
		gotoxy(60,8);
		printf("\n                        ===========================================================================");
	
		while(fscanf(ptr_checkCredit,"%d %d %d\n %s\n %s\n %s\n %f\n\n",&credit1.day,&credit1.month,&credit1.year,credit1.name,credit1.nameofbank,credit1.amountType,&credit1.amount)!=EOF)
		{
			gotoxy(25,i);
			printf("%d/%d/%d",credit1.day,credit1.month,credit1.year);
				
			gotoxy(41,i);
			printf("%s",credit1.name);
				
			gotoxy(54,i);
			printf("%s",credit1.nameofbank);
				
			gotoxy(72,i);
			printf(" %s",credit1.amountType);
				
			gotoxy(88,i);
			printf("%.2f",credit1.amount);
			i=i+1;
		}
		
		getche();
		system("cls");
		checkCredit();		
	}
		
	else if(mainMenuNum==2)
	{
		system("cls");
		compName(); 
		
		printf("\t\t Enter The Name To Be Searched:  ");
		scanf("%s",&name);
		fflush(stdin);
		
		system("cls"); 
		
		compName();
		
		printf("\t\t\t\t\t\t     -------------\n");
		printf("\t\t\t\t\t\t      Credit List\t\t\n");
		printf("\t\t\t\t\t\t     -------------\n");
		
		gotoxy(30,8);
		printf("Date \t Name \t      Bank Name \t Type \t        Amount");
		
		gotoxy(60,8);
		printf("\n                        ===========================================================================");
	
		while(fscanf(ptr_checkCredit,"%d %d %d\n %s\n %s\n %s\n %f\n\n",&credit1.day,&credit1.month,&credit1.year,credit1.name,credit1.nameofbank,credit1.amountType,&credit1.amount)!=EOF)
		{
			if(strcmp(credit1.name,name)==0)
			{
				gotoxy(25,i);
				printf("%d/%d/%d",credit1.day,credit1.month,credit1.year);
					
				gotoxy(41,i);
				printf("%s",credit1.name);
					
				gotoxy(54,i);
				printf("%s",credit1.nameofbank);
					
				gotoxy(72,i);
				printf(" %s",credit1.amountType);
					
				gotoxy(88,i);
				printf("%.2f",credit1.amount);
				i=i+1;
			}
		}
		
		getche();
		system("cls");
		checkCredit();
	}
	else
	{
		system("cls");
		bankWork();
	}
	
    fclose(ptr_checkCredit);
}
//******************************************Bank Satement*******************************************************
void bankStatement()
{
	char name[30] ;
	int i=10 ;
	float creditSum=0 , debitSum=0 , bankState;
	struct credit credit1;
	struct debit debit1;
	FILE *stateCredit;
	FILE *stateDebit;
	
	compName();
	
	stateCredit = fopen("credit account.txt","r");
	stateDebit = fopen("debit account.txt","r");
	
	if((stateCredit==NULL) && (stateDebit==NULL))
	{
	    printf("file can't open!!!!");
	    exit(1);
	}
	
	printf("\t\t Enter The Name Of Bank To Be Searched:  ");
	scanf("%s",&name);
	fflush(stdin);
	
	system("cls"); 
	
	compName();
		
	
	printf("\t\t\t\t\t\t     --------------------------\n");
	printf("\t\t\t\t\t\t      Bank Statement Of %s\t\t\n",name);
	printf("\t\t\t\t\t\t     --------------------------\n");
	
	gotoxy(17,8);
	printf("Debit Date    \t       Debit Amount     \t  Credit Date    \t    Credit Amount");
	
	gotoxy(60,8);
	printf("\n           ====================================================================================================");
	
	while(fscanf(stateCredit,"%d %d %d\n %s\n %s\n %s\n %f\n\n",&credit1.day,&credit1.month,&credit1.year,credit1.name,credit1.nameofbank,credit1.amountType,&credit1.amount)!=EOF)
	{
		if(strcmp(credit1.nameofbank,name)==0)
		{
			gotoxy(66,i);
			printf("%d/%d/%d",credit1.day,credit1.month,credit1.year);
				
			gotoxy(95,i);
			printf("%.2f",credit1.amount);
			creditSum+=credit1.amount;
			i=i+1;
		}
	}
	
	i=10;
	while(fscanf(stateDebit,"%d %d %d\n %s\n %s\n %s\n %f\n\n",&debit1.day,&debit1.month,&debit1.year,debit1.name,debit1.nameofbank,debit1.amountType,&debit1.amount)!=EOF)
	{
		if(strcmp(debit1.nameofbank,name)==0)
		{
			gotoxy(17,i);
			printf("%d/%d/%d",debit1.day,debit1.month,debit1.year);
				
			gotoxy(40,i);
			printf("%.2f",debit1.amount);
			
			debitSum+=debit1.amount;
			i=i+1;
		}
	}
	
	printf("\n\n\nTotal Debit Amount = %.2f",debitSum);
	printf("\nTotal Credit Amount = %.2f",creditSum);
	
	bankState=debitSum-creditSum;
	printf("\nBank Statement Of %s = %.2f",name,bankState);
	
	
		
    fclose(stateCredit);
    fclose(stateDebit);
    
	getche();
	
	system("cls");
	   
	bankWork();
}















