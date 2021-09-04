// game-snake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include <Windows.h>

#pragma region 	�nnouncement
using namespace std;
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitx, fruity, score;
int tailX[100], tailY[100];
int nTail;
enum eDirections { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirections dir;
#pragma endregion

void Setup() { // options
	gameOver = false;
	dir = STOP;
	x = width / 2 - 1;
	y = height / 2 - 1;
	fruitx = rand() % width;
	fruity = rand() % height;
	score = 0;
}

void Draw() { // map
	system("cls");

	for (int i = 0; i < width + 1; i++) {
		cout << "#";
	}

	cout << endl;

	for (int i = 0; i < height; i++) {

		for (int j = 0; j < width; j++) {

			if (j == 0 || j == width - 1)
				cout << "#";
			if (i == y && j == x)             // <- esli osibka est to tut - poslanie sebe na budusee)))  
				cout << "0";
			else
				if (i == fruity && j == fruitx)
					cout << "F";
				else {
					bool print = false;
					for (int k = 0; k < nTail; k++) {
						if (tailX[k] == j && tailY[k] == i) {
							print = true;
							cout << 'o';
						}
					}
					if (!print)
						cout << " ";
				}

		}
		cout << endl;
	}

	for (int i = 0; i < width + 1; i++)
		cout << "#";
	cout << endl;
	cout << "SCORE: " << score << endl;
}

void input() {
	if (_kbhit()) {

		switch (_getch()) {
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
	for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir) {

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
	}
	if (x > width || x < 0 || y> height || y < 0) {
		gameOver = true;
	}
	if (x == fruitx && y == fruity) {
		score += 10;
		fruitx = rand() % width;
		fruity = rand() % height;
		nTail++;
	}
}

int main()
{
	Setup();
	while (gameOver == false) {
		Draw();
		input();
		Logic();
		Sleep(200);
	}
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
