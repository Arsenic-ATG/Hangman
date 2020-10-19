<<<<<<< HEAD
/*-------------------------------HANGMAN v1.0---------------------------------
Hangman is a popular game where one player writes the name of a movie, with
all the consonants hidden and only vowels and numbers visible. The other
player has to guess the movie name letter by letter. If (s)he guesses a
correct letter, the first player has to fill the appropriate blank spaces with
that letter, else the first letter of the word 'HANGMAN', i.e. H, is written
down. The game continues in a similar fashion. If all the blank spaces are
filled, i.e. the movie name has been guessed correctly, before all the letters
of HANGMAN are written down, then the guessing player wins, otherwise the
player who gave the movie wins.

We have implemented the basics of the game in this program, along with a
rudimentary score-keeping system and a login system. We have used text files to
store scores, but login IDs and passwords are in binary files, as a substitute
for encoding them. As for the version written above, each compilation of the
program corresponds to a 0.1 increase, and each major overhaul, or addition of
new features, or a full 'plugs out' test, corresponds to an increase of 1, so
you can guess our hard work by looking at the version number :)
Enjoy the game!
----------------------------------------------------------------------------*/

//Header files:
#include<fstream.h>
#include<process.h>
=======
#include<fstream>
#include<iostream>
#include<string.h>
>>>>>>> 23ea19d396e961d85197ff20f19962fdfb25ac81
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

//A class to create players of the game
class PLAYER
{
	char login[20], name[20], password[20];
	int wins, losses;
	public:
	PLAYER(){}
	PLAYER(char l[20], char n[20], char p[20])
	{
		strcpy(login, l);
		strcpy(name, n);
		strcpy(password, p);
	}
	void add_User();
	void disp_User()
	{
		cout<<"\nName: "<<name;
		cout<<"\nLogin id: "<<login;
	}
	char* ret_name()	{	return name;	}
	char* ret_login()	{	return login;	}
	char* ret_password()	{	return password;	}
	int ret_win()
	{
		return wins;
	}
	int ret_loss()
	{
		return losses;
	}
	void winmore();
	void losemore();
};
void PLAYER::winmore()
{
	ifstream fin("users.dat", ios::binary);
	ofstream fout("temp.dat", ios::binary);
	PLAYER user;
	wins++;
	while(!fin.eof())
	{
		fin.read((char*)&user, sizeof(user));
		if(fin.eof())
			break;
		if(strcmp(user.ret_login(), login) == 0)
			fout.write((char*)this, sizeof(this));
		else
			fout.write((char*)&user, sizeof(user));
	}
	fin.close();
	fout.close();
	remove("users.dat");
	rename("temp.dat", "users.dat");
}
void PLAYER::losemore()
{
	ifstream fin("users.dat", ios::binary);
	ofstream fout("temp.dat", ios::binary);
	PLAYER user;
	losses++;
	while(!fin.eof())
	{
		fin.read((char*)&user, sizeof(user));
		if(fin.eof())
			break;
		if(strcmp(user.ret_login(), login) == 0)
			fout.write((char*)this, sizeof(this));
		else
			fout.write((char*)&user, sizeof(user));
	}
	fin.close();
	fout.close();
	remove("users.dat");
	rename("temp.dat", "users.dat");
}

void PLAYER::add_User()
{
	cout<<"\nHello new user!";
	do
	{
		cout<<"\nEnter your name: ";
		gets(name);
		if(strcmp(name, "administrator") == 0)
			cout<<"Name not allowed!";
	}while(strcmp(name, "administrator") == 0);
	do
	{
		cout<<"\nEnter your login ID: ";
		gets(login);
		if(strcmp(login, "00000") == 0)
			cout<<"Login id not allowed!";
	}while(strcmp(login, "00000") == 0);
	do
	{
		cout<<"\nEnter your password: ";
		gets(password);
		if(strcmp(password, "admin") == 0)
			cout<<"Password not allowed!";
	}while(strcmp(password, "admin") == 0);
}
//A class to create and store a movie name, and encode it, along with some
//basic functions required to properly implement the game
class MOVIE
{
	char name[20], check_Name[20], code_Name[20];
	int count;
	char hangman[8];
	public:
	MOVIE()
	{	strcpy(hangman, "HANGMAN");
		count = 0;
	}
	void encode();
	void add_Movie(char*);
	void check_Letter(char);
	int check_Win();
	void disp_Hangman();
	char* ret_codename()	{	return code_Name;	}
	int ret_count()	{	return count;	}
};

