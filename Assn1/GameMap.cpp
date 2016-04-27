#include "GameMap.h"
#include <stdlib.h>
#include <stdexcept>
#include <iostream>

void DrawRoadLine(int Maplength, int Mapheight, int x, mat4 MVMatrix)
{
	double Linelength = Maplength / 20;
	double Lineheight = Mapheight / 12;
	
	ORect* maprect = new ORect(x*Maplength - Linelength, 0, 2*Linelength, Lineheight, ORect::BOTTOMLEFT, 0.0f, "GAMEMAPROAD");
	maprect->setColor(255,255,255);

	maprect->draw(MVMatrix * Translate(x*Maplength - Linelength, 0, 0));
	maprect->draw(MVMatrix * Translate(x*Maplength - Linelength, -3 * Lineheight, 0));
	maprect->draw(MVMatrix * Translate(x*Maplength - Linelength, -6 * Lineheight, 0));
	maprect->draw(MVMatrix * Translate(x*Maplength - Linelength, -9 * Lineheight, 0));
	maprect->draw(MVMatrix * Translate(x*Maplength - Linelength, -12 * Lineheight, 0));

	delete(maprect);
}

GameMap::GameMap(GameMap::GameMode mode) : GObject(Rect(0, MAPHEIGHT, COLUMN_WIDTH*MAPLENGTH, MAPHEIGHT), Rect(0,-MAPHEIGHT/2,COLUMN_WIDTH*MAPLENGTH*2,MAPHEIGHT*4), "BACKGROUND")
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
			if (mode & MODE_ROAD && mode & MODE_WATER) {
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
			}
			else if (mode & MODE_ROAD) {
				switch (rand() % 3) {
					case 0: mapinfo[i] = ROADUP;
						break;
					case 1: mapinfo[i] = ROADDOWN;
						break;
					case 2: mapinfo[i] = GRASS;
				}
			}
			else {
				std::cerr << "Invalid GameMap Option" << std::endl;
				system("pause");
				exit(1);
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
	ORect* back_maprect = new ORect(0.0f, 0.0f, MAPLENGTH * COLUMN_WIDTH, 2000, ORect::BOTTOMLEFT, 0.0f, "GAMEMAP");
	back_maprect->setColor(44, 128, 44);
	back_maprect->draw(MVMatrix*Translate(0, 1000, 0));
	delete back_maprect;

	ORect* maprect = new ORect(0.0f, 0.0f, MAPLENGTH * COLUMN_WIDTH, MAPHEIGHT, ORect::BOTTOMLEFT, 0.0f, "GAMEMAP");
	maprect->setColor(51, 51, 51);
	maprect->draw(MVMatrix);
	
	ORect* grassrect = new ORect(0.0, 0.0f, COLUMN_WIDTH, MAPHEIGHT, ORect::BOTTOMLEFT, 0.0f, "GAMEMAPGRASS");
	grassrect->setColor(83, 255, 26);
	ORect* waterrect = new ORect(0.0, 0.0f, COLUMN_WIDTH, 2000, ORect::BOTTOMLEFT, 0.0f, "GAMEMAPWATER");
	waterrect->setColor(25, 30, 255);
	for (int i = 0; i < MAPLENGTH; i++)
	{
		if (getLine(i) == GRASS)
		{			
			grassrect->draw(MVMatrix * Translate(i*COLUMN_WIDTH, 0, 0));			
		}
		else if ((getLine(i) == WATERDOWN) || (getLine(i) == WATERUP))
		{
			waterrect->draw(MVMatrix * Translate(i*COLUMN_WIDTH, 1000, 0));
		}
		else
		{
			if ((getLine(i - 1) != GRASS) && (getLine(i - 1) != WATERDOWN) && (getLine(i - 1) != WATERUP))
				DrawRoadLine(COLUMN_WIDTH, MAPHEIGHT, i, MVMatrix);
		}
	}
	delete(maprect);
	delete(grassrect);

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