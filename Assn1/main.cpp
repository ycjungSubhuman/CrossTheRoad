#include<Windows.h>
#include<GL/GL.h>
#include<GL/glut.h>
#include<iostream>
#include "stdlib.h"
#include <time.h>
#include "Game.h"
#include "Car.h"

Game game;

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	/* Initiallize Objects */
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
	gluOrtho2D(0, GameMap::COLUMN_WIDTH*GameMap::MAPLENGTH, 0, GameMap::MAPHEIGHT);
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
		break;
	}
}
void genCar(int linenum) {

}

void updateScene(int value)
{
	/* Implement Scene Update */
	//initiate timer call loop for car generation


	//check for player collisions
	std::list<GObject*> tree_col = game.getScene()->getCollisionsOf(game.getPlayer(), "TREE");
	if (!tree_col.empty()) {
		std::cout << "treecollist : " << tree_col.size() << std::endl;
		game.getPlayer()->move(game.getPlayer()->getPrevDir());
	}

	glutTimerFunc(20, updateScene, 0);
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();

	glutDisplayFunc(drawView);
	glutReshapeFunc(reshape);
	glutSpecialFunc(processUserInput);
	glutTimerFunc(20, updateScene, 0);
	glutMainLoop();
	return 0;
}