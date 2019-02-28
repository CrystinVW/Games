#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;


bool gameOver;
const int width = 40;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int ntail;
int sleepTime = 70;
int level;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;


void Setup() {
	cout << "Difficulty Levels: " << endl;
	cout << "Easy = 1" << endl;
	cout << "Medium = 2" << endl;
	cout << "Hard = 3" << endl;
	cout << "Enter a difficulty level: ";
	cin >> level;
	system("cls");
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % (width -1);
	fruitY = rand() % (height -1);
	score = 0;
}


void ClearScreen()
{
	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}


void Draw() 
{
	ClearScreen();
	//system("cls"); // Clears the screen
	for (int i = 0; i < width+2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "O";
			else if (i == fruitY && j == fruitX)
				cout << "F";
			else
			{
				bool print = false;
				for (int k = 0; k < ntail; k++)
				{
					
					if (tailX[k] == j && tailY[k] == i)
					{
						// print tail
						cout << "o";
						print = true;
					}
					
				}
				if (!print)
					cout << " ";
				
			}
			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < width+2; i++)
		cout << "#";

	cout << endl;
	cout << "Score: " << score << endl;

}


void Input() {
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;

		}
	}

}


void Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < ntail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch(dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	if (x > width || x < 0 || y > height || y < 0)
		gameOver = true;
	for (int i = 0; i < ntail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;

	if (x == fruitX && y == fruitY)
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		ntail++;
	}
}


int main() {
	Setup();
	while (!gameOver) {
		
		Draw();
		Input();
		Logic();
		if (level == 1)
		{
			sleepTime = 80;
		}
		else if (level == 2)
		{
			sleepTime = 50;
		}
		else if (level == 3)
		{
			sleepTime = 20;
		}
		Sleep(sleepTime);
	}
	system("cls"); // Clears the screen
	cout << "Final Score: " << score << endl;
	Sleep(2000);
	return 0;

}
