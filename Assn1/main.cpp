#include<Windows.h>
#include<GL/glew.h>
#include<GL/glut.h>
#include "stdlib.h"
#include <time.h>
#include "Game.h"
#include "ModelManager.h"
#include "Car.h"
#include "LogOnWater.h"
#include<iostream>
#include<algorithm>
#include "shaderutil.h"

Game* game;
ModelManager* modelManager;

extern GLuint rectbuffer;
extern GLint u_Projection;
extern GLint u_Model;
extern GLint color_in;

void genCar(int linenum) {
	//the car is generated by 1/3 chance
	if (rand() % 3 == 0) {
		Car* car = new Car(linenum, game->getMap()->getLine(linenum));
		game->getMap()->addObject(car, 4);
	}
	glutTimerFunc(Car::GENTIME, genCar, linenum);
}
void genLog(int linenum) {
	//the log is generated by 1/2 chance
	if (rand() % 2 == 0) {
		LogOnWater* log = new LogOnWater(linenum, game->getMap()->getLine(linenum));
		game->getMap()->addObject(log, 1);
	}
	glutTimerFunc(LogOnWater::GENTIME, genLog, linenum);
}
void respawnPlayer(int dummy) {
	game->newPlayer();
}
void init(void) {
	//make VAO
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	/* load default shaders */
	char vShaderFile[] = "VertexShader1.glsl";
	char fShaderFile[] = "FragmentShader1.glsl";
	loadShadersFromFile(vShaderFile, fShaderFile);

	//load models and init game
	modelManager = new ModelManager();
	modelManager->loadModelFromFile("object/player.wobj");
	modelManager->loadModelFromFile("object/christmastree/christmas_tree.wobj");
	modelManager->loadModelFromFile("object/policecar/police_car.wobj");
	modelManager->loadModelFromFile("object/taxi/Taxi.wobj");
	modelManager->loadModelFromFile("object/truck/truck_blue.wobj");

	game = new Game();

	/* init screen */
	glClearColor(33.0f/256.0f, 33.0f/256.0f, 157.0f/256.0f, 0.0f);

	//initiate timer call loop for car and log generation
	for (int i = 0; i < GameMap::MAPLENGTH; i++) {
		int line = game->getMap()->getLine(i);
		if (line == GameMap::ROADDOWN || line == GameMap::ROADUP) {
			glutTimerFunc(Car::GENTIME+rand()%1000, genCar, i);
		}
		if (line == GameMap::WATERDOWN || line == GameMap::WATERUP) {
			glutTimerFunc(LogOnWater::GENTIME + rand() % 1000, genLog, i);
		}
	}

	//Set projection matrix by ortho2D
	mat4 projection = mat4();
	projection = Ortho(0, GameMap::MAPHEIGHT*2, 0, GameMap::MAPHEIGHT, 0, 1000);
	glUniformMatrix4fv(u_Projection, 1, true, projection);

	//set basic rect info 
	vec3 points[4] = { vec3(0, -1, 0), vec3(0, 0, 0), vec3(1, -1, 0), vec3(1, 0, 0)};

	glGenBuffers(1, &rectbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, rectbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	
	mciSendString("open \"dead.mp3\" type mpegvideo alias dead", NULL, 0, NULL);
	mciSendString("open \"pong_1.mp3\" type mpegvideo alias pong1", NULL, 0, NULL);
	mciSendString("open \"pong_2.mp3\" type mpegvideo alias pong2", NULL, 0, NULL);
	mciSendString("open \"CrossTheRoad_2.mp3\" type mpegvideo alias back", NULL, 0, NULL);
	mciSendString("play back repeat", NULL, 0, NULL);
	mciSendString("open \"CrossTheRoad_1.mp3\" type mpegvideo alias front", NULL, 0, NULL);
	mciSendString("play front repeat", NULL, 0, NULL);
	mciSendString("setaudio front Volume to 1", NULL, 0, NULL);

}
void drawView(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	/* Implement view function*/
	game->getScene()->drawScene();
	glutSwapBuffers();
}
void processUserInput(int key, int x, int y) {
	/* process User Input*/	
	switch (key) {
	case GLUT_KEY_UP:
		game->getPlayer()->move(Player::KEY_UP);
		break;
	case GLUT_KEY_DOWN:
		game->getPlayer()->move(Player::KEY_DOWN);
		break;
	case GLUT_KEY_RIGHT:
		game->getPlayer()->move(Player::KEY_RIGHT);
		break;
	case GLUT_KEY_LEFT:
		game->getPlayer()->move(Player::KEY_LEFT);
		break;
	}
}
void processPerspective(unsigned char key, int x, int y) {
	switch (key) {
		case '1':
			game->getScene()->setCameraMode(GScene::TOP);
			break;
		case '2':
			game->getScene()->setCameraMode(GScene::POV);
			break;
		case '3':
			game->getScene()->setCameraMode(GScene::SHOULDER);
			break;
	}

}


void updateScene(int val)
{
	/* Implement Scene Update */
	Rect player = game->getPlayer()->getgloobj();
	Rect parent = game->getPlayer()->getParent() -> getgloobj();

	if (game->getMap()->getLine(game->getPlayer()->getLinenum()) != GameMap::GRASS) {
		mciSendString("setaudio front Volume to 1000", NULL, 0, NULL);
	}
	else {
		mciSendString("setaudio front Volume to 1", NULL, 0, NULL);
	}

	//clear cars out of the map
	game->getScene()->updateScene();

	//check for collisions of car
	std::list<GObject*> car_col = game->getScene()->getCollisionsOf(game->getPlayer(), "CAR");

	//check for collisions of water
	std::list<GObject*> log_col = game->getScene()->getCollisionsOf(game->getPlayer(), "LOG");

	//check for out-of-map objects
	std::list<GObject*> map_noncol = game->getScene()->getNonCollisions(game->getMap());

	for (std::list<GObject*>::iterator it = map_noncol.begin(); it != map_noncol.end(); it++) {
		if ((*it)->getType() == "PLAYER") {
			map_noncol.erase(it);
			break;
		}
	}

	//clear out-of-map objects
	std::for_each(map_noncol.begin(), map_noncol.end(), [=](GObject* obj) {
		if (obj->getType() == "LOG" || obj->getType() == "CAR") {
			if (game->getPlayer()->isPlayerBound() && obj == game->getPlayer()->getBoundObject()) {
				game->newPlayer();
			}
			game->getScene()->removeObject(obj);
		}
		else {
			game->getScene()->removeObject(obj);
		}
	});

	//check if the player is in water
	GameMap::Linetype current_coltype = game->getMap()->getLine(game->getPlayer()->getLinenum());

	//check for player death
	if (!game->getPlayer()->isPlayerDead() && !car_col.empty() ||  //collision with car
		(game->getPlayer()->getMoveDir() == Player::NONE && log_col.empty() && (current_coltype==GameMap::WATERDOWN || current_coltype==GameMap::WATERUP))) {
		//^ no collisions with LogOnWater but in the water
		//game over
		if (!car_col.empty() && game->getPlayer()->getMoveDir()!=Player::NONE) {
			//bind to car
			game->getPlayer()->bindPlayerToCenter(car_col.front());
			game->getPlayer()->markDead(Player::HORIZONTAL);
		}
		else {
			game->getPlayer()->markDead(Player::VERTICAL);
		}
		glutTimerFunc(800, respawnPlayer, 0);
	}

	//check for log riding
	if (!log_col.empty()) {
		GameMap::Linetype linetype_of_next;
		switch (game->getPlayer()->getMoveDir()) {
		case Player::RIGHT:
			linetype_of_next = game->getMap()->getLine(game->getPlayer()->getLinenum()+1);
			break;
		case Player::LEFT:
			linetype_of_next = game->getMap()->getLine(game->getPlayer()->getLinenum()-1);
			break;
		default:
			linetype_of_next = game->getMap()->getLine(game->getPlayer()->getLinenum());
			break;
		}
		if (linetype_of_next == GameMap::WATERDOWN || linetype_of_next == GameMap::WATERUP) {
			//make the player ride the log
			if (game->getPlayer()->getPlayerStatus() == Player::ALIVE) {
				if (game->getPlayer()->getMoveDir() == Player::RIGHT)
					game->getPlayer()->incrLinenum(1);
				else if (game->getPlayer()->getMoveDir() == Player::LEFT)
					game->getPlayer()->incrLinenum(-1);
				//find the closet log
				std::list<GObject*>::iterator target_log = log_col.begin();
				if ((*target_log) == game->getPlayer()->getBoundObject()) {
					if (log_col.size() > 1) {
						target_log++;
						game->getPlayer()->bindPlayerToCenter(*target_log);
					}
				}
				else {
					game->getPlayer()->bindPlayerToCenter(*target_log);
				}
			}
		}
	}

	glEnableVertexAttribArray(color_in);
	//check for goal
	if (game->getPlayer()->getLinenum() == GameMap::MAPLENGTH - 1) {
		exit(0);
	}

	//check for tree collision
	std::list<GObject*> tree_col = game->getScene()->getCollisionsOf(game->getPlayer(), "TREE");
	if (!tree_col.empty()) {
		game->getPlayer()->undoMove();
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
	glutKeyboardFunc(processPerspective);
	//glutIdleFunc(updateScene);
	glutTimerFunc(20, updateScene, 0);
	glutMainLoop();
	return 0;
}
