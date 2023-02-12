#include<iostream>
#include<conio.h>
#include<windows.h>
#include<fstream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctime>
#include<string>
#include<vector>
#include<sstream>
#include<stack>
#include<unordered_map>
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
	cout<<"\t\t\t\t\t\t        Chicago Crimes\t\t\n";
	cout<<"\t\t\t\t\t\t*****************************\n";
	
	cout<<"\n";
}

void setChoice();
void preprocessing();
int main();
//****************************************** Classes *************************************************

//****************************************** Class Binary Search Tree *************************************************

class BST
{

    struct node
    {
        string data;
        int count;
        node *left;
        node *right;
        int height;
    };

    node *root;

    void makeEmpty(node *t)
    {
        if (t == NULL)
            return;
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }

    node *insert(string x, node *t)
    {
        if (t == NULL)
        {
            t = new node;
            t->data = x;
            t->height = 0;
            t->left = t->right = NULL;
            t->count++;
        }
        else if (x < t->data)
        {
            t->left = insert(x, t->left);
            if (height(t->left) - height(t->right) == 2)
            {
                if (x < t->left->data)
                    t = singleRightRotate(t);
                else
                    t = doubleRightRotate(t);
            }
        }
        else if (x > t->data)
        {
            t->right = insert(x, t->right);
            if (height(t->right) - height(t->left) == 2)
            {
                if (x > t->right->data)
                    t = singleLeftRotate(t);
                else
                    t = doubleLeftRotate(t);
            }
        }
        else if (x == t->data)
        {
            t->count++;
        }
        t->height = max(height(t->left), height(t->right)) + 1;
        return t;
    }

    node *singleRightRotate(node *&t)
    {
        node *u = t->left;
        t->left = u->right;
        u->right = t;
        t->height = max(height(t->left), height(t->right)) + 1;
        u->height = max(height(u->left), t->height) + 1;
        return u;
    }

    node *singleLeftRotate(node *&t)
    {
        node *u = t->right;
        t->right = u->left;
        u->left = t;
        t->height = max(height(t->left), height(t->right)) + 1;
        u->height = max(height(t->right), t->height) + 1;
        return u;
    }

    node *doubleLeftRotate(node *&t)
    {
        t->right = singleRightRotate(t->right);
        return singleLeftRotate(t);
    }

    node *doubleRightRotate(node *&t)
    {
        t->left = singleLeftRotate(t->left);
        return singleRightRotate(t);
    }

    node *findMin(node *t)
    {
        if (t == NULL)
            return NULL;
        else if (t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }

    node *findMax(node *t)
    {
        if (t == NULL)
            return NULL;
        else if (t->right == NULL)
            return t;
        else
            return findMax(t->right);
    }

    node *remove(string x, node *t)
    {
        node *temp;
        // Element not found
        if (t == NULL)
            return NULL;

        // Searching for element
        else if (x < t->data)
            t->left = remove(x, t->left);
        else if (x > t->data)
            t->right = remove(x, t->right);

        // Element found
        // With 2 children
        else if (t->left && t->right)
        {
            temp = findMin(t->right);
            t->data = temp->data;
            t->right = remove(t->data, t->right);
        }
        // With one or zero child
        else
        {
            temp = t;
            if (t->left == NULL)
                t = t->right;
            else if (t->right == NULL)
                t = t->left;
            delete temp;
        }
        if (t == NULL)
            return t;

        t->height = max(height(t->left), height(t->right)) + 1;

        // If node is unbalanced
        // If left node is deleted, right case
        if (height(t->left) - height(t->right) == 2)
        {
            // right right case
            if (height(t->left->left) - height(t->left->right) == 1)
                return singleLeftRotate(t);
            // right left case
            else
                return doubleLeftRotate(t);
        }
        // If right node is deleted, left case
        else if (height(t->right) - height(t->left) == 2)
        {
            // left left case
            if (height(t->right->right) - height(t->right->left) == 1)
                return singleRightRotate(t);
            // left right case
            else
                return doubleRightRotate(t);
        }
        return t;
    }

    int height(node *t)
    {
        return (t == NULL ? -1 : t->height);
    }

    int getBalance(node *t)
    {
        if (t == NULL)
            return 0;
        else
            return height(t->left) - height(t->right);
    }

    void inorder(node *t,string fileName)
    {
        fstream file3;
        
        file3.open(fileName , ios :: out);
        
        if (!file3.is_open())
        {
            cout << "ERROR";
        }
        stack<node *> stack;

        node *curr = root;

        while (!stack.empty() || curr != NULL)
        {
            if (curr != NULL)
            {
                stack.push(curr);
                curr = curr->left;
            }
            else
            {
                curr = stack.top();
                stack.pop();
                file3 << curr->data << " " << curr->count << " " << endl;
                curr = curr->right;
            }
        }
    }

	public:
    BST()
    {
        root = NULL;
    }

    void insert(string x)
    {
        root = insert(x, root);
    }

    void remove(string x)
    {
        root = remove(x, root);
    }

    void display(string file)
    {
        inorder(root,file);
        cout << endl;
    }
};

//****************************************** Class Chicago Crimes *************************************************

class Chicago_Crimes
{
	BST Community,CrimeRates,district , arrest , typeOfCrimes , particularDate;
	unordered_map<string, vector<string>> CaseNum;
	unordered_map<string, vector<string>> CaseID;
	string hashTag , ID , CaseNumber, Date , Block ,  IUCR , PrimaryType , Description , LocationDescription ;
    string Arrest , Domestic  , Beat , District , Ward , CommunityArea , FBICode , time1 ;
	string XCoordinate , YCoordinate , Year , UpdatedOn , Latitude, Longitude , Location; 
	
