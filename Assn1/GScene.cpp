#include "GScene.h"
#include <algorithm>
#include <iostream>

GScene::GScene()
: GObject(Rect(0,0,0,0), Rect(0,0,0,0), "SCENE") {
	cam_x = 0;
	cam_y = 0;
}
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
	// nothing to draw. blank
}
void GScene::frameAction() {
	/* ---------------------------- */
	/* implement camera moving here */
	/* ---------------------------- */
}
std::list<GObject*> GScene::getCollisionsOf(GObject* obj, std::string type) {
	std::list<GObject*>& current_children = getChildren();
}
