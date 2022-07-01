#include "iGraphics.h"
#include"bitmap_loader.h"
#include<math.h>


int im_OpeningPaper;


///ALL FLAGS
int flag_gamestate = 0;
int flag_OpenScreen = 1;
int flag_gamestateH = 0;
int flag_OpenScreenH = 1;
int i = 1;

///Timer
int colisionCheckTimer;
int fireTimer;
int bombCollisionTimer;
int bombTankCollisionHealthTimer;
int musicTimer;

///coordinates
typedef struct Coordinates coordinates;
struct Coordinates
{
	int x;
	int y;
	int w;
	int h;
};
//FirstPageOption
coordinates opt1[5] = { { 30, 420, 250, 70 }, { 30, 330, 250, 70 }, { 30, 240, 250, 70 }, { 30, 160, 250, 70 }, { 30, 80, 250, 70 } };
int opt1Picin[5];
char opt1Pic[5][30] = { "picture\\Main\\Start-Game1.png", "picture\\Main\\Instruction1.png", "picture\\Main\\High_Score1.png", "picture\\Main\\Credit1.png", "picture\\Main\\Exit1.png" };
//FirstPageOptionH
coordinates opt1H[5] = { { 30, 420, 250, 70 }, { 30, 330, 250, 70 }, { 30, 240, 250, 70 }, { 30, 160, 250, 70 }, { 30, 80, 250, 70 } };
int opt1PicinH[5];
char opt1PicH[5][30] = { "picture\\Main\\Start-Game.png", "picture\\Main\\Instructions.png", "picture\\Main\\High_Score.png", "picture\\Main\\Credit.png", "picture\\Main\\Exit.png" };
int gOver;//index
int pausePicIn;
bool pause = false;



int screenWidth = 1000; //1000 
int screenHeight = 700; //700
//Tank position 
int tank_dx = 0;
int tank_dy = -70;
int tankWidthT = 315;
int tankHeightT = 214;
int tankWidthB = 315 + 100;
int tankHeightB = 214 + 100;
int tankTopPos_dx = tank_dx + 75;
int tankTopPos_dy = tank_dy + 93;

//image 
int bottomR;
int bc;
int base;
int topR;
int topL;
int fireTopR;
int fireTopL;


//AIM
double pointx;
double pointy;
double turretCentre_x;
double turretCentre_y;
double opposite;
double adjacent;
double angle;
int horizontal;

//Fire
int firetopClickR;
int firetopClickL;
int ballPic;

//Shoot 
double firePos_x;
double firePos_y;
double bullet_x;
double bullet_y;
double gradient;
bool fire = false;
double endx;
double endy;
void shoot();
int one;
double de;
double ae;
double bcc;
double angleFixed;

//plane #enemy
//horizontal 250 ;
char planeOne[3][20] = { "picture\\p1.bmp", "picture\\p2.bmp", "picture\\p3.bmp" };
int planeNumber = 3;
int planeHorizontalLength = 150;
int planeVerticalLength = 79;
bool sonicBoom = false;

struct planestruct
{
	int plane_x;
	int plane_y;
	int planeIndex;
	bool planeShow = true;
};

planestruct enemyplane[3];

///BOMB 
int extra_bn = 4;
int bombnumber = 4;
struct bombardo
{
	int bomb_x;
	int bomb_y;
	int bombIndex;
	int picNo;
	bool bombShow = true;
};

bombardo bomb[3];

int bombW = 450;
int bombH = 250;
int bombDrop;// image variable 

//Extra bombs
struct BOMBARDO
{
	int bx;
	int by;
	int bIndex;
	int picNum;
	bool BOMBSHOW = true;
};

BOMBARDO extra_bomb[4];
int ran = 100;
int exApp[10] = { 0, 2, 4, 6, 8, 10, 12, 14, 16, 18 };
int exAppI = 0;
int virusExplode;
//background rendering 
void setAll();
struct background{
	int x;
	int y;
	int bgpicNo;
	int bgindex;
};

background bcPicture[60];
bool bcMoveFor = true;
bool bcMoveBack = true;
int I;
bool iIni = true;
int count;
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::Idraw Here::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
unsigned char debug;

//TANK Health 
struct heal
{
	int healthIndex;
	int health_x;
	int health_y;
	int picNo;


	bool healthShow;
};
heal health[6];
int healthNo;
int tankdead;
int heartpic;

bool showTankbottom = true;
bool showTanktop = true;

//tankExplosion Animation 
struct tankExplode
{
	int tankExplaodeX;
	int tankExplodeY;
	int tankexplodePicNo;

	bool showTankExplode = false;
};
tankExplode tankExplodeAnimation[6];



//Scores
char score[1000][5] = { "0", "10", "20", "30", "40", "50", "60", "70", "80", "90", "100", "110", "120", "130", "140", "150", "160", "170", "180", "190", "200", "210", "220", "230", "240", "250", "260", "270", "280", "290", "300", "310", "320", "330", "340", "350", "360", "370", "380", "390", "400", "410", "420", "430", "440", "450", "460", "470", "480", "490", "500", "510", "520", "530", "540", "550", "560", "570", "580", "590", "600", "610", "620", "630", "640", "650", "660", "670", "680", "690", "700", "710", "720", "730", "740", "750", "760", "770", "780", "790", "800", "810", "820", "830", "840", "850", "860", "870", "880", "890", "900", "910", "920", "930", "940", "950", "960", "970", "980", "990", "1000" };
int scoreIndex = 0;
bool scoreCountF = true;


//LEVEL 
bool Level1 = true;
bool Level2 = false;
bool Level3 = false;
int lvl2In;
int lvl3In;
struct lvlUP
{
	int sRng;
	int eRng;
};
lvlUP lvl1UP = { 0, 20 };
lvlUP lvl2UP = { 20, 50 };
lvlUP lvl3UP = { 50, 100 };

int lvl1UpIn;
int lvl2UpIn;
int lvl3UpIn;
int crePic;
int instPic;

//Sound 
bool musicShoot;
bool bcsoundLevel1 = false; //////////////////////////////////////////////////////////// MUSIC OFFED



//Functions
void music();



///debug
int check;


//HighScore
char name[100];
bool enter = true;
int highscorePic;
bool entername = false;
int indexNumber = 0;
int scoreBoard;
bool lvlUpF = true;
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::Idraw Here::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://


