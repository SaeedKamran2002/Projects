#include<iostream>
#include<conio.h>
#include<windows.h>
#include<fstream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctime>
using namespace std;
//****************************************** GOTOXY FUNCTION & Time & Date & text color & Comapny Name*************************************************
COORD coord = {0, 0};
void gotoxy(int x, int y)
{
 	COORD coord;
 	coord.X = x;
 	coord.Y = y;
 	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void textcolor(int x)
{
	HANDLE hconsole;
	hconsole=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hconsole, x );	
}

int t(void)
{
 	time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
	gotoxy(90,2);
	textcolor(245);
	cout<<"Date : "<<__DATE__;
	gotoxy(90,3);
	cout<<"Time : "<<__TIME__;
	textcolor(240);
	return 0;
}

void LOGO()
{
	cout<<"\t\t\t\t\t\t*****************************\n";
	cout<<"\t\t\t\t\t\t    Pak Chemicals Pvt Ltd\t\t\n";
	cout<<"\t\t\t\t\t\t*****************************\n";
	
	cout<<"\n";
}
//******************************************Forward Declarations*******************************************************
int main();
class Bank;
void setChoice();
//******************************************STRUCTURE*******************************************************
struct order
{
	int d , m ,y ;
	string name ;
	string itemName ;
	string country;
	float quantity;
	string quantitytype;
	long int price;
};
struct bank_detalis{
	int d , m , y;
	string name;
	string bankName;
	string cashType;
	long int amount;
};
struct expenses{
	int day , month , year;
	string name;
	long int amount;
};
//******************************************Global Variables*******************************************************
char yesNo;
//****************************************** CLASS Chemical_Company*************************************************
class Chemical_Company
{
	public:
		struct order o ;
		Chemical_Company()
		{
			o.d = 0 ;
			o.m = 0 ;
			o.y = 0 ;
			o.name = " ";
			o.itemName = " ";
			o.country = " ";
			o.quantity = 0 ;
			o.quantitytype = " ";
			o.price = 0 ;
		}
		Chemical_Company(int da ,int mo , int ye , string na ,string it ,string co  ,float qu ,string qt ,float pr)
		{
			o.d = da ;
			o.m = mo ;
			o.y = ye ;
			o.name = na ;
			o.itemName = it ;
			o.country = co ;
			o.quantity = qu ;
			o.quantitytype = qt ;
			o.price = pr ;
		}
		
};
//****************************************** CLASS Customer*************************************************
class Customer : public Chemical_Company
{

	int sNO , cust_SNO , cd, cm ,cy , num ;
	float amount ;
	float buyingPrice , totBuyingAmount , totBuyingAmount1;
	int customerOrderingQuantity , customerQuantity;
	string customerName , customerContact;

	
	public:
		Customer()
		{
		}
		Customer(int da ,int mo , int ye , string na ,string it ,string co  ,float qu ,string qt ,float pr):Chemical_Company(da ,mo ,ye ,na ,it ,co  ,qu ,qt ,pr)
		{
		}
		//******************************************Sale Item*************************************************
		void saleItem()            
		{
			textcolor(240);
			system("cls");
			LOGO();
			
			double salePrice;
			string boughtItem , itemMeasure;
			fstream buying;
			buying.open("Sale List.txt",ios::app);
			fstream purchase;
			purchase.open("Chemical List.txt", ios::in);
			
			if(!purchase.is_open())
			{
				cout<<"File not opened\n";
				getche();
				setChoice();
			}
			if(!buying.is_open())
			{
				cout<<"File not opened\n";
				setChoice();
			}
			
			cout<<  "\t\t\t\t\t\t     *******************";
			cout << "\n\t\t\t\t\t\t          ITEM LIST";
			cout<<  "\n\t\t\t\t\t\t     *******************";
			
			
	        purchase>>sNO>>o.d>>o.m>>o.y>>o.name>>o.itemName>>o.country>>o.quantity>>o.quantitytype>>buyingPrice>>o.price>>totBuyingAmount;
	        
	        gotoxy(0,8);
	        cout<<"-------------------------------------------------------------------------------------"<<endl;
			cout<<"S.no        ITEM NAME        COUNTRY       QUANTITY       QUANTITY TYPE       PRICE"<<endl;
			cout<<"-------------------------------------------------------------------------------------"<<endl;
			        
			int i = 11;
			
			while(purchase.good())
			{
				gotoxy(0, i);
				cout<<sNO;
				
				gotoxy(13,i);
				cout<<o.itemName;
				
				gotoxy(29,i);
				cout<<o.country;
				
				gotoxy(45,i);
				cout<<o.quantity;
				
				gotoxy(58,i);
				cout<<o.quantitytype;
				
				gotoxy(78,i);
				cout<<o.price;
				
			    i++;
			    
			    purchase>>sNO>>o.d>>o.m>>o.y>>o.name>>o.itemName>>o.country>>o.quantity>>o.quantitytype>>buyingPrice>>o.price>>totBuyingAmount;
			}
			purchase.close();
			
			    cout<<endl<<endl;
				cout<<"For Purcahsing The Item [Press 1] Or Go Back [Press 2] : ";	
				cin>>num;
				
				if(num == 1 )
				{
					do{
						textcolor(240);
						cout<<endl<<"Please Enter The Serial Number of Item You Want To Purcahse  : ";
						cin>>cust_SNO;
					
						system("cls");
						LOGO();
						
						cout<<"\t\tEnter Date[DD/MM/YYYY]:  ";
						cin>>cd>>cm>>cy;
						
						cout<<"\t\tEnter Your Name: ";
						cin>>customerName;
						
						cout<<"\t\tEnter Your Contact No. : ";
						cin>>customerContact;
						
						cout<<"\t\tEnter the Quantity You Want To Buy: ";
						cin>>customerOrderingQuantity;
						
						fstream purchase;
						purchase.open("Chemical List.txt", ios::in );
						
						purchase>>sNO>>o.d>>o.m>>o.y>>o.name>>o.itemName>>o.country>>o.quantity>>o.quantitytype>>buyingPrice>>o.price>>totBuyingAmount;
					
						while(!purchase.eof())
						{
							if(sNO == cust_SNO )
							{
								salePrice = o.price	;
								boughtItem = o.itemName;
								itemMeasure = o.quantitytype;
								if(customerOrderingQuantity  >  o.quantity)
								{
									while(customerOrderingQuantity    >   o.quantity)
									{
										cout<<"\n\t\tEntered Invalid Quantity : \n\t\tEnter the Quantity You Want To Buy: ";
										cin>>customerOrderingQuantity;
									}
								}
								buying<<cd<<" "<<cm<<" "<<cy<<" "<<customerName<<" "<<o.itemName<<" "<<o.country<<" "<<customerOrderingQuantity<<" "<<o.quantitytype<<" "<<o.price<<" "<<(o.price*customerOrderingQuantity)<<endl;	
							}
							purchase>>sNO>>o.d>>o.m>>o.y>>o.name>>o.itemName>>o.country>>o.quantity>>o.quantitytype>>buyingPrice>>o.price>>totBuyingAmount;
					
						}
						purchase.close();
						

						fstream purchase2;
						purchase.open("Chemical List.txt", ios::in );
						purchase2.open("Chemical List 2.txt", ios::out );
						
						purchase>>sNO>>o.d>>o.m>>o.y>>o.name>>o.itemName>>o.country>>o.quantity>>o.quantitytype>>buyingPrice>>o.price>>totBuyingAmount;
					
						while(purchase.good())
						{
							
							if(sNO == cust_SNO )
							{
								customerQuantity = 	o.quantity-customerOrderingQuantity ; 
								purchase2 <<sNO<<" "<<o.d<<" "<<o.m<<" "<<o.y<<" "<<o.name<<" "<<o.itemName<<" "<<o.country<<" "<<customerQuantity<<" "<<o.quantitytype<<" "<<buyingPrice<<" "<<o.price<<" "<<totBuyingAmount<<endl;
				
							}
							else
							{
								purchase2 <<sNO<<" "<<o.d<<" "<<o.m<<" "<<o.y<<" "<<o.name<<" "<<o.itemName<<" "<<o.country<<" "<<o.quantity<<" "<<o.quantitytype<<" "<<buyingPrice<<" "<<o.price<<" "<<totBuyingAmount<<endl;
				
							}
							purchase>>sNO>>o.d>>o.m>>o.y>>o.name>>o.itemName>>o.country>>o.quantity>>o.quantitytype>>buyingPrice>>o.price>>totBuyingAmount;
							
						}
						purchase.close();
						purchase2.close();
						
						textcolor(244);
						cout<<"\n\n\t\tORDER CONFIRMED SUCCESSFULLY!!!";
						cout<<"\n\n\t\tOrder Details : \n\t\tYou Ordered "<<customerOrderingQuantity<<" "<<itemMeasure<<" of "<<boughtItem;
						cout<<"\n\t\tYour Total Amount Is : "<<(customerOrderingQuantity*salePrice);
						
						textcolor(240);
						cout<<"\n\n\t\tFor More Entries Enter Y for Yes And N For No :";
						getchar();
						cin>>yesNo;
						
					}while(yesNo=='Y' || yesNo=='y');
					
					buying.close();
					
					fstream purchase2;
					purchase.open("Chemical List.txt", ios::out );
					purchase2.open("Chemical List 2.txt", ios::in );
				    
				    purchase2>>sNO>>o.d>>o.m>>o.y>>o.name>>o.itemName>>o.country>>o.quantity>>o.quantitytype>>buyingPrice>>o.price>>totBuyingAmount;
							    
				    while(purchase2.good())
				    {
						purchase <<sNO<<" "<<o.d<<" "<<o.m<<" "<<o.y<<" "<<o.name<<" "<<o.itemName<<" "<<o.country<<" "<<o.quantity<<" "<<o.quantitytype<<" "<<buyingPrice<<" "<<o.price<<" "<<totBuyingAmount<<endl;
						purchase2>>sNO>>o.d>>o.m>>o.y>>o.name>>o.itemName>>o.country>>o.quantity>>o.quantitytype>>buyingPrice>>o.price>>totBuyingAmount;
							
					}
					remove("Chemical List 2.txt");  
				    purchase2.close();
				    purchase.close();
				    
				    system("cls");
				    
					main();
					
				}  
				else
				{
					main();
				}
				
		}


};
//****************************************** CLASS Manager*************************************************
class Manager : public Chemical_Company
{
	float buyingPrice;
	
