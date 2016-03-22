#include "GameMap.h"
#include <stdlib.h>
#include <stdexcept>
#include <iostream>

GameMap::GameMap(int z) : GObject(Rect(0, 0, COLUMN_WIDTH*MAPLENGTH, MAPHEIGHT), Rect(0,0,0,0), z, "BACKGROUND")
{
	/* �� ��ü�� �׸��� �Լ�
	 mapinfo�� �迭�� ���� �ٸ� ���� �׷��� �Ѵ�*/
	//init mapinfo
	mapinfo = std::vector<Linetype>(MAPLENGTH);
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
}
void GameMap::draw() {
	/* implement map drawing here */
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
