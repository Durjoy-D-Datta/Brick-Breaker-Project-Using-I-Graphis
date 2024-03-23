#include<iostream>
using namespace std;
#include "iGraphics.h"
#define totalBricks 5*10
#define screenWidth 1200
#define screenHight 650
#define yAxisMargin 50
int mposx, mposy;
int line = 0;
int t, t2;
int life = 3;
char lifes[] = "Life = 3";
char scores[20] = " 0";
char Level[20] = "1";
int score = 0, l = 1;

struct buttonCordinate
{
	int x;
	int y;
}
bCordinate[3];
bool musicOn = true;
char hm[15] = "ga\\hm2.bmp";
char button[10][15] = { "ga\\s.bmp", "ga\\a.bmp", "ga\\e.bmp", "ga\\play.bmp", "ga\\quit.bmp" };

char gameover[15] = { "ga\\go.bmp" };
char homemenu[15] = "ga\\2.bmp";
char about[15] = "ga\\durjoy.bmp";
char backGroundImage[15] = "ga\\bg.bmp";
struct brickStructure
{
	int p;
	int q;
	int dp = 100;
	int dq = 20;
	bool show = true;
	int red;
	int green;
	int blue;

};
brickStructure bricks[totalBricks];
int red = 0;
int green = 0;
int blue = 255;


int pBall = (int)screenWidth / 2;
int qBall = yAxisMargin;
int radiusBall = 10;
int initialSpeed = 7;

int acceleration = 5;
int dp = initialSpeed;
int dq = acceleration;


int pBoard = pBall - 50;
int qBoard = qBall - 20;
int dpBoard = 100;
int dqBoard = 10;

bool isStarted = false;




void ballChange();
void restartBall();
void defineBricks();
int gamestate = -2;
void scor()
{
	score = 0;
	for (int p = 0; p < 50; p++)
	{
		if (bricks[p].show == false)score++;
	}
	if (score < 10){
		scores[0] = ' ';
		scores[1] = score + 48;

	}
	else{
		scores[0] = (score / 10) + 48;
		scores[1] = (score % 10) + 48;
	}
	scores[2] = '\0';
}