	public:
	
	//****************************************** PreProcessing *************************************************
	void PreProcessing()
	{
        fstream file, file2;
        file.open("Chicago_Crimes_2008_to_2017.csv", ios::in);

		system("cls");
		LOGO();
		textcolor(240);
       
        if (!file.is_open())
        {
            cout << "file Not Opened ";
            getch();
            setChoice();
        }
        else
        {
			cout << "\n\n\n\n\n\n\n\t\t\t\t\t\t Loading....";
    		cout.flush();

            while (file.good())
            {
                getline(file, hashTag, ',');
                getline(file, ID, ',');
                getline(file, CaseNumber, ',');
                getline(file, Date ,' ');
				getline(file, time1 , ',');
                getline(file, Block, ',');
                getline(file, IUCR, ',');
                getline(file, PrimaryType, ',');
                getline(file, Description, ',');
                getline(file, LocationDescription, ',');
                getline(file, Arrest, ',');
                getline(file, Domestic, ',');
                getline(file, Beat, ',');
                getline(file, District, ',');
                getline(file, Ward, ',');
                getline(file, CommunityArea, ',');
                getline(file, FBICode, ',');
                getline(file, XCoordinate, ',');
                getline(file, YCoordinate, ',');
                getline(file, Year, ',');
                getline(file, UpdatedOn, ',');
                getline(file, Latitude, ',');
                getline(file, Longitude, ',');
                getline(file, Location, ',');
                getline(file, Location, '\n');

				vector<string> v = 	{Date,Block,PrimaryType,Description,LocationDescription,Arrest,FBICode,Year,UpdatedOn};
				
				CaseNum[CaseNumber] = v;
				CaseID[hashTag] = v;
				v.clear();

				if(District.size() <=  4 && District != "True" && District != " "&& District != "  " && District != "")
				{
					if(stoi(District) >= 1 && stoi(District) <=25)
                		district.insert(District);
				}

				if(Arrest == "True" || Arrest =="False")
				{
					arrest.insert(Arrest);
				}

				typeOfCrimes.insert(PrimaryType);

				if(Date != "Date,Block,IUCR,Primary")
				{
					particularDate.insert(Date);
				}
				
				if(Year == "2008" || Year == "2009" || Year == "2010" || Year == "2011" || Year == "2012" || Year == "2013" || Year == "2014" || Year == "2015" ||  Year == "2017" || Year == "2016")
				{
					CrimeRates.insert(Year);
				}

				if(CommunityArea != "" && CommunityArea != "Community Area" && CommunityArea != " Community Area" && CommunityArea != "False" && CommunityArea != " False" && CommunityArea != " " && CommunityArea != "  " && CommunityArea != "Y Coordinate")
				{
                	Community.insert(CommunityArea);
				}

            }


            file.close();
            file2.close();
            district.display("CrimesInDistrict");
            CrimeRates.display("CrimeRates");
            Community.display("CrimesInComunityArea");
			arrest.display("CriminalsArrestedOrNotArrested");
			typeOfCrimes.display("typeOfCrimesRate");
			particularDate.display("DatesOfCrimes");
        }
    }
	
