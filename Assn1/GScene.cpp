#include "GScene.h"
#include "mat.h"
#include <algorithm>
#include <iostream>
#include <functional>

float camloc;
float PlayerX;

void GScene::drawScene() {
	/* Draws all elements in the scene */

	mat4 MVMatrix = identity();
	MVMatrix = LootAt(
		vec4(camloc, 0, 0, 1),
		vec4(camloc, 0, -1, 1),
		vec4(0, 1, 0, 1));
	onTraverseDraw(MVMatrix);
}
void GScene::updateScene() {
	/* Updates all elements in the scene. */
	onTraverseUpdate();
}
void GScene::draw(mat4 MVMatrix) {
	// nothing to draw
}
void GScene::frameAction() {
	float cam_dest = PlayerX;
	camloc = 0.1 * cam_dest + 0.9 * camloc;
}
std::list<GObject*> GScene::getCollisions(GObject* obj) {

}
std::list<GObject*> GScene::getCollisionsOf(GObject* obj, std::string type) {

}