void iDraw()
{
	//place your drawing codes here
	iClear();
	if (gamestate == -2)
	{
		iShowBMP(0, 0, "ga\\hm2.bmp");
		iText(50, 50, "Loading...", GLUT_BITMAP_TIMES_ROMAN_24);
		iFilledRectangle(50, 20, 70 + line, 20);
	}
	//


	if (gamestate == -1)
	{
		//Homemenu
		iShowBMP(0, 0, homemenu);
		for (int i = 0; i < 3; i++)
		{
			iShowBMP2(bCordinate[i].x, bCordinate[i].y, button[i], 255);
		}
	}
	else if (gamestate == 0)
	{
		//int bg
		//bg= iLoadImage("Theme\\bg3.png");
		iShowBMP(0, 0, backGroundImage);
		iSetColor(0, 255, 0);
		iText(60, 590, lifes, GLUT_BITMAP_TIMES_ROMAN_24);
		if (score == 15){
			l = 2;

			_itoa_s(l, Level, 20);
		}
		else if (score == 30){
			l = 3;

			_itoa_s(l, Level, 20);
		}

		iText(170, 590, "Level=", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(240, 590, Level, GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(0, 255, 0);
		iText(1000, 590, "Score = ", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(1090, 590, scores, GLUT_BITMAP_TIMES_ROMAN_24);

		iSetColor(255, 255, 0);
		iFilledCircle(pBall, qBall, radiusBall, 1000);
		iFilledRectangle(pBoard, qBoard, dpBoard, dqBoard);
		for (int i = 0; i < totalBricks; i++)
		{
			if (bricks[i].show)
			{
				iSetColor(bricks[i].red, bricks[i].green, bricks[i].blue);
				iFilledRectangle(bricks[i].p, bricks[i].q, bricks[i].dp, bricks[i].dq);

			}

		}

	}
	else if (gamestate == 1)
	{
		iShowBMP(0, 0, "ga\\durjoy.bmp");

	}
	else if (gamestate == 2)
	{
		iShowBMP(0, 0, "ga\\e.bmp");
	}
	else if (gamestate == 3){
		iShowBMP(0, 0, "ga\\go.bmp");
		for (int i = 3; i < 5; i++)
		{
			iShowBMP2(bCordinate[i].x, bCordinate[i].y, button[i], 255);
		}
		iText(500, 250, "SCORES : ", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(610, 250, scores, GLUT_BITMAP_TIMES_ROMAN_24);

	}
	else if (gamestate == 4)
	{

		iShowBMP(0, 0, "ga\\play.bmp");

	}
	else if (gamestate == 5)
	{

		iShowBMP(0, 0, "ga\\quit.bmp");

	}
}

void iMouseMove(int mx, int my)

{

}

void iMouse(int button, int state, int mx, int my)
{


	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		if (!isStarted)
		{
			isStarted = true;
			iResumeTimer(t);
		}
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

		for (int i = 0; i < 3; i++)
		{
			if (mx >= bCordinate[i].x&&mx <= bCordinate[i].x + 166 && my >= bCordinate[i].y &&my <= bCordinate[i].y + 70)
			{
				gamestate = i;
			}
		}
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{

			for (int i = 3; i < 5; i++)
			{
				if (mx >= bCordinate[i].x&&mx <= bCordinate[i].x + 166 && my >= bCordinate[i].y &&my <= bCordinate[i].y + 70)
				{
					gamestate = i;
				}
			}
		}
		if (gamestate == 2)
			exit(1);
	}
}


/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
	if (key == 's')
	{
		if (musicOn)
		{
			musicOn = false;
			PlaySound(0, 0, 0);
		}
		else
		{
			musicOn = true;
			PlaySound("music\\mu.wav", NULL, SND_LOOP | SND_ASYNC);
		}
	}
	else if (key == 'p')
	{
		if (gamestate == 0)
		{
			iPauseTimer(t);
		}

	}
	else if (key == 'c')
	{
		if (gamestate == 0)
		{
			iResumeTimer(t);
		}
	}
	else if (key == 'd')
	{

	}
	else if (key == ' ')
	{

	}
	//place your codes for other keys here
}

/*
function iSpecialKeyboard() is called whenver user hits special keys like-
function keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

	if (key == GLUT_KEY_UP)
	{
		if (!isStarted)
		{
			isStarted = true;
			iResumeTimer(t);
		}
	}
	else if (key == GLUT_KEY_DOWN)
	{

	}
	else if (key == GLUT_KEY_LEFT)
	{
		if (pBoard >38)
		{
			pBoard -= 10;
			if (!isStarted)
			{
				pBall -= 10;
			}
		}
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		if (pBoard < screenWidth - dpBoard - 38)
		{
			pBoard += 10;
			if (!isStarted)
			{
				pBall += 10;
			}
		}
	}

	if (key == GLUT_KEY_END)
	{
		if (gamestate == 1)
		{
			gamestate = -1;
		}
	}
	if (key == GLUT_KEY_END)
	{
		if (gamestate == 3)
		{
			gamestate = -1;
			scores[0] = ' ';
			scores[1] = '0';
			for (int i = 0; i < 50; i++)bricks[i].show = true;
		}
	}
	//place your codes for other keys here
}
//
void ballChange()
{

	if (isStarted)
	{	if (score == 15) {
		
		dp = 7;
			dq = 7;
	}
	else if (score == 30) {
		
		dp = 8;
		dq = 8;
	}
		pBall += dp;
		qBall += dq;
		if (pBall >= screenWidth - 33 || pBall <= 33)
			dp *= (-1);
		if (qBall >= screenHight - 25 || qBall <= 0)
			dq *= (-1);
	
		for (int i = 0; i < totalBricks; i++)
		{
			if (bricks[i].show)
			{
				if (pBall >= bricks[i].p && pBall <= bricks[i].p + bricks[i].dp)
				{

					if (qBall >= bricks[i].q && qBall <= bricks[i].q + bricks[i].dq)
					{
						dq *= (-1);
						bricks[i].show = false;
					}
				}
				else if (qBall >= bricks[i].q && qBall <= bricks[i].q + bricks[i].dq)
				{

					if (pBall >= bricks[i].p && pBall <= bricks[i].p + bricks[i].dp)
					{
						dp *= (-1);
						bricks[i].show = false;
					}
				}
			}
		}
		if (pBall >= pBoard && pBall <= pBoard + dpBoard && qBall >= qBoard && qBall <= qBoard + dqBoard)
		{
			dq *= (-1);
		}
		else
		{
			if (qBall < qBoard)
			{
				life--;
				if (life == 2)lifes[7] = '2';
				if (life == 1)lifes[7] = '1';
				if (life <= 0)
				{
					gamestate = 3;
					line = 0;
					life = 3;
					lifes[7] = '3';
					score = 0;
					red = 0;
					green = 0;
					blue = 255;


					pBall = (int)screenWidth / 2;
					qBall = yAxisMargin;
					radiusBall = 10;
					
					dp = initialSpeed;
					dq = initialSpeed;


					pBoard = pBall - 50;
					qBoard = qBall - 20;
					dpBoard = 100;
					dqBoard = 10;

					isStarted = false;
					iPauseTimer(t);

				}
				else restartBall();
			}
		}
	}
	scor();
}
void restartBall()
{
	pBall = (int)screenWidth / 2;
	qBall = yAxisMargin;

	dp = initialSpeed;
	dq = initialSpeed;

	pBoard = pBall - 50;
	qBoard = qBall - 20;


	isStarted = false;
}

void defineBricks()
{
	int sumx = 100;
	int sumy = 450;
	for (int i = 0; i <totalBricks; i++)
	{
		bricks[i].red = rand() % 255;
		bricks[i].green = rand() % 255;
		bricks[i].blue = rand() % 255;

		bricks[i].p = sumx;
		bricks[i].q = sumy;
		///cout<<"brick number " <<i+1<<" "<<bricks[i].x << " "<<bricks[i].y <<endl;;
		sumx += 100;
		if (sumx > 1000)
		{
			sumx = 100;
			sumy += 20;
		}
	}
}
void lineMove()
{
	if (line <= screenWidth - 150)
		line += 15;
	else{
		(gamestate = -1);
		iPauseTimer(t2);
	}

}
int main()
{ 

	int speed = 25;
	t2 = iSetTimer(30, lineMove);
	int sum = 20;
	for (int i = 2; i >= 0; i--)
	{
		bCordinate[i].x = 50;
		bCordinate[i].y = sum;
		sum += 80;
	}
	defineBricks();

	t = iSetTimer(speed, ballChange);


	if (musicOn)
		PlaySound("music\\mu.wav", NULL, SND_LOOP | SND_ASYNC);
	iInitialize(screenWidth, screenHight, "Bricks Breaker Game");

	return 0;
}
