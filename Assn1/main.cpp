#include<Windows.h>
#include<GL/GL.h>
#include<GL/glut.h>
#include<iostream>
#include "stdlib.h"
#include <time.h>
#include "Game.h"
#include "Car.h"

Game game;
double camloc = 0.0f;
double goalloc = 0.0f;
double portion = 0.5;
void genCar(int linenum) {
	//the car is generated by 1/3 chance
	if (rand() % 3 == 0) {
		Car* car = new Car(linenum, game.getMap()->getLine(linenum));
		game.getScene()->addObject(car);
	}
	glutTimerFunc(Car::GENTIME, genCar, linenum);
}
void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);

	//initiate timer call loop for car generation
	for (int i = 0; i < GameMap::MAPLENGTH; i++) {
		int line = game.getMap()->getLine(i);
		if (line == GameMap::ROADDOWN || line == GameMap::ROADUP) {
			glutTimerFunc(Car::GENTIME+rand()%200, genCar, i);
		}
	}
}
void drawView(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	/* Implement view function*/
	game.getScene()->drawAll();

	glutSwapBuffers();
}
void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, GameMap::MAPHEIGHT*2, 0, GameMap::MAPHEIGHT);
	//gluOrtho2D(0, GameMap::MAPHEIGHT, 0, GameMap::MAPHEIGHT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void processUserInput(int key, int x, int y) {
	/* process User Input*/	
	switch (key) {
	case GLUT_KEY_UP:
		game.getPlayer()->move(Player::UP);
		break;
	case GLUT_KEY_DOWN:
		game.getPlayer()->move(Player::DOWN);
		break;
	case GLUT_KEY_RIGHT:
		game.getPlayer()->move(Player::RIGHT);
		goalloc = (game.getPlayer()->getX() - 5);		
		std::cout << "player : " << camloc << std::endl;		
		break;
	}	
}


void updateScene(int val)
{
	/* Implement Scene Update */
	//clear cars out of the map
	game.getScene()->updateAll();
	game.getScene()->clearOutOfRect(Rect(-20, GameMap::MAPHEIGHT+20, 1600, 1200));

	//check for death
	std::list<GObject*> car_col = game.getScene()->getCollisionsOf(game.getPlayer(), "CAR");
	if (!car_col.empty()) {
		//game over
		game.newPlayer();
		goalloc = 0.0f;
	}

	//check for goal
	if (game.getPlayer()->getLinenum() == GameMap::MAPLENGTH - 2) {
		std::cout << "WIN" << std::endl;
		exit(0);
	}

	//check for tree collision
	std::list<GObject*> tree_col = game.getScene()->getCollisionsOf(game.getPlayer(), "TREE");
	if (!tree_col.empty()) {
		game.getPlayer()->undoMove();
	}

	//check for maximum camera location
	if (goalloc > (GameMap::MAPLENGTH - 9)*GameMap::COLUMN_WIDTH)
		goalloc = (GameMap::MAPLENGTH - 9)*GameMap::COLUMN_WIDTH;

	//camera move
	camloc = goalloc * portion + camloc * (1 - portion);
	glLoadIdentity();
	gluLookAt(
		camloc, 0, 0,
		camloc, 0, -1,
		0, 1, 0);	
	glutTimerFunc(20, updateScene, 0);
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();

	glutDisplayFunc(drawView);
	glutReshapeFunc(reshape);
	glutSpecialFunc(processUserInput);
	//glutIdleFunc(updateScene);
	glutTimerFunc(20, updateScene, 0);
	glutMainLoop();
	return 0;
}