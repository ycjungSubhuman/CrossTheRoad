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
	std::function<void(Rect& rect, int, int, int)> drawFunc = [](Rect& rect, int r, int g, int b)->void {
		double x = rect.x();
		double y = rect.y();
		double w = rect.width();
		double h = rect.height();
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(r,g,b);
		glRectf(x,y,x+w,y+h);
		glutSwapBuffers();
	};
	setFunc(drawFunc);
}
void GameMap::frameAction() {
	//Maybe color flickering when invincible item obtained??
	//Nothing to do for now.
}