	//****************************************** Crime Rate Inc Dec*************************************************
	void crime_rate_inc_dec()
	{
		system("cls");
		LOGO();
		textcolor(240);
		
		int year1= 0 , year2 = 0, yearNo = 0 , yearNo1 = 0 , yearNo2 = 0;
		int ye = 0;
		
		cout<<"\t\t Enter The Years Between You Want To Search Crime Rate Is Increased Or Decreased :";
		cin >> year1 >> year2;
	 
		fstream file;
		file.open("CrimeRates", ios::in);
			
			if(!file.is_open() )
			{
				cout << "file Not Opened ";
				getch();
				setChoice();
			}
			
			else
			{ 
				cout<<"\n\n";
				
				file >> ye >> yearNo ;
				
			    while (file.good()) 
				{
					if(year1 == ye)
					{
						yearNo1 = yearNo ;
						
						cout << "\t\t In " <<ye<<" Crimes Were : "<<yearNo<<endl ; 
					}
					
					else if(year2 ==ye)
					{
						yearNo2 = yearNo ;
						
						cout << "\t\t In " <<ye<<" Crimes Were : "<<yearNo<<endl ; 
					}
					
					file >> ye >> yearNo ;
		    	}
		    	
		    	if(yearNo1 > yearNo2)
		    	{
		    		cout <<"\n\n\t\t Crime Rate Is Decreased In "<<year2 ;
				}
				
				else if(yearNo1 < yearNo2)
				{
					cout <<"\n\n\t\t Crime Rate Is Increased In "<<year2 ;
				}
				
				else
				{
					cout <<"\t\t Crime Rate Remained Same Between Years "<<year1<<" and "<<year2 ;
				}
    		}
		
		file.close();
		getch();
		setChoice(); 
	}	
	
	void Search_By_District_Year_CrimeType()
	{	
		system("cls");
		LOGO();
		textcolor(240);
		
		fstream file;
        file.open("Chicago_Crimes_2008_to_2017.csv", ios::in);
       
        if (!file.is_open())
        {
            cout << "file Not Opened ";
            getch();
            setChoice();
        }
        else
        {	
			string dist,yea,CrimeTy;
			
			cout << "\t\t Enter The District No :";
			cin >> dist;
			
			cout << "\t\t Enter The Year :";
			cin >> yea;
			
			cout << "\t\t Enter The Crime Type :";
			cin >> CrimeTy;
			
            cout << "\n\n";
			int crimeCount = 0;
            while (file.good())
            {

                getline(file, hashTag, ',');
                getline(file, ID, ',');
                getline(file, CaseNumber, ',');
                getline(file, Date, ',');
                getline(file, Block, ',');
                getline(file, IUCR, ',');
                getline(file, PrimaryType, ',');
                getline(file, Description, ',');
                getline(file, LocationDescription, ',');
                getline(file, Arrest, ',');
                getline(file, Domestic, ',');
                getline(file, Beat, ',');
                getline(file, District, ',');
                getline(file, Ward, ',');
                getline(file, CommunityArea, ',');
                getline(file, FBICode, ',');
                getline(file, XCoordinate, ',');
                getline(file, YCoordinate, ',');
                getline(file, Year, ',');
                getline(file, UpdatedOn, ',');
                getline(file, Latitude, ',');
                getline(file, Longitude, ',');
                getline(file, Location, ',');
                getline(file, Location, '\n');
				if(District == dist && Year == yea && CrimeTy == PrimaryType)
				{
					crimeCount++;
				}

			}
			cout << "\t\t In " << yea << " There Were " << crimeCount <<" "<< CrimeTy << " in this (" << dist << ") District";
        	
        }
		file.close();
		getch();
		setChoice();
	}
	
	void rate_of_crimes()
	{
		system("cls");
		LOGO();
		textcolor(240);		

		string crime , crime1;
		int noOfCrimes , n =1 ;
		getline(cin , crime);

		fstream file ;
		file.open("typeOfCrimesRate" , ios :: in) ;

		if(!file.is_open())
		{
			cout << "File Not Opened";
			getch();
			setChoice();
		}

		cout <<"\n\n\t\t The Types Of Crimes And Their Rates Which Held In Chicago Between 2007 and 2017 Are : \n\n";

		getline(file , crime1);
		
		while(file.good())
		{
			cout<<" \t\t"<<n<<". "<< crime1 <<endl ;
			n++;
			getline(file , crime1);
		}

		file.close();
		getch();
		setChoice();
		
	}
	
