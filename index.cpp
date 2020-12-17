#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<cctype>
#include<cstdio>
#include<cstdlib>

void clear()
{
	/*
		CUSTOM CLEARSCREEN FUNCTION TO DISPLAY TOP BANNER
	*/
	system("cls");
	for (int i = 0; i < 80; i++)
		std::cout << "=";
	std::cout << "\t\t\t\tHANGMAN v3.14\n";
	for (int j = 0; j < 80; j++)
		std::cout << "=";
}
class USER
{
	char* username, password;
	float win, loss;
	public:
	USER()
	{
		//constructor function to initialize class
		win = 0;	
		loss = 0; 
	}
	char* retname() 
	{ 
		return username; 
	}
	char* retpassword() { return password; }
	void copy(USER person)
	{
		strcpy(username, person.retname());
		strcpy(password, person.retpassword());
		win = person.retwin();
		loss = person.retloss();
	}
	float retwin() { return win; }
	float retloss() { return loss; }
	void winmore() { win++; }
	void lossmore() { loss++; }
	void take();
	void show()
	{
		std::cout << "\nUsername: " << username;
		std::cout << "\nWins: " << win;
		std::cout << "\nLosses: " << loss;
		if (loss != 0)
			std::cout << "\nW/L ratio: " << win / loss;
	}
};

void USER::take()
{
	std::cout << "\nEnter username: ";	
	getline(std::cin, username);
	std::cout << "Enter password: ";
	char ch;	int i = 0;
	while (1)
	{
		ch = std::cin.get();
		if (ch == '\r')
		{
			password[i] = '\0';
			break;
		}
		password[i++] = ch;
		std::cout << "*";
	}
}

void adduser();
int login(USER&);
void normie(USER&);
void singleplayer(USER&);
void admin_mode();
void multiplayer(USER&, USER&);
void update(USER&);
void update(USER&, USER&);

int main()
{
	char cont;	int choice; 	USER obj;
	do {
		clear();
		/*std::cout<<"\n\t\t\tWelcome to HANGMAN v1.0!\n";
		std::cout<<"------------------------------------------------------------------------------";*/
		std::cout << "\nMenu:\n1.Login\n2.Sign up\n3.Play game\n0.Exit";
		std::cout << "\nEnter your choice: ";
		std::cin >> choice;
		switch (choice)
		{
		case 0:
			exit(0);
			break;
		case 1:	clear();
			std::cout << "Enter your credentials";
			obj.take();
			if (strcmp(obj.retname(), "admin") == 0)
			{
				if (strcmp(obj.retpassword(), "00000") == 0)
				{
					admin_mode();
					break;
				}
			}
			else
				normie(obj);
			break;
		case 2:	clear();
			adduser();
			break;
		case 3:	clear();
			int choice2;
			std::cout << "\n1.Play as a user\n2.Play as guest\n0.Return to main menu";
			std::cout << "\nEnter your choice: ";
			std::cin >> choice2;
			switch (choice2)
			{
			case 0:	break;
			case 1: std::cout << "\nEnter your credentials";
				obj.take();
				if (strcmp(obj.retname(), "admin") == 0)
				{
					if (strcmp(obj.retpassword(), "00000") == 0)
					{
						admin_mode();
						break;
					}
				}
				else
					normie(obj);
				break;
			case 2:	std::cout << "\nEnter your username as 'guest', and password as 'nobody'";
				obj.take();
				if (strcmp(obj.retname(), "guest") == 0)
				{
					if (strcmp(obj.retpassword(), "nobody") == 0)
					{
						normie(obj);
						break;
					}
				}
				std::cout << "\nYou have entered the username or password incorrectly!";
				break;
			default:std::cout << "\nError!";
			}
			break;
		default:std::cout << "\nWrong input!";
		}
		std::cout << "\nDo you want to display the main menu again? (Y/N) ";
		std::cin >> cont;
	} while (cont == 'y' || cont == 'Y');
	return 0;
}

