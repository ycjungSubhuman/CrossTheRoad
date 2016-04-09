#include<Windows.h>
#include<GL/glew.h>
#include<GL/glut.h>
#include "stdlib.h"
#include <time.h>
#include "Game.h"
#include "Car.h"
#include "LogOnWater.h"
#include<iostream>
#include "shaderutil.h"

Game game;
double camloc = 0.0f;
double goalloc = 0.0f;
double portion = 0.5;

extern GLint u_Projection;

void genCar(int linenum) {
	//the car is generated by 1/3 chance
	if (rand() % 3 == 0) {
		Car* car = new Car(linenum, game.getMap()->getLine(linenum));
		game.getScene()->addObject(car, 4);
	}
	glutTimerFunc(Car::GENTIME, genCar, linenum);
}
void genLog(int linenum) {
	//the log is generated by 1/2 chance
	if (rand() % 2 == 0) {
		LogOnWater* log = new LogOnWater(linenum, game.getMap()->getLine(linenum));
		game.getScene()->addObject(log, 1);
	}
	glutTimerFunc(LogOnWater::GENTIME, genLog, linenum);
}
void init(void) {
	/* load default shaders */
	char vShaderFile[] = "VertexShader1.glsl";
	char fShaderFile[] = "FragmentShader1.glsl";
	loadShadersFromFile(vShaderFile, fShaderFile);

	/* init screen */
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);

	//initiate timer call loop for car and log generation
	for (int i = 0; i < GameMap::MAPLENGTH; i++) {
		int line = game.getMap()->getLine(i);
		if (line == GameMap::ROADDOWN || line == GameMap::ROADUP) {
			glutTimerFunc(Car::GENTIME+rand()%1000, genCar, i);
		}
		if (line == GameMap::WATERDOWN || line == GameMap::WATERUP) {
			glutTimerFunc(LogOnWater::GENTIME + rand() % 1000, genLog, i);
		}
	}

	//Set projection matrix by ortho2D
	mat4 projection = mat4();
	//projection = Ortho2D(0, GameMap::MAPHEIGHT * 2, 0, GameMap::MAPHEIGHT);
	glUniformMatrix4fv(u_Projection, 1, false, projection);
}
void drawView(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	/* Implement view function*/
	//game.getScene()->drawScene();
	ORect rec = ORect(0.0, 0.0, 1.0, 1.0, ORect::TOPLEFT, 0.0, "");
	mat4 mats = mat4();
	rec.draw(mats);

	glutSwapBuffers();
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
	case GLUT_KEY_LEFT:
		game.getPlayer()->move(Player::LEFT);
		break;
	}
}


void updateScene(int val)
{
	/* Implement Scene Update */

	//clear cars out of the map
	game.getScene()->updateScene();

	//check for collisions of car
	std::list<GObject*> car_col = game.getScene()->getCollisionsOf(game.getPlayer(), "CAR");

	//check for collisions of water
	std::list<GObject*> log_col = game.getScene()->getCollisionsOf(game.getPlayer(), "LOG");

	//check if the player is in water
	GameMap::Linetype current_coltype = game.getMap()->getLine(game.getPlayer()->getLinenum());

	//check for player death
	if (!car_col.empty() ||  //collision with car
		(log_col.empty() && (current_coltype==GameMap::WATERDOWN || current_coltype==GameMap::WATERUP))) {
		//^ no collisions with LogOnWater but in the water
		//game over
		game.newPlayer();
	}

	//check for log riding
	if (!log_col.empty()) {
		GameMap::Linetype linetype_of_next;
		switch (game.getPlayer()->getMoveDir()) {
		case Player::RIGHT:
			linetype_of_next = game.getMap()->getLine(game.getPlayer()->getLinenum()+1);
			break;
		case Player::LEFT:
			linetype_of_next = game.getMap()->getLine(game.getPlayer()->getLinenum()-1);
			break;
		default:
			linetype_of_next = game.getMap()->getLine(game.getPlayer()->getLinenum());
			break;
		}
		if (linetype_of_next == GameMap::WATERDOWN || linetype_of_next == GameMap::WATERUP) {
			//make the player ride the log
			if (game.getPlayer()->getPlayerStatus() == Player::ALIVE)
				game.getPlayer()->bindPlayerToCenter(log_col.front());
		}
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

	/* check for maximum camera location
	if (goalloc > (GameMap::MAPLENGTH - 9)*GameMap::COLUMN_WIDTH)
		goalloc = (GameMap::MAPLENGTH - 9)*GameMap::COLUMN_WIDTH;

	//camera move
	camloc = goalloc * portion + camloc * (1 - portion);
	glLoadIdentity();
	gluLookAt(
		camloc, 0, 0,
		camloc, 0, -1,
		0, 1, 0);	 */
	glutTimerFunc(20, updateScene, 0);
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	glewInit();
	init();

	glutDisplayFunc(drawView);
	glutSpecialFunc(processUserInput);
	//glutIdleFunc(updateScene);
	glutTimerFunc(20, updateScene, 0);
	glutMainLoop();
	return 0;
}