void initializaAll()
{
	showTankbottom = true;
	showTanktop = true;
	tank_dx = 0;
	tank_dy = -70;
	tankWidthT = 315;
	tankHeightT = 214;
	tankWidthB = 315 + 100;
	tankHeightB = 214 + 100;
	tankTopPos_dx = tank_dx + 75;
	tankTopPos_dy = tank_dy + 93;
	angleFixed = 0;
	angle = 0;

	lvlUpF = true;
	for (int i = 0; i < bombnumber; i++)
	{
		bomb[i].bombShow = true;
	}

	///Extra Bomb Falling

	for (int i = 2; i < extra_bn; i++)
	{
		extra_bomb[i].BOMBSHOW = true;
	}
	printf("in");
	///ALL FLAGS
	/* flag_gamestate = 0;
	flag_OpenScreen = 1;
	flag_gamestateH = 0;
	flag_OpenScreenH = 1;
	i = 1; */

	///coordinates
	pause = false;

	int bombnumber = 4;
	struct bombardo
	{
		int bomb_x;
		int bomb_y;
		int bombIndex;
		int picNo;
		bool bombShow = true;
	};

	bombardo bomb[3];


	//Tank position 




	//Shoot 
	fire = false;
	sonicBoom = false;


	bombW = 450;
	bombH = 250;


	//Extra bombs
	ran = 100;

	bcMoveFor = true;
	bcMoveBack = true;



	//Scores
	scoreIndex = 0;
	scoreCountF = true;

	//LEVEL 
	Level1 = true;
	Level2 = false;
	Level3 = false;


	//Sound 
	bcsoundLevel1 = true;

	//Functions
	setAll();
	lvlUpF = false;
	healthNo = 5;
	shoot();

}


void enemyMovement()
{
	for (int i = 0; i < planeNumber; i++)
	{
		if (enemyplane[i].planeShow)
		{
			iShowBMP2(enemyplane[i].plane_x, enemyplane[i].plane_y, planeOne[i], 0); // enemyplane[i].planeIndex
		}
		else
		{
			iShowBMP2(enemyplane[i].plane_x, enemyplane[i].plane_y, "picture\\sonicboom.bmp", 0);
			sonicBoom = false;
		}
	}
}


void bombMovement()
{
	for (int i = 0; i < bombnumber; i++)
	{

		if (bomb[i].bombShow)
		{
			if (bomb[i].bomb_y <= 5)
			{
				iShowImage(bomb[i].bomb_x + 180, bomb[i].bomb_y + 100, 100, 100, bombDrop);
			}
			else
				iShowImage(bomb[i].bomb_x, bomb[i].bomb_y, bombW, bombH, bomb[i].picNo);


			//Range Ball 
			/*
			iFilledCircle(bomb[i].bomb_x + 180 , bomb[i].bomb_y +100 , 10);

			iFilledCircle(bomb[i].bomb_x +260, bomb[i].bomb_y +100 , 10);

			iFilledCircle(bomb[i].bomb_x + 180, bomb[i].bomb_y + 180, 10);
			*/

		}

		else
		{
			//iShowBMP2(bomb[i].bomb_x + 160, bomb[i].bomb_y + 50, "picture\\sonicboom.bmp", 0);
			iShowImage(bomb[i].bomb_x + 160, bomb[i].bomb_y + 50, 150, 150, virusExplode);
			sonicBoom = false;
			//iFilledCircle(bomb[0].bomb_x, bomb[0].bomb_y, 10);
		}
	}
	//extraBomb
	if (scoreIndex >= lvl2UP.sRng && scoreIndex < lvl2UP.eRng)
		extra_bn = 3;
	if (scoreIndex >= lvl1UP.sRng && scoreIndex <= lvl1UP.eRng)
		extra_bn = 2;
	for (int i = 2; i < extra_bn; i++)
	{
		if (extra_bomb[i].BOMBSHOW)
		{

			iShowImage(extra_bomb[i].bx, extra_bomb[i].by, 50, 100, extra_bomb[i].picNum);


			//Range Ball 
			/*
			iFilledCircle(extra_bomb[i].bx , extra_bomb[i].by  , 10);

			iFilledCircle(extra_bomb[i].bx + 260, extra_bomb[i].by + 100, 10);

			iFilledCircle(bomb[i].bomb_x + 180, bomb[i].bomb_y + 180, 10);
			*/

		}

		else
		{
			//iShowBMP2(extra_bomb[i].bx, extra_bomb[i].by, "picture\\sonicboom.bmp", 0);
			iShowImage(bomb[i].bomb_x + 160, bomb[i].bomb_y + 50, 150, 150, virusExplode);

			sonicBoom = false;
			//iFilledCircle(bomb[0].bomb_x, bomb[0].bomb_y, 10);
		}
	}
	extra_bn = 4;

	iText(853, 631, score[scoreIndex], GLUT_BITMAP_TIMES_ROMAN_24);
}


void healthShow()
{
	if (healthNo < 0)
	{
		/*
		iShowImage(tank_dx +70 , tank_dy + 100 , 200, 250, tankdead);
		showTankbottom = false;
		showTanktop = false;
		*/
		showTankbottom = false;
		showTanktop = false;
		for (int i = 0; i < 6; i++)
		{
			iShowImage(tank_dx, tank_dy, 200, 250, tankExplodeAnimation[i].tankexplodePicNo);
		}

		// HIGH SCORE

		int i, j;
		int topScores[4];
		char player[4][100];
		int temp;
		char charTemp[1][100];
		strcpy(player[3], name);
		topScores[3] = scoreIndex * 10;

		FILE *fp;
		fp = fopen("highscorex.txt", "r");

		for (i = 0; i < 3; i++)
		{
			fscanf(fp, "%s %d", player[i], &topScores[i]);
		}
		fclose(fp);
		/*
		for (i = 0; i < 3; i++)
		{
		printf( "%s %d\n", player[i], topScores[i]);
		}
		*/
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (topScores[i] > topScores[j])
				{
					temp = topScores[i];
					topScores[i] = topScores[j];
					topScores[j] = temp;

					strcpy(charTemp[0], player[i]);
					strcpy(player[i], player[j]);
					strcpy(player[j], charTemp[0]);
				}
			}
		}
		/*
		for (i = 0; i < 4; i++)
		{
		printf( "%s %d\n", player[i], topScores[i]);
		}
		*/
		fp = fopen("highscorex.txt", "w");

		for (i = 0; i < 3; i++)
		{
			fprintf(fp, "%s %d\n", player[i], topScores[i]);
		}

		fclose(fp);



	}
	else
	{
		iShowImage(58, 639, 250, 40, health[healthNo].picNo);
	}



	///TANK base Range 
	//iFilledCircle(tank_dx + 60, tank_dy + 200, 5, 100);
	//iFilledCircle(tank_dx + 335, tank_dy + 200, 5, 100);

	iShowImage(58, 639, 45, 45, heartpic);
}


