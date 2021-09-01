#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <dos.h>
#include <stdlib.h>

static int x = 1;			//used for x cursor co-ordinate
#define pos gotoxy(33, x++) /*for cursor movement*/
#define ln printf(".......................");
//.......................................................................................................................................................................
COORD coord = {0, 0};

void gotoxy(int x, int y);

void gotoxy(int x, int y) //function to set the cursor position
{
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//.......................................................................................................................................................................
void delay(unsigned int mseconds) //function for delay
{
	clock_t goal = mseconds + clock();
	while (goal > clock())
		;
}
//.............................................................................................................................................................................
void setcolor(int ForgC) //function to change setcolor
{
	WORD wColor;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	//We use csbi for the wAttributes word.
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		//Mask out all but the background attribute, and add in the forgournd color
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
	return;
}

//.................................................................................................................................................................................
void sett(); //sets time limit for playing game
int t = 30;
int c = 0;

char name[15];
void getscore(int score, int speed, int level);
void startgame(); //to start the game
void scorecard(); //to update high score
void About_me();
void help();
//...............................................................................................................................................................................
void rectangle(int x, int y, int l, int b) //to create a rectangle
{
	int i, m;
	gotoxy(x, y);
	printf("%c", 201);
	for (i = x + 1; i < l - 1; i++)
	{
		gotoxy(i, y);
		printf("%c", 205);
	}
	gotoxy(i, y);
	printf("%c", 187);

	for (m = y + 1; m < b; m++)
	{
		gotoxy(x, m);
		for (i = x; i < l; i++)
		{
			if (i == x || i == l - 1)
			{
				gotoxy(i, m);
				printf("%c", 186);
			}
		}
	}

	gotoxy(x, m);
	printf("%c", 200);
	for (i = x + 1; i < l - 1; i++)
	{
		gotoxy(i, m);
		printf("%c", 205);
	}
	gotoxy(i, m);
	printf("%c", 188);
}

//................................................................................................................................................................................
//			main function
int main()
{
	int ch;

	time_t t;
	time(&t);
	//	rectangle(0,0,70,15);
	x = 1;
	system("cls");
	pos;
	setcolor(12);
	printf(" WELCOME TO TYPING GAME\n");
	pos;
	ln pos;
	setcolor(10);
	pos;
	printf("%s", ctime(&t));
	pos;
	ln pos;
	setcolor(14);
	if (c == 0)
	{
		printf("\nEnter Player's Name : ");
		gets(name);
	}
	c++;
	pos;
	ln pos;
	setcolor(10);
	printf("   #...MAIN MENU...#");
	pos;
	ln pos;
	printf("1. Startgame");
	pos;
	printf("2. Scorecard");
	pos;
	printf("3. Set the Time Limit");
	pos;
	printf("4. Help");
	pos;
	printf("5. About me");
	pos;
	printf("0. Exit");
	pos;
	setcolor(14);
	printf("\nEnter your Choice : ");
	scanf("%d", &ch);
	pos;
	switch (ch)
	{
	case 1:
		startgame();
		break;
	case 2:
		scorecard();
		break;
	case 3:
		sett();
		main();
	case 4:
		help();
		break;
	case 5:
		About_me();
		break;
	case 0:
		system("cls");
		gotoxy(17, 10);
		printf("Thanks for Playing!\n\n");
		delay(1000);
		exit(1);
	default:
		main();
	}

	getch();
}
//.....................end of main function.................................

//startgame
//..........................................................................
void startgame()
{
	int score = 0, level = 1, mode = 100, count = 0;
	clock_t begin;
	int time_spent, speed;

	int r, letter, ch;
	rectangle(0, 0, 90, 15);
	delay(500);

	system("cls");
	srand(time(NULL)); //initilizes random function and seed with time
	x = 2;
	pos;
	setcolor(12);
	printf("#...SELECT THE MODE...#");
	pos;
	ln
		pos;
	printf("1. Easy Mode");
	pos;
	printf("2. Normal Mode");
	pos;
	printf("3. Hard Mode");
	pos;
	printf("4. Back to Main Menu\n");
	pos;
	scanf("%d", &level);
	if (level == 4)
		main();

	else

	{
		if (level == 1) //boundary addition for lowercase alphabet
			mode = 65;
		if (level == 2) //boundary addition for uppercase
			mode = 97;
		if (level == 3) //condition for mixed case
			mode = 120;
		begin = clock();
		while (1)
		{
			system("cls");
			time_spent = (int)(clock() - begin) / CLOCKS_PER_SEC;

			if (time_spent >= t)
				break;
			r = rand() % 1000;
			r = r % 26 + mode;
			gotoxy(20, 8);
			printf(".....Type the Following Character.....");
			gotoxy(36, 11);
			printf(" %c  ", r); //prints random character

			letter = getch();

			if (letter != r)
				break;
			else
			{
				count++;
				score = score + 10;
				gotoxy(28, 9);
				printf("score=%d", score); //prints score
				gotoxy(37, 9);
				printf("time_spent=%d sec", time_spent); //prints time spent during game

				if (level == 1)
					delay(400);
				if (level == 2)
					delay(200);
				if (level == 3)
					delay(100);

			} //end of else
		}	  //end of while
		gotoxy(26, x);

		delay(400);

		setcolor(5); //blue text color
		++x;
		pos;
		speed = (count * 60) / time_spent;
		//	symbol=2;
		if (time_spent < t - 1)
			printf("Game Over!\n");
		else
		{
			setcolor(11);
			printf("Times up! Game over!");
			pos;
			setcolor(5);
			if ((speed >= 40) && (speed <= 50))
			{
				printf("Good Work! Keep it up!");
				pos;

				printf("You got Silver Medal");
			}
			else if (speed > 50)
			{
				printf("Congrats! You got Gold medal");
			}
			else
				printf("Sorry no medal... Practise more!");
		}
		pos;
		printf("Total score is : %d", score);
		pos;

		printf("Your net speed : %d letters per minute", speed);

		getscore(score, speed, level); //saves data to file
		++x;
		pos;
		printf("\n1. Play Again");
		pos;

		printf("2. Main Menu");
		pos;
		printf("3. Exit");
		pos;
		printf("\nEnter your Choice : ");
		scanf("%d", &ch);
		switch (ch)
		{
		case 1:
			startgame();
			break; //recursive call
		case 2:
			main();
			break;
		case 3:
			system("cls");
			gotoxy(17, 10);
			printf("Thanks for Playing!\n\n");
			delay(1000);
			exit(1);
		default:
			pos;
			printf("\nINVALID CHOICE!");
			pos;
			main();
		}
	}
}
//......................end of start game function..........................

//...........................sett function starts..........................
void sett() //set time limit
{
	int ch;
	system("cls");
	//rectangle(0,0,70,15);
	setcolor(11);
	x = 5;
	pos;
	printf("Set the time limit for game in minutes :");
	pos;
	ln
		pos;
	printf("Press 0 for half minute");
	pos;
	printf("Press 1 for 1 minute");
	pos;
	printf("Press 2 for 2 minute");
	pos;
	scanf("%d", &ch);
	switch (ch)
	{
	case 0:
		t = 30;
		break;
	case 1:
		t = 60;
		break;
	case 2:
		t = 120;
		break;
	default:
		main();
	}
}
//....................sett function ends....................................

//........................................................................
void help()
{
	system("cls");
	//rectangle(0,0,70,15);
	gotoxy(7, 5);
	setcolor(6);

	printf("#...RULES OF THE GAME...#");
	gotoxy(7, 6);
	printf("=>Enter your name as player name");
	gotoxy(7, 7);
	printf("=>Set the time limit under option 3 in main menu (default limit is 30 sec)");
	gotoxy(7, 8);
	printf("=>Select the level and get started :");
	gotoxy(7, 9);
	printf("=>Characters are displayed and you have to type them as fast as you can");
	gotoxy(7, 10);
	printf("=>Avoid incorrect typing otherwise game will be over...");
	getch();
	main();
}
void About_me()
{
	system("cls");
	gotoxy(7, 7);
	printf("We are a bunch of lazy bastards :) Hv fun Playing!");
	getch();
	main();
}
//.........................................................................
void getscore(int score, int speed, int level)
{
	FILE *fp;
	fp = fopen("file.txt", "a");
	pos;
	if (fp == NULL)
		printf("error in opening file");
	fprintf(fp, "\nNAME : %s   SCORE : %d    LEVEL : %d    SPEED : %d", name, score, level, speed);
	fclose(fp);
	pos;
	printf("\nSCORECARD UPDATED\n");
}
void scorecard()
{
	int ch;
	FILE *fp;
	system("cls");
	//rectangle(0,0,70,15);
	x = 3;

	printf("\t\t\t#...SCOREBOARD...#\n");

	fp = fopen("file.txt", "r");
	while ((ch = fgetc(fp)) != EOF)
	{
		printf("%c", ch);
	}
	getch();
	main();
}
