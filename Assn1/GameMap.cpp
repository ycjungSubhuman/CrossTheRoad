#include "GameMap.h"
#include <stdlib.h>

GameMap::GameMap(int z) : GObject(Rect(0, 0, COLUMN_WIDTH*MAPLENGTH, MAPHEIGHT), Rect(0,0,0,0), z, "BACKGROUND")
{
	/* 맵 전체를 그리는 함수
	 mapinfo의 배열에 따라서 다른 맵을 그려야 한다*/
	//init mapinfo
	mapinfo[0] = GRASS;
	mapinfo[1] = rand()%2 ? ROADUP : ROADDOWN;
	mapinfo[MAPLENGTH - 2] = rand()%2 ? ROADUP : ROADDOWN;
	mapinfo[MAPLENGTH - 1] = GRASS; //the first and the last should be GRASS
	int prevroad = 0;
	for (int i = 2; i < MAPLENGTH-2; i++) {
		if (prevroad < 3)
			mapinfo[i] = rand() % 2 ? ROADUP : ROADDOWN;
		else {
			switch (rand() % 3) {
				case 0: mapinfo[i] = ROADUP;
				case 1: mapinfo[i] = ROADDOWN;
				case 2: mapinfo[i] = GRASS;
			}
			if(mapinfo[i]==GRASS) prevroad = 0;
		}
	}
	//sets drawfunc
	std::function<void(Rect& rect, int, int, int)> drawFunc = [this](Rect& rect, int r, int g, int b)->void {
		glClear(GL_COLOR_BUFFER_BIT);
		int roadlength = 0;
		glColor3f(0.0f, 0.0f, 0.0f);
		glRectf(0.0f, 0.0f, MAPLENGTH * COLUMN_WIDTH, MAPHEIGHT);
		for (int i = 0; i < MAPLENGTH; i++)
		{
			switch (this.Getminfo(i))
			{
			case GRASS:
				glColor3f(0.0f, 1.0f, 0.0f);
				glRectf(i*COLUMN_WIDTH, 0.0f, (i + 1)*COLUMN_WIDTH, MAPHEIGHT);
				roadlength = 0;
				break;
			case ROADUP :
			case ROADDOWN :
				if (roadlength != 0)				
					DrawRoadLine(i);
		}		
		glutSwapBuffers();
	};
	setFunc(drawFunc);
}
void GameMap::frameAction() {
	//Maybe color flickering when invincible item obtained??
	//Nothing to do for now.
}
Linetype GameMap::Getminfo(int i)
{
	return mapinfo[i];
}
void GameMap::DrawRoadLine(int x)
{
	double Linelength = MAPLENGTH / 20;
	double Lineheight = MAPHEIGHT / 12;
	glColor3f(1.0f, 1.0f, 1.0f);
	for (int i = -1; i < 12; i+4)
	{
		glRectf(x*MAPLENGTH - Linelength, i*Lineheight, x*MAPLENGTH + Linelength, (i + 2)Lineheight);
	}
}