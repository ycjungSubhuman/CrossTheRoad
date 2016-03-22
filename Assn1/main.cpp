#include<Windows.h>
#include<GL/GL.h>
#include<GL/glut.h>
#include "stdlib.h"
#include <time.h>
#include "Game.h"
#include "Car.h"

Game game;

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	srand((unsigned int)time(NULL));
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
	gluOrtho2D(0, 1, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void processUserInput(int key, int x, int y) {

	/* process User Input*/
}
void genCar(int linenum) {

}

void updateScene(int value)
{
	/* Implement Scene Update */
	//initiate timer call loop for car generation


	//check for player collisions

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