	public:
	Manager()
	{
	}	
	Manager(int da ,int mo , int ye , string na ,string it ,string co  ,float qu ,string qt ,float pr):Chemical_Company(da ,mo ,ye ,na ,it ,co  ,qu ,qt ,pr)
	{
	}
	//****************************************** Purchase Item*************************************************	
	void purchaseItem()
	{		
			textcolor(240);
			float totBuyingAmount;
			int sNo ,serialNo;
			fstream purchase  , chemical_list , sNo_chemical_list;
			purchase.open("Purchase list.txt" , ios::app);
			chemical_list.open("Chemical List.txt" , ios::app);
			sNo_chemical_list.open("Chemical List.txt" , ios::in);
			if(!purchase.is_open())
			{
				cout<<"File not opened\n";
			}
			if(!chemical_list.is_open())
			{
				cout<<"File not opened\n";
			}
						
			if(!sNo_chemical_list.is_open())
			{
				cout<<"File not opened\n";
			}
			
			while(sNo_chemical_list.good())
			{
					sNo = sNo + 1;
					sNo_chemical_list>>serialNo>>o.d>>o.m>>o.y>>o.name>>o.itemName>>o.country>>o.quantity>>o.quantitytype>>buyingPrice>>o.price>>totBuyingAmount;
			}
			
			do
			{
				sNo_chemical_list>>serialNo>>o.d>>o.m>>o.y>>o.name>>o.itemName>>o.country>>o.quantity>>o.quantitytype>>buyingPrice>>o.price>>totBuyingAmount;
			
				system("cls");
				LOGO();
				
				cout<<"\t\tEnter Date[DD/MM/YYYY]:  ";
				cin>>o.d>>o.m>>o.y;
				
				cout<<"\t\tEnter Supplier Name : ";
				cin>>o.name;
				
				cout<<"\t\tEnter Item Name :";
				cin>>o.itemName;
				
				cout<<"\t\tEnter Country : ";
				cin>>o.country;
			
				cout<<"\t\tEnter Quantity :";
				cin>>o.quantity;
				
				cout<<"\t\tEnter Measurement :";
				cin>>o.quantitytype;
				
				cout<<"\t\tEnter Buying Price:";
				cin>>buyingPrice;
				
				cout<<"\t\tEnter Selling Price:";
				cin>>o.price;
				
				totBuyingAmount = (o.quantity*buyingPrice);
				
				purchase <<o.d<<" "<<o.m<<" "<<o.y<<" "<<o.name<<" "<<o.itemName<<" "<<o.country<<" "<<o.quantity<<" "<<o.quantitytype<<" "<<buyingPrice<<" "<<o.price<<" "<<totBuyingAmount<<endl;
				chemical_list <<sNo<<" "<<o.d<<" "<<o.m<<" "<<o.y<<" "<<o.name<<" "<<o.itemName<<" "<<o.country<<" "<<o.quantity<<" "<<o.quantitytype<<" "<<buyingPrice<<" "<<o.price<<" "<<totBuyingAmount<<endl;
				
				sNo++;
				
				cout<<"\n\n\t\tFor More Entries Enter Y for Yes And N For No :";
				getchar();
				cin>>yesNo;
			}while(yesNo=='Y' || yesNo=='y');
			
			sNo_chemical_list.close();
			chemical_list.close();
			purchase.close();
			setChoice();
		}
		//****************************************** Ledger************************************************
		void ledger()
		{
			textcolor(240);
			fstream purchase , selling , debit1 , credit1;
			struct order s ;
			struct bank_detalis d;
			struct bank_detalis c;
			long int sellingPrice , totBuyingAmount , totalSellingAmount;
			int i=10 , a=0 ;
			long int totdebit1=0 , totdebit2=0 , totcredit1=0 , totcredit2 = 0;
			long int totdebit=0 , totcredit=0;
			string searchName;
				
			system("cls"); 
			LOGO();
			
			cout<<"\t\t Enter The Name Whose Account To Be Searched:  ";
			cin>>searchName;
				
			cout<<"\t\t\t\t\t\t     -------------\n";
			cout<<"\t\t\t\t\t\t       "<<searchName<<"\t\t\n";
			cout<<"\t\t\t\t\t\t     -------------\n";
			
			gotoxy(1,8);
			cout<<"Date";
			
			gotoxy(14,8);
			cout<<"Item Name";
			
			gotoxy(25,8);
			cout<<"Country";
			
			gotoxy(42,8);
			cout<<"Quantity";
			
			gotoxy(63,8);
			cout<<"Price";
			
			gotoxy(78,8);
			cout<<"Debit";
			
			gotoxy(90,8);
			cout<<"Credit";
			
			gotoxy(0,9);
			cout<<"=======================================================================================================================";
			
			purchase.open("Purchase list.txt",ios::in);
			if(!purchase.is_open())
			{
				cout<<"File not opened\n";
				setChoice();
			}
			
			purchase>>o.d>>o.m>>o.y>>o.name>>o.itemName>>o.country>>o.quantity>>o.quantitytype>>o.price>>sellingPrice>>totBuyingAmount;
				
				while(purchase.good())
				{
					if(o.name==searchName)
					{
						gotoxy(1,i);
						cout<<o.d<<"/"<<o.m<<"/"<<o.y;
						
						gotoxy(14,i);
						cout<<o.itemName;
						
						gotoxy(25,i);
						cout<<o.country;
						
						gotoxy(42,i);
						cout<<o.quantity<<" "<<o.quantitytype;
						
						gotoxy(63,i);
						cout<<o.price;
						
						gotoxy(78,i);
						cout<<"+"<<totBuyingAmount;
						
						gotoxy(90,i);
						cout<<a;
						
						totdebit1+=totBuyingAmount;
						i++;
					}
					purchase>>o.d>>o.m>>o.y>>o.name>>o.itemName>>o.country>>o.quantity>>o.quantitytype>>o.price>>sellingPrice>>totBuyingAmount;
				}
			
			selling.open("Sale List.txt",ios::in);
			if(!selling.is_open())
			{
				cout<<"File not opened\n";
				setChoice();
			}
			
			selling>>s.d>>s.m>>s.y>>s.name>>s.itemName>>s.country>>s.quantity>>s.quantitytype>>s.price>>totalSellingAmount;
			while(selling.good())
			{
				if(searchName==s.name)
				{
					gotoxy(1,i);
					cout<<s.d<<"/"<<s.m<<"/"<<s.y;
						
					gotoxy(14,i);
					cout<<s.itemName;
						
					gotoxy(25,i);
					cout<<s.country;
						
					gotoxy(42,i);
					cout<<s.quantity<<" "<<s.quantitytype;
						
					gotoxy(63,i);
					cout<<s.price;
						
					gotoxy(78,i);
					cout<<a;
						
					gotoxy(90,i);
					cout<<"-"<<totalSellingAmount;
							
					totcredit1+=totalSellingAmount;
					i++;	
				}
				selling>>s.d>>s.m>>s.y>>s.name>>s.itemName>>s.country>>s.quantity>>s.quantitytype>>s.price>>totalSellingAmount;
			}
			
			debit1.open("Debit List.txt",ios::in);
			if(!debit1.is_open())
			{
				cout<<"File not opened\n";
				setChoice();
			}
			debit1>>d.d>>d.m>>d.y>>d.name>>d.bankName>>d.cashType>>d.amount;
			
				while(debit1.good())
				{
					if(d.name==searchName)
					{
						gotoxy(1,i);
						cout<<d.d<<"/"<<d.m<<"/"<<d.y;
						
						gotoxy(14,i);
						cout<<"Recvd Cash";
						
						gotoxy(25,i);
						cout<<d.bankName;
						
						gotoxy(42,i);
						cout<<d.cashType;
						
						gotoxy(63,i);
						cout<<d.amount;
						
						gotoxy(78,i);
						cout<<"+"<<d.amount;
						
						gotoxy(90,i);
						cout<<a;
						
						totdebit2+=d.amount;
						i++;
						
					}
					debit1>>d.d>>d.m>>d.y>>d.name>>d.bankName>>d.cashType>>d.amount;
				}
				
				credit1.open("Credit List.txt",ios::in);
				if(!credit1.is_open())
				{
					cout<<"File not opened\n";
					setChoice();
				}
				
				credit1>>c.d>>c.m>>c.y>>c.name>>c.bankName>>c.cashType>>c.amount;
			
				while(credit1.good())
				{
					if(c.name==searchName)
					{
						gotoxy(1,i);
						cout<<c.d<<"/"<<c.m<<"/"<<c.y;
						
						gotoxy(14,i);
						cout<<"Paid Cash";
						
						gotoxy(25,i);
						cout<<c.bankName;
						
						gotoxy(42,i);
						cout<<c.cashType;
						
						gotoxy(63,i);
						cout<<c.amount;
						
						gotoxy(78,i);
						cout<<a;
						
						gotoxy(90,i);
						cout<<"-"<<c.amount;
						
						totcredit2+=c.amount;	
						i++;
						
					}
					credit1>>c.d>>c.m>>c.y>>c.name>>c.bankName>>c.cashType>>c.amount;		
				}
				
			totdebit=totdebit1 + totdebit2;
			totcredit=totcredit1 + totcredit2;
				
			cout<<"\n\n\nTotal Debit Amount = "<< totdebit;
			cout<<"\nTotal Credit Amount = "<<totcredit;
			cout<<"\nAmount = "<<(totdebit-totcredit);
			
			selling.close();
			purchase.close();
		    debit1.close();
		    credit1.close();
		    
			getche();
			setChoice();
			
		}
		//****************************************** Sale And Purchase*************************************************	
		void SalePurchase()
		{
			textcolor(240);
			long int totalSale=0,totalPurchase=0,Profit=0;
			long int totBuyingAmount;
			
			system("cls");
			LOGO();
		
			cout<<"\t\t\t\t\t\t     ----------------------\n";
			cout<<"\t\t\t\t\t\t       Sale/Purchase Record\t\t\n";
			cout<<"\t\t\t\t\t\t     ----------------------\n\n";
			
			fstream sale;
			fstream purchase;
			sale.open("Sale List.txt",ios::in);
			purchase.open("Purchase list.txt",ios::in);
			
			if(!sale.is_open())
			{
				cout<<"File not opened\n";
				setChoice();
			}
			
			if(!purchase.is_open())
			{
				cout<<"File not opened\n";
				setChoice();
			}
			
			purchase>>o.d>>o.m>>o.y>>o.name>>o.itemName>>o.country>>o.quantity>>o.quantitytype>>buyingPrice>>o.price>>totBuyingAmount;
			gotoxy(0,10);
			cout<<"Date";
			gotoxy(15,10);
			cout<<"Purchase";	
		 	gotoxy(30,10);
			cout<<"Item";
			gotoxy(45,10);
			cout<<"Country";
			gotoxy(60,10);
			cout<<"Quantity";
			gotoxy(75,10);
			cout<<"Type";
			gotoxy(90,10);
			cout<<"Price"<<endl;
			cout<<"========================================================================================================================"<<endl;
			int r=12;
			while(!purchase.eof()){
				gotoxy(0,r);
				cout<<o.d<<"/"<<o.m<<"/"<<o.y;
				gotoxy(15,r);
				cout<<o.name;	
			 	gotoxy(30,r);
				cout<<o.itemName;
				gotoxy(45,r);
				cout<<o.country;
				gotoxy(60,r);
				cout<<o.quantity;
				gotoxy(75,r);
				cout<<o.quantitytype;
				gotoxy(90,r);
				cout<<buyingPrice;
				r++;
				totalPurchase=totalPurchase+totBuyingAmount;
				purchase>>o.d>>o.m>>o.y>>o.name>>o.itemName>>o.country>>o.quantity>>o.quantitytype>>buyingPrice>>o.price>>totBuyingAmount;
			}
			purchase.close();
		
			r=r+3;
		
			sale>>o.d>>o.m>>o.y>>o.name>>o.itemName>>o.country>>o.quantity>>o.quantitytype>>o.price>>totBuyingAmount;
			
			gotoxy(0,r);
			cout<<"Date";
			gotoxy(15,r);
			cout<<"Sale";	
		 	gotoxy(30,r);
			cout<<"Item";
			gotoxy(45,r);
			cout<<"Country";
			gotoxy(60,r);
			cout<<"Quantity";
			gotoxy(75,r);
			cout<<"Type";
			gotoxy(90,r);
			cout<<"Price"<<endl;
			cout<<"========================================================================================================================"<<endl;
			 r=r+2;
			while(!sale.eof()){
				gotoxy(0,r);
				cout<<o.d<<"/"<<o.m<<"/"<<o.y;
				gotoxy(15,r);
				cout<<o.name;	
			 	gotoxy(30,r);
				cout<<o.itemName;
				gotoxy(45,r);
				cout<<o.country;
				gotoxy(60,r);
				cout<<o.quantity;
				gotoxy(75,r);
				cout<<o.quantitytype;
				gotoxy(90,r);
				cout<<o.price;
				r++;
				totalSale=totalSale+totBuyingAmount;
				sale>>o.d>>o.m>>o.y>>o.name>>o.itemName>>o.country>>o.quantity>>o.quantitytype>>o.price>>totBuyingAmount;
			}
			sale.close();
			
			cout<<"\n\nTotal Sale = "<<totalSale<<endl;
			cout<<"Total Purchase = "<<totalPurchase<<endl;
			if(totalSale-totalPurchase>=0){
				cout<<"Profit = "<<totalSale-totalPurchase;	
			}
			else{
				cout<<"Loss = "<<totalSale-totalPurchase;
			}
			
			
			getch();
			setChoice();
		}
		//****************************************** Add Expenses*************************************************
		void addExpenses()
	    {
	    	textcolor(240);
	    	struct expenses exp;
		    fstream expen;
		
	    	expen.open("Expenses Account.txt",ios::app);
		 
		    system("cls");
		    LOGO();
		
		    if (!expen.is_open()) 
		    {
	            cout<<"Error!";
	       	    exit(1);
	        }
	    
		    do{
			    cout<<"\t\t Enter Date[DD/MM/YYYY]:  ";
			    cin>>exp.day>>exp.month>>exp.year;
			
			    cout<<"\t\t Enter Name:";
			    getchar();
			    cin>>exp.name;
			
			    cout<<"\t\t Enter Amount:";
			    cin>>exp.amount;
			
			    expen<<exp.day<<" "<<exp.month<<" "<<exp.year<<" "<<exp.name<<" "<<exp.amount<<endl;
			
			    cout<<"\n\n\t\tFor More Entries Enter Y for Yes And N For No :";
			    getchar();
			    cin>>yesNo;
	
			
			    system("cls");
			    LOGO();
			
		    }while(yesNo=='Y' || yesNo=='y');
		
		    expen.close();
		
		    system("cls");
			setChoice();	
	}
	//****************************************** Expenses Account*************************************************
	void expensesAccount()
	{
		textcolor(240);
		struct order p;
		struct order cust;
		struct expenses exp;
		int i=10 ;
		long int totSales , totalPurchase ;  
		long int total , totBuyingAmount , sellingPrice , totexp=0 , totPro ;
		
		fstream expen;
		fstream sale;
		fstream purchase;
		purchase.open("Purchase list.txt",ios::in);
		sale.open("Sale List.txt",ios::in);
		expen.open("Expenses Account.txt",ios::in);
		
		system("cls");
		LOGO();
		
		if(!expen.is_open())
		{
		    cout<<"file can't open!!!!";
		    setChoice();
		}
		if(!sale.is_open())
		{
		    cout<<"file can't open!!!!";
		    setChoice();
		}
		if(!purchase.is_open())
		{
		    cout<<"file can't open!!!!";
		    setChoice();
		}
		

		
		cout<<"\t\t\t\t\t\t    ----------------\n";
		cout<<"\t\t\t\t\t\t      Expenses List\t\tn\n";
		cout<<"\t\t\t\t\t\t    ----------------\n";
		
			gotoxy(40,8);
			printf("Date \t           Name \t      Amount");
			
			gotoxy(40,8);
			cout<<"\n                        ===========================================================================";
			
			sale>>o.d>>o.m>>o.y>>o.name>>o.itemName>>o.country>>o.quantity>>o.quantitytype>>o.price>>totBuyingAmount;
				
			while(sale.good())
			{
				totSales+=totBuyingAmount;
				sale>>o.d>>o.m>>o.y>>o.name>>o.itemName>>o.country>>o.quantity>>o.quantitytype>>o.price>>totBuyingAmount;
			
			}
			
			purchase>>p.d>>p.m>>p.y>>p.name>>p.itemName>>p.country>>p.quantity>>p.quantitytype>>p.price>>sellingPrice>>totBuyingAmount;
			while(purchase.good())
			{
				totalPurchase += totBuyingAmount;
				purchase>>p.d>>p.m>>p.y>>p.name>>p.itemName>>p.country>>p.quantity>>p.quantitytype>>p.price>>sellingPrice>>totBuyingAmount;
			}
			
			expen>>exp.day>>exp.month>>exp.year>>exp.name>>exp.amount;
			while(expen.good())
			{
				gotoxy(40,i);
				cout<<exp.day<<"/"<<exp.month<<"/"<<exp.year;
					
				gotoxy(58,i);
				cout<<exp.name;
					
				gotoxy(78,i);
				cout<<exp.amount;
			
				totexp+=exp.amount;
				
				i=i+1;	
				
				expen>>exp.day>>exp.month>>exp.year>>exp.name>>exp.amount;
			}
			
			
			totPro = totSales-totalPurchase;
			
			
			cout<<"\n\n\nTotal Expenses Amount = "<<totexp;
			cout<<"\nTotal profit = "<<totPro;
			cout<<"\nRemaining Amount= "<<totPro-totexp;
			
			getchar();
			getch();
			sale.close();
			expen.close();
			purchase.close();
			
			setChoice();
		}
		//****************************************** Update Chemical*************************************************
		void updateChemical()
		{
			textcolor(240);
			float newQuantity ,buyingPrice ,totBuyingAmount , newPrice;
			int date , month , year;
			int sPrice;
			string suppName;
			int  sNO;
			fstream List1;
			fstream List2;
			fstream purchase;
			
			List1.open("Chemical List.txt",ios::in );
			List2.open("list2.txt",ios::out);
			purchase.open("Purchase list.txt",ios::app);
			
			if(!List1.is_open())
			{
				cout<<"File not opened\n";
			}
			
			if(!List2.is_open())
			{
				cout<<"File not opened\n";
			}
			
			if(!purchase.is_open())
			{
				cout<<"File not opened\n";
			}
			
			List1>>sNO>>o.d>>o.m>>o.y>>o.name>>o.itemName>>o.country>>o.quantity>>o.quantitytype>>buyingPrice>>o.price>>totBuyingAmount;	
			
			system("cls");
			LOGO();
				
			while(List1.good())
		    {
	    		if(o.quantity<50)
				{
					cout<<endl<<"\t\t"<<o.itemName<<" Has Less Than 50 Quantity Please Update: "<<endl<<endl;
					
					cout<<"\t\tEnter Date[DD/MM/YYYY]: ";
					cin >> date >> month >> year;
					
					cout<<"\t\tEnter Supplier Name : ";
					cin>>suppName;
					
					cout<<"\t\tEnter The New Quantity : ";
			        cin>>newQuantity;
			        
			        cout<<"\t\tEnter The Price : ";
			        cin>>newPrice;
			        
			        cout<<"\t\tEnter The Selling Price : ";
			        cin>>sPrice;
			        
			        List2 <<sNO<<" "<<o.d<<" "<<o.m<<" "<<o.y<<" "<<o.name<<" "<<o.itemName<<" "<<o.country<<" "<<(o.quantity+newQuantity)<<" "<<o.quantitytype<<" "<<newPrice<<" "<<sPrice<<" "<<totBuyingAmount<<endl;
					purchase <<date<<" "<<month<<" "<<year<<" "<<suppName<<" "<<o.itemName<<" "<<o.country<<" "<<newQuantity<<" "<<o.quantitytype<<" "<<newPrice<<" "<<sPrice<<" "<<(sPrice*newQuantity)<<endl;
				
				}
				else
				{
		            List2 <<sNO<<" "<<o.d<<" "<<o.m<<" "<<o.y<<" "<<o.name<<" "<<o.itemName<<" "<<o.country<<" "<<o.quantity<<" "<<o.quantitytype<<" "<<buyingPrice<<" "<<o.price<<" "<<totBuyingAmount<<endl;
				}
				List1>>sNO>>o.d>>o.m>>o.y>>o.name>>o.itemName>>o.country>>o.quantity>>o.quantitytype>>buyingPrice>>o.price>>totBuyingAmount;	
			
				
		    }

		    List1.clear();
		    List1.close();
		    List2.close();
		    List2.open("list2.txt",ios::in);
		    List1.open("Chemical List.txt",ios::out);
		    List2>>sNO>>o.d>>o.m>>o.y>>o.name>>o.itemName>>o.country>>o.quantity>>o.quantitytype>>buyingPrice>>o.price>>totBuyingAmount;	
			    
		    while(List2.good())
		    {
				List1 <<sNO<<" "<<o.d<<" "<<o.m<<" "<<o.y<<" "<<o.name<<" "<<o.itemName<<" "<<o.country<<" "<<o.quantity<<" "<<o.quantitytype<<" "<<buyingPrice<<" "<<o.price<<" "<<totBuyingAmount<<endl;
				List2>>sNO>>o.d>>o.m>>o.y>>o.name>>o.itemName>>o.country>>o.quantity>>o.quantitytype>>buyingPrice>>o.price>>totBuyingAmount;	
			
			}
			remove("list2.txt");  
		    List2.close();
		    system("cls");
		    setChoice();
		}
		//****************************************** Purchase Detail*************************************************
		void PurchaseDetail()
		{
			textcolor(240);
			int task;
			string sName;
			long int totalPurchase;
			int d,m,y,b,s,t,q;
			string n,in,c,qt;
			system("cls");
			LOGO();
			long int totBuyingAmount;
			cout<<"\t\t\t\t\t\t     -----------------\n";
			cout<<"\t\t\t\t\t\t       Purchase Record\t\t\n";
			cout<<"\t\t\t\t\t\t     -----------------\n\n";
			
			cout << "\t\t 1.Display Full list"<<endl;
			cout << "\t\t 2.Search by Name"<<endl;
			cout << "\t\t 3.go to menu"<<endl;
		
			cout<<"\n\n\t\tTo Perform The Given Task Enter The Number :  ";
			cin>>task;
			if(task == 1){
			system("cls");
			LOGO();

			cout<<"\t\t\t\t\t\t     ---------------\n";
			cout<<"\t\t\t\t\t\t       Purchase Record\t\t\n";
			cout<<"\t\t\t\t\t\t     ---------------\n\n";
	
			fstream purchase;
			purchase.open("Purchase list.txt",ios::in);
			
			if(!purchase.is_open())
			{
				cout<<"File not opened\n";
				setChoice();
			}
			
			purchase>>o.d>>o.m>>o.y>>o.name>>o.itemName>>o.country>>o.quantity>>o.quantitytype>>buyingPrice>>o.price>>totBuyingAmount;
			
			int r=13;
			
			gotoxy(0,11);
			cout<<"Date";
			gotoxy(15,11);
			cout<<"Seller Name";	
		 	gotoxy(30,11);
			cout<<"Item";
			gotoxy(45,11);
			cout<<"Country";
			gotoxy(60,11);
			cout<<"Quantity";
			gotoxy(75,11);
			cout<<"Type";
			gotoxy(90,11);
			cout<<"Buying Price";
			gotoxy(105,11);
			cout<<"Total"<<endl;
			
			cout<<"========================================================================================================================"<<endl;

			while(!purchase.eof()){
		
			gotoxy(0,r);
			cout<<o.d<<"/"<<o.m<<"/"<<o.y;
			gotoxy(15,r);
			cout<<o.name;	
		 	gotoxy(30,r);
			cout<<o.itemName;
			gotoxy(45,r);
			cout<<o.country;
			gotoxy(60,r);
			cout<<o.quantity;
			gotoxy(75,r);
			cout<<o.quantitytype;
			gotoxy(90,r);
			cout<<buyingPrice;
			gotoxy(105,r);
			cout<<totBuyingAmount;	
			totalPurchase=totalPurchase+totBuyingAmount;
			r++;
			purchase>>o.d>>o.m>>o.y>>o.name>>o.itemName>>o.country>>o.quantity>>o.quantitytype>>buyingPrice>>o.price>>totBuyingAmount;
			}
			purchase.close();
			
			cout<<"\n\n\nTotal Purchase ="<<totalPurchase;
			
			getch();
			PurchaseDetail();
			}
			else if(task==2)
			{
				system("cls");
				LOGO();
			
				cout<<"\t\t\t\t\t\t     ---------------\n";
				cout<<"\t\t\t\t\t\t       Purchase Record\t\t\n";
				cout<<"\t\t\t\t\t\t     ---------------\n\n";
				
				fstream purchase;
				purchase.open("Purchase list.txt",ios::in);
			
				purchase>>o.d>>o.m>>o.y>>o.name>>o.itemName>>o.country>>o.quantity>>o.quantitytype>>buyingPrice>>o.price>>totBuyingAmount;
				
				cout<<"\tEnter the name you want to search :";
				cin>>sName;
			
				int r=13;
			
				gotoxy(0,11);
				cout<<"Date";
				gotoxy(15,11);
				cout<<"Seller Name";	
		 		gotoxy(30,11);
				cout<<"Item";
				gotoxy(45,11);
				cout<<"Country";
				gotoxy(60,11);
				cout<<"Quantity";
				gotoxy(75,11);
				cout<<"Type";
				gotoxy(90,11);
				cout<<"Buying Price";
				gotoxy(105,11);
				cout<<"Total"<<endl;
			
				cout<<"========================================================================================================================"<<endl;

				while(!purchase.eof()){
					if(sName==o.name){
						gotoxy(0,r);
						cout<<o.d<<"/"<<o.m<<"/"<<o.y;
						gotoxy(15,r);
						cout<<o.name;	
		 				gotoxy(30,r);
						cout<<o.itemName;
						gotoxy(45,r);
						cout<<o.country;
						gotoxy(60,r);
						cout<<o.quantity;
						gotoxy(75,r);
						cout<<o.quantitytype;
						gotoxy(90,r);
						cout<<buyingPrice;
						gotoxy(105,r);
						cout<<totBuyingAmount;	
						totalPurchase=totalPurchase+totBuyingAmount;
						r++;
					}
				purchase>>o.d>>o.m>>o.y>>o.name>>o.itemName>>o.country>>o.quantity>>o.quantitytype>>buyingPrice>>o.price>>totBuyingAmount;
				}
				purchase.close();
			
			cout<<"\n\n\nTotal Purchase ="<<totalPurchase;
			getch();
			PurchaseDetail();
			}
			else if(task==3){
				setChoice();
			}
			else{
				cout << "\n\n\t\tInvalid Option Choose Right Option";
				getch();
				PurchaseDetail();
			}
			}
			//****************************************** Sale Detail*************************************************
			void SaleDetail()
			{
			int task;
			textcolor(240);
			long int totalSale=0;
			system("cls");
			LOGO();
			long int totBuyingAmount;
			cout<<"\t\t\t\t\t\t     ---------------\n";
			cout<<"\t\t\t\t\t\t       Sales Record\t\t\n";
			cout<<"\t\t\t\t\t\t     ---------------\n\n";
			
			cout << "\t\t 1.Display Full list"<<endl;
			cout << "\t\t 2.Search by Name"<<endl;
			cout << "\t\t 3.go to menu"<<endl;
		
			cout<<"\n\n\t\tTo Perform The Given Task Enter The Number :  ";
			cin>>task;
			if(task == 1){
			system("cls");
			LOGO();

			cout<<"\t\t\t\t\t\t     ---------------\n";
			cout<<"\t\t\t\t\t\t       Sales Record\t\t\n";
			cout<<"\t\t\t\t\t\t     ---------------\n\n";
	
			fstream sale;
			sale.open("Sale List.txt",ios::in);
			
			if(!sale.is_open())
			{
				cout<<"File not opened\n";
				setChoice();
			}
			
			sale>>o.d>>o.m>>o.y>>o.name>>o.itemName>>o.country>>o.quantity>>o.quantitytype>>o.price>>totBuyingAmount;
			
			int r=13;
			
			gotoxy(0,11);
			cout<<"Date";
			gotoxy(15,11);
			cout<<"Seller Name";	
		 	gotoxy(30,11);
			cout<<"Item";
			gotoxy(45,11);
			cout<<"Country";
			gotoxy(60,11);
			cout<<"Quantity";
			gotoxy(75,11);
			cout<<"Type";
			gotoxy(90,11);
			cout<<"Selling Price";
			gotoxy(105,11);
			cout<<"Total"<<endl;
			
			cout<<"========================================================================================================================"<<endl;

			while(!sale.eof()){
		
			gotoxy(0,r);
			cout<<o.d<<"/"<<o.m<<"/"<<o.y;
			gotoxy(15,r);
			cout<<o.name;	
		 	gotoxy(30,r);
			cout<<o.itemName;
			gotoxy(45,r);
			cout<<o.country;
			gotoxy(60,r);
			cout<<o.quantity;
			gotoxy(75,r);
			cout<<o.quantitytype;
			gotoxy(90,r);
			cout<<o.price;
			gotoxy(105,r);
			cout<<totBuyingAmount;	
			totalSale=totalSale+totBuyingAmount;
			r++;
			sale>>o.d>>o.m>>o.y>>o.name>>o.itemName>>o.country>>o.quantity>>o.quantitytype>>o.price>>totBuyingAmount;
			}
			sale.close();
			
			cout<<"\n\n\nTotal Sales ="<<totalSale;
			
			getch();
			SaleDetail();
			}
			else if(task==2)
			{
				string sName;
				system("cls");
				LOGO();
			
				cout<<"\t\t\t\t\t\t     ----------------\n";
				cout<<"\t\t\t\t\t\t       Sales Record\t\t\n";
				cout<<"\t\t\t\t\t\t     ----------------\n\n";
				
				fstream Sale;
				Sale.open("Sale List.txt",ios::in);
			
				cout<<"\tEnter the name you want to search :";
				cin>>sName;
			
				int r=13;
			
				gotoxy(0,11);
				cout<<"Date";
				gotoxy(15,11);
				cout<<"Buyer Name";	
		 		gotoxy(30,11);
				cout<<"Item";
				gotoxy(45,11);
				cout<<"Country";
				gotoxy(60,11);
				cout<<"Quantity";
				gotoxy(75,11);
				cout<<"Type";
				gotoxy(90,11);
				cout<<"Selling Price";
				gotoxy(105,11);
				cout<<"Total"<<endl;
			
				cout<<"========================================================================================================================"<<endl;
				
				Sale>>o.d>>o.m>>o.y>>o.name>>o.itemName>>o.country>>o.quantity>>o.quantitytype>>o.price>>totBuyingAmount;
				
				while(!Sale.eof()){
					if(sName==o.name){
					gotoxy(0,r);
					cout<<o.d<<"/"<<o.m<<"/"<<o.y;
					gotoxy(15,r);
					cout<<o.name;	
				 	gotoxy(30,r);
					cout<<o.itemName;
					gotoxy(45,r);
					cout<<o.country;
					gotoxy(60,r);
					cout<<o.quantity;
					gotoxy(75,r);
					cout<<o.quantitytype;
					gotoxy(90,r);
					cout<<o.price;
					gotoxy(105,r);
					cout<<totBuyingAmount;	
					totalSale=totalSale+totBuyingAmount;
					r++;
		    }
			Sale>>o.d>>o.m>>o.y>>o.name>>o.itemName>>o.country>>o.quantity>>o.quantitytype>>o.price>>totBuyingAmount;
			}
			Sale.close();
			
			cout<<"\n\n\nTotal Sale ="<<totalSale;
			getch();
			SaleDetail();
			}
			else if(task==3){
				setChoice();
			}
			else{
				cout << "\n\n\t\tInvalid Option Choose Right Option";
				getch();
				SaleDetail();
			}
		}
		//****************************************** References Chemical List*************************************************
		void ReferenceList()
		{
			textcolor(240);
			int task,task2;
			string chemicalName,supName,contact,sName;
			system("cls");
			LOGO();
			cout<<  "\t\t\t\t\t\t****************************  ";
			cout<<  "\n\t\t\t\t\t\t      Refernce Chemical List";
			cout<<  "\n\t\t\t\t\t\t****************************\n\n\n";
			cout<<"\t\t1. Add Chemical\n";
			cout<<"\t\t2. Search Chemical By Name\n";
			cout<<"\t\t3. Display Full list\n";
			cout<<"\t\t4. To go back to main menu\n";
			cout<<"\n\n\t\t Choose from the following : ";
			cin>>task;
			
			if(task==1){
				task2=1;
				while(task2=1){
					
					fstream rList;
					rList.open("referenceList.txt",ios::app);
					system("cls");
					LOGO();
					
					cout<<  "\t\t\t\t\t\t*******************  ";
					cout<<  "\n\t\t\t\t\t\t      Add Chemical ";
					cout<<  "\n\t\t\t\t\t\t*******************\n\n\n";	
				
					cout << "\t\t Enter the Chemical Name : ";
					cin >>chemicalName;
					cout << "\t\t Enter the Supplier Name : ";
					cin >>supName;
					cout<<"\t\t Enter the Contact Number : ";
					cin>>contact;	
				
					rList<<chemicalName<<" "<<supName<<" "<<contact<<endl;
					rList.close();
					A:				
					cout<<"\n\n\t\t[Press 1] to Add more Chemical OR [Press 2] to go Back : ";
					cin>>task2;
					if(task2==1){
					}
					else if(task2==2){
						ReferenceList();
					}
					else{
						cout<<"\t\tInvalid option"<<endl;
						getch();
						goto A;
					}
					
				}	
			}
			else if(task==2){
					fstream rList;
					rList.open("referenceList.txt",ios::in);
					
					if(!rList.is_open())
					{
						cout<<"File not opened\n";
						setChoice();
					}
					system("cls");
					LOGO();
					cout<<  "\t\t\t\t\t\t********************* ";
					cout<<  "\n\t\t\t\t\t\t      Search Chemical ";
					cout<<  "\n\t\t\t\t\t\t*********************\n\n";	
					
					cout<<"\t\tEnter the name to search : ";
					cin>>sName;
					gotoxy(10,10);
					cout<<"S:no";
					gotoxy(20,10);
					cout<<"Chemical Name";
					gotoxy(40,10);
					cout<<"Supplier Name";
					gotoxy(60,10);
					cout<<"Contact";
					cout <<"\n======================================================================================================================="<<endl;
					rList>>chemicalName>>supName>>contact;
					int i,r=12;
					i=1;
					while(rList.good()){
						
						if(sName==chemicalName){
							gotoxy(10,r);
							cout<<i;
							gotoxy(20,r);
							cout<<chemicalName;
							gotoxy(40,r);
							cout<<supName;
							gotoxy(60,r);
							cout<<contact;
							i++;
							r++;
						}
					rList>>chemicalName>>supName>>contact;	
					}
					getch();
					ReferenceList();
			}
			else if(task==3){
					fstream rList;
					rList.open("referenceList.txt",ios::in);
					
					if(!rList.is_open())
					{
						cout<<"File not opened\n";
						setChoice();
					}
					
					system("cls");
					LOGO();
					cout<<  "\t\t\t\t\t\t*********************  ";
					cout<<  "\n\t\t\t\t\t\t      Search Chemical ";
					cout<<  "\n\t\t\t\t\t\t*********************\n\n";	
					
	
					gotoxy(10,10);
					cout<<"S:no";
					gotoxy(20,10);
					cout<<"Chemical Name";
					gotoxy(40,10);
					cout<<"Supplier Name";
					gotoxy(60,10);
					cout<<"Contact";
					cout <<"\n===================================================================================================================="<<endl;
					rList>>chemicalName>>supName>>contact;
					int i,r=12;
					i=1;
					while(rList.good()){
						
							gotoxy(10,r);
							cout<<i;
							gotoxy(20,r);
							cout<<chemicalName;
							gotoxy(40,r);
							cout<<supName;
							gotoxy(60,r);
							cout<<contact;
							i++;
							r++;
					rList>>chemicalName>>supName>>contact;	
					}
					
					getch();
					ReferenceList();
			}
			else if(task == 4){
				setChoice();
			}
			else{
				cout << "\t\t\t\tInvalid option"<<endl;
				getch();
				ReferenceList();
			}
		}
};
//****************************************** CLASS Bank*************************************************
class Bank 
{
	friend void setChoice();
	struct bank_detalis d;
	struct bank_detalis c;
	