void iDraw()
{

	if (flag_OpenScreen == 1)
	{
		iShowImage(0, 0, 1000, 700, im_OpeningPaper);

		for (i = 0; i < 5; i++)
		{
			iShowImage(opt1[i].x, opt1[i].y, opt1[i].w, opt1[i].h, opt1Picin[i]);        //Start-->i(0) Load-->i(1) High-->i(2)
		}
		if (flag_OpenScreenH == 2)
			iShowImage(opt1H[0].x, opt1H[0].y, opt1H[0].w, opt1H[0].h, opt1PicinH[0]);
		if (flag_gamestateH == 2)
			iShowImage(opt1H[1].x, opt1H[1].y, opt1H[1].w, opt1H[1].h, opt1PicinH[1]);
		if (flag_gamestateH == 3)
			iShowImage(opt1H[2].x, opt1H[2].y, opt1H[2].w, opt1H[2].h, opt1PicinH[2]);
		if (flag_gamestateH == 4)
			iShowImage(opt1H[3].x, opt1H[3].y, opt1H[3].w, opt1H[3].h, opt1PicinH[3]);
		if (flag_gamestateH == 5)
			iShowImage(opt1H[4].x, opt1H[4].y, opt1H[4].w, opt1H[4].h, opt1PicinH[4]);
	}


	else if (flag_OpenScreen == 2)
	{
		iClear();

		if (enter)
		{
			iShowImage(0, 0, screenWidth, screenHeight, highscorePic);
			iText(396, 339, name, GLUT_BITMAP_TIMES_ROMAN_24);
			return;

		}
		else
		{
			if (lvlUpF && (scoreIndex == lvl2UP.sRng || scoreIndex == lvl3UP.sRng || scoreIndex == lvl3UP.eRng))
			{
				if (scoreIndex == lvl2UP.sRng)
				{
					iShowImage(0, 0, screenWidth, screenHeight, lvl1UpIn);
				}
				if (scoreIndex == lvl3UP.sRng)
				{
					iShowImage(0, 0, screenWidth, screenHeight, lvl2UpIn);
				}
				if (scoreIndex == lvl3UP.eRng)
				{
					iShowImage(0, 0, screenWidth, screenHeight, lvl3UpIn);
				}
			}


			// backgroun rendering
			//Level 1

			else
			{
				if (scoreIndex >= lvl1UP.sRng && scoreIndex <= lvl1UP.eRng)
				{
					for (int i = 0; i < 20; i++)
					{
						iShowImage(bcPicture[i].x, bcPicture[i].y, 63, 700, bcPicture[i].bgpicNo);
					}
					//printf("%d\n", scoreIndex);
				}


				//Level 2

				if (scoreIndex >= lvl2UP.sRng && scoreIndex < lvl2UP.eRng)
				{
					iShowImage(0, 0, 1000, 700, lvl2In);
					for (int i = 20; i < 40; i++)
					{
						iShowImage(bcPicture[i].x, bcPicture[i].y, 63, 700, bcPicture[i].bgpicNo);
					}

					if (scoreIndex >(lvl2UP.sRng) && scoreIndex < (lvl2UP.eRng))
					{
						lvlUpF = true;
						printf("%d", lvlUpF);
					}

				}


				//Level 3
				if (scoreIndex >= lvl3UP.sRng && scoreIndex <= lvl3UP.eRng)
				{
					iShowImage(0, 0, 1000, 700, lvl3In);
					for (int i = 40; i < 60; i++)
					{
						iShowImage(bcPicture[i].x, bcPicture[i].y, 63, 700, bcPicture[i].bgpicNo);
					}

					if (scoreIndex >(lvl3UP.sRng) && scoreIndex < (lvl3UP.eRng))
					{
						lvlUpF = true;
						printf("%d", lvlUpF);
					}
				}
				/**/



				iShowImage(0, 0, iScreenWidth, 100, base);

				//printf("Angle = %lf\n", angle);
				if (showTankbottom == true)
				{
					iShowImage(tank_dx, tank_dy, tankWidthB, tankHeightB, bottomR);
				}

				//ANGLE SHOOTING
				//BALL Fire
				if (showTanktop == true)
				{
					if (fire == true)
					{
						//shoot();

						if (angleFixed >= 0 && angleFixed <= 90)
							iShowBMPAlternativeSkipWhite(bullet_x - 10, bullet_y - 10, "picture\\BallSth.bmp");

						else
							iShowBMPAlternativeSkipWhite(bullet_x - 10, bullet_y - 10, "picture\\BallSth.bmp");
					}

					if (angle >= 0 && angle <= 90)
					{
						iRotate(turretCentre_x, turretCentre_y, angle);
						iShowImage(tankTopPos_dx, tankTopPos_dy - 20, tankWidthT, tankHeightT + 20, topR);
						iUnRotate();
					}

					else
					{
						iRotate(turretCentre_x - 50, turretCentre_y, angle);
						iShowImage(tankTopPos_dx - 100, tankTopPos_dy - 30, tankWidthT - 10, tankHeightT + 60, topL);
						iUnRotate();
					}

				}

				//printf("point x = %d\n", pointx);
				iSetColor(255, 0, 0);
				iFilledCircle(pointx, pointy, 10, 100);
				//iFilledCircle(turretCentre_x, turretCentre_y, 10, 100);
				//iFilledCircle(firePos_x, firePos_y + 10, 10, 100);

				//enemyMovement();
				bombMovement();

				healthShow();

				//pause
				if (pause)
					iShowImage(200, 240, 600, 300, pausePicIn);

			}

		}
	}


	if (flag_gamestate == 2)
	{
		//loadgame
		iClear();
		iShowImage(0, 0, screenWidth, screenHeight, instPic);
		flag_OpenScreen = 0;
		//iText(853, 631, "Instruction", GLUT_BITMAP_TIMES_ROMAN_24);
	}

	if (flag_gamestate == 3)
	{
		iClear();
		//// HIGH SCORE
		iShowImage(0, 0, screenWidth, screenHeight, scoreBoard);

		char player[3][100];
		char scoresNow[3][100];

		int i;

		FILE *f;

		f = fopen("highscorex.txt", "r");
		for (i = 0; i < 3; i++)
		{
			fscanf(f, "%s %s", player[i], scoresNow[i]);
		}
		fclose(f);

		///printing names
		iSetColor(255, 255, 0);
		iText(213 + 150, 489, player[0], GLUT_BITMAP_TIMES_ROMAN_24);
		iText(213 + 150, 420, player[1], GLUT_BITMAP_TIMES_ROMAN_24);
		iText(213 + 150, 351, player[2], GLUT_BITMAP_TIMES_ROMAN_24);
		///printing Score
		iSetColor(0, 255, 0);
		iText(500 + 150, 489, scoresNow[0], GLUT_BITMAP_TIMES_ROMAN_24);
		iText(500 + 150, 420, scoresNow[1], GLUT_BITMAP_TIMES_ROMAN_24);
		iText(500 + 150, 351, scoresNow[2], GLUT_BITMAP_TIMES_ROMAN_24);


		flag_OpenScreen = 0;


	}



	if (flag_gamestate == 4)
	{
		//credit
		iClear();
		iShowImage(0, 0, screenWidth, screenHeight, crePic);
		flag_OpenScreen = 0;

		//iText(853, 631, "Instruction", GLUT_BITMAP_TIMES_ROMAN_24);
	}
	if (flag_gamestate == 5)
	{
		//exit
		iClear();
		flag_OpenScreen = 0;
		exit(0);
		//iText(853, 631, "Instruction", GLUT_BITMAP_TIMES_ROMAN_24);
	}
	if (healthNo == -1)
	{
		iShowImage(0, 0, 1000, 700, gOver);
		flag_OpenScreen = 0;

	}




}


