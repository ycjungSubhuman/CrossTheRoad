#include "GScene.h"
#include <algorithm>

GObject* GScene::addObject(GObject* obj) {
	objects.push_back(obj);
}
GObject* GScene::removeObject(GObject* obj) {
	objects.erase(std::find(objects.begin(), objects.end(), obj));
}
std::list<GObject*> GScene::getCollisions(GObject* obj) {
	std::list<GObject*> result;
	//check for collision.
	for (std::vector<GObject*>::iterator iter = objects.begin(); iter < objects.end(); iter++) {
		if (GObject::isCollide(*(*iter), *obj))
			result.push_front(obj);
	}
	return result;
}