	public:
	Bank()
	{
	}
	//****************************************** Add Debit*************************************************	
	void addDebit()
	{	
			textcolor(240);
			fstream debit;
			debit.open("Debit List.txt",ios::app);
			
		    
			do{
				system("cls");
				LOGO();
				
				cout<<"\t\t\t\t\t\t        -------------\n";
				cout<<"\t\t\t\t\t\t         Debit Entry\t\t\n";
				cout<<"\t\t\t\t\t\t        -------------\n";
				
				cout<<"\t\t Enter Date[DD/MM/YYYY]: ";
				cin >> d.d >> d.m >> d.y;
				
				cout<<"\t\t Enter Name: ";
				cin >> d.name;
				
				cout<<"\t\t Enter Bank Name :";
				cin >> d.bankName;
				
				cout<<"\t\t Enter Amount Type:";
				cin >> d.cashType;
				
				cout<<"\t\t Enter Debit Amount :";
				cin >> d.amount;
				
				debit <<d.d<<" "<<d.m<<" "<<d.y<<" "<<d.name<<" "<<d.bankName<<" "<<d.cashType<<" "<<d.amount<<endl;
				
				cout<<"\n\n\t\tFor More Entries Enter Y for Yes And N For No :";
				getchar();
				cin>>yesNo;
				
				}while(yesNo=='Y' || yesNo=='y');
				
				debit.close();	
				setChoice();
	}
	//****************************************** Add Credit*************************************************
	void addCredit()
	{	
			textcolor(240);
			fstream credit;
			credit.open("Credit List.txt",ios::app);
			
		    
			do{
				system("cls");
				LOGO();
				
				cout<<"\t\t\t\t\t\t        -------------\n";
				cout<<"\t\t\t\t\t\t         Credit Entry\t\t\n";
				cout<<"\t\t\t\t\t\t        -------------\n";
				
				cout<<"\t\t Enter Date[DD/MM/YYYY]: ";
				cin >> c.d >> c.m >> c.y;
				
				cout<<"\t\t Enter Name: ";
				cin >> c.name;
				
				cout<<"\t\t Enter Bank Name :";
				cin >> c.bankName;
				
				cout<<"\t\t Enter Amount Type:";
				cin >> c.cashType;
				
				cout<<"\t\t Enter Credit Amount :";
				cin >> c.amount;
				
				credit <<c.d<<" "<<c.m<<" "<<c.y<<" "<<c.name<<" "<<c.bankName<<" "<<c.cashType<<" "<<c.amount<<endl;
				
				cout<<"\n\n\t\tFor More Entries Enter Y for Yes And N For No :";
				getchar();
				cin>>yesNo;
				
				}while(yesNo=='Y' || yesNo=='y');
				
				credit.close();	
				setChoice();
	}
	//****************************************** Search Debit*************************************************
	void searchDebit()
	{
		textcolor(240);
		int i=1 , task;
		string Sname;
		
		system("cls");
		LOGO();
		
		cout<<"\t\t\t\t\t\t     ---------------\n";
		cout<<"\t\t\t\t\t\t       Debit Details\t\t\n";
		cout<<"\t\t\t\t\t\t     ---------------\n";
		
	
		cout << "\t\t 1.Display Full list"<<endl;
		cout << "\t\t 2.Search by Name"<<endl;
		cout << "\t\t 3.go to menu"<<endl;
		
		cout<<"\n\n\t\tTo Perform The Given Task Enter The Number :  ";
		cin>>task;
		
			if(task==1)
			{
				system("cls");
				LOGO();
				
				fstream debit;
				debit.open("Debit List.txt",ios::in);
				
				if(!debit.is_open())
				{
					cout<<"File not opened\n";
					setChoice();
				}
				
				cout<<"\t\t\t\t\t\t     ---------------\n";
				cout<<"\t\t\t\t\t\t       Debit Details\t\t\n";
				cout<<"\t\t\t\t\t\t     ---------------\n";
			
				cout<<"\n\t\t\tS.No\tDate\t\tName\t\tBank Name\tCash Type\tDebit"<<endl;
				cout<<"========================================================================================================================"<<endl;
				
				debit>>d.d>>d.m>>d.y>>d.name>>d.bankName>>d.cashType>>d.amount;
								
				while(!debit.eof())
				{
					cout<<"\t\t\t";
					
					cout <<i<<"\t"<< d.d<<"/"<<d.m<<"/"<<d.y<<"\t" <<d.name<<"\t\t"<<d.bankName<<"\t" << d.cashType<<"\t\t" << d.amount<<endl;
					i++	;
					debit>>d.d>>d.m>>d.y>>d.name>>d.bankName>>d.cashType>>d.amount;
				}
				
				debit.close();
				getch();
				searchDebit();	
			}
			else if(task == 2)
			{
				system("cls");
				LOGO();
				
				fstream debit;
				debit.open("Debit List.txt",ios::in);
				
				if(!debit.is_open())
				{
					cout<<"File not opened\n";
					setChoice();
				}
				
				cout<<"\t\t\t\t\t\t     ---------------\n";
				cout<<"\t\t\t\t\t\t       Debit Details\t\t\n";
				cout<<"\t\t\t\t\t\t     ---------------\n";
				
				cout<<"\t\t Enter The Name To Be Searched:  ";
				cin >>Sname;
				
				system("cls");
				LOGO();
				
				cout<<"\t\t\t\t\t\t     ---------------\n";
				cout<<"\t\t\t\t\t\t       Debit Details Of "<<Sname<<"\t\t\n";
				cout<<"\t\t\t\t\t\t     ---------------\n";
				
				cout<<"\n\t\t\tS.No\tDate\t\tBank Name\tCash Type\tDebit"<<endl;
				cout<<"========================================================================================================================"<<endl;
				
				debit>>d.d>>d.m>>d.y>>d.name>>d.bankName>>d.cashType>>d.amount;
				
				while(!debit.eof())
				{
					if(Sname == d.name)
					{
						cout<<"\t\t\t" <<i<<"\t"<<d.d<<"/"<<d.m<<"/"<<d.y<<"\t" << d.bankName<<"\t" << d.cashType<<"\t\t" << d.amount<<endl;
						i++	;
					}
					debit>>d.d>>d.m>>d.y>>d.name>>d.bankName>>d.cashType>>d.amount;
				}
				debit.close();
				getch();
				searchDebit();	
			}
			else
			{
				setChoice();
			}	
		}
		//****************************************** Search Credit*************************************************
	void searchCredit()
	{
		textcolor(240);
		int i=1 , task;
		string Sname;
		
		system("cls");
		LOGO();
		
		cout<<"\t\t\t\t\t\t     ---------------\n";
		cout<<"\t\t\t\t\t\t      Credit Details\t\t\n";
		cout<<"\t\t\t\t\t\t     ---------------\n";
		
	
		cout << "\t\t 1.Display Full list"<<endl;
		cout << "\t\t 2.Search by Name"<<endl;
		cout << "\t\t 3.go to menu"<<endl;
		
		cout<<"\n\n\t\tTo Perform The Given Task Enter The Number :  ";
		cin>>task;
		
			if(task==1)
			{
				system("cls");
				LOGO();
				
				fstream credit;
				credit.open("Credit List.txt",ios::in);
				
				if(!credit.is_open())
				{
					cout<<"File not opened\n";
					setChoice();
				}
				
				cout<<"\t\t\t\t\t\t     ---------------\n";
				cout<<"\t\t\t\t\t\t      Credit Details\t\t\n";
				cout<<"\t\t\t\t\t\t     ---------------\n";
			
				cout<<"\n\t\t\tS.No\tDate\t\tName\t\tBank Name\tCash Type\tCredit"<<endl;
				cout<<"========================================================================================================================"<<endl;
				
				credit>>c.d>>c.m>>c.y>>c.name>>c.bankName>>c.cashType>>c.amount;
								
				while(!credit.eof())
				{
					cout<<"\t\t\t";
					
					cout <<i<<"\t"<< c.d<<"/"<<c.m<<"/"<<c.y<<"\t" <<c.name<<"\t\t"<<c.bankName<<"\t" << c.cashType<<"\t\t" << c.amount<<endl;
					i++	;
					credit>>c.d>>c.m>>c.y>>c.name>>c.bankName>>c.cashType>>c.amount;
				}
				
				credit.close();
				getch();
				searchCredit();	
			}
			else if(task == 2)
			{
				system("cls");
				LOGO();
				
				fstream credit;
				credit.open("Credit List.txt",ios::in);
				
				if(!credit.is_open())
				{
					cout<<"File not opened\n";
					setChoice();
				}
				
				cout<<"\t\t\t\t\t\t     ---------------\n";
				cout<<"\t\t\t\t\t\t      Credit Details\t\t\n";
				cout<<"\t\t\t\t\t\t     ---------------\n";
				
				cout<<"\t\t Enter The Name To Be Searched:  ";
				cin >>Sname;
				
				system("cls");
				LOGO();
				
				cout<<"\t\t\t\t\t\t     ---------------\n";
				cout<<"\t\t\t\t\t\t      Credit Details\t\t\n";
				cout<<"\t\t\t\t\t\t     ---------------\n";
				
				cout<<"\n\t\t\tS.No\tDate\t\tBank Name\tCash Type\tCredit"<<endl;
				cout<<"========================================================================================================================"<<endl;
				
				credit>>c.d>>c.m>>c.y>>c.name>>c.bankName>>c.cashType>>c.amount;
				
				while(!credit.eof())
				{
					if(Sname == c.name)
					{
						cout<<"\t\t\t" <<i<<"\t"<<c.d<<"/"<<c.m<<"/"<<c.y<<"\t" << c.bankName<<"\t" << c.cashType<<"\t\t" << c.amount<<endl;
						i++	;
					}
					credit>>c.d>>c.m>>c.y>>c.name>>c.bankName>>c.cashType>>c.amount;
				}
				credit.close();
				getch();
				searchCredit();	
			}
			else
			{
				setChoice();
			}	
		}
		//****************************************** CashBook*************************************************
		void cashbook()
		{
			textcolor(240);
			int i = 1, r;
			long int totalCredit = 0 ,totalDebit = 0 , Balance = 0;
		
			system("cls");
			LOGO();
			
			cout<<"\t\t\t\t\t\t     ---------------\n";
			cout<<"\t\t\t\t\t\t         CashBook\t\t\n";
			cout<<"\t\t\t\t\t\t     ---------------\n\n";
			
			fstream credit;
			fstream debit;
			
			credit.open("Credit List.txt",ios::in);
			debit.open("Debit List.txt",ios::in);
			
			if(!credit.is_open())
			{
				cout<<"File not opened\n";
				setChoice();
			}
				
			if(!debit.is_open())
			{
				cout<<"File not opened\n";
				setChoice();
			}
			
			credit>>c.d>>c.m>>c.y>>c.name>>c.bankName>>c.cashType>>c.amount;
			debit>>d.d>>d.m>>d.y>>d.name>>d.bankName>>d.cashType>>d.amount;
			
			cout <<"\t"<< "S:no\t"<<"Recived Date\t"<<"Recived Name\t"<<"Recived Amount"<<"\t"<<"Paid Date\t"<<"Paid Name\t"<<"Paid Amount"<<endl;
			cout<<"========================================================================================================================"<<endl;
			
			while(debit.good())
			{
				cout <<"\t"<< i<<"\t"<<d.d<<"/"<<d.m<<"/"<<d.y<<"\t"<<d.name<<"\t\t"<<d.amount<<endl;
				totalDebit=totalDebit+d.amount;
				debit>>d.d>>d.m>>d.y>>d.name>>d.bankName>>d.cashType>>d.amount;
				i++;
			}
			debit.close();
			r=10;
			
			while(credit.good())
			{
				gotoxy(50,r);
				cout<<"\t\t"<<c.d<<"/"<<c.m<<"/"<<c.y<<"\t"<<c.name<<"\t\t"<<c.amount<<endl;
				totalCredit=totalCredit+c.amount;
				credit>>c.d>>c.m>>c.y>>c.name>>c.bankName>>c.cashType>>c.amount;
				r++;
			}
			credit.close();
			
			Balance=totalDebit-totalCredit;
			
			cout<< "\n\n\n\t Credit ="<<totalCredit<<endl;
			cout<<"\t Debit ="<<totalDebit<<endl;
			cout<<"\t Balance ="<<Balance;
			getch();
			setChoice();
		}
		//****************************************** Bank Statement*************************************************
		void BankStatement()
		{
			textcolor(240);
			string sname;
			int Task;
			long int totalCredit=0,totalDebit=0,Balance=0;
			
			system("cls");
			LOGO();
			
			cout<<"\t\t\t\t\t\t     ---------------\n";
			cout<<"\t\t\t\t\t\t      Bank Statement   \t\t\n";
			cout<<"\t\t\t\t\t\t     ---------------\n\n";
		
			fstream debit,credit;
			
			debit.open("Debit List.txt",ios::in);
			credit.open("Credit List.txt",ios::in);
			
			if(!credit.is_open())
			{
				cout<<"File not opened\n";
				setChoice();
			}
				
			if(!debit.is_open())
			{
				cout<<"File not opened\n";
				setChoice();
			}
			
			credit>>c.d>>c.m>>c.y>>c.name>>c.bankName>>c.cashType>>c.amount;
			debit>>d.d>>d.m>>d.y>>d.name>>d.bankName>>d.cashType>>d.amount;
			
			cout <<"\t\t Enter The Name Of Bank To Be Searched:  ";
			cin>>sname;
			
			system("cls");
			LOGO();
			
			cout<<"\t\t\t\t\t\t     ----------------------------\n";
			cout<<"\t\t\t\t\t\t      Bank Statement Of "<<sname<<"\t\t\n";
			cout<<"\t\t\t\t\t\t     ----------------------------\n\n";
			
			cout << "\t\t    Debited Date\t"<<"Debited Amount\t\t"<<" Credited Date\t"<<"    Creadited Amount"<<endl;
			cout << "======================================================================================================================="<<endl;
			
			while(debit.good())
			{
				if(sname==d.bankName)
				{
					cout<<"\t\t     "<<d.d <<"/"<<d.m<<"/"<<d.y<<"\t\t"<<d.amount<<endl;
					totalDebit=totalDebit+d.amount;	
				}
				debit>>d.d>>d.m>>d.y>>d.name>>d.bankName>>d.cashType>>d.amount;
			}
			debit.close();
			int r=10;
			while(credit.good())
			{
				if(sname==c.bankName)
				{
					gotoxy(49,r);
					cout<<"\t\t  "<<c.d <<"/"<<c.m<<"/"<<c.y<<"\t\t"<<c.amount<<endl;	
					r++;
					totalCredit=totalCredit+c.amount;
				
				}
				credit>>c.d>>c.m>>c.y>>c.name>>c.bankName>>c.cashType>>c.amount;
			}
			
			gotoxy(0,17);
			cout<<"Total Debit Amount : "<<totalDebit<<endl;
			cout<<"Total Credit Amount : "<<totalCredit<<endl;
			cout <<"Bank Statement of "<<sname<<"  : "<<totalDebit-totalCredit;
			credit.close();
			getch();
			setChoice();			 
		}

};
void setChoice()
	{
		struct order o ;
		class Manager M;
		class Bank b;
		fstream warning;
		int task , sNO , i = 27;
		float buyingPrice , totBuyingAmount ;
		system("cls");
		LOGO();
		t();
		textcolor(240);
		
		cout<<"\t\t\t\t\t\t\t\t\t     ---------------\n";
		cout<<"\t\t\t\t\t\t        Main Menu\t\t\n";
		cout<<"\t\t\t\t\t\t     ---------------\n";
		
		cout<<"\n";
		
		cout<<"\t\t 1. Purchase Item\n";
		cout<<"\t\t 2. Enter Debit\n";
		cout<<"\t\t 3. Enter Credit\n";
		cout<<"\t\t 4. Sales And Purchase\n";
		cout<<"\t\t 5. Purchase details\n";
		cout<<"\t\t 6. Selling details\n";
		cout<<"\t\t 7. CashBook\n";
		cout<<"\t\t 8. Debit Details\n";
		cout<<"\t\t 9. Credit Details\n";
		cout<<"\t\t 10. Bank Statement\n";
		cout<<"\t\t 11. Chemical List\n";
		cout<<"\t\t 12. Ledger\n";
		cout<<"\t\t 13. Enter Expenses\n";
		cout<<"\t\t 14. Expenses Account\n";
		cout<<"\t\t 15. Update Chemical Less Than 50 ";
		cout<<"\t\t 16. Exit";
		
		
	    
	    warning.open("Chemical List.txt",ios::in);
	    
	    warning>>sNO>>o.d>>o.m>>o.y>>o.name>>o.itemName>>o.country>>o.quantity>>o.quantitytype>>buyingPrice>>o.price>>totBuyingAmount;
	        		
		while(warning.good())
		{
			if(o.quantity<50)
			{
				gotoxy(50,i);
				textcolor(252);
				cout<<endl<<"WARNING : "<<o.itemName<<" Is Left With Only "<<o.quantity<<" "<<o.quantitytype<<endl;
			}
			i++;
			textcolor(271);
					
			warning>>sNO>>o.d>>o.m>>o.y>>o.name>>o.itemName>>o.country>>o.quantity>>o.quantitytype>>buyingPrice>>o.price>>totBuyingAmount;
	    
		}
		
		textcolor(240);
		gotoxy(16,24);
		cout<<"\n\n\t\tTo Perform The Given Task Enter The Number :  ";
	    cin>>task;
	    
		if(task==1)
		{
			M.purchaseItem();
		}
		else if(task==2)
		{
			b.addDebit();
		}
		else if(task==3)
		{
			b.addCredit();
		}
		else if(task==4)
		{
			M.SalePurchase();
		}
		else if(task==5)
		{
			M.PurchaseDetail();
		}
		else if(task==6)
		{
			M.SaleDetail();
		}
		else if(task==7)
		{
			b.cashbook();
		}
		else if(task==8)
		{
			b.searchDebit();
		}
		else if(task==9)
		{
			b.searchCredit();
		}
		else if(task==10)
		{
			b.BankStatement();
		}
		else if(task==11)
		{
			M.ReferenceList();
		}
		else if(task==12)
		{
			M.ledger();
		}
		else if(task==13)
		{
			M.addExpenses();
		}
		else if(task==14)
		{
			M.expensesAccount();
		}
		else if(task==15)
		{
			M.updateChemical();
		}
		else
		{
			system("cls");
			main();
		}
	}
