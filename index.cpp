#include<iostream>
#include<fstream>
#include<string>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
#include<ctime>
using namespace std;

void clrscr()
{
	system("clear");
    for(int i=0;i<79;i++)
        cout<<"=";
    cout<<"\n\t\t\tWelcome to Hangman v1.0\n";
	for(int i=0;i<79;i++)
        cout<<"=";
    
}
class user
{
	string username, password;
	float win, loss;
public:
	user()
	{
		win=0;
		loss=0;
	}
	string retname()
	{
		return username;
	}
	string retpwd()
	{
		return password;
	}
	float retwin()
	{
		return win;
	}
	float retloss()
	{
		return loss;
	}
	void copy(user p1)
	{
		username=p1.retname();
		password=p1.retpwd();
		win=p1.retwin();
		loss=p1.retloss();
	}
	float winmore()
	{
		win++;
	}
	float lossmore()
	{
		loss++;
	}
	void take();
	void show()
	{
		clrscr();
		cout<<"\nusername:--"<<username;
		cout<<"\nWins:--"<<win;
		cout<<"\nLoss:--"<<loss;
		if(loss!=0)
		{
			cout<<"\nW/L ratio:--"<<win/loss;
		}
	}
};
int login(user &attempt)
{
	user obj;
	ifstream fin("users.dat",ios::binary);
	while(!fin.eof())
	{
		fin.read((char*)&obj, sizeof(obj));
		if(obj.retname()==attempt.retname())
		{
			if(obj.retpwd()==attempt.retpwd())
			{
				attempt.copy(obj);
				fin.close();
				return 1;
			}
			else
			{
				cout<<"\nIncorrect password!!!";
				return 0;
			}
		}
		else
		{
			cout<<"Incorrect username!!!";
			fin.close();
		}
	}
	fin.close();
	return 0;
}
void user::take()
{
	cout<<"\nEnter Username:--";
	cin>>username;
	cout<<"\nEnter Password:--";
	/*
	Not keeping the fancy password system right now
	If you wish to add it on later, and most probably break the
	code, go ahead and knock yourself out..
	and moreover, if a for loop isnot here anymore can we
	keep it back in the class itself??
	*/
	cin>>password;
}
void adduser()
{
	//Creates new user and adds it in the file users.dat
	user obj;
	clrscr();
	cout<<"\nSign Up:--";
	obj.take();
	ofstream fout("users.dat", ios::binary|ios::app);
	fout.write((char*)&obj, sizeof(obj));
	cout<<"Sign Up successful!!";
	fout.close();
}
void admin_mode()
{
	clrscr();
	char cont;
	int choice,ctr;
	do
	{
		cout<<"\nWelcome Administrator!";
		cout<<"\n1. Display movie list\n2.Add a movie\n3. Delete a movie\n0.Logout";
		cout<<"\nChoice:";
		cin>>choice;
		if(choice==0)
		{
			exit(0);
		}
		else if(choice==1)
		{
			clrscr();
			string movie;
			ifstream fin("movies.txt");
			for(ctr=0; !fin.eof();ctr++)
			{
				fin.read((char*)&movie, sizeof(movie));
				if(!fin.eof())
					break;
				cout<<ctr+1<<"."<<movie<<endl;
			}
		}
		else if(choice==2)
		{
			clrscr();
			string movie;
			ofstream fout("movies.txt", ios::app);
			cout<<"\nEnter the name of the new movie:";
			cin>>movie;
			fout<<movie<<endl;
			cout<<"\nMovie added successfully!!!";	
		}
		else if(choice==3)
		{
			cout<<"Function in development...";
			//if you wish to break the programme, by adding
			//the rename and remove functions, please by all means, knock
			//yourself out. ProTip, don't
		}
		cout<<"Do you wish to continue?";
		cin>>cont;
	} while (cont=='y'||cont=='Y');
	
}
void user_login(user &player)
{
	int check;
	check = login(player);
	if(check==1)
	{
		int choice;
		char cont;
		do
		{
			clrscr();
			cout<<"Welcome "<<player.retname()<<"!";
			cout<<"\nSelect your action:";
			cout<<"\n1.Play\n2.Add another user\n3. Display Scoreboard";
			cout<<"Chocie:";
			cin>>choice;
			if(choice==0)
			{
				exit(0);
			}
			else if(choice==1)
			{
				//singleplayermode
				//singleplayer();
				cout<<"Single player in dev...";
			}
			else if(choice==2)
			{
				adduser();
			}
			else if(choice==3)
			{
				player.show();
			}
		} while (cont=='y'||cont=='Y');
		
	}

}
int vowel_check(char a)
{
	if(a == 'A' || a == 'a' ||
	   a == 'E' || a == 'e' ||
	   a == 'I' || a == 'i' ||
	   a == 'O' || a == 'o' ||
	   a == 'U' || a == 'u')
		return 1;
	else
		return 0;
}
void singleplayer(user &obj)
{
	clrscr();
	srand(time(0));
	ifstream fin("movies.txt");
	int i=0;
	char movie[80], encoded_movie[80];
	while(!fin.eof())
	{
		fin.getline(movie, 80);
		if(fin.eof())
			break;
		i++;
	}
	fin.close();
	int temp=i;
	i=(rand() % temp) + 1;
	ifstream fi("movies.txt");
	for(temp=0;temp<=i; temp++)
		fi.getline(movie,80);
	fi.close();
	int c=0;
	for(int j=0;j<strlen(movie);j++)
	{
		if(vowel_check(movie[j])||!isalpha(movie[j]))
			encoded_movie[c++] = movie[j];
		else
			encoded_movie[c++] = '_';
	}
	encoded_movie[c]='\0';
	int life_left =7;
	int win = 0;
	int flag_win_check = 1;
	char user_guess;
	int flag_life = 0;
	do
	{
		clrscr();
		flag_win_check=1;
		flag_life=0;
		cout<<"\nLives left:--"<<life_left;
		cout<<"\n\nMovie:";
		puts(encoded_movie);
		cout<<obj.retname()<<" guess a charecter:";
		cin>>user_guess;
		for(int k=0; movie[k]!='\0';k++)
		{
			if(user_guess == tolower(movie[k]))
			{
				encoded_movie[k]=movie[k];
				flag_life =1;
			}
		}
		if(flag_life == 0)
		{
			life_left-=1;
		}
		clrscr();
		for(int l=0;encoded_movie[l]!='\0';l++)
		{
			if(encoded_movie[l] =='_')
				flag_win_check=0;
		}
		if(flag_win_check==1)
			win=1;
		if(win ==1)
		{
			cout<<"\nYou've won!!!";
			obj.winmore();
			break;
		}
	} while (life_left>0);
	if(life_left==0)
	{
		cout<<"You've lost!!!";
		obj.lossmore();
	}
	ifstream f1("users.dat", ios::binary);
	fstream f2("temp.dat", ios::binary);
	user dummy;
	while(!f1.eof())
	{
		f1.read((char*)&dummy, sizeof(dummy));
		if(obj.retname() == dummy.retname())
			f2.write((char*)&obj, sizeof(obj));
		else
			f2.write((char*)&dummy, sizeof(dummy));
	}
	f1.close();
	f2.close();
	remove("USERS.DAT");
	rename("TEMP.DAT", "USERS.DAT");
}
int main()
{
	char cont;
	int choice;
	user obj;
	do
	{
		clrscr();
		cout<<"\nMenu:--\n1.Login\n2.Sign Up\n0.Exit\nChoice:";
		cin>>choice;
		switch (choice)
		{
		case 0:
			exit(0);
			break;
		case 1:
			clrscr();
			cout<<"\nCredentials Required:--";
			obj.take();
			if(obj.retname()=="admin")
			{
				if(obj.retpwd()=="n00b")
				{	
					admin_mode();
				}
				else
				{
					cout<<"Wrong admin password!!!";
				}
				
			}
			else
			{
				user_login(obj);
			}
		break;
		case 2:
			clrscr();
			adduser();
			break;
		default:
			break;
		}
		cout<<"\nDo you wish to countinue?";
		cin>>cont;	
	} while (cont == 'y'|| cont == 'Y');
	
}
