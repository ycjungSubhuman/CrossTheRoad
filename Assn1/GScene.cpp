#include "GScene.h"
#include <algorithm>
#include <iostream>

GScene::~GScene() {
	//delete all objects in the scene
	std::for_each(objects.begin(), objects.end(), [](GObject* obj) {delete obj; });
}
void GScene::drawAll() {
	std::for_each(objects.begin(), objects.end(), [](GObject* obj) { 
		obj->draw(); 
	});
}
void GScene::updateAll() {
	std::for_each(objects.begin(), objects.end(), [](GObject* obj) {
		obj->frameAction();
	});
}
void GScene::clearOutOfRect(Rect& rect) {
	for (std::list<GObject*>::iterator it = objects.begin(); it != objects.end();) {
		if (!Rect::isCollide(rect, (*it)->getobj())) {
			it = objects.erase(it);
		}
		else {
			it++;
		}
	}
}
GObject* GScene::addObject(GObject* obj) {
	bool isAdded = false;
	//keeps z index ordered ascending
	for (std::list<GObject*>::iterator i = objects.begin(); i != objects.end(); i++) {
		if (obj->getZ() < (*i)->getZ()) {
			isAdded = true;
			objects.insert(i, obj);
			break;
		}
	}
	if (!isAdded) {
		objects.push_back(obj);
	}
	return obj;
}
GObject* GScene::removeObject(GObject* obj) {
	objects.erase(std::find(objects.begin(), objects.end(), obj));
	return obj;
}
std::list<GObject*> GScene::getCollisions(GObject* obj) {
	std::list<GObject*> result;
	//check for collision.
	for (std::list<GObject*>::iterator iter = objects.begin(); iter != objects.end(); iter++) {
		if (GObject::isCollide(*(*iter), *obj))
			result.push_front(obj);
	}
	return result;
}
std::list<GObject*> GScene::getCollisionsOf(GObject* obj, std::string type) {
	std::list<GObject*> result;
	//check for collision.
	for (std::list<GObject*>::iterator iter = objects.begin(); iter != objects.end(); iter++) {
		if (GObject::isCollide(*(*iter), *obj) && (*iter)->getType()==type)
			result.push_front(obj);
	}
	return result;
}