void MOVIE::encode()
{
	int i = 0, j = 0;
	while(name[i] != '\0')
	{
		if(isalpha(name[i]))
		{
			if(isupper(name[i]))
				check_Name[i] = tolower(name[i]);
		}
		i++;
	}
	while(check_Name[j] != '\0')
	{
		if(isalpha(check_Name[j]))
		{
			if(check_Name[j] == 'a' ||
			   check_Name[j] == 'e' ||
			   check_Name[j] == 'i' ||
			   check_Name[j] == 'o' ||
			   check_Name[j] == 'u')
				code_Name[j] = check_Name[j];
			else
				code_Name[j] = '_';
		}
		else
			code_Name[j] = '_';
		j++;
	}
}

void MOVIE::add_Movie(char moviename[20])
{
	strcpy(name, moviename);
	encode();
}

void MOVIE::check_Letter(char l)
{
	int i = 0;
	while(check_Name[i] != '\0')
	{
		if(check_Name[i] == l)
			code_Name[i] = l;
		else
			count++;
		i++;
	}
}

int MOVIE::check_Win()
{
	int i = 0;
	while(code_Name[i] != '\0')
	{
		if(code_Name[i] == '_')
		{
			count++;
			return 0;
		}
	}
	return 1;
}

void MOVIE::disp_Hangman()
{
	for(int i = 0; i <= count; i++)
		cout<<hangman[i];
}

void new_user(PLAYER p)
{
	clrscr();
	fstream fio;
	fio.open("USERS.dat", ios::out|ios::in|ios::binary|ios::app);
	PLAYER obj;
	while(!fio.eof())
	{
		fio.read((char*)&obj, sizeof(obj));
		if(strcmp(p.ret_name(), obj.ret_name()) == 0 ||
		   strcmp(obj.ret_login(), p.ret_login()) == 0)
		{
			cout<<"\nUser already exists!";
			fio.close();
			return;
		}
	}
	fio.write((char*)&p, sizeof(PLAYER));
	cout<<"\nUser successfully added!";
	fio.close();
}

int check_login(char id[20], char name[20], char password[20])
{
	PLAYER obj;
	int flag=0;
	ifstream fin("USERS.dat", ios::binary);
	while(!fin.eof())
	{
		fin.read((char*)&obj ,sizeof(PLAYER));
		if(strcmp(id, obj.ret_login())==0)
		{
			if(strcmp(name, obj.ret_name())==0)
			{
				if(strcmp(password, obj.ret_password())==0)
				{
					flag=1;
					break;
				}
			}
		}
	}
	fin.close();
	return flag;
}

void view_score(char id[20])
{
	PLAYER obj;
	ifstream fin("USER.txt",ios::in);
	while(!fin.eof())
	{
		fin.read((char*)&obj,sizeof(PLAYER));
		if(strcmp(obj.ret_login(),id)==0)
		{
			cout<<"\nSCORE:";
			cout<<"\nWINS: "<<obj.ret_win();
			cout<<"\nLOSSES: "<<obj.ret_loss();
		}
	}
}

void admin_mode()
{
	clrscr();	char cont;
	cout<<"\nWelcome Administrator!";
	do{
		cout<<"\nSelect your action:";
		cout<<"\n1.View all users\n2.Edit pre-loaded movies\n3.Add more movies\n4.Delete an existing movie\n0.Logout";
		cout<<"\nEnter your choice (0-2): ";
		int choice;
		cin>>choice;
		switch(choice)
		{
			case 0:	return;
			case 1:	clrscr();
				ifstream fin("Users.dat", ios::binary);
				PLAYER obj;
				while(!fin.eof())
				{
					fin.read((char*)&obj, sizeof(obj));
					if(fin.eof())
						break;
					obj.disp_User();
					cout<<"\nPassword: "<<obj.ret_password();
					cout<<"\n---------------------------";
				}
				fin.close();
				break;
			case 2:	clrscr();
				char line[80];	int counter = 0, choice;
				ifstream fi("movies.txt");
				ofstream fo("temp.txt");
				while(!fi.eof())
				{
					fi.getline(line, 80);
					if(fi.eof())
						break;
					cout<<counter + 1<<". "<<line<<endl;
					counter++;
				}
				cout<<"\nEnter which movie to edit: ";
				cin>>choice;
				counter = 0;
				fin.seekg(0);
				while(!fi.eof())
				{
					fi.getline(line, 80);
					if(counter+1 == choice)
					{
						cout<<"\nEnter new movie name: ";
						gets(line);
						fo<<line<<endl;
						cout<<"\nUpdated!";
						break;
					}
					else
						fo<<line<<endl;
					counter++;
				}
				fi.close();
				fo.close();
				remove("movies.txt");
				rename("temp.txt", "movies.txt");
				break;
			case 3:	char movie[20];
				cout<<"\nEnter movie name: ";
				gets(movie);
				ofstream f("movies.txt", ios::app);
				f<<endl<<movie;
				cout<<"\nMovie successfully added!";
				f.close();
				break;
			case 4: clrscr();
				char l[80];	int co = 0, ch;
				ifstream finn("movies.txt");
				ofstream foutt("temp.txt");
				while(!finn.eof())
				{
					finn.getline(l, 80);
					if(finn.eof())
						break;
					cout<<counter + 1<<". "<<l<<endl;
					counter++;
				}
				cout<<"\nEnter which movie to delete: ";
				cin>>ch;
				co = 0;
				finn.seekg(0);
				while(!finn.eof())
				{
					finn.getline(l, 80);
					if(co+1 != choice)
						foutt<<l<<endl;
					co++;
				}
				finn.close();
				foutt.close();
				remove("movies.txt");
				rename("temp.txt", "movies.txt");
				break;
			default:cout<<"\nError!";
		}
		cout<<"\nDo you want to logout? (Y/N): ";
		cin>>cont;
	}while(cont == 'y' || cont == 'Y');
}