void adduser()
{
	USER player, obj;
	std::cout << "\nSign up";
	player.take();
	std::ifstream fin("USERS.DAT", ios::binary);
	while(!fin.eof())
	{
		fin.read((char*)&obj, sizeof(obj));
		if(strcmp(obj.retname(), player.retname()) == 0)
		{
			std::cout<<"\nUser already exists!";
			fin.close();
			return;
		}
	}
	fin.close();
	std::ofstream fout("USERS.DAT", ios::binary | ios::app);
	fout.write((char*)& player, sizeof(player));
	std::cout << "\nSign up successful!";
	fout.close();
}

int login(USER & attempt)
{
	USER obj;
	std::ifstream fin("USERS.DAT", ios::binary);
	while (!fin.eof())
	{
		fin.read((char*)& obj, sizeof(obj));
		if (strcmp(obj.retname(), attempt.retname()) == 0)
		{
			if (strcmp(obj.retpassword(), attempt.retpassword()) == 0)
			{
				attempt.copy(obj);
				fin.close();
				return 1;
			}
			else
			{
				std::cout << "\nIncorrect password!";
				return 0;
			}
		}
	}
	std::cout << "\nIncorrect username!";
	fin.close();
	return 0;
}

void normie(USER & player)
{
	int check;
	check = login(player);
	if (check == 1)
	{
		int choice;	char cont;
		do {
			clear();
			std::cout << "\nWelcome " << player.retname() << "!";
			std::cout << "\nSelect your action:";
			std::cout << "\n1.Play singleplayer\n2.Play multiplayer\n3.Add another user\n4.Display scoreboard\n0.Logout";
			std::cout << "\nEnter your choice: ";
			std::cin >> choice;
			if(choice == 1)
				singleplayer(player);
			else if(choice == 2)	{
				clear();
				USER player2;
				std::cout<<"\nAnother user is needed to play in multiplayer mode!";
				std::cout<<"\nPlayer 2, enter your credentials below: (if you want to log in as guest, enter username as 'guest' and password as 'nobody')";
				player2.take();
				int flag = login(player2);
				if(flag == 0)
				{
					std::cout<<"\nLogin failed!";
					break;
				}
				multiplayer(player, player2);
			}
			else if(choice == 3)
				adduser();
			else if(choice == 4)	{
				clear();
				player.show();
			}
			else if(choice == 0);
			else
				std::cout<<"\nError!"
			std::cout<<"\n" << player.retname()<<", logout? (Y/N) ";
			std::cin >> cont;
		  } while (cont == 'n' || cont == 'N');
	}
}

int vowel_check(char a)
{
	if (a == 'A' || a == 'a' ||
		a == 'E' || a == 'e' ||
		a == 'I' || a == 'i' ||
		a == 'O' || a == 'o' ||
		a == 'U' || a == 'u')
		return 1;
	else
		return 0;
}

void admin_mode()
{
	char cont;	int choice;
	do {
		clear();
		std::cout << "\nWelcome administrator!";
		std::cout << "\n1.Display movie list\n2.Add a movie\n3.Delete a movie\n0.Logout";
		std::cout << "\nEnter choice: ";
		std::cin >> choice;
		if(choice == 0);
		else if (choice == 1)	{
			clear();
			char* movie;
			std::ifstream fin("movies.txt");
			for (int i = 0; !fin.eof(); i++)
			{
				fin.getline(std::cin, movie);
				if (fin.eof())
					break;
				std::cout << i + 1 << ". " << movie << std::endl;
			}
		}
		else if(choice == 2)	{
			clear();
			char* line;
			std::ofstream fout("movies.txt", std::ios::app);
			std::cout << "\nEnter the name of the new movie: ";
			getline(std::cin, line);
			fout << line << std::endl;
			std::cout << "\nMovie added!";
		}
		else if(choice == 3)	{
			clear();
			char* del, name;
			std::ifstream f1("movies.txt");
			std::ofstream f2("temp.txt");
			std::cout << "\nEnter name of the movie to be deleted: ";
			getline(std::cin, del);
			while (!f1.eof())
			{
				f1.getline(name, 80);
				if (f1.eof())
					break;
				if (strcmp(name, del) != 0)
					f2 << name << std::endl;
			}
			f1.close();
			f2.close();
			remove("movies.txt");
			rename("temp.txt", "movies.txt");
		}
		else
			std::cout<<"\nError!";
		std::cout << "\nDo you want to logout? (Y/N) ";
		std::cin >> cont;
	} while (cont == 'n' || cont == 'N');
}