	void criminal_arrested_or_notArrested()
	{
		system("cls");
		LOGO();
		textcolor(240);	

		int num1 , num2 ;
		double n1, n2 ;
		double totCriminals;
		string str ;
		double arrCr , narrCr ;

		fstream file ;
		file.open("CriminalsArrestedOrNotArrested" , ios :: in);

		if(!file.is_open())
		{
			cout << "File Not Opened";
			getch();
			setChoice();
		}

		file >> str >> num1 ;
		cout << " \n\n\t\t The Number Of Criminals Who Are Noe Arrested Are : " << num1 ;
		n1 = num1 ;

		file >> str >> num2 ;
		cout << "\n\n\t\t The Number Of Criminals Who Are Arrested Are : " << num2 ;
		n2 = num2 ;

		totCriminals = n1 + n2 ;
		cout << "\n\n\t\t The Total Number Of Criminals Are : " << num1+num2 ;

		arrCr = ((n2/totCriminals) * 100) ;
		narrCr = ((n1/totCriminals) * 100) ;

		cout<<"\n\n\t\t Percentage Of Arrested Criminals : " << arrCr;
		cout<<"\n\n\t\t Percentage Of Non Arrested Criminals : " << narrCr;

		file.close();
		getch();
		setChoice();
	}
	
	void crimes_by_date_rangeOfPeriod()
	{
		system("cls");
		LOGO();
		textcolor(240);	

		string date1 , date2 ;
		int numOfCrimes = 0 , no = 0;

		cout<<"\t\t Enter The Date [MM/DD/YYYY] For Which You Want To Search No Of Crimes :";
		cin >> date1;
	 
		fstream file;
		file.open("DatesOfCrimes", ios::in);
			
		if(!file.is_open() )
		
		{
			cout << "file Not Opened";
			getch();
			setChoice();
		}	

		file >> date2 >> numOfCrimes ;

		while(file.good())
		{
			if(date1 == date2)
			{
				no = numOfCrimes;
				break ;
			}

			file >> date2 >> numOfCrimes ;
		}

		cout <<"\n\n\t\t At Date "<<date1 << " No of Crimes Held Are : "<<no ;

		file.close();
		getch();
		setChoice();
	}
	
	void district_community_highest_lowest_crime_rate()
	{
		system("cls");
		LOGO();
		textcolor(240);
		int max = 0 , min = 0 ;
		int crims = 0 ;
		float community = 0 ;
		float maxCom = 0 , minCom = 0 ;
		
		fstream file ;
		file.open("CrimesInComunityArea" , ios :: in );
		
		file >> community >> crims ;
		min = crims ;
		minCom = community ;
		
		while(file.good())
		{
			if(crims > max)
			{
				max = crims ;
				maxCom = community  ;
			}
			
			else if(crims < min)
			{
				min = crims ;
				minCom = community ;
			}		
			
			file >> community >> crims ;	
		}
		
		cout<<"\n\n\t\t Community Area : "<<endl<<endl;
		cout << "\t\t The Community Area With Highest Crime Rate Is "<<maxCom<<" with crime rate :"<<max<<endl ;
		cout << "\t\t The Community Area With Lowest Crime Rate Is "<<minCom<<" with crime rate :"<<min<<endl ;	

		file.close();

		file.open("CrimesInDistrict" , ios :: in);

		max = 0 ; min = 0 ; crims = 0 ;
		float dist = 0 , minDist = 0 , maxDist = 0 ;

		file >> dist >> crims ;
		min = crims ;
		minDist = dist ;
		
		while(file.good())
		{
			if(crims > max)
			{
				max = crims ;
				maxDist = dist  ;
			}
			
			else if(crims < min)
			{
				min = crims ;
				minDist = dist ;
			}		
			
			file >> dist >> crims ;	
		}
		
		cout<<"\n\n\t\t District : "<<endl<<endl;
		cout << "\t\t The District With Highest Crime Rate Is "<<maxDist<<" with crime rate :"<<max<<endl ;
		cout << "\t\t The District With Lowest Crime Rate Is "<<minDist<<" with crime rate :"<<min<<endl ;

		file.close();	
		
		getch();
		setChoice(); 
		
	}
	
	void crimes_by_id_caseNumber()
	{
		system("cls");
		LOGO();
		textcolor(240);
		string cNumber;

		cout << "\n\t\t Enter the Case Number To search the case : ";
		cin >> cNumber;

		unordered_map<string,vector<string>> ::iterator itr = CaseNum.find(cNumber);

		if(itr == CaseNum.end())
		{
			cout << "Not Found" << endl;
		}
		else
		{
			vector<string> v = itr->second;
			cout << "\n\t\t Date On Which Crime Happend : " << v[0] << endl;
			cout << "\t\t BLock In Which Crime Happend : " << v[1] << endl;
			cout << "\t\t Primary Type of Crime : " << v[2] << endl;
			cout << "\t\t Description of Crime : " << v[3] << endl;
			cout << "\t\t Location Description : " << v[4] << endl;
			cout << "\t\t Arrest : " << v[5] << endl;
			cout << "\t\t FBI CODE OF THE CRIME : " << v[6] << endl;
			cout << "\t\t Year Of The Crime : " << v[7] << endl;
			cout << "\t\t UpDated ON : " << v[8] << endl; 
		}
		getch();
		setChoice();

	}
	