void iMouseMove(int mx, int my)
{
	pointx = mx;
	pointy = my;

	turretCentre_x = tankTopPos_dx + (tankWidthT / 2) - 10;

	turretCentre_y = tankTopPos_dy + 100;
	opposite = pointy - (turretCentre_y);
	if (angle >= 0 && angle <= 90)
		adjacent = pointx - (turretCentre_x);
	else
		adjacent = pointx - (turretCentre_x - 50);
	angle = atan(opposite / adjacent) * 180 / 3.14159265;

}

//*******************************************************************ipassiveMouse***********************************************************************//
void iPassiveMouseMove(int mx, int my)
{
	if (flag_OpenScreen == 1)
	{
		for (i = 0; i < 5; i++)
		{
			if ((mx >= opt1[i].x && mx <= opt1[i].x + opt1[i].w)
				&& (my >= opt1[i].y && my <= opt1[i].y + opt1[i].h))
			{
				if (i == 0)
					flag_OpenScreenH = 2;
				else
					flag_gamestateH = i + 1;
				break;

			}
			else
			{
				flag_OpenScreenH = 0;
				flag_gamestateH = 0;
			}
		}
		//printf("%d %d\n", flag_gamestateH, flag_OpenScreenH);
	}
}


void iMouse(int button, int state, int mx, int my)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		printf("Point = %d %d\n", mx, my);
		printf("Point = %d %d\n", mx, my);
		//printf("%d %d\n", flag_gamestate, flag_OpenScreen);


		///FirstScreen
		if (flag_OpenScreen == 1)
		{
			for (i = 0; i < 5; i++)
			{
				if ((mx >= opt1[i].x && mx <= opt1[i].x + opt1[i].w)
					&& (my >= opt1[i].y && my <= opt1[i].y + opt1[i].h))
				{
					if (i == 0)
						flag_OpenScreen = 2;
					else
						flag_gamestate = i + 1;
					//printf("%d %d\n", flag_gamestate, flag_OpenScreen);
				}
			}
		}
		///FirstScreenFinish

		//if (enter)(mx > 853 && mx < 324 && my > 324 && my < 795 ) entername = 1 ;





	}


	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{

	}
}


