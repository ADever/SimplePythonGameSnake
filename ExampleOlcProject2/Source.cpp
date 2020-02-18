//First attempt at a snake game, nothing special but gets the job done

#include <iostream>
#include <conio.h>
#include <windows.h>

bool gameOver;
bool immediateStop;

const int width = 20;
const int height = 20;

int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;

enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void Setup()
{
	std::cout << "Press 'i' for instructions, press any other button to continue" << std::endl;

	char ch;
	ch = _getch();

	if (ch == 'i') {
		system("cls");
		std::cout << "Welcome to Snake" << std::endl;
		std::cout << "Use 'wasd' as your directional keys and 'x' to exit" << std::endl;
		std::cout << "Feed upon the 'f's to grow larger and avoid the # signs" << std::endl;
		std::cout << "Press 'x' to close the game at any time" << std::endl;
		Sleep(3000);
		std::cout << std::endl;
		std::cout << "Good luck..." << std::endl;
		Sleep(2000);
		system("cls");
	}

	gameOver = false;
	immediateStop = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void Draw()
{
	
	system("cls");
	
	for (int i = 0; i < width + 2; i++)
		std::cout << "#";
	std::cout << std::endl;

	for (int i = 0; i < height; i++) {

		for (int j = 0; j < width; j++) {
			if (j == 0)
				std::cout << "#";
			if (i == y && j == x)
				std::cout << "0";
			else if (i == fruitY && j == fruitX)
				std::cout << "F";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						std::cout << "o";
						print = true;
					}
				}
				if (!print)
					std::cout << " ";
			}
			
			if (j == width - 1)
				std::cout << "#";
		}
		std::cout << std::endl;
	}

	for (int i = 0; i < width + 2; i++)
		std::cout << "#";
	std::cout << std::endl;
	std::cout << "Score: " << score << std::endl;
}

void Input()
{
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
			immediateStop = true;
				break;
		}
	}
}

void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;

	}
	switch (dir)
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
	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	
	//if (x >= width) x = 0; else if (x < -3) x = width - 1;
	//if (y >= height) y = 0; else if (y < 0) y = height - 1;
	
	//above code makes it so the walls don't kill you

	if (x == fruitX && y == fruitY)
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % width;
		nTail++;
	}

	if (dir == UP || dir == DOWN)
	{
		Sleep(40);
	}
}

int main()
{
	Setup();
	while (!gameOver && !immediateStop)

	{
		Draw();
		Input();
		Logic();
	}
	if (gameOver && !immediateStop)
	{
		std::cout << "You lost" << std::endl;
		if (score < 100) {
			std::cout << "You can do better than that" << std::endl;
		}
		else if (score > 100) {
			std::cout << "Decent score, good job!" << std::endl;
		}
		else {
			std::cout << "Good job! That was a high score!" << std::endl;
		}
		Sleep(3000);
	}
	
	return 0;
}