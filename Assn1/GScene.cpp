#include "GScene.h"
#include "mat.h"
#include <algorithm>
#include <iostream>
#include <queue>
#include "GameMap.h"
#include "Player.h"

float camloc;
float camlocY;
double rot;
float PlayerX;
mat4 V;
extern GLint u_Projection;
extern GLuint program;

GScene::GScene()
: GObject(Rect(0,0,0,0), Rect(0,0,0,0), "SCENE") {
	setCameraMode(CHICKEN);
	cam_x = 0;
	cam_y = 0;
}
void GScene::drawScene() {
	/* Draws all elements in the scene */
	mat4 MVMatrix = mat4();
	vec4 rotatedvec;
	switch (mode_cam) {
	case TOP:
		MVMatrix *= Angel::LookAt(
			vec4(camloc, 0, 100, 1),
			vec4(camloc, 0, -1, 1),
			vec4(0, 1, 0, 1)
			);
		V = Angel::LookAt(
			vec4(camloc, 0, 100, 1),
			vec4(camloc, 0, -1, 1),
			vec4(0, 1, 0, 1)
		);
		break;
	case POV:
	{
		vec3 cnt = vec3(camloc+30, camlocY, 10);
		vec3 ori = vec3(camloc+40, camlocY, 10);
		vec3 lay = vec3(camloc + 50, camlocY, 8);
		vec3 sub = lay - cnt;
		vec3 subori = ori - cnt;
		vec4 rotd = RotateZ(rot)*sub;
		vec4 rotori = RotateZ(rot)*subori;
		vec4 rotatedvec = rotd + cnt;
		vec4 rotatedori = rotori + cnt;
		/*if (rot == 0.0) rotatedvec = vec4(camloc + 50, camlocY, 8, 1);
		else if (rot == 90.0) rotatedvec = vec4(camloc + 30, camlocY+30, 8, 1);
		else if (rot == 180.0) rotatedvec = vec4(camloc - 10, camlocY, 8, 1);
		else rotatedvec = vec4(camloc + 30, camlocY-30, 8, 1);*/
		MVMatrix *= Angel::LookAt(
			rotatedori,
			rotatedvec,
			vec4(0, 0, 1, 1)
			);
		V = Angel::LookAt(
			rotatedori,
			rotatedvec,
			vec4(0, 0, 1, 1)
		);
		break;
	}
	case SHOULDER:
		MVMatrix *= Angel::LookAt(
			vec4(camloc, camlocY-5, 20, 1),
			vec4(camloc+30, camlocY-5, 0, 1),
			vec4(1, 0, 0, 1)
			);
		V = Angel::LookAt(
			vec4(camloc, camlocY - 5, 20, 1),
			vec4(camloc + 30, camlocY - 5, 0, 1),
			vec4(1, 0, 0, 1)
		);
		break;
	case CHICKEN:
		MVMatrix *= Angel::LookAt(
			vec4(-190, 0, 20, 1),
			vec4(-200, 0, 0, 1),
			vec4(1, 0, 0, 1)
			);
		V = Angel::LookAt(
			vec4(-190, 0, 20, 1),
			vec4(-200, 0, 0, 1),
			vec4(1, 0, 0, 1)
		);
	}
	GLint VV;
	VV = glGetUniformLocation(program, "V");
	glUniformMatrix4fv(VV, 1, true, V);
	onTraverseDraw(MVMatrix);
}
void GScene::updateScene() { /* Updates all elements in the scene. */
	onTraverseUpdate();
}
void GScene::setCameraMode(CameraMode mode) {
	this->mode_cam = mode;
	mat4 projection = mat4();
	switch (mode) {
		case TOP:
			projection = Ortho(0, GameMap::MAPHEIGHT, 0, GameMap::MAPHEIGHT, -400, 400);
			glUniformMatrix4fv(u_Projection, 1, true, projection);
			break;
		case POV:
			projection = Perspective(65, 1, 10, 1000);
			glUniformMatrix4fv(u_Projection, 1, true, projection);
			break;
		case CHICKEN:
		case SHOULDER:
			projection = Perspective(90, 1, 10, 1000);
			glUniformMatrix4fv(u_Projection, 1, true, projection);
			break;
	}
}
void GScene::draw(mat4 MVMatrix) {
	// nothing to draw. blank
}
void GScene::frameAction() {
	float cam_dest = getChildOfType("PLAYER")->getgloobj().x() - 30;
	float cam_destY = getChildOfType("PLAYER")->getgloobj().y() - 5;
	rot = getChildOfType("PLAYER")->getRotation();
	if (mode_cam == POV || mode_cam == SHOULDER) camloc = cam_dest;
	else {
		camloc = 0.3 * cam_dest + 0.7 * camloc;
		if (camloc < 0) camloc = 0;
	}
	camlocY = 0.3 * cam_destY + 0.7 * camlocY;
}
std::list<GObject*> GScene::getCollisionsOf(GObject* obj, std::string type) {
	/* I'll go with iterative traverse because returning copy of list in recursion is possibly too
	expensive. Traverse using BFS */
	std::queue<GObject*> travq;
	std::list<GObject*>* current_children;
	std::list<GObject*> result;

	travq.push(this);

	while(!travq.empty()){
		current_children = travq.front()->getChildren();
		travq.pop();
		for (std::list<GObject*>::iterator it = current_children->begin(); it != current_children->end(); it++) {
			if ((*it) != obj) {
				if (GObject::isCollide(*(*it), *obj) && (*it)->getType() == type) {
					result.push_front((*it));
				}
			}
			travq.push((*it));
		}
	}
	return result;
}
std::list<GObject*> GScene::getNonCollisions(GObject* obj) {
	//check for only first children. not grand children
	std::list<GObject*> result;
	for (std::list<GObject*>::iterator it = obj->getChildren()->begin();
	it != obj->getChildren()->end(); it++) {
		if (!GObject::isCollide(*(*it), *obj)) {
			result.push_front((*it));
		}
	}
	return result;

	/*std::queue<GObject*> travq;
	std::list<GObject*>* current_children;

	travq.push(this);

	while(!travq.empty()){
		current_children = travq.front()->getChildren();
		travq.pop();
		for (std::list<GObject*>::iterator it = current_children->begin(); it != current_children->end(); it++) {
			if ((*it) != obj) {
				if (!GObject::isCollide(*(*it), *obj)) {
					result.push_front((*it));
				}
			}
			travq.push((*it));
		}
	}
	return result; */
}