void iKeyboard(unsigned char key)
{
	if ((key == 'd' || key == 'D') && tank_dx <= screenWidth - tankWidthB + 90)
	{
		tank_dx += 10;
		tankTopPos_dx += 10;

		turretCentre_x = tankTopPos_dx + (tankWidthT / 2) - 10;
		turretCentre_y = tankTopPos_dy + 100;
		//AIM Turret Rotation
		//bullet_x = turretCentre_x;
		//bullet_y = turretCentre_y;
		if (bcMoveFor)
		{
			setAll();
			bcMoveFor = false;
			bcMoveBack = true;
		}

		//Level 1
		if (scoreIndex >= lvl1UP.sRng && scoreIndex < lvl1UP.eRng)
		{
			for (I = 0; I < 20; I++)
			{
				bcPicture[I].x -= 7;

				if (bcPicture[I].x <= -64)
				{
					bcPicture[I].x = screenWidth + 165;

				}
				//count = I;
				//iIni = true;
			}
		}


		//Level 2
		if (scoreIndex >= lvl2UP.sRng && scoreIndex < lvl2UP.eRng)
		{
			for (I = 20; I < 40; I++)
			{
				bcPicture[I].x -= 7;

				if (bcPicture[I].x <= -64)
				{
					bcPicture[I].x = screenWidth + 165;

				}
				//count = I;
				//iIni = true;
			}
		}
		/**/

		//Level 3
		if (scoreIndex >= lvl3UP.sRng && scoreIndex <= lvl3UP.eRng)
		{
			for (I = 40; I < 60; I++)
			{
				bcPicture[I].x -= 7;

				if (bcPicture[I].x <= -64)
				{
					bcPicture[I].x = screenWidth + 165;

				}
				//count = I;
				//iIni = true;
			}
		}
		/**/
	}

	if ((key == 'a' || key == 'A') && tank_dx >= -70)
	{
		tank_dx -= 10;
		tankTopPos_dx -= 10;

		turretCentre_x = tankTopPos_dx + (tankWidthT / 2) - 10;
		turretCentre_y = tankTopPos_dy + 100;
		//AIM Turret Rotation 
		//bullet_x = turretCentre_x;
		//bullet_y = turretCentre_y;
		if (bcMoveBack)
		{
			setAll();
			bcMoveFor = true;
			bcMoveBack = false;
		}

		//Level 1
		if (scoreIndex >= lvl1UP.sRng && scoreIndex < lvl1UP.eRng)
		{
			for (I = 0; I < 20; I++)
			{
				bcPicture[I].x += 7;

				if (bcPicture[I].x >= 1180)
				{
					bcPicture[I].x = -55;

				}
			}
		}


		//Level 2
		if (scoreIndex >= lvl2UP.sRng && scoreIndex < lvl2UP.eRng)
		{
			for (I = 20; I < 40; I++)
			{
				bcPicture[I].x += 7;

				if (bcPicture[I].x >= 1180)
				{
					bcPicture[I].x = -55;

				}
			}
		}
		/**/

		//Level 3
		if (scoreIndex >= lvl3UP.sRng && scoreIndex <= lvl3UP.eRng)
		{
			for (I = 40; I < 60; I++)
			{
				bcPicture[I].x += 7;

				if (bcPicture[I].x >= 1180)
				{
					bcPicture[I].x = -55;

				}
			}
		}
		/**/


	}

	if (key == ' ')
	{
		fire = true;
		if (angle >= 0 && angle <= 90)
			bullet_x = turretCentre_x;
		else
			bullet_x = turretCentre_x - 50;
		one = 1;
		scoreCountF = true;

		musicShoot = true;
		//printf("MusicShoot keyboard = %d\n", musicShoot);
		printf("score space %d\n", scoreCountF);
		PlaySound("picture\\soundShoot.wav", NULL, SND_ASYNC);
		//PlaySoundA("picture\\s1.wav", NULL, SND_ASYNC);
		//bcsoundLevel1 = true;

		///debug
		iIni = true;
	}
	if ((key == 'p' || key == 'P') && flag_OpenScreen == 2)
	{
		PlaySound("picture\\PAUSE.wav", NULL, SND_ASYNC);
		iPauseTimer(fireTimer);
		iPauseTimer(musicTimer);
		iPauseTimer(colisionCheckTimer);
		iPauseTimer(bombCollisionTimer);
		iPauseTimer(bombTankCollisionHealthTimer);
		pause = true;
	}
	if (key == 'r')
	{
		pause = false;
		PlaySound("picture\\PAUSE.wav", NULL, SND_ASYNC);
		iResumeTimer(fireTimer);
		iResumeTimer(musicTimer);
		iResumeTimer(colisionCheckTimer);
		iResumeTimer(bombCollisionTimer);
		iResumeTimer(bombTankCollisionHealthTimer);
	}


	//printf("TankTop x = %d , tanktop y = %d  %d\n", tankTopPos_dx, tankTopPos_dy, turretCentre_y);
	//printf("Bullet x = %lf , bullet y = %lf\n", bullet_x, bullet_y);
	//printf("turretCentre_x = %lf ,turretCentre_y = %lf\n", turretCentre_x, turretCentre_y);




	//input name thingy

	if (enter && flag_OpenScreen == 2)
	{
		if (key != '\b')
		{
			name[indexNumber] = key;
			indexNumber++;
			name[indexNumber] = '\0';
		}
		else
		{
			if (indexNumber <= 0){
				indexNumber = 0;
			}
			else
			{
				indexNumber--;
			}
			name[indexNumber] = '\0';
		}
	}




	/// Exit  
	if (key == 'b')
	{
		///HIGH SCORE
		if (scoreIndex == lvl3UP.eRng)
		{

			int i, j;
			int topScores[4];
			char player[4][100];
			int temp;
			char charTemp[1][100];
			strcpy(player[3], name);
			topScores[3] = scoreIndex * 10;

			FILE *fp;
			fp = fopen("highscorex.txt", "r");

			for (i = 0; i < 3; i++)
			{
				fscanf(fp, "%s %d", player[i], &topScores[i]);
			}
			fclose(fp);

			for (i = 0; i < 3; i++)
			{
				printf("%s %d\n", player[i], topScores[i]);
			}

			for (i = 0; i < 4; i++)
			{
				for (j = 0; j < 4; j++)
				{
					if (topScores[i] > topScores[j])
					{
						temp = topScores[i];
						topScores[i] = topScores[j];
						topScores[j] = temp;

						strcpy(charTemp[0], player[i]);
						strcpy(player[i], player[j]);
						strcpy(player[j], charTemp[0]);
					}
				}

			}
			for (i = 0; i < 4; i++)
			{
				printf("%s %d\n", player[i], topScores[i]);
			}

			fp = fopen("highscorex.txt", "w");

			for (i = 0; i < 3; i++)
			{
				fprintf(fp, "%s %d\n", player[i], topScores[i]);
			}

			fclose(fp);

		}
		initializaAll();
		flag_OpenScreen = 1;
		flag_gamestate = 0;
		enter = true;
	}

	// LEVEL UP SCREEN COMMAND NEXT

	if (key == 'f' || key == 'F')
	{


		if (scoreIndex == lvl3UP.eRng)
		{
			initializaAll();
			flag_OpenScreen = 1;
			flag_gamestate = 0;
		}
		else
		{
			lvlUpF = false;
			for (int i = 0; i < bombnumber; i++)
			{
				bomb[i].bombShow = true;
			}

			///Extra Bomb Falling

			for (int i = 2; i < extra_bn; i++)
			{
				extra_bomb[i].BOMBSHOW = true;
			}
			if (scoreIndex != lvl3UP.eRng)
			{
				showTankbottom = true;
				showTanktop = true;
				tank_dx = 0;
				tank_dy = -70;
				tankWidthT = 315;
				tankHeightT = 214;
				tankWidthB = 315 + 100;
				tankHeightB = 214 + 100;
				tankTopPos_dx = tank_dx + 75;
				tankTopPos_dy = tank_dy + 93;
				angleFixed = 0;
				angle = 0;
			}

		}
	}


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


	if (key == GLUT_KEY_RIGHT)
	{

	}
	if (key == GLUT_KEY_LEFT)
	{

	}

	if (key == GLUT_KEY_HOME)
	{

	}
	if (key == GLUT_KEY_END)
	{
		enter = false;
		//printf("Name = %s", name);
	}

}


void shoot()
{
	if (fire == true)
	{
		if (one)
		{
			firePos_x = turretCentre_x;
			firePos_y = turretCentre_y;
			endx = pointx;
			endy = pointy;
			one = 0;
			angleFixed = angle;
		}

		de = (endy - firePos_y);
		if (angleFixed >= 0 && angleFixed <= 90)
		{
			ae = (endx - firePos_x);
			bcc = ((bullet_x - firePos_x)*de) / ae;
		}
		else
		{
			ae = (endx - firePos_x + 50);
			bcc = ((bullet_x - firePos_x + 50)*de) / ae;
		}

		bullet_y = bcc + firePos_y;
		//printf("Bullet x = %lf , bullet y = %lf\n", bullet_x, bullet_y);
		//printf("turretCentre_x = %lf ,turretCentre_y = %lf %lf\n", turretCentre_x, turretCentre_y, gradient);

		//printf("%lf\n", angleFixed);

		if (bullet_x > endx && angleFixed >= 0 && angleFixed <= 90)
		{
			fire = false;
		}
		if (bullet_y > endy && angleFixed >= -90 && angleFixed <= -0)
		{
			fire = false;
		}

		if (angleFixed <= 90 && angleFixed >= 0)
		{
			if (angleFixed >= 88)
				bullet_x += 7.1;
			else if (angleFixed >= 80 && angleFixed < 88)
				bullet_x += 07.5;
			else if (angleFixed >= 70 && angleFixed < 80)
				bullet_x += 8;
			else if (angleFixed >= 60 && angleFixed < 70)
				bullet_x += 8.5;
			else if (angleFixed >= 50 && angleFixed < 60)
				bullet_x += 9;
			else
				bullet_x += 10;
		}
		else
		{
			if (angleFixed <= -87)
				bullet_x -= 7.1;
			else if (angleFixed <= -80 && angleFixed > -87)
				bullet_x -= 7.5;
			else if (angleFixed <= -70 && angleFixed > -80)
				bullet_x -= 8;
			else if (angleFixed <= -60 && angleFixed > -70)
				bullet_x -= 8.5;
			else if (angleFixed <= -50 && angleFixed > -60)
				bullet_x -= 9;
			else
				bullet_x -= 10;
		}


	}

	////////PlaneEnemy 

	for (int i = 0; i < planeNumber; i++)
	{
		enemyplane[i].plane_x -= 10;
		if (enemyplane[i].plane_x <= 0)
		{
			enemyplane[i].plane_x = screenWidth + rand() % 100;
			enemyplane[i].planeShow = true;
		}

		enemyplane[i].planeIndex++;
		if (enemyplane[i].planeIndex >= 3)
			enemyplane[i].planeIndex = 0;

	}

	///Bomb Falling 

	for (int i = 0; i < bombnumber; i++)
	{
		bomb[i].bomb_y -= 1;
		if (scoreIndex >= lvl1UP.sRng && scoreIndex <= lvl1UP.eRng)
		{
			bomb[i].bomb_y -= 1;
		}
		else if (scoreIndex >= lvl2UP.sRng && scoreIndex < lvl2UP.eRng)
		{
			bomb[i].bomb_y -= 2;
		}

		else if (scoreIndex >= lvl3UP.sRng && scoreIndex <= lvl3UP.eRng)
		{
			bomb[i].bomb_y -= 3;
		}



		if (bomb[i].bomb_y <= 0)// || bomb[i].bomb_y>=700
		{
			bomb[i].bomb_y = screenHeight + rand() % 100;
			bomb[i].bombShow = true;
		}
	}

	///Extra Bomb Falling

	for (int i = 2; i < extra_bn; i++)
	{
		extra_bomb[i].by -= 2;

		if (extra_bomb[i].by <= 0)// || extra_bomb[i].by >= 700
		{
			extra_bomb[i].by = screenHeight + rand() % 1000;
			extra_bomb[i].BOMBSHOW = true;
		}
	}
}


