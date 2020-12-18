#include <iostream>
#include "utility_functions.h"

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

// void adduser();
// int login(USER&);
// void normie(USER&);
// void singleplayer(USER&);
// void admin_mode();
// void multiplayer(USER&, USER&);
// void update(USER&);
// void update(USER&, USER&);

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
