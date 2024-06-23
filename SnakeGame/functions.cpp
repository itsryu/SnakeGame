#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>

using namespace std;

#include "functions.h"

Direction dir;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;

void gotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void textBackground(DOS_COLORS color) {
	HANDLE hl = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	GetConsoleScreenBufferInfo(hl, &bufferInfo);
	bufferInfo.wAttributes &= 0x000F;
	SetConsoleTextAttribute(hl, bufferInfo.wAttributes |= (color << 4));
}

void textColor(DOS_COLORS color) {
	HANDLE hl = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	GetConsoleScreenBufferInfo(hl, &bufferInfo);
	bufferInfo.wAttributes &= 0x00F0;
	SetConsoleTextAttribute(hl, bufferInfo.wAttributes |= color);
}

void gameSetup(const int width, const int height, bool* gameOver) {
	system("color 17");
	system("title Snake Game");

	*gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;

	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
}

void drawGame(const int width, const int height) {
	gotoXY(0, 0);

	for(int i = 0; i < width + 2; i++)
		cout << "#"; cout << endl;

	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			if(j == 0) cout << "#";

			if(i == y && j == x) cout << "O";
			else if(i == fruitY && j == fruitX) cout << "$";
			else {
				bool print = false;

				for(int k = 0; k < nTail; k++) {
					if(tailX[k] == j && tailY[k] == i) {
						cout << "o";
						print = true;
					}
				}

				if(!print) cout << " ";
			}

			if(j == width - 1) cout << "#";
		}
		cout << endl;
	}

	for(int i = 0; i < width + 2; i++)
		cout << "#"; cout << endl;

	textBackground(BLUE);
	cout << "\nScore: " << score << endl;
}

void getUserInput(bool* gameOver) {
	if(_kbhit()) {
		switch(_getch()) {
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
			case UP_KEY:
				dir = UP;
				break;
			case DOWN_KEY:
				dir = DOWN;
				break;
			case LEFT_KEY:
				dir = LEFT;
				break;
			case RIGHT_KEY:
				dir = RIGHT;
				break;
			case 'x':
				*gameOver = true;
				break;
		}
	}
}

void gameLogic(const int width, const int height, bool* gameOver) {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;

	for(int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch(dir) {
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

	if(x >= width) x = 0; else if(x < 0) x = width - 1;
	if(y >= height) y = 0; else if(y < 0) y = height - 1;

	for(int i = 0; i < nTail; i++) {
		if(tailX[i] == x && tailY[i] == y) *gameOver = true;
	}

	if(x == fruitX && y == fruitY) {
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
		Beep(100, 100);
	}
}