///BackGround
void setAll()
{
	//Level 1
	if (scoreIndex >= lvl1UP.sRng && scoreIndex < lvl1UP.eRng)
	{
		int sum = 0;
		for (int i = 0; i < 20; i++)
		{
			bcPicture[i].y = 0;
			bcPicture[i].x = sum;
			sum += 62;
		}
	}


	//Level 2
	if (scoreIndex >= lvl2UP.sRng && scoreIndex < lvl2UP.eRng)
	{
		int sum = 0;
		for (int i = 20; i < 40; i++)
		{
			bcPicture[i].y = 0;
			bcPicture[i].x = sum;
			sum += 62;
		}
	}
	/**/

	//Level 3
	if (scoreIndex >= lvl3UP.sRng && scoreIndex < lvl3UP.eRng)
	{
		int sum = 0;
		for (int i = 40; i < 60; i++)
		{
			bcPicture[i].y = 0;
			bcPicture[i].x = sum;
			sum += 62;
		}
	}
	/**/
}


void setEnemyVariables()
{
	for (int i = 0; i < planeNumber; i++)
	{
		enemyplane[i].plane_x = screenWidth + rand() % 1000;
		enemyplane[i].plane_y = 375 + rand() % 300;
		enemyplane[i].planeShow = true; /// collission 
	}
}


void setBombVariables()
{
	for (int i = 0; i < bombnumber; i++)
	{
		bomb[i].bomb_x = 0 + rand() % 1010;
		bomb[i].bomb_y = screenHeight + rand() % 1000;
		bomb[i].bombShow = true; // collision 
	}

}


void setExtraBombVariables()
{
	///ExtraBomb
	for (int j = 2; j < extra_bn; j++)
	{
		extra_bomb[j].bx = 0 + rand() % ran;

		extra_bomb[j].by = screenHeight + rand() % 1000;

		extra_bomb[j].BOMBSHOW = true;

		if (ran > 900)
			ran = 200;
		ran += 500;
	}


}


