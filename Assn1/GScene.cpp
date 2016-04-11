#include "GScene.h"
#include "mat.h"
#include <algorithm>
#include <iostream>
#include <queue>
#include "GameMap.h"

float camloc;
float PlayerX;

GScene::GScene()
: GObject(Rect(0,0,0,0), Rect(0,0,0,0), "SCENE") {
	cam_x = 0;
	cam_y = 0;
}
void GScene::drawScene() {
	/* Draws all elements in the scene */

	mat4 MVMatrix = mat4();
	MVMatrix *= Angel::LookAt(
		vec4(camloc, 0, 1, 1),
		vec4(camloc, 0, -1, 1),
		vec4(0, 1, 0, 1)
		); 
	onTraverseDraw(MVMatrix);
}
void GScene::updateScene() {
	/* Updates all elements in the scene. */
	onTraverseUpdate();
}
void GScene::draw(mat4 MVMatrix) {
	// nothing to draw. blank
}
void GScene::frameAction() {
	float cam_dest = getChildOfType("PLAYER")->getgloobj().x() - 30;
	camloc = 0.3 * cam_dest + 0.7 * camloc;
	if (camloc < 0) camloc = 0;
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
std::list<GObject*> GScene::getNonCollisions(GObject*obj) {
	std::queue<GObject*> travq;
	std::list<GObject*>* current_children;
	std::list<GObject*> result;

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
	return result;
}