void singleplayer(USER & obj)
{
	clear();
	randomize();
	std::ifstream fin("movies.txt");
	int i = 0;	char movie[80], encoded_movie[80];
	while (!fin.eof())
	{
		fin.getline(movie, 80);
		if (fin.eof())
			break;
		i++;
	}
	fin.close();
	int temp = i;
	i = random(temp);
	std::ifstream fi("movies.txt");
	for (temp = 0; temp <= i; temp++)
		fi.getline(movie, 80);
	fi.close();
	int c = 0;
	for (int j = 0; j < strlen(movie); j++)
	{
		if (vowel_check(movie[j]) || !isalpha(movie[j]))
			encoded_movie[c++] = movie[j];
		else
			encoded_movie[c++] = '_';
	}
	encoded_movie[c] = '\0';
	int life_left = 7;
	int win = 0;
	int flag_win_check = 1;
	char user_guess;
	int flag_life = 0;
	do {
		flag_win_check = 1;
		flag_life = 0;
		std::cout << "\nLIVES LEFT = " << life_left;
		std::cout << "\n\nMovie: ";	puts(encoded_movie);
		std::cout << obj.retname() << ", guess a character: ";
		std::cin >> user_guess;
		for (int k = 0; movie[k] != '\0'; k++)
		{
			if (user_guess == tolower(movie[k]))
			{
				encoded_movie[k] = movie[k];
				flag_life = 1;
			}
		}
		if (flag_life == 0)
			life_left -= 1;
		clear();
		//win check from here
		for (int l = 0; encoded_movie[l] != '\0'; l++)
		{
			if (encoded_movie[l] == '_')
				flag_win_check = 0;
		}
		if (flag_win_check == 1)
			win = 1;
		if (win == 1)
		{
			std::cout << "You've won!!!";
			obj.winmore();
			break;
		}
	} while (life_left > 0);
	if (life_left == 0)
	{
		std::cout << "You've lost!!!";
		obj.lossmore();
	}
	update(obj);
}

void update(USER &obj)
{
	std::ifstream f1("USERS.DAT", ios::binary);
	std::ofstream f2("TEMP.DAT", ios::binary);
	USER dummy;
	while (!f1.eof())
	{
		f1.read((char*)& dummy, sizeof(dummy));
		if (strcmp(obj.retname(), dummy.retname()) == 0)
			f2.write((char*)& obj, sizeof(obj));
		else
			f2.write((char*)& dummy, sizeof(dummy));
	}
	f1.close();
	f2.close();
	remove("USERS.DAT");
	rename("TEMP.DAT", "USERS.DAT");
}

void update(USER &obj, USER &obj2)
{
	std::ifstream f1("USERS.DAT", ios::binary);
	std::ofstream f2("TEMP.DAT", ios::binary);
	USER dummy;
	while (!f1.eof())
	{
		f1.read((char*)& dummy, sizeof(dummy));
		if (strcmp(obj.retname(), dummy.retname()) == 0)
			f2.write((char*)& obj, sizeof(obj));
		else
			f2.write((char*)& dummy, sizeof(dummy));
	}
	f1.close();
	f2.close();
	remove("USERS.DAT");
	rename("TEMP.DAT", "USERS.DAT");
	std::ifstream f3("USERS.DAT", ios::binary);
	std::ofstream f4("TEMP.DAT", ios::binary);
	while (!f3.eof())
	{
		f3.read((char*)& dummy, sizeof(dummy));
		if (strcmp(obj2.retname(), dummy.retname()) == 0)
			f4.write((char*)& obj2, sizeof(obj2));
		else
			f4.write((char*)& dummy, sizeof(dummy));
	}
	f3.close();
	f4.close();
	remove("USERS.DAT");
	rename("TEMP.DAT", "USERS.DAT");
}

