#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <thread>

using namespace std;

#include "functions.h"

const int width = 100;
const int height = 20;
bool gameOver;

int main(void) {
	#ifdef _WIN32
		gameSetup(width, height, &gameOver);

		while(!gameOver) {
			textBackground(GREEN);
			textColor(WHITE);
			drawGame(width, height);
			getUserInput(&gameOver);
			gameLogic(width, height, &gameOver);
			this_thread::sleep_for(chrono::milliseconds(16));
		}

		system("pause");
	#else
		cout << "This game is only available on Windows." << endl;
	#endif

	return 0;
}