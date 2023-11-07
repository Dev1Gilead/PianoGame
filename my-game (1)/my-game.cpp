// Game Name: Piano Code
// Written by: Gabriel Anderson
// Date: 12/6/2022
//
// Instructions: 
// 1) Click tiles before they hit the bottom of the screen.
// 2) Try to get the highest  score you can.
// 3) Have fun!
//

#include "graphics.h"
#include <string>
#include <random>
#include <iostream>
#include <cmath>
using namespace std;

const int BACKGROUND_COLOR = BLUE;
const int TEXT_COLOR = WHITE;
const int BAR_COLOR = WHITE;
const int PIANO_COLOR = BLACK;
const int windowH = 1000;
const int windowW = 1000;
const int MAX_SIZE = 1000;
//random num
default_random_engine generator;
random_device myEngine;
uniform_int_distribution<int> randomInt(1, 3);

// prototyps
void welcomeScreen();
void showScore(int score);
// Structur
struct leftBarStruct {
	double x1, x2, y1, y2, prevX1, prevX2, prevY1, prevY2, xVel, xMid, prevXMid;
	int color;
	bool alive;
};


// main
int main()
{

	//declorations
	char keyPressed;

	bool keepGoing = true;
	bool playAgain = true;
	bool newBar = false;
	bool whiteClicked = false;

	double topDistaince = 0;

	int randomNum2;
	int randomNum;
	int mouseClickX, mouseClickY;
	int lowestBar = 0;
	int barVelocity = 25;
	int score = 1;
	//declaring variable for Structure
	leftBarStruct leftBar[MAX_SIZE];




	//Modes
	enum mode { BEFOREPLAYING, PLAYING, NOTHING };
	mode gameMode = BEFOREPLAYING;



	initwindow(windowW, windowH, (char*)"Piano Code", 10, 10);

	welcomeScreen();


	// -------- Main "Play Again" loop
	//

	double delaySpeed = 50;
	do {

		// 
		// -------- Main "Keep Going" loop
		//

		// Black backround
		setfillstyle(SOLID_FILL, PIANO_COLOR);
		bar(windowW * .75, 0, windowW * .25, windowH);


		keepGoing = true;
		while (keepGoing) {
			delay(delaySpeed);

			// declorations
			topDistaince = (leftBar[lowestBar].y2 - 1.25 * windowH);

			if (lowestBar == 5) {
				lowestBar = 0;
			}
			// end declorations
			if (score % 10 == 0 && score != 0) {
				barVelocity = barVelocity + 1;
			}

			// check if left click on white bar
			if (ismouseclick(WM_LBUTTONUP)) {
				getmouseclick(WM_LBUTTONUP, mouseClickX, mouseClickY);
				if (getpixel(mouseClickX, mouseClickY) == WHITE) {
					whiteClicked = true;
				}
				else whiteClicked = false;

				false;
			}
			// declaring previouse x and y
			if (NOTHING) {
				for (int i = 0; i < 5; i++) {
					leftBar[i].prevX1 = leftBar[i].x1;
					leftBar[i].prevX2 = leftBar[i].x2;
					leftBar[i].prevY1 = leftBar[i].y1;
					leftBar[i].prevY2 = leftBar[i].y2;
				}
			}

			// setting up bars before game starts
			if (gameMode == BEFOREPLAYING) {

				for (int i = 0; i < 5; i++) {
					leftBar[i].x1 = 0;
					leftBar[i].x2 = 0;
					leftBar[i].y1 = windowH * .75;
					leftBar[i].y2 = windowH;

				}


				for (int i = 0; i < 5; i++) {

					int k = 0;
					randomInt(myEngine);
					randomNum = randomInt(myEngine);

					if (randomNum == 1) {
						leftBar[i].x1 = windowW * .25;
						leftBar[i].x2 = windowW * .25 + windowW / 6;
						setfillstyle(SOLID_FILL, WHITE);
						bar(leftBar[i].x1, leftBar[i].y1, leftBar[i].x2, leftBar[i].y2);

					}
					else if (randomNum == 2) {
						leftBar[i].x1 = windowW * .25 + windowW / 6;
						leftBar[i].x2 = windowW * .25 + 2 * (windowW / 6);
						setfillstyle(SOLID_FILL, WHITE);
						bar(leftBar[i].x1, leftBar[i].y1, leftBar[i].x2, leftBar[i].y2);
					}
					else if (randomNum == 3) {
						leftBar[i].x1 = windowW * .25 + 2 * (windowW / 6);
						leftBar[i].x2 = windowW * .25 + 3 * (windowW / 6);
						setfillstyle(SOLID_FILL, WHITE);
						bar(leftBar[i].x1, leftBar[i].y1, leftBar[i].x2, leftBar[i].y2);
					}
					k = i + 1;
					leftBar[k].y1 = leftBar[i].y1 - windowH * .25;
					leftBar[k].y2 = leftBar[i].y2 - windowH * .25;
				}
				gameMode = NOTHING;
			}

			// if tile is clicked
			if (whiteClicked && gameMode == PLAYING) {



				// score
				score++;
				showScore(score);
				//volocity
				barVelocity = barVelocity + .1;

				// random num
				randomInt(myEngine);
				randomNum2 = randomInt(myEngine);

				//new bar x cords
				if (randomNum2 == 1) {
					// left
					leftBar[lowestBar].x1 = windowW * .25;
					leftBar[lowestBar].x2 = windowW * .25 + windowW / 6;
				}
				else if (randomNum2 == 2) {
					//mid
					leftBar[lowestBar].x1 = windowW * .25 + windowW / 6;
					leftBar[lowestBar].x2 = windowW * .25 + 2 * (windowW / 6);
				}
				else if (randomNum2 == 3) {
					//right
					leftBar[lowestBar].x1 = windowW * .25 + 2 * (windowW / 6);
					leftBar[lowestBar].x2 = windowW * .25 + 3 * (windowW / 6);
				}
				// new bar y cords
				leftBar[lowestBar].y1 = (topDistaince - windowH * .25);
				leftBar[lowestBar].y2 = topDistaince;

				setfillstyle(SOLID_FILL, WHITE);
				bar(leftBar[lowestBar].x1, leftBar[lowestBar].y1, leftBar[lowestBar].x2, leftBar[lowestBar].y2);
				lowestBar++;
				// end drawing
				whiteClicked = false;
			}
			else if (whiteClicked && gameMode == NOTHING) {

				// covering old bar
				setfillstyle(SOLID_FILL, BLACK);
				bar(leftBar[lowestBar].x1, leftBar[lowestBar].y1, leftBar[lowestBar].x2, leftBar[lowestBar].y2);

				leftBar[lowestBar].y1 = (topDistaince - windowH * .25);
				leftBar[lowestBar].y2 = topDistaince;

				setfillstyle(SOLID_FILL, WHITE);
				bar(leftBar[lowestBar].x1, leftBar[lowestBar].y1, leftBar[lowestBar].x2, leftBar[lowestBar].y2);
				lowestBar++;
				whiteClicked = false;
				//score
				showScore(score);
				gameMode = PLAYING;
			}

			// moving left bar
		// covering up left bar
			if (gameMode == PLAYING) {
				for (int i = 0; i < 5; i++) {
					setfillstyle(SOLID_FILL, BLACK);
					bar(leftBar[i].prevX1, leftBar[i].prevY1, leftBar[i].prevX2, leftBar[i].prevY2);
					leftBar[i].prevY1 = leftBar[i].prevY1 + barVelocity;
					leftBar[i].prevY2 = leftBar[i].prevY2 + barVelocity;
				}
			}

			// drawing left bar
			if (gameMode == PLAYING) {
				for (int i = 0; i < 5; i++) {
					leftBar[i].y1 = leftBar[i].y1 + barVelocity;
					leftBar[i].y2 = leftBar[i].y2 + barVelocity;
					setfillstyle(SOLID_FILL, WHITE);
					bar(leftBar[i].x1, leftBar[i].y1, leftBar[i].x2, leftBar[i].y2);
				}
			}

			leftBar[lowestBar].xMid = (leftBar[lowestBar].y1 + (leftBar[lowestBar].y2 - leftBar[lowestBar].y1) / 2);
			if (leftBar[lowestBar].xMid > windowH && gameMode == PLAYING) {
				keepGoing = false;
			}


			// -------- Check to see if a key has been pressed
			if (kbhit()) {
				keyPressed = getch();

				// KEY: Q or ESC pressed
				if (keyPressed == 'q' || keyPressed == 'Q' || keyPressed == 0x1b) {
					keepGoing = false;
				}

			}


		} // end while(keepGoing)

			// Game has ended

		outtextxy(windowW * .25, windowH * .5, (char*)"GAME OVER, Play Again (Y/N)");
		keyPressed = getch();
		if (keyPressed == 'y' || keyPressed == 'Y') {
			score = 1;
			gameMode = BEFOREPLAYING;
			barVelocity = 20;
			lowestBar = 0;

			cleardevice();
			welcomeScreen();
		}
		else {
			playAgain = false;
		}

	} while (playAgain == true);  // Main "Play Again" loop

	return 0;
} // end main()


void welcomeScreen() {
	setbkcolor(BACKGROUND_COLOR);
	cleardevice();

	setcolor(TEXT_COLOR);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, windowW * .003);
	outtextxy(10, 10, (char*)"Press any key to begin Piano Code!");
	outtextxy(windowW * .25, windowH * .5, (char*)"LET THE MADNESS BEGIN");
	getch();
	cleardevice();
}



void showScore(int score) {
	// Draw score on the screen
	char s[20];
	sprintf_s(s, "Score: %d", score);
	setcolor(BLACK);
	outtextxy(20, 20, &s[0]);
}