void imageLoaded()
{
	//MainMenu
	im_OpeningPaper = iLoadImage("picture\\MainMenu.png");
	///OpeningScreenPicMainMenu
	for (int i = 0; i < 5; i++)
	{
		opt1Picin[i] = iLoadImage(opt1Pic[i]);
	}
	for (int i = 0; i < 5; i++)
	{
		opt1PicinH[i] = iLoadImage(opt1PicH[i]);
	}
	gOver = iLoadImage("picture\\Game_Over.png");
	pausePicIn = iLoadImage("picture\\Main\\Pausemenu.png");
	crePic = iLoadImage("picture\\Main\\Creditpic.png");
	instPic = iLoadImage("picture\\Main\\Instructionspic.png");
	lvl1UpIn = iLoadImage("picture\\Extra\\Level1com.png");
	lvl2UpIn = iLoadImage("picture\\Extra\\Level2com.png");
	lvl3UpIn = iLoadImage("picture\\Extra\\Level3com.png");

	//High Score Screen
	highscorePic = iLoadImage("picture\\Main\\highscoreMain.png");

	//Tank Body 
	topR = iLoadImage("picture\\topR.png");
	topL = iLoadImage("picture\\topL.png");
	bottomR = iLoadImage("picture\\bottomR.png");
	bc = iLoadImage("picture\\bc.jpg");
	base = iLoadImage("picture\\base.png");
	fireTopR = iLoadImage("picture\\fireTopR.png");
	fireTopL = iLoadImage("picture\\fireTopL.png");

	///BOMBS
	bomb[0].picNo = iLoadImage("picture\\m0.png");
	bomb[1].picNo = iLoadImage("picture\\m1.png");
	bomb[2].picNo = iLoadImage("picture\\m2.png");
	bomb[3].picNo = iLoadImage("picture\\m3.png");
	bombDrop = iLoadImage("picture\\bombdrop.png");
	virusExplode = iLoadImage("picture\\sonicboom.png");
	///EXTRA_BOMBS
	extra_bomb[0].picNum = iLoadImage("picture\\m3.png");
	extra_bomb[1].picNum = iLoadImage("picture\\m2.png");
	extra_bomb[2].picNum = iLoadImage("picture\\Health1.png");
	extra_bomb[3].picNum = iLoadImage("picture\\Health1.png");

	///Health 
	health[0].picNo = iLoadImage("picture\\h0.png");
	health[1].picNo = iLoadImage("picture\\h1.png");
	health[2].picNo = iLoadImage("picture\\h2.png");
	health[3].picNo = iLoadImage("picture\\h3.png");
	health[4].picNo = iLoadImage("picture\\h4.png");
	health[5].picNo = iLoadImage("picture\\h5.png");
	heartpic = iLoadImage("picture\\theheart.png");
	tankdead = iLoadImage("picture\\boom.png");

	///Background
	bcPicture[0].bgpicNo = iLoadImage("picture\\Level1\\b1.png");
	bcPicture[1].bgpicNo = iLoadImage("picture\\Level1\\b2.png");
	bcPicture[2].bgpicNo = iLoadImage("picture\\Level1\\b3.png");
	bcPicture[3].bgpicNo = iLoadImage("picture\\Level1\\b4.png");
	bcPicture[4].bgpicNo = iLoadImage("picture\\Level1\\b5.png");
	bcPicture[5].bgpicNo = iLoadImage("picture\\Level1\\b6.png");
	bcPicture[6].bgpicNo = iLoadImage("picture\\Level1\\b7.png");
	bcPicture[7].bgpicNo = iLoadImage("picture\\Level1\\b8.png");
	bcPicture[8].bgpicNo = iLoadImage("picture\\Level1\\b9.png");
	bcPicture[9].bgpicNo = iLoadImage("picture\\Level1\\b10.png");
	bcPicture[10].bgpicNo = iLoadImage("picture\\Level1\\b11.png");
	bcPicture[11].bgpicNo = iLoadImage("picture\\Level1\\b12.png");
	bcPicture[12].bgpicNo = iLoadImage("picture\\Level1\\b13.png");
	bcPicture[13].bgpicNo = iLoadImage("picture\\Level1\\b14.png");
	bcPicture[14].bgpicNo = iLoadImage("picture\\Level1\\b15.png");
	bcPicture[15].bgpicNo = iLoadImage("picture\\Level1\\b16.png");
	bcPicture[16].bgpicNo = iLoadImage("picture\\Level1\\b17.png");
	bcPicture[17].bgpicNo = iLoadImage("picture\\Level1\\b18.png");
	bcPicture[18].bgpicNo = iLoadImage("picture\\Level1\\b19.png");
	bcPicture[19].bgpicNo = iLoadImage("picture\\Level1\\b20.png");

	//Level 2
	lvl2In = iLoadImage("picture\\Level2\\Lvl2.jpg");
	bcPicture[20].bgpicNo = iLoadImage("picture\\Level2\\c1.png");
	bcPicture[21].bgpicNo = iLoadImage("picture\\Level2\\c2.png");
	bcPicture[22].bgpicNo = iLoadImage("picture\\Level2\\c3.png");
	bcPicture[23].bgpicNo = iLoadImage("picture\\Level2\\c4.png");
	bcPicture[24].bgpicNo = iLoadImage("picture\\Level2\\c5.png");
	bcPicture[25].bgpicNo = iLoadImage("picture\\Level2\\c6.png");
	bcPicture[26].bgpicNo = iLoadImage("picture\\Level2\\c7.png");
	bcPicture[27].bgpicNo = iLoadImage("picture\\Level2\\c8.png");
	bcPicture[28].bgpicNo = iLoadImage("picture\\Level2\\c9.png");
	bcPicture[29].bgpicNo = iLoadImage("picture\\Level2\\c10.png");
	bcPicture[30].bgpicNo = iLoadImage("picture\\Level2\\c11.png");
	bcPicture[31].bgpicNo = iLoadImage("picture\\Level2\\c12.png");
	bcPicture[32].bgpicNo = iLoadImage("picture\\Level2\\c13.png");
	bcPicture[33].bgpicNo = iLoadImage("picture\\Level2\\c14.png");
	bcPicture[34].bgpicNo = iLoadImage("picture\\Level2\\c15.png");
	bcPicture[35].bgpicNo = iLoadImage("picture\\Level2\\c16.png");
	bcPicture[36].bgpicNo = iLoadImage("picture\\Level2\\c17.png");
	bcPicture[37].bgpicNo = iLoadImage("picture\\Level2\\c18.png");
	bcPicture[38].bgpicNo = iLoadImage("picture\\Level2\\c19.png");
	bcPicture[39].bgpicNo = iLoadImage("picture\\Level2\\c20.png");

	//Level 3

	lvl3In = iLoadImage("picture\\Level3\\Lvl3.png");
	bcPicture[40].bgpicNo = iLoadImage("picture\\Level3\\d1.png");
	bcPicture[41].bgpicNo = iLoadImage("picture\\Level3\\d2.png");
	bcPicture[42].bgpicNo = iLoadImage("picture\\Level3\\d3.png");
	bcPicture[43].bgpicNo = iLoadImage("picture\\Level3\\d4.png");
	bcPicture[44].bgpicNo = iLoadImage("picture\\Level3\\d5.png");
	bcPicture[45].bgpicNo = iLoadImage("picture\\Level3\\d6.png");
	bcPicture[46].bgpicNo = iLoadImage("picture\\Level3\\d7.png");
	bcPicture[47].bgpicNo = iLoadImage("picture\\Level3\\d8.png");
	bcPicture[48].bgpicNo = iLoadImage("picture\\Level3\\d9.png");
	bcPicture[49].bgpicNo = iLoadImage("picture\\Level3\\d10.png");
	bcPicture[50].bgpicNo = iLoadImage("picture\\Level3\\d11.png");
	bcPicture[51].bgpicNo = iLoadImage("picture\\Level3\\d12.png");
	bcPicture[52].bgpicNo = iLoadImage("picture\\Level3\\d13.png");
	bcPicture[53].bgpicNo = iLoadImage("picture\\Level3\\d14.png");
	bcPicture[54].bgpicNo = iLoadImage("picture\\Level3\\d15.png");
	bcPicture[55].bgpicNo = iLoadImage("picture\\Level3\\d16.png");
	bcPicture[56].bgpicNo = iLoadImage("picture\\Level3\\d17.png");
	bcPicture[57].bgpicNo = iLoadImage("picture\\Level3\\d18.png");
	bcPicture[58].bgpicNo = iLoadImage("picture\\Level3\\d19.png");
	bcPicture[59].bgpicNo = iLoadImage("picture\\Level3\\d20.png");

	//tank explode animation 
	tankExplodeAnimation[0].tankexplodePicNo = iLoadImage("picture\\bT0.png");
	tankExplodeAnimation[1].tankexplodePicNo = iLoadImage("picture\\bT1.png");
	tankExplodeAnimation[2].tankexplodePicNo = iLoadImage("picture\\bT2.png");
	tankExplodeAnimation[3].tankexplodePicNo = iLoadImage("picture\\bT3.png");
	tankExplodeAnimation[4].tankexplodePicNo = iLoadImage("picture\\bT4.png");
	tankExplodeAnimation[5].tankexplodePicNo = iLoadImage("picture\\bT5.png");

	///ScoreBoard
	scoreBoard = iLoadImage("picture\\Main\\scoreBoard.png");


}