void login()
{
	int task, attemp=3 , p=0;
	char user[20]={"admin"};
	char pas[20]={"admin"};
	char pasword[20],username[20]; 
	
	system("cls");

		int a=0,i=0;
    	char uname[10],c=' '; 
    	char pword[10],code[10];
    	char pass[10]="admin";
		
    	do
		{
			textcolor(240);
			LOGO();
    		cout<<" \n\n \t\t\t\t                    USERNAME = ";
			cin>>uname; 
			
			cout<<" \n\n \t\t\t\t                    PASSWORD = ";
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
					cout<<"*";
	    			i++;
	    		}
			}
			pword[i]='\0';
			i=0;
			
			if(strcmp(uname,"admin")==0 && strcmp(pword,"admin")==0)
			{
				cout<<"  \n\n\n \t\t         WELCOME TO PAK CHEMICAL MANAGEMENT SYSTEM !!!! YOUR LOGIN IS SUCCESSFUL";
				textcolor(242);
				cout<<"\n\n\n\t\t\t                       Press any key to continue...";
				getch();//holds the screen
				setChoice();
			}
			else
			{
				textcolor(252);
				cout<<"\n\n\n\t\t\t        SORRY !!!!  LOGIN IS UNSUCESSFUL!";
				a++;
			
				getch();//holds the screen
			
			}
			system("cls");
		}
		while(a<=2);
		if (a>2)
		{
			cout<<"\n\t\t\tSorry you have entered the wrong username and password for four times!!!";
			getch();//holds the screen
		}
		else
		{
			exit(1);
		}
}	
int main()
{
	int task ;
	textcolor(240);
	system("cls");
	LOGO();
	
	cout<<"\t\t 1. Customer\n";
	cout<<"\t\t 2. Manager\n";
	cout<<"\t\t 3. Exit\n";
	
	cout<<"\n\n\t\tTo Perform The Given Task Enter The Number :  ";
	cin>>task;
	
	system("cls");
	
	if(task==1)
	{
		Customer obj1;
		obj1.saleItem();
	}
	if(task==2)
	{
		login();
	}
	
}	
