#include "GScene.h"
#include <algorithm>

void GScene::drawAll() {
	std::for_each(objects.begin(), objects.end(), [](GObject* obj) { obj->draw(); });
}
GObject* GScene::addObject(GObject* obj) {
	objects.push_back(obj);
}
GObject* GScene::removeObject(GObject* obj) {
	objects.erase(std::find(objects.begin(), objects.end(), obj));
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