#include "GScene.h"
#include <algorithm>
#include <iostream>
#include <functional>


void GScene::drawScene() {
	/* Draws all elements in the scene. trasversing down to the leaf
	in the left->right BFS trasversing*/
	onTrasverseDo([](GObject* obj)->void { 
		obj->draw();
	});
}
void GScene::updateScene() {
	/* Updates all elements in the scene. trasversing down to the leaf
	in the left->right BFS trasversing*/
	onTrasverseDo([](GObject* obj)->void {
		obj->frameAction();
	});
}
void GScene::clearOutOfRect(Rect& rect) {
	/* Checks if there are nodes outside of specified Rect.
	If there are, delete them from the Scene Graph */
	onTrasverseDo([&rect](GObject* obj)->void {
		//callbacks for all the 1st child nodes
		if (!Rect::isCollide(obj->getobj(), rect)) {
			//if the object is not colliding with the given rect
			//remove this node from this tree 
			obj->getParent()->removeObject(obj);
		}
	});
}
std::list<GObject*> GScene::getCollisions(GObject* obj) {
	/* Trasverse Down to the Scene graph using left-side BFS. 
	If found any collisions, returns the list of objects*/
	std::list<GObject*> result;
	//check for collision.
	for (std::list<GObject*>::iterator iter = objects.begin(); iter != objects.end(); iter++) {
		if (GObject::isCollide(*(*iter), *obj))
			result.push_front(obj);
	}
	return result;
}
std::list<GObject*> GScene::getCollisionsOf(GObject* obj, std::string type) {
	/* The same method as getCollisions. The only difference if that
	it returns only the GObjects of certain types */
	std::list<GObject*> result;
	//check for collision.
	for (std::list<GObject*>::iterator iter = objects.begin(); iter != objects.end(); iter++) {
		if (GObject::isCollide(*(*iter), *obj) && (*iter)->getType()==type)
			result.push_front(obj);
	}
	return result;
}
