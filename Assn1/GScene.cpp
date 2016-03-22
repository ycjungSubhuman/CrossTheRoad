#include "GScene.h"
#include <algorithm>

void GScene::drawAll() {
	std::for_each(objects.begin(), objects.end(), [](GObject* obj) { obj->draw(); });
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
		if (std::next(i, 1) == objects.end()) {
			objects.insert(std::next(i, 1), obj);
		}
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