void multiplayer(USER &player1, USER &player2)
{
	int life_left = 7;
	int win = 0;
	int flag_win_check = 1;
	char user_guess;
	int flag_life = 0;
	char movie[80], encoded_movie[80];
	int c = 0;
	std::cout << player1.retname();
	std::cout << "\nEnter the movie: (Hide the screen from "<<player2.retname()<<"!) ";
	getline(std::cin, movie);
	for (int j = 0; j < strlen(movie); j++)
	{
		if (vowel_check(movie[j]) || !isalpha(movie[j]))
			encoded_movie[c++] = movie[j];
		else
			encoded_movie[c++] = '_';
	}
	encoded_movie[c] = '\0';
	do
	{
		clear();
		flag_win_check = 1;
		flag_life = 0;
		std::cout << "\nLIVES LEFT = " << life_left;
		std::cout << "\n\nMovie: ";
		puts(encoded_movie);
		std::cout << player2.retname()<<", guess a character: ";
		std::cin >> user_guess;
		for (int k = 0; movie[k] != '\0'; k++)
		{
			if (user_guess == tolower(movie[k]))
			{
				encoded_movie[k] = movie[k];
				flag_life = 1;
			}
		}
		if (flag_life == 0)
			life_left -= 1;
		clear();
		//win check from here
		for (int l = 0; encoded_movie[l] != '\0'; l++)
		{
			if (encoded_movie[l] == '_')
				flag_win_check = 0;
		}
		if (flag_win_check == 1)
			win = 1;
		if (win == 1)
		{
			std::cout << player2.retname()<<" wins round 1!!!";
			player2.winmore();	player1.lossmore();
			break;
		}
	} while (life_left > 0);
	if (life_left == 0)
	{
		std::cout << player1.retname()<<" wins round 1!!!";
		player2.lossmore();	player1.winmore();
	}
	std::cout<<"\nRound 2!";
	c = 0;
	std::cout << std::endl << player2.retname();
	std::cout << ", enter the movie: (Hide the screen from "<<player1.retname()<<"!) ";
	getline(std::cin, movie);
	for (int k = 0; k < strlen(movie); k++)
	{
		if (vowel_check(movie[k]) || !isalpha(movie[k]))
			encoded_movie[c++] = movie[k];
		else
			encoded_movie[c++] = '_';
	}
	encoded_movie[c] = '\0';
	do
	{
		clear();
		flag_win_check = 1;
		flag_life = 0;
		std::cout << "\nLIVES LEFT = " << life_left;
		std::cout << "\n\nMovie: ";
		puts(encoded_movie);
		std::cout << player1.retname()<<", guess a character: ";
		std::cin >> user_guess;
		for (int k = 0; movie[k] != '\0'; k++)
		{
			if (user_guess == tolower(movie[k]))
			{
				encoded_movie[k] = movie[k];
				flag_life = 1;
			}
		}
		if (flag_life == 0)
			life_left -= 1;
		clear();
		//win check from here
		for (int l = 0; encoded_movie[l] != '\0'; l++)
		{
			if (encoded_movie[l] == '_')
				flag_win_check = 0;
		}
		if (flag_win_check == 1)
			win = 1;
		if (win == 1)
		{
			std::cout << player1.retname()<<" wins round 2!!!";
			player1.winmore();	player2.lossmore();
			break;
		}
	} while (life_left > 0);
	if (life_left == 0)
	{
		std::cout << player2.retname()<<" wins round 2!!!";
		player1.lossmore();	player2.winmore();
	}
	update(player1, player2);
}