#pragma once

#define UP_KEY 72
#define DOWN_KEY 80
#define LEFT_KEY 75
#define RIGHT_KEY 77

typedef enum Direction {
	STOP = 0,
	LEFT,
	RIGHT,
	UP,
	DOWN
} Direction;

typedef enum DOS_COLORS {
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	LIGHT_GRAY,
	DARK_GRAY,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_CYAN,
	LIGHT_RED,
	LIGHT_MAGENTA,
	YELLOW,
	WHITE
} DOS_COLORS;

void gotoXY(const int x, const int y);
void gameSetup(const int width, const int height, bool* gameOver);
void drawGame(const int width, const int height);
void getUserInput(bool* gameOver);
void gameLogic(const int width, const int height, bool* gameOver);
void textBackground(DOS_COLORS color);
void textColor(DOS_COLORS color);