void human_vs_comp(char id[20], char name[20], char password[20])
{
	clrscr();
	PLAYER user(id, name, password);
	randomize();
	char movie[20];	MOVIE obj;
	ifstream fin("movies.txt");
	int index, win = 0;
	index = random(50);
	for(int i = 0; i <= index; i++)
	{
		fin.getline(movie, 20);
		if(i == index)
		{
			obj.add_Movie(movie);
			break;
		}
	}
	fin.close();
	char letter;
	clrscr();
	while(win != 1 && obj.ret_count() < 6)
	{
		cout<<obj.ret_codename();
		cout<<name<<", enter the letter you want to guess: ";
		cin>>letter;
		obj.check_Letter(letter);
		win = obj.check_Win();
		obj.disp_Hangman();
	}
	if(win == 1)
	{
		cout<<endl<<name<<" wins!!!";
		user.winmore();
	}
	else
	{
		cout<<"\nComputer wins!!!";
		user.losemore();
	}
}

void main()
{
	clrscr();
	int choice;
	char id[20], name[20], password[20], cont, movie[20];
	cout<<"HANGMAN v1.0";
	cout<<"\nWelcome to Hangman, a movie name - guessing game in Turbo C++!";
	do{
		cout<<"\nSelect what you would like to do:";
		cout<<"\n1.Login to account\n2.Add a new user ID\n3.Play the game\n0.Exit";
		cout<<"\nEnter your choice: ";	cin>>choice;
		switch(choice)
		{
			case 0:	exit(0);
			case 1:	clrscr();
				cout<<"\nEnter user ID: ";
				gets(id);
				cout<<"\nEnter your name: ";
				gets(name);
				cout<<"\nEnter password: ";
				gets(password);
				if(strcmp(name, "administrator") == 0 &&
				   strcmp(id, "00000") == 0 && strcmp(password, "admin") == 0)
				{
					admin_mode();
					break;
				}
				int flag;
				flag = check_login(id, name, password);
				if(flag == 0)
				{
					cout<<"\nIncorrect credentials!";
					break;
				}
				else
				{
					clrscr();
					cout<<"\nWelcome "<<name<<"!";
					cout<<"\nSelect which action to perform: ";
					cout<<"\n1.View score record\n2.Play in Human v/s Computer mode\n3.Logout and return to main menu";
					cout<<"\nEnter your choice: ";
					int choice2;	char cont2;
					cin>>choice2;
					do{
						switch(choice2)
						{
							case 1: cout<<"\nID: "<<id;
								cout<<"\nName: "<<name;
								view_score(id);
								break;
							case 2: clrscr();
								human_vs_comp(id, name, password);
								break;
							case 3:	break;
							default:cout<<"\nError!";
						}
						cout<<"\nAre you sure you want to logout and exit to main menu? (Y/N) ";
						cin>>cont2;
					}while(cont2 == 'y' || cont2 == 'Y');
				}
				break;
			case 2:	clrscr();
				PLAYER new_Player;
				new_Player.add_User();
				new_user(new_Player);
				break;
			default:clrscr();
				cout<<"\nError!!!";
				break;
		}
		cout<<"\nDo you want to exit to main menu? (Y/N): ";
		cin>>cont;
	}while(cont == 'y' || cont == 'Y');
	getch();
}