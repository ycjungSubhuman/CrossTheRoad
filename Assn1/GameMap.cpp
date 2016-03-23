#include "GameMap.h"
#include <stdlib.h>
#include <stdexcept>
#include <iostream>

void DrawRoadLine(int Maplength, int Mapheight, int x)
{
	double Linelength = Maplength / 20;
	double Lineheight = Mapheight / 12;
	glColor3f(1.0f, 1.0f, 1.0f);
	for (int i = -1; i < 12; i + 4)
	{
		glRectf(x*Maplength - Linelength, i*Lineheight, x*Maplength + Linelength, (i + 2)*Lineheight);
	}
}

GameMap::GameMap(int z) : GObject(Rect(0, 0, COLUMN_WIDTH*MAPLENGTH, MAPHEIGHT), Rect(0,0,0,0), z, "BACKGROUND")
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
			switch (rand() % 3) {
				case 0: mapinfo[i] = ROADUP;
					break;
				case 1: mapinfo[i] = ROADDOWN;
					break;
				case 2: mapinfo[i] = GRASS;
					break;
			}
			if(mapinfo[i]==GRASS) prevroad = 0;
		}
		std::cout << mapinfo[i] << ", ";
	}
	std::cout << "]" << std::endl;
}
void GameMap::draw() {
	/* implement map drawing here */
	int roadlength = 0;
	glColor3f(0.0f, 0.0f, 0.0f);
	glRectf(0.0f, 0.0f, MAPLENGTH * COLUMN_WIDTH, MAPHEIGHT);
	for (int i = 0; i < MAPLENGTH; i++)
	{
		switch (getLine(i))
		{
		case GRASS:
			glColor3f(0.0f, 1.0f, 0.0f);
			glRectf(i*COLUMN_WIDTH, 0.0f, (i + 1)*COLUMN_WIDTH, MAPHEIGHT);
			roadlength = 0;
			break;
		case ROADUP:
		case ROADDOWN:
			if (roadlength != 0)
				DrawRoadLine(MAPLENGTH, MAPHEIGHT, i);
		}		
	}
}
GameMap::Linetype GameMap::getLine(int i) {
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