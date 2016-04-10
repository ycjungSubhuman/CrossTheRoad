#include "GameMap.h"
#include <stdlib.h>
#include <stdexcept>
#include <iostream>

/*void DrawRoadLine(int Maplength, int Mapheight, int x)
{
	double Linelength = Maplength / 20;
	double Lineheight = Mapheight / 12;
	glColor3f(1.0f, 1.0f, 1.0f);
	
	glRectf(x*Maplength - Linelength, 0, x*Maplength + Linelength, Lineheight);
	glRectf(x*Maplength - Linelength, 3 * Lineheight, x*Maplength + Linelength, 5 * Lineheight);
	glRectf(x*Maplength - Linelength, 7 * Lineheight, x*Maplength + Linelength, 9 * Lineheight);
	glRectf(x*Maplength - Linelength, 11 * Lineheight, x*Maplength + Linelength, 112 * Lineheight);
}*/

GameMap::GameMap() : GObject(Rect(0, 0, COLUMN_WIDTH*MAPLENGTH, MAPHEIGHT), Rect(0,0,0,0), "BACKGROUND")
{
	/* 맵 전체를 그리는 함수
	 mapinfo의 배열에 따라서 다른 맵을 그려야 한다*/
	//init mapinfo
	mapinfo = std::vector<Linetype>(MAPLENGTH);
	mapinfo[0] = GRASS;
	mapinfo[1] = rand()%2 ? ROADUP : ROADDOWN;
	mapinfo[MAPLENGTH - 2] = rand()%2 ? ROADUP : ROADDOWN;
	mapinfo[MAPLENGTH - 1] = GRASS; //the first and the last should be GRASS
	int prevroad = 0;
	std::cout << "MAPINFO: [";
	for (int i = 2; i < MAPLENGTH-2; i++) {
		if (prevroad < 3) {
			mapinfo[i] = rand() % 2 ? ROADUP : ROADDOWN;
			prevroad++;
		}
		else {
			switch (rand() % 5) {
				case 0: mapinfo[i] = ROADUP;
					break;
				case 1: mapinfo[i] = ROADDOWN;
					break;
				case 2: mapinfo[i] = GRASS;
					break;
				case 3: mapinfo[i] = WATERUP;
					break;
				case 4: mapinfo[i] = WATERDOWN;
			}
			if(mapinfo[i]==GRASS) prevroad = 0;
		}
		std::cout << mapinfo[i] << ", ";
	}
	std::cout << "]" << std::endl;
}
void GameMap::draw(mat4 MVMatrix) {
	/* ------------------------------------- */
	/* implement drawing using MVMatrix here */
	/* ------------------------------------- */

	/* glColor3f(51.0f/256.0f, 51.0f / 256.0f, 51.0f / 256.0f);
	glRectf(0.0f, 0.0f, MAPLENGTH * COLUMN_WIDTH, MAPHEIGHT);
	for (int i = 0; i < MAPLENGTH; i++)
	{
		if (getLine(i) == GRASS)
		{
			glColor3f(83.0f/256.0f, 255.0f/256.0f, 26.0f/256.0f);
			glRectf(i*COLUMN_WIDTH, 0.0f, (i + 1)*COLUMN_WIDTH, MAPHEIGHT);
		}
		else
		{
			if (getLine(i-1) != GRASS)
				DrawRoadLine(COLUMN_WIDTH, MAPHEIGHT, i);
		}		
	} */
}
GameMap::Linetype GameMap::getLine(int i) {
	if (i < 0) i = 0;
	try {
		return mapinfo.at(i);
	}
	catch (std::out_of_range) {
		std::cout << "Erorr: Gamemap deref out of range" << std::endl;
		throw 1;
	}
}
void GameMap::frameAction() {
	//Maybe color flickering when invincible item obtained??
	//Nothing to do for now.
}