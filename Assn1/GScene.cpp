#include "GScene.h"
#include <algorithm>
#include <iostream>
#include <functional>


void GScene::drawScene() {
	/* Draws all elements in the scene */

	mat4 MVMatrix = identity();
	/* ------------------------------------- */
	/* Implement making camera MVMatrix here */
	/* ------------------------------------- */
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
	/* ---------------------------- */
	/* implement camera moving here */
	/* ---------------------------- */
}
std::list<GObject*> GScene::getCollisions(GObject* obj) {

}
std::list<GObject*> GScene::getCollisionsOf(GObject* obj, std::string type) {

}