	void crimes_by_FBIcode()
	{
		system("cls");
		LOGO();
		textcolor(240);		

		string CID;

		cout << "\n\n\t\t Enter the ID of the case To search the case : ";
		cin >> CID;

		unordered_map<string,vector<string>> ::iterator itr = CaseID.find(CID);

		if(itr == CaseID.end())
		{
			cout << "Not Found" << endl;
		}
		
		else
		{
			vector<string> v = itr->second;
			cout << "\n\n\t\t Date On Which Crime Happend : " << v[0] << endl;
			cout << "\t\t BLock In Which Crime Happend : " << v[1] << endl;
			cout << "\t\t Primary Type of Crime : " << v[2] << endl;
			cout << "\t\t Description of Crime : " << v[3] << endl;
			cout << "\t\t Location Description : " << v[4] << endl;
			cout << "\t\t Arrest : " << v[5] << endl;
			cout << "\t\t FBI CODE OF THE CRIME : " << v[6] << endl;
			cout << "\t\t Year Of The Crime : " << v[7] << endl;
			cout << "\t\t UpDated ON : " << v[8] << endl; 
		}

		getch();
		setChoice();
	}
};	

//****************************************** Processing Function Caller *************************************************
class Chicago_Crimes b;

void preprocessing()
{
	b.PreProcessing();
	setChoice();
}

//****************************************** Fuction Caller (SetChoice()) *************************************************

void setChoice()
{
	int task ;

	system("cls");
	LOGO();
	t();
	textcolor(240);
		
		cout<<"\t\t\t\t\t\t\t\t\t     ---------------\n";
		cout<<"\t\t\t\t\t\t        Main Menu\t\t\n";
		cout<<"\t\t\t\t\t\t     ---------------\n";
		
		cout<<"\n";
		
		cout<<"\t\t 1. Check Crime Rate Increasing Or Decreasing\n";
		cout<<"\t\t 2. Search District Crimes By Year And Crime Type\n";
		cout<<"\t\t 3. Search Crime Cases By Case Numbers\n";
		cout<<"\t\t 4. Rates Of Different Type Of Crimes\n";
		cout<<"\t\t 5. Search How Much Criminals Have Been Arrested Or Not Arrested\n";
		cout<<"\t\t 6. Search How Many Crimes Happened At Particular Date\n";
		cout<<"\t\t 7. Check Which District Or Community Area Have Highest/Lowest Crime Rate\n";
		cout<<"\t\t 8. Classify Crime By ID Numbers\n";
		cout<<"\t\t 9. Exit";
		

		cout<<"\n\n\n\t\tTo Perform The Given Task Enter The Number :  ";
	    cin>>task;
	    
		if(task==1)
		{
			b.crime_rate_inc_dec();
		}
		else if(task==2)
		{
			b.Search_By_District_Year_CrimeType();
		}
		else if(task==3)
		{
			b.crimes_by_id_caseNumber();
		}
		else if(task==4)
		{
			b.rate_of_crimes();
		}
		else if(task==5)
		{
			b.criminal_arrested_or_notArrested();
		}
		else if(task==6)
		{
			b.crimes_by_date_rangeOfPeriod();
		}
		else if(task==7)
		{
			b.district_community_highest_lowest_crime_rate();
		}
		else if(task==8)
		{
			b.crimes_by_FBIcode();
		}	
		else
		{
			system("cls");
			exit(1);

		}
	}
	
//****************************************** Login Function *************************************************

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
				cout<<"  \n\n\n \t\t         WELCOME TO CHICAGO CRIMES SERACH SYSTEM !!!! YOUR LOGIN IS SUCCESSFUL";
				textcolor(242);
				cout<<"\n\n\n\t\t\t                       Press any key to continue...";
				getch();//holds the screen
				preprocessing();
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
			main();
		}
}

//****************************************** Main() Function *************************************************

int main()
{
	int task ;
	textcolor(240);
	system("cls");
	LOGO();
	
	Chicago_Crimes Cri ;
	
	cout<<"\t\t 1. Login\n";
	cout<<"\t\t 2. Exit\n";
	
	cout<<"\n\n\t\tTo Perform The Given Task Enter The Number :  ";
	cin>>task;
	
	system("cls");
	
	if(task==1)
	{
		login();
	}
	else
	{
		exit(1);
	}
}	
