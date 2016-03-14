#pragma once
#include "GObject.h"
#include <list>

class GScene {
private:
	std::list<GObject*> objects;
public:
	void drawAll();
	GObject* addObject(GObject* obj);
	GObject* removeObject(GObject* obj);
	std::list<GObject*> getCollisions(GObject* obj);
};
