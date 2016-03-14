#pragma once
#include "GObject.h"
#include <vector>
#include <list>

class GScene {
private:
	std::vector<GObject*> objects;
public:
	GObject* addObject(GObject* obj);
	GObject* removeObject(GObject* obj);
	std::list<GObject*> getCollisions(GObject* obj);
};