void colisionCheck()
{

	if ((enemyplane[0].plane_x <= bullet_x && enemyplane[0].plane_x <= bullet_x) && (enemyplane[0].plane_y <= bullet_y && enemyplane[0].plane_y <= bullet_y))
	{
		enemyplane[0].planeShow = false;

		sonicBoom = true;


	}



	else if ((enemyplane[1].plane_x <= bullet_x && enemyplane[1].plane_x <= bullet_x) && (enemyplane[1].plane_y <= bullet_y && enemyplane[1].plane_y <= bullet_y))
	{
		enemyplane[1].planeShow = false;

		sonicBoom = true;
	}


	else if ((enemyplane[2].plane_x <= bullet_x && enemyplane[2].plane_x <= bullet_x) && (enemyplane[2].plane_y <= bullet_y && enemyplane[2].plane_y <= bullet_y))
	{
		enemyplane[2].planeShow = false;

		sonicBoom = true;
	}

}


void bombCollision()
{

	for (int i = 0; i < bombnumber; i++)
	{
		if ((bomb[i].bomb_x + 180 <= bullet_x && bullet_x <= bomb[i].bomb_x + 260) && (bomb[i].bomb_y <= bullet_y && bomb[i].bomb_y + 180 >= bullet_y) && scoreCountF && bomb[i].bombShow)
		{
			bomb[i].bombShow = false;

			sonicBoom = true;
			scoreIndex++;
			check = i;
			printf("%d %d\n", bomb[i].bombShow, scoreCountF);

		}
	}
	/*if (iIni)
	{
	printf("%d %d f\n", bomb[check].bombShow, scoreCountF);

	}*/


	///extra
	if (scoreIndex >= lvl2UP.sRng && scoreIndex < lvl2UP.eRng)
		extra_bn = 3;
	if (scoreIndex >= lvl1UP.sRng && scoreIndex <= lvl1UP.eRng)
		extra_bn = 2;

	for (int i = 2; i < extra_bn; i++)
	{

		if ((extra_bomb[i].bx <= bullet_x && bullet_x <= extra_bomb[i].bx + 50) && (extra_bomb[i].by <= bullet_y && extra_bomb[i].by + 100 >= bullet_y) && scoreCountF && extra_bomb[i].BOMBSHOW)
		{
			extra_bomb[i].BOMBSHOW = false;

			sonicBoom = true;

			if (i == 0)
				scoreIndex -= 2;
			else if (i == 1)
				scoreIndex += 2;
			else
				healthNo++;
			if (healthNo > 5)
				healthNo = 5;
			if (scoreIndex < 0)
				scoreIndex = 0;
			printf("%d %d ex\n", extra_bomb[i].BOMBSHOW, scoreCountF);
			//check = i;
		}


	}
	/*if (iIni)
	{
	printf("%d %d ex\n", extra_bomb[check].BOMBSHOW, scoreCountF);
	iIni = false;
	}*/
	extra_bn = 4;

	////
	if (bullet_x > endx && angleFixed >= 0 && angleFixed <= 90)
	{
		scoreCountF = false;
		//printf("score col %d\n", scoreCountF);
	}
	if (bullet_y > endy && angleFixed >= -90 && angleFixed <0)
	{
		scoreCountF = false;
		//printf("score col %d\n", scoreCountF);
	}

}


void bombTankCollisionHealth()
{
	for (int i = 0; i < 5; i++)
	{
		if ((bomb[i].bomb_x + 180 >= tank_dx + 60 && bomb[i].bomb_x + 260 <= tank_dx + 335) && (bomb[i].bomb_y + 100 == tank_dy + 200) && bomb[i].bombShow)
		{
			healthNo--;
		}
	}

	/*
	iFilledCircle(tank_dx + 60, tank_dy + 200, 5, 100);
	iFilledCircle(tank_dx + 335, tank_dy + 200, 5, 100);

	iFilledCircle(bomb[i].bomb_x + 180 , bomb[i].bomb_y +100 , 10);

	iFilledCircle(bomb[i].bomb_x +260, bomb[i].bomb_y +100 , 10);

	iFilledCircle(bomb[i].bomb_x + 180, bomb[i].bomb_y + 180, 10);
	*/
}


void music()
{
	//printf("Music Shoot = %d\n", musicShoot);

	/*
	if (musicShoot == true)
	{
	bcsoundLevel1 = false;
	PlaySound("picture\\soundShoot.wav", NULL, SND_ASYNC); ///one time else SND_LOOP | SND_ASYNC;
	musicShoot = false;
	bcsoundLevel1 = true;
	}
	*/
	if (bcsoundLevel1 == true)
	{
		//PlaySound("picture\\s1.wav", NULL, SND_ASYNC);
		PlaySoundA("picture\\s1.wav", NULL, SND_ASYNC);
		//bcsoundLevel1 = false;
	}

	//printf("in\n");
}

////debug
void makeTrue()
{
	for (int i = 0; i < bombnumber; i++)
	{
		if (bomb[i].bomb_y<0 && bomb[i].bomb_y>1000)
			bomb[i].bombShow = true;
	}
	for (int i = 0; i < extra_bn; i++)
	{
		if (extra_bomb[i].by<0 && extra_bomb[i].by>1000)
			extra_bomb[i].BOMBSHOW = true;
	}
}
///findebug


void highScoreX(int scoreIndex, char *name)
{
	FILE *fp;
	int i, j;
	int topScores[3];
	char player[3][100];

	fp = fopen("highscorex.txt", "r");



	for (i = 0; i < 3; i++)
	{
		fscanf(fp, "%s %d", player[i], &topScores[i]);
	}
	/*
	for (i = 0; i < 3; i++)
	{
	if ((scoreIndex - 1) * 10 > topScores[i])
	{
	for (j = 2; j>i; j--)
	{
	topScores[j] = topScores[j - 1];
	strcpy(player[j], player[j - 1]);
	}
	topScores[i] = (scoreIndex - 1) * 10;
	strcpy(player[i], name);
	break;

	}
	}

	fclose(fp);
	*/
	/*
	fp = fopen("highscorex.txt", "w");
	for (i = 0; i<3; i++)
	{
	fprintf(fp, "%s %d\n", player[i], topScores[i]);
	}
	fclose(fp);
	*/
}


int main()
{
	healthNo = 5;

	setAll();
	iInitialize(screenWidth, screenHeight, "Tank Warfare I.O.");
	imageLoaded();

	setEnemyVariables();
	colisionCheckTimer = iSetTimer(0, colisionCheck);

	bombCollisionTimer = iSetTimer(0, bombCollision);
	fireTimer = iSetTimer(0, shoot);

	bombTankCollisionHealthTimer = iSetTimer(0, bombTankCollisionHealth);

	//highScoreX( scoreIndex, name);


	musicTimer = iSetTimer(1500, music);

	setBombVariables();
	setExtraBombVariables();



	iStart();
	return 0;

}

